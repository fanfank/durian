#pragma once
#include "afxwin.h"
#include "DurianButton.h"

// CAffairDlg �Ի���

class CAffairDlg : public CDialog
{
	DECLARE_DYNAMIC(CAffairDlg)

public:
	CAffairDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAffairDlg();

// �Ի�������
	enum { IDD = IDD_AFFAIR };

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
	afx_msg void OnBnClickedAffairNextpage();
	afx_msg void OnBnClickedAffairPreviouspage();
	CDurianButton m_btnAffairGp1Ent;
	CDurianButton m_btnAffairGp2Ent;
	CDurianButton m_btnAffairGp3Ent;
	CDurianButton m_btnAffairGp4Ent;
	CDurianButton m_btnAffairGp5Ent;
	CDurianButton m_btnAffairGp6Ent;
	CDurianButton m_btnAffairPrePg;
	CDurianButton m_btnAffairNxtPg;

	afx_msg void OnBnClickedBookGroup1Enter();
	afx_msg void OnBnClickedBookGroup2Enter();
	afx_msg void OnBnClickedBookGroup3Enter();
	afx_msg void OnBnClickedBookGroup4Enter();
	afx_msg void OnBnClickedBookGroup5Enter();
	afx_msg void OnBnClickedBookGroup6Enter();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
