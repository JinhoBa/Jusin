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
		cout << "1. ���� 2. ���� �� 3. ���� 4. ���ư��� : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			cout << "�����۸� :\t ���� " << endl;
			cout << "���� :\t 50G" << endl;
			cout << "ȿ�� :\t ü�� 50�� ȸ���մϴ�." << endl;
			SYSTEM_PAUSE;
			break;
		case 2:
			cout << "�����۸� :\t ���� �� " << endl;
			cout << "���� :\t 100G" << endl;
			cout << "ȿ�� :\t ���ݷ� +5" << endl;
			SYSTEM_PAUSE;
			break;
		case 3:
			cout << "�����۸� :\t ���� " << endl;
			cout << "���� :\t 150G" << endl;
			cout << "ȿ�� :\t �ִ� ü�� +50" << endl;
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
