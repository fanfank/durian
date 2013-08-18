
// DurianDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Durian.h"
#include "DurianDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "LoginDlg.h"
#include "CreateItemDlg.h"
#include "FileManage.h"
#include "RegisterDlg.h"
#include "AccountFriendDlg.h"
#include "AccountManageDlg.h"
#include "AuthorInfoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define m_db CDurianApp::m_db
#define m_pRecordSet CDurianApp::m_pRecordSet
#define m_strWorkingDir CDurianApp::m_strWorkingDir
#define m_strDB CDurianApp::m_strDB
#define m_strFtp CDurianApp::m_strFtp
#define m_user CDurianApp::m_user
#define m_ftpRootDir CDurianApp::m_ftpRootDir
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDurianDlg �Ի���



CDurianDlg::CDurianDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDurianDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDurianDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_TAB, m_tabCtrl);
	DDX_Control(pDX, IDC_TABS, m_sheet);
	DDX_Control(pDX, IDC_LOGIN, m_btLogin);
	DDX_Control(pDX, IDC_REGISTER, m_btRegister);
	DDX_Control(pDX, IDC_MAIN_REFRESH, m_btRefresh);
	DDX_Control(pDX, IDC_FRIEND_MANAGE, m_btFriends);
	DDX_Control(pDX, IDC_CREATE_ITEM, m_btCreateItem);
	DDX_Control(pDX, IDC_ACCOUNT_MANAGE, m_btAccountManage);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_PROMPT, m_stPrompt);
	DDX_Control(pDX, IDC_MIN, m_btMin);
	DDX_Control(pDX, IDC_CLOSE, m_btClose);
	DDX_Control(pDX, IDC_TITLE, m_stTitle);
	DDX_Control(pDX, IDC_EDIT_INFO, m_btInfo);
}

void CDurianDlg::enableButtons(bool enable)
{
	CString prompt;
	if(enable)
	{
		m_btLogin.SetWindowText(L"| �ǳ� |");
		m_btRegister.SetWindowText(L"");
		m_btRegister.EnableWindow(false);
		m_btFriends.SetWindowText(L"| �ҵĺ��� |");
		m_btFriends.EnableWindow(true);
		m_btCreateItem.SetWindowText(L"| ������Ŀ |");
		m_btCreateItem.EnableWindow(true);
		if(m_user.m_iUserType == USER_ADMIN)
		{
			m_btAccountManage.SetWindowText(L"| �˺Ź��� |");
			m_btAccountManage.EnableWindow(true);
			prompt.Format(L"�𾴵Ĺ���Ա��%s   ��ӭ����!", m_user.m_sUserName);
			m_stPrompt.SetWindowText(prompt);
		}
		else
		{
			prompt.Format(L"�װ����û���%s   ��ӭ����!", m_user.m_sUserName);
			m_stPrompt.SetWindowText(prompt);
		}
		
		m_btInfo.ShowWindow(true);
	}
	else
	{
		m_btLogin.SetWindowText(L"| ��¼ |");
		m_btRegister.SetWindowText(L"| ע�� |");
		m_btRegister.EnableWindow(true);
		m_btFriends.SetWindowText(L"");
		m_btFriends.EnableWindow(false);
		m_btCreateItem.SetWindowText(L"");
		m_btCreateItem.EnableWindow(false);
		m_btAccountManage.SetWindowText(L"");
		m_btAccountManage.EnableWindow(false);
		m_stPrompt.SetWindowText(L">> �οͣ����ã���¼������������ྫ�ʣ� <<");
		m_btInfo.ShowWindow(false);
	}
}

BEGIN_MESSAGE_MAP(CDurianDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOGIN, &CDurianDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_CREATE_ITEM, &CDurianDlg::OnBnClickedCreateItem)
	ON_BN_CLICKED(IDC_REGISTER, &CDurianDlg::OnBnClickedRegister)
	ON_BN_CLICKED(IDC_FRIEND_MANAGE, &CDurianDlg::OnBnClickedFriendManage)
	ON_BN_CLICKED(IDC_ACCOUNT_MANAGE, &CDurianDlg::OnBnClickedAccountManage)
	ON_BN_CLICKED(IDC_MAIN_REFRESH, &CDurianDlg::OnBnClickedMainRefresh)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CLOSE, &CDurianDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_MIN, &CDurianDlg::OnBnClickedMin)
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDOK, &CDurianDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_EDIT_INFO, &CDurianDlg::OnBnClickedEditInfo)
	ON_BN_CLICKED(IDC_RATE, &CDurianDlg::OnBnClickedRate)
	ON_STN_CLICKED(IDC_TITLE, &CDurianDlg::OnStnClickedTitle)
	ON_STN_CLICKED(IDC_AUTHORINFO, &CDurianDlg::OnStnClickedAuthorinfo)
END_MESSAGE_MAP()


// CDurianDlg ��Ϣ�������

BOOL CDurianDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_sheet.AddPage(L"��ҳ", &m_pageMain, IDD_MAIN);
	m_sheet.AddPage(L"��Ӱ", &m_pageMovie, IDD_MOVIE);
	m_sheet.AddPage(L"�鼮", &m_pageBook, IDD_BOOK);
	m_sheet.AddPage(L"ʱ��", &m_pageAffair, IDD_AFFAIR);
	m_sheet.Show();

	m_btCancel.m_clrButtonColNormal = m_btLogin.m_clrButtonColNormal = m_btRegister.m_clrButtonColNormal = m_btRefresh.m_clrButtonColNormal = DURIAN_COLOR_GREEN;
	m_btCancel.m_clrButtonColHoverd = m_btLogin.m_clrButtonColHoverd = m_btRegister.m_clrButtonColHoverd = m_btRefresh.m_clrButtonColHoverd = DURIAN_COLOR_ORANGE;
	m_btCancel.m_clrButtonColDisabled = m_btLogin.m_clrButtonColDisabled = m_btRegister.m_clrButtonColDisabled = m_btRefresh.m_clrButtonColDisabled = DURIAN_COLOR_GREEN;

	m_btFriends.m_clrButtonColNormal = m_btAccountManage.m_clrButtonColNormal = m_btCreateItem.m_clrButtonColNormal = DURIAN_COLOR_GREEN;
	m_btFriends.m_clrButtonColHoverd = m_btAccountManage.m_clrButtonColHoverd = m_btCreateItem.m_clrButtonColHoverd = DURIAN_COLOR_ORANGE;
	m_btFriends.m_clrButtonColDisabled = m_btAccountManage.m_clrButtonColDisabled = m_btCreateItem.m_clrButtonColDisabled = DURIAN_COLOR_GREEN;

	m_btInfo.m_clrButtonColNormal = m_btMin.m_clrButtonColNormal = m_btClose.m_clrButtonColNormal = DURIAN_COLOR_GREEN;
	m_btInfo.m_clrButtonColHoverd = m_btMin.m_clrButtonColHoverd = m_btClose.m_clrButtonColHoverd = DURIAN_COLOR_ORANGE;

	enableButtons(false);

	m_fontTitle.CreatePointFont(180, L"΢���ź�");
	m_stTitle.SetFont(&m_fontTitle);

	if(!CFileManage::m_bIsFtpConnected)
		AfxMessageBox(L"�޷����ӵ�Ftp\n��Ŀ�޷����أ���Ǹ��");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDurianDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDurianDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);

		
	}
	else
	{
		CDialogEx::OnPaint();
	}
	CRect crect;
	GetWindowRect(&crect);
	ScreenToClient(&crect);
	CDC *pDC = GetDC();
	CPen pen = CPen(PS_SOLID, 1, DURIAN_COLOR_GREEN);
	pDC->SelectObject(&pen);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(&crect);

	//pDC->FillSolidRect(crect.left, crect.top, crect.right, 40, DURIAN_COLOR_GREEN);
	
	ReleaseDC(pDC);

	m_stPrompt.RedrawWindow();
	m_btClose.RedrawWindow();
	m_btMin.RedrawWindow();
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDurianDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDurianDlg::OnBnClickedLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString loginState;
	GetDlgItemText(IDC_LOGIN, loginState);
	if(loginState == L"| ��¼ |")
	{ 
		CLoginDlg loginDlg;
		if(loginDlg.DoModal() == IDOK)
		{
			/*
				SetDlgItemText(IDC_LOGIN, L"�ǳ�");
				SetDlgItemText(IDC_IDENTITY, loginDlg.Get_username());

				GetDlgItem(IDC_REGISTER)->EnableWindow(FALSE);


				GetDlgItem(IDC_CREATE_ITEM)->EnableWindow(TRUE);
				GetDlgItem(IDC_FRIEND_MANAGE)->EnableWindow(TRUE);
				GetDlgItem(IDC_CREATE_ITEM)->ShowWindow(TRUE);
				GetDlgItem(IDC_FRIEND_MANAGE)->ShowWindow(TRUE);
			*/
				m_user.InitUser(&loginDlg);
				enableButtons(true);
				if(m_user.m_iUserType == USER_ADMIN)
				{
					GetDlgItem(IDC_ACCOUNT_MANAGE)->EnableWindow(TRUE);
					GetDlgItem(IDC_ACCOUNT_MANAGE)->ShowWindow(TRUE);
				}

		}

	}
	else
	{
		//m_user.doLogout();
		/*
		SetDlgItemText(IDC_LOGIN, L"��¼");
		SetDlgItemText(IDC_IDENTITY, L"�ο�");
		GetDlgItem(IDC_REGISTER)->EnableWindow(TRUE);

		GetDlgItem(IDC_CREATE_ITEM)->EnableWindow(FALSE);
		GetDlgItem(IDC_FRIEND_MANAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CREATE_ITEM)->ShowWindow(FALSE);
		GetDlgItem(IDC_FRIEND_MANAGE)->ShowWindow(FALSE);
		GetDlgItem(IDC_ACCOUNT_MANAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_ACCOUNT_MANAGE)->ShowWindow(FALSE);
		*/
		enableButtons(false);
		m_user.m_iUserType = USER_CUSTOMER;
	}
}


void CDurianDlg::OnBnClickedCreateItem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CCreateItemDlg itemDlg;
	if(itemDlg.DoModal() == IDOK)
	{
		CString sql;
		sql.Format(L"select item_name from item where item_name=\"%s\" and item_type=\"%c\"", itemDlg.m_strName, itemDlg.m_strType[0]);

		//AfxMessageBox(sql);

		m_pRecordSet = m_db.Select(sql);
		if(!m_pRecordSet->adoBOF)
		{
			AfxMessageBox(L"�Ѿ����ڸ���Ŀ��~��");
			return;
		}

		itemDlg.m_strAbstract.Replace(L"\\",L"\\\\");
		itemDlg.m_strAbstract.Replace(L"\"",L"\\\"");
		itemDlg.m_strName.Replace(L"\\",L"\\\\");
		itemDlg.m_strName.Replace(L"\"",L"\\\"");
		itemDlg.m_strContent.Replace(L"\\",L"\\\\");
		itemDlg.m_strContent.Replace(L"\"",L"\\\"");


		sql.Format(L"insert into item values(null, \"%s\", \"%s\", 0, 0, \"%c\", %s, \"%s\")", 
			itemDlg.m_strName, itemDlg.m_strAbstract, itemDlg.m_strType[0], CFileManage::GetSystemTime(0), itemDlg.m_strContent);  

		//�޸�ͼƬ��ʽ
		CImage img;
		img.Attach(itemDlg.GetHBITMAP());

		CString coverPath = itemDlg.m_strCoverPath;
		for(int i = coverPath.GetLength()-1; coverPath[i]!='\\'; --i)
		{	coverPath.Delete(i);
		//AfxMessageBox(coverPath);
		}
		coverPath.Append(L"preview.jpg");
		img.Save(coverPath);

		//�ϴ�FTPͼƬ
		if(CFileManage::UploadFtp(/*L"localhost"*/ m_strFtp, 
			coverPath, m_ftpRootDir + itemDlg.m_strType + L"/" + itemDlg.m_strName + L"/" + L"preview.jpg"))
		{
			//�������ݿ�
			if(m_db.Insert(sql)<=0)
				AfxMessageBox(L"�������ݿ�ʧ�ܣ�");
			else
			{	
				AfxMessageBox(L"��ϲ���ϴ��ɹ���", MB_ICONINFORMATION); 
				if(itemDlg.m_strType == L"movie")
					m_pageMovie.SynchronizeDB();
				else if(itemDlg.m_strType == L"book")
					m_pageBook.SynchronizeDB();
				else
					m_pageAffair.SynchronizeDB();
				
				m_pageMain.SynchronizeDB();
			}
		}
		else
			AfxMessageBox(L"�ϴ�ͼƬʧ�ܣ�");
		
		img.Detach();
		DeleteFile(coverPath);
	}
}


void CDurianDlg::OnBnClickedRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegisterDlg registerDlg;
	registerDlg.DoModal();
}


void CDurianDlg::OnBnClickedFriendManage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAccountFriendDlg friendDlg;
	friendDlg.m_iUserID = m_user.GetUserId();
	friendDlg.DoModal();
}


void CDurianDlg::OnBnClickedAccountManage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAccountManageDlg accountDlg;
	accountDlg.DoModal();
}


void CDurianDlg::OnBnClickedMainRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	if(m_pageMain.SynchronizeDB())
		if()
			if()
				if()
				*/
	m_pageMain.SynchronizeDB();
	m_pageBook.SynchronizeDB();
	m_pageMovie.SynchronizeDB();
	m_pageAffair.SynchronizeDB();
}


HBRUSH CDurianDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	UINT ctrlID = pWnd->GetDlgCtrlID();
	if(ctrlID == IDC_PROMPT || ctrlID == IDC_TITLE)
	{
		//pDC->SetBkColor(DURIAN_COLOR_GREEN);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(DURIAN_COLOR_GREEN);
		//return (HBRUSH) ::CreateSolidBrush(DURIAN_COLOR_GREEN);
		//return (HBRUSH) ::GetStockObject(NULL_BRUSH);
	}

	return hbr;
}


void CDurianDlg::OnBnClickedClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->SendMessage(WM_CLOSE);
}


void CDurianDlg::OnBnClickedMin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_MINIMIZE);
	
}


LRESULT CDurianDlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = rect.top + 40;
	ClientToScreen(&rect);

	return rect.PtInRect(point)? HTCAPTION : CDialog::OnNcHitTest(point);
	//return CDialogEx::OnNcHitTest(point);
}


void CDurianDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxMessageBox(L"msg received");

	CDialogEx::OnOK();
}


void CDurianDlg::OnBnClickedEditInfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegisterDlg registerdlg;
	registerdlg.isEditInfo = 1;
	registerdlg.m_iUserID = m_user.GetUserId();
	registerdlg.DoModal();
}


void CDurianDlg::OnBnClickedRate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedMainRefresh();
}


void CDurianDlg::OnStnClickedTitle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDurianDlg::OnStnClickedAuthorinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAuthorInfoDlg infoDlg;
	infoDlg.DoModal();
}
