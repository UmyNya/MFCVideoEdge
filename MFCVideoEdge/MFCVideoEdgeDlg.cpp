
// MFCVideoEdgeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCVideoEdge.h"
#include "MFCVideoEdgeDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCVideoEdgeDlg 对话框



CMFCVideoEdgeDlg::CMFCVideoEdgeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCVIDEOEDGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCVideoEdgeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	// 视频地址
	DDX_Text(pDX, IDC_EDIT1, videoPath);
	// 保存地址
	DDX_Text(pDX, IDC_EDIT2, savePath);
	// Canny 算法的两个参数
	DDX_Text(pDX, IDC_EDIT3, threshold1);
	DDX_Text(pDX, IDC_EDIT4, threshold2);
}

BEGIN_MESSAGE_MAP(CMFCVideoEdgeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCVideoEdgeDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCVideoEdgeDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCVideoEdgeDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCVideoEdgeDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCVideoEdgeDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCVideoEdgeDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CMFCVideoEdgeDlg::OnEnChangeEdit4)
END_MESSAGE_MAP()


// CMFCVideoEdgeDlg 消息处理程序

BOOL CMFCVideoEdgeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	UpdateData(TRUE);
	// 默认路径（方便演示和调试）
	videoPath = "Flower Storm - Eve.mp4";
	savePath = "result.mp4";
	// 默认canny参数
	threshold1 = 35;
	threshold2 = 60;
	UpdateData(FALSE);

	// 创建非模态弹窗
	saveSuccessDlg.Create(IDD_SAVESUCCESS);
	savingDlg.Create(IDD_SAVING);
	// 居中
	saveSuccessDlg.CenterWindow(this);
	savingDlg.CenterWindow(this);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCVideoEdgeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCVideoEdgeDlg::OnPaint()
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
HCURSOR CMFCVideoEdgeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCVideoEdgeDlg::OnBnClickedButton1()
{
	// 读取视频地址
	UpdateData(TRUE);
	// 转换为 string 类型
	vPath = (CStringA)videoPath;
	UpdateData(FALSE);

	// 打开视频
	//video.open("FlowerStorm.mp4");
	video.open(vPath);
	if (!video.isOpened()) {
		// TODO 改成弹窗的形式
		UpdateData(TRUE);
		videoPath = TEXT("视频打开失败，请检查文件路径！");
		UpdateData(FALSE);
	}

	// 帧率
	double fps = video.get(CAP_PROP_FPS);
	// 视频宽度和高度
	double vWidth = video.get(CAP_PROP_FRAME_WIDTH);
	double vHeight = video.get(CAP_PROP_FRAME_HEIGHT);

	while (true) {
		// 读取视频帧
		Mat frame;
		video >> frame;

		// 如果视频放完了，就退出
		if (frame.empty()) {
			break;
		}

		// 展示视频
		imshow("Video", frame);
		// 控制视频展示的帧率，并读取键盘输入
		uchar exit = waitKey((int)(1000 / fps));
		// 如果键盘输入为 ESC ，就退出
		if (exit == 27) {
			break;
		}
	}

	// 关闭窗口
	destroyWindow("Video");
}


void CMFCVideoEdgeDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCVideoEdgeDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCVideoEdgeDlg::OnBnClickedButton2()
{
	// 读取视频地址
	UpdateData(TRUE);
	// 转换为 string 类型
	vPath = (CStringA)videoPath;
	UpdateData(FALSE);

	// 打开视频
	video.open(vPath);
	if (!video.isOpened()) {
		// TODO 改成弹窗的形式
		UpdateData(TRUE);
		videoPath = TEXT("视频打开失败，请检查文件路径！");
		UpdateData(FALSE);
	}

	// 帧率
	double fps = video.get(CAP_PROP_FPS);
	// 视频宽度和高度
	double vWidth = video.get(CAP_PROP_FRAME_WIDTH);
	double vHeight = video.get(CAP_PROP_FRAME_HEIGHT);

	// 读取视频帧
	Mat frame;
	video >> frame;

	while (true) {
		// 如果视频读完了，就退出
		if (!video.read(frame)) {
			break;
		}

		// TODO 视频处理的逻辑
		Mat result;
		// 转化为灰度图像
		cvtColor(frame, result, COLOR_BGR2GRAY);
		// 均值模糊
		blur(result, result, Size(7, 7));
		// Canny 边缘检测
		Canny(result, result, threshold1, threshold2, 3);

		// 展示视频
		imshow("Video", result);
		// 控制视频展示的帧率，并读取键盘输入
		uchar exit = waitKey((int)(1000 / fps));
		// 如果键盘输入为 ESC ，就退出
		if (exit == 27) {
			break;
		}
	}

	destroyWindow("Video");
}


void CMFCVideoEdgeDlg::OnBnClickedButton3()
{	
	// 读取视频地址
	UpdateData(TRUE);
	// 转换为 string 类型
	vPath = (CStringA)videoPath;
	UpdateData(FALSE);

	// 打开视频
	video.open(vPath);
	if (!video.isOpened()) {
		// TODO 改成弹窗的形式
		UpdateData(TRUE);
		videoPath = TEXT("视频打开失败，请检查文件路径！");
		UpdateData(FALSE);
	}

	// 帧率
	double fps = video.get(CAP_PROP_FPS);
	// 视频宽度和高度
	double vWidth = video.get(CAP_PROP_FRAME_WIDTH);
	double vHeight = video.get(CAP_PROP_FRAME_HEIGHT);

	// 读取视频帧
	Mat frame;
	video >> frame;

	// 读取保存地址
	UpdateData(TRUE);
	// TODO 变成弹窗
	sPath = (CStringA)savePath;
	UpdateData(FALSE);

	// 保存视频
	VideoWriter writer;
	// 保存的编码
	int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
	// 是否保存彩色
	//bool isColor = (frame.type() == CV_8UC3);
	bool isColor = FALSE;

	writer.open(sPath, codec, fps, frame.size(), isColor);
	if (!writer.isOpened()) {
		UpdateData(TRUE);
		// TODO 变成弹窗
		savePath = TEXT("保存失败，请检查路径问题。");
		UpdateData(FALSE);
	} else {
		//savingDlg.DoModal();
		savingDlg.ShowWindow(SW_NORMAL);
		waitKey(1500);
	}

	while (true) {
		// 如果视频读完了，就退出
		if (!video.read(frame)) {
			savingDlg.ShowWindow(SW_HIDE);
			saveSuccessDlg.ShowWindow(SW_NORMAL);
			break;
		}

		// TODO 视频处理的逻辑
		Mat result;
		// 转化为灰度图像
		cvtColor(frame, result, COLOR_BGR2GRAY);
		// 均值模糊
		blur(result, result, Size(7, 7));
		// Canny 边缘检测
		Canny(result, result, threshold1, threshold2, 3);

		// 写入每一帧
		writer.write(result);
	}
}


void CMFCVideoEdgeDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCVideoEdgeDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
