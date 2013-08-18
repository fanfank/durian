#pragma once
#include "afxwin.h"
#include "DurianButton.h"

// CFileSizeDlg �Ի���

class CFileSizeDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileSizeDlg)

public:
	CFileSizeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFileSizeDlg();

// �Ի�������
	enum { IDD = IDD_FILESIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CDurianButton m_btOK;
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
