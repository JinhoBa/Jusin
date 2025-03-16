#pragma once
#include "CObj.h"
#include "Define.h"

class CBullet : public CObj
{
public:
	CBullet();
	~CBullet();
public:
	void Initialize(RECT* _pRcPlayer);
	void Render();
	void Release();
	void Add_Bullet();
private:
	list<RECT*> listBullet;
	RECT* m_pBullet;
	RECT* m_preBullet;
	RECT* m_pRc;
	list<RECT*>::iterator iter;
};

