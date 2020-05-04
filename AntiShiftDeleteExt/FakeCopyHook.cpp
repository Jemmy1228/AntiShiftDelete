#include "pch.h"
#include "FakeCopyHook.h"

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
