// ItemDetailDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Durian.h"
#include "ItemDetailDlg.h"
#include "afxdialogex.h"
#include "ControllerEdit.h"
#include "CommentDlg.h"
#include "MessageDlg.h"
#include "FileManage.h"

#define m_user CDurianApp::m_user
#define m_db CDurianApp::m_db
#define m_strFtp CDurianApp::m_strFtp
#define m_ftpRootDir CDurianApp::m_ftpRootDir

// CItemDetailDlg 对话框

IMPLEMENT_DYNAMIC(CItemDetailDlg, CDialog)

CItemDetailDlg::CItemDetailDlg(bool isAdmin, HBITMAP hbm, vector<_variant_t> vectorItem, CWnd* pParent /*=NULL*/)
	: CDialog(CItemDetailDlg::IDD, pParent)
{
	m_hbm = hbm;
	m_vectorItem = vectorItem;
	m_bIsAdmin = isAdmin;
	m_iRate = 0;

	m_imgStar.Load(L"res\\durian.png");
	m_imgBStar.Load(L"res\\durian-b.png");

	m_iRateNum = (int)m_vectorItem[3];
	m_fTotalRate = (m_vectorItem[4].fltVal) * m_iRateNum;

	if(m_iRateNum)
		m_iCurRate = (int) (double((m_fTotalRate)/m_iRateNum) + 0.5);
		
	else
		m_iCurRate = 0;

	/*
	if(m_iCurRate==4)
		AfxMessageBox(L"HI!");
		*/
}

CItemDetailDlg::~CItemDetailDlg()
{
	//m_img.Detach();
}

void CItemDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ITEM_DETAIL_COMMENT, m_btComment);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_ITEM_DETAIL_DELETE, m_btDelete);
	DDX_Control(pDX, IDC_ITEM_DETAIL_TITLE, m_stTitile);
	DDX_Control(pDX, IDC_ITEM_DETAIL_CLOSE, m_btClose);
	//DDX_Control(pDX, IDC_STAR1, m_picStar1);
	DDX_Control(pDX, IDC_RATE, m_btnRate);
}


BEGIN_MESSAGE_MAP(CItemDetailDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ITEM_DETAIL_COMMENT, &CItemDetailDlg::OnBnClickedItemDetailComment)
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_ITEM_DETAIL_CLOSE, &CItemDetailDlg::OnBnClickedItemDetailClose)
	//ON_BN_CLICKED(IDC_PRESS_OK, &CItemDetailDlg::OnBnClickedPressOk)
	ON_STN_CLICKED(IDC_STAR1, &CItemDetailDlg::OnStnClickedStar1)
	ON_STN_CLICKED(IDC_STAR2, &CItemDetailDlg::OnStnClickedStar2)
	ON_STN_CLICKED(IDC_STAR3, &CItemDetailDlg::OnStnClickedStar3)
	ON_STN_CLICKED(IDC_STAR4, &CItemDetailDlg::OnStnClickedStar4)
	ON_STN_CLICKED(IDC_STAR5, &CItemDetailDlg::OnStnClickedStar5)
	ON_BN_CLICKED(IDC_RATE, &CItemDetailDlg::OnBnClickedRate)
	ON_BN_CLICKED(IDC_ITEM_DETAIL_DELETE, &CItemDetailDlg::OnBnClickedItemDetailDelete)
END_MESSAGE_MAP()


// CItemDetailDlg 消息处理程序


BOOL CItemDetailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CControllerEdit::ShowPicture(this, IDC_ITEM_DETAIL_PIC, m_hbm);
	SetDlgItemTextW(IDC_ITEM_DETAIL_INTRO, _VariantToCString(m_vectorItem[1]));
	SetDlgItemTextW(IDC_ITEM_DETAIL_TEXT , _VariantToCString(m_vectorItem[7]));

	/*
	if(m_bIsAdmin)
	{
		GetDlgItem(IDOK)->ShowWindow(TRUE);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
	*/

	//GetDlgItem(IDC_ITEM_DETAIL_DELETE)->ShowWindow(m_bIsAdmin);

	m_btDelete.m_clrButtonColHoverd = DURIAN_COLOR_RED;
	if(m_user.m_iUserType == USER_ADMIN)
	{
		m_btDelete.EnableWindow(true);
		m_btDelete.ShowWindow(true);
	}
	
	CString title;
	switch (_VariantToCString(m_vectorItem[5])[0])
	{
	case 'm': title = L"电影"; break;
	case 'b': title = L"书籍"; break;
	case 'a': title = L"时事"; break;
	}
	title+=L"：" + _VariantToCString(m_vectorItem[1]);
	m_stTitile.SetWindowText(title);

	return true;
}


void CItemDetailDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CControllerEdit::ShowPicture(this, IDC_ITEM_DETAIL_PIC, m_hbm);
	SetDlgItemTextW(IDC_ITEM_DETAIL_INTRO, _VariantToCString(m_vectorItem[2]));
	SetDlgItemTextW(IDC_ITEM_DETAIL_TEXT , _VariantToCString(m_vectorItem[7]));

	CDC *pDC = GetDC();
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	pDC->SelectStockObject(DC_PEN);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SetDCPenColor(DURIAN_COLOR_ORANGE);
	pDC->Rectangle(&rect);

	pDC->FillSolidRect(rect.left, rect.top, rect.right, 30, DURIAN_COLOR_ORANGE);
	
	GetDlgItem(IDC_ITEM_DETAIL_PIC)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.left--; rect.top--; rect.bottom++; rect.right++;
	pDC->Rectangle(&rect);

	GetDlgItem(IDC_ITEM_DETAIL_INTRO)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.left--; rect.top-=2; rect.bottom++; rect.right++;
	pDC->Rectangle(&rect);

	GetDlgItem(IDC_ITEM_DETAIL_TEXT)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.left--; rect.top-=2; rect.bottom++; rect.right++;
	pDC->Rectangle(&rect);

	ReleaseDC(pDC);

	m_stTitile.RedrawWindow();
	m_btClose.RedrawWindow();

	SynchornizeDB();

	/*
	CImage img;
	img.Load(L"res\\star.png");
	CControllerEdit::ShowPicture(this, IDC_STAR1, HBITMAP(img));
	*/
	
	//m_picStar1.SetIcon(::LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_STAR)));
}


void CItemDetailDlg::OnBnClickedItemDetailComment()
{
	// TODO: 在此添加控件通知处理程序代码
	CCommentDlg commentDlg(_VariantToCString(m_vectorItem[5]), _VariantToCString(m_vectorItem[1]));
	commentDlg.m_nUserID = m_user.GetUserId();
	commentDlg.m_nItemID = (int)m_vectorItem[0];
	commentDlg.m_bAdmin = (m_user.m_iUserType == USER_ADMIN);
	commentDlg.DoModal();
}

//
//void CItemDetailDlg::OnOK()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	CMessageDlg msgDlg(L"确定删除该条目？", L"确定删除");
//	if(msgDlg.DoModal() != IDOK)
//		return ;
//
//	CString sql;
//	sql.Format(L"delete from item where item_id = %d", (int)m_vectorItem[0]);
//	if(!m_db.Delete(sql))
//	{
//		AfxMessageBox(L"条目删除失败！");
//		return ;
//	}
//	
//	sql.Format(L"delete from comment where item_id = %d", (int)m_vectorItem[0]);
//	AfxMessageBox(L"条目已删除。");
//	
//	//item/movie/
//	CString filename = L"item/";
//	CString type = _VariantToCString(m_vectorItem[5]);
//	if(type[0]=='a')
//		filename = filename+L"affair/";
//	else if(type[0]=='b')
//		filename = filename+L"book/";
//	else
//		filename = filename+L"movie/";
//	filename = filename + _VariantToCString(m_vectorItem[1]) + L"/preview.jpg";
//	CFileManage::DeleteItemFtp(m_strFtp, filename);
//
//	CDialog::OnOK();
//}


HBRUSH CItemDetailDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	UINT ctrlID = pWnd->GetDlgCtrlID();
	if(ctrlID == IDC_ITEM_DETAIL_TITLE)
	{
		pDC->SetTextColor(DURIAN_COLOR_WHITE);
		pDC->SetBkColor(DURIAN_COLOR_ORANGE);
		return (HBRUSH) ::CreateSolidBrush(DURIAN_COLOR_ORANGE);
	}
	return hbr;
}


LRESULT CItemDetailDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CRect rect;
	GetClientRect(&rect);
	rect.bottom = rect.top + 30;
	ClientToScreen(&rect);

	return rect.PtInRect(point)? HTCAPTION : CDialog::OnNcHitTest(point);

	//return CDialog::OnNcHitTest(point);
}

void CItemDetailDlg::SynchornizeDB()
{
	for(int i = 0; i<m_iCurRate;++i)
		CControllerEdit::ShowPicture(this, IDC_CUR_STAR1+i, HBITMAP(m_imgStar));
	for(int i = m_iCurRate; i<5;++i)
		CControllerEdit::ShowPicture(this, IDC_CUR_STAR1+i, HBITMAP(m_imgBStar));

	for(int i=0;i<m_iRate;++i)
		CControllerEdit::ShowPicture(this, IDC_STAR1+i, HBITMAP(m_imgStar));
	for(int i=m_iRate;i<5;++i)
		CControllerEdit::ShowPicture(this, IDC_STAR1+i, HBITMAP(m_imgBStar));

	SetDlgItemText(IDC_RATENUM, L"共计"+_VariantToCString(m_iRateNum)+L"次评分");

}

void CItemDetailDlg::OnBnClickedItemDetailClose()
{
	// TODO: 在此添加控件通知处理程序代码
	this->SendMessage(WM_CLOSE);
}


void CItemDetailDlg::OnStnClickedStar1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iRate = 1;
	OnPaint();
}


void CItemDetailDlg::OnStnClickedStar2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iRate = 2;
	OnPaint();
}


void CItemDetailDlg::OnStnClickedStar3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iRate = 3;
	OnPaint();
}


void CItemDetailDlg::OnStnClickedStar4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iRate = 4;
	OnPaint();
}


void CItemDetailDlg::OnStnClickedStar5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iRate = 5;
	OnPaint();
}


void CItemDetailDlg::OnBnClickedRate()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_user.m_iUserType ==USER_CUSTOMER)
	{
		AfxMessageBox(L"游客您好！请先登录再评分！");
		return;
	}

	m_btnRate.EnableWindow(FALSE);
	
	m_iRateNum++;
	m_fTotalRate += m_iRate;
	m_iCurRate = m_fTotalRate/m_iRateNum;

	CString sql;
	sql.Format(L"update item set ratenum=%d, rate=%lf where item_id=%d", m_iRateNum, m_fTotalRate/m_iRateNum, (int)m_vectorItem[0]);
	int result = m_db.Update(sql);
	if(result == 1)
		AfxMessageBox(L"评分成功！", MB_ICONINFORMATION);
	else
		AfxMessageBox(L"评分失败！");

	OnPaint();
	
}


void CItemDetailDlg::OnBnClickedItemDetailDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CMessageDlg msgDlg(L"确定删除该条目？", L"确定删除");
	if(msgDlg.DoModal() != IDOK)
		return ;

	CString sql;
	sql.Format(L"delete from item where item_id = %d", (int)m_vectorItem[0]);
	if(!m_db.Delete(sql))
	{
		AfxMessageBox(L"条目删除失败！");
		return ;
	}
	
	sql.Format(L"delete from comment where item_id = %d", (int)m_vectorItem[0]);
	AfxMessageBox(L"条目已删除。");
	
	//item/movie/
	CString filename = m_ftpRootDir;
	CString type = _VariantToCString(m_vectorItem[5]);
	if(type[0]=='a')
		filename = filename+L"affair/";
	else if(type[0]=='b')
		filename = filename+L"book/";
	else
		filename = filename+L"movie/";
	filename = filename + _VariantToCString(m_vectorItem[1]) + L"/preview.jpg";
	CFileManage::DeleteItemFtp(m_strFtp, filename);

	CDialog::OnOK();
}
