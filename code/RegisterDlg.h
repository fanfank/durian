#pragma once
#include "afxwin.h"
#include "MasterStatic.h"
#include "DurianButton.h"
#include "resource.h"

// CRegisterDlg �Ի���

class CRegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterDlg)

public:
	CRegisterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegisterDlg();

// �Ի�������
	enum { IDD = IDD_REGISTER };

//˽�б���
private:
	CString m_username;
	CString m_password;
	CString m_password2;
	CString password;
	CString m_email;
	CString m_name;
	CString m_qq;
	CString m_selfintro;
	int m_gender;
	CString m_year;
	CString m_month;
	CFont m_font;
	COLORREF m_clrBorder;

public:
	bool isEditInfo;
	int m_iUserID;
//˽�к���
private:
	bool	UsernameValidation();
	bool	CheckUsernameExist();
	bool	PasswordValidation();
	bool	PasswordMatch();
	bool	EmailValidation();
	bool	NameValidation();
	bool	BirthdateValidation();
	bool	CheckForm();
	void	SetTips(CString tips, bool showtips = true);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	
private:
	CMasterStatic m_stPrompt;
	CMasterStatic m_stTitle;
	CDurianButton m_btOK;
	CDurianButton m_btCancel;
	virtual void OnOK();
	
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnPaint();
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedChangePassword();
private:
	CDurianButton m_btChangePass;
};
