#pragma once
#include "CommonClass.h"
#include "CWeapon.h"


struct SpriteStruct
{
	CWeapon	*pSprite;
	SpriteStruct	*pNext;
	SpriteStruct	*pPrev;
};

class CSpriteList
{
private:
	SpriteStruct *m_pListHeader;
	int	 m_iListSize;

public:
	CSpriteList();
	~CSpriteList();
	int GetListSize() { return m_iListSize; };
	SpriteStruct *AddSprite(CWeapon  *pSprite);
	void DeleteSprite(const char *szName, bool bDeleteImage);
	CWeapon  *GetSprite(const int iIndex);
	CWeapon * GetSprite(const char *szName);
	void DeleteAllSprite(bool bDeleteImage);
};