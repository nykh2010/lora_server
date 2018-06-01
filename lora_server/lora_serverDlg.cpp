
// lora_serverDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "lora_server.h"
#include "lora_serverDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLoraServerDlg �Ի���




CLoraServerDlg::CLoraServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoraServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoraServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLoraServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CLoraServerDlg::OnBnClickedButton3)
	ON_MESSAGE(WM_HASDATA, &CLoraServerDlg::OnHasdata)
END_MESSAGE_MAP()


// CLoraServerDlg ��Ϣ�������

BOOL CLoraServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CListCtrl *infoList = (CListCtrl *)GetDlgItem(IDC_LIST2);
	DWORD dwStyle;
	dwStyle = GetWindowLong(infoList->m_hWnd,GWL_STYLE);
	dwStyle &= ~LVS_TYPEMASK;
	dwStyle |= LVS_REPORT;
	SetWindowLong(infoList->m_hWnd,GWL_STYLE,dwStyle);
	dwStyle = infoList->GetExtendedStyle();
	dwStyle |= LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT;
	infoList->SetExtendedStyle(dwStyle);

	UpdateData(true);

	infoList->InsertColumn(0,_T("����ʱ��"),LVCFMT_CENTER,100);
	infoList->InsertColumn(1,_T("�ն�ID"),LVCFMT_CENTER,100);
	infoList->InsertColumn(2,_T("����ֵ"),LVCFMT_CENTER,100);

	UpdateData(false);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLoraServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLoraServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLoraServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLoraServerDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static BOOL connect_flag = false;
	int status;
	UpdateData(true);
	CEdit *port_edit = (CEdit *)GetDlgItem(IDC_EDIT1);
	CString port;
	port_edit->GetWindowTextW(port);
	UpdateData(false);
	if (!port.GetLength()) {
		AfxMessageBox(_T("������˿ں�"));
		return;
	}
	if (connect_flag == false) {		//δ����
		status = this->socket.Create(atoi((CT2A)port),SOCK_DGRAM,_T("192.168.1.2"));
		if (status == false) {
			AfxMessageBox(_T("����socketʧ��"));
			return;
		}
		/*status = this->socket.Listen();
		if (status == false) {
			this->socket.Close();
			return;
		}*/
		UpdateData(true);
		CButton *button = (CButton *)GetDlgItem(IDC_BUTTON3);
		button->SetWindowTextW(_T("�Ͽ�"));
		UpdateData(false);
		connect_flag = true;
	}
	else {								//������
		this->socket.Close();
		UpdateData(true);
		CButton *button = (CButton *)GetDlgItem(IDC_BUTTON3);
		button->SetWindowTextW(_T("����"));
		UpdateData(false);
		connect_flag = false;
	}
}


afx_msg LRESULT CLoraServerDlg::OnHasdata(WPARAM wParam, LPARAM lParam)
{
	//AfxMessageBox(_T("has data"));
	//socket.gateway.new_record_id;
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString get_time;
	get_time.Format(_T("%02d:%02d:%02d"),st.wHour,st.wMinute,st.wSecond);

	CString new_record_id;
	CString new_pos;
	wchar_t *convert_str = NULL;
	socket.gateway.new_record_id;
	int new_record_id_len = strlen(socket.gateway.new_record_id);
	int new_pos_len = strlen(socket.gateway.new_pos_data);
	convert_str = (wchar_t *)calloc(new_record_id_len+1,sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP,0,socket.gateway.new_record_id,new_record_id_len+1,convert_str,new_record_id_len+1);
	new_record_id.Format(_T("%s"),convert_str);
	free(convert_str);
	convert_str = (wchar_t *)calloc(new_pos_len+1,sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP,0,socket.gateway.new_pos_data,new_pos_len+1,convert_str,new_pos_len+1);
	new_pos.Format(_T("%s"),convert_str);
	free(convert_str);

	UpdateData(true);
	CListCtrl *infoList = (CListCtrl *)GetDlgItem(IDC_LIST2);
	CString payload_data;
	payload_data = new_pos.Mid(2,8);			//��ȡ�м���Ч����
	int nItem = 0;
	for(nItem = 0; nItem < infoList->GetItemCount(); nItem++)
	{
		if(infoList->GetItemText(nItem,1) == new_record_id)
		{
			break;
		}
	}
	if(nItem == infoList->GetItemCount())				//Ϊ�¼����ն�
	{
		infoList->InsertItem(nItem,get_time);
	}
	else
	{
		infoList->SetItemText(nItem,0,get_time);
	}
	infoList->SetItemText(nItem,1,new_record_id);
	infoList->SetItemText(nItem,2,payload_data);

	UpdateData(false);
	
	return 0;
}
