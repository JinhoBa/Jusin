#pragma once
#include "CScene.h"

class CStoreRoom : public CScene
{
public:
	CStoreRoom();
	~CStoreRoom();

public:
	void Initialize() override;
	void Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

};

