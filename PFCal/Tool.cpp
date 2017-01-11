// Tool.cpp : 实现文件
//

#include "stdafx.h"
#include "PFCal.h"


#include "Tool.h"
#include "Common.h"

#include "PFCalConstants.h"

// CTool

CTool::CTool():
	m_Id(-1),
	m_IdFrom(-1), m_IdTo(-1), m_RatVol(220),
	// transmission lines
	m_B1(0), m_G1(0), m_R1(0), m_X1(0), m_Length(0),
	m_Trans(false), 
	// transformers
	m_Sn(0), m_Uk(0), m_Ul(0), m_Uh(0), m_Pk(0), m_Po(0), m_Io(0),
	// VT Bus
	m_VtE(0), m_VtF(0),
	// PV Bus
	m_PvP(0), m_PvU(0),
	// PQ Bus
	m_PqP(0), m_PqQ(0)
{
}

CTool::~CTool()
{
}

void CTool::ChangeBasePoint(CPoint point) {
	int width = m_EnclosingRect.Width();
	int height = m_EnclosingRect.Height();
	m_EnclosingRect = CRect(
		point.x, point.y, point.x + width, point.y + height
	);
}

CRect CTool::GetBoundRect() const {
	CRect boundingRect(m_EnclosingRect);

	boundingRect.InflateRect(m_PenWidth, m_PenWidth);
	return boundingRect;
}

ToolType CTool::GetToolType() const {
	return m_ToolType;
}


// CTool 成员函数


CLine::CLine(const CPoint& start, const CPoint& end)
{
	m_EnclosingRect = CRect(start, end);
	m_EnclosingRect.NormalizeRect();
	m_ToolType = LINE;
	m_StartPoint = start;
	m_EndPoint = end;
}

void CLine::Draw(CDC* pDC) {
	CPen aPen;
	if (!aPen.CreatePen(PS_SOLID, m_PenWidth, m_PenColor)) {
		return;
	}
	CPen* pOldPen = pDC->SelectObject(&aPen);

	pDC->MoveTo(m_StartPoint);
	if (abs(m_EndPoint.y - m_StartPoint.y) > abs(m_EndPoint.x - m_StartPoint.x)) {
		pDC->LineTo(m_StartPoint.x, m_EndPoint.y);
		pDC->MoveTo(m_StartPoint.x, m_EndPoint.y);
		pDC->LineTo(m_EndPoint.x, m_EndPoint.y);
		if (m_Trans) {
			CFont m_Font;
			m_Font.CreatePointFont(120, _T("Arial"), pDC);
			pDC->SelectObject(&m_Font);
			pDC->SetTextColor(m_PvColor);
			pDC->SetBkMode(TRANSPARENT);
			CString m_Text;
			m_Text.Format(_T("From bus %d to bus %d"), m_IdFrom, m_IdTo);
			pDC->TextOutW(m_StartPoint.x
				, (m_StartPoint.y + m_EndPoint.y) / 2
				, m_Text);
		}
	}
	else {
		pDC->LineTo(m_EndPoint.x, m_StartPoint.y);
		pDC->MoveTo(m_EndPoint.x, m_StartPoint.y);
		pDC->LineTo(m_EndPoint.x, m_EndPoint.y);
		if (m_Trans) {
			CFont m_Font;
			m_Font.CreatePointFont(120, _T("Arial"), pDC);
			pDC->SelectObject(&m_Font);
			pDC->SetTextColor(m_PvColor);
			pDC->SetBkMode(TRANSPARENT);
			CString m_Text;
			m_Text.Format(_T("From bus %d to bus %d"), m_IdFrom, m_IdTo);
			pDC->TextOutW((m_StartPoint.x + m_EndPoint.x)/2
				, m_StartPoint.y
				, m_Text);
		}
	}

	pDC->SelectObject(pOldPen);
}


CLine::~CLine()
{
}


CVtheta::CVtheta(const CPoint& start, const CPoint& end)
{
	m_EnclosingRect = CRect(CPoint(end.x-m_RectX*GRID/2, end.y-m_RectY*GRID/2),
		CSize(m_RectX*GRID, m_RectY*GRID));
	m_EnclosingRect.NormalizeRect();
	m_ToolType = VTHETA;
	m_StartPoint = start;
	m_EndPoint = end;
}

void CVtheta::Draw(CDC* pDC) {
	CPen aPen;
	aPen.CreatePen(PS_SOLID, m_PenWidth * 2, m_VthetaColor);
	CBrush aBrush;
	aBrush.CreateHatchBrush(HS_BDIAGONAL, m_VthetaColor);

	CPen* pOldPen = pDC->SelectObject(&aPen);
	CBrush* pOldBrush = pDC->SelectObject(&aBrush);

	pDC->Rectangle(m_EnclosingRect);
	
	CFont m_Font;
	m_Font.CreatePointFont(200, _T("Arial"), pDC);
	pDC->SelectObject(&m_Font);
	pDC->SetTextColor(m_VthetaColor);
	pDC->SetBkMode(TRANSPARENT);
	CString m_Text;
	m_Text.Format(_T("Vθ %d"), this->m_Id);
	BOOL TextOk = pDC->TextOutW(m_StartPoint.x - 2*m_RectX*GRID / 3
		, m_StartPoint.y + m_RectY*GRID / 2, m_Text);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

CVtheta::~CVtheta()
{
}


CPq::CPq(const CPoint& start, const CPoint& end)
{
	m_EnclosingRect = CRect(CPoint(start.x - m_RectX*GRID / 2, start.y - m_RectY*GRID / 2),
		CSize(m_RectX*GRID, m_RectY*GRID));
	m_EnclosingRect.NormalizeRect();
	m_ToolType = PQ;
	m_StartPoint = start;
	m_EndPoint = end;
}

void CPq::Draw(CDC* pDC) {
	CPen aPen;
	aPen.CreatePen(PS_SOLID, m_PenWidth * 2, m_PqColor);
	CBrush aBrush;
	aBrush.CreateHatchBrush(HS_BDIAGONAL, m_PqColor);

	CPen* pOldPen = pDC->SelectObject(&aPen);
	CBrush* pOldBrush = pDC->SelectObject(&aBrush);

	pDC->Rectangle(m_EnclosingRect);

	CFont m_Font;
	m_Font.CreatePointFont(200, _T("Arial"), pDC);
	pDC->SelectObject(&m_Font);
	pDC->SetTextColor(m_PqColor);
	pDC->SetBkMode(TRANSPARENT);
	CString m_Text;
	m_Text.Format(_T("PQ %d"), this->m_Id);
	BOOL TextOk = pDC->TextOutW(m_StartPoint.x - 2*m_RectX*GRID / 3, m_StartPoint.y + m_RectY*GRID / 2, m_Text);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}


CPq::~CPq()
{
}


CPv::CPv(const CPoint& start, const CPoint& end)
{
	m_EnclosingRect = CRect(CPoint(start.x - m_RectX*GRID / 2, start.y - m_RectY*GRID / 2),
		CSize(m_RectX*GRID, m_RectY*GRID));
	m_EnclosingRect.NormalizeRect();
	m_ToolType = PV;
	m_StartPoint = start;
	m_EndPoint = end;
}

void CPv::Draw(CDC* pDC) {
	CPen aPen;
	aPen.CreatePen(PS_SOLID, m_PenWidth * 2, m_PvColor);
	CBrush aBrush;
	aBrush.CreateHatchBrush(HS_BDIAGONAL, m_PvColor);

	CPen* pOldPen = pDC->SelectObject(&aPen);
	CBrush* pOldBrush = pDC->SelectObject(&aBrush);

	pDC->Rectangle(m_EnclosingRect);

	CFont m_Font;
	m_Font.CreatePointFont(200, _T("Arial"), pDC);
	pDC->SelectObject(&m_Font);
	pDC->SetTextColor(m_PvColor);
	pDC->SetBkMode(TRANSPARENT);
	CString m_Text;
	m_Text.Format(_T("PV %d"), this->m_Id);
	BOOL TextOk = pDC->TextOutW(m_StartPoint.x - 2*m_RectX*GRID/3, m_StartPoint.y + m_RectY*GRID / 2, m_Text);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

CPv::~CPv()
{
}
