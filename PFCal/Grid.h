#pragma once
#include "afxcmn.h"


// CGrid 对话框

class CGrid : public CDialogEx
{
	DECLARE_DYNAMIC(CGrid)

public:
	CGrid(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGrid();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_Grid;
	int m_GridSize;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSliderGrid(NMHDR *pNMHDR, LRESULT *pResult);
};
