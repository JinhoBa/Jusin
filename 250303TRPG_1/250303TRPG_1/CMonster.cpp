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
	cout << "�̸� : " << m_Info.sName << endl;
	cout << "ü�� : " << m_Info.iHp << "\t���ݷ� : " << m_Info.iAttack << endl;
	cout << "------------------------------------------------" << endl;
}
