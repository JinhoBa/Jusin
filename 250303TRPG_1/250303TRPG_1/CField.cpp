#include "pch.h"
#include "CField.h"

CField::CField()
{
	m_pPlayer = nullptr;
	m_pMonster = nullptr;
}

CField::~CField()
{
}

void CField::Initialize(CObj& _rPlayer)
{
	m_pPlayer = &_rPlayer;
	if (nullptr == m_pMonster)
	{
		m_pMonster = new CMonster;
		m_pMonster->Initialize();
	}
}

void CField::Update()
{
	int iInput(0);

	while (true)
	{
		SYSTEM_CLOSE;
		dynamic_cast<CPlayer*>(m_pPlayer)->Render();

		cout << "1. �ʱ� 2. �߱� 3. ��� 4. ���ư��� : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			dynamic_cast<CMonster*>(m_pMonster)->Set_Info("�ʱ�", 30, 3);
			break;
		case 2:
			dynamic_cast<CMonster*>(m_pMonster)->Set_Info("�߱�", 60, 6);
			break;
		case 3:
			dynamic_cast<CMonster*>(m_pMonster)->Set_Info("���", 90, 9);
			break;
		case 4:
			return;
		default:
			ENTER_AGAIN;
			break;
		}
		Fight();
	}
}

void CField::Release()
{
}

void CField::Fight()
{
	int iInput(0);

	while (true)
	{
		SYSTEM_CLOSE;
		dynamic_cast<CPlayer*>(m_pPlayer)->Render();
		dynamic_cast<CMonster*>(m_pMonster)->Render();

		cout << "1. ���� 2. ����: ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			dynamic_cast<CPlayer*>(m_pPlayer)->Get_Damage(m_pMonster->Get_Info().iAttack);
			dynamic_cast<CMonster*>(m_pMonster)->Get_Damage(m_pPlayer->Get_Info().iAttack);
			if (0 >= m_pPlayer->Get_Info().iHp)
			{
				cout << "�й�" << endl;
				dynamic_cast<CPlayer*>(m_pPlayer)->Set_Hp();
				SYSTEM_PAUSE;
				return;
			}
			if (0 >= m_pMonster->Get_Info().iHp)
			{
				cout << "�¸�" << endl;
				SYSTEM_PAUSE;
				return;
			}
			break;
		case 2:
			return;
		default:
			ENTER_AGAIN;
			break;
		}
	}
}
