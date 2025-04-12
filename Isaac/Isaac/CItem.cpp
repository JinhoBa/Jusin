#include "pch.h"
#include "CItem.h"

CItem::CItem() : m_eItemID(ITEM_END), m_CreateTime(GetTickCount64()), m_fTime(0.f)
{
}

CItem::~CItem()
{
}

