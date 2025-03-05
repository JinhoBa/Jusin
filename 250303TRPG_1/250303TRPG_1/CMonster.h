#pragma once
#include "CObj.h"

class CMonster : public CObj
{
public:
	CMonster();
	~CMonster();
public:
	virtual void Render();
};

