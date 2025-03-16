#pragma once
#include "CObj.h"
#include "CBullet.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	void Initialize();
	void Update();
	void Render();
	void Release();
public:
	void Move_Right();
	void Move_Left();
	void Jump();
	void Shoot();
protected:
	ULONG time;
	HBRUSH myBrush;
	CObj* m_pBullet;
};

