#pragma once

#define DURIAN_COLOR_YELLOW RGB(0xFC,0xCE, 0x00)
#define DURIAN_COLOR_GREEN RGB(0x8E, 0xC2, 0x1F)
#define DURIAN_COLOR_ORANGE RGB(0xED,0x7B, 0x00)
#define DURIAN_COLOR_RED RGB(0xBD, 0x11, 0x11)
#define DURIAN_COLOR_WHITE RGB(0xFF, 0xFF, 0xFF)
#define DURIAN_COLOR_GRAY RGB(0xBD, 0xBD, 0xBD)
// CDurianButton

class CDurianButton : public CButton
{
	DECLARE_DYNAMIC(CDurianButton)

public:
	CDurianButton();
	virtual ~CDurianButton();
	void SetTextCol(COLORREF textColf);
	void ResetCol();

public:
	COLORREF m_clrTextColNormal;
	COLORREF m_clrTextColDisabled;
	COLORREF m_clrTextColHoverd;
	COLORREF m_clrTextColDown;

	COLORREF m_clrButtonColNormal;
	COLORREF m_clrButtonColDisabled;
	COLORREF m_clrButtonColHoverd;
	COLORREF m_clrButtonColDown;

	bool m_bHover;
	bool m_bTrack;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


