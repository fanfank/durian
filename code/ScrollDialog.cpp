// ScrollDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ScrollDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScrollDialog dialog

CScrollDialog::CScrollDialog()
	: CDialog()
{
}

CScrollDialog::CScrollDialog(UINT nIDTemplate, CWnd* pParentWnd)
	: CDialog(nIDTemplate, pParentWnd)
{
}

CScrollDialog::CScrollDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
	: CDialog(lpszTemplateName, pParentWnd)
{
}

CScrollDialog::~CScrollDialog()
{
}

void CScrollDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScrollDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScrollDialog, CDialog)
	//{{AFX_MSG_MAP(CScrollDialog)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollDialog message handlers

BOOL CScrollDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rc;
    GetClientRect(&rc);

    const SIZE sz = { rc.right - rc.left, rc.bottom - rc.top };

    SCROLLINFO si;
    si.cbSize = sizeof(SCROLLINFO);
    si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE;
    si.nPos = si.nMin = 1;

    si.nMax = sz.cx;
    si.nPage = sz.cx;
    SetScrollInfo(SB_HORZ, &si, FALSE);

    si.nMax = sz.cy;
    si.nPage = sz.cy;
    SetScrollInfo(SB_VERT, &si, FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScrollDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(nType != SIZE_RESTORED && nType != SIZE_MAXIMIZED)
        return;

    SCROLLINFO si;
    si.cbSize = sizeof(SCROLLINFO);

    const int bar[] = { SB_HORZ, SB_VERT };
    const int page[] = { cx, cy };

    for(size_t i = 0; i < ARRAYSIZE(bar); ++i)
    {
        si.fMask = SIF_PAGE;
        si.nPage = page[i];
        SetScrollInfo(bar[i], &si, TRUE);

        si.fMask = SIF_RANGE | SIF_POS;
        GetScrollInfo(bar[i], &si);

        const int maxScrollPos = si.nMax - (page[i] - 1);

        const bool needToScroll =
            (si.nPos != si.nMin && si.nPos == maxScrollPos) ||
            (nType == SIZE_MAXIMIZED);

        if(needToScroll)
        {
            ScrollClient(bar[i], si.nPos);
        }
    }
}

void CScrollDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	HVScrool(SB_HORZ,nSBCode);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CScrollDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	HVScrool(SB_VERT,nSBCode);
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CScrollDialog::ScrollClient(int nBar, int nPos)
{
    static int s_prevx = 1;
    static int s_prevy = 1;

    int cx = 0;
    int cy = 0;

    int& delta = (nBar == SB_HORZ ? cx : cy);
    int& prev = (nBar == SB_HORZ ? s_prevx : s_prevy);

    delta = prev - nPos;
    prev = nPos;

    if(cx || cy)
    {
        ScrollWindow(cx, cy, NULL, NULL);
    }
}

void CScrollDialog::HVScrool(int nBar, UINT nSBCode)
{
	const int scrollPos = GetScrollPos(nBar,nSBCode);

    if(scrollPos == -1)
        return;

    SetScrollPos(nBar, scrollPos, TRUE);
    ScrollClient(nBar, scrollPos);
}

int CScrollDialog::GetScrollPos(int nBar, UINT nSBCode)
{
    SCROLLINFO si;
    si.cbSize = sizeof(SCROLLINFO);
    si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;
    GetScrollInfo(nBar, &si);

    const int minPos = si.nMin;
    const int maxPos = si.nMax - (si.nPage - 1);

    int result = -1;

    switch(nSBCode)
    {
    case SB_LINEUP /*SB_LINELEFT*/:
        result = max(si.nPos - 1, minPos);
        break;
    case SB_LINEDOWN /*SB_LINERIGHT*/:
        result = min(si.nPos + 1, maxPos);
        break;
    case SB_PAGEUP /*SB_PAGELEFT*/:
        result = max(si.nPos - (int)si.nPage, minPos);
        break;
    case SB_PAGEDOWN /*SB_PAGERIGHT*/:
        result = min(si.nPos + (int)si.nPage, maxPos);
        break;
    case SB_THUMBPOSITION:
        // do nothing
        break;
    case SB_THUMBTRACK:
        result = si.nTrackPos;
        break;
    case SB_TOP /*SB_LEFT*/:
        result = minPos;
        break;
    case SB_BOTTOM /*SB_RIGHT*/:
        result = maxPos;
        break;
    case SB_ENDSCROLL:
        // do nothing
        break;
    }

    return result;
}
