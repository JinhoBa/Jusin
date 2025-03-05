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

		cout << "1. 초급 2. 중급 3. 고급 4. 돌아가기 : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			dynamic_cast<CMonster*>(m_pMonster)->Set_Info("초급", 30, 3);
			break;
		case 2:
			dynamic_cast<CMonster*>(m_pMonster)->Set_Info("중급", 60, 6);
			break;
		case 3:
			dynamic_cast<CMonster*>(m_pMonster)->Set_Info("고급", 90, 9);
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

		cout << "1. 전투 2. 도망: ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			dynamic_cast<CPlayer*>(m_pPlayer)->Get_Damage(m_pMonster->Get_Info().iAttack);
			dynamic_cast<CMonster*>(m_pMonster)->Get_Damage(m_pPlayer->Get_Info().iAttack);
			if (0 >= m_pPlayer->Get_Info().iHp)
			{
				cout << "패배" << endl;
				dynamic_cast<CPlayer*>(m_pPlayer)->Set_Hp();
				SYSTEM_PAUSE;
				return;
			}
			if (0 >= m_pMonster->Get_Info().iHp)
			{
				cout << "승리" << endl;
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
