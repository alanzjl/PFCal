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

// PFCalDoc.cpp : implementation of the CPFCalDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PFCal.h"
#endif

#include "PFCalDoc.h"
#include "ToolTypeLine.h"
#include "ToolTypeBus.h"
#include "Output.h"
#include "Grid.h"
#include "About.h"

#include <algorithm>

#include <propkey.h>

using namespace Eigen;
//using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPFCalDoc

IMPLEMENT_DYNCREATE(CPFCalDoc, CDocument)

BEGIN_MESSAGE_MAP(CPFCalDoc, CDocument)
	ON_COMMAND(ID_TOOLS_LINE, &CPFCalDoc::OnToolsLine)
	ON_COMMAND(ID_TOOLS_VTHETA, &CPFCalDoc::OnToolsVtheta)
	ON_COMMAND(ID_TOOLS_PQ, &CPFCalDoc::OnToolsPq)
	ON_COMMAND(ID_TOOLS_PV, &CPFCalDoc::OnToolsPv)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_LINE, &CPFCalDoc::OnUpdateToolsLine)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_VTHETA, &CPFCalDoc::OnUpdateToolsVtheta)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_PQ, &CPFCalDoc::OnUpdateToolsPq)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_PV, &CPFCalDoc::OnUpdateToolsPv)
	ON_COMMAND(ID_TOOL_SELECT, &CPFCalDoc::OnToolSelect)
	ON_UPDATE_COMMAND_UI(ID_TOOL_SELECT, &CPFCalDoc::OnUpdateToolSelect)
	ON_COMMAND(ID_PROPERTIES, &CPFCalDoc::OnProperties)
	ON_COMMAND(ID_RUN, &CPFCalDoc::OnRun)
	ON_COMMAND(ID_FILE_SAVE, &CPFCalDoc::OnFileSave)
	ON_COMMAND(ID_BUTTON2, &CPFCalDoc::OnButton2)
	ON_COMMAND(ID_ABOUT, &CPFCalDoc::OnAbout)
END_MESSAGE_MAP()


// CPFCalDoc construction/destruction

CPFCalDoc::CPFCalDoc()
{
	// TODO: add one-time construction code here
	m_Tool = SELECT;
	m_BusIdCount = 0;
	m_LineIdCount = 0;
	m_pSelectedTool = nullptr;
	m_SelectedToolType = LINE;
	m_VtCount = 0;
	m_BusCount = -1;
	m_LineCount = -1;
	m_Draw = false;
	m_GridSize = 50;
}

CPFCalDoc::~CPFCalDoc()
{
	for (auto iter = m_ToolList.begin(); iter != m_ToolList.end(); ++iter)
		delete *iter;
	m_ToolList.clear();
}

BOOL CPFCalDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CPFCalDoc serialization

void CPFCalDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		CString tmp;
		tmp.Format(_T("%d\n"), m_ToolList.size()); ar << tmp;
		tmp.Format(_T("%d\n"), m_BusIdCount); ar << tmp;
		tmp.Format(_T("%d\n"), m_LineIdCount); ar << tmp;


		CTool* pIter;
		for (auto iter = m_ToolList.begin(); iter != m_ToolList.end(); ++iter) {
			pIter = *iter;
			if(pIter->GetToolType() == LINE)
				tmp.Format(_T("%d"), 0); 
			else if (pIter->GetToolType() == VTHETA)
				tmp.Format(_T("%d"), 1);
			else if (pIter->GetToolType() == PQ)
				tmp.Format(_T("%d"), 2);
			else
				tmp.Format(_T("%d"), 3);
			ar << tmp;
			tmp.Format(_T("%ld"), pIter->m_StartPoint.x); ar << tmp;
			tmp.Format(_T("%ld"), pIter->m_StartPoint.y); ar << tmp;
			tmp.Format(_T("%ld"), pIter->m_EndPoint.x); ar << tmp;
			tmp.Format(_T("%ld"), pIter->m_EndPoint.y); ar << tmp;
			
			tmp.Format(_T("%d"), pIter->m_Id); ar << tmp;
			tmp.Format(_T("%d"), pIter->m_IdFrom); ar << tmp;
			tmp.Format(_T("%d"), pIter->m_IdTo); ar << tmp;
			
			tmp.Format(_T("%lf"), pIter->m_RatVol); ar << tmp;
			tmp.Format(_T("%d"), pIter->m_Trans ? 1 : 0); ar << tmp;

			tmp.Format(_T("%lf"), pIter->m_X1); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_R1); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_G1); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_B1); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_Length); ar << tmp;

			tmp.Format(_T("%lf"), pIter->m_Sn); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_Uh); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_Ul); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_Uk); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_Pk); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_Po); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_Io); ar << tmp;

			tmp.Format(_T("%lf"), pIter->m_VtE); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_VtF); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_PqP); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_PqQ); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_PvP); ar << tmp;
			tmp.Format(_T("%lf"), pIter->m_PvU); ar << tmp;
		}
	}
	else
	{
		// TODO: add loading code here
		//m_ToolList.clear();
		CTool* tool;
		CString tmp;
		int totalNum;
		ar >> tmp; totalNum = _ttoi(tmp);
		ar >> tmp; m_BusIdCount = _ttoi(tmp);
		ar >> tmp; m_LineIdCount = _ttoi(tmp);
		LONG s_x, s_y, e_x, e_y;
		int type, id, idFrom, idTo;
		for (int i = 0; i < totalNum; i++) {
			ar >> tmp;
			type = _ttoi(tmp);
			ar >> tmp; s_x = _ttol(tmp); ar >> tmp; s_y = _ttol(tmp);
			ar >> tmp; e_x = _ttol(tmp); ar >> tmp; e_y = _ttol(tmp);
			
			if (type == 0) {
				tool = new CLine(CPoint(s_x, s_y), CPoint(e_x, e_y));
			}
			else if (type == 1) {
				tool = new CVtheta(CPoint(s_x, s_y), CPoint(e_x, e_y));
			}
			else if (type == 2) {
				tool = new CPq(CPoint(s_x, s_y), CPoint(e_x, e_y));
			}
			else {
				tool = new CPv(CPoint(s_x, s_y), CPoint(e_x, e_y));
			}

			ar >> tmp; tool->m_Id = _ttol(tmp); 
			ar >> tmp; tool->m_IdFrom = _ttol(tmp); 
			ar >> tmp; tool->m_IdTo = _ttol(tmp);

			ar >> tmp; tool->m_RatVol = _ttof(tmp);
			ar >> tmp; tool->m_Trans = _ttoi(tmp) ? true : false;

			ar >> tmp; tool->m_X1 = _ttof(tmp);
			ar >> tmp; tool->m_R1 = _ttof(tmp);
			ar >> tmp; tool->m_G1 = _ttof(tmp);
			ar >> tmp; tool->m_B1 = _ttof(tmp);
			ar >> tmp; tool->m_Length = _ttof(tmp);

			ar >> tmp; tool->m_Sn = _ttof(tmp);
			ar >> tmp; tool->m_Uh = _ttof(tmp);
			ar >> tmp; tool->m_Ul = _ttof(tmp);
			ar >> tmp; tool->m_Uk = _ttof(tmp);
			ar >> tmp; tool->m_Pk = _ttof(tmp);
			ar >> tmp; tool->m_Po = _ttof(tmp);
			ar >> tmp; tool->m_Io = _ttof(tmp);

			ar >> tmp; tool->m_VtE = _ttof(tmp);
			ar >> tmp; tool->m_VtF = _ttof(tmp);
			ar >> tmp; tool->m_PqP = _ttof(tmp);
			ar >> tmp; tool->m_PqQ = _ttof(tmp);
			ar >> tmp; tool->m_PvP = _ttof(tmp);
			ar >> tmp; tool->m_PvU = _ttof(tmp);

			AddTool(tool);
			//UpdateAllViews(nullptr);
		}

	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPFCalDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPFCalDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPFCalDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPFCalDoc diagnostics

#ifdef _DEBUG
void CPFCalDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPFCalDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPFCalDoc commands

void CPFCalDoc::OnToolsLine()
{
	// TODO: 在此添加命令处理程序代码
	m_Tool = LINE;
}

void CPFCalDoc::OnToolsVtheta()
{
	// TODO: 在此添加命令处理程序代码
	m_Tool = VTHETA;
}

void CPFCalDoc::OnToolsPq()
{
	// TODO: 在此添加命令处理程序代码
	m_Tool = PQ;
}

void CPFCalDoc::OnToolsPv()
{
	// TODO: 在此添加命令处理程序代码
	m_Tool = PV;
}

void CPFCalDoc::OnToolSelect()
{
	// TODO: 在此添加命令处理程序代码
	m_Tool = SELECT;
}

void CPFCalDoc::OnUpdateToolsLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_Tool == LINE);
}

void CPFCalDoc::OnUpdateToolsVtheta(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_Tool == VTHETA);
}

void CPFCalDoc::OnUpdateToolsPq(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_Tool == PQ);
}

void CPFCalDoc::OnUpdateToolSelect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_Tool == SELECT);
}

void CPFCalDoc::OnUpdateToolsPv(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_Tool == PV);
}

int CPFCalDoc::JudgePoint(CPoint &point) {
	CTool* pTool(nullptr);
	for (auto iter = m_ToolList.begin(); iter != m_ToolList.end(); ++iter) {
		pTool = *iter;
		if (pTool->GetToolType() != LINE) {
			if (pTool->GetBoundRect().PtInRect(point)) {
				CRect temp = pTool->GetBoundRect();
				if (temp.CenterPoint().x > point.x)
					point.x = temp.TopLeft().x + GRID/10;
				else
					point.x = temp.BottomRight().x - GRID / 10;
				return pTool->m_Id;
			}
		}
	}
	return -1;
}

CTool* CPFCalDoc::FindTool(CPoint point, ToolType &type) {
	CTool* pTool(nullptr);
	for (auto iter = m_ToolList.begin(); iter != m_ToolList.end(); ++iter) {
		pTool = *iter;
		if (pTool->GetBoundRect().PtInRect(point)) {
			type = pTool->GetToolType();
			m_SelectedToolType = type;
			m_pSelectedTool = pTool;
			return pTool;
		}
	}
	m_pSelectedTool = nullptr;
	return nullptr;
}

void CPFCalDoc::DeleteTool(CTool* pTool) {
	if (pTool->GetToolType() == LINE) {
		m_ToolList.remove(pTool);
		delete pTool;
	}
	else if(pTool->GetToolType() == VTHETA ||
		pTool->GetToolType() == PQ || 
		pTool->GetToolType() == PV){
		CTool* pIterTool(nullptr);
		for (auto iter = m_ToolList.begin(); iter != m_ToolList.end(); ++iter) {
			pIterTool = *iter;
			if (pIterTool->GetToolType() == LINE) {
				if (pIterTool->m_IdFrom == pTool->m_Id ||
					pIterTool->m_IdTo == pTool->m_Id) {
					m_ToolList.remove(pIterTool);
					delete pIterTool;
					DeleteTool(pTool);
					return;
				}
			}
		}
		m_ToolList.remove(pTool);
		delete pTool;
	}
	UpdateAllViews(nullptr);
}

void CPFCalDoc::OnProperties()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pSelectedTool && m_SelectedToolType == LINE) {
		CToolTypeLine aDlg;
		aDlg.m_Id = m_pSelectedTool->m_Id;
		aDlg.m_RatVol = m_pSelectedTool->m_RatVol;
		aDlg.m_Trans = m_pSelectedTool->m_Trans;

		// initial for lines
		aDlg.m_Id_From = m_pSelectedTool->m_IdFrom;
		aDlg.m_Id_To = m_pSelectedTool->m_IdTo;
		aDlg.m_X1 = m_pSelectedTool->m_X1;
		aDlg.m_R1 = m_pSelectedTool->m_R1;
		aDlg.m_G1 = m_pSelectedTool->m_G1;
		aDlg.m_B1 = m_pSelectedTool->m_B1;
		aDlg.m_Length = m_pSelectedTool->m_Length;
		// initial for transformers
		aDlg.m_Uh = m_pSelectedTool->m_Uh;
		aDlg.m_Ul = m_pSelectedTool->m_Ul;
		aDlg.m_Pk = m_pSelectedTool->m_Pk;
		aDlg.m_Po = m_pSelectedTool->m_Po;
		aDlg.m_Io = m_pSelectedTool->m_Io;
		aDlg.m_Sn = m_pSelectedTool->m_Sn;
		aDlg.m_Uk = m_pSelectedTool->m_Uk;



		if (aDlg.DoModal() == IDOK) {
			m_pSelectedTool->m_RatVol = aDlg.m_RatVol;
			m_pSelectedTool->m_Trans = aDlg.m_Trans;
			// for lines
			m_pSelectedTool->m_IdFrom = aDlg.m_Id_From;
			m_pSelectedTool->m_IdTo = aDlg.m_Id_To;
			m_pSelectedTool->m_X1 = aDlg.m_X1;
			m_pSelectedTool->m_R1 = aDlg.m_R1;
			m_pSelectedTool->m_G1 = aDlg.m_G1;
			m_pSelectedTool->m_B1 = aDlg.m_B1;
			m_pSelectedTool->m_Length = aDlg.m_Length;
			// for transformers
			m_pSelectedTool->m_Uh = aDlg.m_Uh;
			m_pSelectedTool->m_Ul = aDlg.m_Ul;
			m_pSelectedTool->m_Pk = aDlg.m_Pk;
			m_pSelectedTool->m_Po = aDlg.m_Po;
			m_pSelectedTool->m_Io = aDlg.m_Io;
			m_pSelectedTool->m_Uk = aDlg.m_Uk;
			m_pSelectedTool->m_Sn = aDlg.m_Sn;
		}
	}
	else if (m_pSelectedTool &&
		(m_SelectedToolType == VTHETA ||
			m_SelectedToolType == PQ ||
			m_SelectedToolType == PV)) {
		CToolTypeBus aDlg;

		aDlg.m_ToolType = m_pSelectedTool->GetToolType();
		aDlg.m_Id = m_pSelectedTool->m_Id;
		aDlg.m_RatVol = m_pSelectedTool->m_RatVol;

		aDlg.m_VtE = m_pSelectedTool->m_VtE;
		aDlg.m_VtF = m_pSelectedTool->m_VtF;

		aDlg.m_PqP = m_pSelectedTool->m_PqP;
		aDlg.m_PqQ = m_pSelectedTool->m_PqQ;

		aDlg.m_PvP = m_pSelectedTool->m_PvP;
		aDlg.m_PvU = m_pSelectedTool->m_PvU;

		if (aDlg.DoModal() == IDOK) {
			m_pSelectedTool->m_RatVol = aDlg.m_RatVol;

			m_pSelectedTool->m_VtE = aDlg.m_VtE;
			m_pSelectedTool->m_VtF = aDlg.m_VtF;

			m_pSelectedTool->m_PqP = aDlg.m_PqP;
			m_pSelectedTool->m_PqQ = aDlg.m_PqQ;

			m_pSelectedTool->m_PvP = aDlg.m_PvP;
			m_pSelectedTool->m_PvU = aDlg.m_PvU;
		}
	}
	UpdateAllViews(nullptr);
}

bool CPFCalDoc::DeleteNone(int & busno, int & lineno) {
	// To resort IDs of every Bus/Line
	busno = 0; lineno = 0;
	CTool* pIter(nullptr);
	CTool* pIter2(nullptr);
	int startid = 1;
	int tmpid;
	for (auto iter = m_ToolList.begin(); iter != m_ToolList.end(); ++iter) {
		pIter = *iter;
		if (pIter->GetToolType() != LINE) {
			busno++;
			if (pIter->m_Id != startid) {
				tmpid = pIter->m_Id;
				pIter->m_Id = startid;
				for (auto iter2 = m_ToolList.begin(); iter2 != m_ToolList.end(); ++iter2) {
					pIter2 = *iter2;
					if (pIter2->GetToolType() == LINE) {
						if (pIter2->m_IdFrom == tmpid)
							pIter2->m_IdFrom = startid;
						else if (pIter2->m_IdTo == tmpid)
							pIter2->m_IdTo = startid;
					}
				}
			}
			startid++;
		}
		else
			lineno++;
	}
	return true;
}

bool CompareRule(CTool* A, CTool* B) {
	return (A->m_Id < B->m_Id);
}

int CPFCalDoc::SortBus() {
	int VtCount = 0;
	int CurrentId;
	bool BusModified = false;
	CTool* pIter(nullptr);
	CTool* pIter2(nullptr);
	for (auto iter = m_ToolList.begin(); iter != m_ToolList.end(); ++iter) {
		pIter = *iter;
		CurrentId = pIter->m_Id;
		BusModified = false;
		if (pIter->GetToolType() == LINE)
			continue;
		if (pIter->GetToolType() == VTHETA) {
			VtCount++;
			if (CurrentId == VtCount)
				continue;
			else {
				for (auto iter2 = m_ToolList.begin(); iter2 != m_ToolList.end(); ++iter2) {
					pIter2 = *iter2;
					if (pIter2->GetToolType() == LINE) {
						if (pIter2->m_IdFrom == CurrentId) 
							pIter2->m_IdFrom = VtCount;
						else if (pIter2->m_IdFrom == VtCount)
							pIter2->m_IdFrom = CurrentId;
						if (pIter2->m_IdTo == CurrentId)
							pIter2->m_IdTo = VtCount;
						else if (pIter2->m_IdTo == VtCount)
							pIter2->m_IdTo = CurrentId;
					}
					else if(!BusModified) {			// Make sure only one pair of buses exchange id
						if (pIter2->m_Id == VtCount) {
							pIter2->m_Id = CurrentId;
							BusModified = true;
							pIter->m_Id = VtCount;
						}
					}
				}
			}
		}
	}
	m_VtCount = VtCount;
	m_ToolList.sort(CompareRule);
	//std::sort(m_ToolList.begin(), m_ToolList.end(), CompareRule);
	return VtCount;
}

bool CPFCalDoc::CalcY() {
	CTool* pIter;
	pIter = *m_ToolList.begin();
	double baseVol = pIter->m_RatVol;	// get the base voltage
	double k;
	pIter = nullptr;

	Y.Initialize();

	int busCount = 0;
	double R, X, Rt, Xt, G, B;
	for (auto iter = m_ToolList.begin(); iter != m_ToolList.end(); ++iter) {
		pIter = *iter;
		if (pIter->GetToolType() == LINE) {
			if (pIter->m_Trans) {	//for transformers
				// Z = R+jX, Y = G+jB 
				k = baseVol / pIter->m_RatVol;
				R = k * k * (pIter->m_Pk * pIter->m_Uh * pIter->m_Uh) / (1000 * pIter->m_Sn * pIter->m_Sn);
				X = k * k * (pIter->m_Uk * pIter->m_Uh * pIter->m_Uh) / (100 * pIter->m_Sn);
				// 1/(R+jX) = Rt + jXt
				Rt = Y.InverseReal(R, X);
				Xt = Y.InverseImg(R, X);
				
				G = (pIter->m_Po) / (1000 * pIter->m_Uh * pIter->m_Uh);
				B = (pIter->m_Io * pIter->m_Sn) / (100 * pIter->m_Uh * pIter->m_Uh);
				G /= k * k;
				B /= k * k;
				// for Yii, i equals idfrom and idto
				Y.Add(pIter->m_IdFrom, pIter->m_IdFrom, Rt + G, Xt + B);
				Y.Add(pIter->m_IdTo, pIter->m_IdTo, Rt, Xt);
				// for Yij
				Y.Add(pIter->m_IdFrom, pIter->m_IdTo, -Rt, -Xt);
				Y.Add(pIter->m_IdTo, pIter->m_IdFrom, -Rt, -Xt);
			}
			else {		// for transmission lines
				k = baseVol / pIter->m_RatVol;
				// Z = R + jX, Y = G + jB
				R = k * k * (pIter->m_R1 * pIter->m_Length);
				X = k * k * (pIter->m_X1 * pIter->m_Length);
				// 1/(R+jX) = Rt + jXt
				Rt = Y.InverseReal(R, X);
				Xt = Y.InverseImg(R, X);

				G = (pIter->m_G1 * pIter->m_Length) / (k * k);
				B = (pIter->m_B1 * pIter->m_Length) / (k * k);
				// for Yii, i equals idfrom and idto
				Y.Add(pIter->m_IdFrom, pIter->m_IdFrom, Rt + G/2, Xt + B/2);	
				Y.Add(pIter->m_IdTo, pIter->m_IdTo, Rt + G/2, Xt + B/2);
				// for Yij
				Y.Add(pIter->m_IdFrom, pIter->m_IdTo, -Rt, -Xt);
				Y.Add(pIter->m_IdTo, pIter->m_IdFrom, -Rt, -Xt);
			}
		}
		else {
			// Bus initialization
			if (pIter->GetToolType() == PQ) {
				bus[busCount].type = Bus_PQ;
				bus[busCount].P = pIter->m_PqP;
				bus[busCount].Q = pIter->m_PqQ;
				bus[busCount].v_rating = pIter->m_RatVol;
				Complex init(220, 0);
				bus[busCount].v_es[0] = init;

			}
			else if (pIter->GetToolType() == PV) {
				bus[busCount].type = Bus_PV;
				bus[busCount].v_mag = pIter->m_PvU;
				bus[busCount].P = pIter->m_PvP;
				bus[busCount].v_rating = pIter->m_RatVol;
				Complex init(220, 0);
				bus[busCount].v_es[0] = init;
			}
			else if (pIter->GetToolType() == VTHETA) {
				bus[busCount].type = Bus_VT;
				bus[busCount].v.set(pIter->m_VtE, pIter->m_VtF);
				bus[busCount].v_rating = pIter->m_RatVol;
				for (int j = 0; j < MAX_ITERATION; j++)				//initailize  v_theta voltage
				{
					bus[busCount].v_es[j] = bus[busCount].v;
				}
			}
			++busCount;
		}
	}
	return true;
}

/*void CPFCalDoc::Initialize_Bus(Bus bus[])
{
	for (int i = 0; i < total_buses; i++)
	{
		if (bus[i].type != Bus_VT)								//not V_theta bus
		{
			Complex init(1, 0);
			bus[i].v_es[0] = init;								//initailize voltage: 220+j0
		}
		else
		{
			for (int j = 0; j < MAX_ITERATION; j++)				//initailize  v_theta voltage
			{
				bus[i].v_es[j] = bus[i].v;
			}
		}
	}
}*/

void CPFCalDoc::Calculate_Voltage(Bus bus[], double Y[MAX_BUSES][MAX_BUSES][2])
{
	int total_buses = m_BusCount;
	int num_VT = m_VtCount;
	int itr_num = 0;								 	//number of interaction
	int equ_num = 2 * (total_buses - num_VT);		   //number of eqations
	VectorXd delta_f(equ_num);
	MatrixXd J(equ_num, equ_num);					  //Jacobi matrix

	while (1)
	{
		for (int i = 1; i < total_buses; i++)	//将 v_theta 置于0 
		{
			int row = 2 * (i - num_VT);
			if (bus[i].type == Bus_PQ)
			{
				//calculate aii and bii
				double aii = 0, bii = 0;
				for (int j = 0; j < total_buses; j++)
				{
					aii += Y[i][j][0] * bus[j].v_es[itr_num].real() -					//Ge-Bf
						Y[i][j][1] * bus[j].v_es[itr_num].imag();

					bii += Y[i][j][0] * bus[j].v_es[itr_num].imag() +			//Gf+Be
						Y[i][j][1] * bus[j].v_es[itr_num].real();

					//set Jacobi matrix
					int col = 2 * j;

					if (j >= total_buses - num_VT || row < 0) continue;
					//Hij
					J(row, col) = -Y[i][j + num_VT][1] * bus[i].v_es[itr_num].real()	//不算0行0列
						+ Y[i][j + num_VT][0] * bus[i].v_es[itr_num].imag();

					//Nij
					J(row, col + 1) = +Y[i][j + num_VT][0] * bus[i].v_es[itr_num].real()
						+ Y[i][j + num_VT][1] * bus[i].v_es[itr_num].imag();

					//Jij = -Nij
					J(row + 1, col) = -J(row, col + 1);

					//Lij = Hij
					J(row + 1, col + 1) = J(row, col);
				}

				bus[i].P_es[itr_num] = bus[i].v_es[itr_num].real() * aii +			//Pi
					bus[i].v_es[itr_num].imag() * bii;

				bus[i].Q_es[itr_num] = bus[i].v_es[itr_num].imag() * aii -		//Qi
					bus[i].v_es[itr_num].real() * bii;

				for (int j = 0; j < total_buses - num_VT; j++)
				{
					int col = 2 * j;
					if (i == j + num_VT)					// on diagonal
					{
						//modify Hii
						J(row, col) += bii;
						//modify Nii
						J(row, col + 1) += aii;
						//modify Jii
						J(row + 1, col) += aii;
						//modify Lii
						J(row + 1, col + 1) -= bii;
					}
				}

				//cout << "J: " << endl << J << endl;

				delta_f[row] = bus[i].P - bus[i].P_es[itr_num];
				delta_f[row + 1] = bus[i].Q - bus[i].Q_es[itr_num];		//set delta_f
			}

			else if (bus[i].type == Bus_PV)
			{
				//calculate aii and bii
				double aii = 0, bii = 0;
				int row = 2 * (i - num_VT);
				for (int j = 0; j < total_buses; j++)
				{
					aii += Y[i][j][0] * bus[j].v_es[itr_num].real() -					//Ge-Bf
						Y[i][j][1] * bus[j].v_es[itr_num].imag();

					bii += Y[i][j][0] * bus[j].v_es[itr_num].imag() +			//Gf+Be
						Y[i][j][1] * bus[j].v_es[itr_num].real();

					//set Jacobi matrix
					int col = 2 * j;

					if (j >= total_buses - num_VT || row < 0) continue;
					//Hij
					J(row, col) = -Y[i][j + num_VT][0] * bus[i].v_es[itr_num].real()
						+ Y[i][j + num_VT][1] * bus[i].v_es[itr_num].imag();

					//Nij
					J(row, col + 1) = +Y[i][j + num_VT][1] * bus[i].v_es[itr_num].real()
						+ Y[i][j + num_VT][0] * bus[i].v_es[itr_num].imag();

					//Rij = 0
					J(row + 1, col) = 0;

					//Sij = 0
					J(row + 1, col + 1) = 0;
				}

				bus[i].P_es[itr_num] = bus[i].v_es[itr_num].real() * aii +				//Pi
					bus[i].v_es[itr_num].imag() * bii;
				bus[i].v_mag_es[itr_num] = sqrt(pow(bus[i].v_es[itr_num].real(), 2) +		//Vi^2
					pow(bus[i].v_es[itr_num].imag(), 2));

				for (int j = 0; j < total_buses - num_VT; j++)
				{
					int col = 2 * j;
					if (i == j + num_VT)
					{
						//modify Hii
						J(row, col) += bii;

						//modify Sii
						J(row + 1, col + 1) = 2 * bus[i].v_es[itr_num].real();

						//modify Nii
						J(row, col + 1) += aii;

						//modify Rii
						J(row + 1, col) = 2 * bus[i].v_es[itr_num].imag();
					}
				}

				delta_f[row] = bus[i].P - bus[i].P_es[itr_num];
				delta_f[row + 1] = pow(bus[i].v_mag, 2) - pow(bus[i].v_mag_es[itr_num], 2);	//set delta_f
			}
		}

		VectorXd delta_x(equ_num);
		delta_x = J.inverse() * delta_f;

		if (J.determinant() == 0)
		{
			//cout << "Data error, J is not invertable!" << endl;
			return;
		}

		//cout << "J: " << endl << J << endl;
		//cout << "Delta_f: " << endl << delta_f << endl;
		//cout << "Delta_X: " << endl << delta_x << endl;

		itr_num++;
		int is_end_flag = 1;
		for (int i = 1; i < total_buses; i++)
		{
			if (fabs(delta_x(i)) >= pow(10, -5))
			{
				is_end_flag = 0;
			}
			int row = 2 * (i - num_VT);
			if (row < 0) continue;
			bus[i].v_es[itr_num].set(										//update estimated v
				bus[i].v_es[itr_num - 1].real() + delta_x(row + 1),
				bus[i].v_es[itr_num - 1].imag() + delta_x(row)
			);
		};
		if (is_end_flag)
		{
			//cout << "\nCalculation end!!" << endl << "Number of iterations: " << itr_num << endl;
			//cout << "J: " << endl << J << endl;
			//cout << "Delta_X: " << endl << delta_x << endl;
			for (int j = 0; j < total_buses; j++)
			{
				bus[j].v = bus[j].v_es[itr_num];
			}
			break;
		}

	}

	// devide K
	CTool* pIter = *(m_ToolList.begin());
	double baseVol = pIter->m_RatVol;
	double k;
	int i = 0;
	for (auto iter = m_ToolList.begin(); iter != m_ToolList.end(); ++iter) {
		pIter = *iter;
		if (pIter->GetToolType() != LINE) {
			k = baseVol/pIter->m_RatVol;
			bus[i].v.dat[0] /= k;
			bus[i].v.dat[1] /= k;
			++i;
			if (i >= m_BusCount)
				return;
		}
	}
}

void CPFCalDoc::Calculate_Power(Bus bus[], double Y[MAX_BUSES][MAX_BUSES][2])
{
	//power on VT and PV bus
	int total_buses = m_BusCount;
	int num_VT = m_VtCount;
	for (int i = 0; i < total_buses; i++)
	{
		if (bus[i].type != Bus_PQ)
		{
			Complex sum;
			for (int j = 0; j < total_buses; j++)
			{
				Complex Yij(Y[i][j][0], Y[i][j][1]);
				Complex Uj(bus[j].v.real(), bus[j].v.imag());
				sum = Yij.conjugate() * Uj.conjugate();
			}
			bus[i].P = (bus[i].v * sum).real();
			bus[i].Q = (bus[i].v * sum).imag();
		}
	}
}

void CPFCalDoc::OnRun()
{
	// TODO: 在此添加命令处理程序代码
	if (!DeleteNone(m_BusCount, m_LineCount)) { /*Delete failed*/ }
	if (m_VtCount = SortBus()) {/*No Vt buses*/};
	if (m_VtCount > 0 && m_LineCount > 0) {
		if (!CalcY()) {}

		Calculate_Voltage(bus, Y.Y);
		Calculate_Power(bus, Y.Y);
	}
	else {
		/*No Vtheta buses*/
	}
	COutput aOut;
	UpdateAllViews(nullptr);
	aOut.bus = bus;
	aOut.m_ToolList = &m_ToolList;
	if (aOut.DoModal() == IDOK) {
		m_Draw = true;
	}
	
}

void CPFCalDoc::OnFileSave()
{
	CFileDialog dlg(FALSE, L"PFcal File(*.pfc)|*.pfc", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"PFcal File(*.pfc)|*.pfc||");

	int nRetn = dlg.DoModal();
	if (nRetn == IDOK)
	{
		CString filename;
		filename = dlg.GetPathName();
		LPCTSTR address = filename.GetString();
		this->OnSaveDocument(address);
	}
}


void CPFCalDoc::OnButton2()
{
	// TODO: 在此添加命令处理程序代码
	CAbout aDlg;
	//aDlg.m_GridSize = m_GridSize;
	if (aDlg.DoModal() == IDOK) {
	//	m_GridSize = ((aDlg.m_GridSize)/5)*5;
	}
}


void CPFCalDoc::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAbout aDlg;
	aDlg.DoModal();
}
