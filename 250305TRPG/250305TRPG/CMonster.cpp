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
	cout << "�̸� : " << m_tInfo.sName << endl;
	cout << "ü�� : " << m_tInfo.iHp << "\t���ݷ� : " << m_tInfo.iAttack << endl;
	cout << "------------------------------------" << endl;
}
