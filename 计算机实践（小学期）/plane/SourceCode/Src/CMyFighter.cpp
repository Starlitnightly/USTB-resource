#include "CMyFighter.h"
#include "CommonClass.h"
#include "LessonX.h"



CMyFighter::CMyFighter(const char* szName):CWeapon(szName)
{
	m_fVelocityLeft = 0.f;
	m_fVelocityRight = 0.f;
	m_fVelocityUp = 0.f;
	m_fVelocityDown = 0.f;
	m_fBulletCreateTime = 0.3;

}

void CMyFighter::OnMove(bool bKeyDown, int iKey)
{
	if (bKeyDown)
	{
		switch (iKey)
		{
		case KEY_A:  // 左
			m_fVelocityLeft = 30.f;
			break;
		case KEY_D:  // 右
			m_fVelocityRight = 30.f;
			break;
		case KEY_W:  // 上
			m_fVelocityUp = 15.f;
			break;
		case KEY_S:  // 下
			m_fVelocityDown = 15.f;
			break;
		}
	}
	else
	{
		switch (iKey)
		{
		case KEY_A:  // 左
			m_fVelocityLeft = 0.f;
			break;
		case KEY_D:  // 右
			m_fVelocityRight = 0.f;
			break;
		case KEY_W:  // 上
			m_fVelocityUp = 0.f;
			break;
		case KEY_S:  // 下
			m_fVelocityDown = 0.f;
			break;
		}
	}
	float fVelX = m_fVelocityRight - m_fVelocityLeft;
	float fVelY = m_fVelocityDown - m_fVelocityUp;
	SetSpriteLinearVelocity(fVelX, fVelY);
}

void CMyFighter::OnFire(float fDeltaTime)
{
	m_fBulletCreateTime -= fDeltaTime;
	if (m_fBulletCreateTime <= 0.f && m_bCanFire == true)
	{
		// 固定发射时间
		m_fBulletCreateTime = 0.3f;
		g_GameMain.CreateBullet(0,GetSpritePositionX(), GetSpritePositionY());
	}
}

void CMyFighter::OnColOtherSprite(CWeapon *pOther)
{
	if (NULL == pOther)
		return;
	if (pOther->IsMyBullet())
		return;
	SetHp(GetHp() - pOther->GetDamage());
	if (GetHp() <= 200)
	{
		SetSpriteColorGreen(0);
		SetSpriteColorBlue(0);
	}
	else if (GetHp() <= 500)
	{
		SetSpriteColorGreen(128);
		SetSpriteColorBlue(128);
	}
	else
	{
		SetSpriteColorGreen(255);
		SetSpriteColorBlue(255);
	}
}



CMyFighter::~CMyFighter()
{
}
