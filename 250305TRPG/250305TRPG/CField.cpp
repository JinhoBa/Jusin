#include "pch.h"
#include "CField.h"

CField::CField()
{
	m_pMonster = nullptr;
}

CField::~CField()
{
}

void CField::Initialize(CObj* _pPlayer)
{
	m_pPlayer = _pPlayer;
	if (nullptr == m_pMonster)
		m_pMonster = new CMonster;
}

void CField::Update()
{
	int iInput(0);

	while (true)
	{
		SYSTEM_CLOSE;
		dynamic_cast<CPlayer*>(m_pPlayer)->Render();
		cout << "1. 초급 2. 중급 3. 고급 4. 돌아가기\n>> ";
		cin >> iInput;

		switch (iInput)
		{
		case EASY:
			m_pMonster->Set_Info("초급", 30 * iInput, 3 * iInput, 5 * iInput, 2 * iInput);
			break;
		case MIDDLE:
			m_pMonster->Set_Info("중급", 30 * iInput, 3 * iInput, 5 * iInput, 2 * iInput);
			break;
		case HARD:
			m_pMonster->Set_Info("상급", 30 * iInput, 3 * iInput, 5 * iInput, 2 * iInput);
			break;
		case BACK:
			Release();
			return;
		default:
			ENTER_AGAIN;
			continue;
		}
		Fight();
	}
}

void CField::Release()
{
	Safe_Delete(m_pMonster);
}

void CField::Fight()
{
	int iInput(0);

	while (true)
	{
		SYSTEM_CLOSE;
		dynamic_cast<CPlayer*>(m_pPlayer)->Render();
		dynamic_cast<CMonster*>(m_pMonster)->Render();
		cout << "1. 전투 2. 도망\n>> ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			if (!(m_pPlayer->Get_Damage(*m_pMonster)))
			{
				cout << "패배.." << endl;
				dynamic_cast<CPlayer*>(m_pPlayer)->Set_Hp();
				SYSTEM_PAUSE;
				return;
			}
			if (!(m_pMonster->Get_Damage(*m_pPlayer)))
			{
				cout << "승리" << endl;
				dynamic_cast<CPlayer*>(m_pPlayer)->Get_Reward(*m_pMonster);
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
