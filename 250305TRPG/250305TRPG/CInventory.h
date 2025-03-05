#pragma once
#include "CMenu.h"
class CInventory : public CMenu
{
public:
	CInventory();
	virtual ~CInventory();
public:
	virtual void Initialize(CObj* _pPlayer);
	virtual void Update();
	virtual void Release();
};

