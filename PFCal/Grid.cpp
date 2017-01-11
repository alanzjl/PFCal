// Grid.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PFCal.h"
#include "Grid.h"
#include "afxdialogex.h"


// CGrid �Ի���

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


// CGrid ��Ϣ�������


BOOL CGrid::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Grid.SetRange(10, 100);
	m_Grid.SetPos(m_GridSize);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CGrid::OnNMCustomdrawSliderGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	m_GridSize = m_Grid.GetPos();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
