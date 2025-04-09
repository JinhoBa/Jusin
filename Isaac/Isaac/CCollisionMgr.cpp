#include "pch.h"
#include "CCollisionMgr.h"
#include "CTile.h"
CCollisionMgr* CCollisionMgr::m_pInstance = nullptr;

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Obj(list<CObj*> DstList, list<CObj*> SrcList)
{
	float fWidth(0.f), fHeight(0.f);

	for (auto& Dst : DstList)
	{
		for (auto& Src : SrcList)
		{
			if (Check_Obj(Dst, Src, &fWidth, &fHeight))
			{
				DIRECTION eDstDir;
				DIRECTION eSrcDir;

				if (fWidth < fHeight)
				{
					if (Dst->Get_Collison()->fX < Src->Get_Collison()->fX) // 왼쪽에서 충돌
					{
						eDstDir = DIR_LEFT;
						eSrcDir = DIR_RIGHT;
					}

					else
					{
						eDstDir = DIR_RIGHT;
						eSrcDir = DIR_LEFT;
					}
				}
				// 위아래 충돌
				else
				{
					if (Dst->Get_Collison()->fY < Src->Get_Collison()->fY) // 위에서 충돌
					{
						eDstDir = DIR_UP;
						eSrcDir = DIR_DOWN;
					}
					else
					{
						eDstDir = DIR_DOWN;
						eSrcDir = DIR_UP;
					}
				}

				Dst->Collision(Src, HITPOINT(fWidth, fHeight, eDstDir));
				Src->Collision(Dst, HITPOINT(fWidth, fHeight, eSrcDir));
			}
		}
	}
}



bool CCollisionMgr::Check_Obj(CObj* pDst, CObj* pSrc, float* pWidth, float* pHeight)
{
	float fDistanceX = fabsf(pDst->Get_Collison()->fX - pSrc->Get_Collison()->fX);
	float fDistanceY = fabsf(pDst->Get_Collison()->fY - pSrc->Get_Collison()->fY);
	float fRadiusX = (pDst->Get_Collison()->fCX + pSrc->Get_Collison()->fCX) * 0.5f;
	float fRadiusY = (pDst->Get_Collison()->fCY + pSrc->Get_Collison()->fCY) * 0.5f;

	if (fRadiusX >= fDistanceX && fRadiusY >= fDistanceY)
	{
		*pWidth = fRadiusX - fDistanceX;
		*pHeight = fRadiusY - fDistanceY;

		return true;
	}


	return false;
}

void CCollisionMgr::Collision_Tile(list<CObj*> DstList, vector<CObj*> vecSrc)
{
	if (vecSrc.empty())
		return;
	float fWidth(0.f), fHeight(0.f);

	for (auto& Dst : DstList)
	{
		float fX = Dst->Get_Collison()->fX / TILECX;
		float fY = Dst->Get_Collison()->fY / TILECY;

		int iMinX = (fX <= 0.f) ? 0 : (int)fX - 1;
		int iMaxX = (fX > TILEX) ? TILEX : (int)fX + 2;
		int iMinY = (fY <= 0.f) ? 0 : (int)fY - 1;
		int iMaxY = (fY > TILEY) ? TILEY : (int)fY + 2;

		for (int j = iMinY; j < iMaxY; ++j)
		{
			for (int i = iMinX; i < iMaxX; ++i)
			{
				if(Check_Tile(Dst, vecSrc[TILEX * j + i], &fWidth, &fHeight))
				{
					DIRECTION eDstDir;
					DIRECTION eSrcDir;

					if (fWidth < fHeight)
					{
						if (Dst->Get_Collison()->fX < vecSrc[TILEX * j + i]->Get_Info()->fX) // 왼쪽에서 충돌
						{
							eDstDir = DIR_LEFT;
							eSrcDir = DIR_RIGHT;
						}
						else
						{
							eDstDir = DIR_RIGHT;
							eSrcDir = DIR_LEFT;
						}

					}
					// 위아래 충돌
					else
					{
						if (Dst->Get_Collison()->fY < vecSrc[TILEX * j + i]->Get_Info()->fY) // 위에서 충돌
						{
							eDstDir = DIR_UP;
							eSrcDir = DIR_DOWN;
						}
						else
						{
							eDstDir = DIR_DOWN;
							eSrcDir = DIR_UP;
						}
					}

					Dst->Collision(vecSrc[TILEX * j + i], HITPOINT(fWidth, fHeight, eDstDir));
					vecSrc[TILEX * j + i]->Collision(Dst, HITPOINT(fWidth, fHeight, eSrcDir));
				}
			}
		}
	
	}
}

bool CCollisionMgr::Check_Tile(CObj* pDst, CObj* pTile, float* pWidth, float* pHeight)
{
	/*if (0 == dynamic_cast<CTile*>(pTile)->Get_Option())
		return false;*/

	float fDistanceX = fabsf(pDst->Get_Collison()->fX - pTile->Get_Info()->fX);
	float fDistanceY = fabsf(pDst->Get_Collison()->fY - pTile->Get_Info()->fY);
	float fRadiusX = (pDst->Get_Collison()->fCX + pTile->Get_Info()->fCX) * 0.5f;
	float fRadiusY = (pDst->Get_Collison()->fCY + pTile->Get_Info()->fCY) * 0.5f;

	if (fRadiusX >= fDistanceX && fRadiusY >= fDistanceY)
	{
		*pWidth = fRadiusX - fDistanceX;
		*pHeight = fRadiusY - fDistanceY;

		return true;
	}

	return false;
}
