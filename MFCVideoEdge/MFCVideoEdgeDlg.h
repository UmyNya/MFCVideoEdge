
// MFCVideoEdgeDlg.h: 头文件
//

#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "SaveSuccess.h"
#include "Saving.h"

using namespace std;
using namespace cv;

// CMFCVideoEdgeDlg 对话框
class CMFCVideoEdgeDlg : public CDialogEx
{
// 构造
public:
	CMFCVideoEdgeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCVIDEOEDGE_DIALOG };
#endif

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

private:
	// 视频打开路径
	CString videoPath;
	string vPath;
	// 文件保存路径
	CString savePath;
	string sPath;
	// 视频处理
	VideoCapture video;
	// canny 参数
	double threshold1;
	double threshold2;
	SaveSuccess saveSuccessDlg;
	Saving savingDlg;

public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
};
