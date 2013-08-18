// ChangePassDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Durian.h"
#include "ChangePassDlg.h"
#include "afxdialogex.h"
#include "resource.h"


// CChangePassDlg 对话框

IMPLEMENT_DYNAMIC(CChangePassDlg, CDialogEx)

CChangePassDlg::CChangePassDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangePassDlg::IDD, pParent)
	, old_password(_T(""))
	, new_password1(_T(""))
	, new_password2(_T(""))
{
	password = "";
}

CChangePassDlg::~CChangePassDlg()
{
}

void CChangePassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OLD_PASSWORD, old_password);
	DDX_Text(pDX, IDC_NEW_PASSWORD1, new_password1);
	DDX_Text(pDX, IDC_NEW_PASSWORD2, new_password2);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}


BEGIN_MESSAGE_MAP(CChangePassDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChangePassDlg::OnBnClickedOk)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CChangePassDlg 消息处理程序

bool CChangePassDlg::PasswordValidation()
{
	CString temp;
	GetDlgItemText(IDC_NEW_PASSWORD1, temp);
	const int len = temp.GetLength();
	if(len < 6 || len > 15)
		return false;
	else
	{
		for(int i = 0;i < len; i++)
		{
			if( !( ('a'<=temp[i]&&temp[i]<='z')||('0'<=temp[i]&&temp[i]<='9')||('A'<=temp[i]&&temp[i]<='Z') ))
				return false;
		}
	}
	return true;
}

bool CChangePassDlg::PasswordMatch()
{
	CString temp1, temp2;
	GetDlgItemText(IDC_NEW_PASSWORD1, temp1);
	GetDlgItemText(IDC_NEW_PASSWORD2, temp2);
	return (temp1 == temp2);
}

bool CChangePassDlg::OldPasswordMatch() {
	CString temp;
	GetDlgItemText(IDC_OLD_PASSWORD, temp);
	return (temp == password);
}

bool CChangePassDlg::CheckPasswordForm() {
	bool checkRecult = true;
	CString errPrompt;
	if(!OldPasswordMatch()){
		errPrompt = L"输入的密码不正确，请重新输入！";
		GetDlgItem(IDC_OLD_PASSWORD)->SetFocus();
		checkRecult = false;
	}

	else if(!PasswordValidation())
	{
		errPrompt = L"密码无效。密码由英文字母、数字组成，长度为6到20位。";
		GetDlgItem(IDC_NEW_PASSWORD1)->SetFocus();
		checkRecult = false;
	}
	else if(!PasswordMatch())
	{
		errPrompt = L"两次输入的密码不一致，请重新输入";
		GetDlgItem(IDC_NEW_PASSWORD2)->SetFocus();
		checkRecult = false;
	}
	if(!checkRecult)
	{
		AfxMessageBox(errPrompt);
	}
	return checkRecult;
}

void CChangePassDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if(CheckPasswordForm()) {
		AfxMessageBox(L"修改密码成功");
		CDialogEx::OnOK();
	}
}


BOOL CChangePassDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_btOK.m_clrButtonColNormal = m_btCancel.m_clrButtonColNormal = DURIAN_COLOR_RED;

	return TRUE;
}


void CChangePassDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CDC *pDC = GetDC();
	pDC->SelectStockObject (DC_PEN);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SetDCPenColor(DURIAN_COLOR_RED);
	
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	pDC->Rectangle(&rect);

	pDC->FillSolidRect(rect.left, rect.top, rect.right, 30, DURIAN_COLOR_RED);

	ReleaseDC(pDC);
	
	GetDlgItem(IDC_CHANGEPASS_TITLE)->RedrawWindow();
}


HBRUSH CChangePassDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	UINT ctrlID = pWnd->GetDlgCtrlID();
	if(ctrlID == IDC_CHANGEPASS_TITLE)
	{
		pDC->SetTextColor(DURIAN_COLOR_WHITE);
		pDC->SetBkColor(DURIAN_COLOR_RED);
		return (HBRUSH) ::CreateSolidBrush(DURIAN_COLOR_RED);
	}
	return hbr;
}
