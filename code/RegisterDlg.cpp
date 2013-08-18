// RegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "ADO.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include "DatabaseADO.h"
#include "resource.h"
#include "Durian.h"
#include "ChangePassDlg.h"
#define db CDurianApp::m_db
#define m_user CDurianApp::m_user
// CRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialogEx)

	CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegisterDlg::IDD, pParent)
	, m_username(_T(""))
	, m_password(_T(""))
	, m_password2(_T(""))
	, m_email(_T(""))
	, m_name(_T(""))
	, m_qq(_T(""))
	, m_selfintro(_T(""))
	, m_year(_T(""))
	, m_month(_T(""))
	, m_gender(0)
{
	m_clrBorder = DURIAN_COLOR_ORANGE;
	isEditInfo = 0;
	password = "";
}

CRegisterDlg::~CRegisterDlg()
{
	m_font.DeleteObject();
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REGISTER_PROMPT, m_stPrompt);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDC_REGISTER_TITLE, m_stTitle);
	DDX_Text(pDX, IDC_REGISTER_USERNAME, m_username);
	DDV_MaxChars(pDX, m_username, 15);
	DDX_Text(pDX, IDC_REGISTER_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 20);
	DDX_Text(pDX, IDC_REGISTER_PASSWORD2, m_password2);
	DDV_MaxChars(pDX, m_password2, 20);
	DDX_Text(pDX, IDC_REGISTER_EMAIL, m_email);
	DDV_MaxChars(pDX, m_email, 60);
	DDX_Text(pDX, IDC_REGISTER_NAME, m_name);
	DDV_MaxChars(pDX, m_name, 10);
	DDX_Text(pDX, IDC_REGISTER_QQ, m_qq);
	DDV_MaxChars(pDX, m_qq, 15);
	DDX_Text(pDX, IDC_REGISTER_SELFINTRO, m_selfintro);
	DDV_MaxChars(pDX, m_selfintro, 300);
	DDX_Text(pDX, IDC_REGISTER_BIRTHYEAR, m_year);
	DDV_MaxChars(pDX, m_year, 4);
	DDX_Text(pDX, IDC_REGISTER_BIRTHMONTH, m_month);
	DDV_MaxChars(pDX, m_month, 2);
	DDX_Radio(pDX, IDC_REGISTER_FEMALE, m_gender);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_CHANGE_PASSWORD, m_btChangePass);
}

bool CRegisterDlg::UsernameValidation()
{
	CString temp;
	GetDlgItemText(IDC_REGISTER_USERNAME, temp);
	const int len = temp.GetLength();
	if(len < 3 || len > 15)
		return false;
	else
	{
		for(int i = 0;i < len; i++)
		{
			if( !( ('a'<=temp[i]&&temp[i]<='z')||('0'<=temp[i]&&temp[i]<='9')||(temp[i]=='_') ))
				return false;
		}
	}
	return true;
}

bool CRegisterDlg::CheckUsernameExist()
{
	CString temp;
	GetDlgItemText(IDC_REGISTER_USERNAME, temp);
	vector<vector<_variant_t> > v(2);
	db.Select(L"SELECT user_id FROM user WHERE user_name=\""+temp+L"\"", v);
	return !(v.size()>0);
}

bool CRegisterDlg::PasswordValidation()
{
	CString temp;
	GetDlgItemText(IDC_REGISTER_PASSWORD, temp);
	const int len = temp.GetLength();
	if(len < 6 || len > 15)
		return false;
	else
	{
		for(int i = 0;i < len; i++)
		{
			if( !( ('a'<=temp[i]&&temp[i]<='z')||('0'<=temp[i]&&temp[i]<='9')||('A'<=temp[i]&&temp[i]<='Z') ))
				return false;
		}
	}
	return true;
}

bool CRegisterDlg::PasswordMatch()
{
	CString temp1, temp2;
	GetDlgItemText(IDC_REGISTER_PASSWORD, temp1);
	GetDlgItemText(IDC_REGISTER_PASSWORD2, temp2);
	return (temp1 == temp2);
}

bool CRegisterDlg::EmailValidation()
{
	CString temp;
	GetDlgItemText(IDC_REGISTER_EMAIL, temp);
	const int len = temp.GetLength();
	int addin = -1;
	for(int i = 0;i < len; i++)
	{
		//只能由大小写英文字母、数字以及符号“@”、“.”、“_”、“-”构成
		if( !( ('a'<=temp[i]&&temp[i]<='z')||('0'<=temp[i]&&temp[i]<='9')||('A'<=temp[i]&&temp[i]<='Z')||(temp[i] == '_')||(temp[i] == '.')||(temp[i] == '-')||(temp[i] == '@') ))
			return false;
		if(temp[i] == '@')	//有且只有一个“@”
		{
			if(addin != -1)
				return false;
			else 
				addin = i;
		}
	}
	if(! (addin < len-1 && addin > 0))	
		return false;	//含有“@”且“@”不在首尾
	if(temp[addin - 1] == '.' || temp[addin + 1] == '.')	
		return false;	//“@”的前后不能为“.”
	if( !( ('a'<=temp[len-1]&&temp[len-1]<='z')||('0'<=temp[len-1]&&temp[len-1]<='9')||('A'<=temp[len-1]&&temp[len-1]<='Z')))
		return false;	//不能以标点符号结尾

	bool dotafteradd = false;
	for(int i = addin+2;i < len - 1; i++)
	{
		if(temp[i] == '.')
		{
			if(temp[i-1] != '.' && temp[i+1]!='.')	//“@”后应该有至少一个“.”且不能连续出现
				dotafteradd = true;
			else									
				return false;
		}
	}
	return dotafteradd;

}

bool CRegisterDlg::NameValidation()
{
	CString temp;
	GetDlgItemText(IDC_REGISTER_NAME, temp);
	return (temp != L"");
}

bool CRegisterDlg::BirthdateValidation()
{
	CString year, month;
	GetDlgItemText(IDC_REGISTER_BIRTHYEAR, year);
	GetDlgItemText(IDC_REGISTER_BIRTHMONTH, month);
	if(year == L"" && month == L"")
		return true;
	if((year.Compare(L"1900") < 0 || year.Compare(L"2012") > 0))
		return false;
	if(month.GetLength() == 1)
		month = L"0" + month;
	if((month.Compare(L"01") < 0 || month.Compare(L"12") > 0))
		return false;
	return true;
}

bool CRegisterDlg::CheckForm()
{
	bool checkRecult = true;
	CString errPrompt;
	if(!UsernameValidation())
	{
		errPrompt = L"用户名无效。用户名由小写英文字母、数字、下划线组成，长度为3到15位。";
		GetDlgItem(IDC_REGISTER_USERNAME)->SetFocus();
		checkRecult = false;
	}
	else if(!isEditInfo && !CheckUsernameExist())
	{
		errPrompt = L"用户名已存在";
		GetDlgItem(IDC_REGISTER_USERNAME)->SetFocus();
		checkRecult = false;
	}
	else if(!isEditInfo && !PasswordValidation())
	{
		errPrompt = L"密码无效。密码由英文字母、数字组成，长度为6到20位。";
		GetDlgItem(IDC_REGISTER_PASSWORD)->SetFocus();
		checkRecult = false;
	}
	else if(!PasswordMatch())
	{
		errPrompt = L"两次输入的密码不一致，请重新输入";
		GetDlgItem(IDC_REGISTER_PASSWORD2)->SetFocus();
		checkRecult = false;
	}
	else if(!EmailValidation())
	{
		errPrompt = L"请填写正确的Email地址";
		GetDlgItem(IDC_REGISTER_EMAIL)->SetFocus();
		checkRecult = false;
	}
	else if(!NameValidation())
	{
		errPrompt = L"请填写您的真实姓名";
		GetDlgItem(IDC_REGISTER_NAME)->SetFocus();
		checkRecult = false;
	}
	else if(!BirthdateValidation())
	{
		errPrompt = L"请输入正确的出生年月";
		GetDlgItem(IDC_REGISTER_BIRTHYEAR)->SetFocus();
		checkRecult = false;
	}

	if(!checkRecult)
	{
		m_clrBorder = DURIAN_COLOR_RED;
		m_stPrompt.SetWindowText(errPrompt);
	}

	return checkRecult;
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CRegisterDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHANGE_PASSWORD, &CRegisterDlg::OnBnClickedChangePassword)
END_MESSAGE_MAP()


// CRegisterDlg 消息处理程序


BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_CHANGE_PASSWORD)->ShowWindow(FALSE);
	m_stPrompt.Set_TextColor(DURIAN_COLOR_WHITE);
	if(isEditInfo != 1) m_stPrompt.SetWindowText(L"请填写注册信息  带 * 号的为必填项");
	m_font.CreateFont(50, 18, 0, 0, 100, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, _T("微软雅黑"));
	if(isEditInfo) m_stTitle.SetWindowTextW(L"修 改 资 料");
	m_stTitle.SetFont(&m_font);
	m_stTitle.Set_TextColor(DURIAN_COLOR_ORANGE);
	if(isEditInfo) {
		GetDlgItem(IDC_CHANGE_PASSWORD)->ShowWindow(TRUE);
		CString sql;
		vector<vector<_variant_t> > vUserInfo;
		sql.Format(L"select user_name from user where user_id = %d", m_iUserID);
		db.Select(sql, vUserInfo);
		if(vUserInfo[0].size() != 0) GetDlgItem(IDC_REGISTER_USERNAME)->SetWindowTextW(_VariantToCString(vUserInfo[0].at(0)));
		GetDlgItem(IDC_REGISTER_USERNAME)->EnableWindow(FALSE);
		sql.Format(L"select user_password from user where user_id = %d", m_iUserID);
		db.Select(sql, vUserInfo);
		password = _VariantToCString(vUserInfo[0].at(0));
		GetDlgItem(IDC_REGISTER_PASSWORD)->SetWindowTextW(L"······");
		GetDlgItem(IDC_REGISTER_PASSWORD)->EnableWindow(FALSE);
		GetDlgItem(IDC_REGISTER_PASSWORD2)->SetWindowTextW(L"······");
		GetDlgItem(IDC_REGISTER_PASSWORD2)->EnableWindow(FALSE);
		sql.Format(L"select email from user where user_id = %d", m_iUserID);
		db.Select(sql, vUserInfo);
		if(vUserInfo[0].size() != 0) GetDlgItem(2004)->SetWindowTextW(_VariantToCString(vUserInfo[0].at(0)));
		sql.Format(L"select name from user where user_id = %d", m_iUserID);
		db.Select(sql, vUserInfo);
		if(vUserInfo[0].size() != 0) GetDlgItem(IDC_REGISTER_NAME)->SetWindowTextW(_VariantToCString(vUserInfo[0].at(0)));
		sql.Format(L"select qq from user where user_id = %d", m_iUserID);
		db.Select(sql, vUserInfo);
		if(vUserInfo[0].size() != 0) GetDlgItem(IDC_REGISTER_QQ)->SetWindowTextW(_VariantToCString(vUserInfo[0].at(0)));
		sql.Format(L"select gender from user where user_id = %d", m_iUserID);
		db.Select(sql, vUserInfo);
		if(_VariantToCString(vUserInfo[0].at(0)) == "male") CheckRadioButton(IDC_REGISTER_FEMALE, IDC_REGISTER_MALE, IDC_REGISTER_MALE); 
		if(_VariantToCString(vUserInfo[0].at(0)) == "female") CheckRadioButton(IDC_REGISTER_FEMALE, IDC_REGISTER_MALE, IDC_REGISTER_FEMALE);
		sql.Format(L"select birthdate from user where user_id = %d", m_iUserID);
		db.Select(sql, vUserInfo);
		if(vUserInfo[0].size() != 0) {
			CString year;
			year.Format(L"%s", _VariantToCString(vUserInfo[0].at(0)).Left(4));
			GetDlgItem(IDC_REGISTER_BIRTHYEAR)->SetWindowTextW(year);
			CString month;
			month.Format(L"%s", _VariantToCString(vUserInfo[0].at(0)).Mid(5,2));
			GetDlgItem(IDC_REGISTER_BIRTHMONTH)->SetWindowTextW(month);
		}
		sql.Format(L"select selfintro from user where user_id = %d", m_iUserID);
		db.Select(sql, vUserInfo);
		if(vUserInfo[0].size() != 0) GetDlgItem(IDC_REGISTER_SELFINTRO)->SetWindowTextW(_VariantToCString(vUserInfo[0].at(0)));
	}
	if(isEditInfo != 1) GetDlgItem(IDC_REGISTER_USERNAME)->SetFocus();
	return false;
}


void CRegisterDlg::OnOK()
{
	if(!db.m_bIsOpen)
	{	AfxMessageBox(L"未连接到数据库\n无法使用注册功能！");
		return;
	}

	// TODO: 在此添加专用代码和/或调用基类
	m_clrBorder = DURIAN_COLOR_GREEN;
	m_stPrompt.SetWindowText(L"正在提交 请稍候...");

	if(CheckForm())
	{
		UpdateData(true);
		//AfxMessageBox(sql);
		m_selfintro.Replace(L"\\", L"\\\\");
		m_selfintro.Replace(L"\"", L"\\\"");
		m_name.Replace(L"\\", L"\\\\");
		m_name.Replace(L"\"", L"\\\"");

		if(isEditInfo) {
			CString userid;
			CString gender;
			userid.Format(L"%d", m_iUserID);
			CString sql;
			if (m_qq  == L"") m_qq = L"NULL";
			else m_qq = L"\"" + m_qq + L"\"";
			if (m_gender == 0) gender = L"female";
			else gender = "male";
			if(m_month.GetLength() == 1)	m_month = L"0"+m_month;
			if (m_year == L"") m_year = L"NULL";
			else m_year = L"\"" + m_year + m_month + L"01\"";
			if (m_selfintro == L"") m_selfintro = L"NULL";
			else m_selfintro = L"\"" + m_selfintro + L"\"";
			sql.Format(L"UPDATE user SET user_password = \"%s\", email = \"%s\", name = \"%s\", qq = %s, gender = \"%s\", birthdate = %s, selfintro = %s where user_id = %d", 
						password, m_email, m_name, m_qq, gender, m_year, m_selfintro, m_iUserID);
			//5/*sql+=(m_selfintro == L"")? L"NULL, ": (L"\"" + m_selfintro);
			if(db.Update(sql) == 0)
			{
				/*m_clrBorder = DURIAN_COLOR_RED;
				m_stPrompt.SetWindowText(L"更改资料失败！");
				AfxMessageBox(L"更改资料失败..");
				*/
			}
			else
			{
				m_stPrompt.SetWindowText(L"更新资料成功！");
				AfxMessageBox(L"更新资料成功！");
			}
		}
		else {
			CString sql = L"INSERT INTO user VALUE (NULL, ";
			sql+=L"\"" + m_username + L"\", ";
			sql+=L"\"" + m_password + L"\", ";
			sql+=L"\"" + m_email + L"\", ";
			sql+=L"\"" + m_name + L"\", ";
			sql+=(m_qq  == L"")? L"NULL, " : (L"\"" + m_qq + L"\", ");
			sql+=(m_gender == 0)? (L"\"female\", ") : (L"\"male\", ");
			if(m_month.GetLength() == 1)	m_month = L"0"+m_month;
			sql+=(m_year == L"")? L"NULL, " : (L"\"" + m_year + m_month + L"01\", ");
			sql+=(m_selfintro == L"")? L"NULL, ": (L"\"" + m_selfintro + L"\", ");
			SYSTEMTIME curTime;
			GetLocalTime(&curTime);
			CString registertime;
			registertime.Format(L"%04d%02d%02d%02d%02d%02d", curTime.wYear, curTime.wMonth, curTime.wDay, curTime.wHour, curTime.wMinute, curTime.wSecond);
			sql+=registertime+L", ";
			sql+=L"0, 0)";
			if(db.Insert(sql) == -1)
			{
				m_clrBorder = DURIAN_COLOR_RED;
				m_stPrompt.SetWindowText(L"注册失败！");
				AfxMessageBox(L"注册失败..");
			}
			else
			{
				m_stPrompt.SetWindowText(L"注册成功！");
				AfxMessageBox(L"注册成功！欢迎加入榴莲");
			}
		}
		this->SendMessage(WM_CLOSE);
	}
}


LRESULT CRegisterDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = rect.top + 100;
	ClientToScreen(&rect);

	return rect.PtInRect(point)? HTCAPTION : CDialogEx::OnNcHitTest(point);
}


void CRegisterDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC *pDC = GetDC();
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);

	pDC->SelectStockObject(DC_PEN);
	pDC->SetDCPenColor(m_clrBorder);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(&rect);
	pDC->FillSolidRect(rect.left, rect.top + rect.Height() - 30, rect.Width(), 30, m_clrBorder);

	ReleaseDC(pDC);
	//AfxMessageBox(L"PAINT DONE");
}


HBRUSH CRegisterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(pWnd->GetDlgCtrlID() == IDC_REGISTER_PROMPT)
	{
		return (HBRUSH) ::CreateSolidBrush(m_clrBorder);
	}
	return hbr;
}


void CRegisterDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CRegisterDlg::OnBnClickedChangePassword()
{
	// TODO: 在此添加控件通知处理程序代码
	CChangePassDlg changePsw;
	changePsw.password = password;
	if(changePsw.DoModal() == IDOK){
		password = changePsw.new_password1;
	}
}
