#pragma once


// CAuthorInfoDlg 对话框

class CAuthorInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAuthorInfoDlg)

public:
	CAuthorInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAuthorInfoDlg();

// 对话框数据
	enum { IDD = IDD_AUTHORINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
