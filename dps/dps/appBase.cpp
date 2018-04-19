/*!
* \file         appEntry.cc
* \author       lidong
* \date         2018/04/13
* \copyright    Copyright(c) kemyond 2015, All rights reserved.
*
* \brief        Ӧ��ϵͳ��ͳһ��ڳ���
*
* ������μ� dps_global.h
*/

#include <stdio.h>
//#include <libgen.h> //basename
#include <stdlib.h> //exit getenv
//#include <dlfcn.h>  //dlopen

//�Զ�����
#include "Dbmodel.h"


//�����˳��ĺ궨��
#define exitx(errcode,msg,...) \
{ \
if (NULL != dl) \
	dlclose(dl); \
	Alarm((errcode), (msg), ##__VA_ARGS__); \
	exit((errcode)); \
}

int main(int argc, char* argv[])
{
	//��ȡ���ݿ���ص������ļ�


	  string sDbUser = "root";
	  string sDbPasswd = "kemyond";
	  string sDbIp = "192.168.1.48";
	  string sDbName = "log_anlysis";
	  string sDbTbName = "rule_conf";
	 const unsigned int iDbport = 3306;
	  string  sDbQuerySql = "";


	Dbmodel *pdbmodel = new Dbmodel();

	if (pdbmodel->ConnectDBInst(sDbUser, sDbPasswd, sDbIp, sDbName, sDbTbName, iDbport, ""))
	{
		std::cout << "connect kemyond docker database suc" << std::endl;
	}

	sDbQuerySql = "select * from ruleConf";





	MYSQL_ROW oRow;
	MYSQL_RES *pRes = pdbmodel->GetDbData(sDbQuerySql, sDbQuerySql.length());
	while (oRow = mysql_fetch_row(pRes)) {
		for (int t = 0; t<mysql_num_fields(pRes); t++) {
			printf("%s  ", oRow[t]);
		}
	}
	
	pdbmodel->CloseDbConn();

	delete pdbmodel;
	pdbmodel = NULL;
	system("pause");
	return 0;
}




