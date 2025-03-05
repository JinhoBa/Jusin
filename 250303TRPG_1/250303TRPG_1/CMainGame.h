#pragma once
#include "CPlayer.h"
#include "CField.h"
#include "CStore.h"

class CMainGame
{
public:
	CMainGame();
	virtual ~CMainGame();
public:
	virtual void Initialize();
	virtual void Update();
	virtual void Release();
protected:
	CObj* m_pPlayer;
	CField* m_pField;
	CStore* m_pStore;
};

