
// lora_serverDlg.h : 头文件
//

#pragma once
#include "afxsock.h"
#include "Mysocket.h"


// CLoraServerDlg 对话框
class CLoraServerDlg : public CDialogEx
{
// 构造
public:
	CLoraServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LORA_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	// 套接字
	CMysocket socket;
protected:
	afx_msg LRESULT OnHasdata(WPARAM wParam, LPARAM lParam);
};
