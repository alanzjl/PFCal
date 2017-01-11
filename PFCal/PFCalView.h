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

// PFCalView.h : interface of the CPFCalView class
//

#pragma once
#include "atltypes.h"
#include "Tool.h"


class CPFCalView : public CView
{
protected: // create from serialization only
	CPFCalView();
	DECLARE_DYNCREATE(CPFCalView)
	CTool* CreateTool(void) const;
// Attributes
public:
	CPFCalDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CPFCalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool m_IsPaste;

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	CPoint m_FirstPoint;
	CPoint m_SecondPoint;
	CTool* m_pTempTool;
	CTool* m_pCopiedTool;
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnToolRemove();
	CTool* m_pSelectedTool;
	ToolType m_SelectedToolType;
	afx_msg void OnEditPaste();
	void DrawPoint(CDC* aDC, CPoint point, COLORREF color, int size);
	afx_msg void OnEditRemove();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void DrawOutput();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in PFCalView.cpp
inline CPFCalDoc* CPFCalView::GetDocument() const
   { return reinterpret_cast<CPFCalDoc*>(m_pDocument); }
#endif

