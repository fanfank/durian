// DurianButton.cpp : 实现文件
//

#include "stdafx.h"
//#include "ADO.h"
#include "DurianButton.h"

#define DEFAULE_COLOR_LGREEN RGB(0xD2, 0xF7, 0x00)
#define DEFAULE_COLOR_GREEN  RGB(0x70, 0xE5, 0x00)
#define DEFAULE_COLOR_YELLOW RGB(0xFF, 0xE5, 0x00)
#define DEFAULE_COLOR_DGREEN RGB(0x89, 0xA1, 0x00)
#define DEFAULE_COLOR_WHITE  RGB(0xFF, 0xFF, 0xFF)
#define DEFAULE_COLOR_GRAY	 RGB(0xBD, 0xBD, 0xBD)

// CDurianButton

IMPLEMENT_DYNAMIC(CDurianButton, CButton)

CDurianButton::CDurianButton()
{
	ResetCol();
	m_bHover = false;
	m_bTrack = true;
}

CDurianButton::~CDurianButton()
{
}

void CDurianButton::SetTextCol(COLORREF textCol)
{
	m_clrTextColNormal = textCol;
}

void CDurianButton::ResetCol()
{
	m_clrButtonColDisabled = DURIAN_COLOR_RED;
	m_clrTextColDisabled = DEFAULE_COLOR_WHITE;

	m_clrButtonColDown = DURIAN_COLOR_YELLOW;
	m_clrTextColDown = DEFAULE_COLOR_WHITE;

	m_clrButtonColHoverd = DURIAN_COLOR_GREEN;
	m_clrTextColHoverd = DEFAULE_COLOR_WHITE;

	m_clrButtonColNormal = DURIAN_COLOR_ORANGE;
	m_clrTextColNormal = DEFAULE_COLOR_WHITE;
}


BEGIN_MESSAGE_MAP(CDurianButton, CButton)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// CDurianButton 消息处理程序



void CDurianButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	UINT nButtonState = lpDrawItemStruct->itemState;
	CRect rect;
	GetClientRect(&rect);
	CString text;
	GetWindowText(text);
	

	if(nButtonState & ODS_DISABLED)
	{
		dc.FillRect(rect, &CBrush(m_clrButtonColDisabled));
		dc.SetTextColor(m_clrTextColDisabled);
	}
	else if(nButtonState & ODS_SELECTED)
	{
		dc.FillRect(rect, &CBrush(m_clrButtonColDown));
		dc.SetTextColor(m_clrTextColDown);
	}
	else if(m_bHover)
	{
		dc.FillRect(rect, &CBrush(m_clrButtonColHoverd));
		dc.SetTextColor(m_clrTextColHoverd);
	}
	else
	{
		dc.FillRect(rect, &CBrush(m_clrButtonColNormal));
		dc.SetTextColor(m_clrTextColNormal);
	}
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(text, &rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	dc.Detach();
}


BOOL CDurianButton::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return true;
	//return CButton::OnEraseBkgnd(pDC);
}




void CDurianButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//AfxMessageBox(L"hH");
	if(!m_bHover)
	{
		m_bHover = true;
		Invalidate();
	}

	CButton::OnMouseHover(nFlags, point);
}


void CDurianButton::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//AfxMessageBox(L"hH");
	if(m_bHover)
	{
		m_bHover = false;
		Invalidate();
	}

	m_bTrack = true;

	CButton::OnMouseLeave();
}


void CDurianButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(m_bTrack)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		tme.dwHoverTime = 1;
		::_TrackMouseEvent(&tme);
		m_bTrack = false;
	}

	CButton::OnMouseMove(nFlags, point);
}


void CDurianButton::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CButton::OnLButtonDblClk(nFlags, point);
}


BOOL CDurianButton::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_LBUTTONDBLCLK)
	{
		pMsg->message = WM_LBUTTONDOWN;
	}

	return CButton::PreTranslateMessage(pMsg);
}
