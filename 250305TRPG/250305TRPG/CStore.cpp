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
		cout << "구매할 물건을 선택하세요" << endl;
		cout << "1. 낡은 단검(10G) 2. 빛나는 지팡이(30G) 3. 용기사의 검(100G) 4. 돌아가기\n>> ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			if (10 <= m_pPlayer->Get_Gold())
			{
				m_pItem->Set_Item("낡은 단검", 0, 5, 10);
				dynamic_cast<CPlayer*>(m_pPlayer)->Buy_Item(*m_pItem);
			}
			else
				cout << "소지금이 부족합니다..." << endl;
			break;
		case 2:
			if (30 <= m_pPlayer->Get_Gold())
			{
				m_pItem->Set_Item("빛나는 지팡이", 0, 15, 30);
				dynamic_cast<CPlayer*>(m_pPlayer)->Buy_Item(*m_pItem);
			}
			else
				cout << "소지금이 부족합니다..." << endl;
			break;
		case 3:
			if (100 <= m_pPlayer->Get_Gold())
			{
				m_pItem->Set_Item("용기사의 검", 100, 20, 100);
				dynamic_cast<CPlayer*>(m_pPlayer)->Buy_Item(*m_pItem);
			}
			else
				cout << "소지금이 부족합니다..." << endl;
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
