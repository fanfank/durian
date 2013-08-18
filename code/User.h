#pragma once
#include "LoginDlg.h"
#define USER_ADMIN 0
#define USER_NORMAL 1
#define USER_CUSTOMER 2

class CUser
{
public:
	CUser(void);
	~CUser(void);
	int m_iUserID;
	CString m_sUserName;
	CString m_sUserPasswd;

	int m_iUserType;
	bool m_bIsBlocked;

	struct PersonalInfo
	{
		CString m_sName;
		CString m_sSelfIntroduction;
		CString m_sQQNum;
		CString m_sEmail;
		bool m_bIsMale;
		CString m_strBirthDate;
		CString m_strRegDate;
	}m_personalInfo;

	bool InitUser(CLoginDlg* loginDlg);

	int GetUserId() {return m_iUserID;}

private:
};

