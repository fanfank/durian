#pragma once
#include "afxwin.h"
#include "DurianButton.h"


// CBookDlg �Ի���

class CBookDlg : public CDialog
{
	DECLARE_DYNAMIC(CBookDlg)

public:
	CBookDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBookDlg();

// �Ի�������
	enum { IDD = IDD_BOOK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CScrollBar m_verScroll;

	int m_iLastDownloadPage;
	int m_iLastPos;
	int m_iPageIndex;
	int m_iItemNum;
	vector<vector<_variant_t> > m_strPath;//���Դ洢·����ǰ����±����Ա�ʾ��Ӧ���飬������±�����Ϊ{Ԥ��ͼƬ·������Ŀ��ͼƬ·��1����Ŀ��ͼƬ·��2....}
	
	CString m_tmpStrPath[6][6]; //���Դ洢·����ǰ����±����Ա�ʾ��Ӧ���飬������±�����Ϊ{Ԥ��ͼƬ·������Ŀ��ͼƬ·��1����Ŀ��ͼƬ·��2....}
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
