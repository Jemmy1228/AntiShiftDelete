#include "pch.h"
#include "FakeObjectWithSite.h"

STDMETHODIMP CFakeObjectWithSite::GetSite(
    REFIID riid,
    void** ppvSite
)
{
    return IObjectWithSiteImpl<CFakeObjectWithSite>::GetSite(riid, ppvSite);
}

STDMETHODIMP CFakeObjectWithSite::SetSite(
    IUnknown* pUnkSite
)
{
    return IObjectWithSiteImpl<CFakeObjectWithSite>::SetSite(pUnkSite);
}
