/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
#include "CBullet.h"
#include "CSpriteList.h"
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;	

//==============================================================================
//
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。

//==============================================================================
//
// 构造函数
CGameMain::CGameMain()
{
	m_iGameState			=	0;


	m_pBeginSprite = new CSprite("GameBegin");
	m_pCurScoreText = new CTextSprite("CurScoreText");
	m_pMaxScoreText = new CTextSprite("MaxScoreText");
	m_pMyFighter = NULL;



}
//==============================================================================
//
// 析构函数
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// 游戏主循环，此函数将被不停的调用，引擎每刷新一次屏幕，此函数即被调用一次
// 用以处理游戏的开始、进行中、结束等各种状态. 
// 函数参数fDeltaTime : 上次调用本函数到此次调用本函数的时间间隔，单位：秒
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
		// 初始化游戏，清空上一局相关数据
	case 1:
		{
			GameInit();
			SetGameState(2); // 初始化之后，将游戏状态设置为进行中
		}
		break;

		// 游戏进行中，处理各种游戏逻辑
	case 2:
		{
			// TODO 修改此处游戏循环条件，完成正确游戏逻辑
			if(!IsGameLost())
			{
				GameRun( fDeltaTime );
			}
			else // 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
			{				
				GameEnd();
				SetGameState(0);
				
			}
		}
		break;

		// 游戏结束/等待按空格键开始
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// 每局开始前进行初始化，清空上一局相关数据
void CGameMain::GameInit()
{
	m_pBeginSprite->SetSpriteVisible(false);

	if (NULL == m_pMyFighter)
	{
		m_pMyFighter = new CMyFighter("ControlSprite");
		m_pMyFighter->SetSpriteWorldLimit(WORLD_LIMIT_STICKY, CSystem::GetScreenLeft() - 10.f, CSystem::GetScreenTop(), CSystem::GetScreenRight(), CSystem::GetScreenBottom());
	}
	m_pMyFighter->SetHp(500);
	m_pMyFighter->SetScore(0);
	m_pMyFighter->SetSpriteVisible(true);
	m_pCurScoreText->SetTextValue(m_pMyFighter->GetScore());
	m_pMaxScoreText->SetTextValue(0);
	m_iCreatedBulletCount = 0;

	


}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{
	// 执行我方战机的循环函数
	if (m_pMyFighter)
		m_pMyFighter->OnFire(fDeltaTime);
	CEnemyFighter::createEnemyFighter(fDeltaTime);

	int	iListSize = m_SpriteList.GetListSize();
	for (int iLoop = 0; iLoop < iListSize; iLoop++)
	{
		CSprite * pSprite = m_SpriteList.GetSprite(iLoop);
		if (pSprite != NULL && (strstr(pSprite->GetName(), "HorizontalSprite") != NULL))
		{
			((CEnemyFighter *)pSprite)->OnFire(fDeltaTime);
		}
	}
	m_pCurScoreText->SetTextValue(m_pMyFighter->GetScore());


}
//=============================================================================
//
// 本局游戏结束
void CGameMain::GameEnd()
{
	m_pBeginSprite->SetSpriteVisible(true);
	m_SpriteList.DeleteAllSprite(true);
	m_pMyFighter->SetSpriteVisible(false);
	delete m_pMyFighter;
	m_pMyFighter = NULL;

}
//==========================================================================
//
// 鼠标移动
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseMove( const float fMouseX, const float fMouseY )
{
	
}
//==========================================================================
//
// 鼠标点击
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	
}
//==========================================================================
//
// 鼠标弹起
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{

	
}
//==========================================================================
//
// 键盘按下
// 参数 iKey：被按下的键，值见 enum KeyCodes 宏定义
// 参数 iAltPress, iShiftPress，iCtrlPress：键盘上的功能键Alt，Ctrl，Shift当前是否也处于按下状态(0未按下，1按下)
void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{	
	// 按下空格，游戏开始
	if (KEY_SPACE == iKey && 0 == GetGameState())
	{
		SetGameState(1);
	}

	if (2 == GetGameState()) //当游戏状态为2时
	{
		m_pMyFighter->OnMove(true, iKey);
	}
	// 游戏进行中，按下空格发射子弹
	if (2 == GetGameState() && KEY_SPACE == iKey && NULL != m_pMyFighter)
		m_pMyFighter->SetCanFire(true);



}
//==========================================================================
//
// 键盘弹起
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
void CGameMain::OnKeyUp( const int iKey )
{
	if (2 == GetGameState())
	{
		m_pMyFighter->OnMove(false, iKey);
	}
	if (2 == GetGameState() && KEY_SPACE == iKey && NULL != m_pMyFighter)
		m_pMyFighter->SetCanFire(false);

}
//===========================================================================
//
// 精灵与精灵碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	if (2 != GetGameState())
		return;

	CWeapon	*pSrcSprite = IsMyFighter(szSrcName) ? m_pMyFighter : GetSprite(szSrcName);
	CWeapon *pTarSprite = IsMyFighter(szTarName) ? m_pMyFighter : GetSprite(szTarName);

	if (NULL == pSrcSprite || NULL == pTarSprite)
		return;

	pSrcSprite->OnColOtherSprite(pTarSprite);
	pTarSprite->OnColOtherSprite(pSrcSprite);

	if (!pSrcSprite->IsMyFighter())
	{
		if (pSrcSprite->IsDead())
			g_GameMain.DeleteSprite(szSrcName, true);
	}
	if (!pTarSprite->IsMyFighter())
	{
		if (pTarSprite->IsDead())
			g_GameMain.DeleteSprite(szTarName, true);
	}

	
}
//===========================================================================
//
// 精灵与世界边界碰撞
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	
}

void CGameMain::CreateBullet(int iType,const float fPosX, const float fPosY)
{
	char	szName[MAX_NAME_LEN];// MAX_NAME_LE为CommonClass.h中宏定义 值为128
	sprintf(szName, "Bullet1_%d", m_iCreatedBulletCount);
	m_iCreatedBulletCount++;
	CBullet *pBullet = new CBullet(iType, szName);
	pBullet->CloneSprite("Bullet1_Template");
	pBullet->SetSpritePosition(fPosX, fPosY);
	if (1 == iType) //如果iType值为1，则说明子弹为敌方战机发射。
	{
		pBullet->SetSpriteLinearVelocityX(-30);
	}
	else//其他情况说明为我方战机反射
	{
		pBullet->SetSpriteFlipX(true);
		pBullet->SetSpriteLinearVelocityX(60);
	}

	pBullet->SetSpriteWorldLimit(WORLD_LIMIT_NULL, CSystem::GetScreenLeft() - 10.f, CSystem::GetScreenTop(), CSystem::GetScreenRight() + 200.f, CSystem::GetScreenBottom());
	pBullet->SetSpriteCollisionActive(true, true);
	pBullet->SetDamage(100);
	pBullet->SetHp(10);

	AddSprite(pBullet);
}

void CGameMain::AddSprite(CWeapon  *pSprite)
{
	m_SpriteList.AddSprite(pSprite);
}

CWeapon *CGameMain::GetSprite(const int iIndex)
{
	return m_SpriteList.GetSprite(iIndex);
}

CWeapon *CGameMain::GetSprite(const char *szName)
{
	return m_SpriteList.GetSprite(szName);
}
//包装删除精灵
void	CGameMain::DeleteSprite(const char *szName, bool bDeleteImage)
{
	m_SpriteList.DeleteSprite(szName, bDeleteImage);
}

bool CGameMain::IsMyFighter(const char *szName)
{
	return (strcmp(m_pMyFighter->GetName(), szName) == 0);
}

CMyFighter * CGameMain::GetMyFighter()
{
	return m_pMyFighter;
}

bool CGameMain::IsGameLost()
{
	return (m_pMyFighter ? m_pMyFighter->IsDead() : false);
}




