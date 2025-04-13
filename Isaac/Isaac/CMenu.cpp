#include "pch.h"
#include "CMenu.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CUIMgr.h"
#include "CButton.h"
#include "CUIBar.h"
#include "CSoundMgr.h"

CMenu::CMenu()
{
}

CMenu::~CMenu()
{
	Release();
}

void CMenu::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/UI/MainMenu.bmp", L"MainMenu");

	CUI* pButton = new CButton;
	pButton->Initialize();

	CUIMgr::Get_Instance()->Add_UI(UI_BUTTON, pButton);
	CSoundMgr::Get_Instance()->PlayBGM(L"Danny Baranowsky - The Binding of Isaac - 01 Those Responsible.mp3", 0.3f);
}

void CMenu::Update()
{
	CUIMgr::Get_Instance()->Update();
}

void CMenu::Late_Update()
{
	CUIMgr::Get_Instance()->Late_Update();
}

void CMenu::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MainMenu");

	BitBlt(hDC,
		0,
		0,
		WINCX, WINCY,
		hMemDC,
		0, 0,
		SRCCOPY);

	CUIMgr::Get_Instance()->Render(hDC);
}

void CMenu::Release()
{
	CSoundMgr::Get_Instance()->Release();
	CUIMgr::Get_Instance()->Delete_UI(UI_BUTTON);
}

