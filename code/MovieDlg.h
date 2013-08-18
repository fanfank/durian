#pragma once
#include "ScrollDialog.h"
#include "afxwin.h"
#include "DatabaseADO.h"
#include "DurianButton.h"
#include <vector>
using std::vector;

// CMovieDlg �Ի���

class CMovieDlg : public CDialog
{
	DECLARE_DYNAMIC(CMovieDlg)

public:
	CMovieDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMovieDlg();

	void Refresh();

// �Ի�������
	enum { IDD = IDD_MOVIE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CScrollBar m_verScroll;
	
	int m_iLastDownloadPage;
	int m_iLastPos;
	int m_iPageIndex;
	int m_iItemNum;
	vector<vector<_variant_t> > m_strPath;//��Ŀ�����Զ�������
	
	//for testing
	CString m_tmpStrPath[6][6]; //���Դ洢·����ǰ����±����Ա�ʾ��Ӧ���飬������±�����Ϊ{Ԥ��ͼƬ·������Ŀ��ͼƬ·��1����Ŀ��ͼƬ·��2....}
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
