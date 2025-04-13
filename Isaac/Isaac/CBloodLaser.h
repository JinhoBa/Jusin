#pragma once
#include "CBullet.h"

class CBloodLaser : public CBullet
{
public:
	CBloodLaser();
	~CBloodLaser();

public:
	void Initialize() override;

	void Late_Initialize() override;

	int Update() override;

	int Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

	void Collision(CObj* _pObj, HITPOINT _tHitPoint) override;

private:
	long m_top;
};

