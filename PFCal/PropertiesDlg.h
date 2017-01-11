#pragma once



// CPropertiesDlg 窗体视图

class CPropertiesDlg : public CFormView
{
	DECLARE_DYNCREATE(CPropertiesDlg)

protected:
	CPropertiesDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CPropertiesDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPERTIES };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


