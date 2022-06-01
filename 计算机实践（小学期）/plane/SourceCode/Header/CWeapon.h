#pragma once

#include "CommonClass.h"

class CWeapon : public CSprite
{
private:
	int	 m_iHp;
	int	 m_iDamage;
	int	 m_iScore;
	int	 m_iType;

public:
	CWeapon(const char *szName);
	CWeapon(int iType, const char* szName);  //为CBullet类准备
	virtual ~CWeapon() { };

	bool		IsDead() { return m_iHp <= 0; }
	virtual bool	IsMyFighter() { return false; }
	virtual bool	IsMyBullet() { return false; }
	virtual void	OnColOtherSprite(CWeapon *pOther) {}

	void SetHp(int hp) {
		m_iHp = hp;
	}

	void SetDamage(int da) {
		m_iDamage = da;
	}
	void SetScore(int s) {
		m_iScore = s;
	}
	void SetType(int t){
		m_iType = t;
	}

	int GetHp() { return m_iHp; }
	int GetDamage() { return m_iDamage; }
	int GetScore() { return m_iScore; }
	int GetType() { return m_iType; }


};
