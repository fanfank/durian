
// Durian.cpp : ����Ӧ�ó��������Ϊ��
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


// CDurianApp ����

CDurianApp::CDurianApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬

	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CDurianApp ����

CDurianApp theApp;

//����ļ����Ƿ����
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
// CDurianApp ��ʼ��

BOOL CDurianApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	//************************************************************
	//�˶������ʼ��������ϵͳ����Ҫ����ԭʼ����
	//�����ݿ�
	
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
	
	//��ȡ��ǰ����Ŀ¼
	wchar_t currentDir[500];// = new wchar_t[500];
	HMODULE hl = GetModuleHandle(NULL);
	GetModuleFileName(hl, currentDir, 500);

	CString m_strWorkingDir = CString(currentDir);
	for(int j = m_strWorkingDir.GetLength() - 1; m_strWorkingDir[j]!='\\';--j)
			m_strWorkingDir.Delete(j);
		
	//������ʱ�����ļ���
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

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CDurianDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int CDurianApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(m_pRecordSet != NULL)
	{
		m_pRecordSet->Close();
		m_pRecordSet = NULL;
	}
	if(m_bDBOpen)
		m_db.Close();

	return CWinApp::ExitInstance();
}
