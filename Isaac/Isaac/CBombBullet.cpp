#include "pch.h"
#include "CBombBullet.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CTile.h"
#include "CEffect.h"
#include "CBombEffect.h"
#include "CCollisionMgr.h"

CBombBullet::CBombBullet() : m_dwTime(GetTickCount64()), m_bCollision(false)
{
}

CBombBullet::~CBombBullet()
{
	Release();
}

void CBombBullet::Initialize()
{
	m_eBulletID = BULLET_BOMB;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bullet/bomb.bmp", L"bomb");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Effect/explosion.bmp", L"explosion");

	Set_CollisionBoxPos(m_tInfo.fX -10.f, m_tInfo.fY);
	Set_CollisionBoxSize(40.f, 40.f);

	Set_Frame(0, 0, 0);
	m_tFrame.dwFrameSpeed = 30;
	m_tFrame.dwTime = GetTickCount64();
}

void CBombBullet::Late_Initialize()
{
}

int CBombBullet::Update()
{
	if (m_bDead)
		return DEAD;
	__super::Update_Rect();
	__super::Move_Frame();
	Set_CollisionBoxPos(m_tInfo.fX - 5.f, m_tInfo.fY - 5.f);

	return NOEVENT;
}

int CBombBullet::Late_Update()
{
	if (m_dwTime + 500 < GetTickCount64())
	{
		m_bCollision = true;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 1;
	}

	if (m_dwTime + 1500 < GetTickCount64())
	{
		CObjMgr::Get_Instance()->Add_CObj(OBJ_EFFECT, Create_Effect<CBombEffect>(L"explosion", m_tInfo.fX, m_tInfo.fY, 192.f, 192.f));
		m_bDead = true;
	}
		

	return NOEVENT;
}

void CBombBullet::Render(HDC hDC)
{
	//__super::Collison_Render(hDC);
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"bomb");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX - 10,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY - 10,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		//m_tFrame.iStart * (int)m_tInfo.fCX + m_tFrame.iStart * 10.f,
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,// * m_tFrame.iMotion,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CBombBullet::Release()
{
}

void CBombBullet::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_TILE:
		if (0 != dynamic_cast<CTile*>(_pObj)->Get_Option())
		{
			switch (_tHitPoint.eDirection)
			{
			case DIR_DOWN:
				m_tInfo.fY += _tHitPoint.fY;
				break;
			case DIR_UP:
				m_tInfo.fY -= _tHitPoint.fY;
				break;
			case DIR_LEFT:
				m_tInfo.fX -= _tHitPoint.fX;
				break;
			case DIR_RIGHT:
				m_tInfo.fX += _tHitPoint.fX;
				break;
			default:
				break;
			}
		}
		break;

	case OBJ_PLAYER:
		if(m_bCollision)
		{
			switch (_tHitPoint.eDirection)
			{
			case DIR_DOWN:
				m_tInfo.fY += _tHitPoint.fY;
				break;
			case DIR_UP:
				m_tInfo.fY -= _tHitPoint.fY;
				break;
			case DIR_LEFT:
				m_tInfo.fX -= _tHitPoint.fX;
				break;
			case DIR_RIGHT:
				m_tInfo.fX += _tHitPoint.fX;
				break;
			default:
				break;
			}
		}
		break;

	default:
		break;
	}
}
