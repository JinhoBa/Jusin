#include "pch.h"
#include "CStore.h"

CStore::CStore()
{
	m_pPlayer = nullptr;
}

CStore::~CStore()
{
}

void CStore::Initialize(CObj& _rPlayer)
{
	m_pPlayer = &_rPlayer;
}

void CStore::Update()
{
	int iInput(0);

	while (true)
	{
		SYSTEM_CLOSE;
		dynamic_cast<CPlayer*>(m_pPlayer)->Render();
		cout << "1. 포션 2. 낡은 검 3. 갑옷 4. 돌아가기 : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			cout << "아이템명 :\t 포션 " << endl;
			cout << "가격 :\t 50G" << endl;
			cout << "효과 :\t 체력 50을 회복합니다." << endl;
			SYSTEM_PAUSE;
			break;
		case 2:
			cout << "아이템명 :\t 낡은 검 " << endl;
			cout << "가격 :\t 100G" << endl;
			cout << "효과 :\t 공격력 +5" << endl;
			SYSTEM_PAUSE;
			break;
		case 3:
			cout << "아이템명 :\t 갑옷 " << endl;
			cout << "가격 :\t 150G" << endl;
			cout << "효과 :\t 최대 체력 +50" << endl;
			SYSTEM_PAUSE;
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}

void CStore::Release()
{
}
