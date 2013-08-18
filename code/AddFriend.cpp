// AddFriend.cpp : 实现文件
//

#include "stdafx.h"
//#include "ADO.h"
#include "AddFriend.h"
#include "afxdialogex.h"
#include "resource.h"

// CAddFriend 对话框

IMPLEMENT_DYNAMIC(CAddFriend, CDialogEx)

	CAddFriend::CAddFriend(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddFriend::IDD, pParent)
	, text(_T(""))
	, is_ID(0)
{
}

CAddFriend::~CAddFriend()
{
}

void CAddFriend::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT_FOR_SEARCH, text);
	DDX_Radio(pDX, IDC_SEARCH_BY_ID, is_ID);
	DDX_Control(pDX, IDOK, m_btSearch);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}


BEGIN_MESSAGE_MAP(CAddFriend, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CAddFriend::OnBnClickedOk)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAddFriend 消息处理程序

BOOL CAddFriend::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return true;
}
void CAddFriend::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	GetDlgItemText(IDC_TEXT_FOR_SEARCH, text);
	CDialogEx::OnOK();
}


void CAddFriend::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CDC *pDC = GetDC();
	pDC->SelectStockObject (DC_PEN);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SetDCPenColor(DURIAN_COLOR_ORANGE);
	
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	pDC->Rectangle(&rect);

	pDC->FillSolidRect(rect.left, rect.top, rect.right, 30, DURIAN_COLOR_ORANGE);

	ReleaseDC(pDC);
	
	GetDlgItem(IDC_ADDFRIEND_TITLE)->RedrawWindow();
}


HBRUSH CAddFriend::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	UINT ctrlID = pWnd->GetDlgCtrlID();
	if(ctrlID == IDC_ADDFRIEND_TITLE)
	{
		pDC->SetTextColor(DURIAN_COLOR_WHITE);
		pDC->SetBkColor(DURIAN_COLOR_ORANGE);
		return (HBRUSH) ::CreateSolidBrush(DURIAN_COLOR_ORANGE);
	}
	return hbr;
}
