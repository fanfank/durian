// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "ADO.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "Durian.h"

#define m_db CDurianApp::m_db
#define m_pRecordSet CDurianApp::m_pRecordSet
// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{
	
}

CLoginDlg::~CLoginDlg()
{
	/*
	if(m_pRecordSet != NULL)
	{
		m_pRecordSet->Close();
		m_pRecordSet = NULL;
	}
	m_db.Close();
	*/
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_LOGIN_TITLE, m_stTitle);
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_clrBorder = DURIAN_COLOR_GREEN;
	m_btOK.m_clrButtonColNormal = m_btCancel.m_clrButtonColNormal = DURIAN_COLOR_GREEN;
	m_btOK.m_clrButtonColHoverd = m_btCancel.m_clrButtonColHoverd = DURIAN_COLOR_ORANGE;

	m_fontTitle.CreatePointFont(130, L"΢���ź�");
	m_stTitle.SetFont(&m_fontTitle);

	//m_bDBOpen = false;
	return false;
	//return 
}


bool CLoginDlg::setInfo()
{
	if(m_pRecordSet == NULL)
		return false;
	else
	{
		m_id = (int)m_pRecordSet->GetCollect("user_id");
		m_username = _VariantToCString(m_pRecordSet->GetCollect("user_name"));
		m_password = _VariantToCString(m_pRecordSet->GetCollect("user_password"));
		m_email = _VariantToCString(m_pRecordSet->GetCollect("email"));
		m_name = _VariantToCString(m_pRecordSet->GetCollect("name"));
		m_qq = _VariantToCString(m_pRecordSet->GetCollect("qq"));
		m_gender = _VariantToCString(m_pRecordSet->GetCollect("gender"));
		m_birthdate = _VariantToCString(m_pRecordSet->GetCollect("birthdate"));
		m_selfintro = _VariantToCString(m_pRecordSet->GetCollect("selfintro"));
		m_registerdate = _VariantToCString(m_pRecordSet->GetCollect("registerdate"));
	    isadmin = (bool)m_pRecordSet->GetCollect("isadmin");
		isblocked = (bool)m_pRecordSet->GetCollect("isblocked");
		return true;
	}
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)

	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������


void CLoginDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(!m_db.m_bIsOpen)
	{	AfxMessageBox(L"δ���ӵ����ݿ�\n�޷�ʹ�õ�¼���ܣ�");
		return;
	}

	CString username, password;
	GetDlgItemText(IDC_LOGIN_USERNAME, username);
	GetDlgItemText(IDC_LOGIN_PASSWD, password);
	if(username == "")
	{
		AfxMessageBox(L"�������û���");
		(CWnd*)GetDlgItem(IDC_LOGIN_USERNAME) ->SetFocus();
	}
	else if(password == "")
	{
		AfxMessageBox(L"����������");
		(CWnd*)GetDlgItem(IDC_LOGIN_PASSWD) ->SetFocus();
	}
	else
	{
		/*
		if(!m_bDBOpen)
		{
			m_db.Open();
			m_bDBOpen = false;
		}
		*/
		CString sql;
		//sql.Format(L"select * from user where user_name=\"%s\" and user_password=\"%s\"", username, password);
		sql.Format(L"select * from user where user_name = \"%s\"", username);
		m_pRecordSet = m_db.Select(sql);
		
		if(m_pRecordSet->adoBOF)
			AfxMessageBox(L"�û���������");
		else if((int)m_pRecordSet->GetCollect("isblocked") == 1)
			AfxMessageBox(L"�����˺��ѱ�����");
		else if(_VariantToCString(m_pRecordSet->GetCollect("user_password")) != password)
			AfxMessageBox(L"���벻��ȷ");
		else
		{
			setInfo();
			return CDialog::OnOK();
		}
	}
}

/*
CString CLoginDlg::makeInfostr()
{
	CString r;
	r.Format(L"ID: %d\nUSER: %s\tPASSWD: %s\nEMAIL: %s\tNAME: %s\tQQ: %s\nGENDER: %s\tBIRTHDATE: %s\nINTRO: %s\nREGDATE: %s\t%d\t%d", 
		m_id, m_username, m_password, m_email, m_name, m_qq, m_gender, m_birthdate, m_selfintro, m_registerdate, isadmin, isblocked);
	return r;
}
*/


void CLoginDlg::OnPaint()
{
	CPaintDC dc(this);

	CDC *pDC = GetDC();
	pDC->SelectStockObject(DC_PEN);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SetDCPenColor(m_clrBorder);

	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);

	pDC->Rectangle(rect);
	pDC->FillSolidRect(rect.left, rect.top, rect.Width(), 40, m_clrBorder);

	ReleaseDC(pDC);
}


HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetDlgCtrlID() == IDC_LOGIN_TITLE)
	{
		pDC->SetTextColor(DURIAN_COLOR_WHITE);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH) ::GetStockObject(NULL_BRUSH);
	}
	return hbr;
}
