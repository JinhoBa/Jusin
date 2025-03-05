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
	cout << "------------------------------------------------" << endl;
	cout << "이름 : " << m_Info.sName << endl;
	cout << "체력 : " << m_Info.iHp << "\t공격력 : " << m_Info.iAttack << endl;
	cout << "------------------------------------------------" << endl;
}
