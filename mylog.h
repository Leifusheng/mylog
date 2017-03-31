//written by Frank_Lei
//20150423
//log.h ��־ͷ�ļ�

#ifndef _MY_LOG_H_
#define _MY_LOG_H_

//����log�ȼ�
#define MYLOG_LEVEL_NOLOG			0
#define MYLOG_LEVEL_DEBUG			1
#define MYLOG_LEVEL_INFO			2
#define MYLOG_LEVEL_WARNING			3
#define MYLOG_LEVEL_ERROR			4

//�ļ����ƺʹ�С
#define MYLOG_DEBUG_FILE			"mylog.log"
#define MYLOG_MAX_STRING_LEN 		10240

/************************************************************************ 
const char *file���ļ�����
int line���ļ��к�
int level�����󼶱�
		0 -- û����־
		1 -- debug����
		2 -- info����
		3 -- warning����
		4 -- err����
int status��������
const char *fmt���ɱ����
************************************************************************/
extern int  LogLevel[5];
void MYLOG(const char *file, int line, int level, int status, const char *fmt, ...);

#endif
