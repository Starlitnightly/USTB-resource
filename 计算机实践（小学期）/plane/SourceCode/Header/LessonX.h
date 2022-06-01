/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include "CMyFighter.h"
#include "CBullet.h"
#include "CEnemyFighter.h"
#include "CSpriteList.h"

/////////////////////////////////////////////////////////////////////////////////
//
// 游戏总管类。负责处理游戏主循环、游戏初始化、结束等工作
class	CGameMain
{
private:
	int				m_iGameState;				// 游戏状态，0：结束或者等待开始；1：初始化；2：游戏进行中

public:
	CGameMain();            //构造函数
	~CGameMain();           //析构函数  

	// Get方法
	int				GetGameState()											{ return m_iGameState; }
	
	// Set方法
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }
	
	// 游戏主循环等
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();
	void 			OnMouseMove( const float fMouseX, const float fMouseY );
	void 			OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY );
	void 			OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY );
	void 			OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress );
	void 			OnKeyUp( const int iKey );
	void 			OnSpriteColSprite( const char *szSrcName, const char *szTarName );
	void 			OnSpriteColWorldLimit( const char *szName, const int iColSide );

	CSprite*		m_pBeginSprite; //GameBegin为“空格开始”精灵
	CTextSprite*	m_pCurScoreText;//显示当前积分
	CTextSprite*	m_pMaxScoreText;// 显示最高分
	CMyFighter*		 m_pMyFighter;
	int m_iCreatedBulletCount;
	void CreateBullet(int iType, const float fPosX, const float fPosY);
	CSpriteList m_SpriteList;
	void AddSprite(CWeapon  *pSprite);
	CWeapon *GetSprite(const int iIndex);
	CWeapon *GetSprite(const char *szName);
	void DeleteSprite(const char *szName, bool bDeleteImage);

	bool IsMyFighter(const char *szName);
	CMyFighter * GetMyFighter();

	bool IsGameLost();

	

};

/////////////////////////////////////////////////////////////////////////////////
// 
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_