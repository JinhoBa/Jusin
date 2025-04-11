#pragma once
#include "CUI.h"
#include "CObj.h"

class CBossHp : public CUI
{
public:
	CBossHp();
	~CBossHp();

public:
	void Set_Boss(CObj* _pBoss) { m_pBoss = _pBoss; }

public:
	void Initialize() override;
	void Late_Initialize() override;
	int Update() override;
	int Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	bool m_bDead;
	CObj* m_pBoss;
	float m_fMaxBossHp;
	float m_fBossHp;
};

