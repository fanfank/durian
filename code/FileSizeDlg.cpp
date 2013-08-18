// FileSizeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Durian.h"
#include "FileSizeDlg.h"
#include "afxdialogex.h"


// CFileSizeDlg 对话框

IMPLEMENT_DYNAMIC(CFileSizeDlg, CDialog)

CFileSizeDlg::CFileSizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSizeDlg::IDD, pParent)
{

}

CFileSizeDlg::~CFileSizeDlg()
{
}

void CFileSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOK);
}


BEGIN_MESSAGE_MAP(CFileSizeDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CFileSizeDlg 消息处理程序


BOOL CFileSizeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_btOK.m_clrButtonColNormal = DURIAN_COLOR_RED;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}





HBRUSH CFileSizeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	UINT ctrlID = pWnd->GetDlgCtrlID();
	if(ctrlID == IDC_FILESIZE_TITLE)
	{
		pDC->SetTextColor(DURIAN_COLOR_WHITE);
		pDC->SetBkColor(DURIAN_COLOR_RED);
		return (HBRUSH) ::CreateSolidBrush(DURIAN_COLOR_RED);

	}
	return hbr;
}


void CFileSizeDlg::OnPaint()
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
	
	GetDlgItem(IDC_FILESIZE_TITLE)->RedrawWindow();
}
