#pragma once
#include "ScrollDialog.h"
#include "afxwin.h"
#include "DatabaseADO.h"
#include "DurianButton.h"
#include <vector>
using std::vector;

// CMovieDlg 对话框

class CMovieDlg : public CDialog
{
	DECLARE_DYNAMIC(CMovieDlg)

public:
	CMovieDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMovieDlg();

	void Refresh();

// 对话框数据
	enum { IDD = IDD_MOVIE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CScrollBar m_verScroll;
	
	int m_iLastDownloadPage;
	int m_iLastPos;
	int m_iPageIndex;
	int m_iItemNum;
	vector<vector<_variant_t> > m_strPath;//条目的属性都在里面
	
	//for testing
	CString m_tmpStrPath[6][6]; //用以存储路径，前面的下标用以表示对应的组，后面的下标依次为{预览图片路径，条目内图片路径1，条目内图片路径2....}
	CImage m_imgPreview[6];

	void Download(int startIndex, int downloadNum, LPCTSTR fileName); //Download(m_iPageIndex*6, 6, L"preview.jpg");
	bool SynchronizeDB();

	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedMovieNextpage();
	afx_msg void OnBnClickedMoviePreviouspage();
	afx_msg void OnBnClickedMovieGroup1Enter();
	afx_msg void OnBnClickedMovieGroup2Enter();
	afx_msg void OnBnClickedMovieGroup3Enter();
	afx_msg void OnBnClickedMovieGroup4Enter();
	afx_msg void OnBnClickedMovieGroup5Enter();
	afx_msg void OnBnClickedMovieGroup6Enter();
	CDurianButton m_btnMovieGp1Ent;
	CDurianButton m_btnMovieGp2Ent;
	CDurianButton m_btnMovieGp3Ent;
	CDurianButton m_btnMovieGp4Ent;
	CDurianButton m_btnMovieGp5Ent;
	CDurianButton m_btnMovieGp6Ent;
	CDurianButton m_btnMoviePrePg;
	CDurianButton m_btnMovieNxtPg;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
