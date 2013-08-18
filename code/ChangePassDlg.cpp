// ChangePassDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Durian.h"
#include "ChangePassDlg.h"
#include "afxdialogex.h"
#include "resource.h"


// CChangePassDlg �Ի���

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


// CChangePassDlg ��Ϣ�������

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
		errPrompt = L"��������벻��ȷ�����������룡";
		GetDlgItem(IDC_OLD_PASSWORD)->SetFocus();
		checkRecult = false;
	}

	else if(!PasswordValidation())
	{
		errPrompt = L"������Ч��������Ӣ����ĸ��������ɣ�����Ϊ6��20λ��";
		GetDlgItem(IDC_NEW_PASSWORD1)->SetFocus();
		checkRecult = false;
	}
	else if(!PasswordMatch())
	{
		errPrompt = L"������������벻һ�£�����������";
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(CheckPasswordForm()) {
		AfxMessageBox(L"�޸�����ɹ�");
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
