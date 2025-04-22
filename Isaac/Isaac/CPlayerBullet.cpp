#include "pch.h"
#include "CPlayerBullet.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CEffect.h"
#include "CTile.h"
#include "CSoundMgr.h"
#include "CTools.h"

CPlayerBullet::CPlayerBullet() : m_fDistance(0.f)
{
}

CPlayerBullet::~CPlayerBullet()
{
}

void CPlayerBullet::Initialize()
{
	m_eBulletID = BULLET_PLAYER;

	m_fSpeed = 5.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bullet/Bullet.bmp", L"Player_Bullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Effect/bullet_death.bmp", L"bullet_death");

	Set_CollisionBoxPos(m_tInfo.fX - 1.f, m_tInfo.fY);
	Set_CollisionBoxSize(10.f, 10.f);
	Set_Frame(0, 0, 0);

	
	
	if ((CTools::Get_RandomNumber(1, 2) % 2) == 0)
		Set_Sound(L"Tears_Fire_1.mp3", 1.f);
	else
		Set_Sound(L"Tears_Fire_0.mp3", 1.f);
}

void CPlayerBullet::Late_Initialize()
{
}

int CPlayerBullet::Update()
{
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(m_iSoundChennel);
		CSoundMgr::Get_Instance()->Return_Chennel(m_iSoundChennel);
		CObjMgr::Get_Instance()->Add_CObj(OBJ_EFFECT, Create_Effect<CEffect>(L"bullet_death", m_tInfo.fX, m_tInfo.fY, 60.f, m_tInfo.fCY, 4));
		return DEAD;
	}
	__super::Update_Rect();
	Set_CollisionBoxPos(m_tInfo.fX - 1.f, m_tInfo.fY);

	return NOEVENT;
}

int CPlayerBullet::Late_Update()
{
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);

	if (3 <= m_tStat.fAttack && 5 > m_tStat.fAttack)
		m_tFrame.iStart = 1;
	else if (5 <= m_tStat.fAttack)
		m_tFrame.iStart = 2;

	if (90.f == m_fAngle || 270.f == m_fAngle)
	{
		if (m_tStat.fIntersection < m_fDistance + 40.f)
		{
			m_tInfo.fY += 0.2f * 9.8f * m_fSpeed * 0.25f;
		}
	}

	if (m_tStat.fIntersection < m_fDistance)
	{
		m_bDead = true;
	}
	m_fDistance += m_fSpeed;

	return NOEVENT;
}

void CPlayerBullet::Render(HDC hDC)
{
	__super::Collision_Render(hDC);
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Player_Bullet");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		//m_tFrame.iStart * (int)m_tInfo.fCX + m_tFrame.iStart * 10.f,
		(int)m_tInfo.fCX * m_tFrame.iStart,
		0,// * m_tFrame.iMotion,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));			// 제거할 이미지 색상 값
}

void CPlayerBullet::Release()
{
}

void CPlayerBullet::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_TILE:
		if (0 != dynamic_cast<CTile*>(_pObj)->Get_Option() && 4 != dynamic_cast<CTile*>(_pObj)->Get_Option())
		{
			m_bDead = true;
		}
		break;

	case OBJ_MONSTER:
		m_bDead = true;
		break;

	default:
		break;
	}
}
