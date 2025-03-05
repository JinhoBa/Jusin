#include "pch.h"
#include "CObj.h"

CObj::CObj()
{
	m_Info.sName = "";
	m_Info.iHp = 0;
	m_Info.iMaxHp = 0;
	m_Info.iAttack = 0;
	m_Info.iMoney = 0;
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

void CObj::Set_Info(string _sName, int _iHp, int _iAttack)
{
	m_Info.sName = _sName;
	m_Info.iHp = m_Info.iMaxHp = _iHp;
	m_Info.iAttack = _iAttack;
	m_Info.iMoney = 0;
}

void CObj::Get_Damage(int _iDamage)
{
	m_Info.iHp -= _iDamage;
}
