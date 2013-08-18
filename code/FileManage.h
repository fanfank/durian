#include "durian.h"

#pragma once
class CFileManage
{
public:
	CFileManage(void);
	~CFileManage(void);
	static LPCTSTR ftpURL;
	static CString ftpUser;
	static CString ftpPasswd;

	static BOOL m_bIsFtpConnected;
	static BOOL UploadFtp(LPCTSTR ftpURL, LPCTSTR strLocalFileName, LPCTSTR strDestFileName);
	static BOOL UploadHttp(LPCTSTR strURL, LPCTSTR strLocalFileName);
	static BOOL DownloadFtp(LPCTSTR ftpURL, LPCTSTR strServerFileName, LPCTSTR strLocalFileName);
	static BOOL DownloadHttp(const CString& strFileURLInServer, const CString& strFileLocalFullPath);
	static BOOL DeleteItemFtp(LPCTSTR ftpURL, LPCTSTR strServerFileName);
	static BOOL TryFtp(LPCTSTR ftpURL);

	static CString GetSystemTime(bool dateTime);
	static BOOL FolderExist(CString strPath);
	static int MakeDir(CString itemType, CString itemName);
};

