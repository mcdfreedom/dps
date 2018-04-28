#include "Dbmodel.h"


Dbmodel::Dbmodel()
{
	m_conn = NULL;
	m_res = NULL;
	m_row = NULL;
	m_sdbuser = "";
	m_sdbpasswd = "";
	m_sdbip = "";
	m_sdbname = "";
	m_sdbtbname = "";
	m_idbport = 0;
	m_sdbquerysql = "";
}


Dbmodel::~Dbmodel()
{
}

int Dbmodel::initDBInst()
{
	m_conn = mysql_init((MYSQL*)0);
	return m_conn != NULL ? 0 : -1;
}

int Dbmodel::ConnectDBInst(
	const string sDbUser, \
	const string sDbPasswd, \
	const string sDbIp, \
	const string sDbName, \
	const string sDbTbName, \
	unsigned int iDbPort, \
	const string sDbQuerySql){

	m_sdbuser = sDbUser;
	m_sdbpasswd = sDbPasswd;
	m_sdbip = sDbIp;
	m_sdbname = sDbName;
	m_sdbtbname = sDbTbName;
	m_idbport = iDbPort;
	m_sdbquerysql = sDbQuerySql;

	int iRetInit = initDBInst();
	if (iRetInit == -1)
	{
		std::cout << "init kemyond database failed,plase try it later or check your conf\n" << std::endl;
	}
	
	MYSQL * iRet = mysql_real_connect(
		m_conn,\
		m_sdbip.c_str(),\
		m_sdbuser.c_str(), \
		m_sdbpasswd.c_str(),
		m_sdbname.c_str(), \
		iDbPort, \
		NULL, \
		0
		);

	if (m_conn != NULL && iRet){
		if (!mysql_select_db(m_conn, m_sdbname.c_str())) {
			printf("conn kemyond docker's tablename success !\n");
		}
		else
		{
			printf("conn kemyond docker's tablename failed !\n");
		}

	}
	else
	{
		printf("conn kemyond docker's database failed !\n");
		return -1;
	}

	return 0;
}


MYSQL_RES* Dbmodel::GetDbData(string sSql, unsigned int iSqlLen)
{

	int iRet = mysql_real_query(m_conn, sSql.c_str(), sSql.length());
	if (iRet < 0)
	{
		printf("Error fail Errorcode is : %s !!!\n", mysql_error(m_conn));
		return NULL;
	}
	m_res = mysql_store_result(m_conn);//将结果保存在res结构体中
	return m_res;
}

void Dbmodel::CloseDbConn()
{
	mysql_free_result(m_res);
	mysql_close(m_conn);
}
