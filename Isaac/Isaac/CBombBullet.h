#pragma once
#include "CBullet.h"

class CBombBullet : public CBullet
{
public:
	CBombBullet();
	~CBombBullet();

public:
	void	Initialize() override;
	void	Late_Initialize() override;
	int		Update() override;
	int		Late_Update() override;
	void	Render(HDC hDC) override;
	void	Release() override;
	void	Collision(CObj* _pObj, HITPOINT _tHitPoint) override;

private:
	DWORD64 m_dwTime;
	bool	m_bCollision;
};

