#pragma once
#include "CScene.h"

class CTreasureRoom : public CScene
{
public:
	CTreasureRoom();
	~CTreasureRoom();

public:
	void Initialize() override;

	void Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

private:
	bool m_bFirst;
	ULONGLONG m_dwTime;
};

