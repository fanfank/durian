#pragma once
#include "afxwin.h"
#include "DurianButton.h"


// CMainDlg 对话框

class CMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDlg();

// 对话框数据
	enum { IDD = IDD_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vector<vector<_variant_t> > m_strPath;
	CImage m_imgPreview[3];
	CString m_strItemType[3];
	int m_iItemNum;

	void Download(int startIndex, int downloadNum, LPCTSTR fileName); //Download(m_iPageIndex*6, 6, L"preview.jpg");
	bool SynchronizeDB();

	CDurianButton m_btnMainGpMovieEnt;
	CDurianButton m_btnMainGpBookEnt;
	CDurianButton m_btnMainGpAffairEnt;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedMainGroupMovieEnter();
	afx_msg void OnBnClickedMainGroupBookEnter();
	afx_msg void OnBnClickedMainGroupAffairEnter();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
