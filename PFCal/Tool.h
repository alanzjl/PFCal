#pragma once

// CTool 命令目标

class CTool : public CObject
{
protected:
	CRect m_EnclosingRect;
	ToolType m_ToolType;
	CTool();
public:
	CPoint m_StartPoint;
	CPoint m_EndPoint;
	virtual ~CTool();
	virtual void Draw(CDC* pDC) {}

	bool operator < (const CTool &A) {
		return (this->m_Id < A.m_Id);
	}
	
	CRect GetBoundRect() const;
	ToolType GetToolType() const;
	void ChangeBasePoint(CPoint point);
	int m_Id;
		double m_RatVol;
		bool m_Trans;

		// for line
		int m_IdFrom, m_IdTo;
		double m_X1, m_R1, m_G1, m_B1;	// x,r,g,b per km
		double m_Length;

		// for transformers
		double m_Sn;
		double m_Uh, m_Ul, m_Uk;	// voltage on high and low voltage side
		double m_Pk, m_Po, m_Io;

		double m_VtE, m_VtF;	// For Vtheta BUS
		double m_PqP, m_PqQ;	// For PQ BUS
		double m_PvP, m_PvU;	// For PvBus
};

class CLine :
	public CTool
{
public:
	CLine(const CPoint& start, const CPoint& end);
	virtual void Draw(CDC* pDC);
	~CLine();

protected:
	
};

class CVtheta :
	public CTool
{
public:
	CVtheta(const CPoint& start, const CPoint& end);
	virtual void Draw(CDC* pDC);
	~CVtheta();
protected:
};

class CPq :
	public CTool
{
public:
	CPq(const CPoint& start, const CPoint& end);
	virtual void Draw(CDC* pDC);
	~CPq();
protected:
};

class CPv :
	public CTool
{
public:
	CPv(const CPoint& start, const CPoint& end);
	virtual void Draw(CDC* pDC);
	~CPv();
protected:
};


