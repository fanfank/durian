// AuthorInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Durian.h"
#include "AuthorInfoDlg.h"
#include "afxdialogex.h"


// CAuthorInfoDlg 对话框

IMPLEMENT_DYNAMIC(CAuthorInfoDlg, CDialogEx)

CAuthorInfoDlg::CAuthorInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAuthorInfoDlg::IDD, pParent)
{

}

CAuthorInfoDlg::~CAuthorInfoDlg()
{
}

void CAuthorInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAuthorInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CAuthorInfoDlg 消息处理程序
