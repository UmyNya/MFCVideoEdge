#pragma once
#include "afxdialogex.h"


// SaveSuccess 对话框

class SaveSuccess : public CDialogEx
{
	DECLARE_DYNAMIC(SaveSuccess)

public:
	SaveSuccess(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SaveSuccess();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAVESUCCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
