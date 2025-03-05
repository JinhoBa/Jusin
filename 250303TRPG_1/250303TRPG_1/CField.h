#pragma once
#include "CPlayer.h"
#include "CMonster.h"

class CField
{
public:
	CField();
	~CField();
public:
	void Initialize(CObj& _rPlayer);
	void Update();
	void Release();
	void Fight();
private:
	CObj* m_pPlayer;
	CObj* m_pMonster;
};

