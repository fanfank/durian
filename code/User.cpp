#include "stdafx.h"
#include "User.h"


CUser::CUser(void)
{
	m_iUserType = USER_CUSTOMER;
	m_iUserID = -1;
}


CUser::~CUser(void)
{
}


bool CUser::InitUser(CLoginDlg* loginDlg)
{
	m_iUserID = loginDlg->Get_userID();
	m_sUserName = loginDlg->Get_username();
	m_sUserPasswd = loginDlg->Get_password();
	
	m_iUserType = (loginDlg->isAdmin())?USER_ADMIN:USER_NORMAL;
	m_personalInfo.m_sName = loginDlg->Get_name();
	m_personalInfo.m_sSelfIntroduction = loginDlg->Get_selfintro();
	m_personalInfo.m_sQQNum = loginDlg->Get_qq();
	m_personalInfo.m_sEmail = loginDlg->Get_email();
	m_personalInfo.m_bIsMale = (loginDlg->Get_gender())[0]=='m'?1:0;
	m_personalInfo.m_strBirthDate = loginDlg->Get_birthdate();
	m_personalInfo.m_strRegDate = loginDlg->Get_registerdate();

	return true;
}
