#pragma once


// CToolTypeBus 对话框

class CToolTypeBus : public CDialogEx
{
	DECLARE_DYNAMIC(CToolTypeBus)

public:
	CToolTypeBus(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CToolTypeBus();
	int m_Id;
	double m_RatVol;

	ToolType m_ToolType;
	
	double m_VtE, m_VtF;	// For Vtheta BUS
	double m_PqP, m_PqQ;	// For PQ BUS
	double m_PvP, m_PvU;	// For PvBus

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOL_BUS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void SetEditInitial(int, double, int);
	void SetReadOnly(int);
	void SetNotReadOnly(int);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeBusVte();
	afx_msg void OnEnChangeBusVtf();
	afx_msg void OnEnChangeBusPqp();
	afx_msg void OnEnChangeBusPqq();
	afx_msg void OnEnChangeBusPvp();
	afx_msg void OnEnChangeBusPvu();
	afx_msg void OnEnChangeBusRatvol();
};
