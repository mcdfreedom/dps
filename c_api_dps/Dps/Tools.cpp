
#include "tools.h"
#include <stdarg.h>

using namespace _sql_;



bool CTools::initmysql(const char* pIP,
	const char* pUser,
	const char* pPwd,
	const char* pDatabase,
	unsigned short nPort /* = 3306 */)
{
	//mysql��ʼ��
	mysql_init(&Mysql);
	//�������ݿ�
	if (!mysql_real_connect(&Mysql, pIP, pUser, pPwd, pDatabase, nPort, NULL, CLIENT_MULTI_STATEMENTS))
	{
		m_bOpen = false;
		return m_bOpen;
	}
	mysql_query(&Mysql, "SET NAMES 'utf8'");
	mysql_query(&Mysql, "set global max_connections=4000");//�����������������mysql������Ĭ��Ϊ151  ���������ҵ������ļ� ֻ������취����
	mysql_options(&Mysql, MYSQL_READ_DEFAULT_GROUP, "IMServer");
	m_bOpen = true;
	return m_bOpen;

}

bool CTools::select_sql_beack(__in const char *pSQL, __out ...)
{
	va_list ap;
	va_start(ap, pSQL);
	bool bRet = SelectBeack(pSQL, e_char, ap);
	va_end(ap);
	return bRet;
}

bool CTools::select_sql_beack_s(__in const char *pSQL, __out ...)
{
	va_list ap;
	va_start(ap, pSQL);
	bool bRet = SelectBeack(pSQL, e_string, ap);
	va_end(ap);
	return bRet;
}

bool CTools::SelectBeack(__in const char *pSQL, e_strType nstrType, __out va_list ap)
{
	MYSQL_ROW row;				//����
	MYSQL_RES *pResult = NULL;	//��¼��ָ��
	unsigned int num_fields;	//�ֶθ���
	MYSQL_FIELD* pFields;		//�ֶ�������Ϣ

	if (!m_bOpen)
	{
		return false;
	}
	try
	{
		if (m_strOldSql != pSQL)
		{
			//û�в�ѯ��SQL�½���ѯ
			ClearResult();//�����¼������
			g_mtxmysql.lock();
			if (!(mysql_query(&Mysql, pSQL) == 0))
			{
				//��ѯʧ��
				g_mtxmysql.unlock();
				return false;
			}
			//��ѯ����
			pResult = mysql_use_result(&Mysql);
			g_mtxmysql.unlock();
			int nCount = mysql_field_count(&Mysql);
			if (!pResult)
			{
				return false;
			}
			m_strOldSql = pSQL;
			//m_strOldSql.Format("%s", pSQL);
		}
		else
		{
			pResult = m_pResult;
		}

		int *pnType = NULL;
		string *pstrType = NULL;
		char * pszType = NULL;

		num_fields = mysql_num_fields(pResult);
		//��ȡһ������
		if (!(row = mysql_fetch_row(pResult)))
		{
			ClearResult();
			return false;
		}
		for (unsigned int i = 0; i<num_fields; i++)
		{
			pFields = mysql_fetch_field_direct(pResult, i);//��ȡ��ǰ�ֶ���Ϣ
			enum_field_types nfieldtype = pFields->type;
			switch (nfieldtype)
			{
				//ת����  //������С����Ļ�û�������� ��Ҫ��һ������
			case MYSQL_TYPE_SHORT:
			case MYSQL_TYPE_LONG:
			case MYSQL_TYPE_INT24:
			case MYSQL_TYPE_LONGLONG:
			case MYSQL_TYPE_FLOAT:
			case MYSQL_TYPE_DOUBLE:
			{
									  pnType = va_arg(ap, int *);
									  if (pnType == NULL)
									  {
										  break;
									  }
									  if (row[i] == NULL)
									  {
										  *pnType = 0;
									  }
									  else
									  {
										  *pnType = atoi(row[i]);
									  }

			}
				break;
				//ת�ַ�����
			case MYSQL_TYPE_DATE:
			case MYSQL_TYPE_TIME:
			case MYSQL_TYPE_DATETIME:
			case MYSQL_TYPE_STRING:
			case MYSQL_TYPE_TINY:
			case MYSQL_TYPE_VAR_STRING:
			{
										  if (nstrType == e_string)
										  {
											  pstrType = va_arg(ap, string *);
											  if (pstrType == NULL)
											  {
												  break;
											  }
											  if (row[i] == NULL)
											  {
												  *pstrType = "";
											  }
											  else
											  {
												  *pstrType = row[i];
											  }

										  }
										  else
										  {
											  pszType = va_arg(ap, char *);
											  if (pszType == NULL)
											  {
												  break;
											  }
											  if (row[i] == NULL)
											  {
												  pszType[0] = 0;
											  }
											  else
											  {
												  strcpy(pszType, row[i]);
											  }
										  }

			}
				break;
			default:
			{
					   // ��δԤ�ϵ������͡��Ѳ���ָ������ƣ�
					   pszType = va_arg(ap, char *);

			}
				break;
			}
		}
	}
	catch (...)
	{
		ClearResult();
		return false;
	}
	m_pResult = pResult;
	return true;
}

bool CTools::execute(const char* pSQL)
{
	assert(pSQL);
	try
	{
		int nRet = mysql_query(&Mysql, pSQL);
		if (nRet != 0)
		{
			const char* pError = NULL;
			pError = mysql_error(&Mysql);
			printf("MYSQL������ʾ%s\r\n", pError);
			return false;
		}
	}
	catch (...)
	{
		return false;
	}
	return true;

}

MYSQL_RES * _sql_::CTools::GetDbData(string sSql, unsigned int iSqlLen)
{

	int iRet = mysql_real_query(&Mysql, sSql.c_str(), sSql.length());
	if (iRet < 0)
	{
		printf("Error fail Errorcode is : %s !!!\n", mysql_error(&Mysql));
		return NULL;
	}
	m_pResult = mysql_store_result(&Mysql);//�����������res�ṹ����
	return m_pResult;
}

bool CTools::delete_sql(__in const char *pSQL)
{
	return execute(pSQL);
}

bool CTools::update_sql(const char *pSQL)
{

	return execute(pSQL);
}

bool CTools::insert_sql(const char *pSQL)
{

	return execute(pSQL);
}


void _sql_::CTools::AutoCommitSQL(BOOL bAuto /*= TRUE*/)
{
	mysql_autocommit(&Mysql, bAuto);
}

string CTools::GetBinPath()
{
	char *buff = new char[BUFSIZ];
	string sPath = _getcwd(buff, 1000);
	return sPath;
}


WCHAR* CTools::ToWChar(char *str)
{
	static WCHAR buffer[1024];
	memset(buffer, 0, 1024);
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str), buffer, 1024);
	return buffer;
}




/************************************************************************/
/*			MYSQL ���ӳ�                                    */
/************************************************************************/
mysql_connection_pool::mysql_connection_pool()
{
	memset(_sql_::mysql_connection_pool::m_szIP, 0, sizeof(_sql_::mysql_connection_pool::m_szIP));
	memset(_sql_::mysql_connection_pool::m_szPwd, 0, sizeof(_sql_::mysql_connection_pool::m_szPwd));
	memset(_sql_::mysql_connection_pool::m_szDatabase, 0, sizeof(_sql_::mysql_connection_pool::m_szDatabase));
	memset(_sql_::mysql_connection_pool::m_szUser, 0, sizeof(_sql_::mysql_connection_pool::m_szUser));
	m_snPort = 0;
}



mysql_connection_pool::~mysql_connection_pool()
{
	DestoryConnPool();
}

mysql_connection_pool * mysql_connection_pool::GetInstance()
{
	static mysql_connection_pool object;
	return &object;
}

CTools * mysql_connection_pool::GetConnection()
{
	g_mtxMysqlPool.lock();
	CTools *pMysqlobject = NULL;
	if (the_queue.empty())
	{
		g_mtxMysqlPool.unlock();
		return pMysqlobject;
	}
	pMysqlobject = the_queue.front();
	the_queue.pop();
	g_mtxMysqlPool.unlock();
	return pMysqlobject;
}

int _sql_::mysql_connection_pool::InitConnection(int nInitialSize/*=1*/)
{
	assert(nInitialSize > 0);
	g_mtxMysqlPool.lock();
	for (int i = 0; i<nInitialSize; i++)
	{
		CTools *pObject = new CTools;
		if (!pObject->initmysql(m_szIP, m_szUser, m_szPwd, m_szDatabase, m_snPort))
		{
			delete pObject;
			pObject = NULL;
			continue;
		}
		/*
		*  ʹ���� ����ִ��SQLǰ��Ҫִ��START TRANSACTION�﷨ʹ��������
		*
		*  ʹ���� ����Ҫ����SQLִ����ɺ󷽿�ִ��COMMIT�﷨ ʹ������һ���ύ
		*/
		pObject->AutoCommitSQL(FALSE);//�ر��Զ��ύ ���������ύ
		the_queue.push(pObject);
	}
	int nSize = the_queue.size();
	g_mtxMysqlPool.unlock();
	return nSize;
}

void _sql_::mysql_connection_pool::SetDatabaseInfo(const char* pIP, const char* pUser, const char* pPwd, const char* pDatabase, unsigned short nPort /* = 3306 */)
{
	assert(pIP != NULL);
	assert(pUser != NULL);
	assert(pPwd != NULL);
	assert(pDatabase != NULL);
	g_mtxMysqlPool.lock();
	memcpy(m_szIP, pIP, strlen(pIP));
	memcpy(m_szUser, pUser, strlen(pUser));
	memcpy(m_szPwd, pPwd, strlen(pPwd));
	memcpy(m_szDatabase, pDatabase, strlen(pDatabase));
	m_snPort = nPort;
	g_mtxMysqlPool.unlock();
}

void mysql_connection_pool::ReleaseConnection(CTools * pObject)
{
	assert(pObject);
	g_mtxMysqlPool.lock();
	the_queue.push(pObject);
	g_mtxMysqlPool.unlock();
}

void mysql_connection_pool::DestoryConnPool() {
	g_mtxMysqlPool.lock();
	if (!the_queue.empty())
	{
		CTools *pMysqlobject = the_queue.front();
		the_queue.pop();
		pMysqlobject->insert_sql("COMMIT");
		delete pMysqlobject;
		pMysqlobject = NULL;
	}
	g_mtxMysqlPool.unlock();
}