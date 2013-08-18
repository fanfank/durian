
// Durian.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "DatabaseADO.h"
#include "User.h"
//#include "FileManage.h"
// CDurianApp:
// 有关此类的实现，请参阅 Durian.cpp
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

// 重写
public:
	virtual BOOL InitInstance();
	//BOOL FolderExist(CString strPath);
// 实现

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CDurianApp theApp;