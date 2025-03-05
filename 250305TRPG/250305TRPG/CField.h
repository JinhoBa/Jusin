#pragma once
#include "CMenu.h"
#include "CMonster.h"

class CField : public CMenu
{
public:
	CField();
	virtual ~CField();
public:
	virtual void Initialize(CObj* _pPlayer);
	virtual void Update();
	virtual void Release();
	void Fight();
private:
	enum FIELDINDEX
	{
		EASY = 1,
		MIDDLE,
		HARD,
		BACK
	};
	CObj* m_pMonster;
};

