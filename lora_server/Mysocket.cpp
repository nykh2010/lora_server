// Mysocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "lora_server.h"
#include "Mysocket.h"

//#include <WinNls.h>
//#include <fstream>

//#pragma comment(lib,"Kernel32.lib")

CMysocket client_sock;

// CMysocket
CMysocket::CMysocket()
{
}

CMysocket::~CMysocket()
{
}


// CMysocket ��Ա����


void CMysocket::OnAccept(int nErrorCode)
{
	//int nErrorCode = 0;
	// TODO: �ڴ����ר�ô����/����û���
	CString address;
	UINT port;
	
	this->Accept(client_sock,NULL,NULL);
	
	//client_sock.GetPeerName(address,port);

	CSocket::OnAccept(nErrorCode);
}


void CMysocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	BYTE buf[2048] = {0};
	int count;
	CByteArray recv_buf;
	count = this->Receive(buf,2048);
	if (count < 120) {
		return;
	}
	recv_buf.SetSize(count);
	memcpy(recv_buf.GetData(),buf,count);
	CProtocol *protocol_ret;// = this->gateway.parse(recv_buf);
	protocol_ret = this->gateway.parse(recv_buf);
	//this->gateway.id = protocol_ret->gateway_id;
	buf[0] = protocol_ret->protocol_version;
	memcpy(buf+1,protocol_ret->random_token,2);
	buf[3] = 0x01;			//Ӧ��
	count = this->Send(buf,4);

	CJson json;
	
	int length = 0;
	char *result;
	result = (char *)json.parse(protocol_ret->json_packet,"addr",&length);
	if (result == NULL) {
		return;
	}
	memcpy(this->gateway.new_record_id,result,8);		//��ȡ��ַ
	this->gateway.new_record_id[8] = 0;
	//free(result-7);
	
	result = (char *)json.parse(protocol_ret->json_packet,"data", &length);
	if (result == NULL) {
		return;
	}
	memcpy(this->gateway.new_pos_data,result,length);			//ȥ����ͷ����ʼ�ֽ�
	this->gateway.new_pos_data[length] = 0;
	//free(result-length+1);

	::SendMessageA(AfxGetMainWnd()->m_hWnd,WM_HASDATA,NULL,NULL);

	CSocket::OnReceive(nErrorCode);
}
