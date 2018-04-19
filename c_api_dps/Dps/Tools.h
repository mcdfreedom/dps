/*!
* \file		CTools.h
* \author	lidong
* \date		2018/04/18
* \copyright	Copyright(c) Kemyond 2015, All rights reserved.
*
* \brief	���ݻ�������
*
*/

//mysql�ο��ĵ�
//http://www.yesky.com/imagesnew/software/mysql/manual_Clients.html


#if !defined(_C_TOOLS_H)
#define _C_TOOLS_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <direct.h>//��ȡ��ǰ·��
//#include <afxtempl.h>
//#include <afxmt.h>
//#include <windows.h>
//#include <WinSock2.h>
#include "mysql.h"

using namespace std;//����std�����ռ�

//�Զ���
#include "dps_common.h"

#include <queue>

#pragma comment(lib, "libmysql.lib")

namespace _sql_ {
	static mutex  g_mtxmysql;//mysql��������Ļ������  
	static mutex  g_mtxMysqlPool;//mysql���ӳصĻ������  
	class CTools
	{
	public:
		MYSQL		Mysql;	//mysql����
		~CTools()
		{
			mysql_close(&Mysql);
		};

		CTools()
		{
			m_pResult = NULL;
			m_bOpen = false;
		};
		/*
		*���ݿ��ʼ������
		*
		*������
		*	pIP:���ݿ�IP��ַ
		*	pUser�����ݿ��û���
		*	pPwd�����ݿ�����
		*	pDatabase�����ݿ�����
		*
		*����ֵ��
		*	����false��ʾ��ʼ��ʧ�ܣ�true��ʾ��ʼ���ɹ�
		*
		*/
		bool initmysql(const char* pIP, const char* pUser, const char* pPwd, const char* pDatabase, unsigned short nPort = 3306);

		/*
		*ִ�����ݿ��ѯ���ܣ���_s�ı�ʶ֧��string���ͣ�������֧��char*���ͣ�
		*������
		*	pSQL��SQL���
		*	...:��η��ز�ѯ��������
		*����ֵ��
		*	����false��ʾ���ݿ��Ѿ���ȡ��ϣ�true��ʾ���ݻ�û�л�ȡ���
		*/
		bool select_sql_beack(__in const char *pSQL, __out ...);
		bool select_sql_beack_s(__in const char *pSQL, __out ...);
		/*
		*�޸�/����/ɾ������
		*������
		*	pSQL��SQL���
		*����ֵ��
		*	����false��ʾִ��ʧ�ܣ�true��ʾִ�гɹ�
		*
		*/
		bool update_sql(__in const char *pSQL);
		bool insert_sql(__in const char *pSQL);
		bool delete_sql(__in const char *pSQL);
		/*
		*ִ�в�ѯSQL����ȡ��ѯ������
		*
		*������
		*	pSQL��sql���
		*	ap����Σ���ָ�����ѯ��������
		*
		*����ֵ��
		*	����false��ʾ������Ч�ַ�����true��ʾ����Ч�ַ�
		*/
		//�����һ��ִ��(��˼���ǲ�֧��Ƕ�ף�Ƕ�׿���ʹ�������Select)
		bool SelectBeack(__in const char *pSQL, e_strType, __out va_list ap);
		/*
		*�����¼��ָ������
		*
		*/

		/*
		*��ȡ MYSQL����״̬
		*
		*����ֵ��
		*		����true ��ʾû�жϿ�  ����false ��ʾmysql�����Ѿ��Ͽ�
		*
		*/
		bool GetMysqlConnectStatus()
		{
			if (m_bOpen)
			{
				if (mysql_ping(&Mysql) == 0)//��������״̬��
				{
					return true;
				}
			}
			return m_bOpen;
		}
		/*
		*�����ѯ���ж�������� ���ִ��sql�����ȡ��������Ҫ���ݺ���ôνӿ�����
		*/
		void ClearResult()
		{
			if (m_pResult != NULL)
			{
				mysql_free_result(m_pResult);
				m_pResult = NULL;
				m_strOldSql = "";
			}

			//m_Lastmysql.initdata();
		}

		/*
		*�ر�mysql����
		*/
		void CloseMysql(){
			//if ( _pMysql )
			{
				mysql_close(&Mysql);
				//_pMysql = NULL;
			}
		}

		//�Ƿ��Զ��ύ
		void AutoCommitSQL(BOOL bAuto = TRUE);

	public:
		bool execute(const char* pSQL);
		MYSQL_RES * GetDbData(string sSql, unsigned int iSqlLen);
	private:
		string m_strOldSql;	//�ɵ�SQL���
		MYSQL_RES *m_pResult;//��¼��
		bool m_bOpen;


		//�����ӿ�
	public:
		static string GetBinPath();
		static WCHAR* ToWChar(char *str);
	};


	/************************************************************************/
	/*			MYSQL ���ӳ�                                    */
	/************************************************************************/
	class mysql_connection_pool
	{

	public:
		~mysql_connection_pool();
		//����ģʽ
		static mysql_connection_pool *GetInstance();

		//��ʼ������
		int InitConnection(int nInitialSize = 1);
		//����mysql��Ϣ
		void SetDatabaseInfo(const char* pIP,\
			const char* pUser,\
			const char* pPwd,\
			const char* pDatabase,\
			unsigned short nPort /* = 3306 */);
		//��ȡmsyql��������
		CTools *GetConnection();
		//�������Ӷ���
		void ReleaseConnection(CTools * pObject);
		//�������ӳ�
		void DestoryConnPool();
	public:
		mysql_connection_pool();
	private:
		char m_szIP[128];
		char m_szUser[128];
		char m_szPwd[128];
		char m_szDatabase[128];
		short m_snPort;
		std::queue<CTools *> the_queue;
		mutex the_mutex;
	};
}


#endif 

