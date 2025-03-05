#include "pch.h"
#include "CMainGame.h"

CMainGame::CMainGame()
{
	m_pPlayer = nullptr;
	m_pField = nullptr;
	m_pStore = nullptr;
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
		dynamic_cast<CPlayer*>(m_pPlayer)->Select_Job();
	}

	if (nullptr == m_pField)
	{
		m_pField = new CField;
	}

	if (nullptr == m_pStore)
	{
		m_pStore = new CStore;
	}
}

void CMainGame::Update()
{
	int iInput(0);

	while (true)
	{
		SYSTEM_CLOSE;
		dynamic_cast<CPlayer*>(m_pPlayer)->Render();
		cout << "1. 사냥터 입장 2. 상점 입장 3. 게임 종료 : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			dynamic_cast<CField*>(m_pField)->Initialize(*m_pPlayer);
			dynamic_cast<CField*>(m_pField)->Update();
			break;
		case 2:
			dynamic_cast<CStore*>(m_pStore)->Initialize(*m_pPlayer);
			dynamic_cast<CStore*>(m_pStore)->Update();
			break;
		case 3:
			cout << "게임 종료" << endl;
			SYSTEM_PAUSE;
			return;
		default:
			ENTER_AGAIN;
			break;
		}
	}
}

void CMainGame::Release()
{
	Safe_Delete(m_pPlayer);
	Safe_Delete(m_pField);
	Safe_Delete(m_pStore);
}
