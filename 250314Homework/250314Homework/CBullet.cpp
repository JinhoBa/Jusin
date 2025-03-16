#include "pch.h"
#include "CBullet.h"

CBullet::CBullet()
{
	listBullet = {};
	m_pBullet = nullptr;
	m_preBullet = nullptr;
	m_pRc = nullptr;
}

CBullet::~CBullet()
{
	Release();
}


void CBullet::Initialize(RECT* _pRcPlayer)
{
	m_preBullet = new RECT;
	m_pRc = _pRcPlayer;
	m_hDC = GetDC(g_hWnd);
}

void CBullet::Render()
{
	if(listBullet.size() > 0)
	{
		/*for (auto& bullet : listBullet)
		{
			*m_preBullet = *bullet;
			m_preBullet->left -= 20;
			m_preBullet->right -= 20;
			InvalidateRect(g_hWnd, m_preBullet, true);
			Ellipse(m_hDC, bullet->left, bullet->top, bullet->right, bullet->bottom);

			bullet->left += 20;
			bullet->right += 20;

		}*/
		
		for (iter = listBullet.begin(); iter != listBullet.end();)
		{
			if ((*iter)->left > 1000)
			{
				Safe_Delete(*iter);
				iter = listBullet.erase(iter);
			}
			else
			{
				*m_preBullet = *(*iter);
				m_preBullet->left -= 20;
				m_preBullet->right -= 20;
				InvalidateRect(g_hWnd, m_preBullet, true);
				Ellipse(m_hDC, (*iter)->left, (*iter)->top, (*iter)->right, (*iter)->bottom);

				(*iter)->left += 20;
				(*iter)->right += 20;
				++iter;
			}
			
		}
	}
}

void CBullet::Release()
{
	Safe_Delete<RECT*>(m_preBullet);
	for (iter = listBullet.begin(); iter != listBullet.end();)
	{
		Safe_Delete<RECT*>(*iter);
		iter = listBullet.erase(iter);
	}
	ReleaseDC(g_hWnd, m_hDC);
}

void CBullet::Add_Bullet()
{
	m_pBullet = new RECT({ m_pRc->left + 10,m_pRc->top +7 , m_pRc->right + 10, m_pRc->bottom -7 });
	listBullet.push_back(m_pBullet);
}
