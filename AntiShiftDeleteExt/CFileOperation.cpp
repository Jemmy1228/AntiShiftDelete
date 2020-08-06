#include "pch.h"
#include "CFileOperation.h"
#include <Windows.h>
#include <detours.h>

using fntDeleteItem = decltype(DeleteItem);
using fntDeleteItems = decltype(DeleteItems);
using fntSetOperationFlags = decltype(SetOperationFlags);
fntDeleteItem* pOldDeleteItem = NULL;
fntDeleteItems* pOldDeleteItems = NULL;
fntSetOperationFlags* pOldSetOperationFlags = NULL;
DWORD dwOperationFlags = 0;

STDMETHODIMP HookFileOperation()
{
    HRESULT hr = S_OK;
    IFileOperation* pfo = NULL;

    if (!SUCCEEDED(hr = CoInitialize(NULL))
        || !SUCCEEDED(hr = CoCreateInstance(CLSID_FileOperation, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pfo))))
        return hr;

    /* Reference https://www.freebuf.com/column/134192.html */
    PVOID** vtbl = (PVOID**)pfo;
    pOldDeleteItem = (fntDeleteItem*)vtbl[0][DeleteItem_Index];
    pOldDeleteItems = (fntDeleteItems*)vtbl[0][DeleteItems_Index];
    pOldSetOperationFlags = (fntSetOperationFlags*)vtbl[0][SetOperationFlags_Index];

    if (DetourTransactionBegin() != NO_ERROR
        || DetourAttach(&(PVOID&)pOldDeleteItem, DeleteItem) != NO_ERROR
        || DetourAttach(&(PVOID&)pOldDeleteItems, DeleteItems) != NO_ERROR
        || DetourAttach(&(PVOID&)pOldSetOperationFlags, SetOperationFlags) != NO_ERROR
        || DetourTransactionCommit() != NO_ERROR)
        return E_FAIL;

    return S_OK;
}

STDMETHODIMP UnHookFileOperation()
{
    if (DetourTransactionBegin() != NO_ERROR
        || DetourDetach(&(PVOID&)pOldDeleteItem, DeleteItem) != NO_ERROR
        || DetourDetach(&(PVOID&)pOldDeleteItems, DeleteItems) != NO_ERROR
        || DetourDetach(&(PVOID&)pOldSetOperationFlags, SetOperationFlags) != NO_ERROR
        || DetourTransactionCommit() != NO_ERROR)
        return E_FAIL;

    return S_OK;
}

STDMETHODIMP DeleteItem(
    IFileOperation* pfo,
    IShellItem* psiItem,
    IFileOperationProgressSink* pfopsItem
)
{
    BOOLEAN ALLOWUNDO = (dwOperationFlags & FOF_ALLOWUNDO) != 0;
    BOOLEAN RECYCLEONDELETE = (dwOperationFlags & FOFX_RECYCLEONDELETE) != 0;
    BOOLEAN RECYCLEBIN = dwOperationFlags == 0x4000110; /* Empty RecycleBin */

    if (!ALLOWUNDO && !RECYCLEONDELETE && !RECYCLEBIN) {
        MessageBeep(MB_ICONWARNING);
        return E_ABORT;
    }

    return (*pOldDeleteItem)(pfo, psiItem, pfopsItem);
}

STDMETHODIMP DeleteItems(
    IFileOperation* pfo,
    IUnknown* punkItems
)
{
    BOOLEAN ALLOWUNDO = (dwOperationFlags & FOF_ALLOWUNDO) != 0;
    BOOLEAN RECYCLEONDELETE = (dwOperationFlags & FOFX_RECYCLEONDELETE) != 0;
    BOOLEAN RECYCLEBIN = dwOperationFlags == 0x4000110; /* Empty RecycleBin */

    if (!ALLOWUNDO && !RECYCLEONDELETE && !RECYCLEBIN) {
        MessageBeep(MB_ICONWARNING);
        return E_ABORT;
    }

    return (*pOldDeleteItems)(pfo, punkItems);
}

STDMETHODIMP SetOperationFlags(
    IFileOperation* pfo,
    DWORD dwFlags
)
{
    dwOperationFlags = dwFlags;
    return (*pOldSetOperationFlags)(pfo, dwFlags);
}
