#include "pch.h"
#include "CStore.h"

CStore::CStore()
{
	m_pItem = nullptr;
}

CStore::~CStore()
{
}

void CStore::Initialize(CObj* _pPlayer)
{
	m_pPlayer = _pPlayer;
	m_pItem = new CItem;
}

void CStore::Update()
{
	int iInput(0);

	while (true)
	{
		SYSTEM_CLOSE;
		dynamic_cast<CPlayer*>(m_pPlayer)->Render();
		cout << "-------------------STORE-------------------" << endl;
		cout << "������ ������ �����ϼ���" << endl;
		cout << "1. ���� �ܰ�(10G) 2. ������ ������(30G) 3. ������ ��(100G) 4. ���ư���\n>> ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			if (10 <= m_pPlayer->Get_Gold())
			{
				m_pItem->Set_Item("���� �ܰ�", 0, 5, 10);
				dynamic_cast<CPlayer*>(m_pPlayer)->Buy_Item(*m_pItem);
			}
			else
				cout << "�������� �����մϴ�..." << endl;
			break;
		case 2:
			if (30 <= m_pPlayer->Get_Gold())
			{
				m_pItem->Set_Item("������ ������", 0, 15, 30);
				dynamic_cast<CPlayer*>(m_pPlayer)->Buy_Item(*m_pItem);
			}
			else
				cout << "�������� �����մϴ�..." << endl;
			break;
		case 3:
			if (100 <= m_pPlayer->Get_Gold())
			{
				m_pItem->Set_Item("������ ��", 100, 20, 100);
				dynamic_cast<CPlayer*>(m_pPlayer)->Buy_Item(*m_pItem);
			}
			else
				cout << "�������� �����մϴ�..." << endl;
			break;
		case 4:
			return;
		default:
			ENTER_AGAIN;
			continue;
		}
		
	}
}

void CStore::Release()
{
}
