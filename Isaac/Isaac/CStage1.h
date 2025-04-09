#pragma once
#include "CScene.h"

class CStage1 : public CScene
{
public:
	CStage1();
	~CStage1();

public:
	void Initialize() override;
	void Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	

};

