#pragma once
#include "afxwin.h"
#include "DurianButton.h"


// CBookDlg 对话框

class CBookDlg : public CDialog
{
	DECLARE_DYNAMIC(CBookDlg)

public:
	CBookDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBookDlg();

// 对话框数据
	enum { IDD = IDD_BOOK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CScrollBar m_verScroll;

	int m_iLastDownloadPage;
	int m_iLastPos;
	int m_iPageIndex;
	int m_iItemNum;
	vector<vector<_variant_t> > m_strPath;//用以存储路径，前面的下标用以表示对应的组，后面的下标依次为{预览图片路径，条目内图片路径1，条目内图片路径2....}
	
	CString m_tmpStrPath[6][6]; //用以存储路径，前面的下标用以表示对应的组，后面的下标依次为{预览图片路径，条目内图片路径1，条目内图片路径2....}
	CImage m_imgPreview[6];

	void Download(int startIndex, int downloadNum, LPCTSTR fileName);
	bool SynchronizeDB();

	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBookNextpage();
	afx_msg void OnBnClickedBookPreviouspage();
	CDurianButton m_btnBookGp1Ent;
	CDurianButton m_btnBookGp2Ent;
	CDurianButton m_btnBookGp3Ent;
	CDurianButton m_btnBookGp4Ent;
	CDurianButton m_btnBookGp5Ent;
	CDurianButton m_btnBookGp6Ent;
	CDurianButton m_btnBookPrePg;
	CDurianButton m_btnBookNxtPg;
	afx_msg void OnBnClickedBookGroup1Enter();
	afx_msg void OnBnClickedBookGroup2Enter();
	afx_msg void OnBnClickedBookGroup3Enter();
	afx_msg void OnBnClickedBookGroup4Enter();
	afx_msg void OnBnClickedBookGroup5Enter();
	afx_msg void OnBnClickedBookGroup6Enter();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
