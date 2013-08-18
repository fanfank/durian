// CommentDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "ADO.h"
#include "CommentDlg.h"
#include "afxdialogex.h"
#include "MessageDlg.h"
#include "Durian.h"

#define m_db CDurianApp::m_db
#define m_pRecordSet CDurianApp::m_pRecordSet
//#define m_strWorkingDir CDurianApp::m_strWorkingDir
// CCommentDlg 对话框

IMPLEMENT_DYNAMIC(CCommentDlg, CDialogEx)

CCommentDlg::CCommentDlg(CString strType, CString strName, CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommentDlg::IDD, pParent)
{
	/*
	m_nUserID = 2;
	m_nItemID = 2;
	m_bAdmin = false;
	*/
	m_strName = strName;
	m_strType = strType;
}

CCommentDlg::~CCommentDlg()
{
	//m_db.Close();
}

void CCommentDlg::ShowReview(int index, bool show)
{
	m_pAuthor[index]->ShowWindow(show);
	m_pReply[index]->ShowWindow(show);
	m_pDelete[index]->ShowWindow(show);
	m_pReviews[index]->ShowWindow(show);
	m_pTime[index]->ShowWindow(show);
}

void CCommentDlg::HideAll()
{
	for(int i = 0;i < NUM_PER_PAGE;i++)
	{
		m_pAuthor[i]->ShowWindow(false);
		m_pDelete[i]->ShowWindow(false);
		m_pDelete[i]->EnableWindow(false);
		m_pDelete[i]->SetWindowText(L"");
		m_pReply[i]->ShowWindow(false);
		m_pReviews[i]->ShowWindow(false);
		m_pTime[i]->ShowWindow(false);
	}
}

void CCommentDlg::Load()
{
	CString filter;
	filter.Format(L"where user.user_id = comment.user_id and comment.item_id = %d order by comment.time desc", m_nItemID);
	CString sql = L"select user.user_id, user.user_name, comment.comment_id, comment.time, comment.content from user, comment " + filter;
	//AfxMessageBox(sql);
	m_nCount = 0;
	m_pRecordSet = m_db.Select(sql);
	if(!m_pRecordSet->adoBOF)
	{
		while(!m_pRecordSet->adoEOF)
		{
			m_pRecordSet->MoveNext();
			m_nCount++;
		}
		m_pRecordSet->MoveFirst();

		m_nTotalPage = m_nCount / NUM_PER_PAGE;
		if(m_nCount%NUM_PER_PAGE == 0) m_nTotalPage--;
		m_nCurPage = 0;
		//CString t;
		//t.Format(L"%d %d", nCount, m_nTotalPage);
		//	AfxMessageBox(t);
//		m_bNoReview = false;
	}
	else
	{
		m_nTotalPage = 0;
	}
	CString num;
	num.Format(L"当前评论数：%d", m_nCount);
	m_stNum.SetWindowText(num);
}

void CCommentDlg::ShowPage(int PageNum)
{
	HideAll();
	if(m_nCount == 0) 
	{
		return ;
	}
	if(PageNum < 0)
	{
		//AfxMessageBox(L"页面显示错误");
		PageNum = 0;
	}
	if(PageNum > m_nTotalPage)
	{
		PageNum = m_nTotalPage;
	}
	m_pRecordSet->Move( (PageNum - m_nCurPage) * NUM_PER_PAGE );
	m_nCurPage = PageNum;
	
	CString username;
	CString time;
	int k = 0;
	while(k < NUM_PER_PAGE && !m_pRecordSet->adoEOF)
	{
		m_pAuthor[k]->SetWindowText(_VariantToCString(m_pRecordSet->GetCollect(L"user_name")));
		//time.Format(L"%.16s", _VariantToCString(m_pRecordSet->GetCollect(L"time")));
		time.Format(L"%s", _VariantToCString(m_pRecordSet->GetCollect(L"time")));

		m_pTime[k]->SetWindowText(L"发表于\n" + time);
		m_pReviews[k]->SetWindowText(_VariantToCString(m_pRecordSet->GetCollect(L"content")));
		m_nID[k] = (long long)m_pRecordSet->GetCollect(L"comment_id");

		ShowReview(k);
		if((int)m_pRecordSet->GetCollect(L"user_id") == m_nUserID || m_bAdmin)
		{
			//m_pDelete[k]->ShowWindow(true);
			m_pDelete[k]->EnableWindow(true);
			m_pDelete[k]->SetWindowText(L"删除");
		}
		
		k++; m_pRecordSet->MoveNext();
	}
	
	m_pRecordSet->Move(-k);
	
	CString page;
	page.Format(L"%d", m_nCurPage + 1);
	m_stCurPage.SetWindowText(page);

	if(m_nCurPage == m_nTotalPage)
		m_stNoMoreTips.ShowWindow(true);
	else
		m_stNoMoreTips.ShowWindow(false);

}

void CCommentDlg::Reply(int index)
{
	CString username;
	m_pAuthor[index]->GetWindowText(username);
	SetDlgItemText(IDC_COMMENT_ST_REPLYNAME, L"回复 "+username+L" ： ");
	m_btCancelReply.ShowWindow(true);

	GetDlgItem(IDC_COMMENT_INPUT) ->SetFocus();
}

void CCommentDlg::Delete(int index)
{
	CMessageDlg messageDlg(L"确定删除此评论？\n\n评论删除后将不能恢复。");
	if(messageDlg.DoModal() != IDOK)
		return ;
	
	CString sql;
	sql.Format(L"delete from comment where comment_id = %d", m_nID[index]);
	if(!m_db.Delete(sql))
		AfxMessageBox(L"删除失败");
	else
	{
		AfxMessageBox(L"评论已被删除");
		int curPage = m_nCurPage;
		Load();
		ShowPage(curPage);
	}
	
}

void CCommentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMMENT_BT_REPLY1, m_btReply1);
	DDX_Control(pDX, IDC_COMMENT_BT_REPLY2, m_btReply2);
	DDX_Control(pDX, IDC_COMMENT_BT_REPLY3, m_btReply3);
	DDX_Control(pDX, IDC_COMMENT_BT_REPLY4, m_btReply4);
	DDX_Control(pDX, IDC_COMMENT_BT_REPLY5, m_btReply5);
	DDX_Control(pDX, IDC_COMMENT_BT_DELETE1, m_btDelete1);
	DDX_Control(pDX, IDC_COMMENT_BT_DELETE2, m_btDelete2);
	DDX_Control(pDX, IDC_COMMENT_BT_DELETE3, m_btDelete3);
	DDX_Control(pDX, IDC_COMMENT_BT_DELETE4, m_btDelete4);
	DDX_Control(pDX, IDC_COMMENT_BT_DELETE5, m_btDelete5);


	DDX_Control(pDX, IDC_COMMENT_SUBMIT, m_btSubmit);
	DDX_Control(pDX, IDC_COMMENT_BT_FIRST, m_btFirst);
	DDX_Control(pDX, IDC_COMMENT_BT_PREVIOUS, m_btPrevious);
	DDX_Control(pDX, IDC_COMMENT_BT_NEXT, m_btNext);
	DDX_Control(pDX, IDC_COMMENT_BT_LAST, m_btLast);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_COMMENT_ST_PAGE, m_stCurPage);                                                  
	//	DDX_Control(pDX, IDC_COMMENT_ST_PROMPT, m_stPrompt);
	DDX_Control(pDX, IDC_COMMENT_ST_NOMORE, m_stNoMoreTips);
	DDX_Control(pDX, IDC_COMMENT_BT_CANCEL_REPLY, m_btCancelReply);
	DDX_Control(pDX, IDC_COMMENT_ST_TITLE, m_stTitle);
	DDX_Control(pDX, IDC_COMMENT_ST_NUM, m_stNum);
	DDX_Control(pDX, IDC_COMMENT_ED_GOTOPAGE, m_edGotoPage);
	DDX_Control(pDX, IDC_COMMENT_BT_GOTO, m_btGoto);
	DDX_Control(pDX, IDC_COMMENT_ST_GOTO, m_stGoto);
}


BEGIN_MESSAGE_MAP(CCommentDlg, CDialogEx)
	ON_BN_CLICKED(IDC_COMMENT_BT_PREVIOUS, &CCommentDlg::OnBnClickedCommentBtPrevious)
	ON_BN_CLICKED(IDC_COMMENT_BT_NEXT, &CCommentDlg::OnBnClickedCommentBtNext)
	ON_BN_CLICKED(IDC_COMMENT_BT_FIRST, &CCommentDlg::OnBnClickedCommentBtFirst)
	ON_BN_CLICKED(IDC_COMMENT_BT_LAST, &CCommentDlg::OnBnClickedCommentBtLast)
	ON_BN_CLICKED(IDC_COMMENT_BT_REPLY1, &CCommentDlg::OnBnClickedCommentBtReply1)
	ON_BN_CLICKED(IDC_COMMENT_BT_REPLY2, &CCommentDlg::OnBnClickedCommentBtReply2)
	ON_BN_CLICKED(IDC_COMMENT_BT_REPLY3, &CCommentDlg::OnBnClickedCommentBtReply3)
	ON_BN_CLICKED(IDC_COMMENT_BT_REPLY4, &CCommentDlg::OnBnClickedCommentBtReply4)
	ON_BN_CLICKED(IDC_COMMENT_BT_REPLY5, &CCommentDlg::OnBnClickedCommentBtReply5)
	ON_BN_CLICKED(IDC_COMMENT_SUBMIT, &CCommentDlg::OnBnClickedCommentSubmit)
	ON_BN_CLICKED(IDC_COMMENT_BT_CANCEL_REPLY, &CCommentDlg::OnBnClickedCommentBtCancelReply)
	ON_BN_CLICKED(IDC_COMMENT_BT_DELETE1, &CCommentDlg::OnBnClickedCommentBtDelete1)
	ON_BN_CLICKED(IDC_COMMENT_BT_DELETE2, &CCommentDlg::OnBnClickedCommentBtDelete2)
	ON_BN_CLICKED(IDC_COMMENT_BT_DELETE3, &CCommentDlg::OnBnClickedCommentBtDelete3)
	ON_BN_CLICKED(IDC_COMMENT_BT_DELETE4, &CCommentDlg::OnBnClickedCommentBtDelete4)
	ON_BN_CLICKED(IDC_COMMENT_BT_DELETE5, &CCommentDlg::OnBnClickedCommentBtDelete5)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_COMMENT_BT_GOTO, &CCommentDlg::OnBnClickedCommentBtGoto)
END_MESSAGE_MAP()


// CCommentDlg 消息处理程序


BOOL CCommentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_clrBorder = DURIAN_COLOR_GREEN;
	m_fontTitle.CreatePointFont(150, L"微软雅黑");
	m_stTitle.SetFont(&m_fontTitle);

	CString title;
	if(m_strType[0] == 'm')
		title = L"电影";
	else if(m_strType[0] == 'b')
		title = L"书籍";
	else if(m_strType[0] == 'a')
		title = L"时事";
	
	title+=L"：" + m_strName + L" 的评论";
	m_stTitle.SetWindowText(title);

	m_btNext.m_clrButtonColNormal = m_btPrevious.m_clrButtonColNormal = m_btFirst.m_clrButtonColNormal = m_btLast.m_clrButtonColNormal = DURIAN_COLOR_GREEN;
	m_btNext.m_clrButtonColHoverd = m_btPrevious.m_clrButtonColHoverd = m_btFirst.m_clrButtonColHoverd = m_btLast.m_clrButtonColHoverd = DURIAN_COLOR_ORANGE;
	m_btSubmit.m_clrButtonColNormal = DURIAN_COLOR_GREEN;
	m_btSubmit.m_clrButtonColHoverd = DURIAN_COLOR_ORANGE;
	m_btCancelReply.m_clrButtonColNormal = m_btCancel.m_clrButtonColNormal = DURIAN_COLOR_GREEN;
	m_btCancelReply.m_clrButtonColHoverd = m_btCancel.m_clrButtonColHoverd = DURIAN_COLOR_RED;

	//m_db.Open();

	int nRev = IDC_COMMENT_ED_REVIEW1;
	int nInf = IDC_COMMENT_ST_TIME1;
	int nDel = IDC_COMMENT_BT_DELETE1;
	int nRep = IDC_COMMENT_BT_REPLY1;
	int nAut = IDC_COMMENT_ST_AUTHOR1;

	for(int i = 0;i < 5; i++)
	{
		m_pReviews[i] = (CEdit*) GetDlgItem(nRev + i);
		m_pTime[i] = (CStatic*) GetDlgItem(nInf + i);
		m_pDelete[i] = (CDurianButton*) GetDlgItem(nDel + i);
		m_pReply[i] = (CDurianButton*) GetDlgItem(nRep + i);
		m_pAuthor[i] = (CStatic*) GetDlgItem(nAut + i);
		/*
		m_pReviews[i] ->SetWindowText(L"aaa");
		m_pTime[i]->SetWindowText(L"bbb");
		m_pDelete[i]->SetWindowText(L"ccc");
		m_pReply[i] ->SetWindowText(L"ddd");
		*/
	}

	m_pReply[1]->m_clrButtonColNormal = m_pReply[3]->m_clrButtonColNormal = DURIAN_COLOR_GREEN;
	m_pDelete[1]->m_clrButtonColNormal = m_pDelete[3]->m_clrButtonColNormal = DURIAN_COLOR_GREEN;
	m_pReply[1]->m_clrButtonColHoverd = m_pReply[3]->m_clrButtonColHoverd = DURIAN_COLOR_ORANGE;
	m_pDelete[1]->m_clrButtonColHoverd = m_pDelete[3]->m_clrButtonColHoverd = DURIAN_COLOR_ORANGE;
	m_pDelete[1]->m_clrButtonColDisabled = m_pDelete[3]->m_clrButtonColDisabled = DURIAN_COLOR_GREEN;
	m_pDelete[0]->m_clrButtonColDisabled = m_pDelete[2]->m_clrButtonColDisabled =m_pDelete[4]->m_clrButtonColDisabled = DURIAN_COLOR_ORANGE;

	m_edGotoPage.SetWindowText(L"1");
	m_nCurPage = 0;
	Load();
	ShowPage(0);

	return TRUE;
}


void CCommentDlg::OnBnClickedCommentBtPrevious()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_nCurPage == 0)
		return ;
	//m_nCurPage --;
	//m_pRecordSet->Move(-NUM_PER_PAGE);
	ShowPage(m_nCurPage - 1);
}


void CCommentDlg::OnBnClickedCommentBtNext()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_nCurPage == m_nTotalPage)
		return ;
	//m_nCurPage ++;
	//m_pRecordSet->Move(NUM_PER_PAGE);
	ShowPage(m_nCurPage + 1);
}


void CCommentDlg::OnBnClickedCommentBtFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_nCurPage == 0)
		return ;
	//m_nCurPage = 0;
	//m_pRecordSet->MoveFirst();
	ShowPage(0);
}


void CCommentDlg::OnBnClickedCommentBtLast()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_nCurPage == m_nTotalPage)
		return ;
	//m_pRecordSet->Move( (m_nTotalPage-m_nCurPage) * NUM_PER_PAGE );
	//m_nCurPage = m_nTotalPage;	
	ShowPage(m_nTotalPage);
}


void CCommentDlg::OnBnClickedCommentBtReply1()
{
	// TODO: 在此添加控件通知处理程序代码
	Reply(0);
}

void CCommentDlg::OnBnClickedCommentBtReply2()
{
	// TODO: 在此添加控件通知处理程序代码
	Reply(1);
}

void CCommentDlg::OnBnClickedCommentBtReply3()
{
	// TODO: 在此添加控件通知处理程序代码
	Reply(2);
}

void CCommentDlg::OnBnClickedCommentBtReply4()
{
	// TODO: 在此添加控件通知处理程序代码
	Reply(3);
}

void CCommentDlg::OnBnClickedCommentBtReply5()
{
	// TODO: 在此添加控件通知处理程序代码
	Reply(4);
}



void CCommentDlg::OnBnClickedCommentSubmit()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_nUserID == -1)
	{
		AfxMessageBox(L"对不起，您还没有登陆，没有发表评论的权限。");
		return ;
	}
	CString content;
	GetDlgItemText(IDC_COMMENT_INPUT, content);
	if(content.GetLength() < 4)
	{
		AfxMessageBox(L"评论内容须大于 4 个字符");
		return ;
	}

	CString reply;
	GetDlgItemText(IDC_COMMENT_ST_REPLYNAME, reply);
	
	CString review = reply + content;
	review.Replace(L"\\", L"\\\\");
	review.Replace(L"\"", L"\\\"");
	
	SYSTEMTIME curTime;
	GetLocalTime(&curTime);
	CString time;
	time.Format(L"%04d%02d%02d%02d%02d%02d", curTime.wYear, curTime.wMonth, curTime.wDay, curTime.wHour, curTime.wMinute, curTime.wSecond);

//AfxMessageBox(review);
	CString sql;
	sql.Format(L"insert into comment values(NULL, %d, %d, \"%s\", \"%s\")", m_nItemID, m_nUserID, time, review);

	//AfxMessageBox(sql);

	if(!m_db.Insert(sql))
		AfxMessageBox(L"Oh no failed");

	SetDlgItemText(IDC_COMMENT_INPUT, L"");
	SetDlgItemText(IDC_COMMENT_ST_REPLYNAME, L"");
	m_btCancelReply.ShowWindow(false);
	Load();
	OnBnClickedCommentBtFirst();
	ShowPage(0);

}


void CCommentDlg::OnBnClickedCommentBtCancelReply()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_COMMENT_ST_REPLYNAME, L"");
	m_btCancelReply.ShowWindow(false);
}


void CCommentDlg::OnBnClickedCommentBtDelete1()
{
	// TODO: 在此添加控件通知处理程序代码
	Delete(0);
}


void CCommentDlg::OnBnClickedCommentBtDelete2()
{
	// TODO: 在此添加控件通知处理程序代码
	Delete(1);
}


void CCommentDlg::OnBnClickedCommentBtDelete3()
{
	// TODO: 在此添加控件通知处理程序代码
	Delete(2);
}


void CCommentDlg::OnBnClickedCommentBtDelete4()
{
	// TODO: 在此添加控件通知处理程序代码
	Delete(3);

}


void CCommentDlg::OnBnClickedCommentBtDelete5()
{
	// TODO: 在此添加控件通知处理程序代码
	Delete(4);
}


void CCommentDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);

	CDC *pDC = GetDC();
	pDC->SelectStockObject(DC_PEN);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SetDCPenColor(m_clrBorder);
	pDC->Rectangle(&rect);

	pDC->FillSolidRect(rect.left, rect.bottom - 30, rect.Width(), 30, m_clrBorder);

	GetDlgItem(IDC_COMMENT_INPUT)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	pDC->MoveTo(rect.left, rect.bottom + 25);
	pDC->LineTo(rect.right + 64, rect.bottom + 25);

	//CRect EDRect;
	//CWnd *pWnd;
	//for(int i = IDC_COMMENT_ED_REVIEW1; i <= IDC_COMMENT_ED_REVIEW5; i++)
	//{
	//	pWnd = GetDlgItem(i);
	//	pDC = pWnd->GetDC();
	//	pWnd->GetClientRect(&EDRect);
	//	//ScreenToClient(&EDRect);
	//	EDRect.top --; EDRect.left--; EDRect.bottom ++; EDRect.right ++;
	//	pDC->SelectStockObject(DC_PEN);
	//	pDC->SelectStockObject(NULL_BRUSH);
	//	pDC->SetDCPenColor(DURIAN_COLOR_ORANGE);
	//	pDC->Rectangle(&EDRect);
	//}

	ReleaseDC(pDC);

	m_btNext.RedrawWindow();
	m_btPrevious.RedrawWindow();
	m_btFirst.RedrawWindow();
	m_btLast.RedrawWindow();
	m_stCurPage.RedrawWindow();
	m_stGoto.RedrawWindow();
	m_edGotoPage.RedrawWindow();
	m_btGoto.RedrawWindow();
	
}


HBRUSH CCommentDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	UINT ctrlID = pWnd->GetDlgCtrlID();
	if(ctrlID <= IDC_COMMENT_ED_REVIEW5 && ctrlID>=IDC_COMMENT_ED_REVIEW1)
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(DURIAN_COLOR_WHITE);
		if(ctrlID == IDC_COMMENT_ED_REVIEW2 || ctrlID == IDC_COMMENT_ED_REVIEW4)
		{
			pDC->SetBkColor(DURIAN_COLOR_GREEN);
			hbr = (HBRUSH) ::CreateSolidBrush(DURIAN_COLOR_GREEN);
		}
		else
		{
			pDC->SetBkColor(DURIAN_COLOR_ORANGE);
			hbr = (HBRUSH) ::CreateSolidBrush(DURIAN_COLOR_ORANGE);
		}
	}
	else if(ctrlID == IDC_COMMENT_ST_PAGE || ctrlID == IDC_COMMENT_ST_GOTO || ctrlID == IDC_COMMENT_ED_GOTOPAGE)
	{
		pDC->SetTextColor(DURIAN_COLOR_WHITE);
		pDC->SetBkColor(m_clrBorder);
		if(ctrlID == IDC_COMMENT_ED_GOTOPAGE)
		{
			pDC->SetBkColor(DURIAN_COLOR_ORANGE);
			return (HBRUSH) ::CreateSolidBrush(DURIAN_COLOR_ORANGE);
		}
		hbr = (HBRUSH) ::CreateSolidBrush(m_clrBorder);
	}
	else if(ctrlID == IDC_COMMENT_ST_TITLE)
	{
		pDC->SetTextColor(DURIAN_COLOR_GREEN);
	}
	
	return hbr;
}


LRESULT CCommentDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);

	return rect.PtInRect(point)? HTCAPTION : CDialogEx::OnNcHitTest(point);
}



void CCommentDlg::OnBnClickedCommentBtGoto()
{
	// TODO: 在此添加控件通知处理程序代码
	int gotopage = GetDlgItemInt(IDC_COMMENT_ED_GOTOPAGE);
	
	if(gotopage < 1)	gotopage = 1;
	if(gotopage > m_nTotalPage + 1)	gotopage = m_nTotalPage + 1;
	
	SetDlgItemInt(IDC_COMMENT_ED_GOTOPAGE, gotopage);
	ShowPage(gotopage - 1);
}


void CCommentDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	if((CWnd *) &m_edGotoPage == GetFocus())
	{
		OnBnClickedCommentBtGoto();
	}

	//CDialogEx::OnOK();
}
