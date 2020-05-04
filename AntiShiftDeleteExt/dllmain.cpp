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
        if (SUCCEEDED(InitializeHook()))
            MessageBoxW(NULL, L"Hook Succeeded", L"AntiShiftDelete", MB_OK);
        else
            MessageBoxW(NULL, L"Hook Succeeded", L"AntiShiftDelete", MB_OK | MB_ICONERROR);
    }
    hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved);
}
