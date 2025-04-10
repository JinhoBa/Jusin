#include "pch.h"
#include "CBoss.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CBullet.h"
#include "CTile.h"
#include "CTools.h"
#include "CMonsterBullet.h"

CBoss::CBoss() : m_bLeft(true)
{
}

CBoss::~CBoss()
{
    Release();
}

void CBoss::Initialize()
{
	m_fSpeed = 1.f;
	m_tInfo.fCX = 120.f;
	m_tInfo.fCY = 120.f;

	Set_Stat(100.f, 1.f, 0.f);
	
	Set_Frame(0, 0, 0);
	m_tFrame.dwFrameSpeed = 1000;
	m_tFrame.dwTime = GetTickCount64();
	m_pFrameKey = L"Boss_LEFT";

	Set_CollisionBoxPos(m_tInfo.fX+10.f, m_tInfo.fY+18.f);
	Set_CollisionBoxSize(110.f, 80.f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Boss_LEFT.bmp", L"Boss_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Boss_RIGHT.bmp", L"Boss_RIGHT");

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
}

void CBoss::Late_Initialize()
{
}

int CBoss::Update()
{
	if (m_bDead || m_tStat.fHp < 0.f)
		return DEAD;

	

	__super::Update_Rect();
	__super::Move_Frame();
	Change_Motion();
	

	return NOEVENT;
}

int CBoss::Late_Update()
{
	switch (m_eCurState)
	{
	case CBoss::IDLE:
		if (m_MotionTime + 3000 < GetTickCount64())
		{
			m_eCurState = CBoss::ATTACK;
		}
		else
		{
			m_fAngle = CTools::Get_Angle(m_pTarget, &m_tInfo);

			m_tInfo.fX += cosf(m_fAngle * PI / 180.f);
			m_tInfo.fY -= sinf(m_fAngle * PI / 180.f);
		}
		break;

	case CBoss::ATTACK:
		if (m_MotionTime + 1500 < GetTickCount64())
		{
			m_fAngle = CTools::Get_Angle(m_pTarget, &m_tInfo);

			for(int i=0; i < 5; ++i)
			{
				float fTmp = (float)(rand() % 10);
				CObjMgr::Get_Instance()->Add_CObj(OBJ_BULLET, Create_Bullet<CMonsterBullet>(
					m_tInfo.fX, m_tInfo.fY,
					34.f, 34.f,
					m_fAngle+ i*3 -10, i, 1.f, 300.f));
			}
			m_eCurState = IDLE;
		}
		else
		{
			
		}
		break;

	case CBoss::HIT:
		break;

	case CBoss::JUMP_ATTACK:
		break;

	case CBoss::SPOWN:
		break;

	case CBoss::BS_END:
		break;
	default:
		break;
	}

	if (CBoss::HIT == m_eCurState)
	{
		
	}
	
	__super::Set_CollisionBoxPos(m_tInfo.fX , m_tInfo.fY + 18.f);

	return NOEVENT;
}

void CBoss::Render(HDC hDC)
{
	//__super::Collision_Render(hDC);
	if (m_bLeft)
		m_pFrameKey = L"Boss_LEFT";
	else
		m_pFrameKey = L"Boss_RIGHT";

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		130,				// 복사 받을 가로 사이즈
		130,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,			// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CBoss::Release()
{
}

void CBoss::Collision(CObj* _pObj, HITPOINT _tHitPoint)
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

	case OBJ_BULLET:
		if (CBullet::BULLET_PLAYER != dynamic_cast<CBullet*>(_pObj)->Get_BulletID())
			break;
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
		break;
	default:
		break;
	}
}

void CBoss::Change_Motion()
{
	
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CBoss::IDLE:
			Set_Frame(0, 0, 0);
			m_tFrame.dwFrameSpeed = 1000;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CBoss::ATTACK:
			Set_Frame(0, 2, 1);
			m_tFrame.dwFrameSpeed = 500;
			m_tFrame.dwTime = GetTickCount64();
			m_MotionTime = GetTickCount64();
			break;

		case CBoss::HIT:
			Set_Frame(0, 1, 2);
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwTime = GetTickCount64();
			m_MotionTime = GetTickCount64();
			break;

		case CBoss::JUMP_ATTACK:
			Set_Frame(0, 0, 3);
			m_tFrame.dwFrameSpeed = 1000;
			m_tFrame.dwTime = GetTickCount64();
			m_MotionTime = GetTickCount64();
			break;
		case CBoss::SPOWN:
			Set_Frame(0, 1, 4);
			m_tFrame.dwFrameSpeed = 2000;
			m_tFrame.dwTime = GetTickCount64();
			m_MotionTime = GetTickCount64();
			break;
		case CBoss::BS_END:
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}

	
}
