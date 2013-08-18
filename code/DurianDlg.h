
// DurianDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "BookDlg.h"
#include "MovieDlg.h"
#include "MainDlg.h"
#include "AffairDlg.h"
#include "TabSheet.h"
#include "ScrollDialog.h"
#include "User.h"
#include "afxwin.h"
#include "DurianButton.h"


// CDurianDlg �Ի���
class CDurianDlg : public CDialogEx   //CDialogEx to CScrollDialog
{
// ����
public:
	CDurianDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DURIAN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CTabCtrl m_tabCtrl;

	CMainDlg m_pageMain;
	CMovieDlg m_pageMovie;
	CBookDlg m_pageBook;
	CAffairDlg m_pageAffair;

	CFont m_fontTitle;

	CTabSheet m_sheet;

	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedCreateItem();
	afx_msg void OnBnClickedRegister();
	afx_msg void OnBnClickedFriendManage();
	afx_msg void OnBnClickedAccountManage();
	afx_msg void OnBnClickedMainRefresh();
private:
	void enableButtons(bool enable);
	CDurianButton m_btLogin;
	CDurianButton m_btRegister;
	CDurianButton m_btRefresh;
	CDurianButton m_btFriends;
	CDurianButton m_btCreateItem;
	CDurianButton m_btAccountManage;
	CDurianButton m_btCancel;
	CStatic m_stPrompt;
	CDurianButton m_btMin;
	CDurianButton m_btClose;
	CDurianButton m_btInfo;

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:

public:
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedMin();
	afx_msg LRESULT OnNcHitTest(CPoint point);
private:
	CStatic m_stTitle;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedEditInfo();
private:

public:
	afx_msg void OnBnClickedRate();
	afx_msg void OnStnClickedTitle();
	afx_msg void OnStnClickedAuthorinfo();
};

//extern CDurianDlg durianDlg;