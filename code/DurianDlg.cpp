
// DurianDlg.cpp : 实现文件
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
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDurianDlg 对话框



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
		m_btLogin.SetWindowText(L"| 登出 |");
		m_btRegister.SetWindowText(L"");
		m_btRegister.EnableWindow(false);
		m_btFriends.SetWindowText(L"| 我的好友 |");
		m_btFriends.EnableWindow(true);
		m_btCreateItem.SetWindowText(L"| 贡献条目 |");
		m_btCreateItem.EnableWindow(true);
		if(m_user.m_iUserType == USER_ADMIN)
		{
			m_btAccountManage.SetWindowText(L"| 账号管理 |");
			m_btAccountManage.EnableWindow(true);
			prompt.Format(L"尊敬的管理员：%s   欢迎回来!", m_user.m_sUserName);
			m_stPrompt.SetWindowText(prompt);
		}
		else
		{
			prompt.Format(L"亲爱的用户：%s   欢迎回来!", m_user.m_sUserName);
			m_stPrompt.SetWindowText(prompt);
		}
		
		m_btInfo.ShowWindow(true);
	}
	else
	{
		m_btLogin.SetWindowText(L"| 登录 |");
		m_btRegister.SetWindowText(L"| 注册 |");
		m_btRegister.EnableWindow(true);
		m_btFriends.SetWindowText(L"");
		m_btFriends.EnableWindow(false);
		m_btCreateItem.SetWindowText(L"");
		m_btCreateItem.EnableWindow(false);
		m_btAccountManage.SetWindowText(L"");
		m_btAccountManage.EnableWindow(false);
		m_stPrompt.SetWindowText(L">> 游客，您好！登录榴莲，体验更多精彩！ <<");
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


// CDurianDlg 消息处理程序

BOOL CDurianDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_sheet.AddPage(L"首页", &m_pageMain, IDD_MAIN);
	m_sheet.AddPage(L"电影", &m_pageMovie, IDD_MOVIE);
	m_sheet.AddPage(L"书籍", &m_pageBook, IDD_BOOK);
	m_sheet.AddPage(L"时事", &m_pageAffair, IDD_AFFAIR);
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

	m_fontTitle.CreatePointFont(180, L"微软雅黑");
	m_stTitle.SetFont(&m_fontTitle);

	if(!CFileManage::m_bIsFtpConnected)
		AfxMessageBox(L"无法连接到Ftp\n条目无法下载，抱歉！");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDurianDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDurianDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDurianDlg::OnBnClickedLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	CString loginState;
	GetDlgItemText(IDC_LOGIN, loginState);
	if(loginState == L"| 登录 |")
	{ 
		CLoginDlg loginDlg;
		if(loginDlg.DoModal() == IDOK)
		{
			/*
				SetDlgItemText(IDC_LOGIN, L"登出");
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
		SetDlgItemText(IDC_LOGIN, L"登录");
		SetDlgItemText(IDC_IDENTITY, L"游客");
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
	// TODO: 在此添加控件通知处理程序代码
	CCreateItemDlg itemDlg;
	if(itemDlg.DoModal() == IDOK)
	{
		CString sql;
		sql.Format(L"select item_name from item where item_name=\"%s\" and item_type=\"%c\"", itemDlg.m_strName, itemDlg.m_strType[0]);

		//AfxMessageBox(sql);

		m_pRecordSet = m_db.Select(sql);
		if(!m_pRecordSet->adoBOF)
		{
			AfxMessageBox(L"已经存在该条目啦~！");
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

		//修改图片格式
		CImage img;
		img.Attach(itemDlg.GetHBITMAP());

		CString coverPath = itemDlg.m_strCoverPath;
		for(int i = coverPath.GetLength()-1; coverPath[i]!='\\'; --i)
		{	coverPath.Delete(i);
		//AfxMessageBox(coverPath);
		}
		coverPath.Append(L"preview.jpg");
		img.Save(coverPath);

		//上传FTP图片
		if(CFileManage::UploadFtp(/*L"localhost"*/ m_strFtp, 
			coverPath, m_ftpRootDir + itemDlg.m_strType + L"/" + itemDlg.m_strName + L"/" + L"preview.jpg"))
		{
			//操作数据库
			if(m_db.Insert(sql)<=0)
				AfxMessageBox(L"更新数据库失败！");
			else
			{	
				AfxMessageBox(L"恭喜，上传成功！", MB_ICONINFORMATION); 
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
			AfxMessageBox(L"上传图片失败！");
		
		img.Detach();
		DeleteFile(coverPath);
	}
}


void CDurianDlg::OnBnClickedRegister()
{
	// TODO: 在此添加控件通知处理程序代码
	CRegisterDlg registerDlg;
	registerDlg.DoModal();
}


void CDurianDlg::OnBnClickedFriendManage()
{
	// TODO: 在此添加控件通知处理程序代码
	CAccountFriendDlg friendDlg;
	friendDlg.m_iUserID = m_user.GetUserId();
	friendDlg.DoModal();
}


void CDurianDlg::OnBnClickedAccountManage()
{
	// TODO: 在此添加控件通知处理程序代码
	CAccountManageDlg accountDlg;
	accountDlg.DoModal();
}


void CDurianDlg::OnBnClickedMainRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	this->SendMessage(WM_CLOSE);
}


void CDurianDlg::OnBnClickedMin()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_MINIMIZE);
	
}


LRESULT CDurianDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = rect.top + 40;
	ClientToScreen(&rect);

	return rect.PtInRect(point)? HTCAPTION : CDialog::OnNcHitTest(point);
	//return CDialogEx::OnNcHitTest(point);
}


void CDurianDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(L"msg received");

	CDialogEx::OnOK();
}


void CDurianDlg::OnBnClickedEditInfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CRegisterDlg registerdlg;
	registerdlg.isEditInfo = 1;
	registerdlg.m_iUserID = m_user.GetUserId();
	registerdlg.DoModal();
}


void CDurianDlg::OnBnClickedRate()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedMainRefresh();
}


void CDurianDlg::OnStnClickedTitle()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDurianDlg::OnStnClickedAuthorinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CAuthorInfoDlg infoDlg;
	infoDlg.DoModal();
}
