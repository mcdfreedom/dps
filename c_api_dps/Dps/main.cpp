/*!
* \file         appEntry.cc
* \author       lidong
* \date         2018/04/13
* \copyright    Copyright(c) kemyond 2018, All rights reserved.
*
* \brief        应用系统的统一入口程序
*
* 具体请参见 dps_global.h
*/

#include <stdio.h>
#include <stdlib.h> //exit getenv

//自定义类
#include "Tools.h"


int main(int argc, char* argv[])
{
	// 实例化数据库对象
	sql::mysql_connection_pool *pPool = new sql::mysql_connection_pool();

	/**
	*  功能描述:数据库相关配置
	*  @param pIP IP地址
	*  @param pPwd 用户
	*  @param pUser 密码
	*  @param pDatabase 数据库名
	*  @param nPort 端口
	*  @param nReConn 重连次数
	*  @return void
	*/
	const string sIP = "192.168.1.48";
	const string sUser = "root";
	const string sPwd = "kemyond";
	const string sDb = "log_analysis";
	const unsigned int uiPort = 3306;

	int iRet = pPool->setDBsetting(sIP.c_str(), \
		sUser.c_str(), \
		sPwd.c_str(), \
		sDb.c_str(), \
		uiPort);
	if (iRet != 0)
	{
		printf("setDBsetting(param1,...),please check your conf \n ");
	}


	/**
	*  功能描述:初始化连接池个数
	*  @iMaxConn 连接池连接个数
	*  @return iRet 成功连接个数
	*/

	unsigned int iMaxConn = 10;
	iRet = pPool->GetInstance()->InitConnection(iMaxConn);
	if (iRet > 0)
		printf("pPool success create %d connection \n", iRet);

	// \ 获取队列中连接
	sql::CTools *pTool = pPool->GetInstance()->GetConnection();
	/**
	*  功能描述:查询数据库
	*  @param sSql 查询sql
	*  @param sSql 查询sql长度
	*  @return
	*/
	string sSql = "select * from ruleConf";
	pTool->query(sSql, sSql.length());
	MYSQL_ROW oRow;
	MYSQL_RES *pRes = pTool->query(sSql, sSql.length());
	while (oRow = mysql_fetch_row(pRes)) {
		for (int t = 0; t<mysql_num_fields(pRes); t++) {
			printf("%s \n", oRow[t]);
		}
	}

	/**
	*  功能描述:删除数据库
	*  @param sSql 删除sql
	*  @return
	*/

	iRet = pTool->delete_sql("delete from ruleConf where logTypeId ='aa'");
	if (iRet <= 0)
		printf("delete_sql failed \n");

	/**
	*  功能描述:删除数据库
	*  @param sSql 增加sql
	*  @return
	*/

	iRet = pTool->insert_sql("insert into ruleConf values ('aa','cc')");
	if (iRet <= 0)
		printf("insert_sql failed \n");

	/**
	*  功能描述:修改数据库
	*  @param sSql 增加sql
	*  @return
	*/

	iRet = pTool->update_sql("UPDATE ruleConf SET logTypeId = 'newAA' WHERE logTypeId = 'aa'");
	if (iRet <= 0)
		printf("insert_sql failed \n");



	/**
	*  功能描述:关闭数据库连接池
	*  @param null
	*  @return
	*/
	pPool->ReleaseConnection(pTool);

	// \程序结束
	if (pPool != NULL)
	{
		delete pPool;
		pPool = NULL;
	}
	

	system("pause");
	return 0;
}




