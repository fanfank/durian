#pragma once
#include "resource.h"


// CAddressDlg �Ի���

class CAddressDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddressDlg)

public:
	CAddressDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddressDlg();

// �Ի�������
	enum { IDD = IDD_SEL_ADDRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strFtp;
	CString m_strDB;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAddressOffline();
	afx_msg void OnStnClickedAuthorInfo();
};
