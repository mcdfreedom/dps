/*!
* \file		CDBConnect.h
* \author	lidong
* \date		2018/04/18
* \copyright	Copyright(c) Kemyond 2015, All rights reserved.
*
* \brief	���ݻ�������
*
*/

//mysql�ο��ĵ�
//http://www.yesky.com/imagesnew/software/mysql/manual_Clients.html


#if !defined(_C_DB_TOOLS_H)
#define _C_DB_TOOLS_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <direct.h>//��ȡ��ǰ·��
#include "mysql.h"

using namespace std;//����std�����ռ�

//�Զ���
#include "dps_common.h"

#include <queue>

#pragma comment(lib, "libmysql.lib")

namespace sql {
	static mutex  g_mtxmysql;//mysql��������Ļ������  
	static mutex  g_mtxMysqlPool;//mysql���ӳصĻ������  
	typedef struct DBsetting
	{
		char cIp[24];//IP
		char cUser[24];//�û���
		char cPasswd[24];//����
		char cdb[24];//���ݿ���
		unsigned int uiPort;//�˿ں�
		unsigned int uiConnpoolsize;//���ӳ�����С
		unsigned int uiReconnectCnt;//��������
		unsigned int uiConTimeout;//���ӳ�ʱʱ��
		DBsetting(){
			memset(cIp, 0, sizeof(cIp));
			memset(cUser, 0, sizeof(cUser));
			memset(cPasswd, 0, sizeof(cPasswd));
			memset(cdb, 0, sizeof(cdb));
			uiPort = 0;
			uiConnpoolsize = 0;
			uiReconnectCnt = 0;
			uiConTimeout = 0;
		}
	}*pDBsetting, dbSetting;

	static dbSetting g_DBsetting;//������ݿ�������Ϣ�������ʹ��
	class CDBConnect
	{
	public:
		MYSQL		Mysql;	//mysql����
		~CDBConnect()
		{
			mysql_close(&Mysql);
		};

		CDBConnect()
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
		bool selectsqlbeack(__in const char *pSQL, __out ...);
		bool selectsqlbeack_s(__in const char *pSQL, __out ...);
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
			 mysql_close(&Mysql);
		}

		//�Ƿ��Զ��ύ
		void AutoCommitSQL(BOOL bAuto = TRUE);

	public:
		bool execute(const char* pSQL);
		MYSQL_RES * query(string sSql, unsigned int iSqlLen);
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
	class CConnPool
	{

	public:
		~CConnPool();
		//����ģʽ
		static CConnPool *GetInstance();

		//��ʼ������
		int InitConnection(int nInitialSize );
		//����mysql��Ϣ
		int setDBsetting(const char* pIP,\
			const char* pUser,\
			const char* pPwd,\
			const char* pDatabase,\
			unsigned int nPort /* = 3306 */
			);
		//��ȡmsyql��������
		CDBConnect *GetConnection();
		//�������Ӷ���
		void ReleaseConnection(CDBConnect * pObject);
		//�������ӳ�
		void DestoryConnPool();
	public:
		CConnPool();
		std::queue<CDBConnect *> the_queue;
		mutex the_mutex;
	};
}


#endif 

