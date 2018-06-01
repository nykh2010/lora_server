#include "StdAfx.h"
#include "Gateway.h"


CGateway::CGateway(void)
{
}


CGateway::~CGateway(void)
{
}


CProtocol *CGateway::parse(CByteArray &data)
{
	static CProtocol protocol_ret;
	protocol_ret.protocol_version = data[0];
	memcpy(protocol_ret.random_token,&data[1],2);
	memcpy(protocol_ret.gateway_id,&data.GetData()[4],8);

	protocol_ret.json_packet.SetSize(data.GetSize()-12);
	memcpy(protocol_ret.json_packet.GetData(),&data.GetData()[12],data.GetSize()-12);
	return &protocol_ret;
}

void *CJson::parse(CByteArray &json_packet, const char *name, int *length)
{
	char *strend;
	//char *json = (char *)calloc(1,json_packet.GetSize()+1);
	//memcpy(json,json_packet.GetData(),json_packet.GetSize());
	char *json = (char *)json_packet.GetData();
	char *result = strstr(json,name);
	if (result == NULL) {
		return NULL;
	}
	else {
		strend = strstr(result+7,"\"");
		*length = strend - (result + 7);
		return result+7;			//·µ»Ø½á¹û
	}
}