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

// PFCalDoc.h : interface of the CPFCalDoc class
//


#pragma once
#include <list>
#include "Tool.h"
#include "Common.h"
#include "OutputWnd.h"
#include "ComplexMat.h"

#include <Eigen/Dense>
#include "Element_class.h"

class CPFCalDoc : public CDocument
{
protected: // create from serialization only
	CPFCalDoc();
	DECLARE_DYNCREATE(CPFCalDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CPFCalDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnToolsLine();
	afx_msg void OnToolsVtheta();
	afx_msg void OnToolsPq();
	afx_msg void OnToolsPv();
	int m_VtCount, m_BusCount, m_LineCount;
	std::list<CTool*> m_ToolList;
	ToolType m_Tool;
	int m_GridSize;
protected:
	int m_BusIdCount, m_LineIdCount;
	bool DeleteNone(int& busno, int& lineno);	// delete empty id
	int SortBus();		// sort buses and make vtheta the first bus
	bool CalcY();
	
	CComplexMat Y;
public:
	afx_msg void OnUpdateToolsLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateToolsVtheta(CCmdUI *pCmdUI);
	afx_msg void OnUpdateToolsPq(CCmdUI *pCmdUI);
	afx_msg void OnUpdateToolsPv(CCmdUI *pCmdUI);

	//bool CompareRule(CTool* A, CTool* B);
	
	unsigned int GetToolType() const {
		return m_Tool;
	}

	void AddTool(CTool* pTool) {
		m_ToolList.push_back(pTool);
	}

	std::list<CTool*>::const_iterator begin() const {
		return m_ToolList.begin();
	}
	
	std::list<CTool*>::const_iterator end() const {
		return m_ToolList.end();
	}

	int GetBusId() {
		return ++m_BusIdCount;
	}
	int GetLineId() {
		return ++m_LineIdCount;
	}
	int GetVtCount() { return m_VtCount; }
	void DeleteTool(CTool* pTool);

	int JudgePoint(CPoint &point);	// To determine whether a point is in a bus
	CTool* FindTool(CPoint point, ToolType &type);
	afx_msg void OnToolSelect();
	afx_msg void OnUpdateToolSelect(CCmdUI *pCmdUI);
	afx_msg void OnProperties();

	CTool* m_pSelectedTool;
	ToolType m_SelectedToolType;
	afx_msg void OnRun();
	afx_msg void OnFileSave();
	bool m_Draw;	//indicate whether draw on the view

	COutputWnd        m_wndOutput;
	//void Initialize_Bus(Bus bus[]);
	void Calculate_Voltage(Bus bus[], double Y[MAX_BUSES][MAX_BUSES][2]);
	void Calculate_Power(Bus bus[], double Y[MAX_BUSES][MAX_BUSES][2]);
	Bus bus[MAX_BUSES];
	afx_msg void OnButton2();
	afx_msg void OnAbout();
};
