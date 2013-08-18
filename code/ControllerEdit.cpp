#include "stdafx.h"
#include "afxdialogex.h"
#include "ControllerEdit.h"


CControllerEdit::CControllerEdit(void)
{
}


CControllerEdit::~CControllerEdit(void)
{
}


bool CControllerEdit::MoveController(CDialog* parent, UINT ctler, int dx, int dy)
{
	CRect rect;
	parent->GetDlgItem(ctler)->GetWindowRect(&rect);//获得空间的绝对坐标
    parent->ScreenToClient(&rect);//获得相对于主窗体的坐标
    rect.OffsetRect(CSize(dx,dy));//这里要是要移动的相对位置
    parent->GetDlgItem(ctler)->MoveWindow(rect);//移动到目标位置
	//parent->UpdateData(FALSE);
	return true;
}

void CControllerEdit::ShowPicture(CDialog* parent, UINT picCtl, HBITMAP hbm)
{
	CImage img;
	img.Attach(hbm);

	CPaintDC dc(parent); // device context for painting
		// TODO: 在此处添加消息处理程序代码
	
	CWnd *pWnd = parent->GetDlgItem(picCtl);
	CDC *pDC = pWnd->GetDC();

	CRect rect;
	pWnd->GetClientRect(&rect);
	pWnd->Invalidate(); // 使控件窗口无效
	pWnd->UpdateWindow(); // 更新控件窗口
	//pDC->Rectangle(&rect);

	pDC->SetStretchBltMode(HALFTONE);
	pDC->SelectStockObject(DC_PEN);
	pDC->SelectStockObject(DC_BRUSH);
	pDC->SetDCPenColor(RGB(240, 240, 240));
	pDC->SetDCBrushColor(RGB(240, 240, 240));
	
	pDC->Rectangle(&rect);
  
	int actualHeight, actualWidth;

	if( (float(img.GetWidth())/img.GetHeight())> ( (float(rect.Width()))/rect.Height()))
	{
		actualHeight = img.GetHeight()*rect.Width()/img.GetWidth();
		img.StretchBlt(pDC->m_hDC, rect.left, rect.Height()/2 - actualHeight/2, rect.Width(), actualHeight, 0, 0, img.GetWidth(), img.GetHeight(), SRCCOPY);
	}
	else
	{
		actualWidth = img.GetWidth()*rect.Height()/img.GetHeight();
		img.StretchBlt(pDC->m_hDC, rect.Width()/2 - actualWidth/2, rect.top, actualWidth, rect.Height(), 0, 0, img.GetWidth(), img.GetHeight(), SRCCOPY);
	}
	//img.StretchBlt(pDC->m_hDC, rect.left, rect.top, img.GetWidth(), img.GetHeight(), 0, 0, img.GetWidth(), img.GetHeight(), SRCCOPY);
	ReleaseDC(pWnd->m_hWnd, pDC->m_hDC);

	img.Detach(); //需要这个吗？
}