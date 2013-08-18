#pragma once
class CControllerEdit
{
public:
	CControllerEdit(void);
	~CControllerEdit(void);
	//static bool MoveController(CDialog *parent, int dx, int dy);
	static bool MoveController(CDialog* parent, UINT ctler, int dx, int dy);
	static void ShowPicture(CDialog* parent, UINT picCtl, HBITMAP hbm);
};