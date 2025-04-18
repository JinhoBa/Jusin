#pragma once
#include "CScene.h"
class CSellGame;

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

public:
	void Set_Start() { m_bStart = true; }
	void Set_End() { m_bStart = false; }

private:
	bool m_bStart;
	CSellGame* pSellGame;
};

