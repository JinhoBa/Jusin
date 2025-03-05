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
		cout << "1. �ʱ� 2. �߱� 3. ��� 4. ���ư���\n>> ";
		cin >> iInput;

		switch (iInput)
		{
		case EASY:
			m_pMonster->Set_Info("�ʱ�", 30 * iInput, 3 * iInput, 5 * iInput, 2 * iInput);
			break;
		case MIDDLE:
			m_pMonster->Set_Info("�߱�", 30 * iInput, 3 * iInput, 5 * iInput, 2 * iInput);
			break;
		case HARD:
			m_pMonster->Set_Info("���", 30 * iInput, 3 * iInput, 5 * iInput, 2 * iInput);
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
		cout << "1. ���� 2. ����\n>> ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			if (!(m_pPlayer->Get_Damage(*m_pMonster)))
			{
				cout << "�й�.." << endl;
				dynamic_cast<CPlayer*>(m_pPlayer)->Set_Hp();
				SYSTEM_PAUSE;
				return;
			}
			if (!(m_pMonster->Get_Damage(*m_pPlayer)))
			{
				cout << "�¸�" << endl;
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
