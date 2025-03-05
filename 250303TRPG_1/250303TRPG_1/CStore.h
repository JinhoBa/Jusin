#pragma once
#include "CPlayer.h"
class CStore
{
public:
	CStore();
	~CStore();
public:
	void Initialize(CObj& _rPlayer);
	void Update();
	void Release();
private:
	CObj* m_pPlayer;
};

