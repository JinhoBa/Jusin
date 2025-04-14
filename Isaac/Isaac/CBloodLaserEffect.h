#pragma once
#include "CObj.h"

class CBloodLaserEffect : public CObj
{
public:
	CBloodLaserEffect();
	~CBloodLaserEffect();

public:
	void Initialize() override;
	void Late_Initialize() override;
	int Update() override;
	int Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Collision(CObj* _pObj, HITPOINT _tHitPoint) override;

public:
	ULONGLONG m_dwTime;
	int m_fCY;
};

