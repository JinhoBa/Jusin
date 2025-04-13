#pragma once
#include "CItem.h"

class CPassiveItem : public CItem
{
public:
	CPassiveItem();
	~CPassiveItem();

public:
	void Initialize() override;
	void Late_Initialize() override;
	int Update() override;
	int Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Collision(CObj* _pObj, HITPOINT _tHitPoint) override;
};

