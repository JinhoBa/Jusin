#include "pch.h"
#include "CEffect.h"
#include "CBmpMgr.h"

CEffect::CEffect()
{
}

CEffect::~CEffect()
{
    Release();
}

void CEffect::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Effect/RedBullet_death.bmp", L"RedBullet_death");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Effect/bullet_dead.bmp", L"bullet_death");
	m_tFrame.dwFrameSpeed = 50;
}

void CEffect::Late_Initialize()
{
}

int CEffect::Update()
{
	if (m_bDead)
		return DEAD;

	__super::Update_Rect();

    return NOEVENT;
}

int CEffect::Late_Update()
{
	__super::Move_Frame();

	if (m_tFrame.iStart == m_tFrame.iEnd)
		m_bDead = true;

    return NOEVENT;
}

void CEffect::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,			// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));			// 제거할 이미지 색상 값
}

void CEffect::Release()
{
}

void CEffect::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
}
