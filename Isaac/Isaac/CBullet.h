#pragma once
#include "CObj.h"
#include "Define.h"

class CBullet : public CObj
{
public:
	enum BULLETID { BULLET_PLAYER, BULLET_BOMB, BULLET_END };
public:
	CBullet();
	virtual ~CBullet();

public:
	BULLETID Get_BulletID() { return m_eBulletID; }

public:
	void Initialize() PURE;
	void Late_Initialize() PURE;
	int	 Update() PURE;
	int	 Late_Update() PURE;
	void Render(HDC hDC) PURE;
	void Release() PURE;
	void Collision(CObj* _pObj, HITPOINT _tHitPoint) PURE;

protected:
	BULLETID m_eBulletID;
};

