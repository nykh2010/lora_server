
// lora_serverDlg.h : ͷ�ļ�
//

#pragma once
#include "afxsock.h"
#include "Mysocket.h"


// CLoraServerDlg �Ի���
class CLoraServerDlg : public CDialogEx
{
// ����
public:
	CLoraServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LORA_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	// �׽���
	CMysocket socket;
protected:
	afx_msg LRESULT OnHasdata(WPARAM wParam, LPARAM lParam);
};
