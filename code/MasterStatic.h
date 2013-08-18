#pragma once


// CMasterStatic

class CMasterStatic : public CStatic
{
	DECLARE_DYNAMIC(CMasterStatic)

public:
	CMasterStatic();
	virtual ~CMasterStatic();
	void Set_TextColor(COLORREF textColf);
	void Set_BkColor(COLORREF bkCol);
	void Set_BkTransparent(bool transp);

private:
	COLORREF m_colText;
	COLORREF m_colBK;
	bool	 m_bTransp;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


