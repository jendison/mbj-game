// CommomClientConfig.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CommomClientConfig.h"
#include "CommomClientConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCommomClientConfigApp

BEGIN_MESSAGE_MAP(CCommomClientConfigApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()



/* Convert a Subversion error into a simple boolean error code.
 *
 * NOTE:  Subversion errors must be cleared (using svn_error_clear())
 *        because they are allocated from the global pool, else memory
 *        leaking occurs.
 */
#define INT_ERR(expr, ret)                           \
  do {                                          \
    svn_error_t *__temperr = (expr);            \
    if (__temperr)                              \
      {                                         \
        svn_error_clear(__temperr);             \
        return ret;                               \
      }                                         \
  } while (0)


// CCommomClientConfigApp construction

CCommomClientConfigApp::CCommomClientConfigApp()
{
	EnableHtmlHelp();

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCommomClientConfigApp object

CCommomClientConfigApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x194E5838, 0xC748, 0x45CB, { 0x9B, 0xDA, 0x62, 0x12, 0x31, 0x18, 0xF1, 0x71 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CCommomClientConfigApp initialization

BOOL CCommomClientConfigApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	EnableAutomation();
	CoUninitialize();
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	// Parse command line for automation or reg/unreg switches.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// App was launched with /Embedding or /Automation switch.
	// Run app as automation server.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Register class factories via CoRegisterClassObject().
		COleTemplateServer::RegisterAll();
	}
	// App was launched with /Unregserver or /Unregister switch.  Remove
	// entries from the registry.
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		COleObjectFactory::UpdateRegistryAll(FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
		return FALSE;
	}
	// App was launched standalone or with other switches (e.g. /Register
	// or /Regserver).  Update registry entries, including typelibrary.
	else
	{
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
		if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
			return FALSE;
	}

	CCommomClientConfigDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
//
//
///* Create a new directory at the path NEW_DIRECTORY in the Subversion
// * repository located at REPOS_PATH.  Perform all memory allocation in
// * POOL.  This function will create a new revision for the addition of
// * NEW_DIRECTORY.  Return zero if the operation completes
// * successfully, non-zero otherwise.
// */
//static int
//make_new_directory(const char *repos_path,
//                   const char *new_directory,
//                   apr_pool_t *pool)
//{
//  svn_error_t *err;
//  svn_repos_t *repos;
//  svn_fs_t *fs;
//  svn_revnum_t youngest_rev;
//  svn_fs_txn_t *txn;
//  svn_fs_root_t *txn_root;
//  const char *conflict_str;
//
//  /* Open the repository located at REPOS_PATH. 
//   */
//  INT_ERR(svn_repos_open(&repos, repos_path, pool));
//
//  /* Get a pointer to the filesystem object that is stored in REPOS. 
//   */
//  fs = svn_repos_fs(repos);
//
//  /* Ask the filesystem to tell us the youngest revision that
//   * currently exists. 
//   */
//  INT_ERR(svn_fs_youngest_rev(&youngest_rev, fs, pool));
//
//  /* Begin a new transaction that is based on YOUNGEST_REV.  We are
//   * less likely to have our later commit rejected as conflicting if we
//   * always try to make our changes against a copy of the latest snapshot
//   * of the filesystem tree. 
//   */
//  INT_ERR(svn_fs_begin_txn(&txn, fs, youngest_rev, pool));
//
//  /* Now that we have started a new Subversion transaction, get a root
//   * object that represents that transaction. 
//   */
//  INT_ERR(svn_fs_txn_root(&txn_root, txn, pool));
//  
//  /* Create our new directory under the transaction root, at the path
//   * NEW_DIRECTORY. 
//   */
//  INT_ERR(svn_fs_make_dir(txn_root, new_directory, pool));
//
//  /* Commit the transaction, creating a new revision of the filesystem
//   * which includes our added directory path.
//   */
//  err = svn_repos_fs_commit_txn(&conflict_str, repos, 
//                                &youngest_rev, txn, pool);
//  if (! err)
//    {
//      /* No error?  Excellent!  Print a brief report of our success.
//       */
//      printf("Directory '%s' was successfully added as new revision "
//             "'%ld'.\n", new_directory, youngest_rev);
//    }
//  else if (err->apr_err == SVN_ERR_FS_CONFLICT)
//    {
//      /* Uh-oh.  Our commit failed as the result of a conflict
//       * (someone else seems to have made changes to the same area 
//       * of the filesystem that we tried to modify).  Print an error
//       * message.
//       */
//      printf("A conflict occurred at path '%s' while attempting "
//             "to add directory '%s' to the repository at '%s'.\n", 
//             conflict_str, new_directory, repos_path);
//    }
//  else
//    {
//      /* Some other error has occurred.  Print an error message.
//       */
//      printf("An error occurred while attempting to add directory '%s' "
//             "to the repository at '%s'.\n", 
//             new_directory, repos_path);
//    }
//
//  INT_ERR(err);
//}