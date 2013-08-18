#pragma once
#include "resource.h"


// CAddressDlg 对话框

class CAddressDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddressDlg)

public:
	CAddressDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddressDlg();

// 对话框数据
	enum { IDD = IDD_SEL_ADDRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strFtp;
	CString m_strDB;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAddressOffline();
	afx_msg void OnStnClickedAuthorInfo();
};
