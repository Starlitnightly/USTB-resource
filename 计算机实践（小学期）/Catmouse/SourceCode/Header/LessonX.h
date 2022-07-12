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
#include <string>
#include <iostream>
#include<vector>


using namespace std;

class Animal :public  CAnimateSprite
{
public:

	int hp;	//血量
	int mp;	//蓝量
	int att;//攻击力
	int defend;//防御力
	float jumptime;//跳跃持续时间
	bool up;//跳起状态
	bool down;//落下状态

	string nowchaoxiang;//精灵当前朝向
	string changechaoxiang;//精灵要改变的朝向
	const char *animation;//精灵当前正在显示并播放的动画

	int mode;//1,run 2,att 3,sta
	Animal(const char*name);//构造函数


};

class	CGameMain
{
private:
	int				m_iGameState;				// 游戏状态，0：结束或者等待开始；1：初始化；2：游戏进行中

	int Now;//当前关卡
	CStaticSprite *map;//定义背景地图的指针
	CTextSprite *debug;//调试用文本显示
	double *score;

	vector<Animal*> human;
	int nowhuman;
	const char*nowhumansta;
	const char*nowhumanrun;
	CEffect *nowhumanatt;
	Animal *cat;//定义人物-猫的指针
	Animal *mouse;//老鼠指针
	CEffect *cat_att_eff;//猫的攻击效果
	CEffect *mouse_att_eff;//狗的攻击效果
	CEffect *jn1;
	CEffect *jn2;


	Animal *sdog;//小怪1-小狗指针
	Animal *boss;//boss-boss指针
	vector<Animal*> smalldog;//小怪容器
	float leftovertime;//小怪自动生成剩余时间
	float lefttime;
	float totaltime;
	float tmptime;
	int produce;//小怪生成数量


	CSprite *mainmap;//主界面地图
	CStaticSprite *first;//第一关按钮
	CStaticSprite *second;//第二关按钮
	CStaticSprite *third;//第三关按钮
	CStaticSprite *xzrw;
	CStaticSprite *xzrwjm;
	CStaticSprite *help;
	CStaticSprite *helpbb;
	CStaticSprite *helpx;
	CStaticSprite *phb;
	CStaticSprite *phbbb;
	CStaticSprite *phbx;
	CSprite *mainmenu;//主菜单
	CStaticSprite *menu;//菜单界面
	CStaticSprite *menu1;//回到游戏
	CStaticSprite *menu2;//退出游戏
	CStaticSprite *menu3;//回到主界面


	CStaticSprite *button_cj;//成就按钮
	CStaticSprite *cj1;//成就界面指针
	CStaticSprite *cjx;//关闭成就界面~
	CStaticSprite *cjd1;//成就点1
	CStaticSprite *cjd2;//成就点2
	CStaticSprite *cjd3;//成就点3
	CStaticSprite *cjd4;//成就点4
	CStaticSprite *cjd5;//成就点5
	CStaticSprite *cjd6;//成就点6
	CStaticSprite *cjd7;//成就点7
	CStaticSprite *cj;
	CStaticSprite *button_bb;//背包按钮
	CStaticSprite *bb;//背包界面
	CStaticSprite *bb1;//左背包
	CStaticSprite *bb2;//右背包
	CStaticSprite *bbx;//关闭背包界面
	bool bagopen;

	CStaticSprite *grey;//灰色界面
	CStaticSprite *gameover;//游戏结束文字
	CStaticSprite *gamenext;//进入下一关
	CStaticSprite *gameback;//返回主界面
	CStaticSprite *tongguan;//通关文字
	CStaticSprite *guanqia;
	CStaticSprite *humant;
	CStaticSprite *sshp;
	CStaticSprite *ssmp;


	const char*bossname;//boss的名称（对应funcode的接口）
	const char*smallbossname;//小怪的名称
	CStaticSprite *bossx;
	CStaticSprite *bosst;
	int bosstj;


	CTextSprite *thp;
	CTextSprite *tmp;
	CTextSprite *tatt;
	CTextSprite *tdef;
	CTextSprite *sshpt;
	CTextSprite *ssmpt;

	CTextSprite *totalt;
	CTextSprite *time1;
	CTextSprite *time2;
	CTextSprite *time3;
	CTextSprite *time4;
	CTextSprite *time5;



	bool config1;
	bool config2;
	bool config3;
	bool config4;
	bool config5;
	bool config6;
	bool config7;

public:
	
	
	CGameMain();    //构造函数
	~CGameMain();   //析构函数     
	int				GetGameState()											{ return m_iGameState; }
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }
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
	void ViewScore(double *score);
/*
	ProduceDog:生产小怪	

	参数：
	i     :编号
	sprite:复制用的怪物名称
	x,y   :生成位置
*/
	
	void ProduceDog(int i,const char*sprite,float x,float y);
/*
ProduceBoss:生产boss
参数：
i     :编号
sprite:复制用的怪物名称
x,y   :生成位置
返回值:
tmpDog:生成的boss对应的地址
*/
	Animal* ProduceBoss(int i, const char*sprite, float x, float y);
	/*
	Init:初始化关卡
	参数：
	now  :当前关卡
	mname:地图名字
	bname:boss名字
	sname:小怪名字
	*/
	void Init(int now, const char*mname, const char*bname, const char*sname);

	void SetAnimalbase(int hp, int mp, int att, int def);
};

/////////////////////////////////////////////////////////////////////////////////
// 
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_