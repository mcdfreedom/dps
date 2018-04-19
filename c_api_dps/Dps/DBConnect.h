/*!
* \file		CDBConnect.h
* \author	lidong
* \date		2018/04/18
* \copyright	Copyright(c) Kemyond 2015, All rights reserved.
*
* \brief	数据基本功能
*
*/

//mysql参考文档
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
#include <direct.h>//获取当前路径
#include "mysql.h"

using namespace std;//引入std命名空间

//自定义
#include "dps_common.h"

#include <queue>

#pragma comment(lib, "libmysql.lib")

namespace sql {
	static mutex  g_mtxmysql;//mysql操作对象的互斥对象  
	static mutex  g_mtxMysqlPool;//mysql连接池的互斥对象  
	typedef struct DBsetting
	{
		char cIp[24];//IP
		char cUser[24];//用户名
		char cPasswd[24];//密码
		char cdb[24];//数据库名
		unsigned int uiPort;//端口号
		unsigned int uiConnpoolsize;//连接池最大大小
		unsigned int uiReconnectCnt;//重连次数
		unsigned int uiConTimeout;//连接超时时间
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

	static dbSetting g_DBsetting;//存放数据库配置信息，多个类使用
	class CDBConnect
	{
	public:
		MYSQL		Mysql;	//mysql对象
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
		*数据库初始化操作
		*
		*参数：
		*	pIP:数据库IP地址
		*	pUser：数据库用户名
		*	pPwd：数据库密码
		*	pDatabase：数据库名称
		*
		*返回值：
		*	返回false表示初始化失败，true表示初始化成功
		*
		*/
		bool initmysql(const char* pIP, const char* pUser, const char* pPwd, const char* pDatabase, unsigned short nPort = 3306);

		/*
		*执行数据库查询功能（带_s的标识支持string类型，不带的支持char*类型）
		*参数：
		*	pSQL：SQL语句
		*	...:变参返回查询到的数据
		*返回值：
		*	返回false表示数据库已经获取完毕，true表示数据还没有获取完毕
		*/
		bool selectsqlbeack(__in const char *pSQL, __out ...);
		bool selectsqlbeack_s(__in const char *pSQL, __out ...);
		/*
		*修改/插入/删除功能
		*参数：
		*	pSQL：SQL语句
		*返回值：
		*	返回false表示执行失败，true表示执行成功
		*
		*/
		bool update_sql(__in const char *pSQL);
		bool insert_sql(__in const char *pSQL);
		bool delete_sql(__in const char *pSQL);
		/*
		*执行查询SQL语句获取查询的数据
		*
		*参数：
		*	pSQL：sql语句
		*	ap：变参，是指输出查询到的数据
		*
		*返回值：
		*	返回false表示不是无效字符，非true表示是无效字符
		*/
		//打断上一次执行(意思就是不支持嵌套，嵌套可以使用上面的Select)
		bool SelectBeack(__in const char *pSQL, e_strType, __out va_list ap);
		/*
		*清理记录集指针数据
		*
		*/

		/*
		*获取 MYSQL连接状态
		*
		*返回值：
		*		返回true 表示没有断开  返回false 表示mysql连接已经断开
		*
		*/
		bool GetMysqlConnectStatus()
		{
			if (m_bOpen)
			{
				if (mysql_ping(&Mysql) == 0)//处于连接状态中
				{
					return true;
				}
			}
			return m_bOpen;
		}
		/*
		*清理查询后有多余的数据 最好执行sql语句后获取到所有需要数据后调用次接口清理
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
		*关闭mysql连接
		*/
		void CloseMysql(){
			 mysql_close(&Mysql);
		}

		//是否自动提交
		void AutoCommitSQL(BOOL bAuto = TRUE);

	public:
		bool execute(const char* pSQL);
		MYSQL_RES * query(string sSql, unsigned int iSqlLen);
	private:
		string m_strOldSql;	//旧的SQL语句
		MYSQL_RES *m_pResult;//记录集
		bool m_bOpen;


		//公共接口
	public:
		static string GetBinPath();
		static WCHAR* ToWChar(char *str);
	};


	/************************************************************************/
	/*			MYSQL 连接池                                    */
	/************************************************************************/
	class CConnPool
	{

	public:
		~CConnPool();
		//单例模式
		static CConnPool *GetInstance();

		//初始化连接
		int InitConnection(int nInitialSize );
		//设置mysql信息
		int setDBsetting(const char* pIP,\
			const char* pUser,\
			const char* pPwd,\
			const char* pDatabase,\
			unsigned int nPort /* = 3306 */
			);
		//获取msyql操作对象
		CDBConnect *GetConnection();
		//回收连接对象
		void ReleaseConnection(CDBConnect * pObject);
		//销毁连接池
		void DestoryConnPool();
	public:
		CConnPool();
		std::queue<CDBConnect *> the_queue;
		mutex the_mutex;
	};
}


#endif 

