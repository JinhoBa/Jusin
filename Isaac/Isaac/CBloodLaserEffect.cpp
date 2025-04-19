#include "pch.h"
#include "CBloodLaserEffect.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"

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
	m_tFrame.dwFrameSpeed = 50;

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	Set_CollisionBoxSize(150.f, 150.f);

	m_tStat.fAttack = 5.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Effect/BloodLaser_Effect.bmp", L"BloodLaser_Effect");
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
}

void CBloodLaserEffect::Late_Initialize()
{
	
}

int CBloodLaserEffect::Update()
{
	if (m_bDead)
	{
		return DEAD;
	}

	__super::Update_Rect();
	__super::Move_Frame();

	return NOEVENT;
}

int CBloodLaserEffect::Late_Update()
{
	if (0 == m_tFrame.iMotion || 1 == m_tFrame.iMotion)
	{
		m_tInfo.fX = m_pTarget->Get_Info()->fX;
	}
	else
	{
		m_tInfo.fY = m_pTarget->Get_Info()->fY;
	}


	if(m_dwTime+900 < GetTickCount64())
		m_bDead = true;
	

	return NOEVENT;
}

void CBloodLaserEffect::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left-5,		// 복사 받을 위치 좌표 left
		m_tRect.top-5,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX + 10,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY + 10,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,			// 복사할 이미지의 left, top
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
