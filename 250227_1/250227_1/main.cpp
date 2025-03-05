#include <iostream>

using namespace std;
template<typename T1, typename T2>
T1 Damage(T1 Attack, T2 Def)
{
	return Attack - Def;
}

class CObj
{
public:
	CObj(int _iAttack, int _iDef) { iAttack = _iAttack; iDef = _iDef; }
	~CObj() {}
	int iAttack;
	int iDef;
};
int main()
{
	CObj player(5, 1);
	CObj monster(3, 2);
	Damage(player.iAttack, monster.iDef);
	
}