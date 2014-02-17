// DlgProxy.h: header file
//

#pragma once

class CCommomClientConfigDlg;


// CCommomClientConfigDlgAutoProxy command target

class CCommomClientConfigDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CCommomClientConfigDlgAutoProxy)

	CCommomClientConfigDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CCommomClientConfigDlg* m_pDialog;

// Operations
public:

// Overrides
	public:
	virtual void OnFinalRelease();

// Implementation
protected:
	virtual ~CCommomClientConfigDlgAutoProxy();

	// Generated message map functions

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CCommomClientConfigDlgAutoProxy)

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

