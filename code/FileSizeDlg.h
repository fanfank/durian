#pragma once
#include "afxwin.h"
#include "DurianButton.h"

// CFileSizeDlg 对话框

class CFileSizeDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileSizeDlg)

public:
	CFileSizeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileSizeDlg();

// 对话框数据
	enum { IDD = IDD_FILESIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CDurianButton m_btOK;
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
