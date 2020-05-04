#include "pch.h"
#include "FakeCopyHook.h"

STDMETHODIMP_(HRESULT __stdcall) CFakeCopyHook::Initialize(
    PCIDLIST_ABSOLUTE pidlFolder,
    IDataObject* pdtobj,
    HKEY              hkeyProgID
)
{
    MessageBoxW(NULL, L"IShellExtInit::Initialize", L"AntiShiftDelete", MB_OK);
    return S_OK;
}

STDMETHODIMP_(UINT) CFakeCopyHook::CopyCallback(
    HWND    hwnd,
    UINT    wFunc,
    UINT    wFlags,
    PCTSTR  pszSrcFile,
    DWORD   dwSrcAttribs,
    LPCTSTR pszDestFile,
    DWORD   dwDestAttribs
)
{
    return IDYES;
}
