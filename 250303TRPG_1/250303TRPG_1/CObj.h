#pragma once
#include "Define.h"

class  CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	virtual void Render() = 0;
	void Initialize();
	void Update();
	void Release();
	void Set_Info(string _sName, int _iHp, int _iAttack);
	INFO& Get_Info() { return m_Info; }
	void Get_Damage(int _iDamage);
protected:
	INFO m_Info;
};

