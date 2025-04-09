#pragma once
#include "CUI.h"

class CButton : public CUI
{
public:
	CButton();
	~CButton();

public:
	// CUI을(를) 통해 상속됨
	void Initialize() override;

	void Late_Initialize() override;

	int Update() override;

	int Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

};

