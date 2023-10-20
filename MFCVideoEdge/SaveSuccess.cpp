// SaveSuccess.cpp: 实现文件
//

#include "pch.h"
#include "MFCVideoEdge.h"
#include "afxdialogex.h"
#include "SaveSuccess.h"


// SaveSuccess 对话框

IMPLEMENT_DYNAMIC(SaveSuccess, CDialogEx)

SaveSuccess::SaveSuccess(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SAVESUCCESS, pParent)
{

}

SaveSuccess::~SaveSuccess()
{
}

void SaveSuccess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SaveSuccess, CDialogEx)
END_MESSAGE_MAP()


// SaveSuccess 消息处理程序
