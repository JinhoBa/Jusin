#include "pch.h"
#include "CItem.h"
#include "CTools.h"
#include "CTile.h"

CItem::CItem() : m_eItemID(ITEM_END), m_CreateTime(GetTickCount64()), m_fTime(0.f), m_fItemSpeedX(0.f), m_iDropTime(0), m_fItemSpeedY(0.f)
{
}

CItem::~CItem()
{
}

void CItem::Initialize()
{
	m_fAngle = 90.f + (float)CTools::Get_RandomNumber(-15, 15);
	m_fItemSpeedX = (m_fAngle - 90.f) / 3.75f * -1.f;
	m_fItemSpeedY = 0.f;
	m_iDropTime = CTools::Get_RandomNumber(400, 570);
}

void CItem::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_ITEM:
		switch (_tHitPoint.eDirection)
		{
		case DIR_DOWN:
			m_tInfo.fY += _tHitPoint.fY;
			//m_fItemSpeedY = 2.f;
			break;
		case DIR_UP:
			m_tInfo.fY -= _tHitPoint.fY;
			//m_fItemSpeedY = -2.f;
			break;
		case DIR_LEFT:
			m_tInfo.fX -= _tHitPoint.fX;
			m_fItemSpeedX = -2.f;
			break;
		case DIR_RIGHT:
			m_tInfo.fX += _tHitPoint.fX;
			m_fItemSpeedX = 2.f;
			break;
		default:
			break;
		}
		break;

	case OBJ_TILE:
		if (0 == dynamic_cast<CTile*>(_pObj)->Get_Option())
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

void CItem::Spown_Move()
{
	if (m_CreateTime + m_iDropTime < GetTickCount64())
	{
		Set_CollisionBoxSize(16.f, 16.f);
		Slip();
	}
	else
	{
		m_tInfo.fX += 10 * cosf(m_fAngle * PI / 180.f) * m_fTime;
		m_tInfo.fY -= 10 * sinf(m_fAngle * PI / 180.f) * m_fTime - 0.5f * 9.8f * m_fTime * m_fTime;
		m_fTime += 0.1f;
	}
}

void CItem::Slip()
{
	if (m_fItemSpeedX > 1.f)
	{
		m_tInfo.fX += m_fItemSpeedX;
		m_fItemSpeedX -= 0.1f;
	}
	else if (m_fItemSpeedX < -1.f)
	{
		m_tInfo.fX += m_fItemSpeedX;
		m_fItemSpeedX += 0.1f;
	}

	

	if (m_fItemSpeedY > 1.f)
	{
		m_tInfo.fY += m_fItemSpeedY;
		m_fItemSpeedY -= 0.1f;
	}
	else if (m_fItemSpeedY < -1.f)
	{
		m_tInfo.fY += m_fItemSpeedY;
		m_fItemSpeedY += 0.1f;
	}

		

}


