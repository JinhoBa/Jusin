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

	while (true)
	{
		SYSTEM_CLOSE;
		cout << "���� ������" << endl;
		dynamic_cast<CPlayer*>(m_pPlayer)->Render_Inventory();
		cout << "�Ǹ��� �������� �����ϼ��� 6. ���ư��� ";
		cout << "\n>> ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			// ������ �Ǹ�
			break;
		case 2:

			break;
		case 3:

			break;
		case 6:
			return;
		default:
			ENTER_AGAIN;
			continue;
		}

	}
}

void CInventory::Release()
{
}
