#include "pch.h"
#include "CBoss.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CBullet.h"
#include "CTile.h"
#include "CTools.h"
#include "CMonsterBullet.h"
#include "CTools.h"
#include "CFly.h"
#include "CBox.h"
#include "CCyclops.h"
#include "CSoundMgr.h"

CBoss::CBoss() 
	: m_bLeft(true), m_bHit(false), m_HitTime(GetTickCount64()), m_MotionTime(GetTickCount64()), m_ePreState(IDLE), m_eCurState(IDLE), m_fTime(0.f), m_fAfterY(0.f)
{
}

CBoss::~CBoss()
{
    Release();
}

void CBoss::Initialize()
{
	m_tInfo.fCX = 120.f;
	m_tInfo.fCY = 120.f;

	Set_Stat(100.f, 1.f, 0.f, 1.f);
	
	Set_Frame(0, 0, 0);
	m_tFrame.dwFrameSpeed = 1000;
	m_tFrame.dwTime = GetTickCount64();
	m_pFrameKey = L"Boss_LEFT";

	Set_CollisionBoxPos(m_tInfo.fX+10.f, m_tInfo.fY+18.f);
	Set_CollisionBoxSize(110.f, 80.f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Boss_LEFT.bmp", L"Boss_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Boss_RIGHT.bmp", L"Boss_RIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Boss_LEFT_HIT.bmp", L"Boss_LEFT_HIT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Boss_RIGHT_HIT.bmp", L"Boss_RIGHT_HIT");

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
}

void CBoss::Late_Initialize()
{
}

int CBoss::Update()
{
	if (m_bDead || m_tStat.fHp < 0.f)
	{
		Set_Sound(L"BossClear.mp3", 0.8f);
		CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CCyclops>::Create_Obj(400.f, 400.f, 50.f, 50.f));
		CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CBox>::Create_Obj(400.f, 300.f, 32.f, 32.f));
		return DEAD;
	}

	
	__super::Update_Rect();
	__super::Move_Frame();
	Change_Motion();
	

	return NOEVENT;
}

int CBoss::Late_Update()
{
	m_bLeft = (m_pTarget->Get_Info()->fX < m_tInfo.fX);

	if (m_bHit && m_HitTime + 300 < GetTickCount64())
	{
		m_bHit = false;
		m_HitTime = GetTickCount64();
	}

	switch (m_eCurState)
	{
	case CBoss::IDLE:
		if (m_MotionTime + 3000 < GetTickCount64())
		{
			if(rand() % 5 != 0)
			{
				if (CTools::Get_Distance(m_pTarget, &m_tInfo) < 250.f)
					m_eCurState = CBoss::ATTACK;
				else
					m_eCurState = CBoss::JUMP_ATTACK;
			}
			else
				m_eCurState = CBoss::SPOWN;
		}
		else
		{
			m_fAngle = CTools::Get_Angle(m_pTarget, &m_tInfo);

			m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
			m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
		}
		break;

	case CBoss::ATTACK:
		if (m_MotionTime + 1500 < GetTickCount64())
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"bloodshoot0.mp3", SOUND_EFFECT, 1.f);
			Attack(5);
			Attack(5);
			Attack(5);
			m_eCurState = CBoss::IDLE;
		}
		else
		{

		}
		break;

	case CBoss::JUMP_ATTACK:
		if (m_MotionTime + 2000 < GetTickCount64())
		{
			
			Set_CollisionBoxSize(110.f, 80.f);
			m_eCurState = CBoss::IDLE;
			m_fTime = 0.f;
		}
		else
		{
			if ((m_fTime < 3.f || m_fAfterY > m_tInfo.fY))
			{
				if (m_tInfo.fY < 480.f)
				{
					if(m_tInfo.fX > 110.f && WINCX - 110.f > m_tInfo.fX)
						m_tInfo.fX += 15 * cosf(m_fAngle * PI / 180.f) * m_fTime;
					m_tInfo.fY -= 15 * sinf(m_fAngle * PI / 180.f) * m_fTime - 0.5f * 9.8f * m_fTime * m_fTime;
				}
				m_tFrame.iStart = 2;
				m_fTime += 0.1;

			}
			else
			{
				Set_CollisionBoxSize(110.f, 80.f);
				m_tFrame.iStart = 3;
				
			}
		}
		break;

	case CBoss::SPOWN:
		if (m_MotionTime + 4000 < GetTickCount64())
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Monster_Grunt_5.mp3", SOUND_EFFECT, 1.f);
			CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER,
				CAbstractFactory<CFly>::Create_Obj(m_tInfo.fX+ 50.f, m_tInfo.fY-50.f, 32.f, 30.f));
			CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER,
				CAbstractFactory<CFly>::Create_Obj(m_tInfo.fX+ 50.f, m_tInfo.fY, 32.f, 30.f));
			CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER,
				CAbstractFactory<CFly>::Create_Obj(m_tInfo.fX+ 50.f, m_tInfo.fY+50.f, 32.f, 30.f));
			m_eCurState = IDLE;
		}
		
		break;

	case CBoss::BS_END:
		break;
	default:
		break;
	}

	
	__super::Set_CollisionBoxPos(m_tInfo.fX , m_tInfo.fY + 18.f);

	if (m_bLeft)
	{
		if(m_bHit)
			m_pFrameKey = L"Boss_LEFT_HIT";
		else
			m_pFrameKey = L"Boss_LEFT";
	}
	else
	{
		if (m_bHit)
			m_pFrameKey = L"Boss_RIGHT_HIT";
		else
			m_pFrameKey = L"Boss_RIGHT";
	}

	return NOEVENT;
}

void CBoss::Render(HDC hDC)
{
	//__super::Collision_Render(hDC);
	

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		130,				// 복사 받을 가로 사이즈
		130,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,		// 복사할 이미지의 left, top
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
	/*case OBJ_MONSTER:
		switch (_tHitPoint.eDirection)
		{
		case DIR_DOWN:
			_pObj->Set_posY(_tHitPoint.fY);
			break;
		case DIR_UP:
			_pObj->Set_posY(-_tHitPoint.fY);
			break;
		case DIR_LEFT:
			_pObj->Set_posX(-_tHitPoint.fX);
			break;
		case DIR_RIGHT:
			_pObj->Set_posX(_tHitPoint.fX);
			break;
		default:
			break;
			
		}
		break;*/

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
		m_bHit = true;
		m_HitTime = GetTickCount64();
		
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

		case CBoss::JUMP_ATTACK:
			Set_Frame(0, 3, 3);
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwTime = GetTickCount64();
			m_MotionTime = GetTickCount64();
			m_fAfterY = m_pTarget->Get_Info()->fY;
			Set_CollisionBoxSize(0.f, 0.f);
			m_fAngle = 80.f;
			if (m_bLeft)
				m_fAngle = 100.f;

			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Boss_Smash.mp3", SOUND_EFFECT, 1.f);

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

void CBoss::Attack(int _iCount)
{
	m_fAngle = CTools::Get_Angle(m_pTarget, &m_tInfo);

	for (int i = 0; i < _iCount; ++i)
	{
		float fAttack = (float)CTools::Get_RandomNumber(1, 4);
		float fSpeed = 1.5f + (float)CTools::Get_RandomNumber(1, 5) * 0.5f;

		float fRand = (float)CTools::Get_RandomNumber(0, 10);
		float fX;

		if (m_bLeft)
			fX = m_tInfo.fX - m_tInfo.fCX * 0.2f - fRand;
		else
			fX = m_tInfo.fX + m_tInfo.fCX * 0.2f + fRand;

		CObjMgr::Get_Instance()->Add_CObj(OBJ_BULLET, Create_Bullet<CMonsterBullet>(
			fX, m_tInfo.fY - 20.f,
			34.f, 34.f,
			m_fAngle + fRand * 5.f - 50.f, 0.f, fAttack, 300.f, fSpeed));
	}
}
