
// lora_serverDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "lora_server.h"
#include "lora_serverDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CLoraServerDlg 对话框




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


// CLoraServerDlg 消息处理程序

BOOL CLoraServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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

	infoList->InsertColumn(0,_T("更新时间"),LVCFMT_CENTER,100);
	infoList->InsertColumn(1,_T("终端ID"),LVCFMT_CENTER,100);
	infoList->InsertColumn(2,_T("数据值"),LVCFMT_CENTER,100);

	UpdateData(false);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLoraServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLoraServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLoraServerDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	static BOOL connect_flag = false;
	int status;
	UpdateData(true);
	CEdit *port_edit = (CEdit *)GetDlgItem(IDC_EDIT1);
	CString port;
	port_edit->GetWindowTextW(port);
	UpdateData(false);
	if (!port.GetLength()) {
		AfxMessageBox(_T("请输入端口号"));
		return;
	}
	if (connect_flag == false) {		//未连接
		status = this->socket.Create(atoi((CT2A)port),SOCK_DGRAM,_T("192.168.1.2"));
		if (status == false) {
			AfxMessageBox(_T("创建socket失败"));
			return;
		}
		/*status = this->socket.Listen();
		if (status == false) {
			this->socket.Close();
			return;
		}*/
		UpdateData(true);
		CButton *button = (CButton *)GetDlgItem(IDC_BUTTON3);
		button->SetWindowTextW(_T("断开"));
		UpdateData(false);
		connect_flag = true;
	}
	else {								//已连接
		this->socket.Close();
		UpdateData(true);
		CButton *button = (CButton *)GetDlgItem(IDC_BUTTON3);
		button->SetWindowTextW(_T("连接"));
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
	payload_data = new_pos.Mid(2,8);			//截取中间有效数字
	int nItem = 0;
	for(nItem = 0; nItem < infoList->GetItemCount(); nItem++)
	{
		if(infoList->GetItemText(nItem,1) == new_record_id)
		{
			break;
		}
	}
	if(nItem == infoList->GetItemCount())				//为新加入终端
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
