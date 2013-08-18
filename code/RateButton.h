#pragma once
#include "resource.h"


// CRateButton

class CRateButton : public CButton
{
	DECLARE_DYNAMIC(CRateButton)

public:
	CRateButton();
	virtual ~CRateButton();

	CImage m_imgNotHover;
	CImage m_imgHover;
	bool m_bIsHover;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


