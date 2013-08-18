/******
FileManage.cpp
******/

#include "stdafx.h"
#include "afxinet.h"
#include "string.h"
#include "FileManage.h"
#include "DatabaseADO.h"

#define m_db CDurianApp::m_db
#define m_pRecordSet CDurianApp::m_pRecordSet

BOOL CFileManage::m_bIsFtpConnected=0;
CString CFileManage::ftpUser = L"durian";
CString CFileManage::ftpPasswd = L"444444bb";

CFileManage::CFileManage(void)
{
	
}


CFileManage::~CFileManage(void)
{
}

BOOL CFileManage::DownloadHttp(const CString& strFileURLInServer, const CString& strFileLocalFullPath)
{
	ASSERT(strFileURLInServer != "");
	ASSERT(strFileLocalFullPath != "");

	CInternetSession session;
	CHttpConnection* pHttpConnection = NULL;
	CHttpFile* pHttpFile = NULL;
	CString strServer, strObject;
	INTERNET_PORT wPort;
	DWORD dwType;

	const int nTimeOut = 2000;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //����֮��ĵȴ���ʱ
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);   //���Դ���
	char* pszBuffer = NULL;  

	try
	{
		AfxParseURL(strFileURLInServer, dwType, strServer, strObject, wPort);
		pHttpConnection = session.GetHttpConnection(strServer, wPort);
		pHttpFile = pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject);

		if(pHttpFile->SendRequest() == FALSE)
			return false;

		DWORD dwStateCode;
		pHttpFile->QueryInfoStatusCode(dwStateCode);
		if(dwStateCode == HTTP_STATUS_OK)
		{
			HANDLE hFile = CreateFile(strFileLocalFullPath, GENERIC_WRITE,
			FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);  //���������� ��
			
			if(hFile == INVALID_HANDLE_VALUE)
			{
				pHttpFile->Close();
				pHttpConnection->Close();
				session.Close();
				return false;
			}

			char szInfoBuffer[1000];  //������Ϣ
			DWORD dwFileSize = 0;   //�ļ�����
			DWORD dwInfoBufferSize = sizeof(szInfoBuffer);
			BOOL bResult = FALSE;

			bResult = pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, (void*)szInfoBuffer,&dwInfoBufferSize,NULL);
			dwFileSize = atoi(szInfoBuffer);
			const int BUFFER_LENGTH = 1024 * 10;
			pszBuffer = new char[BUFFER_LENGTH];  //��ȡ�ļ��Ļ���

			DWORD dwWrite, dwTotalWrite;
			dwWrite = dwTotalWrite = 0;
			
			UINT nRead = pHttpFile->Read(pszBuffer, BUFFER_LENGTH); //��ȡ������������
			while(nRead > 0)
			{
				WriteFile(hFile, pszBuffer, nRead, &dwWrite, NULL);  //д�������ļ�
				dwTotalWrite += dwWrite;
				nRead = pHttpFile->Read(pszBuffer, BUFFER_LENGTH);
			}
   
			delete[]pszBuffer;
			pszBuffer = NULL;
			CloseHandle(hFile);
		}

		else
		{
			delete[]pszBuffer;
			pszBuffer = NULL;

			if(pHttpFile != NULL)
			{
				pHttpFile->Close();
				delete pHttpFile;
				pHttpFile = NULL;
			}

			if(pHttpConnection != NULL)
			{
				pHttpConnection->Close();
				delete pHttpConnection;
				pHttpConnection = NULL;
			}
			session.Close();
			return false;
		}
	}

	catch(...)
	{
		delete[]pszBuffer;
		pszBuffer = NULL;
		if(pHttpFile != NULL)
		{
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}

		if(pHttpConnection != NULL)
		{
			pHttpConnection->Close();
			delete pHttpConnection;
			pHttpConnection = NULL;
		}
		session.Close();
		return false;
	}

	if(pHttpFile != NULL)
		pHttpFile->Close();

	if(pHttpConnection != NULL)
		pHttpConnection->Close();

	session.Close();
	return true;
}

BOOL CFileManage::UploadHttp(LPCTSTR strURL, LPCTSTR strLocalFileName)
{
	ASSERT(strURL != NULL && strLocalFileName != NULL);
	BOOL bResult = FALSE;
	DWORD dwType = 0;
	CString strServer;
	CString strObject;
	INTERNET_PORT wPort = 0;
	DWORD dwFileLength = 0;
	char * pFileBuff = NULL;
	CHttpConnection * pHC = NULL;
	CHttpFile * pHF = NULL;
	CInternetSession cis;
	
	bResult =  AfxParseURL(strURL, dwType, strServer, strObject, wPort);
	if(!bResult)
	 return FALSE;
	
	CFile file;
	try
	{
		if(!file.Open(strLocalFileName, CFile::shareDenyNone | CFile::modeRead))
			return FALSE;

		dwFileLength = file.GetLength();
		if(dwFileLength <= 0)
			return FALSE;
		
		pFileBuff = new char[dwFileLength];
		memset(pFileBuff, 0, sizeof(char) * dwFileLength);

		file.Read(pFileBuff, dwFileLength);
		const int nTimeOut = 5000;
		cis.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //���ӳ�ʱ����
		cis.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);  //����1��

		pHC = cis.GetHttpConnection(strServer, wPort);  //ȡ��һ��Http����
		pHF = pHC->OpenRequest(CHttpConnection::HTTP_VERB_POST, strObject);

		if(!pHF->SendRequest(NULL, 0, pFileBuff, dwFileLength))
		{
			delete[]pFileBuff;
			pFileBuff = NULL;
			pHF->Close();
			pHC->Close();
			cis.Close();
			return FALSE;
		}

		//tt
		AfxMessageBox(L"1");

		DWORD dwStateCode = 0;
		pHF->QueryInfoStatusCode(dwStateCode);
		if(dwStateCode == HTTP_STATUS_OK)
		bResult = TRUE;
	}

	catch(CInternetException * pEx)
	{
		//char* sz = new char[256];
		LPTSTR sz = new TCHAR[256];
		pEx->GetErrorMessage(sz, 25);
		CString str;
		str.Format(L"InternetException occur!\r\n%s", sz);
		AfxMessageBox(str);
	}

	catch(CFileException& fe)
	{
		CString str;
		str.Format(L"FileException occur!\r\n%d", fe.m_lOsError);
		AfxMessageBox(str);
	}

	catch(...)
	{
		DWORD dwError = GetLastError();
		CString str;
		str.Format(L"Unknow Exception occur!\r\n%d", dwError);
		AfxMessageBox(str);
	}

	delete[]pFileBuff;
	pFileBuff = NULL;
	file.Close();
	pHF->Close();
	pHC->Close();
	cis.Close();

	return bResult;
}

int CFileManage::MakeDir(CString itemType, CString itemName) //ע��˺�����ʵ����������ʱ·��Ҫ��Ϊ�����ַ
{
	CString sql;
	sql.Format(L"select * from item where item_name=\"%s\" and item_type=\"%c\"",itemName,itemType[0]);
	m_pRecordSet = m_db.Select(sql);

	if(!m_pRecordSet->adoBOF)
		return -1; //�Ѿ����ڸ���Ŀ
	else
	{	
		CString path =L"G:\\�����ļ��У���ҵ�γ����ϵȷŵ����Ժ�\\������ѧ�ڿγ�\\�������\\����\\����׶�\\Durian\\item\\"+itemType+L"\\"+itemName;
		//AfxMessageBox(path);
		return CreateDirectory(path, NULL);
	}
}

BOOL CFileManage::UploadFtp(LPCTSTR ftpURL, LPCTSTR strLocalFileName, LPCTSTR strDestFileName)
{
	if(!m_bIsFtpConnected)
		return FALSE;

	//����CInternetSession������
	CInternetSession* pSession; 

	//��FTP���ӡ�
	CFtpConnection* pConnection; 
	pConnection = NULL;

	pSession = new CInternetSession( AfxGetAppName(), 1, PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		pConnection = pSession->GetFtpConnection(ftpURL, ftpUser, ftpPasswd);
	}
	catch(CInternetException* e)
	{
		e->Delete();
		pConnection = NULL;
		return FALSE;
	}

	if(pConnection != NULL)
	{
		CString dirPath = strDestFileName;
		int dirPos = dirPath.GetLength()-1;
		for(;dirPath[dirPos]!='/';--dirPos)
			dirPath.Delete(dirPos);
		dirPath.Delete(dirPos);

		pConnection->CreateDirectory(dirPath);

		if(!pConnection->PutFile(strLocalFileName, strDestFileName)) //��һ�������Ǳ���������һ����������Ŀ�ĵص�������
		{
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	if(pConnection != NULL)
	{
		pConnection->Close();
		delete pConnection;
	}
	delete pSession;
	return TRUE;
	
}

BOOL CFileManage::DownloadFtp(LPCTSTR ftpURL, LPCTSTR strServerFileName, LPCTSTR strLocalFileName)
{
	if(!m_bIsFtpConnected)
		return FALSE;

	CInternetSession* pSession;
	CFtpConnection* pConnection;
	pConnection = NULL;

	pSession = new CInternetSession( AfxGetAppName(), 1, PRE_CONFIG_INTERNET_ACCESS);
	
	try
	{
		pConnection = pSession->GetFtpConnection(ftpURL, ftpUser, ftpPasswd);
	}
	catch(CInternetException* e)
	{
		e->Delete();
		pConnection = NULL;
		return FALSE;
	}

	if(pConnection != NULL)
	{
		//tmp��item��movie��book��affair���ļ����ڳ�������ʱ���Ѿ�����
		if(!pConnection->GetFile(strServerFileName, strLocalFileName,0))
		{
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	if(pConnection != NULL)
	{
		pConnection->Close();
		delete pConnection;
	}
	delete pSession;
	
	return TRUE;
}

BOOL CFileManage::DeleteItemFtp(LPCTSTR ftpURL, LPCTSTR strServerFileName)
{
	if(!m_bIsFtpConnected)
		return FALSE;

	//����CInternetSession������
	CInternetSession* pSession; 

	//��FTP���ӡ�
	CFtpConnection* pConnection; 
	pConnection = NULL;

	pSession = new CInternetSession( AfxGetAppName(), 1, PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		pConnection = pSession->GetFtpConnection(ftpURL, ftpUser, ftpPasswd);
	}
	catch(CInternetException* e)
	{
		e->Delete();
		pConnection = NULL;
		return FALSE;
	}

	if(pConnection != NULL)
	{
		CString path = strServerFileName;
		
		if(!pConnection->Remove(path))
		{
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
		
		int dirPos = path.GetLength()-1;
		for(;path[dirPos]!='/';--dirPos)
			path.Delete(dirPos);
		path.Delete(dirPos);
		
		if(!pConnection->RemoveDirectoryW(path))
		{
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
		/*
		pConnection->CreateDirectory(dirPath);

		if(!pConnection->PutFile(strLocalFileName, strDestFileName)) //��һ�������Ǳ���������һ����������Ŀ�ĵص�������
		{
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
		*/
	}

	if(pConnection != NULL)
	{
		pConnection->Close();
		delete pConnection;
	}
	delete pSession;
	return TRUE;
}

BOOL CFileManage::TryFtp(LPCTSTR ftpURL)
{
	CInternetSession* pSession; 

	//��FTP���ӡ�
	CFtpConnection* pConnection; 
	pConnection = NULL;

	pSession = new CInternetSession( AfxGetAppName(), 1, PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		pConnection = pSession->GetFtpConnection(ftpURL, ftpUser, ftpPasswd);
	}
	catch(CInternetException* e)
	{
		e->Delete();
		pConnection = NULL;
		return m_bIsFtpConnected = FALSE;
	}

	if(pConnection != NULL)
	{
		pConnection->Close();
		delete pConnection;
	}
	delete pSession;
	return m_bIsFtpConnected = TRUE;
}

BOOL CFileManage::FolderExist(CString strPath)
{
     WIN32_FIND_DATA   wfd;
     BOOL rValue = FALSE;
     HANDLE hFind = FindFirstFile(strPath, &wfd);
    if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY))
    {
              rValue = TRUE;   
     }
     FindClose(hFind);
    return rValue;
}

CString CFileManage::GetSystemTime(bool dateTime)
{
	SYSTEMTIME curTime;
	GetLocalTime(&curTime);
	CString time;
	
	if(dateTime)
		time.Format(L"%04d%02d%02d%02d%02d%02d", curTime.wYear, curTime.wMonth, curTime.wDay, curTime.wHour, curTime.wMinute, curTime.wSecond);
	else
		time.Format(L"%04d%02d%02d", curTime.wYear, curTime.wMonth, curTime.wDay);

	return time;
}