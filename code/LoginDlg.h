#pragma once

#include "DatabaseADO.h"
#include "afxwin.h"
#include "DurianButton.h"
// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)
private:
	bool setInfo();
	//CString makeInfostr();

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();
	
	int Get_userID()			{ return m_id; }
	CString Get_username()		{ return m_username; }
	CString Get_password()		{ return m_password; }
	CString Get_email()			{ return m_email; }
	CString Get_name()			{ return m_name; }
	CString Get_qq()			{ return m_qq; }
	CString Get_gender()		{ return m_gender; }
	CString Get_birthdate()		{ return m_birthdate; }
	CString Get_selfintro()		{ return m_selfintro; }
	CString Get_registerdate()	{ return m_registerdate; }
	bool isAdmin()				{ return isadmin;}
	bool isBlocked()			{ return isblocked; }
	//bool	Get_isSucceed()		{ return m_bSucceed; }

// 对话框数据
	enum { IDD = IDD_LOGIN };

private:
	int			m_id;
	CString		m_username,
				m_password,
				m_email,
				m_name,
				m_qq,
				m_gender,
				m_birthdate,
				m_selfintro,
				m_registerdate;
	bool		isadmin,
				isblocked;
	
	//CDatabaseADO m_db;
	//_RecordsetPtr m_pRecordSet;
	//bool m_bDBOpen;
	
	CStatic m_stTitle;
	CDurianButton m_btOK;
	CDurianButton m_btCancel;

	COLORREF m_clrBorder;
	CFont m_fontTitle;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnPaint();
private:
	
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
