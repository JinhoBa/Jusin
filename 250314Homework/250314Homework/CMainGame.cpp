#include "pch.h"
#include "CMainGame.h"

CMainGame::CMainGame()
{
	m_hDC = NULL;
	m_pPlayer = nullptr;
	m_pBullet = nullptr;
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
	/*if (nullptr == m_pBullet)
	{
		m_pBullet = new CBullet;
		dynamic_cast<CBullet* > (m_pBullet)->Initialize(m_pPlayer);
	}*/
}

void CMainGame::Update()
{
	InvalidateRect(g_hWnd, 0, false);
	UpdateWindow(g_hWnd);
	
	if (GetAsyncKeyState(VK_RIGHT))
	{
		dynamic_cast<CPlayer*>(m_pPlayer)->Move_Right();
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		dynamic_cast<CPlayer*>(m_pPlayer)->Move_Left();
	}
	else if (GetAsyncKeyState(VK_SPACE))
	{
		dynamic_cast<CPlayer*>(m_pPlayer)->Shoot();
	}

	dynamic_cast<CPlayer*>(m_pPlayer)->Update();
	
	/*if (nullptr != m_pBullet)
	{
		dynamic_cast<CBullet*> (m_pBullet)->Render();
	}*/
}

void CMainGame::Render()
{
	dynamic_cast<CPlayer*>(m_pPlayer)->Render();
	MoveToEx(m_hDC, 0, 500, NULL);
	LineTo(m_hDC, 800, 500);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	Safe_Delete(m_pPlayer);
}
