
// Durian.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Durian.h"
#include "DurianDlg.h"
#include "FileManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDatabaseADO CDurianApp::m_db;
_RecordsetPtr CDurianApp::m_pRecordSet;
CString CDurianApp::m_strWorkingDir;
CString CDurianApp::m_strFtp;
CString CDurianApp::m_strDB;
CString CDurianApp::m_ftpRootDir = L"10ClassB/ziliao/item/";
CUser	CDurianApp::m_user;
BOOL    CDurianApp::m_bIsFtpConnected;

// CDurianApp

BEGIN_MESSAGE_MAP(CDurianApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDurianApp 构造

CDurianApp::CDurianApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，

	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CDurianApp 对象

CDurianApp theApp;

//检测文件夹是否存在
BOOL FolderExist(CString strPath)
{
     WIN32_FIND_DATA   wfd;
     BOOL rValue = FALSE;
     HANDLE hFind = FindFirstFile(strPath, &wfd);
    if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY))
    {
              rValue = TRUE;   
     }
     FindClose(hFind);
    return rValue;
}
// CDurianApp 初始化

BOOL CDurianApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	//************************************************************
	//此段下面初始化本榴莲系统所需要的最原始内容
	//打开数据库
	
	//"DSN=durian;server=localhost;database=durian"
	CAddressDlg addrDlg;
	m_bIsFtpConnected = FALSE;

	int _ID = addrDlg.DoModal();
	if(_ID == IDOK)
	{
		CString strDBSrc = L"DSN=durian_db;server=";
		strDBSrc = strDBSrc + addrDlg.m_strDB + L";database=durian_db";
		//AfxMessageBox(strDBSrc);

		//test
		CFileManage::ftpUser=L"abc";
		CFileManage::ftpPasswd=L"abc12345";
		//test

		if(m_db.m_bIsOpen = m_db.Open(strDBSrc, L"durian_db", L"abc123"))
		{
			//m_strFtp = addrDlg.m_strFtp;
			m_strDB = addrDlg.m_strDB;
		}
		if(m_bIsFtpConnected = CFileManage::TryFtp(addrDlg.m_strFtp))
		{
			m_strFtp = addrDlg.m_strFtp;
		}
	}
	else if(_ID == IDCANCEL)
	{
		CString strDBSrc = L"DSN=durian_db;server=";
		strDBSrc = strDBSrc + addrDlg.m_strDB + L";database=durian_db";
		//AfxMessageBox(strDBSrc);

		if(m_db.m_bIsOpen = m_db.Open(strDBSrc, L"root", L"123456"))
		{
			//m_strFtp = addrDlg.m_strFtp;
			m_strDB = addrDlg.m_strDB;
		}

		CFileManage::ftpUser = L"durian";
		CFileManage::ftpPasswd = L"123456";
		if(m_bIsFtpConnected = CFileManage::TryFtp(addrDlg.m_strFtp))
		{
			m_strFtp = addrDlg.m_strFtp;
		}
	}
	m_pRecordSet = NULL;
	
	//获取当前工作目录
	wchar_t currentDir[500];// = new wchar_t[500];
	HMODULE hl = GetModuleHandle(NULL);
	GetModuleFileName(hl, currentDir, 500);

	CString m_strWorkingDir = CString(currentDir);
	for(int j = m_strWorkingDir.GetLength() - 1; m_strWorkingDir[j]!='\\';--j)
			m_strWorkingDir.Delete(j);
		
	//创建临时缓存文件夹
	if(!FolderExist(m_strWorkingDir+L"tmp"))
		CreateDirectory(m_strWorkingDir+L"tmp", NULL);
	if(!FolderExist(m_strWorkingDir+L"tmp\\item"))
		CreateDirectory(m_strWorkingDir+L"tmp\\item", NULL);
	if(!FolderExist(m_strWorkingDir+L"tmp\\item\\movie"))
		CreateDirectory(m_strWorkingDir+L"tmp\\item\\movie", NULL);
	if(!FolderExist(m_strWorkingDir+L"tmp\\item\\book"))
		CreateDirectory(m_strWorkingDir+L"tmp\\item\\book", NULL);
	if(!FolderExist(m_strWorkingDir+L"tmp\\item\\affair"))
		CreateDirectory(m_strWorkingDir+L"tmp\\item\\affair", NULL);



	//************************************************************
	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CDurianDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



int CDurianApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(m_pRecordSet != NULL)
	{
		m_pRecordSet->Close();
		m_pRecordSet = NULL;
	}
	if(m_bDBOpen)
		m_db.Close();

	return CWinApp::ExitInstance();
}
