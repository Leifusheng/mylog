#define  _CRT_SECURE_NO_WARNINGS 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mylog.h"


int  LogLevel[5] = {MYLOG_LEVEL_NOLOG, MYLOG_LEVEL_DEBUG, MYLOG_LEVEL_INFO, MYLOG_LEVEL_WARNING, MYLOG_LEVEL_ERROR };

//Level������
char LogLevelName[5][10] = {"NOLOG", "DEBUG", "INFO", "WARNING", "ERROR"};

static int MYLOG_Error_GetCurTime(char* strTime)
{
	struct tm*		tmTime = NULL;
	size_t			timeLen = 0;
	time_t			tTime = 0;
	tTime = time(NULL);
	tmTime = localtime(&tTime);
	timeLen = strftime(strTime, 33, "%Y.%m.%d %H:%M:%S", tmTime);
	return timeLen;
}

static int MYLOG_Error_OpenFile(int* pf)
{
	char	fileName[1024];
	
	memset(fileName, 0, sizeof(fileName));
#ifdef WIN32
	sprintf(fileName, "c:\\%s", MYLOG_DEBUG_FILE);
#else
	sprintf(fileName, "%s/log/", getenv("HOME"));
	if (access(fileName, F_OK) != 0)
	{
		//printf("create dir log\n");
		if (mkdir(fileName, 0777))
		{
			printf("create dir failed\n");
		}
	}
	memset(fileName, 0, sizeof(fileName));
	sprintf(fileName, "%s/log/%s", getenv("HOME"), ITCAST_DEBUG_FILE_);
#endif
    
    *pf = open(fileName, O_WRONLY|O_CREAT|O_APPEND, 0666);
    if(*pf < 0)
    {
        return -1;
    }
	return 0;
}

static void MYLOG_Error_Core(const char *file, int line, int level, int status, const char *fmt, va_list args)
{
    char str[MYLOG_MAX_STRING_LEN];
    int	 strLen = 0;
    char tmpStr[64];
    int	 tmpStrLen = 0;
    int  pf = 0;
    
    //��ʼ��
    memset(str, 0, MYLOG_MAX_STRING_LEN);
    memset(tmpStr, 0, 64);
    
    //����LOGʱ��
    tmpStrLen = MYLOG_Error_GetCurTime(tmpStr);
    tmpStrLen = sprintf(str, "[%s] ", tmpStr);
    strLen = tmpStrLen;

    //����LOG�ȼ�
    tmpStrLen = sprintf(str+strLen, "[%s] ", LogLevelName[level]);
    strLen += tmpStrLen;
    
    //����LOG״̬
    if (status != 0) 
    {
        tmpStrLen = sprintf(str+strLen, "[ERRNO is %d] ", status);
    }
    else
    {
    	tmpStrLen = sprintf(str+strLen, "[SUCCESS] ");
    }
    strLen += tmpStrLen;

    //����LOG��Ϣ
    tmpStrLen = vsprintf(str+strLen, fmt, args);
    strLen += tmpStrLen;

    //����LOG�����ļ�
    tmpStrLen = sprintf(str+strLen, " [%s]", file);
    strLen += tmpStrLen;

    //����LOG��������
    tmpStrLen = sprintf(str+strLen, " [%d]\n", line);
    strLen += tmpStrLen;
    
    //��LOG�ļ�
    if(MYLOG_Error_OpenFile(&pf))
	{
		return ;
	}
	
    //д��LOG�ļ�
    write(pf, str, strLen);
    //�ر��ļ�
    close(pf);
    return ;
}


void MYLOG(const char *file, int line, int level, int status, const char *fmt, ...)
{
    va_list args;
	
	//�ж��Ƿ���ҪдLOG
	if(level == MYLOG_LEVEL_NOLOG)
	{
		return ;
	}
	
	//���ú��ĵ�дLOG����
    va_start(args, fmt);
    MYLOG_Error_Core(file, line, level, status, fmt, args);
    va_end(args);
    return ;
}
