#pragma once


// CToolTypeBus �Ի���

class CToolTypeBus : public CDialogEx
{
	DECLARE_DYNAMIC(CToolTypeBus)

public:
	CToolTypeBus(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CToolTypeBus();
	int m_Id;
	double m_RatVol;

	ToolType m_ToolType;
	
	double m_VtE, m_VtF;	// For Vtheta BUS
	double m_PqP, m_PqQ;	// For PQ BUS
	double m_PvP, m_PvU;	// For PvBus

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOL_BUS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
