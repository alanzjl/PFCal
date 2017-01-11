#pragma once
#include "afxcmn.h"

#include "Element_class.h"
#include "Tool.h"
#include <list>


// COutput 对话框

class COutput : public CDialogEx
{
	DECLARE_DYNAMIC(COutput)

public:
	COutput(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COutput();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OUTPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_OutputDlg;
	std::list<CTool*>* m_ToolList;
	virtual BOOL OnInitDialog();
	Bus *bus;
};
