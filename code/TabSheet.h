#pragma once
#include "afxcmn.h"
#define MAXPAGE 5
class CTabSheet :
	public CTabCtrl
{
public:
	CTabSheet(void);
	~CTabSheet(void);
	CDialog* m_pPages[MAXPAGE];
	BOOL AddPage(LPCTSTR title, CDialog *pDialog,UINT ID);
	void Show();
	void SetRect();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	int m_nNumOfPages;
	UINT m_IDD[MAXPAGE];
	LPCTSTR m_Title[MAXPAGE];
	int m_nCurrentPage;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

