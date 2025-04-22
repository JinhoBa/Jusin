#include "pch.h"
#include "CMulligan.h"
#include "CBmpMgr.h"
#include "CSoundMgr.h"
#include "CObjMgr.h"
#include "CMonsterDeathEffect.h"
#include "CTools.h"
#include "CTile.h"
#include "CFly.h"
#include "CMonsterBullet.h"

CMulligan::CMulligan()
{
}

CMulligan::~CMulligan()
{
    Release();
}

void CMulligan::Initialize()
{
	Set_Stat(10.f, 1.f, 800.f, 1.4f);

	Set_Frame(0, 3, 0);
	m_tFrame.dwFrameSpeed = 500;
	m_tFrame.dwTime = GetTickCount64();
	m_eCurState = LEFT;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Monster/Mulligan_LEFT.bmp", L"Mulligan_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Monster/Mulligan_RIGHT.bmp", L"Mulligan_RIGHT");

	m_pFrameKey = L"Mulligan_LEFT";
	m_iSoundChennel = CSoundMgr::Get_Instance()->Get_AvailableChennel();
}

void CMulligan::Late_Initialize()
{
	Set_CollisionBoxPos(m_tInfo.fX + 10.f, m_tInfo.fY);
	Set_CollisionBoxSize(50.f, 50.f);
	
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
}

int CMulligan::Update()
{
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(m_iSoundChennel);
		CSoundMgr::Get_Instance()->Return_Chennel(m_iSoundChennel);
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Meaty_Deaths_3.mp3", SOUND_EFFECT, 1.f);
		CObjMgr::Get_Instance()->Add_CObj(OBJ_DEADEFFECT, Create_Effect<CMonsterDeathEffect>(L"Blood", m_tInfo.fX, m_tInfo.fY, 33.f, 16.f, 0));
		return DEAD;
	}

	__super::Update_Rect();

	return NOEVENT;
}

int CMulligan::Late_Update()
{
	__super::Move_Frame();

	if (m_pTarget->Get_Info()->fX > m_tInfo.fX)
		m_eCurState = LEFT;
	else
		m_eCurState = RIGHT;

	Move();

	Set_CollisionBoxPos(m_tInfo.fX + 5.f, m_tInfo.fY + 7.f);


	return NOEVENT;
}

void CMulligan::Render(HDC hDC)
{
	//__super::Collision_Render(hDC);
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

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

void CMulligan::Release()
{
}

void CMulligan::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_TILE:
		if(2 == dynamic_cast<CTile*>(_pObj)->Get_Option())
		{
			m_fAngle = CTools::Get_Angle(m_pTarget, &m_tInfo);
			Set_CollisionBoxSize(0.f, 0.f);
			for(int i = 0; i < 4; ++i)
			{
				CObjMgr::Get_Instance()->Add_CObj(
					OBJ_MONSTER, 
					CAbstractFactory<CFly>::Create_Obj(
						m_tInfo.fX + 20.f*i * cosf(m_fAngle * PI / 180.f), 
						m_tInfo.fY - 20.f*i * sinf(m_fAngle * PI / 180.f),
						32.f, 30.f
					));
			}
			m_bDead = true;
		}
		break;

	case OBJ_BULLET:
		m_tStat.fHp -= _pObj->Get_Damage();
		if (m_tStat.fHp <= 0.f)
		{
			for (int i = 0; i < 4; ++i)
			{
				CObjMgr::Get_Instance()->Add_CObj(OBJ_BULLET, Create_Bullet<CMonsterBullet>(
					m_tInfo.fX, m_tInfo.fY,
					34.f, 34.f,
					90.f * (float)i, 0.f, m_tStat.fAttack, 800.f, 5.f));
			}
			m_bDead = true;
		}
		break;

	default:
		break;
	}
}

void CMulligan::Change_Motion()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CMulligan::LEFT:
			Set_Frame(0, 7, 0);
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwTime = GetTickCount64();
			m_pFrameKey = L"Mulligan_LEFT";
			break;
		case CMulligan::RIGHT:
			Set_Frame(0, 7, 0);
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwTime = GetTickCount64();
			m_pFrameKey = L"Mulligan_RIGHT";
			break;
		case CMulligan::ST_END:
			break;
		default:
			break;
		}
	}
}

void CMulligan::Move()
{
	if(CTools::Get_Distance(m_pTarget, &m_tInfo) < 200.f)
	{
		m_fAngle = CTools::Get_Angle(m_pTarget, &m_tInfo);
		m_tInfo.fX += -m_fSpeed * cosf(m_fAngle * PI / 180.f);
		m_tInfo.fY -= -m_fSpeed * sinf(m_fAngle * PI / 180.f);
	}
}
