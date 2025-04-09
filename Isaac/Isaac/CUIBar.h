#pragma once
#include "CUI.h"

class CObj;

class CUIBar : public CUI
{
public:
	CUIBar();
	~CUIBar();

	// CUI을(를) 통해 상속됨
	void Initialize() override;
	void Late_Initialize() override;
	int Update() override;
	int Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	CObj*		m_pPlayer;
	ITEMINFO*	m_tItemInfo;
	TCHAR		m_pCoin[16];
	TCHAR		m_pBomb[16];
	TCHAR		m_pKey[16];
	TCHAR		m_pHp[16];
};

