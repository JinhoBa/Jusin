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
		cout << "보유 아이템" << endl;
		dynamic_cast<CPlayer*>(m_pPlayer)->Render_Inventory();
		cout << "판매할 아이템을 선택하세요 6. 돌아가기 ";
		cout << "\n>> ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			// 아이템 판매
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
