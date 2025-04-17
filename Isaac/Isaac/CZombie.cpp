#include "pch.h"
#include "CZombie.h"
#include "CBmpMgr.h"
#include "CSoundMgr.h"
#include "CObjMgr.h"
#include "CMonsterDeathEffect.h"
#include "CBullet.h"
#include "CTools.h"
#include "CTile.h"

CZombie::CZombie() : m_fMeatHp(0.f), m_eCurState(ST_END), m_ePreState(ST_END)
{
}

CZombie::~CZombie()
{
    Release();
}

void CZombie::Initialize()
{
	Set_Stat(10.f, 1.f, 800.f, 1.4f);

	Set_Frame(0, 3, 0);
	m_tFrame.dwFrameSpeed = 500;
	m_tFrame.dwTime = GetTickCount64();
	m_eCurState = CZombie::LEFT;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Monster/Zombie.bmp", L"Zombie");

	m_iSoundChennel = CSoundMgr::Get_Instance()->Get_AvailableChennel();
}

void CZombie::Late_Initialize()
{
	Set_CollisionBoxPos(m_tInfo.fX + 10.f, m_tInfo.fY);
	Set_CollisionBoxSize(50.f, 50.f);
	m_fMeatHp = 10.f;
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
}

int CZombie::Update()
{
	if (m_bDead || m_fMeatHp < 0.f)
	{
		CSoundMgr::Get_Instance()->Return_Chennel(m_iSoundChennel);
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Meaty_Deaths_2.mp3", SOUND_EFFECT, 1.f);
		CObjMgr::Get_Instance()->Add_CObj(OBJ_DEADEFFECT, Create_Effect<CMonsterDeathEffect>(L"Blood", m_tInfo.fX, m_tInfo.fY, 33.f, 16.f, 0));
		return DEAD;
	}

	__super::Update_Rect();

	return NOEVENT;
}

int CZombie::Late_Update()
{
	

	m_fAngle = CTools::Get_Angle(m_pTarget, &m_tInfo);

	if(CZombie::LEFT == m_eCurState || CZombie::RIGHT == m_eCurState){
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
	}

	switch (m_eCurState)
	{
	case CZombie::LEFT:
		if (m_tInfo.fX > m_pTarget->Get_Info()->fX)
			m_eCurState = CZombie::RIGHT;
		break;

	case CZombie::RIGHT:
		if (m_tInfo.fX < m_pTarget->Get_Info()->fX)
			m_eCurState = CZombie::LEFT;
		break;

	case CZombie::MEAT:
		if (m_tFrame.dwTime + 1000 < GetTickCount64())
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Scared_Whimper_2.mp3", m_iSoundChennel, 1.f);
			m_eCurState = CZombie::RESURRECTION;
			m_tStat.fHp = 1.f;
		}
		break;
		
	case CZombie::RESURRECTION:
		if (m_tFrame.iStart == 6)
		{
			
			m_eCurState = CZombie::RIGHT;
			m_tStat.fHp = 10.f;
			m_fMeatHp = 10.f;
			Set_CollisionBoxSize(50.f, 50.f);
		}
		break;

	default:
		break;
	}

	if (m_tStat.fHp <= 0.f)
		m_eCurState = CZombie::MEAT;

	Change_Motion();
	__super::Move_Frame();
	
	Set_CollisionBoxPos(m_tInfo.fX+5.f, m_tInfo.fY+7.f);
	

	return NOEVENT;
}

void CZombie::Render(HDC hDC)
{
	//__super::Collision_Render(hDC);
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Zombie");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		64,				// 복사 받을 가로 사이즈
		64,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,			// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
	
}

void CZombie::Release()
{
}

void CZombie::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_BULLET:
		if (CBullet::BULLET_MONSTER == dynamic_cast<CBullet*>(_pObj)->Get_BulletID())
			break;
		if (CZombie::MEAT != m_eCurState)
			m_tStat.fHp -= _pObj->Get_Damage();
		else
			m_fMeatHp -= _pObj->Get_Damage();

		break;
	case OBJ_TILE:
		switch (dynamic_cast<CTile*>(_pObj)->Get_Option())
		{
		case 0:
			break;
		case 4:
			break;
		case 1:
		case 2:
		case 3:
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
		default:
			break;
		}

		break;
	case OBJ_MONSTER:
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

void CZombie::Change_Motion()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CZombie::LEFT:
			Set_Frame(0, 3, 0);
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CZombie::RIGHT:
			Set_Frame(0, 3, 1);
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CZombie::MEAT:
			Set_Frame(0, 0, 3);
			m_tFrame.dwFrameSpeed = 10000;
			m_tFrame.dwTime = GetTickCount64();
			Set_CollisionBoxSize(30.f, 20.f);
			break;

		case CZombie::RESURRECTION:
			Set_Frame(0, 6, 2);
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwTime = GetTickCount64();
			break;
		
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}

}