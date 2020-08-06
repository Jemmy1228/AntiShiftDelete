// FakeShellIconOverlayIdentifier.cpp: CFakeShellIconOverlayIdentifier 的实现

#include "pch.h"
#include "FakeShellIconOverlayIdentifier.h"


// CFakeShellIconOverlayIdentifier

STDMETHODIMP CFakeShellIconOverlayIdentifier::GetOverlayInfo(
	LPWSTR pwszIconFile,
	int    cchMax,
	int* pIndex,
	DWORD* pdwFlags
)
{
	return E_FAIL;
}

STDMETHODIMP CFakeShellIconOverlayIdentifier::GetPriority(
	int* pPriority
)
{
	return E_FAIL;
}

STDMETHODIMP CFakeShellIconOverlayIdentifier::IsMemberOf(
	LPCWSTR pwszPath,
	DWORD   dwAttrib
)
{
	return S_FALSE;
}
