// MasterStatic.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MasterStatic.h"


// CMasterStatic

IMPLEMENT_DYNAMIC(CMasterStatic, CStatic)

CMasterStatic::CMasterStatic()
{
	m_colText = RGB(0, 0, 0);
	m_colBK = RGB(0, 0, 255);
	m_bTransp = true;
}

CMasterStatic::~CMasterStatic()
{
}

void CMasterStatic::Set_TextColor(COLORREF textCol)
{
	m_colText = textCol;
	//Invalidate();
}

void CMasterStatic::Set_BkColor(COLORREF bkCol)
{
	m_colBK = bkCol;
	//Invalidate();
}

void CMasterStatic::Set_BkTransparent(bool transp)
{
	m_bTransp = transp;
	//Invalidate();
}


BEGIN_MESSAGE_MAP(CMasterStatic, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CMasterStatic ��Ϣ�������


HBRUSH CMasterStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  �ڴ˸��� DC ���κ�����

	pDC->SetTextColor(m_colText);
	pDC->SetBkColor(m_colBK);
	
	if(m_bTransp)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
		//return (HBRUSH)::GetSysColor(COLOR_BTNFACE);
		
	}
	return (HBRUSH)CBrush(m_colBK);
}


LRESULT CMasterStatic::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(message == WM_SETTEXT)
	{
		CRect rect;
		GetWindowRect(&rect);
		CWnd * pWndParent = GetParent();
		if(pWndParent)
		{
			pWndParent->ScreenToClient(&rect);
			pWndParent->InvalidateRect(&rect);
			//AfxMessageBox(L"invdone");
		}
	}
	return CStatic::DefWindowProc(message, wParam, lParam);
}
