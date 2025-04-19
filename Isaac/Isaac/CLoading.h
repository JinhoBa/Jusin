#pragma once
#include "CScene.h"

class CLoading : public CScene
{
public:
	CLoading();
	~CLoading();

private:
	void Initialize() override;
	void Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	int m_iX;

};

