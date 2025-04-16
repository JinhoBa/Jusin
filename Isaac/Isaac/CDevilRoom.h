#pragma once
#include "CScene.h"

class CDevilRoom : public CScene
{
public:
	CDevilRoom();
	~CDevilRoom();

public:
	void Initialize() override;
	void Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

};

