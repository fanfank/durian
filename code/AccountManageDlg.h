#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "DurianButton.h"
#include "MasterStatic.h"
#include "DatabaseADO.h"
#include "MessageDlg.h"


// CAccountManageDlg 对话框

class CAccountManageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAccountManageDlg)

public:
	CAccountManageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAccountManageDlg();

// 对话框数据
	enum { IDD = IDD_ACCOUNT_MANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void LoadList(const vector<vector<_variant_t> > vAccount);
	void SetBtmPrompt(const CString prompt, const COLORREF borderCol = DURIAN_COLOR_ORANGE);

private:
	//CDatabaseADO m_db;
	CListCtrl m_lstAccountList;
	COLORREF m_clrBorder;
	
	CDurianButton m_btBlock;
	CDurianButton m_btUnBlock;
	CDurianButton m_btDelete;
	CDurianButton m_btCancel;
	CDurianButton m_btLookAll;
	CDurianButton m_btSearch;
	CDurianButton m_btSelectAll;
	CDurianButton m_btSelectNone;
	CString m_username;
	CString m_registerfrom;
	CString m_registerto;
	BOOL m_blocked;
	BOOL m_unblocked;
	CMasterStatic m_stNum;
	CMasterStatic m_stDBTips;
	CMasterStatic m_stBtmPrompt;
	CMasterStatic m_stTitle;

	CFont m_fontTitle;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAccountManageLookall();
	afx_msg void OnBnClickedAccountManageDelete();
	afx_msg void OnNMDblclkAccountManageList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAccountManageSearch();


	afx_msg void OnPaint();
//	virtual HRESULT accHitTest(long xLeft, long yTop, VARIANT *pvarChild);
	afx_msg LRESULT OnNcHitTest(CPoint point);
private:
	
public:
	afx_msg void OnBnClickedAccountManageBlock();
	afx_msg void OnBnClickedAccountManageUnblock();
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	
public:
	afx_msg void OnBnClickedAccountManageSelectall();
	afx_msg void OnBnClickedAccountManageSelectnone();
};
