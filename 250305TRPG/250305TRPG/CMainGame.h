#pragma once
#include "CPlayer.h"
#include "CField.h"
#include "CStore.h"
#include "CInventory.h"

class CMainGame
{
	enum MENUINDEX
	{
		FIELD = 1,
		STORE,
		INVENTORY,
		END
	};
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize();
	void Update();
	void Release();
private:
	CObj* m_pPlayer;
	CMenu* m_pMenu;
};

