// PropertiesDlg.cpp : ʵ���ļ�
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


// CPropertiesDlg ���

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


// CPropertiesDlg ��Ϣ�������
