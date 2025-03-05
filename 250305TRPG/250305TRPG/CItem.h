#pragma once
class CItem
{
public:
	CItem();
	~CItem();
public:
	void Set_Item(string _sName, int _iExtraHp, int _iExtraAttack, int _iPrice);
	const int Get_Price() { return iPrice; }
	const string Get_Name() { return sName; }
private:
	string sName;
	int iExtraHp;
	int iExtraAttack;
	int iPrice;
};

