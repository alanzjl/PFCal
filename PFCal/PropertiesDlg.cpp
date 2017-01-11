// PropertiesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PFCal.h"
#include "PropertiesDlg.h"


// CPropertiesDlg

IMPLEMENT_DYNCREATE(CPropertiesDlg, CFormView)

CPropertiesDlg::CPropertiesDlg()
	: CFormView(IDD_PROPERTIES)
{

}

CPropertiesDlg::~CPropertiesDlg()
{
}

void CPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPropertiesDlg, CFormView)
END_MESSAGE_MAP()


// CPropertiesDlg 诊断

#ifdef _DEBUG
void CPropertiesDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPropertiesDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPropertiesDlg 消息处理程序
