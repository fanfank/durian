// AffairDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Durian.h"
#include "AffairDlg.h"
#include "afxdialogex.h"
#include "ControllerEdit.h"
#include "FileManage.h"
#include "ItemDetailDlg.h"

#define m_db CDurianApp::m_db
#define m_pRecordSet CDurianApp::m_pRecordSet
#define m_strWorkingDir CDurianApp::m_strWorkingDir
#define m_strDB CDurianApp::m_strDB
#define m_strFtp CDurianApp::m_strFtp
#define m_user CDurianApp::m_user
#define m_ftpRootDir CDurianApp::m_ftpRootDir
// CAffairDlg 对话框

IMPLEMENT_DYNAMIC(CAffairDlg, CDialog)

CAffairDlg::CAffairDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAffairDlg::IDD, pParent)
{
	m_iLastPos = m_iLastDownloadPage = m_iItemNum = m_iPageIndex = 0;
}

CAffairDlg::~CAffairDlg()
{
}

void CAffairDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_verScroll);
	DDX_Control(pDX, IDC_AFFAIR_GROUP1_ENTER, m_btnAffairGp1Ent);
	DDX_Control(pDX, IDC_AFFAIR_GROUP2_ENTER, m_btnAffairGp2Ent);
	DDX_Control(pDX, IDC_AFFAIR_GROUP3_ENTER, m_btnAffairGp3Ent);
	DDX_Control(pDX, IDC_AFFAIR_GROUP4_ENTER, m_btnAffairGp4Ent);
	DDX_Control(pDX, IDC_AFFAIR_GROUP5_ENTER, m_btnAffairGp5Ent);
	DDX_Control(pDX, IDC_AFFAIR_GROUP6_ENTER, m_btnAffairGp6Ent);
	DDX_Control(pDX, IDC_AFFAIR_PREVIOUSPAGE, m_btnAffairPrePg);
	DDX_Control(pDX, IDC_AFFAIR_NEXTPAGE, m_btnAffairNxtPg);
}


BEGIN_MESSAGE_MAP(CAffairDlg, CDialog)
	ON_WM_VSCROLL()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_AFFAIR_NEXTPAGE, &CAffairDlg::OnBnClickedAffairNextpage)
	ON_BN_CLICKED(IDC_AFFAIR_PREVIOUSPAGE, &CAffairDlg::OnBnClickedAffairPreviouspage)
	ON_BN_CLICKED(IDC_AFFAIR_GROUP1_ENTER, &CAffairDlg::OnBnClickedBookGroup1Enter)
	ON_BN_CLICKED(IDC_AFFAIR_GROUP2_ENTER, &CAffairDlg::OnBnClickedBookGroup2Enter)
	ON_BN_CLICKED(IDC_AFFAIR_GROUP3_ENTER, &CAffairDlg::OnBnClickedBookGroup3Enter)
	ON_BN_CLICKED(IDC_AFFAIR_GROUP4_ENTER, &CAffairDlg::OnBnClickedBookGroup4Enter)
	ON_BN_CLICKED(IDC_AFFAIR_GROUP5_ENTER, &CAffairDlg::OnBnClickedBookGroup5Enter)
	ON_BN_CLICKED(IDC_AFFAIR_GROUP6_ENTER, &CAffairDlg::OnBnClickedBookGroup6Enter)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CAffairDlg 消息处理程序


BOOL CAffairDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_verScroll.SetScrollRange(0,300);
	m_verScroll.SetScrollPos(0);

	SynchronizeDB();
	/*
	CString sql;
	sql = L"select * from item where item_type=\"a\" order by rate";
	m_iItemNum = m_db.Select(sql, m_strPath);
	//载入路径完毕

	//从FTP下载图片到本地临时文件夹
	Download(m_iPageIndex*6, 6, L"preview.jpg");
	*/
	return true;
}


void CAffairDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int pos = m_verScroll.GetScrollPos();
	switch(nSBCode)
	{
	case SB_LINEUP:
		pos--;
		break;
	case SB_LINEDOWN:
		pos++;
		break;
	case SB_PAGEUP:
		pos-=10;
		break;
	case SB_PAGEDOWN:
		pos+=10;
		break;
	case SB_THUMBTRACK:
		pos = nPos;
		break;
	case SB_TOP:
		pos = 0;
		break;
	case SB_BOTTOM:
		pos = 200;
		break;
	}
	if(pos>300) pos = 300;
	if(pos<0) pos = 0;

	m_verScroll.SetScrollPos(pos);

	for(UINT i = 0; i<6; ++i)
	{
		GetDlgItem(IDC_AFFAIR_GROUP1+i)->ShowWindow(0);
		CControllerEdit::MoveController(this, IDC_AFFAIR_GROUP1_PIC+i, 0, -(pos-m_iLastPos));
		CControllerEdit::MoveController(this, IDC_AFFAIR_GROUP1_EDIT+i, 0, -(pos-m_iLastPos));
		CControllerEdit::MoveController(this, IDC_AFFAIR_GROUP1_ENTER+i, 0, -(pos-m_iLastPos));
	}
	
	for(UINT i = 0; i<6; ++i)
	{
		GetDlgItem(IDC_AFFAIR_GROUP1+i)->ShowWindow(1);
		CControllerEdit::MoveController(this, IDC_AFFAIR_GROUP1+i, 0, -(pos-m_iLastPos));
	}
	CControllerEdit::MoveController(this, IDC_AFFAIR_NEXTPAGE, 0, -(pos-m_iLastPos));
	CControllerEdit::MoveController(this, IDC_AFFAIR_PREVIOUSPAGE, 0, -(pos-m_iLastPos));

	m_iLastPos = pos;

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CAffairDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CString prescipt = L"tmp\\item\\affair\\";  //要先下载临时信息到临时文件夹
	CString picpath;
	int itemIndex;
	int i;

	/*
	AfxMessageBox(L"books");
	if(m_iItemNum>0)
		AfxMessageBox(L">0");
	*/

	for(i=0;(itemIndex = m_iPageIndex*6 + i)<m_iItemNum && i<6;++i) //载入图片与时事说明
	{
		GetDlgItem(IDC_AFFAIR_GROUP1_PIC+i)->ShowWindow(TRUE);

		GetDlgItem(IDC_AFFAIR_GROUP1_ENTER+i)->ShowWindow(TRUE);
		GetDlgItem(IDC_AFFAIR_GROUP1_ENTER+i)->EnableWindow(TRUE);

		GetDlgItem(IDC_AFFAIR_GROUP1_EDIT+i)->ShowWindow(TRUE);
		
		SetDlgItemText(IDC_AFFAIR_GROUP1+i,L"时事："+_VariantToCString(m_strPath[itemIndex][1]));
		SetDlgItemText(IDC_AFFAIR_GROUP1_EDIT+i,L"内容简介："+_VariantToCString(m_strPath[itemIndex][2]));

		picpath = prescipt + _VariantToCString(m_strPath[itemIndex][1]) + L"\\preview.jpg";
		m_imgPreview[i].Load(picpath);
		if(!m_imgPreview[i].IsNull())
			CControllerEdit::ShowPicture(this, IDC_AFFAIR_GROUP1_PIC+i, (HBITMAP)m_imgPreview[i]);
	}
	for(;i<6;i++)
	{
		GetDlgItem(IDC_AFFAIR_GROUP1_EDIT+i)->ShowWindow(FALSE);

		GetDlgItem(IDC_AFFAIR_GROUP1_PIC+i)->ShowWindow(FALSE);

		GetDlgItem(IDC_AFFAIR_GROUP1_ENTER+i)->ShowWindow(FALSE);
		GetDlgItem(IDC_AFFAIR_GROUP1_ENTER+i)->EnableWindow(FALSE);
		SetDlgItemText(IDC_AFFAIR_GROUP1+i,L"没有更多时事");
		SetDlgItemText(IDC_AFFAIR_GROUP1_EDIT+i,L"没有时事");
	}
}


void CAffairDlg::OnBnClickedAffairNextpage()
{
	// TODO: 在此添加控件通知处理程序代码
	if((m_iPageIndex+1)*6 < m_iItemNum)
	{
	 m_iPageIndex++;
	 
	 if(m_iPageIndex > m_iLastDownloadPage) //从数据库下载资料
	 {
		 m_iLastDownloadPage = m_iPageIndex;
		 Download(m_iPageIndex*6, 6, L"preview.jpg");
	 }

	 OnPaint();
	 OnVScroll(SB_TOP, m_verScroll.GetScrollPos(), &m_verScroll);
	}
	else
		MessageBox(L"已经到达最后一页~！",L"没有更多条目");
}


void CAffairDlg::OnBnClickedAffairPreviouspage()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_iPageIndex>0)
	{
		m_iPageIndex--;
		OnPaint();
		OnVScroll(SB_TOP, m_verScroll.GetScrollPos(), &m_verScroll);
	}
	else
		MessageBox(L"已经到达最前一页~！",L"没有更多条目");
}

void CAffairDlg::Download(int startIndex, int downloadNum, LPCTSTR fileName)
{
	if(!CFileManage::m_bIsFtpConnected)
		return;

	for(int i = 0; i<downloadNum && (startIndex+i)<m_iItemNum; i++)
	{
		CString sourceName = m_ftpRootDir + L"affair/" + _VariantToCString(m_strPath[startIndex+i][1]) + L"/" + fileName;
		
		//* 当实际发布的时候请使用这个代码
		/*
		wchar_t currentDir[500];// = new wchar_t[500];
		HMODULE hl = GetModuleHandle(NULL);
		GetModuleFileName(hl, currentDir, 500);

		//GetCurrentDirectory(500,currentDir);
		CString curDir = CString(currentDir);
		for(int j = curDir.GetLength() - 1; curDir[j]!='\\';--j)
			curDir.Delete(j);
		*/

		CString destName = m_strWorkingDir + L"tmp\\item\\affair\\" + _VariantToCString(m_strPath[startIndex+i][1]); //+ L"\\" + fileName;
		if(!CFileManage::FolderExist(destName))
			CreateDirectory(destName, NULL);
		
		destName = destName + L"\\" + fileName;
		 //*/

		if(!CFileManage::DownloadFtp(/*L"localhost"*/ m_strFtp, sourceName, destName))
		{
			CString error;
			error.Format(L"失败！\nsrcName:%s\ndestName:%s",sourceName, destName);
			AfxMessageBox(error);
		}
	}
}

bool CAffairDlg::SynchronizeDB()
{
	if(!CFileManage::m_bIsFtpConnected || !m_db.m_bIsOpen)
		return FALSE;

	CString sql;
	sql = L"select * from item where item_type=\"a\" order by item_uploadtime desc";
	m_iItemNum = m_db.Select(sql, m_strPath);
	//载入路径完毕

	//从FTP下载图片到本地临时文件夹
	Download(m_iPageIndex*6, 6, L"preview.jpg");

	m_iPageIndex = m_iLastDownloadPage = 0;
	OnPaint();
	//OnVScroll(SB_TOP, m_verScroll.GetScrollPos(), &m_verScroll);
	return true;
}

void CAffairDlg::OnBnClickedBookGroup1Enter()
{
	// TODO: 在此添加控件通知处理程序代码
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[0]), m_strPath[m_iPageIndex*6]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}


void CAffairDlg::OnBnClickedBookGroup2Enter()
{
	// TODO: 在此添加控件通知处理程序代码
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[1]), m_strPath[m_iPageIndex*6+1]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}


void CAffairDlg::OnBnClickedBookGroup3Enter()
{
	// TODO: 在此添加控件通知处理程序代码
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[2]), m_strPath[m_iPageIndex*6+2]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}


void CAffairDlg::OnBnClickedBookGroup4Enter()
{
	// TODO: 在此添加控件通知处理程序代码
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[3]), m_strPath[m_iPageIndex*6+3]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}


void CAffairDlg::OnBnClickedBookGroup5Enter()
{
	// TODO: 在此添加控件通知处理程序代码
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[4]), m_strPath[m_iPageIndex*6+4]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}


void CAffairDlg::OnBnClickedBookGroup6Enter()
{
	// TODO: 在此添加控件通知处理程序代码
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[5]), m_strPath[m_iPageIndex*6+5]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}

void CAffairDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if(bShow)
		SynchronizeDB();

	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
}
