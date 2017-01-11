#pragma once
#include "afxcmn.h"

#include "Element_class.h"
#include "Tool.h"
#include <list>


// COutput �Ի���

class COutput : public CDialogEx
{
	DECLARE_DYNAMIC(COutput)

public:
	COutput(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COutput();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OUTPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_OutputDlg;
	std::list<CTool*>* m_ToolList;
	virtual BOOL OnInitDialog();
	Bus *bus;
};
