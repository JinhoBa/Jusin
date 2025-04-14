#include "pch.h"
#include "CBloodLaserEffect.h"
#include "CBmpMgr.h"

CBloodLaserEffect::CBloodLaserEffect() : m_dwTime(GetTickCount64())
{
}

CBloodLaserEffect::~CBloodLaserEffect()
{
    Release();
}

void CBloodLaserEffect::Initialize()
{
	Set_Frame(0, 0, 0);
	m_tFrame.dwFrameSpeed = 2000;

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	Set_CollisionBoxSize(150.f, 150.f);

	m_tStat.fAttack = 5.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Effect/BloodLaser_Effect.bmp", L"BloodLaser_Effect");

}

void CBloodLaserEffect::Late_Initialize()
{
	m_fCY = m_tInfo.fCY;
}

int CBloodLaserEffect::Update()
{
	if (m_bDead)
	{
		return DEAD;
	}

	__super::Update_Rect();

	return NOEVENT;
}

int CBloodLaserEffect::Late_Update()
{
	//__super::Move_Frame();

	if(m_dwTime+400 < GetTickCount64())
		m_bDead = true;
	

	return NOEVENT;
}

void CBloodLaserEffect::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * 2,			// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CBloodLaserEffect::Release()
{
}

void CBloodLaserEffect::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
}
