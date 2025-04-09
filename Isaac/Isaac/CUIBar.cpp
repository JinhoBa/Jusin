#include "pch.h"
#include "CUIBar.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"

CUIBar::CUIBar() : m_pPlayer(nullptr), m_pCoin(L""), m_pBomb(L""), m_pKey(L""), m_pHp(L"")
{
	ZeroMemory(&m_tItemInfo, sizeof(ITEMINFO));
}

CUIBar::~CUIBar()
{
    Release();
}

void CUIBar::Initialize()
{
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_tItemInfo = dynamic_cast<CPlayer*>(m_pPlayer)->Get_ItemInfo();
	
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/UI/UI.bmp", L"UIBar");
}

void CUIBar::Late_Initialize()
{
}

int CUIBar::Update()
{
    return NOEVENT;
}

int CUIBar::Late_Update()
{
	wsprintf(m_pCoin, L"%d", m_tItemInfo->iCoin);
	wsprintf(m_pBomb, L"%d", m_tItemInfo->iBomb);
	wsprintf(m_pKey, L"%d", m_tItemInfo->iKey);
	wsprintf(m_pHp, L"%d", (int)(m_pPlayer->Get_Stat()->fHp));
    return NOEVENT;
}

void CUIBar::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"UIBar");
	
	BitBlt(hDC,
		0,
		0,
		WINCX, 100,
		hMemDC,
		0, 0,
		SRCCOPY);
	TextOut(hDC, 430, 13, m_pCoin, lstrlen(m_pCoin));
	TextOut(hDC, 430, 45, m_pBomb, lstrlen(m_pBomb));
	TextOut(hDC, 430, 76, m_pKey, lstrlen(m_pKey));
	TextOut(hDC, 600, 26, m_pHp, lstrlen(m_pHp));
}

void CUIBar::Release()
{
}
