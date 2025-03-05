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
		cout << "���� ������" << endl;
		dynamic_cast<CPlayer*>(m_pPlayer)->Render_Inventory();
		cout << "�������� ������" << endl;
		cout <<"�� " << dynamic_cast<CPlayer*>(m_pPlayer)->Get_Equipment() << endl;
		
		cout << "1. ������ ���� 2. ������ �Ǹ� 3. ���ư��� ";
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
			cout << "�Ǹ��� �����۸��� �Է��ϼ��� \n>> ";
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
