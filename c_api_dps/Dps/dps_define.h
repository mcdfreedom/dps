
/// 用于变参类型 如：%d %s两种类型
/// \def 用于变参类型 如：%d %s两种类型
#define DATA_TYPE_INT               4   //整型  
#define DATA_TYPE_CHARPTR           1   //char*类型         
#define DATA_TYPE_INVALID           0   //无效类型  
#define THREAD_EXEC_CNT 100000 //每个线程操作次数
#define THREAD_NUM 10 //线程个数


/// \def 程序退出的宏定义
#define exitx(errcode,msg,...) \
{ \
if (NULL != dl) \
	dlclose(dl); \
	Alarm((errcode), (msg), ##__VA_ARGS__); \
	exit((errcode)); \
}