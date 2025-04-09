#include "pch.h"
#include "CFly.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CTile.h"
#include "CTools.h"
#include "CBullet.h"

CFly::CFly()
{
}

CFly::~CFly()
{
	Release();
}

void CFly::Initialize()
{
	m_fSpeed = 1.f;

	Set_Stat(3.f, 1.f, 0.f);
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 30.f;

	Set_Frame(0, 3, 0);
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwTime = GetTickCount64();

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	Set_CollisionBoxSize(30.f, 30.f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Monster/Fly.bmp", L"Fly");

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
}

void CFly::Late_Initialize()
{
}

int CFly::Update()
{
	if (m_bDead || m_tStat.fHp < 0.f)
		return DEAD;
	
	__super::Update_Rect();

	return NOEVENT;
}

int CFly::Late_Update()
{
	
	m_fAngle = CTools::Get_Angle(m_pTarget, &m_tInfo);

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f);
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f);

		
	__super::Move_Frame();
	__super::Set_CollisionBoxPos(m_tInfo.fX+10.f, m_tInfo.fY+10.f);

	return NOEVENT;
}

void CFly::Render(HDC hDC)
{
	//__super::Collison_Render(hDC);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Fly");

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

void CFly::Release()
{
}

void CFly::Collision(CObj* _pObj, HITPOINT _tHitPoint)
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

	case OBJ_BULLET:
		if (CBullet::BULLET_PLAYER != dynamic_cast<CBullet*>(_pObj)->Get_BulletID())
			break;
		switch (_tHitPoint.eDirection)
		{
		case DIR_DOWN:
			m_tInfo.fY += _tHitPoint.fY + 20.f;
			break;
		case DIR_UP:
			m_tInfo.fY -= _tHitPoint.fY + 20.f;
			break;
		case DIR_LEFT:
			m_tInfo.fX -= _tHitPoint.fX + 20.f;
			break;
		case DIR_RIGHT:
			m_tInfo.fX += _tHitPoint.fX + 20.f;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
