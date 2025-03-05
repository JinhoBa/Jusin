#pragma once
#include "pch.h"

#define SYSTEM_CLOSE system("cls");
#define SYSTEM_PAUSE system("pause");
#define ENTER_AGAIN cout << "�ٽ� �Է��ϼ���" << '\n';

typedef struct tagInfo
{
	string sName;
	int iHp;
	int iMaxHp;
	int iAttack;
	int iMoney;
	int iExp;
}INFO;

template<typename T>
void Safe_Delete(T& p)
{
	if (p) { delete p; p = nullptr; }
};
