// AddressDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Durian.h"
#include "AddressDlg.h"
#include "afxdialogex.h"
#include "AuthorInfoDlg.h"


// CAddressDlg 对话框

IMPLEMENT_DYNAMIC(CAddressDlg, CDialog)

CAddressDlg::CAddressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddressDlg::IDD, pParent)
	, m_strFtp(_T(""))
	, m_strDB(_T(""))
{

}

CAddressDlg::~CAddressDlg()
{
}

void CAddressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADDRESS_FTP, m_strFtp);
	DDV_MaxChars(pDX, m_strFtp, 15);
	DDX_Text(pDX, IDC_ADDRESS_DB, m_strDB);
	DDV_MaxChars(pDX, m_strDB, 15);
}


BEGIN_MESSAGE_MAP(CAddressDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddressDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_ADDRESS_OFFLINE, &CAddressDlg::OnBnClickedAddressOffline)
	ON_STN_CLICKED(IDC_AUTHOR_INFO, &CAddressDlg::OnStnClickedAuthorInfo)
END_MESSAGE_MAP()


// CAddressDlg 消息处理程序


void CAddressDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if(m_strDB.IsEmpty())
	{
		AfxMessageBox(L"请填写数据库所在服务器IP地址！");
		GetDlgItem(IDC_ADDRESS_DB)->SetFocus();
	}
	else if(m_strFtp.IsEmpty())
	{
		AfxMessageBox(L"请填写FTP服务器地址！");
		GetDlgItem(IDC_ADDRESS_FTP)->SetFocus();
	}
	else
		CDialog::OnOK();
}


BOOL CAddressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_ADDRESS_FTP, L"123.123.123.123");
	SetDlgItemText(IDC_ADDRESS_DB, L"123.123.123.123");

	//SetDlgItemText(IDC_ADDRESS_FTP, L"172.18.71.99");
	//SetDlgItemText(IDC_ADDRESS_DB, L"172.18.71.99");
	//SetDlgItemText(IDC_ADDRESS_FTP, L"172.18.71.2");
	//SetDlgItemText(IDC_ADDRESS_DB, L"172.18.71.2");


	return true;
}


void CAddressDlg::OnBnClickedAddressOffline()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_ADDRESS_FTP, L"localhost");
	SetDlgItemText(IDC_ADDRESS_DB, L"localhost");
	UpdateData();
	return CDialog::OnCancel();
}


void CAddressDlg::OnStnClickedAuthorInfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CAuthorInfoDlg infoDlg;
	infoDlg.DoModal();
}
