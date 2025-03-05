#pragma once
#include "CObj.h"
#include "CPlayer.h"

class CMenu
{
	
public:
	CMenu() { m_pPlayer = nullptr; }
	virtual ~CMenu() { }
public:
	virtual void Initialize(CObj* _pPlayer) = 0;
	virtual void Update() = 0;
	virtual void Release() = 0;
protected:
	CObj* m_pPlayer;
};

