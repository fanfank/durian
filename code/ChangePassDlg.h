#pragma once
#include "resource.h"
#include "afxwin.h"
#include "DurianButton.h"
// CChangePassDlg �Ի���

class CChangePassDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangePassDlg)

public:
	CChangePassDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangePassDlg();

// �Ի�������
	enum { IDD = IDD_CHANGE_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString old_password;
	CString new_password1;
	CString new_password2;
	CString password;
	afx_msg void OnBnClickedOk();

public:
	bool PasswordValidation();
	bool PasswordMatch();
	bool OldPasswordMatch();
	bool CheckPasswordForm();

private:
	CDurianButton m_btOK;
	CDurianButton m_btCancel;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
