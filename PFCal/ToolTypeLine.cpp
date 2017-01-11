// ToolTypeLine.cpp : 实现文件
//

#include "stdafx.h"
#include "PFCal.h"
#include "ToolTypeLine.h"
#include "afxdialogex.h"


// CToolTypeLine 对话框

IMPLEMENT_DYNAMIC(CToolTypeLine, CDialogEx)

CToolTypeLine::CToolTypeLine(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TOOL_LINE, pParent)
{
	m_Id = -1;
	m_Id_From = -1;
	m_Id_To = -1;
	m_X1 = m_R1 = m_G1 = m_B1 = 0;
	m_Length = 0;
	m_RatVol = 0;
	m_Trans = false;
}

CToolTypeLine::~CToolTypeLine()
{
}

void CToolTypeLine::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolTypeLine, CDialogEx)
	ON_EN_UPDATE(IDC_LINE_ID, &CToolTypeLine::OnEnUpdateLineId)
	ON_BN_CLICKED(IDC_LINE_TRANSFORMERS, &CToolTypeLine::OnBnClickedLineTransformers)
	ON_BN_CLICKED(IDC_LINE_LINE, &CToolTypeLine::OnBnClickedLineLine)
	ON_EN_CHANGE(IDC_LINE_R1, &CToolTypeLine::OnEnChangeLineR1)
	ON_EN_CHANGE(IDC_LINE_X1, &CToolTypeLine::OnEnChangeLineX1)
	ON_EN_CHANGE(IDC_LINE_G1, &CToolTypeLine::OnEnChangeLineG1)
	ON_EN_CHANGE(IDC_LINE_B1, &CToolTypeLine::OnEnChangeLineB1)
	ON_EN_CHANGE(IDC_LINE_L, &CToolTypeLine::OnEnChangeLineL)
	ON_EN_CHANGE(IDC_LINE_RATVOL, &CToolTypeLine::OnEnChangeLineRatvol)
	ON_BN_CLICKED(IDC_LINE_EXANGE, &CToolTypeLine::OnBnClickedLineExange)
	ON_EN_CHANGE(IDC_TRANS_UNH, &CToolTypeLine::OnEnChangeTransUnh)
	ON_EN_CHANGE(IDC_TRANS_UNL, &CToolTypeLine::OnEnChangeTransUnl)
	ON_EN_CHANGE(IDC_TRANS_PK, &CToolTypeLine::OnEnChangeTransPk)
	ON_EN_CHANGE(IDC_TRANS_UK, &CToolTypeLine::OnEnChangeTransUk)
	ON_EN_CHANGE(IDC_TRANS_PO, &CToolTypeLine::OnEnChangeTransPo)
	ON_EN_CHANGE(IDC_TRANS_IO, &CToolTypeLine::OnEnChangeTransIo)
	ON_EN_CHANGE(IDC_TRANS_SN, &CToolTypeLine::OnEnChangeTransSn)
END_MESSAGE_MAP()


// CToolTypeLine 消息处理程序


void CToolTypeLine::OnEnUpdateLineId()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CToolTypeLine::SetEditInitial(int nID, double num, int intfloat) {
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

void CToolTypeLine::SetReadOnly(int nID) {
	CEdit* pId;
	pId = (CEdit*)GetDlgItem(nID);
	pId->SetReadOnly(1);
}

void CToolTypeLine::SetNotReadOnly(int nID) {
	CEdit* pId;
	pId = (CEdit*)GetDlgItem(nID);
	pId->SetReadOnly(0);
}


BOOL CToolTypeLine::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetReadOnly(IDC_LINE_ID_FROM);
	SetReadOnly(IDC_LINE_ID_TO);

	if (m_Trans) {
		CButton* pEx;
		pEx = (CButton*)GetDlgItem(IDC_LINE_EXANGE);
		pEx->EnableWindow(true);

		CheckDlgButton(IDC_LINE_TRANSFORMERS, 1);
		SetReadOnly(IDC_LINE_R1);
		SetReadOnly(IDC_LINE_X1);
		SetReadOnly(IDC_LINE_G1);
		SetReadOnly(IDC_LINE_B1);
		SetReadOnly(IDC_LINE_L);
	}
	else {
		CButton* pEx;
		pEx = (CButton*)GetDlgItem(IDC_LINE_EXANGE);
		pEx->EnableWindow(false);	// needn't exchange when it's line

		CheckDlgButton(IDC_LINE_LINE, 1);
		SetReadOnly(IDC_TRANS_UK);
		SetReadOnly(IDC_TRANS_PK);
		SetReadOnly(IDC_TRANS_PO);
		SetReadOnly(IDC_TRANS_IO);
		SetReadOnly(IDC_TRANS_UNH);
		SetReadOnly(IDC_TRANS_UNL);
		SetReadOnly(IDC_TRANS_SN);
	}

	// TODO:  在此添加额外的初始化
	SetEditInitial(IDC_LINE_ID, m_Id, true);
	SetEditInitial(IDC_LINE_RATVOL, m_RatVol, true);

	// transmission lines
	SetEditInitial(IDC_LINE_ID_FROM, m_Id_From, true);
	SetEditInitial(IDC_LINE_ID_TO, m_Id_To, true);
	SetEditInitial(IDC_LINE_R1, m_R1, false);
	SetEditInitial(IDC_LINE_X1, m_X1, false);
	SetEditInitial(IDC_LINE_G1, m_G1, false);
	SetEditInitial(IDC_LINE_B1, m_B1, false);
	SetEditInitial(IDC_LINE_L, m_Length, false);

	// transformers
	SetEditInitial(IDC_TRANS_SN, m_Sn, true);
	SetEditInitial(IDC_TRANS_UNH, m_Uh, false);
	SetEditInitial(IDC_TRANS_UNL, m_Ul, false);
	SetEditInitial(IDC_TRANS_PO, m_Po, false);
	SetEditInitial(IDC_TRANS_PK, m_Pk, false);
	SetEditInitial(IDC_TRANS_IO, m_Io, false);
	SetEditInitial(IDC_TRANS_UK, m_Uk, false);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CToolTypeLine::OnBnClickedLineTransformers()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Trans = true;

	CButton* pEx;
	pEx = (CButton*)GetDlgItem(IDC_LINE_EXANGE);
	pEx->EnableWindow(true);

	SetReadOnly(IDC_LINE_R1);
	SetReadOnly(IDC_LINE_X1);
	SetReadOnly(IDC_LINE_G1);
	SetReadOnly(IDC_LINE_B1);
	SetReadOnly(IDC_LINE_L);
	SetEditInitial(IDC_LINE_ID_FROM, m_Id_From, 1);
	SetEditInitial(IDC_LINE_ID_TO, m_Id_To, 1);

	SetNotReadOnly(IDC_TRANS_SN);
	SetNotReadOnly(IDC_TRANS_UK);
	SetNotReadOnly(IDC_TRANS_PK);
	SetNotReadOnly(IDC_TRANS_PO);
	SetNotReadOnly(IDC_TRANS_IO);
	SetNotReadOnly(IDC_TRANS_UNH);
	SetNotReadOnly(IDC_TRANS_UNL);
}


void CToolTypeLine::OnBnClickedLineLine()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Trans = false;

	CButton* pEx;
	pEx = (CButton*)GetDlgItem(IDC_LINE_EXANGE);
	pEx->EnableWindow(false);	// needn't exchange when it's line

	SetNotReadOnly(IDC_LINE_R1);
	SetNotReadOnly(IDC_LINE_X1);
	SetNotReadOnly(IDC_LINE_G1);
	SetNotReadOnly(IDC_LINE_B1);
	SetNotReadOnly(IDC_LINE_L);
	SetEditInitial(IDC_LINE_ID_FROM, m_Id_From, 1);
	SetEditInitial(IDC_LINE_ID_TO, m_Id_To, 1);

	SetReadOnly(IDC_TRANS_UK);
	SetReadOnly(IDC_TRANS_PK);
	SetReadOnly(IDC_TRANS_PO);
	SetReadOnly(IDC_TRANS_IO);
	SetReadOnly(IDC_TRANS_UNH);
	SetReadOnly(IDC_TRANS_UNL);
	SetReadOnly(IDC_TRANS_SN);
}


void CToolTypeLine::OnEnChangeLineR1()
{
	CString tmp;
	GetDlgItemText(IDC_LINE_R1, tmp);
	m_R1 = _tstof(tmp);
	//m_R1 = GetDlgItemInt(IDC_LINE_R1);
}


void CToolTypeLine::OnEnChangeLineX1()
{
	CString tmp;
	GetDlgItemText(IDC_LINE_X1, tmp);
	m_X1 = _tstof(tmp);
	//m_X1 = GetDlgItemInt(IDC_LINE_X1);
}


void CToolTypeLine::OnEnChangeLineG1()
{
	CString tmp;
	GetDlgItemText(IDC_LINE_G1, tmp);
	m_G1 = _tstof(tmp);
	//m_G1 = GetDlgItemInt(IDC_LINE_G1);
}


void CToolTypeLine::OnEnChangeLineB1()
{
	CString tmp;
	GetDlgItemText(IDC_LINE_B1, tmp);
	m_B1 = _tstof(tmp);
	//m_B1 = GetDlgItemInt(IDC_LINE_B1);
}


void CToolTypeLine::OnEnChangeLineL()
{
	CString tmp;
	GetDlgItemText(IDC_LINE_L, tmp);
	m_Length = _tstof(tmp);
	//m_Length = GetDlgItemInt(IDC_LINE_L);
}


void CToolTypeLine::OnEnChangeLineRatvol()
{
	CString tmp;
	GetDlgItemText(IDC_LINE_RATVOL, tmp);
	m_RatVol = _tstof(tmp);
	//m_RatVol = GetDlgItemInt(IDC_LINE_RATVOL);
}


void CToolTypeLine::OnBnClickedLineExange()
{
	// TODO: 在此添加控件通知处理程序代码
	int tmp = m_Id_From;
	m_Id_From = m_Id_To;
	m_Id_To = tmp;
	SetEditInitial(IDC_LINE_ID_FROM, m_Id_From, 1);
	SetEditInitial(IDC_LINE_ID_TO, m_Id_To, 1);
}



void CToolTypeLine::OnEnChangeTransUnh()
{
	CString tmp;
	GetDlgItemText(IDC_TRANS_UNH, tmp);
	m_Uh = _tstof(tmp);
	//m_Uh = GetDlgItemInt(IDC_TRANS_UNH);
}


void CToolTypeLine::OnEnChangeTransUnl()
{
	CString tmp;
	GetDlgItemText(IDC_TRANS_UNL, tmp);
	m_Ul = _tstof(tmp);
	//m_Ul = GetDlgItemInt(IDC_TRANS_UNL);
}


void CToolTypeLine::OnEnChangeTransPk()
{
	CString tmp;
	GetDlgItemText(IDC_TRANS_PK, tmp);
	m_Pk = _tstof(tmp);
	//m_Pk = GetDlgItemInt(IDC_TRANS_PK);
}


void CToolTypeLine::OnEnChangeTransUk()
{
	CString tmp;
	GetDlgItemText(IDC_TRANS_UK, tmp);
	m_Uk = _tstof(tmp);
	//m_Uk = GetDlgItemInt(IDC_TRANS_UK);
}


void CToolTypeLine::OnEnChangeTransPo()
{
	CString tmp;
	GetDlgItemText(IDC_TRANS_PO, tmp);
	m_Po = _tstof(tmp);
	//m_Po = GetDlgItemInt(IDC_TRANS_PO);
}


void CToolTypeLine::OnEnChangeTransIo()
{
	CString tmp;
	GetDlgItemText(IDC_TRANS_IO, tmp);
	m_Io = _tstof(tmp);
	//m_Io = GetDlgItemInt(IDC_TRANS_IO);
}


void CToolTypeLine::OnEnChangeTransSn()
{
	CString tmp;
	GetDlgItemText(IDC_TRANS_SN, tmp);
	m_Sn = _tstof(tmp);
	//m_Sn = GetDlgItemInt(IDC_TRANS_SN);
}
