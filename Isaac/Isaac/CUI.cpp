#include "pch.h"
#include "CUI.h"

CUI::CUI() : m_iDrawID(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CUI::~CUI()
{
}
