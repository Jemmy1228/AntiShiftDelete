#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "AntiShiftDeleteExt_i.h"
#include "dllmain.h"
#include "compreg.h"


using namespace ATL;

_Use_decl_annotations_
STDAPI DllCanUnloadNow(void)
{
    /* 
    return _AtlModule.DllCanUnloadNow();
    */

    /* To prevent the BHO from being unloaded, must return S_FALSE */
    return S_FALSE;
}

_Use_decl_annotations_
STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

_Use_decl_annotations_
STDAPI DllRegisterServer(void)
{
    HRESULT hr = _AtlModule.DllRegisterServer(FALSE);
    return hr;
}

_Use_decl_annotations_
STDAPI DllUnregisterServer(void)
{
    HRESULT hr = _AtlModule.DllUnregisterServer(FALSE);
    return hr;
}

STDAPI DllInstall(BOOL bInstall, _In_opt_  LPCWSTR pszCmdLine)
{
    HRESULT hr = E_FAIL;
    static const wchar_t szUserSwitch[] = L"user";

    if (pszCmdLine != nullptr)
    {
        if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
        {
            ATL::AtlSetPerUserRegistration(true);
        }
    }

    if (bInstall)
    {
        hr = DllRegisterServer();
        if (FAILED(hr))
        {
            DllUnregisterServer();
        }
    }
    else
    {
        hr = DllUnregisterServer();
    }

    return hr;
}


