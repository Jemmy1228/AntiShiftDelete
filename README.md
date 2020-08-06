# AntiShiftDelete
## Introduction
AntiShiftDelete is a tiny Shell Extension which can disable the PermanentDelete (Shift+Delete) hot key.
Some people (including myself) got used to a habit, that they permanent delete everything instead of recycling to the recycle bin. However, this habit is not that good and might bring us much trouble if we deleted the wrong file/directory.
AntiShiftDelete is here to help those who want to get rid of this bad habit! After installing this extension, Windows Explorer will not delete the files when you press Shift+Delete, instead, it will play a beep sound to remind you that you should use normal delete hot key.

## Implemention
AntiShiftDelete uses the Microsoft detours library to hook the deletion functions inside the Windows Explorer.
So I decided that AntiShiftDelete should be a Shell Extension, as it can be loaded in to explorer.exe automatically.

### Shell Extension
There are a variety types of Shell Extensions. But in order that explorer.exe will load my extension as soon as possible, I choose to pretend a [IconOverlayHandler](https://docs.microsoft.com/en-us/windows/win32/shell/how-to-implement-icon-overlay-handlers) (implements [IShellIconOverlayIdentifier](https://docs.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-ishelliconoverlayidentifier)), which enables the extension to hook explorer.exe in no time.

### Hook
Microsoft Detours Library is really easy to use and I'm not going to talk about that. The methods to be hooked are very interesting.
In Windows Vista, 7, 8, 8.1, 10 and corresponding Server versions, the explorer.exe does not call Windows APIs directly. Rather, it uses FileOperation COM object to operate files. AntiShiftDelete is able to hook the virtual methods of FileOperation COM object and hold back Permanent Delete.

## Compatibility
In theory, Windows Vista and above, both x86 and x64 should be compatible with this extension, but I'm not sure......

Desktop Edition: Windows Vista, Windows 7, Windows 8, Windows 8.1, Windows 10
Server Edition: Server 2008, Server 2008 R2, Server 2012, Server 2012 R2, Server 2016