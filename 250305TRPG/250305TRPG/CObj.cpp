#include "pch.h"
#include "CObj.h"

CObj::CObj()
{
	m_tInfo.sName = "";
	m_tInfo.iHp = 0;
	m_tInfo.iAttack = 0;
	m_tInfo.iMaxHp = 0;
	m_tInfo.iMoney = 0;
	m_tInfo.iExp = 0;
}

CObj::~CObj()
{
	Release();
}

void CObj::Initialize()
{
}

void CObj::Update()
{
}

void CObj::Release()
{
}

void CObj::Render()
{
	
}

void CObj::Set_Info(string _sName, int _iHp, int iAttack, int iMoney, int iExp)
{
	m_tInfo.sName = _sName;
	m_tInfo.iHp = m_tInfo.iMaxHp = _iHp;
	m_tInfo.iAttack = iAttack;
	m_tInfo.iMoney = iMoney;
	m_tInfo.iExp = iExp;
}

bool CObj::Get_Damage(CObj& rObj)
{
	m_tInfo.iHp -= rObj.m_tInfo.iAttack;
	if(0 >= m_tInfo.iHp)
		return false;
	return true;
}
