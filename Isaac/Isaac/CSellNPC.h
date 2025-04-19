#pragma once
#include "CItem.h"
class CSellGame;
class CSellNPC : public CItem
{
public:
	CSellNPC();
	~CSellNPC();

public:
	void Set_SellGame(CSellGame* _pSellGame) { m_pSellGame = _pSellGame; }

public:
	void Initialize() override;
	void Late_Initialize() override;
	int Update() override;
	int Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Collision(CObj* _pObj, HITPOINT _tHitPoint) override;

private:
	CSellGame* m_pSellGame;
};

