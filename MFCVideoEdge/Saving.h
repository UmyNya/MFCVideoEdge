#pragma once
#include "afxdialogex.h"


// Saving 对话框

class Saving : public CDialogEx
{
	DECLARE_DYNAMIC(Saving)

public:
	Saving(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Saving();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAVING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
