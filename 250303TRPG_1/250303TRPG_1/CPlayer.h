#pragma once
#include "CObj.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	~CPlayer();
public:
	virtual void Render();
	void Select_Job();
	void Set_Hp();
};

