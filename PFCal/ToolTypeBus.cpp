// ToolTypeBus.cpp : 实现文件
//

#include "stdafx.h"
#include "PFCal.h"
#include "ToolTypeBus.h"
#include "afxdialogex.h"


// CToolTypeBus 对话框

IMPLEMENT_DYNAMIC(CToolTypeBus, CDialogEx)

CToolTypeBus::CToolTypeBus(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TOOL_BUS, pParent)
{

}

CToolTypeBus::~CToolTypeBus()
{
}

void CToolTypeBus::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CToolTypeBus, CDialogEx)
	ON_EN_CHANGE(IDC_BUS_VTE, &CToolTypeBus::OnEnChangeBusVte)
	ON_EN_CHANGE(IDC_BUS_VTF, &CToolTypeBus::OnEnChangeBusVtf)
	ON_EN_CHANGE(IDC_BUS_PQP, &CToolTypeBus::OnEnChangeBusPqp)
	ON_EN_CHANGE(IDC_BUS_PQQ, &CToolTypeBus::OnEnChangeBusPqq)
	ON_EN_CHANGE(IDC_BUS_PVP, &CToolTypeBus::OnEnChangeBusPvp)
	ON_EN_CHANGE(IDC_BUS_PVU, &CToolTypeBus::OnEnChangeBusPvu)
	ON_EN_CHANGE(IDC_BUS_RATVOL, &CToolTypeBus::OnEnChangeBusRatvol)
END_MESSAGE_MAP()


// CToolTypeBus 消息处理程序
void CToolTypeBus::SetEditInitial(int nID, double num, int intfloat) {
	CEdit* pId;
	pId = (CEdit*)GetDlgItem(nID);
	CString s1;
	if (intfloat == 1)
		s1.Format(_T("%d"), (int)num);
	else if (intfloat == 0)
		s1.Format(_T("%.2f"), num);
	else
		s1.Format(_T(" "));
	pId->SetWindowTextW(s1);
}

void CToolTypeBus::SetReadOnly(int nID) {
	CEdit* pId;
	pId = (CEdit*)GetDlgItem(nID);
	pId->SetReadOnly(1);
}

void CToolTypeBus::SetNotReadOnly(int nID) {
	CEdit* pId;
	pId = (CEdit*)GetDlgItem(nID);
	pId->SetReadOnly(0);
}

BOOL CToolTypeBus::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetEditInitial(IDC_BUS_RATVOL, m_RatVol, 0);
	SetEditInitial(IDC_BUS_ID, m_Id, 1);
	switch (m_ToolType) {
	case VTHETA: {
		CheckDlgButton(IDC_BUS_TYPE_VT, 1);
		SetEditInitial(IDC_BUS_VTE, m_VtE, 0);
		SetEditInitial(IDC_BUS_VTF, m_VtF, 0);
		SetReadOnly(IDC_BUS_PQP);
		SetReadOnly(IDC_BUS_PQQ);
		SetReadOnly(IDC_BUS_PVP);
		SetReadOnly(IDC_BUS_PVU);
		break;
	}
	case PQ: {
		CheckDlgButton(IDC_BUS_TYPE_PQ, 1);
		SetEditInitial(IDC_BUS_PQP, m_PqP, 0);
		SetEditInitial(IDC_BUS_PQQ, m_PqQ, 0);
		SetReadOnly(IDC_BUS_VTE);
		SetReadOnly(IDC_BUS_VTF);
		SetReadOnly(IDC_BUS_PVP);
		SetReadOnly(IDC_BUS_PVU);
		break;
	}
	case PV: {
		CheckDlgButton(IDC_BUS_TYPE_PV, 1);
		SetEditInitial(IDC_BUS_PVP, m_PvP, 0);
		SetEditInitial(IDC_BUS_PVU, m_PvU, 0);
		SetReadOnly(IDC_BUS_PQP);
		SetReadOnly(IDC_BUS_PQQ);
		SetReadOnly(IDC_BUS_VTE);
		SetReadOnly(IDC_BUS_VTF);
		break;
	}
	default:
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CToolTypeBus::OnEnChangeBusVte()
{
	CString tmp;
	GetDlgItemText(IDC_BUS_VTE, tmp);
	m_VtE = _tstof(tmp);
}


void CToolTypeBus::OnEnChangeBusVtf()
{
	CString tmp;
	GetDlgItemText(IDC_BUS_VTF, tmp);
	m_VtF = _tstof(tmp);
}


void CToolTypeBus::OnEnChangeBusPqp()
{
	CString tmp;
	GetDlgItemText(IDC_BUS_PQP, tmp);
	m_PqP = _tstof(tmp);
	//m_PqP = GetDlgItemInt(IDC_BUS_PQP);
}


void CToolTypeBus::OnEnChangeBusPqq()
{
	CString tmp;
	GetDlgItemText(IDC_BUS_PQQ, tmp);
	m_PqQ = _tstof(tmp);
	//m_PqQ = GetDlgItemInt(IDC_BUS_PQQ);
}


void CToolTypeBus::OnEnChangeBusPvp()
{
	CString tmp;
	GetDlgItemText(IDC_BUS_PVP, tmp);
	m_PvP = _tstof(tmp);
	//m_PvP = GetDlgItemInt(IDC_BUS_PVP);
}


void CToolTypeBus::OnEnChangeBusPvu()
{
	CString tmp;
	GetDlgItemText(IDC_BUS_PVU, tmp);
	m_PvU = _tstof(tmp);
	//m_PvU = GetDlgItemInt(IDC_BUS_PVU);
}


void CToolTypeBus::OnEnChangeBusRatvol()
{
	CString tmp;
	GetDlgItemText(IDC_BUS_RATVOL, tmp);
	m_RatVol = _tstof(tmp);
	//m_RatVol = GetDlgItemInt(IDC_BUS_RATVOL);
}
