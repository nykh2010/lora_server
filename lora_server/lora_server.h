
// lora_server.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#define WM_HASDATA		WM_USER+100

// CLoraServer:
// �йش����ʵ�֣������ lora_server.cpp
//

class CLoraServer : public CWinApp
{
public:
	CLoraServer();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLoraServer theApp;