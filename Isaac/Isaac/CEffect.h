#pragma once
#include "CObj.h"

class CEffect : public CObj
{
public:
	CEffect();
	~CEffect();

public:
	void Initialize() override;
	void Late_Initialize() override;
	int Update() override;
	int Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Collision(CObj* _pObj, HITPOINT _tHitPoint) override;
};

