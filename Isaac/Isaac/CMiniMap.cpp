#include "pch.h"
#include "CMiniMap.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CBmpMgr.h"

CMiniMap::CMiniMap()
{
	m_vecSceneState.assign(12, 0);
}

CMiniMap::~CMiniMap()
{
    Release();
}

void CMiniMap::Initialize()
{
    m_tInfo.fCX = 30.f;
    m_tInfo.fCY = 21.f;
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/UI/Map_UI.bmp", L"Map_UI");
}

void CMiniMap::Late_Initialize()
{
}

int CMiniMap::Update()
{
  

    return NOEVENT;
}

int CMiniMap::Late_Update()
{
	m_vecSceneState = CSceneMgr::Get_Instance()->Get_vecSceneState();

    return NOEVENT;
}

void CMiniMap::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Map_UI");
	for(int i = 0; i < 12; ++i)
	{
		if (0 == m_vecSceneState[i])
			continue;

		GdiTransparentBlt(hDC,/// 복사 받을 dc
			40 * (i%3) + 100,		// 복사 받을 위치 좌표 left
			21 * (i / 3),					// 복사 받을 위치 좌표 top
			60,				// 복사 받을 가로 사이즈
			42,				// 복사 받을 세로 사이즈
			hMemDC,							// 복사할 이미지 dc
			(int)m_tInfo.fCX * ((m_vecSceneState[i]-1) % 3),
			(int)m_tInfo.fCY * ((m_vecSceneState[i]-1) / 3),			// 복사할 이미지의 left, top
			(int)m_tInfo.fCX,				// 복사할 이미지의 가로
			(int)m_tInfo.fCY,				// 복사할 이미지의 세로
			RGB(255, 0, 255));
	}
}

void CMiniMap::Release()
{
}
