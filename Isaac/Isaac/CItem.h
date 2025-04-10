#pragma once
#include "Define.h"
#include "CObj.h"

class CItem : public CObj
{
public:
	enum ITEMID{ITEM_COIN, ITEM_BOMB, ITEM_KEY, ITEM_BOX, ITEM_HEART, ITEM_SOULHEART, ITEM_END};
public:
	CItem();
	virtual ~CItem();

public:
	ITEMID Get_ItemID() { return m_eItemID; }

public:
	void Initialize() PURE;
	void Late_Initialize() PURE;
	int Update() PURE;
	int Late_Update() PURE;
	void Render(HDC hDC) PURE;
	void Release() PURE;
	void Collision(CObj* _pObj, HITPOINT _tHitPoint) PURE;
protected:
	ITEMID m_eItemID;
};

