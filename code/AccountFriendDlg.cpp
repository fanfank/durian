// AccountFriendDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "ADO.h"
#include "AccountFriendDlg.h"
#include "afxdialogex.h"
#include "AccountInfoDlg.h"
#include "AddFriend.h"
#include "Durian.h"
// CAccountFriendDlg 对话框
#define m_db CDurianApp::m_db

IMPLEMENT_DYNAMIC(CAccountFriendDlg, CDialogEx)

	CAccountFriendDlg::CAccountFriendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAccountFriendDlg::IDD, pParent)
	//, m_username(_T(""))
	//, m_registerfrom(_T(""))
	//, m_blocked(FALSE)
	//, m_unblocked(FALSE)
	//, m_registerto(_T(""))
{
	//m_db.Open();
	m_clrBorder = DURIAN_COLOR_GREEN;
}

CAccountFriendDlg::~CAccountFriendDlg()
{
	//m_db.Close();
}

void CAccountFriendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACCOUNT_FRIEND_LIST, m_lstAccountList);
	DDX_Control(pDX, IDC_ACCOUNT_FRIEND_LOOKALL, m_btLookAll);
	DDX_Control(pDX, IDC_ACCOUNT_FRIEND_SEARCH, m_btSearch);
	DDX_Control(pDX, IDC_ACCOUNT_FRIEND_BLOCK, m_btBlock);
	DDX_Control(pDX, IDC_ACCOUNT_FRIEND_UNBLOCK, m_btUnBlock);
	DDX_Control(pDX, IDC_ACCOUNT_FRIEND_DELETE, m_btDelete);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	//DDX_Text(pDX, IDC_ACCOUNT_FRIEND_USERNAME, m_username);
	//(pDX, m_username, 15);
	//DDX_Text(pDX, IDC_ACCOUNT_FRIEND_TIMEFROM, m_registerfrom);
	//(pDX, IDC_ACCOUNT_FRIEND_BLOCKED, m_blocked);
	//DDX_Check(pDX, IDC_ACCOUNT_FRIEND_NBLOCKED, m_unblocked);
	//DDX_Text(pDX, IDC_ACCOUNT_FRIEND_TIMETO, m_registerto);
	DDX_Control(pDX, IDC_ACCOUNT_FRIEND_NUM, m_stNum);
	DDX_Control(pDX, IDC_ACCOUNT_FRIEND_DBTIPS, m_stDBTips);
	DDX_Control(pDX, IDC_ACCOUNT_FRIEND_BTMPROMPT, m_stBtmPrompt);
	DDX_Control(pDX, IDC_ACCOUNT_FRIEND_TITLE, m_stTitle);
}

void CAccountFriendDlg::LoadList(const vector<vector<_variant_t> > vAccount)
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

void CAccountFriendDlg::SetBtmPrompt(const CString prompt, const COLORREF borderCol)
{
	m_clrBorder = borderCol;
	m_stBtmPrompt.SetWindowText(prompt);
}




BEGIN_MESSAGE_MAP(CAccountFriendDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_NOTIFY(NM_DBLCLK, IDC_ACCOUNT_FRIEND_LIST, &CAccountFriendDlg::OnNMDblclkAccountFriendList)
	ON_BN_CLICKED(IDC_ACCOUNT_FRIEND_LOOKALL, &CAccountFriendDlg::OnBnClickedAccountFriendLookall)
	ON_BN_CLICKED(IDC_ACCOUNT_FRIEND_SEARCH, &CAccountFriendDlg::OnBnClickedAccountFriendSearch)
	ON_BN_CLICKED(IDC_ACCOUNT_FRIEND_DELETE, &CAccountFriendDlg::OnBnClickedAccountFriendDelete)
	ON_BN_CLICKED(IDC_ACCOUNT_FRIEND_BLOCK, &CAccountFriendDlg::OnBnClickedAccountFriendBlock)
	ON_BN_CLICKED(IDC_ACCOUNT_FRIEND_UNBLOCK, &CAccountFriendDlg::OnBnClickedAccountFriendUnblock)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAccountFriendDlg 消息处理程序

BOOL CAccountFriendDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_fontTitle.CreatePointFont(300, L"微软雅黑");
	m_stTitle.Set_TextColor(DURIAN_COLOR_GREEN);
	m_stTitle.SetFont(&m_fontTitle);

	m_btBlock.m_clrButtonColNormal = m_btCancel.m_clrButtonColNormal = m_btDelete.m_clrButtonColNormal = DURIAN_COLOR_GREEN;
	m_btLookAll.m_clrButtonColNormal = m_btSearch.m_clrButtonColNormal = m_btUnBlock.m_clrButtonColNormal = DURIAN_COLOR_GREEN;
	m_btBlock.m_clrButtonColHoverd = m_btCancel.m_clrButtonColHoverd = m_btDelete.m_clrButtonColHoverd = DURIAN_COLOR_ORANGE;
	m_btLookAll.m_clrButtonColHoverd = m_btSearch.m_clrButtonColHoverd = m_btUnBlock.m_clrButtonColHoverd = DURIAN_COLOR_ORANGE;

	//CTime initFrom(2012, 01, 01, 0, 0, 0);
	//((CDateTimeCtrl*)(GetDlgItem(IDC_ACCOUNT_FRIEND_TIMEFROM)))->SetTime(&initFrom);

	m_stDBTips.Set_TextColor(DURIAN_COLOR_GREEN);
	m_stNum.Set_TextColor(DURIAN_COLOR_WHITE);
	m_stBtmPrompt.Set_TextColor(DURIAN_COLOR_WHITE);
	m_stBtmPrompt.SetWindowText(L"在好友前打  √  以选中好友");

	m_lstAccountList.SetExtendedStyle(m_lstAccountList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT
		| LVS_EX_HEADERDRAGDROP | LVS_EX_CHECKBOXES); 

	m_lstAccountList.DeleteAllItems();
	m_lstAccountList.InsertColumn(0, L"UID", LVCFMT_CENTER, 50, 0);
	m_lstAccountList.InsertColumn(1, L"用户名", LVCFMT_CENTER, 100, 1);
	m_lstAccountList.InsertColumn(2, L"EMAIL", LVCFMT_CENTER, 160, 2);
	m_lstAccountList.InsertColumn(3, L"添加时间", LVCFMT_CENTER, 150, 3);
	m_lstAccountList.InsertColumn(4, L"已加黑", LVCFMT_CENTER, 50, 4);

	return true;
	//return TRUE;  // return TRUE unless you set the focus to a control
}

void CAccountFriendDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	CDC *pDC = GetDC();
	GetWindowRect(&rect);
	ScreenToClient(&rect);

	pDC->SelectStockObject(DC_PEN);
	pDC->SetDCPenColor(m_clrBorder);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(&rect);
	pDC->FillSolidRect(rect.left, rect.top + rect.Height() - 30, rect.Width(), 30, m_clrBorder);

	GetDlgItem(IDC_ACCOUNT_FRIEND_LIST)->GetWindowRect(&rect);
	rect.left--; rect.top--; rect.right++; rect.bottom++;
	ScreenToClient(&rect);

	pDC->SetDCPenColor(DURIAN_COLOR_GREEN);
	pDC->Rectangle(&rect);

	ReleaseDC(pDC);
}



LRESULT CAccountFriendDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	return rect.PtInRect(point)? HTCAPTION : CDialogEx::OnNcHitTest(point);
}


void CAccountFriendDlg::OnNMDblclkAccountFriendList(NMHDR *pNMHDR, LRESULT *pResult)
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
		AfxMessageBox(L"加载好友信息失败");
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




void CAccountFriendDlg::OnBnClickedAccountFriendLookall()
{
	// TODO: 在此添加控件通知处理程序代码
	SetBtmPrompt(L"正在加载好友列表 请稍候 . . . ", DURIAN_COLOR_ORANGE);
	
	OnPaint();

	vector<vector<_variant_t> > vFriend;

	CString sql;
	sql.Format(L"select friend_id, isblocked from friends where user_id = %d", m_iUserID);
	m_db.Select(sql, vFriend);
	vector<vector<_variant_t> > vAccount;
	vector<vector<_variant_t> > vSum;
	CString strID;
	//CString sql;
	for(int i = 0; i < vFriend.size(); i++) {
		strID.Format(L"%d", (int)vFriend[i].at(0) );
		sql.Format(L"select user_id, user_name, email, registerdate, isblocked from user where user_id = %s", strID);
		m_db.Select(sql, vAccount);
		vAccount[0].at(4) = vFriend[i].at(1);
		vSum.push_back(vAccount[0]);
	}
	LoadList(vSum);
	SetBtmPrompt(L"列表加载完成", DURIAN_COLOR_GREEN);
}




void CAccountFriendDlg::OnBnClickedAccountFriendSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddFriend addfri;
	CString sql;
	if(addfri.DoModal() == IDOK){
		if(addfri.is_ID == 0){
			sql.Format(L"select * from user where user_id = \"%s\"", addfri.text);
		}
		if(addfri.is_ID == 1){
			sql.Format(L"select * from user where user_name = \"%s\"", addfri.text);
		}
		vector<vector<_variant_t> > vUserInfo;
		m_db.Select(sql, vUserInfo);

		if(vUserInfo.size() != 1)
		{
			AfxMessageBox(L"您所查找的用户不存在");
			return ;
		}

		CAccountInfoDlg accountInfoDlg;
		accountInfoDlg.m_addFriend = true;
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
		accountInfoDlg.m_iUserID = m_iUserID;
		accountInfoDlg.DoModal();
		//AfxMessageBox(L"");
	}
	//SetBtmPrompt(L"正在更新好友列表 请稍候 . . . ", DURIAN_COLOR_ORANGE);

	SetBtmPrompt(L"列表更新完成", DURIAN_COLOR_GREEN);
	//AfxMessageBox(L"");
}


void CAccountFriendDlg::OnBnClickedAccountFriendDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	SetBtmPrompt(L"正在删除好友 请稍候 . . . ", DURIAN_COLOR_ORANGE);

	CMessageDlg mDlg(L"确定删除选中的好友？", L"请确认");
	if(mDlg.DoModal()!=IDOK)
	{
		SetBtmPrompt(L"在好友前打  √  以选中好友", DURIAN_COLOR_GREEN);;
		return;
	}

	int nRow = m_lstAccountList.GetItemCount();
	int nSucc = 0, nFail = 0;
	//vector<CString> vFailID;
	CString sql;

	for(int i = 0; i < nRow; i++)
	{
		if(m_lstAccountList.GetCheck(i))
		{
			sql.Format(L"delete from friends where friend_id = %s and user_id = %d", m_lstAccountList.GetItemText(i, 0), m_iUserID);
			if(m_db.Delete(sql) )
			{
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
		SetBtmPrompt(L"没有选择任何好友  请在好友前打  √  以选中好友", DURIAN_COLOR_RED);
		return ;
	}

	CString result;
	result.Format(L"成功删除好友 %d 个，失败 %d 个。\n", nSucc, nFail);
	AfxMessageBox(result);

	CString strNum;
	strNum.Format(L"记录数：%d", nRow);
	m_stNum.ShowWindow(false);
	m_stNum.SetWindowText(strNum);
	m_stNum.ShowWindow(true);

	SetBtmPrompt(L"好友删除完成", DURIAN_COLOR_GREEN);
}



void CAccountFriendDlg::OnBnClickedAccountFriendBlock()
{
	// TODO: 在此添加控件通知处理程序代码
	SetBtmPrompt(L"正在将好友加入黑名单 请稍候 . . . ", DURIAN_COLOR_ORANGE);

	CMessageDlg mDlg(L"确定将选中的好友加入黑名单？\n\n被加黑的好友将无法发送消息给您。", L"请确认");
	if(mDlg.DoModal()!=IDOK)
	{
		SetBtmPrompt(L"在好友前打  √  以选中好友", DURIAN_COLOR_GREEN);;
		return;
	}

	int nRow = m_lstAccountList.GetItemCount();
	int nCount = 0;
	//vector<CString> vFailID;

	for(int i = 0; i < nRow; i++)
	{
		if(m_lstAccountList.GetCheck(i))
		{
			m_db.Delete(L"update friends set isblocked = 1 where friend_id = " + m_lstAccountList.GetItemText(i, 0) );
			nCount++;
			m_lstAccountList.SetItemText(i, 4, L"是");
		}
	}

	if(nCount == 0)
	{
		SetBtmPrompt(L"没有选择任何好友  请在好友前打  √  以选中好友", DURIAN_COLOR_RED);
		return ;
	}

	CString result;
	result.Format(L"成功将 %d 个好友加入黑名单。\n", nCount);
	AfxMessageBox(result);
	SetBtmPrompt(L"好友加黑完成", DURIAN_COLOR_GREEN);
}


void CAccountFriendDlg::OnBnClickedAccountFriendUnblock()
{
	// TODO: 在此添加控件通知处理程序代码
	SetBtmPrompt(L"正在将好友移出黑名单 请稍候 . . . ", DURIAN_COLOR_ORANGE);

	CMessageDlg mDlg(L"\n确定将选中的好友移出黑名单？", L"请确认");
	if(mDlg.DoModal()!=IDOK)
	{
		SetBtmPrompt(L"在账号前打  √  以选中好友", DURIAN_COLOR_GREEN);;
		return;
	}


	int nRow = m_lstAccountList.GetItemCount();
	int nCount = 0;
	//vector<CString> vFailID;

	for(int i = 0; i < nRow; i++)
	{
		if(m_lstAccountList.GetCheck(i))
		{
			m_db.Delete(L"update friends set isblocked = 0 where friend_id = " + m_lstAccountList.GetItemText(i, 0) );
			nCount++;
			m_lstAccountList.SetItemText(i, 4, L"");
		}
	}

	if(nCount == 0)
	{
		SetBtmPrompt(L"没有选择任何好友  请在好友前打  √  以选中好友", DURIAN_COLOR_RED);
		return ;
	}

	CString result;
	result.Format(L"成功将 %d 个好友移出黑名单。\n", nCount);
	AfxMessageBox(result);
	SetBtmPrompt(L"好友解黑完成", DURIAN_COLOR_GREEN);
}



HBRUSH CAccountFriendDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	UINT controlID = pWnd->GetDlgCtrlID();

	if(controlID == IDC_ACCOUNT_FRIEND_BTMPROMPT || controlID == IDC_ACCOUNT_FRIEND_NUM)
	{
		return (HBRUSH) ::CreateSolidBrush(m_clrBorder);
	}

	return hbr;
}
