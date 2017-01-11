// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PFCalView.cpp : implementation of the CPFCalView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PFCal.h"
#endif

#include "PFCalDoc.h"
#include "PFCalView.h"
#include "Common.h"

#include <cmath>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define GRID_COLOR RGB(180,180,20)
#define SELETED_COLOR RGB(250,0,0)

// CPFCalView

IMPLEMENT_DYNCREATE(CPFCalView, CView)

BEGIN_MESSAGE_MAP(CPFCalView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_TOOL_REMOVE, &CPFCalView::OnToolRemove)
	ON_COMMAND(ID_EDIT_PASTE, &CPFCalView::OnEditPaste)
	ON_COMMAND(ID_EDIT_Remove, &CPFCalView::OnEditRemove)
	ON_COMMAND(ID_EDIT_COPY, &CPFCalView::OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CPFCalView::OnUpdateEditPaste)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CPFCalView construction/destruction

CPFCalView::CPFCalView()
	: m_FirstPoint(CPoint(0,0))
	, m_SecondPoint(CPoint(0,0))
	, m_pTempTool(nullptr)
	, m_pCopiedTool(nullptr)
	, m_IsPaste(FALSE)
{
	// TODO: add construction code here
	m_pSelectedTool = nullptr;
	m_SelectedToolType = LINE;
}

CPFCalView::~CPFCalView()
{
}

BOOL CPFCalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CPFCalView::DrawPoint(CDC* pDC, CPoint point, COLORREF color, int size=0) {
	CPen aPen;
	aPen.CreatePen(PS_SOLID, 1, GRID_COLOR);
	CBrush aBrush;
	aBrush.CreateSolidBrush(color);
	CPen* pOldPen = pDC->SelectObject(&aPen);
	CBrush* pOldBrush = pDC->SelectObject(&aBrush);
	if(size == 0) 
		pDC->Rectangle(point.x - GRID / 10, point.y - GRID / 10, point.x + GRID / 10, point.y + GRID / 10);
	if (size == 1)
		pDC->Rectangle(point.x - GRID / 5, point.y - GRID / 5, point.x + GRID / 5, point.y + GRID / 5);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

// CPFCalView drawing
void CPFCalView::OnDraw(CDC* pDC)
{
	CPFCalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	/***************Mesh Grid***********************/
	
	CRect m_ClientArea;
	GetClientRect(&m_ClientArea);/*
	CPen aPen;
	aPen.CreatePen(PS_SOLID, 1, GRID_COLOR);
	CBrush aBrush;
	aBrush.CreateSolidBrush(GRID_COLOR);
	CPen* pOldPen = pDC->SelectObject(&aPen);
	CBrush* pOldBrush = pDC->SelectObject(&aBrush);*/
	for (int m = 0; m <= m_ClientArea.Width(); m += GRID) {
		for (int n = 0; n <= m_ClientArea.Height(); n += GRID) {
			//pDC->MoveTo(m, n);
			//pDC->Rectangle(m - GRID / 10, n - GRID / 10, m + GRID / 10, n + GRID / 10);
			DrawPoint(pDC, CPoint(m, n), GRID_COLOR);
		}
	}
	//pDC->SelectObject(pOldPen);
	//pDC->SelectObject(pOldBrush);
	/************************************************/
	/******************Reload************************/
	CTool* pTool(nullptr);
	for (auto iter = pDoc->m_ToolList.begin(); iter != pDoc->m_ToolList.end(); ++iter) {
		pTool = *iter;
		if (pDC->RectVisible(pTool->GetBoundRect()))
			pTool->Draw(pDC);
	}
	/************************************************/
	// TODO: add draw code for native data here
}

void CPFCalView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPFCalView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
	/*if (m_pSelectedTool == nullptr)
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_EMPTY_MENU, point.x, point.y, this, TRUE);
	else if (m_SelectedToolType == LINE)
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_LINE_MENU, point.x, point.y, this, TRUE);
	else
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_BUS_MENU, point.x, point.y, this, TRUE);
	if (m_pSelectedTool != nullptr) {
		CString tmp;
		tmp.Format(_T("id:%d type:%d"), m_pSelectedTool->m_Id, m_SelectedToolType);
		MessageBox(tmp);
	}
	else
		MessageBox(_T("NULL"));*/
#endif
}


// CPFCalView diagnostics

#ifdef _DEBUG
void CPFCalView::AssertValid() const
{
	CView::AssertValid();
}

void CPFCalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPFCalDoc* CPFCalView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPFCalDoc)));
	return (CPFCalDoc*)m_pDocument;
}
#endif //_DEBUG


// CPFCalView message handlers


void CPFCalView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_FirstPoint = CPoint(round((double)point.x/GRID)*GRID, round((double)point.y/GRID)*GRID);
	SetCapture();
	//CView::OnLButtonDown(nFlags, point);

	CPFCalDoc* pDoc = GetDocument();
	CClientDC aDC(this);
	if ((nFlags & MK_LBUTTON) && 
		(pDoc->GetToolType() == VTHETA ||
			pDoc->GetToolType() == PQ ||
			pDoc->GetToolType() == PV)
		) {
		m_SecondPoint = CPoint(round((double)point.x / GRID) * GRID, round((double)point.y / GRID) * GRID);
		if (m_pTempTool) {
			aDC.SetROP2(R2_NOTXORPEN);
			m_pTempTool->m_Id = pDoc->GetBusId();
			CString tmp;
			tmp.Format(_T("%d"), m_pTempTool->m_Id);
			//MessageBox(tmp);
			pDoc->AddTool(m_pTempTool);
			InvalidateRect(nullptr);
			m_pTempTool = nullptr;
		}
		m_pTempTool = CreateTool();
		m_pTempTool->Draw(&aDC);

	}
	if (m_pTempTool &&
		(pDoc->GetToolType() == VTHETA ||
			pDoc->GetToolType() == PQ ||
			pDoc->GetToolType() == PV)
		) {
		m_pTempTool->m_Id = pDoc->GetBusId();
		CString tmp;
		tmp.Format(_T("%d"), m_pTempTool->m_Id);
		//MessageBox(tmp);
		pDoc->AddTool(m_pTempTool);
		InvalidateRect(nullptr);
		m_pTempTool = nullptr;
	}
}

CTool* CPFCalView::CreateTool(void) const {
	CPFCalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	switch (pDoc->GetToolType()) {
	case LINE:
		return new CLine(m_FirstPoint, m_SecondPoint);
	case VTHETA:
		return new CVtheta(m_FirstPoint, m_SecondPoint);
	case PQ:
		return new CPq(m_FirstPoint, m_SecondPoint);
	case PV:
		return new CPv(m_FirstPoint, m_SecondPoint);
	default:
		return nullptr;
	}
}


void CPFCalView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPFCalDoc* pDoc = GetDocument();
	CClientDC aDC(this);

	int PointBusNo1 = pDoc->JudgePoint(m_FirstPoint);
	int PointBusNo2 = pDoc->JudgePoint(m_SecondPoint);
	if ((this == GetCapture()) && (nFlags & MK_LBUTTON) &&
		pDoc->GetToolType() == LINE &&
		PointBusNo1 < 0) {
		//MessageBox(_T("Point not in a bus."));
	}
	if ((this == GetCapture()) && (nFlags & MK_LBUTTON) && 
		pDoc->GetToolType() == LINE &&
		PointBusNo1>0) {
		m_SecondPoint = CPoint(round((double)point.x / GRID) * GRID, round((double)point.y / GRID) * GRID);
		
		if (m_pTempTool) {
			aDC.SetROP2(R2_NOTXORPEN);
			m_pTempTool->Draw(&aDC);
			delete m_pTempTool;
			m_pTempTool = nullptr;
		}
		m_pTempTool = CreateTool();
		m_pTempTool->m_IdFrom = PointBusNo1;
		m_pTempTool->m_IdTo = PointBusNo2;
		m_pTempTool->Draw(&aDC);
	}
	if ((this == GetCapture()) && (nFlags & MK_LBUTTON) &&
		pDoc->GetToolType() == VTHETA ||
		pDoc->GetToolType() == PQ || 
		pDoc->GetToolType() == PV) {


	}
	if (pDoc->m_Draw) {
		DrawOutput();
		pDoc->m_Draw = false;
	}
	
	//CView::OnMouseMove(nFlags, point);
}


void CPFCalView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC aDC(this);
	if (this == GetCapture())
		ReleaseCapture();
	CPFCalDoc* pDoc = GetDocument();

	// Paste
	if (m_IsPaste) {
		if (m_pCopiedTool && m_pCopiedTool->GetToolType()!=LINE) {
			CTool* tmp = nullptr;
			if (m_pCopiedTool->GetToolType() == VTHETA) {
				tmp = new CVtheta(point, point);
			}
			else if (m_pCopiedTool->GetToolType() == PQ) {
				tmp = new CPq(point, point);
			}
			else {
				tmp = new CPv(point, point);
			}
	
			tmp->m_Id = pDoc->GetBusId();

			tmp->m_RatVol = m_pCopiedTool->m_RatVol;

			tmp->m_VtE = m_pCopiedTool->m_VtE;
			tmp->m_VtF = m_pCopiedTool->m_VtF;
			tmp->m_PqP = m_pCopiedTool->m_PqP;
			tmp->m_PqQ = m_pCopiedTool->m_PqQ;
			tmp->m_PvP = m_pCopiedTool->m_PvP;
			tmp->m_PvU = m_pCopiedTool->m_PvU;
			
			pDoc->AddTool(tmp);
			tmp->Draw(&aDC);
			InvalidateRect(nullptr);
			m_pTempTool = nullptr;
		}
		m_IsPaste = FALSE;
		return;
	}

	// To determine which tool is selected
	if (pDoc->GetToolType() == SELECT) {
		if (m_pSelectedTool) {
			aDC.SetROP2(R2_NOTXORPEN);
			{
				DrawPoint(&aDC, m_pSelectedTool->GetBoundRect().BottomRight(), SELETED_COLOR, 1);
				DrawPoint(&aDC, m_pSelectedTool->GetBoundRect().TopLeft(), SELETED_COLOR, 1);
				DrawPoint(&aDC, CPoint(m_pSelectedTool->GetBoundRect().TopLeft().x, m_pSelectedTool->GetBoundRect().BottomRight().y)
					, SELETED_COLOR, 1);
				DrawPoint(&aDC, CPoint(m_pSelectedTool->GetBoundRect().BottomRight().x, m_pSelectedTool->GetBoundRect().TopLeft().y)
					, SELETED_COLOR, 1);
			}
			m_pSelectedTool = nullptr;
		}
	
		m_pSelectedTool = pDoc->FindTool(point, m_SelectedToolType);
		if (m_pSelectedTool) {
			aDC.SetROP2(R2_COPYPEN);
			{
				DrawPoint(&aDC, m_pSelectedTool->GetBoundRect().BottomRight(), SELETED_COLOR, 1);
				DrawPoint(&aDC, m_pSelectedTool->GetBoundRect().TopLeft(), SELETED_COLOR, 1);
				DrawPoint(&aDC, CPoint(m_pSelectedTool->GetBoundRect().TopLeft().x, m_pSelectedTool->GetBoundRect().BottomRight().y)
					, SELETED_COLOR, 1);
				DrawPoint(&aDC, CPoint(m_pSelectedTool->GetBoundRect().BottomRight().x, m_pSelectedTool->GetBoundRect().TopLeft().y)
					, SELETED_COLOR, 1);
			}
		}
	}

	// tool type
	if (m_pTempTool && pDoc->GetToolType() == LINE) {
		if (m_pTempTool->m_IdTo < 0 || m_pTempTool->m_IdFrom < 0 ||
			m_pTempTool->m_IdTo == m_pTempTool->m_IdFrom) {
			//MessageBox(_T("Line does not end in a bus."));
			aDC.SetROP2(R2_NOTXORPEN);
			m_pTempTool->Draw(&aDC);
			delete m_pTempTool;
			m_pTempTool = nullptr;
			return;
		}
		m_pTempTool->m_Id = pDoc->GetLineId();
		
		CString tmp;
		tmp.Format(_T("New Line.\nFrom %d to %d.\nID: %d"), 
			m_pTempTool->m_IdFrom, m_pTempTool->m_IdTo, m_pTempTool->m_Id);
		//MessageBox(tmp);
		pDoc->AddTool(m_pTempTool);
		InvalidateRect(nullptr);
		m_pTempTool = nullptr;
	}

	//CView::OnLButtonUp(nFlags, point);
}


void CPFCalView::OnToolRemove()
{
	// TODO: 在此添加命令处理程序代码
}


void CPFCalView::OnEditPaste()
{
	// TODO: 在此添加命令处理程序代码
	m_IsPaste = TRUE;
}


void CPFCalView::OnEditRemove()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pSelectedTool) {
		CPFCalDoc* pDoc = GetDocument();
		pDoc->DeleteTool(m_pSelectedTool);
		pDoc->UpdateAllViews(nullptr);
		m_pSelectedTool = nullptr;
	}
}

void CPFCalView::OnEditCopy()
{
	if (m_pSelectedTool) {
		if (m_pSelectedTool->GetToolType() == VTHETA ||
			m_pSelectedTool->GetToolType() == PQ ||
			m_pSelectedTool->GetToolType() == PV)
			
			m_pCopiedTool = m_pSelectedTool;
	}
}


void CPFCalView::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_IsPaste);
}


void CPFCalView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPFCalDoc* pDoc = GetDocument();
	if(m_pSelectedTool)
		pDoc->OnProperties();
	CView::OnLButtonDblClk(nFlags, point);
}


void CPFCalView::DrawOutput()
{
	// TODO: 在此添加控件通知处理程序代码
	CPFCalDoc* pDoc = GetDocument();
	CClientDC aDC(this);

	CFont m_Font;
	m_Font.CreatePointFont(130, _T("Arial"));
	aDC.SelectObject(&m_Font);
	aDC.SetTextColor(m_OutputColor);
	aDC.SetBkMode(TRANSPARENT);
	CString m_Text;
	CTool* pIter;
	int count = 0;

	for (auto iter = pDoc->m_ToolList.begin(); iter != pDoc->m_ToolList.end(); ++iter) {
		pIter = *iter;
		if (pIter->GetToolType() == VTHETA ||
			pIter->GetToolType() == PQ ||
			pIter->GetToolType() == PV) {

			if (pDoc->bus[count].v.imag() > -0.0000001)
				m_Text.Format(_T("->%.2f + \nj %.2f (kV)"), pDoc->bus[count].v.real(), pDoc->bus[count].v.imag());
			else
				m_Text.Format(_T("->%.2f - \nj %.2f (kV)"), pDoc->bus[count].v.real(), (-1)*pDoc->bus[count].v.imag());
			aDC.TextOutW(pIter->GetBoundRect().TopLeft().x, 
				pIter->GetBoundRect().BottomRight().y + m_RectY*GRID / 3, m_Text);

			++count;
		}
	}
	
}


void CPFCalView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == 8) {	//backspace
		OnEditRemove();
	}
	else if (nChar == 27) {
		CPFCalDoc* pDoc = GetDocument();
		pDoc->m_Tool = SELECT;
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}
