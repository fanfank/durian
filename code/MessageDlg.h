#pragma once
#include "afxwin.h"
#include "DurianButton.h"
#include "resource.h"


// CMessageDlg 对话框

class CMessageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMessageDlg)

public:
	CMessageDlg(CWnd* pParent = NULL);   // 标准构造函数
	CMessageDlg(CString strCon, CString strCap = L"", COLORREF clrBorder = DURIAN_COLOR_RED, CWnd *pParent = NULL);
	virtual ~CMessageDlg();

// 对话框数据
	enum { IDD = IDD_MESSAGEBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_strCap;
	CString m_strCon;
	COLORREF m_clrBorder;
	CDurianButton m_btOK;
	CDurianButton m_btCancel;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
