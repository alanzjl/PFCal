#pragma once



// CPropertiesDlg ������ͼ

class CPropertiesDlg : public CFormView
{
	DECLARE_DYNCREATE(CPropertiesDlg)

protected:
	CPropertiesDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


