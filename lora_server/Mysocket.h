#pragma once

// CMysocket ����Ŀ��

#include "Gateway.h"

class CMysocket : public CSocket
{
public:
	CMysocket();
	virtual ~CMysocket();
	virtual void OnAccept(int nErrorCode);
public:
	CGateway gateway;
	virtual void OnReceive(int nErrorCode);
};


