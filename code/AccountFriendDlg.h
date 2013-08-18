#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "DurianButton.h"
#include "MasterStatic.h"
#include "DatabaseADO.h"
#include "MessageDlg.h"


// CAccountFriendDlg 对话框

class CAccountFriendDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAccountFriendDlg)

public:
	CAccountFriendDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAccountFriendDlg();

// 对话框数据
	enum { IDD = IDD_ACCOUNT_FRIEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void LoadList(const vector<vector<_variant_t> > vAccount);
	void SetBtmPrompt(const CString prompt, const COLORREF borderCol = DURIAN_COLOR_ORANGE);

public:
	//CDatabaseADO m_db;
	CListCtrl m_lstAccountList;
	COLORREF m_clrBorder;
	
	CDurianButton m_btBlock;
	CDurianButton m_btUnBlock;
	CDurianButton m_btDelete;
	CDurianButton m_btCancel;
	CDurianButton m_btLookAll;
	CDurianButton m_btSearch;
	//CString m_username;
	// m_registerfrom;
	//CString m_registerto;
	//BOOL m_blocked;
	//BOOL m_unblocked;
	CMasterStatic m_stNum;
	CMasterStatic m_stDBTips;
	CMasterStatic m_stBtmPrompt;
	CMasterStatic m_stTitle;
	CFont m_fontTitle;

public:
	int m_iUserID;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNMDblclkAccountFriendList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAccountFriendLookall();
	afx_msg void OnBnClickedAccountFriendSearch();
	afx_msg void OnBnClickedAccountFriendDelete();
	afx_msg void OnBnClickedAccountFriendBlock();
	afx_msg void OnBnClickedAccountFriendUnblock();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
