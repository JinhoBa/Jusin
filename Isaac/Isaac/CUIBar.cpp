#include "pch.h"
#include "CUIBar.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CUIMgr.h"
#include "CMiniMap.h"
#include "CImage.h"
#include "CNumber.h"

CUIBar::CUIBar() : m_pPlayer(nullptr), m_pCoinValue(nullptr), m_pBombValue(nullptr), m_pKeyValue(nullptr)
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

	CUIMgr::Get_Instance()->Add_UI(UI_MINIMAP, CAbstractFactory<CMiniMap>::Create_UI(0.f, 0.f, 0.f, 0.f));
    
	m_pCoinValue = CAbstractFactory<CNumber>::Create_UI(432.f, 17.f, 16.f, 16.f);
	m_pBombValue = CAbstractFactory<CNumber>::Create_UI(432.f, 49.f, 16.f, 16.f);
	m_pKeyValue = CAbstractFactory<CNumber>::Create_UI(432.f, 81.f, 16.f, 16.f);
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
	dynamic_cast<CNumber*>(m_pCoinValue)->Set_Frame(m_tItemInfo->iCoin % 10, m_tItemInfo->iCoin / 10);
	dynamic_cast<CNumber*>(m_pBombValue)->Set_Frame(m_tItemInfo->iBomb % 10, m_tItemInfo->iBomb / 10);
	dynamic_cast<CNumber*>(m_pKeyValue)->Set_Frame(m_tItemInfo->iKey % 10, m_tItemInfo->iKey / 10);

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

	m_pCoinValue->Render(hDC);
	m_pBombValue->Render(hDC);
	m_pKeyValue->Render(hDC);
	


}

void CUIBar::Release()
{
}
