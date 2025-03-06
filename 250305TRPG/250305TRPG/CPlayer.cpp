#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
	vecInventory.reserve(5);
	m_pEquipment =nullptr;
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
	vector<CItem*>::iterator iter;

	for (iter = vecInventory.begin(); iter != vecInventory.end();++iter)
	{
		Safe_Delete<CItem*>(*iter);
	}
	Safe_Delete<CItem*>(m_pEquipment);
}

void CPlayer::Render()
{
	int iGauge = m_tInfo.iExp % 10;
	int iLevel(1);
	if (m_tInfo.iExp > 9)
		iLevel += m_tInfo.iExp / 10;

	cout << "\t\tINFO" << endl;
	cout << "------------------------------------" << endl;
	cout << "이름 : " << m_tInfo.sName << endl;
	cout << "Level : " << iLevel << endl;
	cout << "체력 : " << m_tInfo.iHp << "\t공격력 : " << m_tInfo.iAttack << endl;
	cout << "보유 금액 : " << m_tInfo.iMoney << "G" << endl;
	cout << "Exp ";
	for (int i = 0; i < 10; i++)
	{
		if (iGauge > i)
			cout << "■";
		else
			cout << "□";
	}
	cout << "\n------------------------------------" << endl;
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

		case HIDEN:
			Set_Info("???", 150, 20, 9999, 0);
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

void CPlayer::Set_Item()
{
	m_tInfo.iMaxHp += m_pEquipment->Get_ExtraHp();
	m_tInfo.iAttack += m_pEquipment->Get_ExtraAttack();
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

void CPlayer::Sell_Item(string _Name)
{
	if (vecInventory.empty())
	{
		cout << "아이템이 존재하지 않습니다." << endl;
		SYSTEM_PAUSE;
		return;
	}

	vector<CItem*>::iterator iter;

	for (iter = vecInventory.begin(); iter != vecInventory.end(); )
	{
		if (_Name == (*iter)->Get_Name())
		{
			cout << (*iter)->Get_Name() << " 판매 완료" << endl;
			m_tInfo.iMoney += (*iter)->Get_Price();
			Safe_Delete(*iter);
			iter = vecInventory.erase(iter);
			SYSTEM_PAUSE;
			return;
		}
		else
			++iter;
	}

	
	cout << "아이템이 존재하지 않습니다." << endl;
	SYSTEM_PAUSE;
	
}

void CPlayer::Equip_Item(string _Name)
{
	vector<CItem*>::iterator iter;

	for (iter = vecInventory.begin(); iter != vecInventory.end(); )
	{
		if (_Name == (*iter)->Get_Name())
		{
			m_pEquipment = *iter;
			iter = vecInventory.erase(iter);
			Set_Item();
			SYSTEM_PAUSE;
			return;
		}
		else
			++iter;
	}
		
}

void CPlayer::Unequip_Item()
{
	if (5 == vecInventory.size())
	{
		cout << "인벤토리가 가득 찼습니다." << endl;
		SYSTEM_PAUSE;
		return;
	}
	m_tInfo.iMaxHp -= m_pEquipment->Get_ExtraHp();
	m_tInfo.iAttack -= m_pEquipment->Get_ExtraAttack();
	vecInventory.push_back(m_pEquipment);
	m_pEquipment = nullptr;
	
}

void CPlayer::Render_Inventory()
{
	int i = 1;
	vector<CItem*>::iterator iter;
	cout << "------------------------------------" << endl;
	cout << "\t\t보유한 아이템" << endl;
	for (iter = vecInventory.begin(); iter != vecInventory.end(); ++iter,++i)
	{
		cout << "● " << (*iter)->Get_Name() << endl;
	}
	cout << "------------------------------------" << endl;
}

string CPlayer::Get_Equipment()
{
	if (nullptr != m_pEquipment)
		return m_pEquipment->Get_Name();
	else
		return "없음";
}
