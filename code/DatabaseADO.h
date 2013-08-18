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

/*函数与数据库建立链接，注意在使用Open建立链接后，在下一次调用Open函数之前需要先调用Close函数将旧链接关闭
  参数含义：
  strSource 指在ODBC数据源中建立的数据源的名称（MySQL）
  username 数据库的用户名
  passwd 密码*/
  //"DSN=count_head;server=localhost;database=count_head;"
	bool Open(CString strSource /*= L"DSN=durian;server=localhost;database=durian"*/, CString username /*= L"root"*/, CString passwd /*= L"444444"*/);

/*关闭数据库链接的函数；每次Open后都要Close*/
	bool Close(void);

/*若执行成功，返回记录的数目，否则返回-1
  sqlSelect SELECT语句   
  vRecordSet 若函数执行成功，则结果集储存在vRecordSet中，内向量的元素为一条记录各个域的值，外向量的元素为记录
  注意，无论函数执行是否成功，vRecordSet中原有的内容都会被清空！！*/
	int Select(CString sqlSelect, vector<vector<_variant_t> > &vRecordSet);

/*若执行成功，返回记录集指针，否则返回NULL
  sqlSelect SELECT语句*/
	_RecordsetPtr &Select(CString sqlSelect);

/*若执行成功，返回插入的条目的数目，否则返回-1
  sqlInsert INSERT语句*/
	int Insert(CString sqlInsert);

/*若执行成功，返回更新的条目的数目，否则返回-1
  sqlUpdate UPDATE语句*/
	int Update(CString sqlUpdate);

/*若执行成功，返回删除的条目的数目，否则返回-1
  sqlDelete DELETE语句*/
	int Delete(CString sqlDelete);
	
private:
	int Execute(CString sqlExecute);
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordSet;
	
};


/*提供一个静态函数用于将_variant_t类型的变量转换为CString字符串，方便输出*/
CString _VariantToCString(_variant_t var);
