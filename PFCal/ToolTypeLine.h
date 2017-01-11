#pragma once


// CToolTypeLine 对话框

class CToolTypeLine : public CDialogEx
{
	DECLARE_DYNAMIC(CToolTypeLine)

public:
	CToolTypeLine(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CToolTypeLine();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOL_LINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void SetEditInitial(int, double ,int);
	void SetReadOnly(int);
	void SetNotReadOnly(int);

	DECLARE_MESSAGE_MAP()

public:
	int m_Id;
	double m_RatVol;
	bool m_Trans;	// whether its a transformer

	// transmission lines
	int m_Id_From, m_Id_To;
	double m_X1, m_R1, m_G1, m_B1;
	double m_Length;
	
	// transformers
	double m_Sn;
	double m_Uh, m_Ul, m_Uk;	// voltage on high and low voltage side
	double m_Pk, m_Po, m_Io;


	afx_msg void OnEnUpdateLineId();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedLineTransformers();
	afx_msg void OnBnClickedLineLine();
	afx_msg void OnEnChangeLineR1();
	afx_msg void OnEnChangeLineX1();
	afx_msg void OnEnChangeLineG1();
	afx_msg void OnEnChangeLineB1();
	afx_msg void OnEnChangeLineL();
	afx_msg void OnEnChangeLineRatvol();
	afx_msg void OnBnClickedLineExange();
	afx_msg void OnEnChangeTransUnh();
	afx_msg void OnEnChangeTransUnl();
	afx_msg void OnEnChangeTransPk();
	afx_msg void OnEnChangeTransUk();
	afx_msg void OnEnChangeTransPo();
	afx_msg void OnEnChangeTransIo();
	afx_msg void OnEnChangeTransSn();
};
