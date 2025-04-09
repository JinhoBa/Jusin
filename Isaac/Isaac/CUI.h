#pragma once
#include "Define.h"

class CUI
{
public:
	CUI();
	virtual ~CUI();

public:
	virtual void	Initialize()PURE;
	virtual void	Late_Initialize()PURE;
	virtual int		Update()PURE;
	virtual int		Late_Update()PURE;
	virtual void	Render(HDC hDC)PURE;
	virtual void	Release()PURE;

	void Update_Rect()
	{
		m_tRect.left = long(m_tInfo.fX - m_tInfo.fCX / 2.f);
		m_tRect.top = long(m_tInfo.fY - m_tInfo.fCY / 2.f);
		m_tRect.right = long(m_tInfo.fX + m_tInfo.fCX / 2.f);
		m_tRect.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2.f);

	}

protected:
	INFO m_tInfo;
	RECT m_tRect;
	int	m_iDrawID;
};

