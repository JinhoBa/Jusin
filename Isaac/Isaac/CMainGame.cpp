#include "pch.h"
#include "CMainGame.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CTileMgr.h"
#include "CCollisionMgr.h"
#include "CUIMgr.h"


CMainGame::CMainGame() : m_hDC(NULL), m_hMemoryDC(NULL), hBitmap(nullptr), hOldBitmap(nullptr), m_iFPS(0), m_dwTime(NULL), m_szFPS(L"")
{
	ZeroMemory(&m_Cursor, sizeof(POINT));
	ZeroMemory(&m_rc, sizeof(RECT));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Late_Initialize()
{
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Back.bmp", L"Back");
	CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_MENU);
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();

}

void CMainGame::Late_Update()
{
	
	CSceneMgr::Get_Instance()->Late_Update();
	CKeyMgr::Get_Instance()->Update();
}

void CMainGame::Render()
{
	m_iFPS++;

	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount64();
	}

	HDC hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");


	CSceneMgr::Get_Instance()->Render(hBackDC);


	BitBlt(m_hDC, 0, 0,
		WINCX, WINCY,
		hBackDC,
		0, 0, SRCCOPY);
}

void CMainGame::Release()
{

	CSceneMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CTileMgr::Destory_Instance();
	CCollisionMgr::Destroy_Instance();
	CUIMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hMemoryDC);
	ReleaseDC(g_hWnd, m_hDC);
}
