#include "pch.h"
#include "CImage.h"
#include "CBmpMgr.h"

CImage::CImage() : m_pFrameKey(L""), m_bCoin(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CImage::~CImage()
{
	Release();
}

void CImage::Initialize()
{
}

void CImage::Late_Initialize()
{
}

int CImage::Update()
{
	Update_Rect();

	return NOEVENT;
}

void CImage::Late_Update()
{
	if (!lstrcmp(m_pFrameKey, L"Cursor"))
	{
		m_iCX = 32;
		m_iCY = 32;
	}
	else if (!lstrcmp(m_pFrameKey, L"MainCursor"))
	{
		m_iCX = 24;
		m_iCY = 24;
	}
	else if (!lstrcmp(m_pFrameKey, L"SellerMotion"))
	{
		m_iCX = 64;
		m_iCY = 64;
	}
	else
	{
		m_iCX = 50;
		m_iCY = 50;
	}
}

void CImage::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		m_iCX,				// 복사 받을 가로 사이즈
		m_iCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		0,							// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CImage::Release()
{
}

void CImage::Update_Rect()
{
	m_tRect.left = long(m_tInfo.fX - m_tInfo.fCX / 2.f);
	m_tRect.top = long(m_tInfo.fY - m_tInfo.fCY / 2.f);
	m_tRect.right = long(m_tInfo.fX + m_tInfo.fCX / 2.f);
	m_tRect.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2.f);
}
