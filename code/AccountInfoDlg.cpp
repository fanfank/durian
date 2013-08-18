// AccountInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "ADO.h"
#include "AccountInfoDlg.h"
#include "afxdialogex.h"
#include "DurianButton.h"
#include "Durian.h"

#define m_db CDurianApp::m_db

// CAccountInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CAccountInfoDlg, CDialogEx)

CAccountInfoDlg::CAccountInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAccountInfoDlg::IDD, pParent)
	, m_edUID(_T(""))
	, m_edUsername(_T(""))
	, m_edEmail(_T(""))
	, m_edName(_T(""))
	, m_edQQ(_T(""))
	, m_edGender(_T(""))
	, m_edBirthdate(_T(""))
	, m_edSelfintro(_T(""))
	, m_edRegisterdate(_T(""))
	, m_edBlock(_T(""))
{
	m_bAdmin = false;
	m_addFriend = false;
	m_addNow = false;
//	m_db.Open();
}

CAccountInfoDlg::~CAccountInfoDlg()
{
}

void CAccountInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACCOUNT_INFO_ST_UID, m_stUID);
	DDX_Control(pDX, IDC_ACCOUNT_INFO_ST_USERNAME, m_stUsername);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDC_ACCOUNT_INFO_ST_TITLE, m_stTitle);
	DDX_Text(pDX, IDC_ACCOUNT_INFO_UID, m_edUID);
	DDX_Text(pDX, IDC_ACCOUNT_INFO_USERNAME, m_edUsername);
	DDX_Text(pDX, IDC_ACCOUNT_INFO_EMAIL, m_edEmail);
	DDX_Text(pDX, IDC_ACCOUNT_INFO_NAME, m_edName);
	DDX_Text(pDX, IDC_ACCOUNT_INFO_QQ, m_edQQ);
	DDX_Text(pDX, IDC_ACCOUNT_INFO_GENDER, m_edGender);
	DDX_Text(pDX, IDC_ACCOUNT_INFO_BIRTHDATE, m_edBirthdate);
	DDX_Text(pDX, IDC_ACCOUNT_INFO_SELFINTRO, m_edSelfintro);
	DDX_Text(pDX, IDC_ACCOUNT_INFO_REGISTERTIME, m_edRegisterdate);
	DDX_Text(pDX, IDC_ACCOUNT_INFO_BLOCK, m_edBlock);
	DDX_Control(pDX, IDC_ACCOUNT_INFO_ST_ADMIN, m_stAdmin);
	DDX_Control(pDX, IDCANCLE_THIS, m_btClose);
}


BEGIN_MESSAGE_MAP(CAccountInfoDlg, CDialogEx)

	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDOK, &CAccountInfoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCLE_THIS, &CAccountInfoDlg::OnBnClickedThis)
END_MESSAGE_MAP()


// CAccountInfoDlg ��Ϣ�������



HBRUSH CAccountInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	UINT ctrlID = pWnd->GetDlgCtrlID();

	if(ctrlID <= IDC_ACCOUNT_INFO_ST_BLOCK && ctrlID >= IDC_ACCOUNT_INFO_ST_UID)
	{
		pDC->SetTextColor(DURIAN_COLOR_RED);
	}
	if(ctrlID == IDC_ACCOUNT_INFO_ST_TITLE)
	{
		pDC->SetTextColor(DURIAN_COLOR_WHITE);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH) ::GetStockObject(NULL_BRUSH);
	}

	/*
	else if(ctrlID <= IDC_ACCOUNT_INFO_BLOCK && ctrlID >= IDC_ACCOUNT_INFO_UID)
	{
		//pDC->SetTextColor(DURIAN_COLOR_RED);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH) ::CreateSolidBrush(DURIAN_COLOR_WHITE);
	}*/
	
	return hbr;
}


void CAccountInfoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);

	CDC *pDC = GetDC();
	pDC->SelectStockObject(DC_PEN);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SetDCPenColor(DURIAN_COLOR_RED);
	pDC->Rectangle(&rect);

	pDC->FillSolidRect(rect.left, rect.bottom - 30, rect.Width(), 30, DURIAN_COLOR_RED);
	pDC->FillSolidRect(rect.left, rect.top, rect.Width(), 60, DURIAN_COLOR_RED);

	
	CWnd *pWnd;
	/*
	for(int i = IDC_ACCOUNT_INFO_UID; i <= IDC_ACCOUNT_INFO_BLOCK; i++)
	{
		pWnd = GetDlgItem(i);
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.top-=3;
		rect.left-=3;
		rect.bottom++;
		rect.right++;
		pDC->Rectangle(&rect);
	}*/
	/*
	pWnd = GetDlgItem(IDC_ACCOUNT_INFO_EMAIL);
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.top-=3;
	rect.left-=3;
	rect.bottom++;
	rect.right++;
	pDC->Rectangle(&rect);
	*/
	pWnd = GetDlgItem(IDC_ACCOUNT_INFO_SELFINTRO);
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.top-=3;
	rect.left-=3;
	rect.bottom++;
	rect.right++;
	pDC->Rectangle(&rect);
	
	ReleaseDC(pDC);
}


BOOL CAccountInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_fontTitle.CreatePointFont(220, L"΢���ź�");
	m_stTitle.SetFont(&m_fontTitle);
	m_stTitle.SetWindowText(L"�˺���Ϣ");

	m_btClose.m_clrButtonColNormal = m_btOK.m_clrButtonColNormal = DURIAN_COLOR_RED;
	m_btClose.m_clrButtonColHoverd = m_btOK.m_clrButtonColHoverd = DURIAN_COLOR_ORANGE;
	if(m_addFriend) {
		GetDlgItem(IDOK)->SetWindowText(L"��Ӻ���");
		GetDlgItem(IDCANCLE_THIS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDCANCLE_THIS)->EnableWindow(TRUE);
	}
	else {
		GetDlgItem(IDOK)->SetWindowText(L"ȷ��");
		GetDlgItem(IDCANCLE_THIS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDCANCLE_THIS)->EnableWindow(FALSE);
	}
	return TRUE;
}


LRESULT CAccountInfoDlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CRect rect;
	GetClientRect(&rect);
	rect.bottom = rect.top + 60;
	ClientToScreen(&rect);

	return rect.PtInRect(point)? HTCAPTION : CDialogEx::OnNcHitTest(point);
}



void CAccountInfoDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_addFriend) {
		CString	sql;
		vector<vector<_variant_t> > vFriendExist;
		sql.Format(L"select * from friends where friend_id = %s and user_id = %d", m_edUID, m_iUserID);
		m_db.Select(sql, vFriendExist);
		if(vFriendExist.size() == 0){
			sql = "";
			sql.Format(L"insert into friends values(%d,%s,0)", m_iUserID, m_edUID);
			m_db.Insert(sql);
			MessageBox(L"��Ӻ��ѳɹ�");
		}
		else {
			MessageBox(L"�ú����ѱ����");
		}
	}
	else m_addNow = false;
	CDialogEx::OnOK();
}

void CAccountInfoDlg::OnBnClickedThis()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	this->SendMessage(WM_CLOSE);
}
