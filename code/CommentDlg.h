#pragma once
#include "DurianButton.h"
#include "DatabaseADO.h"
#include "afxwin.h"

#define NUM_PER_PAGE 5
// CCommentDlg 对话框

class CCommentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommentDlg)

public:
	//CCommentDlg(CWnd* pParent = NULL);   // 标准构造函数
	CCommentDlg(CString strType, CString strName, CWnd* pParent = NULL);   // 标准构造函数

	virtual ~CCommentDlg();

private:
	CString m_strType;
	CString m_strName;

// 对话框数据
	enum { IDD = IDD_COMMENT };
public:
	void ShowReview(int index, bool show = true);
	void Delete(int index);
	void Reply(int index);
	void Load();
	void ShowPage(int PageNum);
	void HideAll();

public:
	int m_nUserID;
	int m_nItemID;
	bool m_bAdmin;
	char m_cType;
	//CString m_strName;

public:
	int m_nCount;
	int m_nCurPage;
	int m_nTotalPage;
	COLORREF m_clrBorder;
	CFont m_fontTitle;

	//CDatabaseADO m_db;
	//_RecordsetPtr m_pRecordSet;
	CEdit *m_pReviews[5];
	CStatic *m_pTime[5];
	CStatic *m_pAuthor[5];
	CDurianButton *m_pReply[5];
	CDurianButton *m_pDelete[5];
	long long m_nID[5];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CDurianButton m_btReply1;
	CDurianButton m_btReply2;
	CDurianButton m_btReply3;
	CDurianButton m_btReply4;
	CDurianButton m_btReply5;
	CDurianButton m_btDelete1;
	CDurianButton m_btDelete2;
	CDurianButton m_btDelete3;
	CDurianButton m_btDelete4;
	CDurianButton m_btDelete5;

	CDurianButton m_btSubmit;
	CDurianButton m_btFirst;
	CDurianButton m_btPrevious;
	CDurianButton m_btNext;
	CDurianButton m_btLast;
	CDurianButton m_btCancel;
	CDurianButton m_btCancelReply;
	CDurianButton m_btGoto;

	CEdit m_edGotoPage;
	CStatic m_stCurPage;
	CStatic m_stPrompt;
	CStatic m_stNoMoreTips;
	CStatic m_stTitle;
	CStatic m_stNum;
	CStatic m_stGoto;
public:
	afx_msg void OnBnClickedCommentBtPrevious();
private:
	
	
public:
	afx_msg void OnBnClickedCommentBtNext();
	afx_msg void OnBnClickedCommentBtFirst();
	afx_msg void OnBnClickedCommentBtLast();
private:
	
public:
	afx_msg void OnBnClickedCommentBtReply1();
	afx_msg void OnBnClickedCommentBtReply2();
	afx_msg void OnBnClickedCommentBtReply3();
	afx_msg void OnBnClickedCommentBtReply4();
	afx_msg void OnBnClickedCommentBtReply5();
	afx_msg void OnBnClickedCommentSubmit();
private:
	
public:
	afx_msg void OnBnClickedCommentBtCancelReply();
	afx_msg void OnBnClickedCommentBtDelete1();
	afx_msg void OnBnClickedCommentBtDelete2();
	afx_msg void OnBnClickedCommentBtDelete3();
	afx_msg void OnBnClickedCommentBtDelete4();
	afx_msg void OnBnClickedCommentBtDelete5();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

public:
	afx_msg LRESULT OnNcHitTest(CPoint point);	
	
public:
	afx_msg void OnBnClickedCommentBtGoto();
	virtual void OnOK();
};
