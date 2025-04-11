#pragma once
#include "CMonster.h"

class CBoss : public CMonster
{
	enum BOSSSTATE{IDLE, ATTACK, JUMP_ATTACK, SPOWN, BS_END};
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
	void Attack(int _iCount);
private:
	bool m_bLeft;
	bool m_bHit;

	float m_fTime;
	float m_fAfterY;

	ULONGLONG m_MotionTime;
	ULONGLONG m_HitTime;

	BOSSSTATE m_ePreState;
	BOSSSTATE m_eCurState;
};

