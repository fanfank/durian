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
	parent->GetDlgItem(ctler)->GetWindowRect(&rect);//��ÿռ�ľ�������
    parent->ScreenToClient(&rect);//�������������������
    rect.OffsetRect(CSize(dx,dy));//����Ҫ��Ҫ�ƶ������λ��
    parent->GetDlgItem(ctler)->MoveWindow(rect);//�ƶ���Ŀ��λ��
	//parent->UpdateData(FALSE);
	return true;
}

void CControllerEdit::ShowPicture(CDialog* parent, UINT picCtl, HBITMAP hbm)
{
	CImage img;
	img.Attach(hbm);

	CPaintDC dc(parent); // device context for painting
		// TODO: �ڴ˴������Ϣ����������
	
	CWnd *pWnd = parent->GetDlgItem(picCtl);
	CDC *pDC = pWnd->GetDC();

	CRect rect;
	pWnd->GetClientRect(&rect);
	pWnd->Invalidate(); // ʹ�ؼ�������Ч
	pWnd->UpdateWindow(); // ���¿ؼ�����
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

	img.Detach(); //��Ҫ�����
}