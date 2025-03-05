#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
	vecInventory.reserve(5);
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
}

void CPlayer::Update()
{
}

void CPlayer::Release()
{
	//������ �Ҵ� ����
}

void CPlayer::Render()
{
	cout << "------------------------------------" << endl;
	cout << "�̸� : " << m_tInfo.sName << endl;
	cout << "ü�� : " << m_tInfo.iHp << "\t���ݷ� : " << m_tInfo.iAttack << endl;
	cout << "���� �ݾ� : " << m_tInfo.iMoney << "G" << endl;
	cout << "Exp " << m_tInfo.iExp << endl;
	cout << "------------------------------------" << endl;
}

void CPlayer::Select_Job()
{
	bool bSelect(false);
	int iInput(0);

	while (!bSelect)
	{
		cout << "\t������ �����ϼ���" << '\n';
		cout << "1. ���� 2. ������ 3. ���� 4. ���� \n>> ";
		cin >> iInput;

		switch (iInput)
		{
		case WARRIOR:
			Set_Info("����", 200, 10, 0, 0);
			bSelect = true;
			break;

		case MAGE:
			Set_Info("������", 150, 15, 0, 0);
			bSelect = true;
			break;

		case THIF:
			Set_Info("����", 100, 20, 0, 0);
			bSelect = true;
			break;

		case END:
			cout << "���� ����";
			SYSTEM_CLOSE;
			return;

		default:
			ENTER_AGAIN;
			break;
		}
	}
}

void CPlayer::Get_Reward(CObj& rMonster)
{
	m_tInfo.iMoney += rMonster.Get_Gold();
	m_tInfo.iExp += rMonster.Get_Exp();
}

void CPlayer::Buy_Item(CItem& rItem)
{
	if (5 > vecInventory.size())
	{
		vecInventory.push_back(&rItem);
		m_tInfo.iMoney -= rItem.Get_Price();
		cout << "���� �Ϸ�" << endl;
	}
	else 
		cout << "�κ��丮�� ���� á���ϴ�." << endl;

	
		
	SYSTEM_PAUSE;
	
	
}

void CPlayer::Sell_Item(CItem& rItem)
{
}

void CPlayer::Render_Inventory()
{
	int i = 1;
	vector<CItem*>::iterator iter;
	cout << "------------------------------" << endl;
	cout << "������ ������" << endl;
	for (iter = vecInventory.begin(); iter != vecInventory.end(); ++iter,++i)
	{
		cout << i<<". " << (*iter)->Get_Name() << endl;
	}
	cout << "------------------------------" << endl;
}
