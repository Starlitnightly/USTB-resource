#pragma once
#include "CommonClass.h"
#include "CWeapon.h"
class CEnemyFighter :
	public CWeapon
{
private:


public:

	CEnemyFighter(const char* szName);
	~CEnemyFighter();

	static float	m_fCreateTime;			// 创建敌机的时间间隔
	static int	m_iCreatedEnemyCount;//表示创建战机数量

	void static createEnemyFighter(float fDeltaTime);

	float m_fBulletCreateTime;
	float m_fFloatTime;
	bool m_bFloatUp;
	void  OnFire(float fDeltaTime);
	void OnColOtherSprite(CWeapon *pOther);

};

