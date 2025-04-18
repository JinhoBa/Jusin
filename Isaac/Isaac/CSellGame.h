#pragma once
#include "Define.h"
class CImage;

class CSellGame
{
	enum GAMESTATE {IDLE, START, SHUFFLE, SELLECT, RESULT,STATE_END};
public:
	CSellGame();
	~CSellGame();
public:
	void		Late_Initialize();
	void		Initialize();
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

private:
	void	Shuffle(INFO* Tmp, INFO* Src);
	void	Change_State();
	void	Set_Random_Index();
	void	Show_Item();
	void	Check_Result();
	void	Key_Input();
private:
	GAMESTATE m_eCurState;
	GAMESTATE m_ePreState;

	CImage* m_pSeller;

	bool m_bShuffle;
	bool m_bEnd;
	int m_iCusorIndex;
	int m_iMainCusorIndex;
	int	m_iCount;
	int m_iIndex1;
	int m_iIndex2;

	float m_fX;
	float m_fY;
	float m_fRadius;
	float m_fAngle;
	float m_fShuffleSpeed;
	float m_fShowSpeed;

	CImage* m_pSkeleton1;
	CImage* m_pSkeleton2;
	CImage* m_pSkeleton3;
	CImage* m_pResult1;

	CImage* m_pCursor;
	CImage* m_pMainCursor;

	list<CImage*> m_ImageList;
	vector<bool> m_vecResult;

	vector<INFO*> m_vecSkeletons;
	
};

