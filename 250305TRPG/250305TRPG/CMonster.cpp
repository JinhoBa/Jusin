#include "pch.h"
#include "CMonster.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::Render()
{
	cout << "------------------------------------" << endl;
	cout << "이름 : " << m_tInfo.sName << endl;
	cout << "체력 : " << m_tInfo.iHp << "\t공격력 : " << m_tInfo.iAttack << endl;
	cout << "------------------------------------" << endl;
}
