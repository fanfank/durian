#pragma once
#import "C:\Program Files\common files\system\ado\msado15.dll" no_namespace rename("EOF", "adoEOF") rename("BOF", "adoBOF")
#include <vector>
#include "AddressDlg.h"
using namespace std;

class CDatabaseADO
{
public:
	CAddressDlg addressDlg;
	CString m_strDB;
	CString m_strFtp;
	bool m_bIsOpen;

public:
	CDatabaseADO(void);
	~CDatabaseADO(void);

/*���������ݿ⽨�����ӣ�ע����ʹ��Open�������Ӻ�����һ�ε���Open����֮ǰ��Ҫ�ȵ���Close�����������ӹر�
  �������壺
  strSource ָ��ODBC����Դ�н���������Դ�����ƣ�MySQL��
  username ���ݿ���û���
  passwd ����*/
  //"DSN=count_head;server=localhost;database=count_head;"
	bool Open(CString strSource /*= L"DSN=durian;server=localhost;database=durian"*/, CString username /*= L"root"*/, CString passwd /*= L"444444"*/);

/*�ر����ݿ����ӵĺ�����ÿ��Open��ҪClose*/
	bool Close(void);

/*��ִ�гɹ������ؼ�¼����Ŀ�����򷵻�-1
  sqlSelect SELECT���   
  vRecordSet ������ִ�гɹ���������������vRecordSet�У���������Ԫ��Ϊһ����¼�������ֵ����������Ԫ��Ϊ��¼
  ע�⣬���ۺ���ִ���Ƿ�ɹ���vRecordSet��ԭ�е����ݶ��ᱻ��գ���*/
	int Select(CString sqlSelect, vector<vector<_variant_t> > &vRecordSet);

/*��ִ�гɹ������ؼ�¼��ָ�룬���򷵻�NULL
  sqlSelect SELECT���*/
	_RecordsetPtr &Select(CString sqlSelect);

/*��ִ�гɹ������ز������Ŀ����Ŀ�����򷵻�-1
  sqlInsert INSERT���*/
	int Insert(CString sqlInsert);

/*��ִ�гɹ������ظ��µ���Ŀ����Ŀ�����򷵻�-1
  sqlUpdate UPDATE���*/
	int Update(CString sqlUpdate);

/*��ִ�гɹ�������ɾ������Ŀ����Ŀ�����򷵻�-1
  sqlDelete DELETE���*/
	int Delete(CString sqlDelete);
	
private:
	int Execute(CString sqlExecute);
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordSet;
	
};


/*�ṩһ����̬�������ڽ�_variant_t���͵ı���ת��ΪCString�ַ������������*/
CString _VariantToCString(_variant_t var);
