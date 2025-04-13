#pragma once
#include "CObj.h"

class CMonsterDeathEffect : public CObj
{
public:
	CMonsterDeathEffect();
	~CMonsterDeathEffect();

public:


	// CObj을(를) 통해 상속됨
	void Initialize() override;

	void Late_Initialize() override;

	int Update() override;

	int Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

	void Collision(CObj* _pObj, HITPOINT _tHitPoint) override;

private:
	ULONGLONG m_dwTime;

};

