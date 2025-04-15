#pragma once
#include "CMonster.h"

class CHost : public CMonster
{
public:
	CHost();
	~CHost();

public:
	void Initialize() override;
	void Late_Initialize() override;
	int Update() override;
	int Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Collision(CObj* _pObj, HITPOINT _tHitPoint) override;

private:
	void Attack();

private:
	int m_iPreFrame;

};

