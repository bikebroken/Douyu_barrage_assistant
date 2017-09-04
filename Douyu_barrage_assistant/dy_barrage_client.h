
#ifndef __DY_BARRAGE_CLIENT_H__
#define __DY_BARRAGE_CLIENT_H__

#include <stdint.h>
#include <string>
#include "data_def.h"

using namespace std;

class dy_barrage_client
{
public:
	int sock_fd;		//socket file descriptor
	string src_text;
public:
	dy_barrage_client();
	~dy_barrage_client();

	//connect to douyu barrage server
	int connect_dy_server(const char *host, int port);

	//login douyu live room
	//Note: never login twice unless previous one is failed
	int login_dy_room();

	//join room group
	//Note: there are several groups in a room. group -9999 will get every barrage in this room
	int join_dy_room_group(int room_id, int group_id = -9999);

	//get douyu server message
	void get_dy_server_msg();

	//keep alive with douyu server.
	//Note: server requests clients keep alive at liast once per minute,if not server will kick this "death" client
	void keep_alive();

protected:
	//do something when receive a barrage
	void on_barrage(string data);

	//do something when receive a login response
	void on_login_response(string data);
};

//将UTF字符转化为Unicode字符 否则在Win32控制台里会显示乱码
string UTF82Unicode(const char *szU8);

//wstring转化为string
string ws2s(const wstring& ws);

#endif //__DY_BARRAGE_CLIENT_H__