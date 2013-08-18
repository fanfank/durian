#pragma once
#include "resource.h"
#include "afxwin.h"
#include "DurianButton.h"

// CAddFriend 对话框

class CAddFriend : public CDialogEx
{
	DECLARE_DYNAMIC(CAddFriend)

public:
	CAddFriend(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddFriend();

// 对话框数据
	enum { IDD = IDD_ADD_FRIEND };
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSearchById();
	afx_msg void OnBnClickedSearchByName();
	afx_msg void OnBnClickedOk();
	CString text;
	int is_ID;
private:
	CDurianButton m_btSearch;
	CDurianButton m_btCancel;
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
