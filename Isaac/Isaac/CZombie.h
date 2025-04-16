#pragma once
#include "CMonster.h"

class CZombie : public CMonster
{
	enum ZombieState {LEFT, RIGHT, MEAT, RESURRECTION, ST_END};
public:
	CZombie();
	~CZombie();

public:
	void Initialize() override;
	void Late_Initialize() override;
	int Update() override;
	int Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Collision(CObj* _pObj, HITPOINT _tHitPoint) override;

private:
	void Change_Motion();
private:
	ZombieState m_eCurState;
	ZombieState m_ePreState;

	float m_fMeatHp;
};

