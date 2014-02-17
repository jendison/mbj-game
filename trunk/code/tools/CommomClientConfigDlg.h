// CommomClientConfigDlg.h : header file
//

#pragma once
#include <iostream>
#include <fstream>
#include <afx.h>
#include <json/json.h>
class CCommomClientConfigDlgAutoProxy;


// CCommomClientConfigDlg dialog
class CCommomClientConfigDlg : public CDHtmlDialog
{
	DECLARE_DYNAMIC(CCommomClientConfigDlg);

	friend class CCommomClientConfigDlgAutoProxy;

// Construction
public:
	CCommomClientConfigDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CCommomClientConfigDlg();

// Dialog Data
	enum { IDD = IDD_COMMOMCLIENTCONFIG_DIALOG, IDH = IDR_HTML_COMMOMCLIENTCONFIG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);
	HRESULT OnButtonHelp(IHTMLElement *pElement);
	virtual BOOL CanAccessExternal ();
	 virtual void GotoUrl(LPCTSTR pszUrl);

	virtual BSTR open_file(BSTR path, BSTR model);
	virtual BSTR read_file(BSTR pos, BSTR len,BSTR strLength);
	virtual BSTR write_file(BSTR data,BSTR len,BSTR strLength);
	virtual BSTR tellg_file();
	virtual void seekg_file(BSTR pos);
	virtual void flush_file();
	virtual void close_file();
	virtual BSTR read_all();
	virtual void system(BSTR command);
	virtual BSTR get_dir(BSTR dir);
	//Ö´ÐÐÓÒ¼ü²Ëµ¥ÃüÁî
	virtual BSTR exe_contentCmd(BSTR path, BSTR cmd);

	STDMETHOD(GetHostInfo)(DOCHOSTUIINFO *pInfo);

	virtual void bak_file(BSTR path);
	LRESULT exe_JS(const char* pScript,VARIANT& ret, DISPPARAMS& param);
private:
	CFile file_;
	BOOL is_valid();

	void RecursiveFindFile(const CString& dir, Json::Value& out);
	HRESULT CallJSFunction(IHTMLDocument2* pDoc2,
		const CString& strFunctionName,
		DISPPARAMS* dispParams,
		VARIANT* varResult,
		EXCEPINFO* exceptInfo,
		UINT* nArgErr );
// Implementation
protected:
	HRESULT GetContextMenuForFSItem(LPCWSTR path,IContextMenu**ppCM);

	CCommomClientConfigDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
	//ÉùÃ÷º¯ÊýÓ³Éä
	DECLARE_DISPATCH_MAP()
};
