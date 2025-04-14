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
	bool m_bMaxSize;
	int m_iImageCX;
	int m_iImageCY;
	float m_fSize;
	float m_fMaxSize;
	DIRECTION m_eDir;
	float m_fdelta;
	INFO m_tRenderInfo;

	ULONGLONG m_dwTime;
	
};

