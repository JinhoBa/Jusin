#pragma once
#include "CUI.h"

class CMiniMap : public CUI
{
public:
	CMiniMap();
	~CMiniMap();

public:
	void Initialize() override;
	void Late_Initialize() override;
	int Update() override;
	int Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	vector<int> m_vecSceneState;
};

