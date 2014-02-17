
// CommomClientConfigDlg.cpp : implementation file
//
#include "stdafx.h"

#include <CString>

#include "CommomClientConfig.h"
#include "CommomClientConfigDlg.h"
#include "DlgProxy.h"
#include <comutil.h>
#include <json/json.h>
//extern "C"{
//#include <svn_client.h>
//#include <svn_wc.h>
//#include <svn_path.h>
//#include <svn_pools.h>
//#include <svn_cmdline.h>
//};

using namespace std;
using namespace _com_util;

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(lib, "comsuppw.lib")
#else
#pragma comment(lib, "comsupp.lib")
#endif
const int KXString = -1;
const int KXWString = -2;

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum
	{
		IDD = IDD_ABOUTBOX
	};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
// CCommomClientConfigDlg dialog
BEGIN_DHTML_EVENT_MAP(CCommomClientConfigDlg)
//DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
//DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
//DHTML_EVENT_ONCLICK(_T("ButtonHelp"), OnButtonHelp)
END_DHTML_EVENT_MAP()
BEGIN_DISPATCH_MAP(CCommomClientConfigDlg, CDHtmlDialog)
//DISP_FUNCTION(XExtendDHtmlDlg,"onSearch",onSearch,VT_BSTR,VTS_BSTR)
DISP_FUNCTION(CCommomClientConfigDlg, "open", open_file, VT_BSTR, VTS_BSTR VTS_BSTR)
DISP_FUNCTION(CCommomClientConfigDlg, "read", read_file, VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR)
DISP_FUNCTION(CCommomClientConfigDlg, "all", read_all, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CCommomClientConfigDlg, "write", write_file, VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR)
DISP_FUNCTION(CCommomClientConfigDlg, "tellg", tellg_file, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CCommomClientConfigDlg, "seekg", seekg_file, VT_NULL, VTS_BSTR)
DISP_FUNCTION(CCommomClientConfigDlg, "flush", flush_file, VT_NULL, VTS_NONE)
DISP_FUNCTION(CCommomClientConfigDlg, "close", close_file, VT_NULL, VTS_NONE)
DISP_FUNCTION(CCommomClientConfigDlg, "bak", bak_file, VT_NULL, VTS_BSTR)
DISP_FUNCTION(CCommomClientConfigDlg, "system", system, VT_NULL, VTS_BSTR)
DISP_FUNCTION(CCommomClientConfigDlg, "getDir", get_dir, VT_BSTR, VTS_BSTR)
DISP_FUNCTION(CCommomClientConfigDlg, "exeContentCmd", exe_contentCmd, VT_BSTR, VTS_BSTR VTS_BSTR)


END_DISPATCH_MAP()
IMPLEMENT_DYNAMIC(CCommomClientConfigDlg, CDHtmlDialog);

CCommomClientConfigDlg::CCommomClientConfigDlg(CWnd* pParent /*=NULL*/ ) : CDHtmlDialog(CCommomClientConfigDlg::IDD, CCommomClientConfigDlg::IDH, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CCommomClientConfigDlg::~CCommomClientConfigDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CCommomClientConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCommomClientConfigDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CCommomClientConfigDlg message handlers
BOOL CCommomClientConfigDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	//开启自动化
	EnableAutomation();

	//添加接口支持，让js认识本程序
	SetExternalDispatch(GetIDispatch(true));

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu*	pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);		// Set big icon
	SetIcon(m_hIcon, FALSE);	// Set small icon
	this->GotoUrl(TEXT("./html/CommomClientConfig.htm"));

	// TODO: Add extra initialization here
	return TRUE;				// return TRUE  unless you set the focus to a control
}

void CCommomClientConfigDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,

//  this is automatically done for you by the framework.
void CCommomClientConfigDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);	// device context for painting
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM> (dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);

		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags

//  the minimized window.
HCURSOR CCommomClientConfigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it

//  is dismissed.
void CCommomClientConfigDlg::OnClose()
{
	_variant_t  ret = TRUE;
	DISPPARAMS param = {0};
	if (SUCCEEDED(exe_JS("IsSave", ret, param)))
	{
		if (!ret.bVal)
		{
			return;
		}
	}

	if (CanExit())
		CDHtmlDialog::OnCancel();
}

void CCommomClientConfigDlg::OnOK()
{
	//if (CanExit())
	//	CDHtmlDialog::OnOK();
}

void CCommomClientConfigDlg::OnCancel()
{
	//if (CanExit())
	//	CDHtmlDialog::OnCancel();
}

BOOL CCommomClientConfigDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

HRESULT CCommomClientConfigDlg::OnButtonOK(IHTMLElement * /*pElement*/ )
{
	//OnOK();
	return S_OK;
}

HRESULT CCommomClientConfigDlg::OnButtonCancel(IHTMLElement * /*pElement*/ )
{
	//OnCancel();
	return S_OK;
}

HRESULT CCommomClientConfigDlg::OnButtonHelp(IHTMLElement * /*pElement*/ )
{
	//OnHelp();
	return S_OK;
}

BSTR CCommomClientConfigDlg::open_file(BSTR path, BSTR model)
{

	CFileException e;
	BOOL bRet = false;
	char*  p = (char*) model;
	if (*p == 'r')
	{
		bRet = file_.Open((char*)path, CFile::modeReadWrite | CFile::shareDenyNone, &e);
	}
	else
	{
		bRet = file_.Open((char*)path, CFile::modeWrite | CFile::shareDenyNone | CFile::modeCreate, &e);
	}

	Json::Value jret;
	jret["success"]=bRet;
	if (bRet)
	{
		jret["msg"]="成功打开文件";
	}
	else
	{
		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		jret["msg"]=szError;
	}

	Json::FastWriter w;
	CString ret(w.write(jret).c_str());
	return ret.AllocSysString();
}

void CCommomClientConfigDlg::system( BSTR command )
{
	char* pc = (char*)command;
	::system(pc);
}


BSTR CCommomClientConfigDlg::read_file(BSTR pos, BSTR len, BSTR strLength)
{
	CString ret;
	CString str;
	bool isStr = false;

	if (!is_valid())
	{
		ret = "{success:false,msg:'文件无效'}";
		return ret.AllocSysString();
	}

	char*  pLen = (char*) len;
	int iLen = atoi(pLen);
	char*  pPos = (char*) pos;
	int iPos = atoi(pPos);
	char*  pstrLenth = (char*) strLength;
	int iStrLength = atoi(pstrLenth);

	if (iLen < 0)
		isStr = true;
	else
		isStr = false;

	char*  pData = NULL;

	if (isStr)
	{
		if (iLen == KXString)
		{
			//读取字符串长度
			short slen = 0;
			if (iStrLength > 0)
			{
				slen = iStrLength;
			}
			else
			{
				file_.Read((void*) &slen, sizeof(slen));
			}

			pData = new char[slen + 1];
			memset(pData, 0, slen + 1);

			//读取字符串数据
			this->file_.Read(pData, slen);
		}
		else if (iLen == KXWString)
		{
			//读取字符串长度
			short slen = 0;
			if (iStrLength > 0)
			{
				slen = iStrLength;
			}
			else
			{
				file_.Read((void*) &slen, sizeof(slen));

				//slen*= sizeof(wchar_t);
			}

			//申请空间
			wchar_t*  pWString = new wchar_t[slen + 1];
			memset(pWString, 0, (slen + 1) * sizeof(wchar_t));

			//读取字符串数据
			this->file_.Read(pWString, slen * sizeof(wchar_t));

			int ii = WideCharToMultiByte(CP_ACP, 0, pWString, -1, NULL, 0, NULL, NULL);

			//把unicode转化为ansc
			pData = new char[ii];
			memset(pData, 0, ii);

			int st = WideCharToMultiByte(CP_ACP, 0, pWString, -1, pData, ii, NULL, NULL);

			delete[] pWString;
			pWString = NULL;
		}
	}
	else
	{
		//读取数值
		//pData = new char[iLen];
		//memset(pData, 0, iLen);

		long num = 0;
		this->file_.Read((char*) &num, iLen);
		str.Format(_T("{success:true,msg:'%i'}"), num);

		delete[] pData;
		pData = NULL;

		return str.AllocSysString();
	}

	str.Format(_T("{success:true,msg:'%s'}"), pData);
	delete[] pData;
	pData = NULL;
	return str.AllocSysString();
}

BSTR CCommomClientConfigDlg::write_file(BSTR data, BSTR len, BSTR strLength)
{
	CString ret;

	Json::Value jval;

	bool isStr = false;
	char*  pstrLenth = (char*) strLength;
	int iStrLength = atoi(pstrLenth);

	do
	{

		if (!is_valid())
		{
			jval["success"]=false;
			jval["msg"]="文件无效";
			break;
		}

		char*  pLen = (char*) len;
		int iLen = atoi(pLen);
		char*  p = NULL;
		char*  pData = (char*) data;

		if (pData == NULL)
		{
			pData = new char('\0');
		}

		if (iLen < 0)
			isStr = true;
		else
			isStr = false;

		try
		{
			file_.SeekToEnd();
			if (isStr)
			{
				if (iLen == KXString)
				{
					//取得字符串长度
					char*  temp = NULL;
					if (iStrLength > 0)
					{
						iLen = iStrLength;

						temp = new char[iLen + 1];
						memset(temp, 0, iLen + 1);
						memcpy(temp, pData, strlen(pData));
						pData = temp;
					}
					else
					{
						iLen =(int) strlen(pData);

						short s = (short) iLen;
						//字符串个数
						file_.Write(&s, sizeof(s));
					}

					//字符串数据
					file_.Write(pData, iLen);
					delete[] temp;
					temp = NULL;
					pData = NULL;
				}
				else if (iLen == KXWString)
				{
					//iLen = strlen(pData);
					iLen = MultiByteToWideChar(CP_ACP, 0, pData, -1, NULL, NULL);

					wchar_t*  pwc = new wchar_t[iLen];
					memset(pwc, 0, iLen);

					//把ansc转化为unicode,并取得字符串长度
					MultiByteToWideChar(CP_ACP, 0, pData, -1, pwc, iLen);

					short c =(short) wcslen(pwc);

					//字符串个数
					file_.Write(&c, sizeof(c));

					//字符串数据
					file_.Write(pwc, c * sizeof(wchar_t));

					delete[] pwc;
					pwc = NULL;
				}
			}
			else
			{
				file_.Write(pData, strlen(pData));
			}
		}
		catch(CMemoryException & e)
		{
			TCHAR szError[1024];
			e.GetErrorMessage(szError, 1024);
			jval["success"]=false;
			jval["msg"] = szError;
			break;
		}
		catch(CFileException & e)
		{
			TCHAR szError[1024];
			e.GetErrorMessage(szError, 1024);
			jval["success"]=false;
			jval["msg"] = szError;
			break;
		}
		catch(CException & e)
		{
			TCHAR szError[1024];
			e.GetErrorMessage(szError, 1024);
			jval["success"]=false;
			jval["msg"] = szError;
			break;
		}

		jval["success"]=true;
		jval["msg"] = "";
		delete[] p;
		p = NULL;
	}while (0);

	Json::FastWriter w;
	CString str(w.write(jval).c_str()) ;
	return str.AllocSysString();
}

BSTR CCommomClientConfigDlg::tellg_file()
{
	CString ret;
	if (!is_valid())
	{
		ret = "{success:false,msg:'文件无效'}";
		return ret.AllocSysString();
	}

	int pos =(int) file_.GetPosition();
	CString str;
	str.Format(_T("%i"), pos);
	return str.AllocSysString();
}

void CCommomClientConfigDlg::seekg_file(BSTR pos)
{
	if (!is_valid())
	{
		return;
	}

	char*  p = (char*) pos;
	int i = atoi(p);
	if (i >= 0)
	{
		this->file_.Seek(i, CFile::begin);
	}
	else
	{
		this->file_.SeekToEnd();
	}
}

void CCommomClientConfigDlg::flush_file()
{
	if (is_valid())
	{
		this->file_.Flush();
	}
}

void CCommomClientConfigDlg::close_file()
{
	this->file_.Close();
}

BOOL CCommomClientConfigDlg::CanAccessExternal()
{
	return true;
}

BOOL CCommomClientConfigDlg::is_valid()
{
	if (file_.m_hFile != CFile::hFileNull)
		return true;
	else
		return false;
}

void CCommomClientConfigDlg::GotoUrl(LPCTSTR pszUrl)
{
	CString strPath, str;
	DWORD dwSize = MAX_PATH;

	::GetModuleFileName(NULL, strPath.GetBuffer(MAX_PATH), dwSize);
	strPath.ReleaseBuffer(dwSize);

	int iPos = strPath.ReverseFind('\\');
	str = strPath.Left(iPos + 1);
	ASSERT(pszUrl != NULL);

	if (pszUrl != NULL)
	{
		CString strUrl;
		strUrl = str + pszUrl;
		Navigate(_T("file:///") + strUrl);
	}
}

STDMETHODIMP CCommomClientConfigDlg::GetHostInfo(DOCHOSTUIINFO* pInfo)
{
	pInfo->dwFlags = DOCHOSTUIFLAG_THEME;
	return S_OK;
}

void CCommomClientConfigDlg::bak_file(BSTR path)
{
	//备份文件
	//CString strPath((char*)path);
	//CString bakPath = strPath+CString(".bak");
	//CString cmdLine ;
	//cmdLine.Format(TEXT("cmd.exe /c copy /y \"%s\" \"%s\""),strPath,bakPath);

	char cmdline[MAX_PATH] = {0};
	sprintf(cmdline,"cmd.exe /c copy /y \"%s\" \"%s.bak\"",(char*)path,(char*)path);

	UINT ret = ::WinExec(cmdline,0);
	Sleep(100);

}

BSTR CCommomClientConfigDlg::read_all()
{
	CString ret;

	bool isStr = false;

	Json::Value jval;
	if (!is_valid())
	{
		jval["success"]=false;
		jval["msg"]="文件无效";
	}
	else
	{
		file_.SeekToEnd();
		ULONGLONG num = file_.GetPosition();
		file_.SeekToBegin();
		char* pbuff = new char[num +1];
		memset(pbuff, 0, num * sizeof(char) + 1);
		this->file_.Read(pbuff, num);
		jval["success"]=true;
		jval["msg"]=pbuff;
		delete[] pbuff;
		pbuff = NULL;
	}
	Json::FastWriter w;

	CString str(w.write(jval).c_str());
	return str.AllocSysString();
}

BSTR CCommomClientConfigDlg::get_dir( BSTR dir )
{
	char* pDir = (char*)dir;
	Json::Value val;
	RecursiveFindFile(pDir, val);

	Json::FastWriter w;
	CString out(w.write(val).c_str());

	return out.AllocSysString();
}

void CCommomClientConfigDlg::RecursiveFindFile( const CString& dir, Json::Value& out )
{
	// strRootPath 为目录名;  
	CString strRootPath = dir;
	CFileFind finder;  
	CString FilePath;  
	CString c = strRootPath.Right(1);
	if ( c != "/" && c != "\\" )  
		strRootPath += "\\";  

	strRootPath += "*.*";  

	BOOL res = finder.FindFile(strRootPath);    // 开始遍历root文件夹下有没有文件或文件夹;  
	while ( res )       // res为1，表示仍有nextFile;  
	{  
		res = finder.FindNextFile();  
		FilePath = finder.GetFilePath();  
		
		if ( finder.IsDots() )  continue;       // 如果文件为“.”或“..”，则跳过本次循环;  
		CString strFileaname = finder.GetFileTitle();
		if (strFileaname.GetAt(0) == '_' || strFileaname.GetAt(0) == '.')
		{
			continue;
		}

		Json::Value val;
		
		val["text"] =strFileaname.GetBuffer();
		val["id"] = strFileaname.GetBuffer();
		Json::Value att;
		att["path"] = finder.GetFilePath().GetBuffer();
		val["attributes"] = att;
		if ( finder.IsDirectory() )     // 找到的是文件夹;  
		{  		
			val["state"]="closed";

			Json::Value child;
			RecursiveFindFile(FilePath, child);        // 递归;  
			val["children"] = child;
		}  

		out.append(val);
	}  
}

HRESULT CCommomClientConfigDlg::GetContextMenuForFSItem( LPCWSTR path,IContextMenu**ppCM )
{
	PIDLIST_ABSOLUTE pidlAbs;
	HRESULT hr = SHParseDisplayName(path,0,&pidlAbs,0,0);
	if (!hr)
	{
		IShellFolder *pSF;
		PCUITEMID_CHILD pidlLast;
		hr = SHBindToParent(pidlAbs,IID_IShellFolder,(void**)&pSF,&pidlLast);
		if (!hr)
		{
			hr = pSF->GetUIObjectOf(0,1,&pidlLast,IID_IContextMenu,0,(void**)ppCM);
			pSF->Release();
		}
		ILFree(pidlAbs);
	}
	return hr;
}

BSTR CCommomClientConfigDlg::exe_contentCmd( BSTR path, BSTR cmd )
{
	char* pDir = (char*)path;
	char* pCmd = (char*)cmd;
	USES_CONVERSION;

	IContextMenu*pCM;
    HRESULT hr = GetContextMenuForFSItem(A2W(pDir), &pCM);
    if (!hr) 
    {
        HMENU hMenu = CreatePopupMenu();
        hr = pCM->QueryContextMenu(hMenu,0,1,0x7fff,0);
        if (SUCCEEDED(hr))
        {
			hr = S_FALSE;
			UINT cnt = GetMenuItemCount(hMenu);
			for (int i = 0; i < cnt; ++i)
			{
				char buf[MAX_PATH] = {0};

				//查找命令
				GetMenuString(hMenu,i,buf,MAX_PATH, MF_BYPOSITION);
				if (strnicmp(buf, pCmd, strlen(pCmd)) != 0)
				{
					continue;
				}

				//找到菜单项目id
				MENUITEMINFO mi ={0};
				mi.cbSize = sizeof(mi);
				mi.fMask = MIIM_ID;
				GetMenuItemInfo(hMenu, i, true, &mi );

				CMINVOKECOMMANDINFOEX info = { 0 };
				info.cbSize = sizeof(info);
				info.fMask = CMIC_MASK_UNICODE;
				info.lpVerb  = MAKEINTRESOURCEA(mi.wID - 1);
				info.lpVerbW = MAKEINTRESOURCEW(mi.wID - 1);
				info.nShow = SW_SHOWNORMAL;
				//直接执行
				pCM->InvokeCommand((LPCMINVOKECOMMANDINFO)&info);
				hr = S_OK;

				break;
            }
        }

        pCM->Release();
        DestroyMenu(hMenu);
    }

	Json::Value jval;
	jval["success"] = hr == S_OK;
	Json::FastWriter w;
	CString out(w.write(jval).c_str());

	return out.AllocSysString();
}

LRESULT CCommomClientConfigDlg::exe_JS(const char* pScript,VARIANT& ret,DISPPARAMS& param)
{
	IHTMLDocument2*   pDocument;  
	IHTMLWindow2*   pWindow; 

	HRESULT   hr   =   GetDHtmlDocument(&pDocument);  	
	if (!SUCCEEDED(hr))
		return S_FALSE;

	hr   =   pDocument->get_parentWindow(&pWindow);
	if (!SUCCEEDED(hr))
		return S_FALSE;
/*
	return pWindow->execScript(_com_util::ConvertStringToBSTR(pScript), _com_util::ConvertStringToBSTR("JScript"), &ret);	*/
	return CallJSFunction(pDocument, pScript, &param, &ret, NULL, NULL);

}

HRESULT CCommomClientConfigDlg::CallJSFunction(IHTMLDocument2* pDoc2,
					  const CString& strFunctionName,
					 DISPPARAMS *pDispParams,
					   VARIANT* varResult,
					   EXCEPINFO* exceptInfo,
					   UINT* nArgErr )
{
	IDispatch *pDispScript = NULL;   
	HRESULT hResult;
	hResult = pDoc2->get_Script(&pDispScript);
	if(FAILED(hResult))
	{
		return S_FALSE;
	}
	DISPID   dispid;   
	CComBSTR objbstrValue = strFunctionName;
	BSTR bstrValue =  objbstrValue.Copy();
	OLECHAR   *pszFunct   =  bstrValue ; 
	hResult   =   pDispScript->GetIDsOfNames(IID_NULL, 
		&pszFunct, 
		1,
		LOCALE_SYSTEM_DEFAULT, 
		&dispid);   
	if   (S_OK   !=   hResult)   
	{ 
		pDispScript->Release();   
		return   hResult;   
	}  

	varResult->vt = VT_VARIANT;
	hResult   =   pDispScript->Invoke(dispid,
		IID_NULL, 
		LOCALE_USER_DEFAULT,
		DISPATCH_METHOD,
		pDispParams,
		varResult,
		exceptInfo,
		nArgErr);  
	pDispScript->Release();
	return hResult;
}