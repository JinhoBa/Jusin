#include "pch.h"
#include "CBombEffect.h"
#include "CBmpMgr.h"
#include "CTile.h"
#include "CSoundMgr.h"

CBombEffect::CBombEffect()
{
}

CBombEffect::~CBombEffect()
{
	Release();
}

void CBombEffect::Initialize()
{
	Set_Frame(0, 10, 0);
	m_tFrame.dwFrameSpeed = 100;

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	Set_CollisionBoxSize(150.f, 150.f);

	m_tStat.fAttack = 5.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Effect/explosion.bmp", L"explosion");
	
	Set_Sound(L"Explosion.mp3", 1.f);
}

void CBombEffect::Late_Initialize()
{
}

int CBombEffect::Update()
{
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->Return_Chennel(m_iSoundChennel);
		return DEAD;
	}

	__super::Update_Rect();
	Set_CollisionBoxPos(m_tInfo.fX - 5.f, m_tInfo.fY - 5.f);

	return NOEVENT;
}

int CBombEffect::Late_Update()
{
	__super::Move_Frame();

	if (m_tFrame.iStart == 2)
		Set_CollisionBoxSize(0.f, 0.f);

	if (m_tFrame.iStart == m_tFrame.iEnd)
		m_bDead = true;

	return NOEVENT;
}

void CBombEffect::Render(HDC hDC)
{
	//__super::Collision_Render(hDC);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top-50,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCX,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,			// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(0, 0, 0));
}

void CBombEffect::Release()
{
}

void CBombEffect::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_TILE:
		if (2 != dynamic_cast<CTile*>(_pObj)->Get_Option())
		{
			dynamic_cast<CTile*>(_pObj)->Set_DrawID(0);
			dynamic_cast<CTile*>(_pObj)->Set_OptionID(0);
		}
		break;

	case OBJ_PLAYER:
		_pObj->Set_Hp(1.f);
		break;

	case OBJ_MONSTER:
		_pObj->Set_Hp(m_tStat.fAttack);
		break;

	case OBJ_ITEM:
		_pObj->Set_Dead();
		break;

	default:
		break;
	}
}
