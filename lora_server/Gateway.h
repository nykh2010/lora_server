#pragma once

class CProtocol
{
public:
	BYTE protocol_version;
	BYTE random_token[2];
	BYTE identifier;
	BYTE gateway_id[8];
	CByteArray json_packet;
};

class CGateway
{
public:
	CGateway(void);
	~CGateway(void);
	CProtocol *parse(CByteArray &data);
public:	
	BYTE id[8];					//网关ID
	char new_record_id[10];		//新收到的数据地址
	char new_pos_data[128];		//新收到的位置信息
};

class CJson
{
public:
	void *parse(CByteArray &json_packet, const char *name, int *length);
};