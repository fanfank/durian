#pragma once
#include "afxwin.h"
class CScrollDialog :
	public CDialog
{
public:
	/*CScrollDialog(void);
	~CScrollDialog(void);*/

	// Construction
public:
	CScrollDialog();   // standard constructor
	CScrollDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	CScrollDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);

	virtual ~CScrollDialog();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScrollDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void ScrollClient(int nBar, int nPos);
	void HVScrool(int nBar, UINT nSBCode);
	int GetScrollPos(int nBar, UINT nSBCode);
};

