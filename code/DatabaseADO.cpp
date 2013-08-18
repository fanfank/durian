#include "stdafx.h"
#include "DatabaseADO.h"


CDatabaseADO::CDatabaseADO(void)
{
	::CoInitialize(NULL);
	m_pConnection = NULL;
	m_bIsOpen = false;
}


CDatabaseADO::~CDatabaseADO(void)
{
	if(m_bIsOpen)
	{if(m_pConnection)
		m_pConnection->Close();
	 m_pConnection = NULL;
	 ::CoUninitialize();
	}
}


bool CDatabaseADO::Open(CString strSource, CString username, CString passwd)
{
	/*
	if(addressDlg.DoModal()!=IDOK)
		return false;
	*/

	if(FAILED(m_pConnection.CreateInstance(__uuidof(Connection))))
	{
		AfxMessageBox(L"_Connection ����ʵ����ʧ��");
		return false;
	}

	try
	{  //"DSN=count_head;server=localhost;database=count_head;"
		m_pConnection->Open(strSource.AllocSysString(), username.AllocSysString(), passwd.AllocSysString(), adModeUnknown);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return false;
	}
	
	//m_strDB = addressDlg.m_strDB;
	//m_strFtp = addressDlg.m_strFtp;
	return m_bIsOpen = true;
}


bool CDatabaseADO::Close()
{
	if(m_bIsOpen)
	{if(m_pConnection)
		m_pConnection->Close();
	 m_pConnection = NULL;
	}
	return true;
}


int CDatabaseADO::Select(CString sqlSelect, vector<vector<_variant_t> > &vRecordSet)
{
	if(!m_bIsOpen)
		return 0;

	vRecordSet.clear();
	_RecordsetPtr pRecordSet;
	int nRecord = 0;

	if(FAILED(pRecordSet.CreateInstance(__uuidof(Recordset))))
	{
		AfxMessageBox(L"_Recordset ����ʵ����ʧ��");
		return -1;
	}
	try
	{
		pRecordSet->Open(sqlSelect.AllocSysString(), (IDispatch*)m_pConnection, adOpenDynamic, adLockOptimistic, adCmdText);
		
		if(!pRecordSet->adoBOF)
			pRecordSet->MoveFirst();
		while(!pRecordSet->adoEOF)
		{
			nRecord++;
			vector<_variant_t> vRecord;
			long nFields = pRecordSet->GetFields()->GetCount();
	
			for(long i = 0; i < nFields; i++)
			{
				vRecord.push_back(pRecordSet->GetCollect(i));
			}
			vRecordSet.push_back(vRecord);
			pRecordSet->MoveNext();
		}
		pRecordSet->Close();
		pRecordSet = NULL;
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return -1;
	}
	return nRecord;
}


_RecordsetPtr &CDatabaseADO::Select(CString sqlSelect)
{
	if(FAILED(m_pRecordSet.CreateInstance(__uuidof(Recordset))))
	{
		AfxMessageBox(L"_Recordset ����ʵ����ʧ��");
	}
	try
	{
		if(m_bIsOpen)
			m_pRecordSet->Open(sqlSelect.AllocSysString(), (IDispatch*)m_pConnection, adOpenDynamic, adLockOptimistic, adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	return m_pRecordSet;
}


int CDatabaseADO::Execute(CString sqlExecute)
{
	if(!m_bIsOpen)
		return 0;

	_variant_t nRecordsAffected;
	try
	{
		m_pConnection->Execute(sqlExecute.AllocSysString(), &nRecordsAffected, adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return -1;
	}
	return nRecordsAffected.intVal;
}


int CDatabaseADO::Insert(CString sqlInsert)
{
	return Execute(sqlInsert);
}


int CDatabaseADO::Update(CString sqlUpdate)
{
	return Execute(sqlUpdate);
}


int CDatabaseADO::Delete(CString sqlDelete)
{
	return Execute(sqlDelete);
}


CString _VariantToCString(_variant_t var)
{
    CString strValue;  
    switch (var.vt)  
    {  
    case VT_BSTR: //�ַ���  
    case VT_LPSTR:  
    case VT_LPWSTR:  
        strValue = (LPCTSTR)(_bstr_t)var;  
        break;  
    case VT_I1:   //�޷����ַ�  
    case VT_UI1:  
        strValue.Format(_T("%d"), var.bVal);  //AfxMessageBox(L"UI1");
        break;  
    case VT_I2:   //������  
        strValue.Format(_T("%d"), var.iVal);  //AfxMessageBox(L"UI2");
        break;  
    case VT_UI2:   //�޷��Ŷ�����  
        strValue.Format(_T("%u"), var.uiVal);  //AfxMessageBox(L"UI3");
        break;  
    case VT_INT: //����  
        strValue.Format(_T("%d"), var.intVal);  //AfxMessageBox(L"UI4");
        break;  
    case VT_I4:   //����  
    case VT_I8:   //������  
        strValue.Format(_T("%d"), var.lVal);  //AfxMessageBox(L"UI5");
        break;  
    case VT_UINT:   //�޷�������  
        strValue.Format(_T("%d"), var.uintVal);  //AfxMessageBox(L"UI6");
        break;  
    case VT_UI4:    //�޷�������  
    case VT_UI8:    //�޷��ų�����  
        strValue.Format(_T("%d"), var.ulVal);  //AfxMessageBox(L"UI7");
        break;  
    case VT_VOID:  
        strValue.Format(_T("%08x"), var.byref);  //AfxMessageBox(L"UI8");
        break;  
    case VT_R4:   //������  
        strValue.Format(_T("%f"), var.fltVal);  //AfxMessageBox(L"UI9");
        break;  
    case VT_R8:   //˫������  
        strValue.Format(_T("%f"), var.dblVal);  //AfxMessageBox(L"UI10");
        break;  
    case VT_DECIMAL: //С��  
        strValue.Format(_T("%f"), (double)var);  //AfxMessageBox(L"UI11");
        break;  
    case VT_CY:  
        {  
            COleCurrency cy = var.cyVal;  
            strValue = cy.Format();  
        }  
        break;  
    case VT_BLOB:  
    case VT_BLOB_OBJECT:  
    case 0x2011:  
        strValue = _T("[BLOB]");  
        break;  
    case VT_BOOL:   //������    
        strValue = var.boolVal ? _T("TRUE") : _T("FALSE");  
        break;  
    case VT_DATE: //������  
        {  
            DATE dt = var.date;  
            COleDateTime da = COleDateTime(dt);  
            strValue = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
        }  
        break;  
    case VT_NULL://NULLֵ  
    case VT_EMPTY:   //��  
        strValue = _T("");  
        break;  
    case VT_UNKNOWN:   //δ֪����  
    default:  
        strValue = _T("VT_UNKNOW");  
        break;  
    }  
      
    return strValue;  
}
