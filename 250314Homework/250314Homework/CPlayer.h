#pragma once
#include "CObj.h"

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
	void Shoot();
protected:
	list<RECT> listBullet;
	ULONG time;
	RECT preBullet;
};

