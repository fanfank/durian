#pragma once


// CAuthorInfoDlg �Ի���

class CAuthorInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAuthorInfoDlg)

public:
	CAuthorInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAuthorInfoDlg();

// �Ի�������
	enum { IDD = IDD_AUTHORINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
