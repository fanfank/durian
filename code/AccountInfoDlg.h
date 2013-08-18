#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "DurianButton.h"
#include "MasterStatic.h"
#include "DatabaseADO.h"
#include "MessageDlg.h"
#include "resource.h"


// CAccountInfoDlg 对话框

class CAccountInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAccountInfoDlg)

public:
	CAccountInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAccountInfoDlg();

// 对话框数据
	enum { IDD = IDD_ACCOUNT_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int id;
	int m_iUserID;
public:
	CFont m_fontTitle;

	CStatic m_stUID;
	CStatic m_stUsername;
	CDurianButton m_btOK;
	CStatic m_stTitle;
	CStatic m_stAdmin;
	
public:

	CString m_edUID;
	CString m_edUsername;
	CString m_edEmail;
	CString m_edName;
	CString m_edQQ;
	CString m_edGender;
	CString m_edBirthdate;
	CString m_edSelfintro;
	CString m_edRegisterdate;
	CString m_edBlock;
	bool	m_bAdmin;
	bool	m_addFriend;
	bool	m_addNow;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
private:
	
public:
	virtual BOOL OnInitDialog();

public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancle();
	afx_msg void OnBnClickedCancleThis();
	afx_msg void OnBnClickedThis();
private:
	CDurianButton m_btClose;
};
