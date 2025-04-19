#include "pch.h"
#include "CBloodLaser.h"
#include "CBmpMgr.h"
#include "CTile.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CBloodLaserEffect.h"
#include "CSoundMgr.h"

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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bullet/33.bmp", L"33");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bullet/44.bmp", L"44");

	m_eBulletID = BULLET_LASER;

	
	Set_CollisionBoxSize(40.f, 40.f);

	Set_Frame(0, 3, 0);
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwTime = GetTickCount64();

	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	
	m_iSoundChennel = CSoundMgr::Get_Instance()->Get_AvailableChennel();
	CSoundMgr::Get_Instance()->PlaySound(L"Blood_Laser1.mp3", m_iSoundChennel, 1.f);
}

void CBloodLaser::Late_Initialize()
{
	
	m_tRenderInfo.fX = m_pTarget->Get_Info()->fX;
	m_tRenderInfo.fY = m_pTarget->Get_Info()->fY;
	m_tRenderInfo.fCX = m_pTarget->Get_Info()->fCX;
	m_tRenderInfo.fCY= m_pTarget->Get_Info()->fCY;

	m_fSize = 100.f;
	m_fdelta = 1.f;
	CObj* pEffect(nullptr);
	switch ((int)m_fAngle)
	{
	case 0:
		m_eDir = DIR_RIGHT;
		m_fMaxSize = m_tInfo.fCY;
		m_pFrameKey = L"44";
		pEffect = Create_Effect<CBloodLaserEffect>(L"BloodLaser_Effect", float(WINCX - TILECX), m_tRenderInfo.fY, 64.f, 64.f, 3);
		pEffect->Set_Frame(0, 3, 3);
		break;
	case 180:
		m_eDir = DIR_LEFT;
		m_fMaxSize = m_tInfo.fCY;
		m_pFrameKey = L"44";
		pEffect = Create_Effect<CBloodLaserEffect>(L"BloodLaser_Effect", float(TILECX), m_tRenderInfo.fY, 64.f, 64.f, 3);
		pEffect->Set_Frame(0, 3, 2);
		
		break;

	case 90:
		m_eDir = DIR_UP;
		m_fMaxSize = 40.f;
		m_pFrameKey = L"33";
		pEffect = Create_Effect<CBloodLaserEffect>(L"BloodLaser_Effect", m_tRenderInfo.fX, 100.f +(float)TILECY, 64.f, 64.f, 3);
		pEffect->Set_Frame(0, 3, 0);
		break;

	case 270:
		m_eDir = DIR_DOWN;
		m_fMaxSize = 40.f;
		m_pFrameKey = L"33";
		pEffect = Create_Effect<CBloodLaserEffect>(L"BloodLaser_Effect", m_tRenderInfo.fX, float(WINCY - TILECY), 64.f, 64.f, 3);
		pEffect->Set_Frame(0, 3, 1);

		break;
	default:
		break;
	}
	if (pEffect)
	{
		CObjMgr::Get_Instance()->Add_CObj(OBJ_EFFECT, pEffect);
	}
	
	
}

int CBloodLaser::Update()
{
	if (m_bDead)
		return DEAD;

	__super::Update_Rect();
	__super::Move_Frame();
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
		m_iImageCX = (int)m_tInfo.fCX;
		m_iImageCY = (int)m_tInfo.fCY;
		break;
	case DIR_RIGHT:
		m_tRenderInfo.fX = m_pTarget->Get_Info()->fX;
		m_tRenderInfo.fY = m_pTarget->Get_Info()->fY - m_fSize / 2;
		m_tRenderInfo.fCX = WINCX - m_tRenderInfo.fX - TILECX;
		m_tRenderInfo.fCY = m_fSize;
		m_iImageCX = (int)m_tInfo.fCX;
		m_iImageCY = (int)m_tInfo.fCY;
		break;
	case DIR_UP:
		m_tRenderInfo.fX = m_pTarget->Get_Info()->fX - m_fSize / 2;
		m_tRenderInfo.fY = 100.f + TILECY;
		m_tRenderInfo.fCX = m_fSize;
		m_tRenderInfo.fCY = m_pTarget->Get_Info()->fY - m_tRenderInfo.fY;
		m_iImageCX = (int)m_tInfo.fCX;
		m_iImageCY = (int)m_tInfo.fCY;
		break;
	case DIR_DOWN:
		m_tRenderInfo.fX = m_pTarget->Get_Info()->fX - m_fSize / 2;
		m_tRenderInfo.fY = m_pTarget->Get_Info()->fY;
		m_tRenderInfo.fCX = m_fSize;
		m_tRenderInfo.fCY = WINCY - TILECY - m_tRenderInfo.fY;
		m_iImageCX = (int)m_tInfo.fCX;
		m_iImageCY = (int)m_tInfo.fCY;
		break;
	case DIR_END:
		break;
	default:
		break;
	}
	Set_CollisionBoxPos(m_tRenderInfo.fX + m_tRenderInfo.fCX * 0.5f, m_tRenderInfo.fY + m_tRenderInfo.fCY * 0.5f);

	
	m_dwTime = GetTickCount64();
	m_fSize -= m_fdelta;

	
	

	if (m_fSize < 40.f)
	{
		Set_CollisionBoxSize(0.f, 0.f);
	}
	else
	{
		if (!lstrcmp(L"44", m_pFrameKey))
			Set_CollisionBoxSize(m_tRenderInfo.fCX, m_tRenderInfo.fCY * 0.5f);
		else
			Set_CollisionBoxSize(m_tRenderInfo.fCX * 0.5f, m_tRenderInfo.fCY);
	}
	
	
	if (m_fSize <= 0.f)
		m_bDead = true;

	return NOEVENT;
}

void CBloodLaser::Render(HDC hDC)
{
	//__super::Collision_Render(hDC);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		(int)m_tRenderInfo.fX,  //+ m_tInfo.fCX * 0.5f,		// 복사 받을 위치 좌표 left
		(int)m_tRenderInfo.fY,					// 복사 받을 위치 좌표 top
		(int)m_tRenderInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tRenderInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		m_iImageCX * m_tFrame.iStart,
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
	case OBJ_MONSTER:
		if(m_tCollisionBox.fCX > 0 && m_tCollisionBox.fCY > 0)
			_pObj->Set_Hp(m_tStat.fAttack*0.15);
		break;

	case OBJ_TILE:
		if (0 != dynamic_cast<CTile*>(_pObj)->Get_Option() && 4 != dynamic_cast<CTile*>(_pObj)->Get_Option())
		{

		}
		break;

	default:
		break;
	}
}
