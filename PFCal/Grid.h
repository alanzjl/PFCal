#pragma once
#include "afxcmn.h"


// CGrid �Ի���

class CGrid : public CDialogEx
{
	DECLARE_DYNAMIC(CGrid)

public:
	CGrid(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGrid();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_Grid;
	int m_GridSize;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSliderGrid(NMHDR *pNMHDR, LRESULT *pResult);
};
