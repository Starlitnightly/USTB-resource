#pragma once
#include "CommonClass.h"
#include "CWeapon.h"
class CMyFighter :
	public CWeapon
{
private:
	float m_fVelocityLeft;
	float m_fVelocityRight;
	float m_fVelocityUp;
	float m_fVelocityDown;
	bool m_bCanFire;

public:
	float m_fBulletCreateTime;
	void OnMove(bool bKeyDown, int iKey);
	void OnFire(float fDeltaTime);
	CMyFighter(const char* szName);
	~CMyFighter();


	void	SetCanFire(const bool bCan) { m_bCanFire = bCan; }
	bool GetCanFire() { return m_bCanFire; }
	bool	IsMyFighter()
	{
		return true;
	}

	void OnColOtherSprite(CWeapon *pOther);

};

