
#include "stdafx.h"
#include "dy_barrage_client.h"
#include "barrage_qtts.h"
#include <iostream>
#include <string>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _MSC_VER
#	include <netdb.h>
#	include <sys/socket.h>
#else
#   include <winsock.h>
#   pragma comment(lib, "ws2_32")
#endif
#pragma comment(lib,"winMM.lib")   //可播放音频
using namespace std;

void usage()
{
	std::cout << "usage:" << std::endl;
	std::cout << "\t./get_dy_barrage room_id" << std::endl;
}

#ifdef _MSC_VER
void thr_keep_live(void *args)
#else
void* thr_keep_live(void *args)
#endif 
{
	dy_barrage_client *dy_bclient = (dy_barrage_client *)args;
	while (1)
	{
		dy_bclient->keep_alive();
#ifdef _MSC_VER
		Sleep(45000);
#else
		sleep(45);      //keep live once per 45 seconds
#endif

	}
}

/*#ifdef _MSC_VER
void thr_qtts(void *args)
#else
void* thr_qtts(void *args)
#endif 
{
	dy_barrage_client *dy_bclient = (dy_barrage_client *)args;
	
}
*/
int main(int argc,char **args)
{
	int ret = 0;
	int room_id = 0;
	string host_name = "openbarrage.douyutv.com";
	int32_t port = 8601;
	string host;

	/*if (argc < 2)
	{
		usage();
		return 0;
	}*/

	//parse parameters
	//room_id = atoi(args[1]);
	cout << "请输入房间号：";
	cin >> room_id;
	cout << endl;
	dy_barrage_client dy_bclient;

	ret = dy_bclient.connect_dy_server(host_name.c_str(), port);
	if (0 != ret)
	{
		std::cout << "please check the address and restart the program" << std::endl;
		return 0;
	}

	ret = dy_bclient.login_dy_room();
	if (0 != ret)
	{
		return 0;
	}

	//ret = dy_bclient.join_dy_room_group(room_id, -9999);
	ret = dy_bclient.join_dy_room_group(room_id, -9999);
	if (0 != ret)
	{
		return 0;
	}

	//create a thread to keep alive
#ifdef  _MSC_VER
	HANDLE handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thr_keep_live, &dy_bclient, 0, NULL);
	//WaitForSingleObject(handle, INFINITE)
#else
	pthread_t tid;
	ret = pthread_create(&tid, NULL, &thr_keep_live, &dy_bclient);
	if (ret != 0)
	{
		cout << "Create pthread error!" << endl;
		return 0;
	}
#endif 
	barrage_qtts b_qtts;
	ret = b_qtts.Login();
	if (ret != 0) 
	{
		cout << "fail to Login xunfei" << endl;
		return 0;
	}
	const char* session_begin_params = "voice_name = yanping, text_encoding = gb2312, sample_rate = 16000, speed = 30, volume = 50, pitch = 50, rdn = 2";
	const char* filename = "tts_sample.wav"; //合成的语音文件名称
	const char* src_text;
	while (1)
	{
		dy_bclient.get_dy_server_msg();
		src_text = dy_bclient.src_text.c_str();
		ret = b_qtts.text_to_speech(src_text, filename, session_begin_params);
		if (ret != 0)
		{
			cout << "语音合成失败" << endl;
		}
		else {
			PlaySound(filename, NULL, SND_SYNC);
		}
	}

#ifdef _MSC_VER
#else
	pthread_join(tid, NULL);	//回收线程
#endif

	system("pause");
    return 0;
}

