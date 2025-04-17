#pragma once
#include "Define.h"
#include "CObj.h"

class CItem : public CObj
{
public:
	enum ITEMID{ITEM_COIN, ITEM_BOMB, ITEM_KEY, ITEM_BOX, ITEM_HEART, ITEM_SOULHEART,ITEM_CYCLOPS, ITEM_SPOON, ITEM_118, ITEM_SLOTMACHINE, ITEM_END};
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
	void Set_Stop() { m_bMove = false; }
	void Spown_Move();
	void Slip();
public:
	void Initialize();
	void Late_Initialize() PURE;
	int Update() PURE;
	int Late_Update() PURE;
	void Render(HDC hDC) PURE;
	void Release() PURE;
	void Collision(CObj* _pObj, HITPOINT _tHitPoint);

protected:
	ITEMID m_eItemID;

	bool m_bMove;

	int		m_iDropTime;
	float m_fTime;
	float m_fItemSpeedX;
	float m_fItemSpeedY;

	ULONGLONG m_CreateTime;
	
};

