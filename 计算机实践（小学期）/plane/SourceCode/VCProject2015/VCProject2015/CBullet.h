#pragma once

#include "CommonClass.h"
class CBullet : public CSprite
{
private:
	bool m_bCanFire;
public:
	CBullet(const char *szName);
	~CBullet();

	void	SetCanFire(const bool bCan) { m_bCanFire = bCan; }
	bool GetCanFire() { return m_bCanFire; }
};


