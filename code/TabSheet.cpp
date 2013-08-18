#include "stdafx.h"
#include "TabSheet.h"


CTabSheet::CTabSheet(void)
{
	m_nNumOfPages = 0;
	m_nCurrentPage = 0;
}


CTabSheet::~CTabSheet(void)
{
}

BOOL CTabSheet::AddPage(LPCTSTR title, CDialog *pDialog,UINT ID)
{
	if( MAXPAGE == m_nNumOfPages )
		return FALSE;
	//����Ŀǰ�ܵ��ӶԻ�����
	m_nNumOfPages++;
	//��¼�ӶԻ����ָ�롢��ԴID��Ҫ�ڱ�ǩ����ʾ������
	m_pPages[m_nNumOfPages-1] = pDialog;
	m_IDD[m_nNumOfPages-1] = ID;
	m_Title[m_nNumOfPages-1] = title;
	return TRUE;
}

void CTabSheet::Show()
{
	//����CDialog::Create�������ӶԻ��򣬲���ʹ��CTabCtrl::InsertItem��������Ӧ�ı�ǩ
	for( int i=0; i < m_nNumOfPages; i++ )
	{
		m_pPages[i]->Create( m_IDD[i], this );
		InsertItem( i, m_Title[i] );
	}
	//���ڶԻ�����ʾʱĬ�ϵ��ǵ�һ����ǩ��ѡ�У�����Ӧ���õ�һ���ӶԻ�����ʾ�������ӶԻ�������
	m_nCurrentPage = 0;
	m_pPages[0]->ShowWindow(SW_SHOW);
	for(int i=1; i < m_nNumOfPages; i++)
		m_pPages[i]->ShowWindow(SW_HIDE);
	SetRect();
}

void CTabSheet::SetRect()
{
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;
	//�õ�Tab Control�Ĵ�С
	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);
	//��������ӶԻ���������Tab Control��λ�úʹ�С
	nX=itemRect.left;
	nY=itemRect.bottom+1;
	nXc=tabRect.right-itemRect.left-2;
	nYc=tabRect.bottom-nY-2;
	//���ü���������ݶԸ��ӶԻ�����е���
	m_pPages[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
		for( int nCount=1; nCount < m_nNumOfPages; nCount++ )
	m_pPages[nCount]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
}




BEGIN_MESSAGE_MAP(CTabSheet, CTabCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


void CTabSheet::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�ж��Ƿ񵥻���������ǩ
	/*
	if(m_nCurrentPage != GetCurFocus())
	{
		//��ԭ�ȵ��ӶԻ�������
		m_pPages[m_nCurrentPage]->ShowWindow(SW_HIDE);
		m_nCurrentPage=GetCurFocus();
		//��ʾ��ǰ��ǩ����Ӧ���ӶԻ���
		m_pPages[m_nCurrentPage]->ShowWindow(SW_SHOW);

		if(m_nCurrentPage == 0)
			MessageBox(L"0",L"0");
		else if(m_nCurrentPage == 1)
			MessageBox(L"1",L"1");
		else
			MessageBox(L"2",L"2");
	}
	*/

	CTabCtrl::OnLButtonDown(nFlags, point);
}


void CTabSheet::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_nCurrentPage != GetCurFocus())
	{
		//��ԭ�ȵ��ӶԻ�������
		m_pPages[m_nCurrentPage]->ShowWindow(SW_HIDE);
		m_nCurrentPage=GetCurFocus();
		//��ʾ��ǰ��ǩ����Ӧ���ӶԻ���
		m_pPages[m_nCurrentPage]->ShowWindow(SW_SHOW);
	}

	CTabCtrl::OnLButtonUp(nFlags, point);
}
