#pragma once
#include "CObj.h"

class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();
public:
	virtual void Render();
};

