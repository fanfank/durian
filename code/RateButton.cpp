// RateButton.cpp : 实现文件
//

#include "stdafx.h"
#include "Durian.h"
#include "RateButton.h"
#include "ControllerEdit.h"


// CRateButton

IMPLEMENT_DYNAMIC(CRateButton, CButton)

CRateButton::CRateButton()
{
	CBitmap bmp;
	bmp.LoadBitmap(IDI_STAR);

	m_imgHover.Attach(HBITMAP(bmp));

	bmp.Detach();
	bmp.LoadBitmap(IDI_PANDA);
	m_imgNotHover.Attach(HBITMAP(bmp));

	m_bIsHover = false;
}

CRateButton::~CRateButton()
{
	m_imgNotHover.Detach();
	m_imgHover.Detach();
}


BEGIN_MESSAGE_MAP(CRateButton, CButton)
	ON_WM_MOUSEHOVER()
END_MESSAGE_MAP()



// CRateButton 消息处理程序




void CRateButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bIsHover = true;

	CButton::OnMouseHover(nFlags, point);
}


void CRateButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	UINT nButtonState = lpDrawItemStruct->itemState;
	CRect rect;
	GetClientRect(&rect);
	/*
	CString text;
	GetWindowText(text);
	*/

	/*
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
	*/

	/*
	if(m_bIsHover)
	{
		dc.FillRect(rect, &CBrush(m_clrButtonColHoverd));
		dc.SetTextColor(m_clrTextColHoverd);
		//CControllerEdit::ShowPicture(
	}
	else
	{
		dc.FillRect(rect, &CBrush(m_clrButtonColNormal));
		dc.SetTextColor(m_clrTextColNormal);
	}
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(text, &rect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	dc.Detach();
	*/
}
