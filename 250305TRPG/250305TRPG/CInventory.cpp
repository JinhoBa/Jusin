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
		dynamic_cast<CPlayer*>(m_pPlayer)->Render();
		dynamic_cast<CPlayer*>(m_pPlayer)->Render_Inventory();
		cout << "\t\t�������� ������" << endl;
		cout <<"�� " << dynamic_cast<CPlayer*>(m_pPlayer)->Get_Equipment() << endl;
		
		cout << "1. ������ ���� 2. ������ ���� 3. ������ �Ǹ� 4. ���ư��� ";
		cout << "\n>> ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			cout << "������ �����۸��� �Է��ϼ��� \n>> ";
			cin.ignore();
			getline(cin, sItemName);
			dynamic_cast<CPlayer*>(m_pPlayer)->Equip_Item(sItemName);
			break;

		case 2:
			dynamic_cast<CPlayer*>(m_pPlayer)->Unequip_Item();
			break;

		case 3:
			cout << "�Ǹ��� �����۸��� �Է��ϼ��� \n>> ";
			cin.ignore();
			getline(cin, sItemName);
			dynamic_cast<CPlayer*>(m_pPlayer)->Sell_Item(sItemName);
			break;
		case 4:
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
