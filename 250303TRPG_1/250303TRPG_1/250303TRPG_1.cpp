#include "pch.h"
#include "CMainGame.h"

int main()
{
	CMainGame MainGame;

	MainGame.Initialize();
	MainGame.Update();
	MainGame.Release();

	return 0;
}
