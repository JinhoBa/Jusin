#include "pch.h"
#include "CMainGame.h"

CMainGame::CMainGame()
{
	m_pPlayer = nullptr;
	m_pMenu = nullptr;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	if (nullptr == m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		dynamic_cast<CPlayer*>(m_pPlayer)->Initialize();
		dynamic_cast<CPlayer*>(m_pPlayer)->Select_Job();
	}
}

void CMainGame::Update()
{
	if (nullptr == m_pPlayer)
		return;

	int iInput(0);

	while (true)
	{
		SYSTEM_CLOSE;
		dynamic_cast<CPlayer*>(m_pPlayer)->Render();
		cout << "1. 사냥터 2. 상점 3. 인벤토리 4. 종료 \n>> ";
		cin >> iInput;

		switch (iInput)
		{
		case FIELD:
			m_pMenu = new CField;
			dynamic_cast<CField*>(m_pMenu)->Initialize(m_pPlayer);
			dynamic_cast<CField*>(m_pMenu)->Update();
			Safe_Delete<CMenu*>(m_pMenu);
			break;

		case STORE:
			m_pMenu = new CStore;
			dynamic_cast<CStore*>(m_pMenu)->Initialize(m_pPlayer);
			dynamic_cast<CStore*>(m_pMenu)->Update();
			Safe_Delete<CMenu*>(m_pMenu);
			break;

		case INVENTORY:
			m_pMenu = new CInventory;
			dynamic_cast<CInventory*>(m_pMenu)->Initialize(m_pPlayer);
			dynamic_cast<CInventory*>(m_pMenu)->Update();
			Safe_Delete<CMenu*>(m_pMenu);
			break;

		case END:
			cout << "게임 종료" << endl;
			SYSTEM_PAUSE;
			return;

		default:
			ENTER_AGAIN;
			continue;
		}
	}
}

void CMainGame::Release()
{
	Safe_Delete<CObj*>(m_pPlayer);
	Safe_Delete<CMenu*>(m_pMenu);
}
