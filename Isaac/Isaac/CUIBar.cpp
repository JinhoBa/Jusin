#include "pch.h"
#include "CUIBar.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CUIMgr.h"
#include "CMiniMap.h"

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
	
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/UI/UIBar.bmp", L"UIBar");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/UI/Heart_UI.bmp", L"Heart_UI");

	CUIMgr::Get_Instance()->Add_UI(UI_MINIMAP, CAbstractFactory<CMiniMap>::Create_UI());
    
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
	//wsprintf(m_pHp, L"%d", (int)(m_pPlayer->Get_Stat()->fHp));

	int iHp = (int)(m_pPlayer->Get_Stat()->fHp);
	int iMaxHp = (int)(m_pPlayer->Get_Stat()->fMaxHp);
	int iSoulHp = (int)dynamic_cast<CPlayer*>(m_pPlayer)->Get_SoulHp();

	m_vecHp.clear();
	while (iHp > 0)
	{
		if (1 < iHp)
		{
			m_vecHp.push_back(0);
			iHp -= 2;
		}
		else
		{
			m_vecHp.push_back(1);
			iHp -= 1;
		}
	} 

	for (int i = 0; 0 < (iMaxHp / 2) - m_vecHp.size();++i)
	{
		m_vecHp.push_back(2);
	}

	while (iSoulHp > 0)
	{
		if (1 < iSoulHp)
		{
			m_vecHp.push_back(3);
			iSoulHp -= 2;
		}
		else
		{
			m_vecHp.push_back(4);
			iSoulHp -= 1;
		}
	}


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

	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Heart_UI");
	for (size_t i = 0; i < m_vecHp.size(); i++)
	{
		if(m_vecHp[i] < 3)
		{
			BitBlt(hDC,
				600 + 40 * ((int)i % 4),
				30 + 30 * ((int)i / 4),
				40, 40,
				hMemDC,
				40 * m_vecHp[i], 0,
				SRCCOPY);
		}
		else
		{
			BitBlt(hDC,
				600 + 40 * ((int)i % 4),
				30 + 30 * ((int)i / 4),
				40, 40,
				hMemDC,
				40 * (m_vecHp[i] - 3), 40,
				SRCCOPY);
		}
	}
	HFONT hFont, OldFont;

	hFont = CreateFont(
		18, 0, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE,
		HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS,
		TEXT("±¼¸²")
	);
	OldFont = (HFONT)SelectObject(hDC, hFont);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 430, 13, m_pCoin, lstrlen(m_pCoin));
	TextOut(hDC, 430, 45, m_pBomb, lstrlen(m_pBomb));
	TextOut(hDC, 430, 76, m_pKey, lstrlen(m_pKey));
	TextOut(hDC, 600, 26, m_pHp, lstrlen(m_pHp));

	SelectObject(hDC, OldFont);
	DeleteObject(hFont);
}

void CUIBar::Release()
{
}
