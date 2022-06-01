#pragma once

#include "CommonClass.h"
#include "CWeapon.h"
class CBullet : public CWeapon
{
private:
	
public:
	CBullet(const int iType, const char *szName);
	~CBullet();

	int	m_iType;
	bool IsMyBullet()
	{
		return m_iType == 0;
	}
	void OnColOtherSprite(CWeapon *pOther);

};


