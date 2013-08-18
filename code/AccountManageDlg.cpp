// AccountManageDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "ADO.h"
#include "AccountManageDlg.h"
#include "afxdialogex.h"
#include "AccountInfoDlg.h"
#include "Durian.h"

#define m_db CDurianApp::m_db


// CAccountManageDlg 对话框

IMPLEMENT_DYNAMIC(CAccountManageDlg, CDialogEx)

CAccountManageDlg::CAccountManageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAccountManageDlg::IDD, pParent)
	, m_username(_T(""))
	, m_registerfrom(_T(""))
	, m_blocked(FALSE)
	, m_unblocked(FALSE)
	, m_registerto(_T(""))
{
	//m_db.Open();
	m_clrBorder = DURIAN_COLOR_GREEN;
}

CAccountManageDlg::~CAccountManageDlg()
{
	//m_db.Close();
}

void CAccountManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACCOUNT_MANAGE_LIST, m_lstAccountList);
	DDX_Control(pDX, IDC_ACCOUNT_MANAGE_LOOKALL, m_btLookAll);
	DDX_Control(pDX, IDC_ACCOUNT_MANAGE_SEARCH, m_btSearch);
	DDX_Control(pDX, IDC_ACCOUNT_MANAGE_BLOCK, m_btBlock);
	DDX_Control(pDX, IDC_ACCOUNT_MANAGE_UNBLOCK, m_btUnBlock);
	DDX_Control(pDX, IDC_ACCOUNT_MANAGE_DELETE, m_btDelete);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Text(pDX, IDC_ACCOUNT_MANAGE_USERNAME, m_username);
	DDV_MaxChars(pDX, m_username, 15);
	DDX_Text(pDX, IDC_ACCOUNT_MANAGE_TIMEFROM, m_registerfrom);
	DDX_Check(pDX, IDC_ACCOUNT_MANAGE_BLOCKED, m_blocked);
	DDX_Check(pDX, IDC_ACCOUNT_MANAGE_NBLOCKED, m_unblocked);
	DDX_Text(pDX, IDC_ACCOUNT_MANAGE_TIMETO, m_registerto);
	DDX_Control(pDX, IDC_ACCOUNT_MANAGE_NUM, m_stNum);
	DDX_Control(pDX, IDC_ACCOUNT_MANAGE_DBTIPS, m_stDBTips);
	DDX_Control(pDX, IDC_ACCOUNT_MANAGE_BTMPROMPT, m_stBtmPrompt);
	DDX_Control(pDX, IDC_ACCOUNT_MANAGE_TITLE, m_stTitle);
	DDX_Control(pDX, IDC_ACCOUNT_MANAGE_SELECTALL, m_btSelectAll);
	DDX_Control(pDX, IDC_ACCOUNT_MANAGE_SELECTNONE, m_btSelectNone);
}

void CAccountManageDlg::LoadList(const vector<vector<_variant_t> > vAccount)
{
	CString setNum;
	setNum.Format(L"记录数：%d", vAccount.size());
	m_stNum.ShowWindow(false);
	m_stNum.SetWindowText(setNum);
	m_stNum.ShowWindow(true);
	m_lstAccountList.DeleteAllItems();
	
	CString strID;
	for(int i = 0;i < vAccount.size();i++)
	{
		strID.Format(L"%d", (int)vAccount[i].at(0) );
		m_lstAccountList.InsertItem(i, strID);
		for(int j = 1; j<= 3;j++)
		{
			m_lstAccountList.SetItemText(i, j, _VariantToCString(vAccount[i].at(j)));
		}
		m_lstAccountList.SetItemText(i, 4, (bool)vAccount[i].at(4) == 1? L"是" : L"");
	}
}

void CAccountManageDlg::SetBtmPrompt(const CString prompt, const COLORREF borderCol)
{
	m_clrBorder = borderCol;
	m_stBtmPrompt.SetWindowText(prompt);
}



BEGIN_MESSAGE_MAP(CAccountManageDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ACCOUNT_MANAGE_LOOKALL, &CAccountManageDlg::OnBnClickedAccountManageLookall)
	ON_BN_CLICKED(IDC_ACCOUNT_MANAGE_DELETE, &CAccountManageDlg::OnBnClickedAccountManageDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_ACCOUNT_MANAGE_LIST, &CAccountManageDlg::OnNMDblclkAccountManageList)
	ON_BN_CLICKED(IDC_ACCOUNT_MANAGE_SEARCH, &CAccountManageDlg::OnBnClickedAccountManageSearch)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_ACCOUNT_MANAGE_BLOCK, &CAccountManageDlg::OnBnClickedAccountManageBlock)
	ON_BN_CLICKED(IDC_ACCOUNT_MANAGE_UNBLOCK, &CAccountManageDlg::OnBnClickedAccountManageUnblock)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ACCOUNT_MANAGE_SELECTALL, &CAccountManageDlg::OnBnClickedAccountManageSelectall)
	ON_BN_CLICKED(IDC_ACCOUNT_MANAGE_SELECTNONE, &CAccountManageDlg::OnBnClickedAccountManageSelectnone)
END_MESSAGE_MAP()


// CAccountManageDlg 消息处理程序


void CAccountManageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	//AfxMessageBox(L"onpaint");

	CRect rect;
	CDC *pDC = GetDC();
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	
	pDC->SelectStockObject(DC_PEN);
	pDC->SetDCPenColor(m_clrBorder);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(&rect);
	pDC->FillSolidRect(rect.left, rect.top + rect.Height() - 30, rect.Width(), 30, m_clrBorder);

	GetDlgItem(IDC_ACCOUNT_MANAGE_LIST)->GetWindowRect(&rect);
	rect.left--; rect.top--; rect.right++; rect.bottom++;
	ScreenToClient(&rect);

	pDC->SetDCPenColor(DURIAN_COLOR_GREEN);
	pDC->Rectangle(&rect);

	ReleaseDC(pDC);

	m_stBtmPrompt.RedrawWindow();
	m_stNum.RedrawWindow();
}


BOOL CAccountManageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_fontTitle.CreatePointFont(300, L"微软雅黑");
	m_stTitle.Set_TextColor(DURIAN_COLOR_GREEN);
	m_stTitle.SetFont(&m_fontTitle);

	m_btBlock.m_clrButtonColNormal = m_btCancel.m_clrButtonColNormal = m_btDelete.m_clrButtonColNormal = DURIAN_COLOR_GREEN;
	m_btLookAll.m_clrButtonColNormal = m_btSearch.m_clrButtonColNormal = m_btUnBlock.m_clrButtonColNormal = DURIAN_COLOR_GREEN;
	m_btBlock.m_clrButtonColHoverd = m_btCancel.m_clrButtonColHoverd = m_btDelete.m_clrButtonColHoverd = DURIAN_COLOR_ORANGE;
	m_btLookAll.m_clrButtonColHoverd = m_btSearch.m_clrButtonColHoverd = m_btUnBlock.m_clrButtonColHoverd = DURIAN_COLOR_ORANGE;
	m_btSelectAll.m_clrButtonColNormal = m_btSelectNone.m_clrButtonColNormal = DURIAN_COLOR_GREEN;
	m_btSelectAll.m_clrButtonColHoverd = m_btSelectNone.m_clrButtonColHoverd = DURIAN_COLOR_ORANGE;

	CTime initFrom(2012, 01, 01, 0, 0, 0);
	((CDateTimeCtrl*)(GetDlgItem(IDC_ACCOUNT_MANAGE_TIMEFROM)))->SetTime(&initFrom);

	m_stDBTips.Set_TextColor(DURIAN_COLOR_GREEN);
	m_stNum.Set_TextColor(DURIAN_COLOR_WHITE);
	m_stBtmPrompt.Set_TextColor(DURIAN_COLOR_WHITE);
	m_stBtmPrompt.SetWindowText(L"在账号前打  √  以选中账号");

	m_lstAccountList.SetExtendedStyle(m_lstAccountList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT
									| LVS_EX_HEADERDRAGDROP | LVS_EX_CHECKBOXES); 

	m_lstAccountList.DeleteAllItems();
	m_lstAccountList.InsertColumn(0, L"UID", LVCFMT_CENTER, 50, 0);
	m_lstAccountList.InsertColumn(1, L"用户名", LVCFMT_CENTER, 100, 1);
	m_lstAccountList.InsertColumn(2, L"EMAIL", LVCFMT_CENTER, 160, 2);
	m_lstAccountList.InsertColumn(3, L"注册时间", LVCFMT_CENTER, 150, 3);
	m_lstAccountList.InsertColumn(4, L"已冻结", LVCFMT_CENTER, 50, 4);

	return true;
	//return TRUE;  // return TRUE unless you set the focus to a control
}


LRESULT CAccountManageDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);

	return rect.PtInRect(point)? HTCAPTION : CDialogEx::OnNcHitTest(point);
}


void CAccountManageDlg::OnNMDblclkAccountManageList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	LPNMLISTVIEW pNMLV = reinterpret_cast <LPNMLISTVIEW>(pNMHDR); 
	CString info;
	int row = pNMLV->iItem;
	info.Format(L"%s\n%s\n%s\n%s\n%s", m_lstAccountList.GetItemText(row, 0),m_lstAccountList.GetItemText(row, 1),m_lstAccountList.GetItemText(row, 2),m_lstAccountList.GetItemText(row, 3),m_lstAccountList.GetItemText(row, 4));
	
	CString sql;
	sql.Format(L"select * from user where user_id = %s", m_lstAccountList.GetItemText(row, 0));
	vector<vector<_variant_t> > vUserInfo;
	m_db.Select(sql, vUserInfo);
	
	if(vUserInfo.size() != 1)
	{
		AfxMessageBox(L"加载用户信息失败");
		return ;
	}

	CAccountInfoDlg accountInfoDlg;
	CString uid;
	uid.Format(L"%d", (int)vUserInfo[0].at(0));
	accountInfoDlg.m_edUID = uid;
	
	accountInfoDlg.m_edUsername = _VariantToCString(vUserInfo[0].at(1));
	accountInfoDlg.m_edEmail = _VariantToCString(vUserInfo[0].at(3));
	accountInfoDlg.m_edName = _VariantToCString(vUserInfo[0].at(4));
	
	accountInfoDlg.m_edQQ = _VariantToCString(vUserInfo[0].at(5));
	if(accountInfoDlg.m_edQQ == L"")	accountInfoDlg.m_edQQ = L" ---";
	
	if(_VariantToCString(vUserInfo[0].at(6)) == L"male")
		accountInfoDlg.m_edGender = L"男";
	else
		accountInfoDlg.m_edGender = L"女";

	CString strBirthdate;
	strBirthdate.Format(L"%.10s", _VariantToCString(vUserInfo[0].at(7)));
	accountInfoDlg.m_edBirthdate = (strBirthdate == L"")? L" ---" : strBirthdate;
	
	accountInfoDlg.m_edSelfintro = _VariantToCString(vUserInfo[0].at(8));
	if(accountInfoDlg.m_edSelfintro == L"")	accountInfoDlg.m_edSelfintro = L" ---";
	
	accountInfoDlg.m_edRegisterdate = _VariantToCString(vUserInfo[0].at(9));
	
	if((int)vUserInfo[0].at(10) == 1)
		accountInfoDlg.m_bAdmin = true;
	
	if((int)vUserInfo[0].at(11) == 1)
		accountInfoDlg.m_edBlock = L"是";
	else
		accountInfoDlg.m_edBlock = L"否";
	
	accountInfoDlg.DoModal();
}


void CAccountManageDlg::OnBnClickedAccountManageLookall()
{
	// TODO: 在此添加控件通知处理程序代码
	SetBtmPrompt(L"正在加载账号列表 请稍候 . . . ", DURIAN_COLOR_ORANGE);
	OnPaint();

	//Sleep(800);
	vector<vector<_variant_t> > vAccount;
	m_db.Select(L"select user_id, user_name, email, registerdate, isblocked from user where isadmin = 0", vAccount);
	LoadList(vAccount);

	SetBtmPrompt(L"列表加载完成", DURIAN_COLOR_GREEN);
}


void CAccountManageDlg::OnBnClickedAccountManageSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	SetBtmPrompt(L"正在加载账号列表 请稍候 . . . ", DURIAN_COLOR_ORANGE);
	OnPaint();
	UpdateData(true);
	CString sql = L"select user_id, user_name, email, registerdate, isblocked from user where isadmin = 0 and ";
	sql += L"user_name like \"\%" + m_username + L"\%\" and ";
	sql += L"registerdate >= \"" + m_registerfrom + L"\" and registerdate <= \"" + m_registerto + L"235959\"";
	if(m_blocked && !m_unblocked)
		sql += L" and isblocked = 1";
	else if(!m_blocked && m_unblocked)
		sql += L" and isblocked = 0";

	//AfxMessageBox(sql);

	vector<vector<_variant_t> > vAccount;
	m_db.Select(sql, vAccount);
	LoadList(vAccount);
	
	SetBtmPrompt(L"列表加载完成", DURIAN_COLOR_GREEN);
}


void CAccountManageDlg::OnBnClickedAccountManageDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	SetBtmPrompt(L"正在删除账号 请稍候 . . . ", DURIAN_COLOR_ORANGE);

	CMessageDlg mDlg(L"确定删除选中的账号？\n\n被删除的账号将无法恢复！", L"请确认");
	if(mDlg.DoModal()!=IDOK)
	{
		SetBtmPrompt(L"在账号前打  √  以选中账号", DURIAN_COLOR_GREEN);;
		return;
	}

	int nRow = m_lstAccountList.GetItemCount();
	int nSucc = 0, nFail = 0;
	//vector<CString> vFailID;
	
	CString strID;

	for(int i = 0; i < nRow; i++)
	{
		if(m_lstAccountList.GetCheck(i))
		{
			strID = m_lstAccountList.GetItemText(i, 0);
			if(m_db.Delete(L"delete from user where user_id = " + strID ) )
			{
				m_db.Delete(L"delete from comment where user_id = " + strID);
				m_db.Delete(L"delete from friends where user_id = " + strID + L" or friend_id = " + strID);
				nSucc++;
				m_lstAccountList.DeleteItem(i);
				nRow--;
				i--;
			}
			else
			{
				//vFailID.push_back(m_lstAccountList.GetItemText(i, 0));
				nFail++;
			}
		}
	}

	if(nSucc+nFail == 0)
	{
		SetBtmPrompt(L"没有选择任何账号  请在账号前打  √  以选中账号", DURIAN_COLOR_RED);
		return ;
	}

	CString result;
	result.Format(L"成功删除账号 %d 个，失败 %d 个。\n", nSucc, nFail);
	AfxMessageBox(result);

	CString strNum;
	strNum.Format(L"记录数：%d", nRow);
	m_stNum.ShowWindow(false);
	m_stNum.SetWindowText(strNum);
	m_stNum.ShowWindow(true);
	
	SetBtmPrompt(L"账号删除完成", DURIAN_COLOR_GREEN);

}


void CAccountManageDlg::OnBnClickedAccountManageBlock()
{
	// TODO: 
	SetBtmPrompt(L"正在冻结账号 请稍候 . . . ", DURIAN_COLOR_ORANGE);

	CMessageDlg mDlg(L"确定冻结选中的账号？\n\n被冻结的账号将无法登陆。", L"请确认");
	if(mDlg.DoModal()!=IDOK)
	{
		SetBtmPrompt(L"在账号前打  √  以选中账号", DURIAN_COLOR_GREEN);;
		return;
	}

	int nRow = m_lstAccountList.GetItemCount();
	int nCount = 0;
	//vector<CString> vFailID;
	
	for(int i = 0; i < nRow; i++)
	{
		if(m_lstAccountList.GetCheck(i))
		{
			m_db.Delete(L"update user set isblocked = 1 where user_id = " + m_lstAccountList.GetItemText(i, 0) );
			nCount++;
			m_lstAccountList.SetItemText(i, 4, L"是");
		}
	}

	if(nCount == 0)
	{
		SetBtmPrompt(L"没有选择任何账号  请在账号前打  √  以选中账号", DURIAN_COLOR_RED);
		return ;
	}

	CString result;
	result.Format(L"成功冻结账号 %d 个。\n", nCount);
	AfxMessageBox(result);
	SetBtmPrompt(L"账号冻结完成", DURIAN_COLOR_GREEN);
}


void CAccountManageDlg::OnBnClickedAccountManageUnblock()
{
	// TODO: 在此添加控件通知处理程序代码
	SetBtmPrompt(L"正在解除账号冻结 请稍候 . . . ", DURIAN_COLOR_ORANGE);
	
	CMessageDlg mDlg(L"\n确定解冻选中的账号？", L"请确认");
	if(mDlg.DoModal()!=IDOK)
	{
		SetBtmPrompt(L"在账号前打  √  以选中账号", DURIAN_COLOR_GREEN);;
		return;
	}


	int nRow = m_lstAccountList.GetItemCount();
	int nCount = 0;
	//vector<CString> vFailID;
	
	for(int i = 0; i < nRow; i++)
	{
		if(m_lstAccountList.GetCheck(i))
		{
			m_db.Delete(L"update user set isblocked = 0 where user_id = " + m_lstAccountList.GetItemText(i, 0) );
			nCount++;
			m_lstAccountList.SetItemText(i, 4, L"");
		}
	}

	if(nCount == 0)
	{
		SetBtmPrompt(L"没有选择任何账号  请在账号前打  √  以选中账号", DURIAN_COLOR_RED);
		return ;
	}

	CString result;
	result.Format(L"成功解除冻结账号 %d 个。\n", nCount);
	AfxMessageBox(result);
	SetBtmPrompt(L"账号解冻完成", DURIAN_COLOR_GREEN);
}




HBRUSH CAccountManageDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	UINT controlID = pWnd->GetDlgCtrlID();

	if(controlID == IDC_ACCOUNT_MANAGE_BTMPROMPT || controlID == IDC_ACCOUNT_MANAGE_NUM)
	{
		return (HBRUSH) ::CreateSolidBrush(m_clrBorder);
	}

	return hbr;
}


void CAccountManageDlg::OnBnClickedAccountManageSelectall()
{
	// TODO: 在此添加控件通知处理程序代码
	int nRow = m_lstAccountList.GetItemCount();
	for(int i = 0;i < nRow; i++)
	{
		m_lstAccountList.SetCheck(i, true);
	}
}


void CAccountManageDlg::OnBnClickedAccountManageSelectnone()
{
	// TODO: 在此添加控件通知处理程序代码
	int nRow = m_lstAccountList.GetItemCount();
	for(int i = 0;i < nRow; i++)
	{
		m_lstAccountList.SetCheck(i, false);
	}

}
