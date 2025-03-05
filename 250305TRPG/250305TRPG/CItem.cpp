#include "pch.h"
#include "CItem.h"

CItem::CItem()
{
	sName = "";
	iExtraHp = 0;
	iExtraAttack = 0;
	iPrice = 0;
}

CItem::~CItem()
{
}

void CItem::Set_Item(string _sName, int _iExtraHp, int _iExtraAttack, int _iPrice)
{
	sName = _sName;
	iExtraHp = _iExtraHp;
	iExtraAttack = _iExtraAttack;
	iPrice = _iPrice;
}
