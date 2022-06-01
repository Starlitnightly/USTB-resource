#include "CSpriteList.h"

CSpriteList::CSpriteList()
{

}

CSpriteList::~CSpriteList() {

}

SpriteStruct *CSpriteList::AddSprite(CWeapon *pSprite)
{
	if (NULL == pSprite)
		return NULL;
	SpriteStruct	*pPtr = new SpriteStruct;
	pPtr->pSprite = pSprite;
	pPtr->pNext = NULL;
	pPtr->pPrev = NULL;
	// 插入链表表尾
	if (NULL == m_pListHeader)
		m_pListHeader = pPtr;
	else
	{
		SpriteStruct	*pTemp = m_pListHeader;
		while (NULL != pTemp->pNext)
			pTemp = pTemp->pNext;
		pPtr->pPrev = pTemp;
		pTemp->pNext = pPtr;
	}
	m_iListSize++;
	return pPtr;
}

void CSpriteList::DeleteSprite(const char *szName, bool bDeleteImage)
{
	SpriteStruct	*pPtr = NULL;
	for (pPtr = m_pListHeader; NULL != pPtr; pPtr = pPtr->pNext)
	{
		if (strcmp(szName, pPtr->pSprite->GetName()) == 0)
		{
			// 将本指针从链表中取出(即将链表中的前后指针重新指定)
			// 假设目前链表如下：有ABC三个值，A <-> B <-> C，需要删除B
			// 则需要将A的Next指向C，C的Prev指向A，删除后结果为A <->C
			if (NULL != pPtr->pNext)
			{
				pPtr->pNext->pPrev = pPtr->pPrev;
			}
			if (NULL != pPtr->pPrev)
			{
				pPtr->pPrev->pNext = pPtr->pNext;
			}
			// 如果是表头
			if (pPtr == m_pListHeader)
			{
				m_pListHeader = m_pListHeader->pNext;
			}
			// 删除Sprite
			if (bDeleteImage)
				pPtr->pSprite->DeleteSprite();
			// 释放内存
			delete pPtr;
			m_iListSize--;
			return;
		}
	}
}

CWeapon *CSpriteList::GetSprite(const int iIndex)
{
	int				iLoop = 0;
	SpriteStruct	*pPtr = m_pListHeader;
	while (NULL != pPtr)
	{
		if (iLoop == iIndex)
			return pPtr->pSprite;
		iLoop++;
		pPtr = pPtr->pNext;
	}
	return NULL;
}

CWeapon * CSpriteList::GetSprite(const char *szName)
{
	SpriteStruct	*pPtr = m_pListHeader;
	while (NULL != pPtr)
	{
		if (strcmp(pPtr->pSprite->GetName(), szName) == 0)
			return pPtr->pSprite;
		pPtr = pPtr->pNext;
	}
	return NULL;
}

void CSpriteList::DeleteAllSprite(bool bDeleteImage)
{
	SpriteStruct	*pPtr = NULL;
	SpriteStruct	*pPtrhNext = m_pListHeader;
	while (NULL != pPtrhNext)
	{
		pPtr = pPtrhNext;
		pPtrhNext = pPtrhNext->pNext;
		if (bDeleteImage)
			pPtr->pSprite->DeleteSprite();
		delete pPtr;
	};
	m_pListHeader = NULL;
	m_iListSize = 0;
}
