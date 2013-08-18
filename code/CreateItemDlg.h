#pragma once
#include "afxwin.h"
#include "DurianButton.h"

// CCreateItemDlg 对话框

class CCreateItemDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateItemDlg)

public:
	CCreateItemDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCreateItemDlg();
	CImage m_imgCoverPic;
	CString m_strCoverPath;
	CString m_strType;
	CString m_strName;

// 对话框数据
	enum { IDD = IDD_CREATE_ITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HBITMAP GetHBITMAP();
	afx_msg void OnBnClickedCreateitemCoverSelect();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCreateitemTypeMovie();
	afx_msg void OnBnClickedCreateitemTypeBook();
	afx_msg void OnBnClickedCreateitemTypeAffair();
	CString m_strAbstract;
	CString m_strContent;
private:
	CDurianButton m_btCoverSelect;
	CDurianButton m_btOK;
	CDurianButton m_btCancel;
	CDurianButton m_btClose;
	CStatic m_stPrompt;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
public:
	afx_msg void OnBnClickedCreateitemClose();
};