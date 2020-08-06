#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "AntiShiftDeleteExt_i.h"
#include "dllmain.h"
#include "compreg.h"
#include "CFileOperation.h"

CAntiShiftDeleteExtModule _AtlModule;

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        MessageBeep(MB_ICONINFORMATION);
        if (!SUCCEEDED(HookFileOperation())) {
            MessageBoxW(NULL, L"Hook Failed", L"AntiShiftDelete", MB_OK | MB_ICONERROR);
        }
    }
    if (dwReason == DLL_PROCESS_DETACH) {
        MessageBeep(MB_ICONSTOP);
        if (!SUCCEEDED(UnHookFileOperation())) {
            MessageBoxW(NULL, L"UnHook Failed", L"AntiShiftDelete", MB_OK | MB_ICONERROR);
        }
    }
    hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved);
}
