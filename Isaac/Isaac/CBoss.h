#pragma once
#include "CMonster.h"

class CBoss : public CMonster
{
	enum BOSSSTATE{IDLE, ATTACK, HIT, JUMP_ATTACK, SPOWN, BS_END};
public:
	CBoss();
	~CBoss();

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
	bool m_bLeft;
	ULONGLONG m_MotionTime;

	BOSSSTATE m_ePreState;
	BOSSSTATE m_eCurState;
};

