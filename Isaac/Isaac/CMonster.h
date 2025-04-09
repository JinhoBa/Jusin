#pragma once
#include "CObj.h"

class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	void Initialize() PURE;
	void Late_Initialize() PURE;
	int Update() PURE;
	int Late_Update() PURE;
	void Render(HDC hDC) PURE;
	void Release() PURE;
	void Collision(CObj* _pObj, HITPOINT _tHitPoint) PURE;
};

