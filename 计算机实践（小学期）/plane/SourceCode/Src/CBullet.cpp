#include "CBullet.h"



CBullet::CBullet(const int iType, const char *szName) :CWeapon(iType, szName)
{
	m_iType = iType;
}



CBullet::~CBullet()
{
}



void CBullet::OnColOtherSprite(CWeapon *pOther)
{
	if (NULL == pOther)
		return;
	if (IsMyBullet())
	{
		if (pOther->IsMyFighter())
			return;
		SetHp(GetHp() - pOther->GetDamage());
	}
	else
	{
		if (pOther->IsMyFighter() || pOther->IsMyBullet())
		{
			SetHp(GetHp() - pOther->GetDamage());
		}
	}
}
