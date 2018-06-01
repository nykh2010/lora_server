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
	BYTE id[8];					//����ID
	char new_record_id[10];		//���յ������ݵ�ַ
	char new_pos_data[128];		//���յ���λ����Ϣ
};

class CJson
{
public:
	void *parse(CByteArray &json_packet, const char *name, int *length);
};