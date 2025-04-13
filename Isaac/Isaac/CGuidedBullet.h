#pragma once
#include "CBullet.h"

class CGuidedBullet : public CBullet
{
public:
	CGuidedBullet();
	~CGuidedBullet();

public:


	// CBullet을(를) 통해 상속됨
	void Initialize() override;

	void Late_Initialize() override;

	int Update() override;

	int Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

	void Collision(CObj* _pObj, HITPOINT _tHitPoint) override;

private:
	float m_fDistance;
};

