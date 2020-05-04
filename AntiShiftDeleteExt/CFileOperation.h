#include "pch.h"
#include "Shlobj.h"

#define QueryInterface_Index 0
#define AddRef_Index (QueryInterface_Index + 1)
#define Release_Index (AddRef_Index + 1)
#define Advice_Index (Release_Index + 1)
#define Unadvise_Index (Advice_Index + 1)
#define SetOperationFlags_Index (Unadvise_Index + 1)
#define SetProgressMessage_Index (SetOperationFlags_Index + 1)
#define SetProgressDialog_Index (SetProgressMessage_Index + 1)
#define SetProperties_Index (SetProgressDialog_Index + 1)
#define SetOwnerWindow_Index (SetProperties_Index + 1)
#define ApplyPropertiesToItem_Index (SetOwnerWindow_Index + 1)
#define ApplyPropertiesToItems_Index (ApplyPropertiesToItem_Index + 1)
#define RenameItem_Index (ApplyPropertiesToItems_Index + 1)
#define RenameItems_Index (RenameItem_Index + 1)
#define MoveItem_Index (RenameItems_Index + 1)
#define MoveItems_Index (MoveItem_Index + 1)
#define CopyItem_Index (MoveItems_Index + 1)
#define CopyItems_Index (CopyItem_Index + 1)
#define DeleteItem_Index (CopyItems_Index + 1)
#define DeleteItems_Index (DeleteItem_Index + 1)
#define NewItem_Index (DeleteItems_Index + 1)
#define PerformOperations_Index (NewItem_Index + 1)
#define GetAnyOperationAborted_Index (PerformOperations_Index + 1)

STDMETHODIMP HookFileOperation();
STDMETHODIMP UnHookFileOperation();

/* The first parameter of interface function is "this", namely pfo */
STDMETHODIMP DeleteItem(
    IFileOperation* pfo,
    IShellItem* psiItem,
    IFileOperationProgressSink* pfopsItem
);

STDMETHODIMP DeleteItems(
    IFileOperation* pfo,
    IUnknown* punkItems
);

STDMETHODIMP SetOperationFlags(
    IFileOperation* pfo,
    DWORD dwFlags
);

