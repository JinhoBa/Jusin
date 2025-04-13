#include "pch.h"
#include "CBloodLaser.h"
#include "CBmpMgr.h"
#include "CTile.h"

CBloodLaser::CBloodLaser()
{
}

CBloodLaser::~CBloodLaser()
{
	Release();
}

void CBloodLaser::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bullet/Brimstone_RIGHT.bmp", L"Brimstone_RIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bullet/Brimstone_UP.bmp", L"Brimstone_UP");

	m_eBulletID = BULLET_LASER;

	Set_CollisionBoxPos(m_tInfo.fX - 10.f, m_tInfo.fY);
	Set_CollisionBoxSize(40.f, 40.f);

	Set_Frame(3, 3, 0);
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwTime = GetTickCount64();

	m_top = 75;
}

void CBloodLaser::Late_Initialize()
{
}

int CBloodLaser::Update()
{
	if (m_bDead)
		return DEAD;

	__super::Update_Rect();
	//__super::Move_Frame();
	return NOEVENT;
}

int CBloodLaser::Late_Update()
{
	m_top -= 1.2;
	
	if (m_top <= 0)
		m_bDead;
	return NOEVENT;
}

void CBloodLaser::Render(HDC hDC)
{
	

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Brimstone_RIGHT");



	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		400 - m_top / 2,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		m_top,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		0,
		76 * m_tFrame.iStart,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,			// 복사할 이미지의 가로
		(int)m_tInfo.fCY,			// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CBloodLaser::Release()
{
}

void CBloodLaser::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_TILE:
		if (0 != dynamic_cast<CTile*>(_pObj)->Get_Option())
		{
			m_bDead = true;
		}
		break;

	default:
		break;
	}
}
