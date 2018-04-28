/*!
* \file		dbmodel.h
* \author	lidong
* \date		2018/04/14
* \copyright	Copyright(c) kemyond 2015, All rights reserved.
*
* \brief info类表操作
*
*/
#ifndef _DB_MODEL_H_
#define _DB_MODEL_H_

#include <mysql.h>
#include <string>
//#include <list>
//#include <vector>
#include <iostream>

//using namespace std;
using std::string;
//using std::list;
//using std::vector;

class Dbmodel
{
public:
	Dbmodel();
	~Dbmodel();
public:
private:
	MYSQL * m_conn; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES * m_res;//存放查询结果
	MYSQL_ROW m_row;
//私有变量
private:
	string m_sdbuser;
	string m_sdbpasswd;
	string m_sdbip;
	string m_sdbname;
	string m_sdbtbname;
	unsigned int m_idbport;
	string m_sdbquerysql;
//共有方法
public:
	int initDBInst();
	int ConnectDBInst(
		const string sDbUser, \
		const string sDbPasswd, \
		const string sDbIp, \
		const string sDbName, \
		const string sDbTbName, \
		unsigned int iDbPort, \
		const string sDbQuerySql
		);

	MYSQL_RES* GetDbData(string sSql, unsigned int iSqlLen);

	void CloseDbConn();
};

#endif

