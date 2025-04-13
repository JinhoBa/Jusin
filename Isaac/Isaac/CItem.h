#pragma once
#include "Define.h"
#include "CObj.h"

class CItem : public CObj
{
public:
	enum ITEMID{ITEM_COIN, ITEM_BOMB, ITEM_KEY, ITEM_BOX, ITEM_HEART, ITEM_SOULHEART,ITEM_CYCLOPS, ITEM_SPOON, ITEM_END};
public:
	CItem();
	virtual ~CItem();

public:
	ITEMID Get_ItemID() { return m_eItemID; }
	void Set_Item(const TCHAR* _pFramekey, ITEMID _eItemID)
	{
		__super::Set_FrameKey(_pFramekey);
		m_eItemID = _eItemID;
	}
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
	ULONGLONG m_CreateTime;
	float m_fTime;
};

