#include "pch.h"
#include "CObj.h"
#include "CSoundMgr.h"

CObj::CObj() 
	: m_fSpeed(0.f), m_fAngle(0.f), m_bDead(false), m_pTarget(nullptr), m_pFrameKey(nullptr), m_eID(OBJ_END), m_iSoundChennel(0)
{

	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	ZeroMemory(&m_tCollisionBox, sizeof(INFO));
	ZeroMemory(&m_tStat, sizeof(STAT));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left = long(m_tInfo.fX - m_tInfo.fCX / 2.f);
	m_tRect.top = long(m_tInfo.fY - m_tInfo.fCY / 2.f);
	m_tRect.right = long(m_tInfo.fX + m_tInfo.fCX / 2.f);
	m_tRect.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2.f);

}

void CObj::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwFrameSpeed < GetTickCount64())
	{
		m_tFrame.iStart++;
		m_tFrame.dwTime = GetTickCount64();

		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iStart = 0;
	}
}



void CObj::Collision_Render(HDC hDC)
{
	Rectangle(hDC,
		long(m_tCollisionBox.fX - m_tCollisionBox.fCX / 2.f),
		long(m_tCollisionBox.fY - m_tCollisionBox.fCY / 2.f),
		long(m_tCollisionBox.fX + m_tCollisionBox.fCX / 2.f),
		long(m_tCollisionBox.fY + m_tCollisionBox.fCY / 2.f)
	);
}

void CObj::Set_Sound(const TCHAR* _pFileKey, float _fVolume)
{
	m_iSoundChennel = CSoundMgr::Get_Instance()->Get_AvailableChennel();	
	CSoundMgr::Get_Instance()->PlaySound(_pFileKey, m_iSoundChennel, 1.f);
}
