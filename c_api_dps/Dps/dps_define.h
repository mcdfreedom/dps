
/// ���ڱ������ �磺%d %s��������
/// \def ���ڱ������ �磺%d %s��������
#define DATA_TYPE_INT               4   //����  
#define DATA_TYPE_CHARPTR           1   //char*����         
#define DATA_TYPE_INVALID           0   //��Ч����  
#define TEST_DATA_LENGTH 100000 //ÿ���̲߳�������
#define THREAD_NUM 10 //�̸߳���


/// \def �����˳��ĺ궨��
#define exitx(errcode,msg,...) \
{ \
if (NULL != dl) \
	dlclose(dl); \
	Alarm((errcode), (msg), ##__VA_ARGS__); \
	exit((errcode)); \
}