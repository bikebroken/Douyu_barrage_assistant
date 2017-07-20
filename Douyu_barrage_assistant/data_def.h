
#ifndef __DATA_DEF_H__
#define __DATA_DEF_H__

#include "stdafx.h"
#include <string>

using namespace std;

enum DY_MESSAGE_TYPE
{
	MSG_TYPE_BARRAGE = 1,			//barrage
	MSG_TYPE_LOGIN_RESPONSE = 2		//login response
};

int get_dy_msg_type(string pack_data);

//服务端发给客户端的弹幕消息
//参考《斗鱼弹幕服务器第三方接入协议v1.4.1》--2.4.3弹幕消息的字段
struct dy_barrage_res
{
	int ct;		//client type			0--web,1--android, 2--ios
	
	//0--temporary visitor, 1--room visitor, 2--room temporary administrator
    //3--room administrator, 4--room super administrator, 5--room owner
	int sender_rg;		//sender room group

	//0--temporary visitor, 1--normal user, 2--honor administrator
	//3--tour administrator, 4--director, 5--super administrator
	int sender_pg;      //sender platform group

	std::string content;		//barrage content
	std::string sender_name;	//sender name

	//parse douyu packet,get barrage information
	void parse_from_dy_string(std::string data);
};

struct dy_login_req
{
	//transform login request to douyu packet
	std::string transform_to_dy_string();
};

struct dy_login_res
{
	int ret;		//result code of login request.0 means success

	// parse douyu packet, get login respond information
	void parse_from_dy_string(std::string data);
};

struct dy_join_group_req
{
	int room_id;		//room id to join
	int group_id;		//group id to join

	dy_join_group_req();
	dy_join_group_req(int rid, int gid);

	//transform join group request to douyu packet
	std::string transform_to_dy_string();
};

struct dy_keep_alive_req
{
	int timestamp;

	dy_keep_alive_req();
	dy_keep_alive_req(int ts);

	//transform keep alive request to douyu packet
	std::string transform_to_dy_string();
};
#endif  //__DATA_DEF_H__