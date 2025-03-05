#include "pch.h"
#include "CInventory.h"

CInventory::CInventory()
{
}

CInventory::~CInventory()
{
}

void CInventory::Initialize(CObj* _pPlayer)
{
	m_pPlayer = _pPlayer;
}

void CInventory::Update()
{
	int iInput(0);
	string sItemName;

	while (true)
	{
		SYSTEM_CLOSE;
		cout << "보유 아이템" << endl;
		dynamic_cast<CPlayer*>(m_pPlayer)->Render_Inventory();
		cout << "장착중인 아이템" << endl;
		cout <<"▣ " << dynamic_cast<CPlayer*>(m_pPlayer)->Get_Equipment() << endl;
		
		cout << "1. 아이템 장착 2. 아이템 판매 3. 돌아가기 ";
		cout << "\n>> ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			cout << "장착할 아이템명을 입력하세요 \n>> ";
			cin.ignore();
			getline(cin, sItemName);
			dynamic_cast<CPlayer*>(m_pPlayer)->Equip_Item(sItemName);
			break;
		case 2:
			cout << "판매할 아이템명을 입력하세요 \n>> ";
			cin.ignore();
			getline(cin, sItemName);
			dynamic_cast<CPlayer*>(m_pPlayer)->Sell_Item(sItemName);
			break;
		case 3:
			return;
		default:
			ENTER_AGAIN;
			break;
		}

	}
}

void CInventory::Release()
{
}
