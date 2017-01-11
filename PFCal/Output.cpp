// Output.cpp : 实现文件
//

#include "stdafx.h"
#include "PFCal.h"
#include "Output.h"
#include "afxdialogex.h"


// COutput 对话框

IMPLEMENT_DYNAMIC(COutput, CDialogEx)

COutput::COutput(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OUTPUT, pParent)
{

}

COutput::~COutput()
{
}

void COutput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_OUTPUT, m_OutputDlg);
}


BEGIN_MESSAGE_MAP(COutput, CDialogEx)
END_MESSAGE_MAP()


// COutput 消息处理程序


BOOL COutput::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rect;
	m_OutputDlg.GetClientRect(&rect);
	m_OutputDlg.SetExtendedStyle(m_OutputDlg.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_OutputDlg.InsertColumn(0, _T("Bus Type"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_OutputDlg.InsertColumn(1, _T("Bus No."), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_OutputDlg.InsertColumn(2, _T("Voltage"), LVCFMT_CENTER, rect.Width() / 3, 2);
	m_OutputDlg.InsertColumn(3, _T("Voltage (Amplitude)"), LVCFMT_CENTER, rect.Width() / 3, 3);

	CTool* pIter;
	int count = 0;
	CString tmp;
	for (auto iter = m_ToolList->begin(); iter != m_ToolList->end(); ++iter) {
		pIter = *iter;
		if (pIter->GetToolType() == VTHETA){
			m_OutputDlg.InsertItem(count, _T("Vtheta Bus"));
			tmp.Format(_T("%d"), pIter->m_Id);
			m_OutputDlg.SetItemText(count, 1, tmp);
			if(bus[count].v.imag() > -0.000001)
				tmp.Format(_T("%.2f + j%.2f (KV)"), bus[count].v.real(), bus[count].v.imag());
			else
				tmp.Format(_T("%.2f - j%.2f (KV)"), bus[count].v.real(), (-1.0)*bus[count].v.imag());
			m_OutputDlg.SetItemText(count, 2, tmp);

			tmp.Format(_T("%.2f (KV)"), sqrt(bus[count].v.real()*bus[count].v.real() 
				+bus[count].v.imag()*bus[count].v.imag()));
			m_OutputDlg.SetItemText(count, 3, tmp);
			
			count++;
		}
		else if (pIter->GetToolType() == PQ) {
			m_OutputDlg.InsertItem(count, _T("PQ Bus"));
			tmp.Format(_T("%d"), pIter->m_Id);
			m_OutputDlg.SetItemText(count, 1, tmp);
			if (bus[count].v.imag() > -0.000001)
				tmp.Format(_T("%.2f + j %.2f (KV)"), bus[count].v.real(), bus[count].v.imag());
			else
				tmp.Format(_T("%.2f - j %.2f (KV)"), bus[count].v.real(), (-1.0)*bus[count].v.imag());
			m_OutputDlg.SetItemText(count, 2, tmp);

			tmp.Format(_T("%.2f (KV)"), sqrt(bus[count].v.real()*bus[count].v.real()
				+ bus[count].v.imag()*bus[count].v.imag()));
			m_OutputDlg.SetItemText(count, 3, tmp);

			count++;
		}
		else if (pIter->GetToolType() == PV) {
			m_OutputDlg.InsertItem(count, _T("PV Bus"));
			tmp.Format(_T("%d"), pIter->m_Id);
			m_OutputDlg.SetItemText(count, 1, tmp);
			if (bus[count].v.imag() > -0.000001)
				tmp.Format(_T("%.2f + j %.2f (KV)"), bus[count].v.real(), bus[count].v.imag());
			else
				tmp.Format(_T("%.2f - j %.2f (KV)"), bus[count].v.real(), (-1.0)*bus[count].v.imag());
			m_OutputDlg.SetItemText(count, 2, tmp);

			tmp.Format(_T("%.2f (KV)"), sqrt(bus[count].v.real()*bus[count].v.real()
				+ bus[count].v.imag()*bus[count].v.imag()));
			m_OutputDlg.SetItemText(count, 3, tmp);

			count++;
		}
	}
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
