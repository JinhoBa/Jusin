#pragma once
#include "CUI.h"

class CObj;
class CImage;
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
	vector<int> m_vecHp;

	ITEMINFO*	m_tItemInfo;

	CUI* m_pCoinValue;
	CUI* m_pBombValue;
	CUI* m_pKeyValue;
};

