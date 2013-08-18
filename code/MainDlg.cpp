// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Durian.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "ControllerEdit.h"
#include "DatabaseADO.h"
#include "FileManage.h"
#include "ItemDetailDlg.h"

#define m_db CDurianApp::m_db
#define m_pRecordSet CDurianApp::m_pRecordSet
#define m_strWorkingDir CDurianApp::m_strWorkingDir
#define m_strDB CDurianApp::m_strDB
#define m_strFtp CDurianApp::m_strFtp
#define m_user CDurianApp::m_user
// CMainDlg �Ի���

IMPLEMENT_DYNAMIC(CMainDlg, CDialog)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
	m_iItemNum = 0;
	m_strItemType[0]=L"movie";
	m_strItemType[1]=L"book";
	m_strItemType[2]=L"affair";
}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_GROUP_MOVIE_ENTER, m_btnMainGpMovieEnt);
	DDX_Control(pDX, IDC_MAIN_GROUP_BOOK_ENTER, m_btnMainGpBookEnt);
	DDX_Control(pDX, IDC_MAIN_GROUP_AFFAIR_ENTER, m_btnMainGpAffairEnt);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MAIN_GROUP_MOVIE_ENTER, &CMainDlg::OnBnClickedMainGroupMovieEnter)
	ON_BN_CLICKED(IDC_MAIN_GROUP_BOOK_ENTER, &CMainDlg::OnBnClickedMainGroupBookEnter)
	ON_BN_CLICKED(IDC_MAIN_GROUP_AFFAIR_ENTER, &CMainDlg::OnBnClickedMainGroupAffairEnter)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CMainDlg ��Ϣ�������


BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SynchronizeDB();
	return TRUE;
}

void CMainDlg::Download(int startIndex, int downloadNum, LPCTSTR fileName)
{
	if(!CFileManage::m_bIsFtpConnected)
		return;

	for(int i = 0; i<downloadNum && (startIndex+i)<m_iItemNum; i++)
	{
		CString sourceName = CDurianApp::m_ftpRootDir + m_strItemType[i] + L"/" + _VariantToCString(m_strPath[startIndex+i][1]) + L"/" + fileName;

		CString destName = m_strWorkingDir + L"tmp\\item\\" + m_strItemType[i] + L"\\" + _VariantToCString(m_strPath[startIndex+i][1]);
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

bool CMainDlg::SynchronizeDB()
{
	if(!CFileManage::m_bIsFtpConnected || !m_db.m_bIsOpen)
		return FALSE;

	CString sql = L"select * from item as A ";
	CString condition = L"where A.item_id>=all(select item_id from item where item_type=A.item_type) ";
	sql = sql+condition+L"order by item_type desc";
	m_iItemNum = m_db.Select(sql, m_strPath);

	//����·�����

	//��FTP����ͼƬ��������ʱ�ļ���
	Download(0, 3, L"preview.jpg");
	OnPaint();
	return true;
}


void CMainDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CString prescript = L"tmp\\item\\";//movie\\";  //Ҫ��������ʱ��Ϣ����ʱ�ļ���
	CString picpath;
	CString basicInfo[3][2]={ {L"���µ�Ӱ��",L"��Ŀ�»�û�е�Ӱ"},
							  {L"�����鼮��",L"��Ŀ�»�û���鼮"},
							  {L"����ʱ�£�",L"��Ŀ�»�û��ʱ��"}
							};
	int i;
	for(i=0;i<m_iItemNum;++i) //����ͼƬ��ӰƬ˵��
	{
		GetDlgItem(IDC_MAIN_GROUP_MOVIE_EDIT+i)->ShowWindow(TRUE);

		GetDlgItem(IDC_MAIN_GROUP_MOVIE_PIC+i)->ShowWindow(TRUE);

		GetDlgItem(IDC_MAIN_GROUP_MOVIE_ENTER+i)->ShowWindow(TRUE);
		GetDlgItem(IDC_MAIN_GROUP_MOVIE_ENTER+i)->EnableWindow(TRUE);

		SetDlgItemText(IDC_MAIN_GROUP_MOVIE+i,basicInfo[i][0]+_VariantToCString(m_strPath[i][1]));
		SetDlgItemText(IDC_MAIN_GROUP_MOVIE_EDIT+i,L"���ݼ�飺"+_VariantToCString(m_strPath[i][2]));
		SetDlgItemText(IDC_MAIN_GROUP_MOVIE_DETAIL+i,L"��ϸ���ݣ�"+_VariantToCString(m_strPath[i][7]));

		CString tmpPrescript;
		tmpPrescript = prescript + m_strItemType[i] + L"\\";
		picpath = tmpPrescript + _VariantToCString(m_strPath[i][1]) + L"\\preview.jpg";
		//AfxMessageBox(picpath);

		m_imgPreview[i].Load(picpath);
		if(!m_imgPreview[i].IsNull())
			CControllerEdit::ShowPicture(this, IDC_MAIN_GROUP_MOVIE_PIC+i, (HBITMAP)m_imgPreview[i]);
	}
	for(;i<3;i++)
	{
		GetDlgItem(IDC_MAIN_GROUP_MOVIE_EDIT+i)->ShowWindow(FALSE);

		GetDlgItem(IDC_MAIN_GROUP_MOVIE_PIC+i)->ShowWindow(FALSE);

		GetDlgItem(IDC_MAIN_GROUP_MOVIE_ENTER+i)->ShowWindow(FALSE);
		GetDlgItem(IDC_MAIN_GROUP_MOVIE_ENTER+i)->EnableWindow(FALSE);
		SetDlgItemText(IDC_MAIN_GROUP_MOVIE+i,basicInfo[i][1]);
		//SetDlgItemText(IDC_MOVIE_GROUP1_EDIT+i,L"û�е�Ӱ");
	}
}


void CMainDlg::OnBnClickedMainGroupMovieEnter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[0]), m_strPath[0]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}


void CMainDlg::OnBnClickedMainGroupBookEnter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[1]), m_strPath[1]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}


void CMainDlg::OnBnClickedMainGroupAffairEnter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CItemDetailDlg itemDtDlg(m_user.m_iUserType == 0, HBITMAP(m_imgPreview[2]), m_strPath[2]);
	if(itemDtDlg.DoModal() == IDOK)
		SynchronizeDB();
}


void CMainDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if(bShow)
		SynchronizeDB();

	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
}
