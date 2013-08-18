#pragma once
#include<vector>
#include "afxwin.h"
#include "DurianButton.h"
using std::vector;


// CItemDetailDlg 对话框

class CItemDetailDlg : public CDialog
{
	DECLARE_DYNAMIC(CItemDetailDlg)

public:
	CItemDetailDlg(bool isAdmin, HBITMAP hbm, vector<_variant_t> vectorItem, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CItemDetailDlg();

	//CImage m_img;
	HBITMAP m_hbm;
	bool m_bIsAdmin;
	vector<_variant_t> m_vectorItem;
	int m_iRate;
	int m_iCurRate;
	int m_iRateNum;
	double m_fTotalRate;

	CImage m_imgStar;
	CImage m_imgBStar;

// 对话框数据
	enum { IDD = IDD_ITEM_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedItemDetailComment();
private:
	CDurianButton m_btDelete;
	CDurianButton m_btComment;
	CDurianButton m_btCancel;
	CDurianButton m_btClose;

	CStatic m_stTitile;
	//virtual void OnOK();
	
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);
private:
public:
	afx_msg void OnBnClickedItemDetailClose();
	afx_msg void OnBnClickedPressOk();
	//CStatic m_picStar1;
	afx_msg void OnStnClickedStar1();
	afx_msg void OnStnClickedStar2();
	afx_msg void OnStnClickedStar3();
	afx_msg void OnStnClickedStar4();
	afx_msg void OnStnClickedStar5();

	void SynchornizeDB();
	CDurianButton m_btnRate;
	afx_msg void OnBnClickedRate();
	afx_msg void OnBnClickedItemDetailDelete();
};
