#include "pch.h"
#include "CSellGame.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CImage.h"
#include "CTools.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CSoundMgr.h"

CSellGame::CSellGame() 
	: m_fX(0.f), m_fY(0.f), m_fRadius(0.f), m_fAngle(0.f), m_eCurState(STATE_END), m_ePreState(STATE_END), m_bShuffle(false), 
	m_iCount(0), m_fShuffleSpeed(0.f), m_iIndex1(0), m_iIndex2(0), m_fShowSpeed(1.f), m_bEnd(false), m_iMainCusorIndex(0)
{
}

CSellGame::~CSellGame()
{
	Release();
}



void CSellGame::Initialize()
{
	m_eCurState = IDLE;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/UI/SellBack.bmp", L"SellBack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/SellGame/SellerMotion.bmp", L"SellerMotion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/SellGame/Skeleton.bmp", L"Skeleton");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/SellGame/CoinImg.bmp", L"CoinImg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/SellGame/PooImg.bmp", L"PooImg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/SellGame/Cursor.bmp", L"Cursor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/UI/MainCursor.bmp", L"MainCursor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/UI/ResultUI.bmp", L"ResultUI");


	m_vecResult.push_back(false);
	m_vecResult.push_back(false);
	m_vecResult.push_back(true);

	m_pSeller = new CImage;
	m_pSeller->Set_Info(400.f, 210.f, 32.f, 32.f);
	m_pSeller->Set_FrameKey(L"SellerMotion");

	m_pSkeleton1 = new CImage;
	m_pSkeleton1->Set_Info(340.f, 340.f,32.f,32.f);
	m_pSkeleton1->Set_FrameKey(L"Skeleton");

	m_pSkeleton2 = new CImage;
	m_pSkeleton2->Set_Info(400.f, 340.f, 32.f, 32.f);
	m_pSkeleton2->Set_FrameKey(L"Skeleton");

	m_pSkeleton3 = new CImage;
	m_pSkeleton3->Set_Info(460.f, 340.f, 32.f, 32.f);
	m_pSkeleton3->Set_FrameKey(L"Skeleton");
	m_pSkeleton3->Set_bCoin();

	m_pResult1 = new CImage;
	m_pResult1->Set_Info(m_pSkeleton3->Get_Info()->fX, m_pSkeleton3->Get_Info()->fY, 32.f, 32.f);
	m_pResult1->Set_FrameKey(L"CoinImg");
	
	m_pCursor = new CImage;
	m_pCursor->Set_Info(0.f, 0.f, 16.f, 16.f);
	m_pCursor->Set_FrameKey(L"Cursor");

	m_pMainCursor = new CImage;
	m_pMainCursor->Set_Info(0.f, 0.f, 24.f, 24.f);
	m_pMainCursor->Set_FrameKey(L"MainCursor");

	m_pResultUI = new CImage;
	m_pResultUI->Set_Info(360.f, 220.f, 100.f, 40.f);
	m_pResultUI->Set_FrameKey(L"ResultUI");


	m_ImageList.push_back(m_pSeller);
	m_ImageList.push_back(m_pSkeleton1);
	m_ImageList.push_back(m_pSkeleton2);
	m_ImageList.push_back(m_pSkeleton3);

	m_vecSkeletons.push_back(m_pSkeleton1->Get_Info());
	m_vecSkeletons.push_back(m_pSkeleton2->Get_Info());
	m_vecSkeletons.push_back(m_pSkeleton3->Get_Info());

	Set_Random_Index();

	m_iCount = 10;
	m_bEnd = false;

	m_iSoundChennel = CSoundMgr::Get_Instance()->Get_AvailableChennel();
	m_iCursorSound = CSoundMgr::Get_Instance()->Get_AvailableChennel();
}

void CSellGame::Late_Initialize()
{
}

int CSellGame::Update()
{
	if (m_bEnd)
	{
		Release();
		CSoundMgr::Get_Instance()->StopAll();
		return DEAD;
	}

	for (auto pImg : m_ImageList)
	{
		pImg->Update();
	}
	
	m_pResult1->Update();

	m_pCursor->Update();
	m_pMainCursor->Update();
	m_pResultUI->Update();
	

	return NOEVENT;
}

void CSellGame::Late_Update()
{
	
	Key_Input();

	switch (m_eCurState)
	{
	case CSellGame::IDLE:
		break;
	case CSellGame::START:
		Show_Item();
		break;
	case CSellGame::SHUFFLE:
		if (m_iCount > 0)
		{
			Shuffle(m_vecSkeletons[m_iIndex1], m_vecSkeletons[m_iIndex2]);
		}
		else
			m_eCurState = SELLECT;
		break;
	case CSellGame::SELLECT:
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
			Check_Result();
		break;

	case CSellGame::RESULT:
		Show_Item();
		break;
	case CSellGame::STATE_END:
		break;
	default:
		break;
	}
	
	Change_State();

	if (CKeyMgr::Get_Instance()->Key_Down('V'))
	{
		m_eCurState = START;
		m_iCount = 10;
		m_fShuffleSpeed = 15.f;
		m_fShowSpeed = 1.f;
	}
	
	m_pResult1->Late_Update();
	m_pCursor->Late_Update();
	m_pMainCursor->Late_Update();
	m_pResultUI->Late_Update();

	m_pCursor->Set_Pos(340.f + (float)m_iCusorIndex * 60.f, 340.f);
	m_pMainCursor->Set_Pos(250.f + (float)m_iMainCusorIndex * 190.f, 465.f);
	

	for (auto pImg : m_ImageList)
	{
		pImg->Late_Update();
	}
}

void CSellGame::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SellBack");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		150,		// 복사 받을 위치 좌표 left
		150,					// 복사 받을 위치 좌표 top
		650,				// 복사 받을 가로 사이즈
		400,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		0,
		0,							// 복사할 이미지의 left, top
		512,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		256,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));

	if (START == m_eCurState|| RESULT == m_eCurState)
		m_pResult1->Render(hDC);
	
	for (auto pImg : m_ImageList)
	{
		pImg->Render(hDC);
	}

	if (SELLECT == m_eCurState)
		m_pCursor->Render(hDC);

	if (IDLE == m_eCurState)
	{
		m_pMainCursor->Render(hDC);
	}

	if (RESULT == m_eCurState)
		m_pResultUI->Render(hDC);
	
}

void CSellGame::Release()
{
	for_each(m_ImageList.begin(), m_ImageList.end(), Safe_Delete<CImage*>);
	m_ImageList.clear();
	Safe_Delete<CImage*>(m_pResult1);
	Safe_Delete<CImage*>(m_pCursor);
	Safe_Delete<CImage*>(m_pMainCursor);
	Safe_Delete<CImage*>(m_pResultUI);
	m_vecSkeletons.clear();
	m_vecResult.clear();
	CSoundMgr::Get_Instance()->PlayBGM(L"StoreRoomBGM.mp3", 0.3f);
}

void CSellGame::Shuffle(INFO* Tmp, INFO* Src)
{
	
	if (!m_bShuffle)
	{
		m_fTmpX = Tmp->fX;
		m_fSrcX = Src->fX;
		m_fRadius = fabsf(Tmp->fX - Src->fX)* 0.5f;
		m_fX = (Tmp->fX + Src->fX) * 0.5f;
		m_fY = Tmp->fY;
		m_fAngle = 0.f;
		m_bShuffle = true;
	}

	if(m_fTmpX < m_fSrcX)
	{
		Tmp->fX = m_fX - m_fRadius * cosf(m_fAngle * PI / 180.f);
		Src->fX = m_fX + m_fRadius * cosf(m_fAngle * PI / 180.f);
	}
	else
	{
		Tmp->fX = m_fX + m_fRadius * cosf(m_fAngle * PI / 180.f);
		Src->fX = m_fX - m_fRadius * cosf(m_fAngle * PI / 180.f);
	}
	Tmp->fY = m_fY - m_fRadius * sinf(m_fAngle * PI / 180.f);
	Src->fY = m_fY - m_fRadius * sinf(m_fAngle * PI / 180.f);

	m_fAngle += m_fShuffleSpeed;

	if (m_fAngle > 180.f)
	{
		m_bShuffle = false;
		--m_iCount;
		Set_Random_Index();
	}
}

void CSellGame::Change_State()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CSellGame::IDLE:
			CSoundMgr::Get_Instance()->StopSound(m_iSoundChennel);
			break;
		case CSellGame::START:
			m_pResult1->Set_Info(m_pSkeleton3->Get_Info()->fX, m_pSkeleton3->Get_Info()->fY, 32.f, 32.f);
			break;
		case CSellGame::SHUFFLE:
			m_pSeller->Set_FrameStart(1);
			CSoundMgr::Get_Instance()->PlayLoop(L"ShellGame.mp3", m_iSoundChennel, 0.5f);
			break;
		case CSellGame::SELLECT:
			CSoundMgr::Get_Instance()->StopSound(m_iSoundChennel);
			break;
		case CSellGame::STATE_END:
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CSellGame::Set_Random_Index()
{
	m_iIndex1 = CTools::Get_RandomNumber(0, 2);

	while (true)
	{
		m_iIndex2 = CTools::Get_RandomNumber(0, 2);
		if (m_iIndex2 != m_iIndex1)
		{
			if (m_iIndex1 > m_iIndex2)
				swap(m_iIndex1, m_iIndex2);

			break;
		}
	}
}

void CSellGame::Show_Item()
{

	for (auto pImg : m_vecSkeletons)
	{
		pImg->fY -= m_fShowSpeed;
	}

	if (m_vecSkeletons.front()->fY <= 280.f)
		m_fShowSpeed *= -1.f;

	if (m_vecSkeletons.front()->fY >= 340.f)
	{
		for (auto pImg : m_vecSkeletons)
		{
			pImg->fY = 340.f;
		}
		if (START == m_eCurState)
			m_eCurState = SHUFFLE;
		else if (RESULT == m_eCurState)
			m_eCurState = IDLE;
	}


}

void CSellGame::Check_Result()
{
	if (340 + 60 * m_iCusorIndex == m_pSkeleton3->Get_Info()->fX)
	{
		m_pSeller->Set_FrameStart(3);
		m_pResultUI->Set_FrameStart(0);
		dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Coin(2);
		CSoundMgr::Get_Instance()->PlaySound(L"ThumbsUp.mp3", m_iSoundChennel, 0.5f);
	}
	else
	{
		m_pSeller->Set_FrameStart(2);
		m_pResultUI->Set_FrameStart(1);
		dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Coin(-1);
		CSoundMgr::Get_Instance()->PlaySound(L"ThumbsDown.mp3", m_iSoundChennel, 0.5f);
	}
	m_pResult1->Set_Info(m_pSkeleton3->Get_Info()->fX, m_pSkeleton3->Get_Info()->fY, 32.f, 32.f);
	m_eCurState = RESULT;
	
	m_fShowSpeed = 1.f;
	m_dwTime = GetTickCount64();
}

void CSellGame::Key_Input()
{
	switch (m_eCurState)
	{
	case IDLE:
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))
		{
			++m_iMainCusorIndex;
			CursorSound();
			if (1 < m_iMainCusorIndex)
				m_iMainCusorIndex = 0;
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))
		{
			--m_iMainCusorIndex;
			CursorSound();
			if (0 > m_iMainCusorIndex)
				m_iMainCusorIndex = 1;
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
		{
			if (0 == m_iMainCusorIndex)
			{
				if(0 < dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_ItemInfo()->iCoin)
				{
					m_eCurState = START;
					m_iCount = 10;
					m_fShuffleSpeed = 10.f;
					m_fShowSpeed = 1.f;
				}
				else
				{
					// 돈 부족 출력
				}
			}
			else
				m_bEnd = true;
		}
		break;

	case SELLECT:
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))
		{
			++m_iCusorIndex;
			CursorSound();
			if (2 < m_iCusorIndex)
				m_iCusorIndex = 0;
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))
		{
			--m_iCusorIndex;
			CursorSound();
			if (0 > m_iCusorIndex)
				m_iCusorIndex = 2;
		}
		break;

	defualt:
		break;
	}
		
	

}

void CSellGame::CursorSound()
{
	CSoundMgr::Get_Instance()->StopSound(m_iCursorSound);
	CSoundMgr::Get_Instance()->PlaySound(L"Cursor.mp3", m_iCursorSound, 1.f);
}
