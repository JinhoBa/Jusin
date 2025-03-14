#pragma once
#include "CPlayer.h"

class CBullet : public CPlayer
{
public:
	CBullet();
	~CBullet();
public:
	//void Initialize(CObj* _pPlayer);
	void Render();
};

