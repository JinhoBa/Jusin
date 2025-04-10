#include "pch.h"
#include "CMonsterBullet.h"
#include "CBmpMgr.h"
#include "CTile.h"
#include "CEffect.h"
#include "CObjMgr.h"

CMonsterBullet::CMonsterBullet()
{
}

CMonsterBullet::~CMonsterBullet()
{
	Release();
}

void CMonsterBullet::Initialize()
{
	m_eBulletID = BULLET_MONSTER;

	m_fSpeed = 3.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Bullet/RedBullet.bmp", L"Monster_Bullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Effect/RedBullet_dead.bmp", L"Monster_bullet_death");

	Set_CollisionBoxPos(m_tInfo.fX - 1.f, m_tInfo.fY);
	Set_CollisionBoxSize(10.f, 10.f);

	Set_Frame(0, 0, 0);
}

void CMonsterBullet::Late_Initialize()
{
	


}

int CMonsterBullet::Update()
{
	if (m_bDead)
		return DEAD;

	__super::Update_Rect();

	Set_CollisionBoxPos(m_tInfo.fX - 1.f, m_tInfo.fY);

	return NOEVENT;
}

int CMonsterBullet::Late_Update()
{
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);

    return NOEVENT;
}

void CMonsterBullet::Render(HDC hDC)
{
	__super::Collision_Render(hDC);
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Monster_Bullet");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		//m_tFrame.iStart * (int)m_tInfo.fCX + m_tFrame.iStart * 10.f,
		(int)m_tInfo.fCX * m_tFrame.iStart,
		0,// * m_tFrame.iMotion,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,			// 복사할 이미지의 가로
		(int)m_tInfo.fCY,			// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CMonsterBullet::Release()
{
}

void CMonsterBullet::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_TILE:
		if (0 != dynamic_cast<CTile*>(_pObj)->Get_Option())
		{
			CObjMgr::Get_Instance()->Add_CObj(OBJ_EFFECT, Create_Effect<CEffect>(L"Monster_bullet_death", m_tInfo.fX, m_tInfo.fY, 60.f, 60.f));
			m_bDead = true;
		}
		break;

	case OBJ_PLAYER:
		CObjMgr::Get_Instance()->Add_CObj(OBJ_EFFECT, Create_Effect<CEffect>(L"Monster_bullet_death", m_tInfo.fX, m_tInfo.fY, 60.f, 60.f));
		_pObj->Set_Hp(m_tStat.fAttack);
		m_bDead = true;
		break;

	default:
		break;
	}
}
