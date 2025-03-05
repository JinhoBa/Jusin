#pragma once
#include "CMenu.h"
#include "CItem.h"

class CStore : public CMenu
{
public:
	CStore();
	virtual ~CStore();
public:
	virtual void Initialize(CObj* _pPlayer);
	virtual void Update();
	virtual void Release();
private:
	CItem* m_pItem;
};

