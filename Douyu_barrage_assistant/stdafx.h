// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#ifdef _MSC_VER
#include <Windows.h>
#include <tchar.h>

#define strtoll _strtoi64
#define strtoull _strtoui64
#define snprintf _snprintf
#define popen   _popen
#define pclose  _pclose
#define strcasecmp _stricmp
#define strncasecmp _strnicmp

#else
#include <pthread.h>
#endif



// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
