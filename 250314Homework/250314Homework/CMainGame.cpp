#include "pch.h"
#include "CMainGame.h"


CMainGame::CMainGame()
{
	dwTime = 0;
	m_hDC = NULL;
	m_pPlayer = nullptr;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	dwTime = GetTickCount64();
	m_hDC = GetDC(g_hWnd);
	if (nullptr == m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		dynamic_cast<CPlayer*>(m_pPlayer)->Initialize();
		m_pPlayer->SetHDC(m_hDC);
	}
	
}

void CMainGame::Update()
{
	
	if (GetAsyncKeyState('D'))
	{
		dynamic_cast<CPlayer*>(m_pPlayer)->Move_Right();
	}
	else if (GetAsyncKeyState('A'))
	{
		dynamic_cast<CPlayer*>(m_pPlayer)->Move_Left();
	}
	else if (GetAsyncKeyState(VK_SPACE))
	{
		dynamic_cast<CPlayer*>(m_pPlayer)->Jump();
	}
	else if (GetAsyncKeyState(VK_LBUTTON) && dwTime + 500 < GetTickCount64())
	{
		dynamic_cast<CPlayer*>(m_pPlayer)->Shoot();
		dwTime = GetTickCount64();
	}

	dynamic_cast<CPlayer*>(m_pPlayer)->Update();
	
}

void CMainGame::Render()
{
	
	MoveToEx(m_hDC, 0, 500, NULL);
	LineTo(m_hDC, 800, 500);
	dynamic_cast<CPlayer*>(m_pPlayer)->Render();
}

void CMainGame::Release()
{
	dynamic_cast<CPlayer*>(m_pPlayer)->Release();
	ReleaseDC(g_hWnd, m_hDC);
	Safe_Delete(m_pPlayer);
}
