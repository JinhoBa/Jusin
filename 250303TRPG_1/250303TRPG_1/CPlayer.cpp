#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Render()
{
	cout << "------------------------------------------------" << endl;
	cout << "이름 : " << m_Info.sName << endl;
	cout << "체력 : " << m_Info.iHp << "\t공격력 : " << m_Info.iAttack << endl;
	cout << "------------------------------------------------" << endl;
}

void CPlayer::Select_Job()
{
	bool bSelect(false);
	int iInput(0);

	while (!bSelect)
	{
		SYSTEM_CLOSE;
		cout << "직업을 선택하세요" << endl;
		cout << "1. 전사 2. 마법사 3. 도적 : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			Set_Info("전사", 180, 10);
			break;
		case 2:
			Set_Info("마법사", 130, 13);
			break;
		case 3:
			Set_Info("도적", 100, 20);
			break;
		default:
			ENTER_AGAIN;
			continue;
		}
		bSelect = true;
	}
}

void CPlayer::Set_Hp()
{
	m_Info.iHp = m_Info.iMaxHp;
}
