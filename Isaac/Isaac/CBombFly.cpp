#include "pch.h"
#include "CBombFly.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CTools.h"
#include "CTile.h"
#include "CBombEffect.h"
#include "CBullet.h"

CBombFly::CBombFly() : m_fDirX(0.f), m_fDirY(0.f)
{
}

CBombFly::~CBombFly()
{
    Release();
}

void CBombFly::Initialize()
{

	Set_Stat(3.f, 1.f, 0.f, 1.5f);
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	Set_Frame(0, 1, 0);
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwTime = GetTickCount64();

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	Set_CollisionBoxSize(40.f, 40.f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Monster/BombFly.bmp", L"BombFly");

	m_fDirX = 1.f;
	m_fDirY = 1.f;
}

void CBombFly::Late_Initialize()
{

}

int CBombFly::Update()
{
	if (m_bDead || m_tStat.fHp < 0.f)
	{
		CObjMgr::Get_Instance()->Add_CObj(OBJ_EFFECT, Create_Effect<CBombEffect>(L"explosion", m_tInfo.fX, m_tInfo.fY, 192.f, 192.f, 10));
		return DEAD;
	}
        

    __super::Update_Rect();

    return NOEVENT;
}

int CBombFly::Late_Update()
{

	m_tInfo.fX += m_fSpeed * m_fDirX;
	m_tInfo.fY -= m_fSpeed * m_fDirY;

	__super::Move_Frame();
	__super::Set_CollisionBoxPos(m_tInfo.fX + 5.f, m_tInfo.fY + 10.f);

    return NOEVENT;
}

void CBombFly::Render(HDC hDC)
{
	//__super::Collision_Render(hDC);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BombFly");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		50,				// 복사 받을 가로 사이즈
		50,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,			// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CBombFly::Release()
{

}

void CBombFly::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_TILE:
		if (2 == dynamic_cast<CTile*>(_pObj)->Get_Option())
		{
			switch (_tHitPoint.eDirection)
			{
			case DIR_DOWN:
				m_tInfo.fY += _tHitPoint.fY;
				m_fDirY *= -1.f;
				break;
			case DIR_UP:
				m_tInfo.fY -= _tHitPoint.fY;
				m_fDirY *= -1.f;
				break;
			case DIR_LEFT:
				m_fDirX *= -1.f;
				m_tInfo.fX -= _tHitPoint.fX;
				break;
			case DIR_RIGHT:
				m_fDirX *= -1.f;
				m_tInfo.fX += _tHitPoint.fX;
				break;
			default:
				break;
			}
		}
		break;

	case OBJ_BULLET:
		if (CBullet::BULLET_MONSTER == dynamic_cast<CBullet*>(_pObj)->Get_BulletID())
			break;
		m_tStat.fHp -= _pObj->Get_Damage();
		break;
	default:
		break;
	}
}
