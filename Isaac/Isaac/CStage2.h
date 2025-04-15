#pragma once
#include "CScene.h"

class CStage2 : public CScene
{
public:
	CStage2();
	~CStage2();

public:
	void Initialize() override;
	void Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

