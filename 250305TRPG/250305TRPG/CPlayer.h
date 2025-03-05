#pragma once
#include "CObj.h"
#include "CItem.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
	enum JOBINDEX
	{
		WARRIOR = 1,
		MAGE,
		THIF,
		END
	};
public:
	void Initialize();
	void Update();
	void Release();
public:
	virtual void Render();
	void Select_Job();
	const void Set_Hp() { m_tInfo.iHp = m_tInfo.iMaxHp; }
	void Get_Reward(CObj& rMonster);
	void Buy_Item(CItem& rItem);
	void Sell_Item(CItem& rItem);
	void Render_Inventory();
private:
	vector<CItem*> vecInventory;
};

