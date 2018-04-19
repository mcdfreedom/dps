/*!
* \file         appEntry.cc
* \author       lidong
* \date         2018/04/13
* \copyright    Copyright(c) kemyond 2015, All rights reserved.
*
* \brief        应用系统的统一入口程序
*
* 具体请参见 dps_global.h
*/

#include <stdio.h>
//#include <libgen.h> //basename
#include <stdlib.h> //exit getenv
//#include <dlfcn.h>  //dlopen

//自定义类
#include "Tools.h"


int main(int argc, char* argv[])
{
	// 实例化数据库对象
	_sql_::mysql_connection_pool *pPool = new _sql_::mysql_connection_pool();

	/**
	*  功能描述:数据库相关配置
	*  @param pIP IP地址
	*  @param pPwd 用户
	*  @param pUser 密码
	*  @param pDatabase 数据库名
	*  @param nPort 端口
	*  @return void
	*/
	//test
	const string sIP = "192.168.1.48";
	const string sUser = "root";
	const string sPwd = "kemyond";
	const string sDb = "log_analysis";
	const unsigned int uiPort = 3306;
	pPool->SetDatabaseInfo(sIP.c_str(),\
		sUser.c_str(),\
		sPwd.c_str(),\
		sDb.c_str(),\
		uiPort
		);

	/**
	*  功能描述:初始化线程池
	*  @param 最大线程个数
	*
	*  @return
	*/
	int iRet = pPool->GetInstance()->InitConnection();
	if (iRet < 0)
	{
		cout << "GetInstance()->InitConnection() failed \n" << endl;
	}




	// 释放数据库对象

	system("pause");
	return 0;
}




