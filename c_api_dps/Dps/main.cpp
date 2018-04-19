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
#include "Tools.h"


int main(int argc, char* argv[])
{
	// ʵ�������ݿ����
	_sql_::mysql_connection_pool *pPool = new _sql_::mysql_connection_pool();

	/**
	*  ��������:���ݿ��������
	*  @param pIP IP��ַ
	*  @param pPwd �û�
	*  @param pUser ����
	*  @param pDatabase ���ݿ���
	*  @param nPort �˿�
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
	*  ��������:��ʼ���̳߳�
	*  @param ����̸߳���
	*
	*  @return
	*/
	int iRet = pPool->GetInstance()->InitConnection();
	if (iRet < 0)
	{
		cout << "GetInstance()->InitConnection() failed \n" << endl;
	}




	// �ͷ����ݿ����

	system("pause");
	return 0;
}




