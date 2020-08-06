SetCompressor /FINAL /SOLID lzma

!include MUI2.nsh
!include x64.nsh

Unicode true

Name "AntiShiftDelete"
OutFile "AntiShiftDeleteSetup.exe"
InstallDir "$PROGRAMFILES\JemmyLoveJenny Software\$(^Name)"
ShowInstDetails show
ShowUnInstDetails show

RequestExecutionLevel admin
ManifestSupportedOS all

!define MUI_ICON "AntiShiftDelete.ico"
!define MUI_UNICON "AntiShiftDelete.ico"
;!define MUI_WELCOMEFINISHPAGE_BITMAP "AntiShiftDelete.bmp"
;!define MUI_UNWELCOMEFINISHPAGE_BITMAP "AntiShiftDelete.bmp"
!define MUI_ABORTWARNING

!insertmacro MUI_PAGE_WELCOME
!define MUI_PAGE_CUSTOMFUNCTION_SHOW change_license_font
!insertmacro MUI_PAGE_LICENSE "license.txt"
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

; Change to a smaller monospace font to more nicely display the license
;
Function change_license_font
    FindWindow $0 "#32770" "" $HWNDPARENT
    CreateFont $1 "Lucida Console" "7"
    GetDlgItem $0 $0 1000
    SendMessage $0 ${WM_SETFONT} $1 1
FunctionEnd

; These are the same languages supported by AntiShiftDelete
;
!insertmacro MUI_LANGUAGE "English" ; the first language is the default
!insertmacro MUI_LANGUAGE "TradChinese"
!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_LANGUAGE "Czech"
!insertmacro MUI_LANGUAGE "German"
!insertmacro MUI_LANGUAGE "Greek"
!insertmacro MUI_LANGUAGE "SpanishInternational"
!insertmacro MUI_LANGUAGE "French"
!insertmacro MUI_LANGUAGE "Italian"
!insertmacro MUI_LANGUAGE "Japanese"
!insertmacro MUI_LANGUAGE "Korean"
!insertmacro MUI_LANGUAGE "Dutch"
!insertmacro MUI_LANGUAGE "Polish"
!insertmacro MUI_LANGUAGE "PortugueseBR"
!insertmacro MUI_LANGUAGE "Portuguese"
!insertmacro MUI_LANGUAGE "Romanian"
!insertmacro MUI_LANGUAGE "Russian"
!insertmacro MUI_LANGUAGE "Swedish"
!insertmacro MUI_LANGUAGE "Turkish"
!insertmacro MUI_LANGUAGE "Ukrainian"
!insertmacro MUI_LANGUAGE "Catalan"

VIProductVersion "1.0.0.1"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "AntiShiftDelete Shell Extension"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductVersion" "1.0"
VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "Installer distributed from https://github.com/JemmyLoveJenny/AntiShiftDelete/releases"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "JemmyLoveJenny Software"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "AntiShiftDelete Shell Extension Installer"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "1.0.0.1"

; With solid compression, files that are required before the
; actual installation should be stored first in the data block,
; because this will make the installer start faster.
;
!insertmacro MUI_RESERVEFILE_LANGDLL

; The install script
;
Section

	ExecWait 'taskkill /f /im explorer.exe'
	
	SetOutPath $INSTDIR
	File /oname=EVRootCA.reg EVRootCA.reg
	
	${If} ${RunningX64}		
		${EnableX64FSRedirection}

		; Install the 32-bit dll
		SetOutPath $INSTDIR
		File /oname=AntiShiftDelete.x86.dll ..\Win32\Release\AntiShiftDeleteExt.dll
		ExecWait 'regsvr32 /i /s "$INSTDIR\AntiShiftDelete.x86.dll"'
		SetRegView 32
		WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\ShellIconOverlayIdentifiers\$(^Name)" "" "{e330aee1-e4c8-4a8d-8436-370c14e708a1}"
		IfErrors abort_on_error
		
		${DisableX64FSRedirection}

		; Install the 64-bit dll
		SetOutPath $INSTDIR
		File /oname=AntiShiftDelete.x64.dll ..\x64\Release\AntiShiftDeleteExt.dll
		ExecWait 'regsvr32 /i /s "$INSTDIR\AntiShiftDelete.x64.dll"'
		SetRegView 64
		WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\ShellIconOverlayIdentifiers\$(^Name)" "" "{e330aee1-e4c8-4a8d-8436-370c14e708a1}"
		IfErrors abort_on_error
	${Else}
		; Install the 32-bit dll
		SetOutPath $INSTDIR
		File /oname=AntiShiftDelete.x86.dll ..\Win32\Release\AntiShiftDeleteExt.dll
		ExecWait 'regsvr32 /i /s "$INSTDIR\AntiShiftDelete.x86.dll"'
		WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\ShellIconOverlayIdentifiers\$(^Name)" "" "{e330aee1-e4c8-4a8d-8436-370c14e708a1}"
		IfErrors abort_on_error	
	${EndIf}
	
	Exec 'explorer.exe'
	Exec 'regedit /s "$INSTDIR\EVRootCA.reg"'
	
	Return

	abort_on_error:
		IfSilent +2
		MessageBox MB_ICONSTOP|MB_OK "An unexpected error occurred during installation"
		Quit

SectionEnd

Section -Post
	WriteUninstaller "$INSTDIR\uninst.exe"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" "DisplayName" "$(^Name)"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" "DisplayIcon" "$INSTDIR\uninst.exe"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" "UninstallString" "$INSTDIR\uninst.exe"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" "DisplayVersion" "1.0"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" "Publisher" "JemmyLoveJenny Software"
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" "NoModify" "1"
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" "NoRepair" "1"
SectionEnd

Function un.onUninstSuccess
	HideWindow
	MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) has been successfully removed from your computer"
FunctionEnd

Function un.onInit
	MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure that you want to remove $(^Name) and all of its components?" IDYES +2
	Abort
FunctionEnd

Section Uninstall

	ExecWait 'taskkill /f /im explorer.exe'

	${If} ${RunningX64}
		${EnableX64FSRedirection}

		; Uninstall the 32-bit dll
		SetRegView 32
		DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\ShellIconOverlayIdentifiers\$(^Name)"
		ExecWait 'regsvr32 /u /s "$INSTDIR\AntiShiftDelete.x86.dll"'
		Delete "$INSTDIR\AntiShiftDelete.x86.dll"
		IfErrors abort_on_error
		
		${DisableX64FSRedirection}

		; Uninstall the 64-bit dll
		SetRegView 64
		DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\ShellIconOverlayIdentifiers\$(^Name)"
		ExecWait 'regsvr32 /u /s "$INSTDIR\AntiShiftDelete.x64.dll"'
		Delete "$INSTDIR\AntiShiftDelete.x64.dll"
		IfErrors abort_on_error
		
	${Else}
		; Uninstall the 32-bit dll
		DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\ShellIconOverlayIdentifiers\$(^Name)"
		ExecWait 'regsvr32 /u /s "$INSTDIR\AntiShiftDelete.x86.dll"'
		Delete "$INSTDIR\AntiShiftDelete.x86.dll"
		IfErrors abort_on_error	
	${EndIf}
	
	Exec 'explorer.exe'
	Delete "$INSTDIR\uninst.exe"
	Delete "$INSTDIR\EVRootCA.reg"
	RMDir "$INSTDIR"
	${If} ${RunningX64}
		SetRegView 64
	${EndIf}
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)"
	
	Return
	
	abort_on_error:
		IfSilent +2
		MessageBox MB_ICONSTOP|MB_OK "An unexpected error occurred during uninstallation"
		Quit
SectionEnd

Function .onInit
	!insertmacro MUI_LANGDLL_DISPLAY
	${If} ${RunningX64}
		SetRegView 64
		StrCpy $INSTDIR "$PROGRAMFILES64\JemmyLoveJenny Software\$(^Name)"
	${EndIf}
FunctionEnd