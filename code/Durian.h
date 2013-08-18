
// Durian.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "DatabaseADO.h"
#include "User.h"
//#include "FileManage.h"
// CDurianApp:
// �йش����ʵ�֣������ Durian.cpp
//

class CDurianApp : public CWinApp
{
public:
	CDurianApp();

	static CDatabaseADO m_db;
	static _RecordsetPtr m_pRecordSet;
	static CString m_strWorkingDir;
	
	bool m_bDBOpen;
	static BOOL m_bIsFtpConnected;
	static CString m_strFtp;
	static CString m_strDB;

	static CUser m_user;
	static CString m_ftpRootDir;
	//static CString m_strDBSrc;

// ��д
public:
	virtual BOOL InitInstance();
	//BOOL FolderExist(CString strPath);
// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CDurianApp theApp;