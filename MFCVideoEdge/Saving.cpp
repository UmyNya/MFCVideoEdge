// Saving.cpp: 实现文件
//

#include "pch.h"
#include "MFCVideoEdge.h"
#include "afxdialogex.h"
#include "Saving.h"


// Saving 对话框

IMPLEMENT_DYNAMIC(Saving, CDialogEx)

Saving::Saving(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SAVING, pParent)
{

}

Saving::~Saving()
{
}

void Saving::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Saving, CDialogEx)
END_MESSAGE_MAP()


// Saving 消息处理程序
