// MessageDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "ADO.h"
#include "MessageDlg.h"
#include "afxdialogex.h"
#include "resource.h"

// CMessageDlg 对话框

IMPLEMENT_DYNAMIC(CMessageDlg, CDialogEx)

CMessageDlg::CMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMessageDlg::IDD, pParent)
{

}

CMessageDlg::CMessageDlg(CString strCon, CString strCap,  COLORREF clrBorder, CWnd *pParent)
	: CDialogEx(CMessageDlg::IDD, pParent)
{
	m_strCon = strCon;
	m_clrBorder = clrBorder;
	m_strCap = strCap;
}

CMessageDlg::~CMessageDlg()
{
}

void CMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}


BEGIN_MESSAGE_MAP(CMessageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CMessageDlg 消息处理程序


BOOL CMessageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_btOK.m_clrButtonColNormal  = m_btCancel.m_clrButtonColNormal = m_clrBorder;
	m_btOK.m_clrButtonColHoverd = m_btCancel.m_clrButtonColHoverd = DURIAN_COLOR_GREEN;

	SetDlgItemText(IDC_MESSAGEBOX_ST_CAPTION, m_strCap);
	SetDlgItemText(IDC_MESSAGEBOX_ST_CONTENT, m_strCon);

	return TRUE;
}


void CMessageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CDC *pDC = GetDC();

	pDC->SelectStockObject(DC_PEN);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SetDCPenColor(m_clrBorder);

	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	pDC->Rectangle(&rect);

	pDC->FillSolidRect(rect.left, rect.top, rect.Width(), 30, m_clrBorder);

	ReleaseDC(pDC);
}


HBRUSH CMessageDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	UINT ctrlID = pWnd->GetDlgCtrlID();
	if(ctrlID == IDC_MESSAGEBOX_ST_CAPTION)
	{
		pDC->SetTextColor(DURIAN_COLOR_WHITE);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH) ::GetStockObject(NULL_BRUSH);
	}

	return hbr;
}


LRESULT CMessageDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	rect.bottom = rect.top + 30;
	return rect.PtInRect(point)? HTCAPTION : CDialogEx::OnNcHitTest(point);
}

