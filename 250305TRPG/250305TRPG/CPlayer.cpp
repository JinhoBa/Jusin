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
	//아이템 할당 해제
}

void CPlayer::Render()
{
	cout << "------------------------------------" << endl;
	cout << "이름 : " << m_tInfo.sName << endl;
	cout << "체력 : " << m_tInfo.iHp << "\t공격력 : " << m_tInfo.iAttack << endl;
	cout << "보유 금액 : " << m_tInfo.iMoney << "G" << endl;
	cout << "Exp " << m_tInfo.iExp << endl;
	cout << "------------------------------------" << endl;
}

void CPlayer::Select_Job()
{
	bool bSelect(false);
	int iInput(0);

	while (!bSelect)
	{
		cout << "\t직업을 선택하세요" << '\n';
		cout << "1. 전사 2. 마법사 3. 도적 4. 종료 \n>> ";
		cin >> iInput;

		switch (iInput)
		{
		case WARRIOR:
			Set_Info("전사", 200, 10, 0, 0);
			bSelect = true;
			break;

		case MAGE:
			Set_Info("마법사", 150, 15, 0, 0);
			bSelect = true;
			break;

		case THIF:
			Set_Info("도적", 100, 20, 0, 0);
			bSelect = true;
			break;

		case END:
			cout << "게임 종료";
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
		cout << "구매 완료" << endl;
	}
	else 
		cout << "인벤토리가 가득 찼습니다." << endl;

	
		
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
	cout << "보유한 아이템" << endl;
	for (iter = vecInventory.begin(); iter != vecInventory.end(); ++iter,++i)
	{
		cout << i<<". " << (*iter)->Get_Name() << endl;
	}
	cout << "------------------------------" << endl;
}
