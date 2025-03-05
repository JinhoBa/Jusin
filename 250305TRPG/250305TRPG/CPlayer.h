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
		END,
		HIDEN = 999
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
	void Sell_Item(string _Name);
	void Equip_Item(string _Name);
	void Render_Inventory();
	string Get_Equipment() { return m_pEquipment->Get_Name(); }
private:
	vector<CItem*> vecInventory;
	CItem* m_pEquipment;
};

