#include "pch.h"
#include "CPlayer.h"
#include "Define.h"

CPlayer::CPlayer()
{
	listBullet = {};
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
	m_rc.left = 395;
	m_rc.top = 480;
	m_rc.right = 405;
	m_rc.bottom = 500;
	time = GetTickCount64();
}

void CPlayer::Update()
{
	
}

void CPlayer::Render()
{
	
	Rectangle(m_hDC, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	for (auto& bullet : listBullet)
	{
		
		if (time + 1000 < GetTickCount64())
			InvalidateRect(g_hWnd, &preBullet, true);
		Ellipse(m_hDC, bullet.left, bullet.top, bullet.right, bullet.bottom);
		preBullet = bullet;
		bullet.left += 20;
		bullet.right += 20;
	}
}

void CPlayer::Release()
{

}

void CPlayer::Move_Right()
{
	InvalidateRect(g_hWnd, &m_rc, true);
	m_rc.left += 10;
	m_rc.right += 10;
}

void CPlayer::Move_Left()
{
	InvalidateRect(g_hWnd, &m_rc, true);
	m_rc.left -= 10;
	m_rc.right -= 10;
}

void CPlayer::Shoot()
{
	listBullet.push_back(m_rc);
}
