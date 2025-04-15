#include "pch.h"
#include "CZombie.h"

CZombie::CZombie()
{
}

CZombie::~CZombie()
{
    Release();
}

void CZombie::Initialize()
{
	Set_Stat(20.f, 1.f, 800.f, 1.f);

	Set_Frame(0, 3, 0);
	m_tFrame.dwFrameSpeed = 2000;
	m_tFrame.dwTime = GetTickCount64();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Monster/Host.bmp", L"Host");
}

void CZombie::Late_Initialize()
{
	Set_CollisionBoxPos(m_tInfo.fX + 10.f, m_tInfo.fY);
	Set_CollisionBoxSize(30.f, 30.f);
}

int CZombie::Update()
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

int CZombie::Late_Update()
{
	__super::Move_Frame();

	if (1 == m_tFrame.iStart && 0 == m_iPreFrame)
		Attack();
	if (1 == m_tFrame.iStart)
		Set_CollisionBoxSize(30.f, 30.f);
	else
		Set_CollisionBoxSize(30.f, 20.f);
	m_iPreFrame = m_tFrame.iStart;

	return NOEVENT;
}

void CZombie::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Host");

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
	__super::Collision_Render(hDC);
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

		if (1 == m_tFrame.iStart)
			m_tStat.fHp -= _pObj->Get_Damage();

		break;

	default:
		break;
	}
}
