#include "pch.h"
#include "CPlayer.h"
#include "Define.h"

CPlayer::CPlayer()
{
	time = 0;
	myBrush = NULL;
	m_pBullet = nullptr;
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

	m_hDC = GetDC(g_hWnd);
	time = GetTickCount64();
	if (m_pBullet == nullptr)
	{
		m_pBullet = new CBullet;
		dynamic_cast<CBullet*>(m_pBullet)->Initialize(&m_rc);
		m_pBullet->SetHDC(m_hDC);
	}
	myBrush = static_cast<HBRUSH>(CreateSolidBrush(RGB(0, 0, 0)));
}

void CPlayer::Update()
{
	
}

void CPlayer::Render()
{
	Rectangle(m_hDC, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	SelectObject(m_hDC, myBrush);
	dynamic_cast<CBullet*>(m_pBullet)->Render();
}

void CPlayer::Release()
{
	Safe_Delete(m_pBullet);
	DeleteObject(myBrush);
	ReleaseDC(g_hWnd, m_hDC);
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

void CPlayer::Jump()
{
	//
}

void CPlayer::Shoot()
{
	dynamic_cast<CBullet*>(m_pBullet)->Add_Bullet();
}
