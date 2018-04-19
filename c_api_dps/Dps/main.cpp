/*!
* \file         appEntry.cc
* \author       lidong
* \date         2018/04/13
* \copyright    Copyright(c) kemyond 2018, All rights reserved.
*
* \brief        Ӧ��ϵͳ��ͳһ��ڳ���
*
* ������μ� dps_global.h
*/

#include <stdio.h>
#include <stdlib.h> //exit getenv

//�Զ�����
#include "Tools.h"


int main(int argc, char* argv[])
{
	// ʵ�������ݿ����
	sql::mysql_connection_pool *pPool = new sql::mysql_connection_pool();

	/**
	*  ��������:���ݿ��������
	*  @param pIP IP��ַ
	*  @param pPwd �û�
	*  @param pUser ����
	*  @param pDatabase ���ݿ���
	*  @param nPort �˿�
	*  @param nReConn ��������
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
	*  ��������:��ʼ�����ӳظ���
	*  @iMaxConn ���ӳ����Ӹ���
	*  @return iRet �ɹ����Ӹ���
	*/

	unsigned int iMaxConn = 10;
	iRet = pPool->GetInstance()->InitConnection(iMaxConn);
	if (iRet > 0)
		printf("pPool success create %d connection \n", iRet);

	// \ ��ȡ����������
	sql::CTools *pTool = pPool->GetInstance()->GetConnection();
	/**
	*  ��������:��ѯ���ݿ�
	*  @param sSql ��ѯsql
	*  @param sSql ��ѯsql����
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
	*  ��������:ɾ�����ݿ�
	*  @param sSql ɾ��sql
	*  @return
	*/

	iRet = pTool->delete_sql("delete from ruleConf where logTypeId ='aa'");
	if (iRet <= 0)
		printf("delete_sql failed \n");

	/**
	*  ��������:ɾ�����ݿ�
	*  @param sSql ����sql
	*  @return
	*/

	iRet = pTool->insert_sql("insert into ruleConf values ('aa','cc')");
	if (iRet <= 0)
		printf("insert_sql failed \n");

	/**
	*  ��������:�޸����ݿ�
	*  @param sSql ����sql
	*  @return
	*/

	iRet = pTool->update_sql("UPDATE ruleConf SET logTypeId = 'newAA' WHERE logTypeId = 'aa'");
	if (iRet <= 0)
		printf("insert_sql failed \n");



	/**
	*  ��������:�ر����ݿ����ӳ�
	*  @param null
	*  @return
	*/
	pPool->ReleaseConnection(pTool);

	// \�������
	if (pPool != NULL)
	{
		delete pPool;
		pPool = NULL;
	}
	

	system("pause");
	return 0;
}




