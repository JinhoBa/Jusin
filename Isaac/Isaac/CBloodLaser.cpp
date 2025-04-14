#include "pch.h"
#include "CBloodLaser.h"
#include "CBmpMgr.h"
#include "CTile.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CBloodLaserEffect.h"

CBloodLaser::CBloodLaser() : m_iImageCX(0), m_iImageCY(0), m_eDir(DIR_END), m_fdelta(0.f), m_fSize(0.f), m_fMaxSize(0.f), m_bMaxSize(false), m_dwTime(NULL)
{
	ZeroMemory(&m_tRenderInfo, sizeof(INFO));
}

CBloodLaser::~CBloodLaser()
{
	Release();
}

void CBloodLaser::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bullet/BloodLaser_RIGHT.bmp", L"BloodLaser_RIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bullet/BloodLaser_UP.bmp", L"BloodLaser_UP");

	m_eBulletID = BULLET_LASER;

	Set_CollisionBoxPos(m_tInfo.fX - 10.f, m_tInfo.fY);
	Set_CollisionBoxSize(40.f, 40.f);

	Set_Frame(0, 0, 0);
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwTime = GetTickCount64();

	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
}

void CBloodLaser::Late_Initialize()
{
	m_tRenderInfo.fX = m_pTarget->Get_Info()->fX;
	m_tRenderInfo.fY = m_pTarget->Get_Info()->fY;
	m_tRenderInfo.fCX = m_pTarget->Get_Info()->fCX;
	m_tRenderInfo.fCY= m_pTarget->Get_Info()->fCY;

	m_fSize = 0.f;
	m_fdelta = 3.f;
	switch ((int)m_fAngle)
	{
	case 0:
		m_eDir = DIR_RIGHT;
		m_fMaxSize = m_tInfo.fCY;
		m_pFrameKey = L"BloodLaser_RIGHT";
		break;
	case 180:
		m_eDir = DIR_LEFT;
		m_fMaxSize = m_tInfo.fCY;
		m_pFrameKey = L"BloodLaser_RIGHT";
		break;

	case 90:
		m_eDir = DIR_UP;
		m_fMaxSize = m_tInfo.fCX;
		m_pFrameKey = L"BloodLaser_UP";
		break;

	case 270:
		m_eDir = DIR_DOWN;
		m_fMaxSize = m_tInfo.fCX;
		m_pFrameKey = L"BloodLaser_UP";
		break;
	default:
		break;
	}
	/*CObjMgr::Get_Instance()->Add_CObj(
		OBJ_EFFECT,
		Create_Effect<CBloodLaserEffect>(L"BloodLaser_Effect",
			WINCX - 25.f, m_tInfo.fY+10.f,
			100.f, 100.f,
			4
		));*/
}

int CBloodLaser::Update()
{
	if (m_bDead)
		return DEAD;

	__super::Update_Rect();
	return NOEVENT;
}

int CBloodLaser::Late_Update()
{
	
	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tRenderInfo.fX = TILECX;
		m_tRenderInfo.fY = m_pTarget->Get_Info()->fY - m_fSize / 2;
		m_tRenderInfo.fCX = m_pTarget->Get_Info()->fX - TILECX;
		m_tRenderInfo.fCY = m_fSize;
		m_iImageCX = (int)m_tRenderInfo.fCX;
		m_iImageCY = (int)m_tInfo.fCY;
		break;
	case DIR_RIGHT:
		m_tRenderInfo.fX = m_pTarget->Get_Info()->fX;
		m_tRenderInfo.fY = m_pTarget->Get_Info()->fY - m_fSize / 2;
		m_tRenderInfo.fCX = m_tInfo.fCX - m_tRenderInfo.fX - TILECX;
		m_tRenderInfo.fCY = m_fSize;
		m_iImageCX = (int)m_tRenderInfo.fCX;
		m_iImageCY = (int)m_tInfo.fCY;
		break;
	case DIR_UP:
		m_tRenderInfo.fX = m_pTarget->Get_Info()->fX - m_fSize / 2;
		m_tRenderInfo.fY = 100.f + TILECY;
		m_tRenderInfo.fCX = m_fSize;
		m_tRenderInfo.fCY = m_pTarget->Get_Info()->fY - m_tRenderInfo.fY;
		m_iImageCX = (int)m_tInfo.fCX;
		m_iImageCY = (int)m_tRenderInfo.fCY;
		break;
	case DIR_DOWN:
		m_tRenderInfo.fX = m_pTarget->Get_Info()->fX - m_fSize / 2;
		m_tRenderInfo.fY = m_pTarget->Get_Info()->fY;
		m_tRenderInfo.fCX = m_fSize;
		m_tRenderInfo.fCY = WINCY - TILECY - m_tRenderInfo.fY;
		m_iImageCX = (int)m_tInfo.fCX;
		m_iImageCY = (int)m_tRenderInfo.fCY;
		break;
	case DIR_END:
		break;
	default:
		break;
	}

	if (m_fSize > m_fMaxSize)
	{
		m_bMaxSize = true;
		m_dwTime = GetTickCount64();
		m_fdelta *= -1.f;
		m_fSize += m_fdelta;
	}

	if (m_dwTime + 300 < GetTickCount64())
		m_bMaxSize = false;

	if(!m_bMaxSize)
		m_fSize += m_fdelta;
	
	if (m_fSize <= 0)
		m_bDead;

	return NOEVENT;
}

void CBloodLaser::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRenderInfo.fX,  //+ m_tInfo.fCX * 0.5f,		// 복사 받을 위치 좌표 left
		m_tRenderInfo.fY,					// 복사 받을 위치 좌표 top
		m_tRenderInfo.fCX,				// 복사 받을 가로 사이즈
		m_tRenderInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		0,
		0,								// 복사할 이미지의 left, top
		m_iImageCX,			// 복사할 이미지의 가로
		m_iImageCY,			// 복사할 이미지의 세로
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
