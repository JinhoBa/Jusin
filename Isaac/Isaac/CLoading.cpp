#include "pch.h"
#include "CLoading.h"
#include "CBmpMgr.h"

CLoading::CLoading() : m_iX(0)
{
}

CLoading::~CLoading()
{
	Release();
}

void CLoading::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Room/BaseMap.bmp", L"Tutorial");
}

void CLoading::Update()
{
}

void CLoading::Late_Update()
{
	m_iX+= 50;
}

void CLoading::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tutorial");

	BitBlt(hDC,
		m_iX,
		0,
		800, 600,
		hMemDC,
		0, 0,
		SRCCOPY);
}

void CLoading::Release()
{
}
