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
	cout << "�̸� : " << m_Info.sName << endl;
	cout << "ü�� : " << m_Info.iHp << "\t���ݷ� : " << m_Info.iAttack << endl;
	cout << "------------------------------------------------" << endl;
}

void CPlayer::Select_Job()
{
	bool bSelect(false);
	int iInput(0);

	while (!bSelect)
	{
		SYSTEM_CLOSE;
		cout << "������ �����ϼ���" << endl;
		cout << "1. ���� 2. ������ 3. ���� : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			Set_Info("����", 180, 10);
			break;
		case 2:
			Set_Info("������", 130, 13);
			break;
		case 3:
			Set_Info("����", 100, 20);
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
