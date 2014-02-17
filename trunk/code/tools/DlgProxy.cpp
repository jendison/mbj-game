// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "CommomClientConfig.h"
#include "DlgProxy.h"
#include "CommomClientConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCommomClientConfigDlgAutoProxy

IMPLEMENT_DYNCREATE(CCommomClientConfigDlgAutoProxy, CCmdTarget)

CCommomClientConfigDlgAutoProxy::CCommomClientConfigDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CCommomClientConfigDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CCommomClientConfigDlg)))
		{
			m_pDialog = reinterpret_cast<CCommomClientConfigDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CCommomClientConfigDlgAutoProxy::~CCommomClientConfigDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CCommomClientConfigDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CCommomClientConfigDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCommomClientConfigDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// Note: we add support for IID_ICommomClientConfig to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {B8116DF4-67E8-49CB-B084-D2615BC48FF9}
static const IID IID_ICommomClientConfig =
{ 0xB8116DF4, 0x67E8, 0x49CB, { 0xB0, 0x84, 0xD2, 0x61, 0x5B, 0xC4, 0x8F, 0xF9 } };

BEGIN_INTERFACE_MAP(CCommomClientConfigDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CCommomClientConfigDlgAutoProxy, IID_ICommomClientConfig, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {28E9DF9D-E7FB-4B14-943F-CE3FD243DCBC}
IMPLEMENT_OLECREATE2(CCommomClientConfigDlgAutoProxy, "CommomClientConfig.Application", 0x28e9df9d, 0xe7fb, 0x4b14, 0x94, 0x3f, 0xce, 0x3f, 0xd2, 0x43, 0xdc, 0xbc)


// CCommomClientConfigDlgAutoProxy message handlers
