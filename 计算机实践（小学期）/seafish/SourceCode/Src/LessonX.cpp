/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
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
	m_iGameState			=	1;
	yu_0 = new CSprite("yu_0");
	m_fScreenBottom = 0.f;
	m_fScreenLeft = 0.f;
	m_fScreenRight = 0.f;
	m_fScreenTop = 0.f;
	speed = 0;
	kongzhiyu=new CSprite("kongzhiyu");

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
			GameInit1();
			SetGameState(2); // 初始化之后，将游戏状态设置为进行中
		}
		break;

		// 游戏进行中，处理各种游戏逻辑
	case 2:
		{
			// TODO 修改此处游戏循环条件，完成正确游戏逻辑
			if( true )
			{
				GameRun( fDeltaTime );
			}
			else // 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
			{				
				SetGameState(0);
				GameEnd();
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
void CGameMain::GameInit1()
{
	yu_0->SetSpriteLinearVelocity(30, 30);
	// 获取屏幕的边界值
	m_fScreenLeft = CSystem::GetScreenLeft();
	m_fScreenRight = CSystem::GetScreenRight();
	m_fScreenTop = CSystem::GetScreenTop();
	m_fScreenBottom = CSystem::GetScreenBottom();

	// 设置精灵世界边界
	yu_0->SetSpriteWorldLimit(WORLD_LIMIT_NULL, m_fScreenLeft, m_fScreenTop, m_fScreenRight, m_fScreenBottom);

	speed = 30;
	yu_0->SetSpriteLinearVelocity(speed, 0);

	// 生成多条鱼精灵
	for (int i = 0; i < 4; i++)
	{
		char  szName[128];
		float fPosX, fPosY;
		float fSpeedX;
		//将szName的值赋为”fish”加I,级循环因子
		sprintf(szName, "fish%d", i);//fish0,fish1,fish2,fish3
		CSprite* tmpSprite = new CSprite(szName);
		tmpSprite->CloneSprite("kongzhiyu");//创建精灵

		fPosX = CSystem::RandomRange(m_fScreenLeft + 10.f, m_fScreenRight - 10.f);
		fPosY = CSystem::RandomRange(m_fScreenTop + 10.f, m_fScreenBottom - 10.f);
		tmpSprite->SetSpritePosition(fPosX, fPosY);
		tmpSprite->SetSpriteWorldLimit(WORLD_LIMIT_NULL, m_fScreenLeft - 20.f, m_fScreenTop, m_fScreenRight + 20.f, m_fScreenBottom);
		
		fSpeedX = CSystem::RandomRange(10, 20);
		tmpSprite->SetSpriteLinearVelocity(fSpeedX, 0);
		m_vFish.push_back(tmpSprite);

	}





}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{
}
//=============================================================================
//
// 本局游戏结束
void CGameMain::GameEnd()
{
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
	float	fSpeedX = 0.f, fSpeedY = 0.f;
	switch (iKey)
	{
	case KEY_W:
		fSpeedY = -10.f; //向上的时候Y方向速度为负的
		break;
	case KEY_A:
		fSpeedX = -15.f;	//向左的时候X方向的速度为负值
		break;
	case KEY_S:
		fSpeedY = 10.f; //向下的时候Y方向的速度为正值
		break;
	case KEY_D:
		fSpeedX = 15.f;//向右的时候X方向的速度为正值
		break;
	}
	kongzhiyu->SetSpriteLinearVelocity(fSpeedX, fSpeedY);

	if (iKey == KEY_F && bCtrlPress == true) {
		yu_0->SetSpriteVisible(false);
	}

}
//==========================================================================
//
// 键盘弹起
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
void CGameMain::OnKeyUp( const int iKey )
{
	float	fSpeedX=0.f, fSpeedY=0.f;
	switch (iKey)
	{
	case KEY_W:
	case KEY_A:
	case KEY_S:
	case KEY_D:
		fSpeedX = 0.f;
		fSpeedY = 0.f;
	}
	kongzhiyu->SetSpriteLinearVelocity(fSpeedX, fSpeedY);

}
//===========================================================================
//
// 精灵与精灵碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	
}
//===========================================================================
//
// 精灵与世界边界碰撞
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	if (strcmp(szName, "yu_0") == 0)
	{
		bool panduan;
		if (speed > 0)
			panduan = true;
		else
			panduan = false;
		speed = 0 - speed;
		yu_0->SetSpriteLinearVelocity(speed, 0);
		
		
		yu_0->SetSpriteFlipX(panduan);
	}

	bool bFlip;
	float fSpeedX = 0.f, fSpeedY = 0.f;

	if (strstr(szName, "fish") != NULL)
	{
		if (iColSide == 1)  // 右边
		{
			bFlip = true;
			fSpeedX = -CSystem::RandomRange(10, 20);
		}
		else if (iColSide == 0)   // 左边
		{
			bFlip = false;
			fSpeedX = CSystem::RandomRange(10, 20);
		}
		CSprite* tmpSprite = FindSpriteByName(szName);
		tmpSprite->SetSpriteFlipX(bFlip);
		tmpSprite->SetSpriteLinearVelocity(fSpeedX, 0);
		float fPosY;
		fPosY = CSystem::RandomRange(m_fScreenTop + 10.f, m_fScreenBottom - 10.f);

		tmpSprite->SetSpritePositionY(fPosY);
	}


}


CSprite* CGameMain::FindSpriteByName(const char* szName)
{
	for (int i = 0; i < m_vFish.size(); i++)
		if (strcmp(szName, m_vFish[i]->GetName()) == 0)
			return m_vFish[i];

}


