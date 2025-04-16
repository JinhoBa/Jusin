#include "pch.h"
#include "CHost.h"
#include "CBmpMgr.h"
#include "CMonsterDeathEffect.h"
#include "CSoundMgr.h"
#include "CObjMgr.h"
#include "CBullet.h"
#include "CMonsterBullet.h"

CHost::CHost() : m_iPreFrame(0)
{
}

CHost::~CHost()
{
	Release();
}

void CHost::Initialize()
{
	Set_Stat(10.f, 1.f, 800.f, 1.f);

	Set_Frame(0, 2, 0);
	m_tFrame.dwFrameSpeed = 2000;
	m_tFrame.dwTime = GetTickCount64();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Monster/Host.bmp", L"Host");
	
}

void CHost::Late_Initialize()
{
	Set_CollisionBoxPos(m_tInfo.fX +15, m_tInfo.fY+20);
	Set_CollisionBoxSize(30.f, 30.f);
}

int CHost::Update()
{
	if (m_bDead || m_tStat.fHp < 0.f)
	{
		CSoundMgr::Get_Instance()->Return_Chennel(m_iSoundChennel);
		CObjMgr::Get_Instance()->Add_CObj(OBJ_EFFECT, Create_Effect<CMonsterDeathEffect>(L"Blood", m_tInfo.fX, m_tInfo.fY, 60.f, 30.f, 0));
		return DEAD;
	}

	__super::Update_Rect();

	return NOEVENT;
}

int CHost::Late_Update()
{
	__super::Move_Frame();
	
	if (1 == m_tFrame.iStart && 0 == m_iPreFrame)
		Attack();
	if(1 == m_tFrame.iStart)
		Set_CollisionBoxSize(30.f, 50.f);
	else
		Set_CollisionBoxSize(30.f, 20.f);
	m_iPreFrame = m_tFrame.iStart;

	return NOEVENT;
}

void CHost::Render(HDC hDC)
{
	
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Host");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		70,				// 복사 받을 가로 사이즈
		80,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,			// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
	//__super::Collision_Render(hDC);
}

void CHost::Release()
{
}

void CHost::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_BULLET:
		if (CBullet::BULLET_MONSTER == dynamic_cast<CBullet*>(_pObj)->Get_BulletID())
			break;
		
		if (1 == m_tFrame.iStart)
			m_tStat.fHp -= _pObj->Get_Damage();
		
		break;

	default:
		break;
	}
}

void CHost::Attack()
{
	for (float f = 0; f < 4.f; ++f)
	{
		CObjMgr::Get_Instance()->Add_CObj(OBJ_BULLET, Create_Bullet<CMonsterBullet>(
			m_tInfo.fX, m_tInfo.fY,
			34.f, 34.f,
			90.f * f , 0.f, m_tStat.fAttack, 800.f, 5.f));
	}
	
}
