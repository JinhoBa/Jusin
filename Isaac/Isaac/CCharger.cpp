#include "pch.h"
#include "CCharger.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "CMonsterDeathEffect.h"
#include "CTools.h"
#include "CBullet.h"
#include "CTile.h"
#include "CSoundMgr.h"

CCharger::CCharger() : m_ePreState(ST_END), m_eCurState(TOP), m_fOffX(0.f), m_fOffY(0.f), m_eStateDIR(ST_END)
{
}

CCharger::~CCharger()
{
	Release();
}

void CCharger::Initialize()
{
	Set_Stat(10.f, 1.f, 800.f, 1.6f);

	Set_Frame(0, 3, 0);
	m_tFrame.dwFrameSpeed = 500;
	m_tFrame.dwTime = GetTickCount64();
	

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Monster/Charger.bmp", L"Charger");

	m_iSoundChennel = CSoundMgr::Get_Instance()->Get_AvailableChennel();
}

void CCharger::Late_Initialize()
{
	
	
	Set_CollisionBoxPos(m_tInfo.fX + 25.f, m_tInfo.fY+15.f);
	
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
}

int CCharger::Update()
{
	if (m_bDead || m_tStat.fHp <= 0.f)
	{
		CSoundMgr::Get_Instance()->StopSound(m_iSoundChennel);
		CSoundMgr::Get_Instance()->Return_Chennel(m_iSoundChennel);
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Meaty_Deaths_0.mp3", SOUND_EFFECT, 1.f);
		CObjMgr::Get_Instance()->Add_CObj(OBJ_DEADEFFECT, Create_Effect<CMonsterDeathEffect>(L"Blood", m_tInfo.fX, m_tInfo.fY, 33.f, 16.f, 0));
		return DEAD;
	}

	__super::Update_Rect();
	
	return NOEVENT;
}

int CCharger::Late_Update()
{
	if (LEFT == m_eCurState || RIGHT == m_eCurState)
	{
		Set_CollisionBoxSize(25.f, 15.f);
		m_fOffX = 10.f;
		m_fOffY = 12.f;
	}
	else
	{
		Set_CollisionBoxSize(15.f, 20.f);
		m_fOffX = 8.f;
		m_fOffY = 12.f;
	}

	Set_CollisionBoxPos(m_tInfo.fX + m_fOffX, m_tInfo.fY + m_fOffY);

	Change_Motion();

	switch (m_eCurState)
	{
	case CCharger::LEFT:
		m_tInfo.fX -= m_fSpeed;
		__super::Move_Frame();
		if (m_pTarget->Get_Info()->fX < m_tInfo.fX &&
			fabsf(m_pTarget->Get_Info()->fY - m_tInfo.fY) < 10.f
			)
		{
			m_eCurState = CCharger::ATTACK;
		}
		break;

	case CCharger::RIGHT:
		m_tInfo.fX += m_fSpeed;
		__super::Move_Frame();
		if (m_pTarget->Get_Info()->fX > m_tInfo.fX &&
			fabsf(m_pTarget->Get_Info()->fY - m_tInfo.fY) < 10.f
			)
		{
			m_eCurState = CCharger::ATTACK;
		}
		break;

	case CCharger::TOP:
		m_tInfo.fY -= m_fSpeed;
		__super::Move_Frame();
		if (m_pTarget->Get_Info()->fY < m_tInfo.fY &&
			fabsf(m_pTarget->Get_Info()->fX - m_tInfo.fX) < 10.f
			)
		{
			m_eCurState = CCharger::ATTACK;
		}
		break;

	case CCharger::BOTTOM:
		m_tInfo.fY += m_fSpeed;
		__super::Move_Frame();
		if (m_pTarget->Get_Info()->fY > m_tInfo.fY &&
			fabsf(m_pTarget->Get_Info()->fX - m_tInfo.fX) < 10.f
			)
		{
			m_eCurState = CCharger::ATTACK;
		}
		break;

	case CCharger::ATTACK:
		if (m_tFrame.dwTime + 1500 < GetTickCount64())
		{
			m_eCurState = m_eStateDIR;
		}
		else
		{
			switch (m_eStateDIR)
			{
			case CCharger::LEFT:
				m_tInfo.fX -= m_fSpeed * 2.f;
				break;
			case CCharger::TOP:
				m_tInfo.fY -= m_fSpeed *2.f;
				break;
			case CCharger::RIGHT:
				m_tInfo.fX += m_fSpeed * 2.f;
				break;
			case CCharger::BOTTOM:
				m_tInfo.fY += m_fSpeed * 2.f;
				break;
			default:
				break;
			}
		}
		break;

	default:
		break;
	}


	

	


	return NOEVENT;
}

void CCharger::Render(HDC hDC)
{
	
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Charger");

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
	//__super::Collision_Render(hDC);
}

void CCharger::Release()
{
}

void CCharger::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_BULLET:
		if (CBullet::BULLET_MONSTER == dynamic_cast<CBullet*>(_pObj)->Get_BulletID())
			break;

		m_tStat.fHp -= _pObj->Get_Damage();
		break;

	case OBJ_TILE:
		if (0 == dynamic_cast<CTile*>(_pObj)->Get_Option())
			return;
		
		switch (_tHitPoint.eDirection)
		{
		case DIR_DOWN:
			m_tInfo.fY += _tHitPoint.fY;
			m_eCurState = BOTTOM;
			break;
		case DIR_UP:
			m_tInfo.fY -= _tHitPoint.fY;
			m_eCurState = TOP;
			break;
		case DIR_LEFT:
			m_tInfo.fX -= _tHitPoint.fX;
			m_eCurState = LEFT;
			break;
		case DIR_RIGHT:
			m_tInfo.fX += _tHitPoint.fX;
			m_eCurState = RIGHT;
			break;
		default:
			break;
		}

	default:
		break;
	}
}

void CCharger::Change_Motion()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CCharger::LEFT:
			Set_Frame(0, 3, 0);
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwTime = GetTickCount64();
			m_eStateDIR = CCharger::LEFT;
				
			break;

		case CCharger::RIGHT:
			Set_Frame(0, 3, 1);
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwTime = GetTickCount64();
			m_eStateDIR = CCharger::RIGHT;		
			break;

		case CCharger::TOP:
			Set_Frame(0, 3, 2);
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwTime = GetTickCount64();
			m_eStateDIR = CCharger::TOP;
			break;

		case CCharger::BOTTOM:
			Set_Frame(0, 3, 3);
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwTime = GetTickCount64();
			m_eStateDIR = CCharger::BOTTOM;
			break;

		case CCharger::ATTACK:
			m_tFrame.dwTime = GetTickCount64();
			m_tFrame.iMotion = 4;
			CSoundMgr::Get_Instance()->StopSound(m_iSoundChennel);
			CSoundMgr::Get_Instance()->PlaySound(L"ChargerAttack.mp3", m_iSoundChennel, 1.f);
			switch (m_eStateDIR)
			{
			case CCharger::LEFT:
				m_tFrame.iStart = 2;
				break;
			case CCharger::TOP:
				m_tFrame.iStart = 3;
				break;
			case CCharger::RIGHT:
				m_tFrame.iStart = 1;
				break;
			case CCharger::BOTTOM:
				m_tFrame.iStart = 0;
				break;
			
			default:
				break;
			}
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}

}
