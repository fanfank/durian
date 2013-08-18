// BookDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Durian.h"
#include "BookDlg.h"
#include "afxdialogex.h"
#include "FileManage.h"
#include "ControllerEdit.h"
#include "ItemDetailDlg.h"

#define m_db CDurianApp::m_db
#define m_pRecordSet CDurianApp::m_pRecordSet
#define m_strWorkingDir CDurianApp::m_strWorkingDir
#define m_strDB CDurianApp::m_strDB
#define m_strFtp CDurianApp::m_strFtp
#define m_user CDurianApp::m_user
#define m_ftpRootDir CDurianApp::m_ftpRootDir
// CBookDlg �Ի���

IMPLEMENT_DYNAMIC(CBookDlg, CDialog)

CBookDlg::CBookDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBookDlg::IDD, pParent)
{
	m_iLastPos = m_iLastDownloadPage = m_iItemNum = m_iPageIndex = 0;
}

CBookDlg::~CBookDlg()
{
	for(int i=0;i<6;++i)
		m_imgPreview[i].Detach();
}

void CBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOOK_VERSCROLL, m_verScroll);
	DDX_Control(pDX, IDC_BOOK_GROUP1_ENTER, m_btnBookGp1Ent);
	DDX_Control(pDX, IDC_BOOK_GROUP2_ENTER, m_btnBookGp2Ent);
	DDX_Control(pDX, IDC_BOOK_GROUP3_ENTER, m_btnBookGp3Ent);
	DDX_Control(pDX, IDC_BOOK_GROUP4_ENTER, m_btnBookGp4Ent);
	DDX_Control(pDX, IDC_BOOK_GROUP5_ENTER, m_btnBookGp5Ent);
	DDX_Control(pDX, IDC_BOOK_GROUP6_ENTER, m_btnBookGp6Ent);
	DDX_Control(pDX, IDC_BOOK_PREVIOUSPAGE, m_btnBookPrePg);
	DDX_Control(pDX, IDC_BOOK_NEXTPAGE, m_btnBookNxtPg);
}


BEGIN_MESSAGE_MAP(CBookDlg, CDialog)
	ON_WM_VSCROLL()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BOOK_NEXTPAGE, &CBookDlg::OnBnClickedBookNextpage)
	ON_BN_CLICKED(IDC_BOOK_PREVIOUSPAGE, &CBookDlg::OnBnClickedBookPreviouspage)
	ON_BN_CLICKED(IDC_BOOK_GROUP1_ENTER, &CBookDlg::OnBnClickedBookGroup1Enter)
	ON_BN_CLICKED(IDC_BOOK_GROUP2_ENTER, &CBookDlg::OnBnClickedBookGroup2Enter)
	ON_BN_CLICKED(IDC_BOOK_GROUP3_ENTER, &CBookDlg::OnBnClickedBookGroup3Enter)
	ON_BN_CLICKED(IDC_BOOK_GROUP4_ENTER, &CBookDlg::OnBnClickedBookGroup4Enter)
	ON_BN_CLICKED(IDC_BOOK_GROUP5_ENTER, &CBookDlg::OnBnClickedBookGroup5Enter)
	ON_BN_CLICKED(IDC_BOOK_GROUP6_ENTER, &CBookDlg::OnBnClickedBookGroup6Enter)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CBookDlg ��Ϣ�������


BOOL CBookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_verScroll.SetScrollRange(0,300);
	m_verScroll.SetScrollPos(0);

	SynchronizeDB();
	/*
	CString sql;
	sql = L"select * from item where item_type=\"b\" order by rate";
	m_iItemNum = m_db.Select(sql, m_strPath);
	//����·�����

	//��FTP����ͼƬ��������ʱ�ļ���
	Download(m_iPageIndex*6, 6, L"preview.jpg");
	*/

	return true;
}


void CBookDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		GetDlgItem(IDC_BOOK_GROUP1+i)->ShowWindow(0);
		CControllerEdit::MoveController(this, IDC_BOOK_GROUP1_PIC+i, 0, -(pos-m_iLastPos));
		CControllerEdit::MoveController(this, IDC_BOOK_GROUP1_EDIT+i, 0, -(pos-m_iLastPos));
		CControllerEdit::MoveController(this, IDC_BOOK_GROUP1_ENTER+i, 0, -(pos-m_iLastPos));
	}
	
	for(UINT i = 0; i<6; ++i)
	{
		GetDlgItem(IDC_BOOK_GROUP1+i)->ShowWindow(1);
		CControllerEdit::MoveController(this, IDC_BOOK_GROUP1+i, 0, -(pos-m_iLastPos));
	}
	CControllerEdit::MoveController(this, IDC_BOOK_NEXTPAGE, 0, -(pos-m_iLastPos));
	CControllerEdit::MoveController(this, IDC_BOOK_PREVIOUSPAGE, 0, -(pos-m_iLastPos));

	m_iLastPos = pos;

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CBookDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CString prescipt = L"tmp\\item\\book\\";  //Ҫ��������ʱ��Ϣ����ʱ�ļ���
	CString picpath;
	int itemIndex;
	int i;

	/*
	AfxMessageBox(L"books");
	if(m_iItemNum>0)
		AfxMessageBox(L">0");
	*/

	for(i=0;(itemIndex = m_iPageIndex*6 + i)<m_iItemNum && i<6;++i) //����ͼƬ��ӰƬ˵��
	{
		GetDlgItem(IDC_BOOK_GROUP1_EDIT+i)->ShowWindow(TRUE);

		GetDlgItem(IDC_BOOK_GROUP1_PIC+i)->ShowWindow(TRUE);

		GetDlgItem(IDC_BOOK_GROUP1_ENTER+i)->ShowWindow(TRUE);
		GetDlgItem(IDC_BOOK_GROUP1_ENTER+i)->EnableWindow(TRUE);

		SetDlgItemText(IDC_BOOK_GROUP1+i,L"�鼮��"+_VariantToCString(m_strPath[itemIndex][1]));
		SetDlgItemText(IDC_BOOK_GROUP1_EDIT+i,L"���ݼ�飺"+_VariantToCString(m_strPath[itemIndex][2]));

		picpath = prescipt + _VariantToCString(m_strPath[itemIndex][1]) + L"\\preview.jpg";
		m_imgPreview[i].Load(picpath);

		if(!m_imgPreview[i].IsNull())
			CControllerEdit::ShowPicture(this, IDC_BOOK_GROUP1_PIC+i, (HBITMAP)m_imgPreview[i]);
	}
	for(;i<6;i++)
	{
		GetDlgItem(IDC_BOOK_GROUP1_EDIT+i)->ShowWindow(FALSE);

		GetDlgItem(IDC_BOOK_GROUP1_PIC+i)->ShowWindow(FALSE);

		GetDlgItem(IDC_BOOK_GROUP1_ENTER+i)->ShowWindow(FALSE);
		GetDlgItem(IDC_BOOK_GROUP1_ENTER+i)->EnableWindow(FALSE);

		SetDlgItemText(IDC_BOOK_GROUP1+i,L"û�и����鼮");
		SetDlgItemText(IDC_BOOK_GROUP1_EDIT+i,L"û���鼮");
	}
}


void CBookDlg::OnBnClickedBookNextpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if((m_iPageIndex+1)*6 < m_iItemNum)
	{
	 m_iPageIndex++;
	 
	 if(m_iPageIndex > m_iLastDownloadPage) //�����ݿ���������
	 {
		 m_iLastDownloadPage = m_iPageIndex;
		 Download(m_iPageIndex*6, 6, L"preview.jpg");
	 }

	 OnPaint();
	 OnVScroll(SB_TOP, m_verScroll.GetScrollPos(), &m_verScroll);
	}
	else
		MessageBox(L"�Ѿ��������һҳ~��",L"û�и�����Ŀ");
}


void CBookDlg::OnBnClickedBookPreviouspage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_iPageIndex>0)
	{
		m_iPageIndex--;
		OnPaint();
		OnVScroll(SB_TOP, m_verScroll.GetScrollPos(), &m_verScroll);
	}
	else
		MessageBox(L"�Ѿ�������ǰһҳ~��",L"û�и�����Ŀ");
}

void CBookDlg::Download(int startIndex, int downloadNum, LPCTSTR fileName)
{
	if(!CFileManage::m_bIsFtpConnected)
		return;

	for(int i = 0; i<downloadNum && (startIndex+i)<m_iItemNum; i++)
	{
		CString sourceName = m_ftpRootDir + L"book/" + _VariantToCString(m_strPath[startIndex+i][1]) + L"/" + fileName;
		
		//* ��ʵ�ʷ�����ʱ����ʹ���������
		/*
		wchar_t currentDir[500];// = new wchar_t[500];
		HMODULE hl = GetModuleHandle(NULL);
		GetModuleFileName(hl, currentDir, 500);

		//GetCurrentDirectory(500,currentDir);
		CString curDir = CString(currentDir);
		for(int j = curDir.GetLength() - 1; curDir[j]!='\\';--j)
			curDir.Delete(j);
		*/

		CString destName = m_strWorkingDir + L"tmp\\item\\book\\" + _VariantToCString(m_strPath[startIndex+i][1]); //+ L"\\" + fileName;
		if(!CFileManage::FolderExist(destName))
			CreateDirectory(destName, NULL);
		
		destName = destName + L"\\" + fileName;
		 //*/

		if(!CFileManage::DownloadFtp(/*L"localhost"*/ m_strFtp, sourceName, destName))
		{
			CString error;
			error.Format(L"ʧ�ܣ�\nsrcName:%s\ndestName:%s",sourceName, destName);
			AfxMessageBox(error);
		}
	}
}

bool CBookDlg::SynchronizeDB()
{
	if(!CFileManage::m_bIsFtpConnected || !m_db.m_bIsOpen)
		return FALSE;

	CString sql;
	sql = L"select * from item where item_type=\"b\" order by item_uploadtime desc";
	m_iItemNum = m_db.Select(sql, m_strPath);
	//����·�����

	//��FTP����ͼƬ��������ʱ�ļ���
	Download(m_iPageIndex*6, 6, L"preview.jpg");

	m_iPageIndex = m_iLastDownloadPage = 0;
	OnPaint();
	//OnVScroll(SB_TOP, m_verScroll.GetScrollPos(), &m_verScroll);
	return true;
}

void CBookDlg::OnBnClickedBookGroup1Enter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[0]), m_strPath[m_iPageIndex*6]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}


void CBookDlg::OnBnClickedBookGroup2Enter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[1]), m_strPath[m_iPageIndex*6+1]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}


void CBookDlg::OnBnClickedBookGroup3Enter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[2]), m_strPath[m_iPageIndex*6+2]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}


void CBookDlg::OnBnClickedBookGroup4Enter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[3]), m_strPath[m_iPageIndex*6+3]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}


void CBookDlg::OnBnClickedBookGroup5Enter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[4]), m_strPath[m_iPageIndex*6+4]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}


void CBookDlg::OnBnClickedBookGroup6Enter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[5]), m_strPath[m_iPageIndex*6+5]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}


void CBookDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if(bShow)
		SynchronizeDB();

	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
}
