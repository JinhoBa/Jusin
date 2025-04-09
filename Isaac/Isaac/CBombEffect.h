#pragma once
#include "CObj.h"

class CBombEffect : public CObj
{
public:
	CBombEffect();
	~CBombEffect();

public:
	void Initialize() override;

	void Late_Initialize() override;

	int Update() override;

	int Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

	void Collision(CObj* _pObj, HITPOINT _tHitPoint) override;

};

