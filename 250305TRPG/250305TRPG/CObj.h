#pragma once
#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	void Initialize();
	void Update();
	void Release();
public:
	virtual void Render() = 0;
	void Set_Info(string _sName, int _iHp, int iAttack, int iMoney, int iExp);
	bool Get_Damage(CObj& rObj);
	const int Get_Gold() { return m_tInfo.iMoney; }
	const int Get_Exp() { return m_tInfo.iExp; }
protected:
	INFO m_tInfo;
};

