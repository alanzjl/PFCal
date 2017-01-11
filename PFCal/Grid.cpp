// Grid.cpp : 实现文件
//

#include "stdafx.h"
#include "PFCal.h"
#include "Grid.h"
#include "afxdialogex.h"


// CGrid 对话框

IMPLEMENT_DYNAMIC(CGrid, CDialogEx)

CGrid::CGrid(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CGrid::~CGrid()
{
}

void CGrid::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_GRID, m_Grid);
}


BEGIN_MESSAGE_MAP(CGrid, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GRID, &CGrid::OnNMCustomdrawSliderGrid)
END_MESSAGE_MAP()


// CGrid 消息处理程序


BOOL CGrid::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Grid.SetRange(10, 100);
	m_Grid.SetPos(m_GridSize);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CGrid::OnNMCustomdrawSliderGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	m_GridSize = m_Grid.GetPos();
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
