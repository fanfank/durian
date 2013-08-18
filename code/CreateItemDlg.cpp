// CreateItemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Durian.h"
#include "CreateItemDlg.h"
#include "afxdialogex.h"
#include "ControllerEdit.h"
#include "FileSizeDlg.h"

#define m_db CDurianApp::m_db
#define m_bIsFtpConnected CDurianApp::m_bIsFtpConnected

// CCreateItemDlg 对话框

IMPLEMENT_DYNAMIC(CCreateItemDlg, CDialog)

CCreateItemDlg::CCreateItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateItemDlg::IDD, pParent)
	, m_strName(_T(""))
	, m_strAbstract(_T(""))
	, m_strContent(_T(""))
{
	m_strCoverPath = L"";
	m_strType = L"";
}

CCreateItemDlg::~CCreateItemDlg()
{
	m_imgCoverPic.Detach();
}

void CCreateItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CREATEITEM_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 120);
	DDX_Text(pDX, IDC_CREATEITEM_ABSTRACT, m_strAbstract);
	DDV_MaxChars(pDX, m_strAbstract, 120);
	DDX_Text(pDX, IDC_CREATEITEM_DETAIL, m_strContent);
	DDX_Control(pDX, IDC_CREATEITEM_COVER_SELECT, m_btCoverSelect);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_CREATEITEM_PROMPT, m_stPrompt);
	DDX_Control(pDX, IDC_CREATEITEM_CLOSE, m_btClose);
}


BEGIN_MESSAGE_MAP(CCreateItemDlg, CDialog)
	ON_BN_CLICKED(IDC_CREATEITEM_COVER_SELECT, &CCreateItemDlg::OnBnClickedCreateitemCoverSelect)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CCreateItemDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CREATEITEM_TYPE_MOVIE, &CCreateItemDlg::OnBnClickedCreateitemTypeMovie)
	ON_BN_CLICKED(IDC_CREATEITEM_TYPE_BOOK, &CCreateItemDlg::OnBnClickedCreateitemTypeBook)
	ON_BN_CLICKED(IDC_CREATEITEM_TYPE_AFFAIR, &CCreateItemDlg::OnBnClickedCreateitemTypeAffair)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CREATEITEM_CLOSE, &CCreateItemDlg::OnBnClickedCreateitemClose)
END_MESSAGE_MAP()


// CCreateItemDlg 消息处理程序


void CCreateItemDlg::OnBnClickedCreateitemCoverSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	wchar_t *filters = L"位图文件(*.bmp)|*.bmp|可交换图形格式文件(*.gif)|*.gif|联合图像专家组文件(*.jpg)|*.jpg|可移植网络图形文件(*.png)|*.png|所有文件(*.*)|*.*||";
	CFileDialog fileDlg(TRUE, L"bmp", L"*.bmp", 
				OFN_HIDEREADONLY, filters);

	CString sFileName;
	bool fitSize=false;
	int openNum=0;
	while(!fitSize)
	{
	 if(fileDlg.DoModal() == IDOK) 
			sFileName = fileDlg.GetPathName();
	 else return;

	 CFileStatus fs;
	 CFile::GetStatus(sFileName, fs);

	 if(fs.m_size>450450)
	 {
		 CFileSizeDlg fileSizeDlg;
		 fileSizeDlg.DoModal();
	 }
	 else
		 fitSize = true;
	}
	//img.Detach();
	m_imgCoverPic.Load(sFileName);
	if (m_imgCoverPic.IsNull()) return;

	m_strCoverPath = sFileName;
	OnPaint();
}


void CCreateItemDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CControllerEdit::ShowPicture(this, IDC_CREATEITEM_COVER_PIC, HBITMAP(m_imgCoverPic));

	CDC *pDC = GetDC();
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	pDC->SelectStockObject(DC_PEN);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SetDCPenColor(DURIAN_COLOR_ORANGE);
	pDC->Rectangle(&rect);

	pDC->FillSolidRect(rect.left, rect.top, rect.Width(), 30 , DURIAN_COLOR_ORANGE);

	GetDlgItem(IDC_CREATEITEM_COVER_PIC)->GetWindowRect(&rect);	
	ScreenToClient(&rect);
	rect.left--; rect.top--; rect.right++; rect.bottom++;
	pDC->Rectangle(&rect);
	
	ReleaseDC(pDC);

	m_stPrompt.RedrawWindow();
	m_btClose.RedrawWindow();
}


void CCreateItemDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_db.m_bIsOpen || !m_bIsFtpConnected)
	{
		AfxMessageBox(L"抱歉！未连接到数据库或FTP\n无法创建新的条目！");
		return;
	}

	UpdateData(TRUE);
	if(m_strName.IsEmpty())
	{
		AfxMessageBox(L"请输入条目名称~");
		GetDlgItem(IDC_CREATEITEM_NAME)->SetFocus();
		return;
	}
	if(m_strType.IsEmpty())
	{
		AfxMessageBox(L"请选择条目类型~");
		GetDlgItem(IDC_CREATEITEM_TYPE_MOVIE)->SetFocus();
		return;
	}
	if(m_strCoverPath.IsEmpty())
	{
		AfxMessageBox(L"请选择封面图片~");
		GetDlgItem(IDC_CREATEITEM_COVER_SELECT)->SetFocus();
		return;
	}
	if(m_strAbstract.IsEmpty())
	{
		AfxMessageBox(L"请输入介绍文字~");
		GetDlgItem(IDC_CREATEITEM_ABSTRACT)->SetFocus();
		return;
	}
	if(m_strContent.IsEmpty())
	{
		AfxMessageBox(L"请输入条目详细内容~");
		GetDlgItem(IDC_CREATEITEM_DETAIL)->SetFocus();
		return;
	}
	CDialog::OnOK();
}


void CCreateItemDlg::OnBnClickedCreateitemTypeMovie()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strType = L"movie";
}


void CCreateItemDlg::OnBnClickedCreateitemTypeBook()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strType = L"book";
}


void CCreateItemDlg::OnBnClickedCreateitemTypeAffair()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strType = L"affair";
}

HBITMAP CCreateItemDlg::GetHBITMAP()
{
	return HBITMAP(m_imgCoverPic);
}

HBRUSH CCreateItemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	UINT ctrlID = pWnd->GetDlgCtrlID();
	if(ctrlID == IDC_CREATEITEM_PROMPT)
	{
		pDC->SetTextColor(DURIAN_COLOR_WHITE);
		pDC->SetBkColor(DURIAN_COLOR_ORANGE);
		return (HBRUSH) ::CreateSolidBrush(DURIAN_COLOR_ORANGE);
	}

	return hbr;
}


void CCreateItemDlg::OnBnClickedCreateitemClose()
{
	// TODO: 在此添加控件通知处理程序代码
	this->SendMessage(WM_CLOSE);
}
