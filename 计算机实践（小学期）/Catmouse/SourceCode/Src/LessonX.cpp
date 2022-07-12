/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "Catfunction.h"
#include "LessonX.h"
#include "ConfigManager.h"
#include "mmsystem.h"//导入声音头文件
#pragma comment(lib,"winmm.lib")//导入声音头文件库
void PlayMp3()
{
	char buf[128];
	char str[128] = { 0 };
	int i = 0;
	//use mciSendCommand
	MCI_OPEN_PARMS mciOpen;
	MCIERROR mciError;
	//SetWindowText(NULL,"12345");
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciOpen.lpstrElementName = "bgm.wav";
	mciError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)&mciOpen);
	if (mciError)
	{
		mciGetErrorString(mciError, buf, 128);
		return;
	}
	UINT DeviceID = mciOpen.wDeviceID;
	MCI_PLAY_PARMS mciPlay;
	mciError = mciSendCommand(DeviceID, MCI_PLAY, 0, (DWORD)&mciPlay);
	if (mciError)
	{
		return;
	}
}


////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;	

Animal::Animal(const char*name) : CAnimateSprite(name) {};




void CGameMain::SetAnimalbase(int hp, int mp, int att, int def)
{
	human[nowhuman]->hp = hp;
	human[nowhuman]->mp = mp;
	human[nowhuman]->att = att;
	human[nowhuman]->defend = def;
	thp->SetTextValue(human[nowhuman]->hp);
	tmp->SetTextValue(human[nowhuman]->mp);
	tatt->SetTextValue(human[nowhuman]->att);
	tdef->SetTextValue(human[nowhuman]->defend);
}

bool Getachievement(const char *key,int value)
{
	ConfigManager *configManger = new ConfigManager("config.ini");
	char *general_sect = "achievement";
	if (configManger->GetInt(general_sect, key, 0) == value)
	{
		return true;
	}
	else return false;
	delete configManger;
}
void Setachievement(const char*key,int value)
{
	ConfigManager *configManger = new ConfigManager("config.ini");
	char *general_sect = "achievement";
	configManger->SetInt(general_sect,key, value);
	delete configManger;
}

double* GetScore()
{
	double *score=new double[7];
	ConfigManager *configManger = new ConfigManager("config.ini");
	for (int i = 0; i < 7; i++)
	{
		string temp = "s" + std::to_string(i);
		score[i]=configManger->GetDouble("score", temp.c_str(), 1000.f);
	}
	delete configManger;
	for (int i = 0; i < 7; i++)
	{
		int maxIndex = i;
		for (int j = i; j < 7; j++)
		{
			if (score[j] < score[maxIndex])
				maxIndex = j;
		}
		int temp = score[maxIndex];
		score[maxIndex] = score[i];
		score[i] = temp;

	}
	return score;
}

void SetScore(double value,double *score)
{
	
	for (int i = 0; i < 7; i++)
	{
		if (score[i] >= value)
		{
			score[i] = value;
			break;
		}
	}
	for (int i = 0; i < 7; i++)
	{
		int maxIndex = i;
		for (int j = i; j < 7; j++)
		{
			if (score[j] < score[maxIndex])
				maxIndex = j;
		}
		int temp = score[maxIndex];
		score[maxIndex] = score[i];
		score[i] = temp;

	}
	ConfigManager *configManger = new ConfigManager("config.ini");
	for (int i = 0; i < 7; i++)
	{
		string temp = "s" + std::to_string(i);
		string temp2 = std::to_string(score[i]);
		configManger->SetString("score", temp.c_str(), temp2.c_str());
	}
	delete configManger;
}

void CGameMain::ViewScore(double *score)
{
	time1->SetTextValueFloat(score[0]);
	time2->SetTextValueFloat(score[1]);
	time3->SetTextValueFloat(score[2]);
	time4->SetTextValueFloat(score[3]);
	time5->SetTextValueFloat(score[4]);
}
/*
ProduceDog:生产小怪
参数：
i     :编号
sprite:复制用的怪物名称
x,y   :生成位置
*/
void CGameMain::ProduceDog(int i, const char*sprite, float x, float y)
{
	//批量产生的怪物名称
	char *tmpdog;
	tmpdog = CSystem::MakeSpriteName("Dog", i);
	//利用批量产生的怪物名称创建指针，并赋予其相应的属性
	Animal *tmpAnimal = new Animal(tmpdog);
	tmpAnimal->CloneSprite(sprite);
	tmpAnimal->SetSpritePosition(x, y);
	tmpAnimal->SetSpriteWorldLimit(WORLD_LIMIT_NULL, CSystem::GetScreenLeft(), CSystem::GetScreenTop(), CSystem::GetScreenRight(), CSystem::GetScreenBottom());
	//基本属性
	tmpAnimal->hp = 1000;
	tmpAnimal->att = 10;
	tmpAnimal->SetSpriteLinearVelocity(-10.f, 0);
	//碰撞
	tmpAnimal->SetSpriteCollisionSend(true);
	tmpAnimal->SetSpriteCollisionReceive(true);
	//朝向
	tmpAnimal->changechaoxiang = "left";
	//将批量产生的怪物放进容器smalldog内管理
	smalldog.push_back(tmpAnimal);
}

/*
ProduceBoss:生产boss
参数：
i     :编号
sprite:复制用的怪物名称
x,y   :生成位置
返回值:
tmpDog:生成的boss对应的地址
*/
Animal* CGameMain::ProduceBoss(int i, const char*sprite, float x, float y)
{
	char *tmpdog;
	tmpdog = CSystem::MakeSpriteName("Boss", i);
	Animal *tmpDog = new Animal(tmpdog);
	tmpDog->CloneSprite(sprite);
	tmpDog->SetSpritePosition(x, y);
	tmpDog->SetSpriteWorldLimit(WORLD_LIMIT_NULL, CSystem::GetScreenLeft(), CSystem::GetScreenTop(), CSystem::GetScreenRight(), CSystem::GetScreenBottom());
	tmpDog->hp = 1000;
	tmpDog->att = 10;
	tmpDog->SetSpriteLinearVelocity(-10.f, 0);
	tmpDog->SetSpriteCollisionSend(true);
	tmpDog->SetSpriteCollisionReceive(true);
	tmpDog->changechaoxiang = "left";
	return tmpDog;
}
/*
	Init:初始化关卡
	参数：
	now  :当前关卡
	mname:地图名字
	bname:boss名字
	sname:小怪名字
*/
void CGameMain::Init(int now,const char*mname, const char*bname, const char*sname) 
{
	lefttime = 1;
	totaltime = 0;
	map->SetStaticSpriteImage(mname, 0);//设置地图
	map->SetSpritePosition(117.f, -45.f);//设置地图位置
	human[nowhuman]->SetSpritePosition(map->GetSpriteLinkPointPosX(1), map->GetSpriteLinkPointPosY(1));//老鼠出生点
	menu->SetSpritePosition(-48.f, -27.f);//菜单按钮消失
	button_cj->SetSpritePosition(-100.f, -27.f);//成就按钮消失
	button_bb->SetSpritePosition(-100.f, -27.f);//背包按钮消失
	xzrw->SetSpritePosition(-100.f, -27.f);//背包按钮消失
	phbbb->SetSpritePosition(-100.f, -27.f);
	helpbb->SetSpritePosition(-100.f, -27.f);
	leftovertime = 2.f;//小怪生成倒计时
	produce = 10;//小怪生成数量
	bossname = bname;//boss名字
	smallbossname = sname;//小怪名字
	Now = now;//设置当前关卡数
	switch (now)
	{
	case 1:
		guanqia->SetStaticSpriteImage("guan11ImageMap", 0); break;
	case 2:
		guanqia->SetStaticSpriteImage("guan22ImageMap", 0); break;
	case 3:
		guanqia->SetStaticSpriteImage("guan33ImageMap", 0); break;
	}
	SetGameState(1);//设置游戏模式
	if (nowhuman == 1)
	{
		SetAnimalbase(2000, 1000, 100, 10);
		humant->SetStaticSpriteImage("moutImageMap", 0);
		humant->SetSpritePosition(-49.f, -31.f);

	}
	else if (nowhuman == 0)
	{
		SetAnimalbase(3000, 500, 100, 10);
		humant->SetStaticSpriteImage("cattImageMap", 0);
		humant->SetSpritePosition(-49.f, -31.f);
	}
	

}

CGameMain::CGameMain()
{

	
	//所有指针的初始化
	xzrw = new CStaticSprite("xzanniu");
	xzrwjm = new CStaticSprite("xuanze");
	cat = new Animal("cat");//创建一个叫cat的指针
	cat_att_eff = new CEffect("cat_att_eff", "", 0.2);//猫的攻击效果
	mouse = new Animal("mouse");//老鼠
	mouse->changechaoxiang = "right";//老鼠的初始朝向	
	nowhuman = 1;
	mouse->hp = 2000;
	mouse_att_eff = new CEffect("mouse_att_eff","",0.2);//老鼠的攻击效果
	jn1 = new CEffect("steam", "", 0.2);
	jn2 = new CEffect("miaosha", "", 0.2);
	map = new CStaticSprite("gamemap1");//创建游戏地图	
	debug = new CTextSprite("cat_hp");//debug显示用
	mainmap= new CSprite("mainmap");
	first = new 	CStaticSprite("first");
	second = new 	CStaticSprite("second");
	third = new 	CStaticSprite("third");
	button_cj = new CStaticSprite("cjbutton");
	button_bb = new CStaticSprite("bbbutton");
	cj1 = new CStaticSprite("cj1");
	cjx=new CStaticSprite("cjx");
	cjd1 = new CStaticSprite("dian1");
	cjd2 = new CStaticSprite("dian2");
	cjd3 = new CStaticSprite("dian3");
	cjd4 = new CStaticSprite("dian4");
	cjd5 = new CStaticSprite("dian5");
	cjd6 = new CStaticSprite("dian6");
	cjd7 = new CStaticSprite("dian7");
	cj = new CStaticSprite("chengjiuneirong");
	bb = new CStaticSprite("mainbb");
	bb1=new CStaticSprite("mainbb1");
	bb2 = new CStaticSprite("mainbb2");
	bbx = new CStaticSprite("bbx");
	mainmenu = new CSprite("mainmenu");
	menu = new CStaticSprite("menu");
	menu1 = new CStaticSprite("menu1");
	menu2 = new CStaticSprite("menu2");
	menu3 = new CStaticSprite("menu3");
	grey=new CStaticSprite ("grey");
	gameover=new CStaticSprite ("gameover");
	gamenext=new CStaticSprite ("gamenext");
	gameback=new CStaticSprite ("gameback");
	tongguan = new CStaticSprite("tongguan");
	bossx = new CStaticSprite("bossx");
	bosst = new CStaticSprite("bosst");
	guanqia = new CStaticSprite("guanqia");
	humant = new CStaticSprite("humant");
	totalt = new CTextSprite("totalt");
	thp = new CTextSprite("thp");
	tmp = new CTextSprite("tmp");
	tatt = new CTextSprite("tatt");
	tdef = new CTextSprite("tdef");
	sshpt = new CTextSprite("sshpt");
	ssmpt = new CTextSprite("ssmpt");
	sshp = new CStaticSprite("sshp");
	ssmp = new CStaticSprite("ssmp");
	helpbb = new CStaticSprite("helpbb");
	helpx = new CStaticSprite("helpx");
	help = new CStaticSprite("help");
	phbbb = new CStaticSprite("phbbb");
	phbx = new CStaticSprite("phbx");
	phb = new CStaticSprite("phb");
	time1 = new CTextSprite("time1");
	time2 = new CTextSprite("time2");
	time3 = new CTextSprite("time3");
	time4 = new CTextSprite("time4");
	time5 = new CTextSprite("time5");

	config1 = false;
	config2 = false;
	config3 = false;
	config4 = false;
	config5 = false;
	config6 = false;
	config7 = false;
	m_iGameState = 0;//设置游戏模式为1
	human.push_back(cat);
	human.push_back(mouse);

}

CGameMain::~CGameMain()
{
	
}

void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{		
	case 1:
	{
		SetGameState(2); // 将游戏状态设置为进行中
		break;
	}
	case 2:// 游戏进行中
	{		
		if(human[nowhuman]->hp>0)//如果老鼠的体力大于0
		{
			GameRun( fDeltaTime );
		}
		else // 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
		{				
			SetGameState(0);
			GameEnd();
		}
		break;
	}
	case 0://主界面内容
	{
		GameInit();
	}
	default:
		break;
	};

	
}



//=============================================================================
//
// 主界面设置内容
void CGameMain::GameInit()
{
	if (nowhuman == 1)
	{
		nowhumansta = "bulumouse_staticAnimation";
		nowhumanrun = "bulumouse_runAnimation";
		nowhumanatt = mouse_att_eff;
	}
	if (nowhuman == 0)
	{
		nowhumansta = "bulucat_staticAnimation";
		nowhumanrun = "bulucat_runAnimation";
		nowhumanatt = cat_att_eff;
	}
	

	//设置老鼠的世界边界
	human[nowhuman]->SetSpriteWorldLimit(WORLD_LIMIT_NULL, CSystem::GetScreenLeft(), CSystem::GetScreenTop(), CSystem::GetScreenRight(), CSystem::GetScreenBottom());
	human[nowhuman]->hp = 2000;
	human[nowhuman]->SetSpriteCollisionSend(true);
	human[nowhuman]->SetSpriteCollisionReceive(true);
	//载入主界面
	mainmap->SetSpritePosition(0.f, 0.f);
	first->SetSpritePosition(mainmap->GetSpriteLinkPointPosX(1), mainmap->GetSpriteLinkPointPosY(1));
	second->SetSpritePosition(mainmap->GetSpriteLinkPointPosX(2), mainmap->GetSpriteLinkPointPosY(2));
	third->SetSpritePosition(mainmap->GetSpriteLinkPointPosX(3), mainmap->GetSpriteLinkPointPosY(3));
	menu->SetSpritePosition(mainmap->GetSpriteLinkPointPosX(6), mainmap->GetSpriteLinkPointPosY(6));
	button_bb->SetSpritePosition(mainmap->GetSpriteLinkPointPosX(7), mainmap->GetSpriteLinkPointPosY(7));
	button_cj->SetSpritePosition(mainmap->GetSpriteLinkPointPosX(8), mainmap->GetSpriteLinkPointPosY(8));
	xzrw->SetSpritePosition(mainmap->GetSpriteLinkPointPosX(9), mainmap->GetSpriteLinkPointPosY(9));
	helpbb->SetSpritePosition(mainmap->GetSpriteLinkPointPosX(10), mainmap->GetSpriteLinkPointPosY(10));
	phbbb->SetSpritePosition(mainmap->GetSpriteLinkPointPosX(11), mainmap->GetSpriteLinkPointPosY(11));
	//隐藏地图与相关人物，使其不出现在主界面
	bossx->SetSpritePosition(-200, -29);
	map->SetSpritePosition(122.f, 147.f);
	humant->SetSpritePosition(-200.f, -26.f);
	if(bagopen!=true)
		human[nowhuman]->SetSpritePosition(-79.f, -81.f);
	human[nowhuman]->up = false;
	if (nowhuman == 1)
	{
		SetAnimalbase(2000, 1000, 100, 10);
	}
	else if(nowhuman==0)
	{
		SetAnimalbase(3000, 500, 100, 10);
	}

	human[nowhuman]->AnimateSpritePlayAnimation(nowhumansta, true);
	//如果小怪容器内有怪物，全部删除
	if (smalldog.size() != 0)
	{
		for (int i = 0; i < smalldog.size(); i++)
		{
			smalldog[i]->DeleteSprite();
			
		}
		smalldog.clear();
	}
	//如果有boss，全部删除
	if (boss != NULL)
	{
		boss->DeleteSprite();
		boss = NULL;
		bosstj = 0;
	}
	score = GetScore();
	ViewScore(score);
	PlayMp3();
	
}




//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{
	int bossattedlink;//boss的链接点位置,为boss的攻击区域（链接点为funcode属性）
	int smallbossattedlink;//小怪的链接点位置

	

	switch (Now)
	{
	case 1:
	{
		smallbossattedlink=3;
		bossattedlink = 4;

	}
	case 2:
	{
		smallbossattedlink = 4;
		bossattedlink = 4;
	}
	case 3:
	{
		smallbossattedlink = 1;
		bossattedlink = 4;
	}
	}
	//老鼠游戏内容
	totaltime += fDeltaTime;
	AnimalChangdirect(human[nowhuman]);//自动调整老鼠方向
	AnimalJump(human[nowhuman], fDeltaTime, -human[nowhuman]->GetSpritePositionY() - 10, 25, 2, 1);//自动判断是否跳跃
	
	tmptime -= fDeltaTime;//回血回蓝倒计时
	if (tmptime < 0)//判断倒计时是否结束
	{
		if (human[nowhuman]->mp < 1000)
			human[nowhuman]->mp += 10;
		if (human[nowhuman]->hp < 2000)
			human[nowhuman]->hp += 10;
		tmptime = 1;
	}
	
	//CSystem::DrawLine(sshp->GetSpriteLinkPointPosX(1), sshp->GetSpriteLinkPointPosY(1), sshp->GetSpriteLinkPointPosX(1) + Calculhp(2000, human[nowhuman]->hp, 17), sshp->GetSpriteLinkPointPosY(2), 8, 0, 255, 0, 0, 255);
	if (nowhuman == 1)
	{
		string temp = std::to_string(human[nowhuman]->hp) + "/2000";
		sshpt->SetTextString(temp.c_str());
		//CSystem::DrawLine(ssmp->GetSpriteLinkPointPosX(1), ssmp->GetSpriteLinkPointPosY(1), ssmp->GetSpriteLinkPointPosX(1) + Calculhp(1000, human[nowhuman]->mp, 17), ssmp->GetSpriteLinkPointPosY(2), 8, 0, 56, 0, 255, 255);
		string temp1 = std::to_string(human[nowhuman]->mp) + "/1000";
		ssmpt->SetTextString(temp1.c_str());
	}
	else if (nowhuman == 0)
	{
		string temp = std::to_string(human[nowhuman]->hp) + "/3000";
		sshpt->SetTextString(temp.c_str());
		//CSystem::DrawLine(ssmp->GetSpriteLinkPointPosX(1), ssmp->GetSpriteLinkPointPosY(1), ssmp->GetSpriteLinkPointPosX(1) + Calculhp(1000, human[nowhuman]->mp, 17), ssmp->GetSpriteLinkPointPosY(2), 8, 0, 56, 0, 255, 255);
		string temp1 = std::to_string(human[nowhuman]->mp) + "/500";
		ssmpt->SetTextString(temp1.c_str());
	}
	if (smalldog.size() > 0)//如果有小怪，老鼠的攻击模式包括小怪
	{
		for (int i = 0; i < smalldog.size(); i++)
		{
			AnimalModeChange(human[nowhuman], nowhumansta, nowhumanrun, nowhumanatt, smalldog[i],jn1,jn2,smalldog);
		}
	}
	else
	{
		if (boss != NULL)//如果有boss，老鼠的攻击模式包括boss
		{
			AnimalModeChange(human[nowhuman], nowhumansta, nowhumanrun,nowhumanatt, boss,jn1,jn2,smalldog);
		}
		else//如果都没有，老鼠无法进入攻击模式
		{
			AnimalModeChange(human[nowhuman], nowhumansta, nowhumanrun,nowhumanatt);
		}

	}
	CSystem::DrawLine(human[nowhuman]->GetSpriteLinkPointPosX(2), human[nowhuman]->GetSpriteLinkPointPosY(2), human[nowhuman]->GetSpriteLinkPointPosX(2) + Calculhp(2000, human[nowhuman]->hp, 5), human[nowhuman]->GetSpriteLinkPointPosY(2), 5, 0, 255, 0, 0, 255);//画老鼠血条
	//小怪游戏内容
	if (produce > 0)//如果小怪还没生产完
	{
		switch (rand() % 6)
		{
		case 0:
			smallbossname = "sdog"; break;
		case 1:
			smallbossname = "scat"; break;
		case 2:
			smallbossname = "sjcat"; break;
		case 3:
			smallbossname = "xg1"; break;
		case 4:
			smallbossname = "xg2"; break;
		case 5:
			smallbossname = "xg3"; break;
		}
		leftovertime -= fDeltaTime;//倒计时
		if (leftovertime < 0)//判断倒计时是否结束
		{
			ProduceDog(5 - produce, smallbossname, map->GetSpriteLinkPointPosX(4), map->GetSpriteLinkPointPosY(4));//产生小怪
			leftovertime = 2;//倒计时重新设置为2s
			produce--;//生产小怪数减一
		}
	}
	lefttime -= fDeltaTime;//倒计时
	guanqia->SetSpritePosition(0,  - (lefttime ) * 30);
	if (lefttime < 0)//判断倒计时是否结束
	{
		debug->SetTextValue(1);
		guanqia->SetSpritePosition(-200, 0);
	}
	for (int i = 0; i < smalldog.size(); i++)//对所有的小怪进行检索
	{
		//自动调整小怪方向
		AnimalChangdirect(smalldog[i]);
		//画血条
		AnimalDrawline(smalldog[i], 1000, 5);
		//小怪攻击范围调整
		Recangle attrange;
		attrange.left = human[nowhuman]->GetSpriteLinkPointPosX(3) - 6;
		attrange.right = human[nowhuman]->GetSpriteLinkPointPosX(3) + 6;
		attrange.top = human[nowhuman]->GetSpriteLinkPointPosY(3) - 6;
		attrange.botton = human[nowhuman]->GetSpriteLinkPointPosY(3) + 6;
		if (Ismouseinrange(smalldog[i]->GetSpriteLinkPointPosX(smallbossattedlink), smalldog[i]->GetSpriteLinkPointPosY(smallbossattedlink), attrange))
		{
			human[nowhuman]->hp -= smalldog[i]->att;
		}
		//小怪死亡后
		if (smalldog[i]->hp < 0)
		{
			//移除小怪精灵
			smalldog[i]->DeleteSprite();
			//小怪容器内删除指导元素
			vector<Animal*>::iterator   iter = smalldog.begin() + i;
			smalldog.erase(iter);
		}
	}

	/*
	boss游戏内容
	*/
	
	//boss生成范围调整
	Recangle bossrange;
	bossrange.left = map->GetSpriteLinkPointPosX(5) - 6;
	bossrange.right = map->GetSpriteLinkPointPosX(5) + 6;
	bossrange.top = map->GetSpriteLinkPointPosY(5) - 6;
	bossrange.botton = map->GetSpriteLinkPointPosY(5) + 6;
	
	if (boss == NULL)//boss不存在
	{
		//如果人物进入了boss生成范围
		bossx->SetSpritePosition(-200, -20);
		if (Ismouseinrange(human[nowhuman]->GetSpritePositionX(), human[nowhuman]->GetSpritePositionY(), bossrange) &&bosstj!=1)
		{
			//boss初始化
			if (Now == 1)
			{
				boss = ProduceBoss(1, bossname, map->GetSpriteLinkPointPosX(5) + 50, map->GetSpriteLinkPointPosY(5));
				boss->hp = 5000;
				boss->att = 100;
				bosstj = 1;
			}
			else if(Now == 2)
			{
				boss = ProduceBoss(1, bossname, map->GetSpriteLinkPointPosX(5) + 50, map->GetSpriteLinkPointPosY(5) - 15);
				boss->hp = 5000;
				boss->att = 100;
				bosstj = 1;
			}
			else if(Now==3)
			{
				boss = ProduceBoss(1, bossname, map->GetSpriteLinkPointPosX(5) + 50, map->GetSpriteLinkPointPosY(5)-25);
				boss->hp = 5000;
				boss->att = 100;
				bosstj = 1;
			}
		}
	}

	if (boss != NULL)//boss存在
	{
		AnimalDrawline(boss, 5000, 20);
		if(Now==1)
			bosst->SetStaticSpriteImage("dogtImageMap", 0);
		else if(Now==2)
			bosst->SetStaticSpriteImage("chushitImageMap", 0);
		else if (Now == 3)
			bosst->SetStaticSpriteImage("nvtImageMap", 0);

		bossx->SetSpritePosition(2, -29);
		CSystem::DrawLine(bossx->GetSpriteLinkPointPosX(1), bossx->GetSpriteLinkPointPosY(1), bossx->GetSpriteLinkPointPosX(1) + Calculhp(5000, boss->hp, 53), bossx->GetSpriteLinkPointPosY(2), 8, 0, 255, 0, 0, 255);
		Recangle attrange;
		attrange.left = human[nowhuman]->GetSpriteLinkPointPosX(4) - 6;
		attrange.right = human[nowhuman]->GetSpriteLinkPointPosX(4) + 6;
		attrange.top = human[nowhuman]->GetSpriteLinkPointPosY(4) - 6;
		attrange.botton = human[nowhuman]->GetSpriteLinkPointPosY(4) + 6;
		if (Ismouseinrange(boss->GetSpriteLinkPointPosX(bossattedlink), boss->GetSpriteLinkPointPosY(bossattedlink), attrange))
		{
			mouse->hp -= boss->att;
		}
		if (boss->hp < 0)
		{
			if(strcmp(bossname,"bossdog1")==0)
				Setachievement("one", 1);
			if (strcmp(bossname, "boss2") == 0)
				Setachievement("two", 1);
			if (strcmp(bossname, "nvzhuren") == 0)
				Setachievement("three", 1);
			boss->DeleteSprite();
			boss = NULL;
			GameEnd();
		}
	}
	config1 = Getachievement("one", 1);
	config2 = Getachievement("two", 1);
	config3 = Getachievement("three", 1);
	config4 = Getachievement("four", 50);
	config5 = Getachievement("five", 2);
	config6 = Getachievement("six", 1);
	config7 = Getachievement("seven", 1);

}


//=============================================================================
//
// 本局游戏结束
void CGameMain::GameEnd()
{
	if (human[nowhuman]->hp > 0)//人物存活
	{
		if (Now != 3)//当前不是最后一关
		{
			grey->SetSpritePosition(0, 0);
			gameback->SetSpritePosition(grey->GetSpriteLinkPointPosX(2), grey->GetSpriteLinkPointPosY(2));
			gamenext->SetSpritePosition(grey->GetSpriteLinkPointPosX(3), grey->GetSpriteLinkPointPosY(3));
			tongguan->SetSpritePosition(grey->GetSpriteLinkPointPosX(4), grey->GetSpriteLinkPointPosY(4));
		}
		else//当前为最后一关
		{
			grey->SetSpritePosition(0, 0);
			gameback->SetSpritePosition(grey->GetSpriteLinkPointPosX(2), grey->GetSpriteLinkPointPosY(2));
			tongguan->SetSpritePosition(grey->GetSpriteLinkPointPosX(4), grey->GetSpriteLinkPointPosY(4));
		}
		SetScore(totaltime, score);
	}
	else//人物阵亡
	{
		
			grey->SetSpritePosition(0, 0);
			gameback->SetSpritePosition(grey->GetSpriteLinkPointPosX(2), grey->GetSpriteLinkPointPosY(2));
			gameover->SetSpritePosition(0, 0);
		
	}
	//清空小怪容器
	if (smalldog.size() != 0)
	{
		for (int i = 0; i < smalldog.size(); i++)
		{
			smalldog[i]->DeleteSprite();

		}
		smalldog.clear();
	}
	//清空boss
	if (boss != NULL)
	{
		boss->DeleteSprite();
		boss = NULL;
		bosstj = 0;
	}
	totalt->SetTextValueFloat(totaltime);
	

}


//==========================================================================
//
// 鼠标移动
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseMove(const float fMouseX, const float fMouseY)
{
	//基本按钮
	BottonView(first, fMouseX, fMouseY, "zc_guan1ImageMap", "dr_guan1ImageMap");
	BottonView(second, fMouseX, fMouseY, "zc_guan2ImageMap", "dr_guan2ImageMap");
	BottonView(third, fMouseX, fMouseY, "zc_guan3ImageMap", "dr_guan3ImageMap");
	BottonView(menu, fMouseX, fMouseY, "menu6ImageMap", "menu3ImageMap");//
	BottonView(button_cj, fMouseX, fMouseY, "cj1ImageMap", "cj2ImageMap");
	BottonView(button_bb, fMouseX, fMouseY, "bb1ImageMap", "bb2ImageMap");
	BottonView(helpbb, fMouseX, fMouseY, "helpbb1ImageMap", "helpbbImageMap");
	BottonView(phbbb, fMouseX, fMouseY, "phbbb1ImageMap", "phbbb2ImageMap");
	BottonView(menu1, fMouseX, fMouseY, "button9ImageMap", "button10ImageMap");
	BottonView(menu2, fMouseX, fMouseY, "button9ImageMap", "button10ImageMap");
	BottonView(menu3, fMouseX, fMouseY, "button9ImageMap", "button10ImageMap");
	BottonView(gameback, fMouseX, fMouseY, "button9ImageMap", "button10ImageMap");
	BottonView(gamenext, fMouseX, fMouseY, "button9ImageMap", "button10ImageMap");
	BottonView(xzrw, fMouseX, fMouseY, "button9ImageMap", "button10ImageMap");
	//成就点亮
	
	BottonView(cjd1, fMouseX, fMouseY, "dian3ImageMap", "dian2ImageMap", config1);
	BottonView(cjd2, fMouseX, fMouseY, "dian3ImageMap", "dian2ImageMap", config2);
	BottonView(cjd3, fMouseX, fMouseY, "dian3ImageMap", "dian2ImageMap", config3);
	BottonView(cjd4, fMouseX, fMouseY, "dian3ImageMap", "dian2ImageMap", config4);
	BottonView(cjd5, fMouseX, fMouseY, "dian3ImageMap", "dian2ImageMap", config5);
	BottonView(cjd6, fMouseX, fMouseY, "dian3ImageMap", "dian2ImageMap", config6);
	BottonView(cjd7, fMouseX, fMouseY, "dian3ImageMap", "dian2ImageMap", config7);

}


//==========================================================================
//
// 鼠标点击
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标


void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(first)))//第一关按钮被按下
	{
		Init(1, "pic1ImageMap", "bossdog1", "sdog");
	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(second)))//第二关按钮被按下
	{
		Init(2, "pic2ImageMap", "boss2", "scat");
	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(third)))//第三关按钮被按下
	{
		Init(3, "map3", "nvzhuren", "sjcat");
	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(menu)))//菜单按钮被按下
	{
		mainmenu->SetSpritePosition(0.f, 0.f);
		menu1->SetSpritePosition(mainmenu->GetSpriteLinkPointPosX(1), mainmenu->GetSpriteLinkPointPosY(1));
		menu2->SetSpritePosition(mainmenu->GetSpriteLinkPointPosX(2), mainmenu->GetSpriteLinkPointPosY(2));
		menu3->SetSpritePosition(mainmenu->GetSpriteLinkPointPosX(3), mainmenu->GetSpriteLinkPointPosY(3));

	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(menu1)))//回到游戏按钮被按下
	{
		mainmenu->SetSpritePosition(-141.f, 53.f);
		menu1->SetSpritePosition(mainmenu->GetSpriteLinkPointPosX(1), mainmenu->GetSpriteLinkPointPosY(1));
		menu2->SetSpritePosition(mainmenu->GetSpriteLinkPointPosX(2), mainmenu->GetSpriteLinkPointPosY(2));
		menu3->SetSpritePosition(mainmenu->GetSpriteLinkPointPosX(3), mainmenu->GetSpriteLinkPointPosY(3));
	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(menu2)))//退出游戏按钮被按下
	{
		exit(0);
	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(menu3)))//回到主界面按钮被按下
	{
		GameInit();
		mainmenu->SetSpritePosition(-141.f, 53.f);
		cj1->SetSpritePosition(-141.f, 53.f);
		menu1->SetSpritePosition(mainmenu->GetSpriteLinkPointPosX(1), mainmenu->GetSpriteLinkPointPosY(1));
		menu2->SetSpritePosition(mainmenu->GetSpriteLinkPointPosX(2), mainmenu->GetSpriteLinkPointPosY(2));
		menu3->SetSpritePosition(mainmenu->GetSpriteLinkPointPosX(3), mainmenu->GetSpriteLinkPointPosY(3));
	}if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(gameback)))//回到主界面按钮被按下
	{
		GameInit();
		grey->SetSpritePosition(-141.f, 53.f);
		gameback->SetSpritePosition(grey->GetSpriteLinkPointPosX(1), grey->GetSpriteLinkPointPosY(1));
		gamenext->SetSpritePosition(grey->GetSpriteLinkPointPosX(2), grey->GetSpriteLinkPointPosY(2));
		tongguan->SetSpritePosition(grey->GetSpriteLinkPointPosX(3), grey->GetSpriteLinkPointPosY(3));
		gameover->SetSpritePosition(grey->GetSpriteLinkPointPosX(3), grey->GetSpriteLinkPointPosY(3));

	}if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(gamenext)))//下一关按钮被按下
	{
		if (Now == 1)//如果当前是第一关
		{
			Init(2, "map2", "boss2", "scat");
			return;
		}
		else if (Now == 2)//如果当前是第二关
		{
			Init(3, "map3", "nvzhuren", "sjcat");
			return;
		}
		grey->SetSpritePosition(-141.f, 53.f);
		gameback->SetSpritePosition(grey->GetSpriteLinkPointPosX(1), grey->GetSpriteLinkPointPosY(1));
		gamenext->SetSpritePosition(grey->GetSpriteLinkPointPosX(2), grey->GetSpriteLinkPointPosY(2));
		tongguan->SetSpritePosition(grey->GetSpriteLinkPointPosX(3), grey->GetSpriteLinkPointPosY(3));
		gameover->SetSpritePosition(grey->GetSpriteLinkPointPosX(3), grey->GetSpriteLinkPointPosY(3));
	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(button_cj)))//成就按钮被按下
	{
		cj1->SetSpritePosition(0.f, 0.f);

	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(helpbb)))//帮助按钮被按下
	{
		help->SetSpritePosition(0.f, 0.f);

	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(phbbb)))//排行榜按钮被按下
	{
		phb->SetSpritePosition(0.f, 0.f);
		score = GetScore();
		ViewScore(score);

	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(button_bb)))//背包按钮被按下
	{
		bb->SetSpritePosition(0.f, 0.f);
		human[nowhuman]->changechaoxiang = "right";
		human[nowhuman]->SetSpritePosition(bb1->GetSpriteLinkPointPosX(1)-5, bb1->GetSpriteLinkPointPosY(1));
		human[nowhuman]->AnimateSpritePlayAnimation(nowhumansta, true);
		bagopen = true;
	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(helpx)))//关闭帮助按钮
	{
		help->SetSpritePosition(-200.f, 0.f);

	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(phbx)))//关闭排行榜按钮
	{
		phb->SetSpritePosition(-200.f, 0.f);

	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(bbx)))//关闭背包按钮
	{
		bb->SetSpritePosition(-200.f, 0.f);
		human[nowhuman]->SetSpritePosition(bb1->GetSpriteLinkPointPosX(1), bb1->GetSpriteLinkPointPosY(1));
		bagopen = false;

	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(cjx)))//关闭成就按钮
	{
		cj1->SetSpritePosition(-200.f, 0.f);
	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(xzrw)))//选择人物按钮
	{
		xzrwjm->SetSpritePosition(-0.f, 0.f);
		mouse->SetSpritePosition(xzrwjm->GetSpriteLinkPointPosX(1), xzrwjm->GetSpriteLinkPointPosY(1));
		cat->SetSpritePosition(xzrwjm->GetSpriteLinkPointPosX(2), xzrwjm->GetSpriteLinkPointPosY(2));
		bagopen = true;
	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(mouse)))
	{
		nowhuman = 1;
		xzrwjm->SetSpritePosition(-200.f, 0.f);
		mouse->SetSpritePosition(-200,0);
		cat->SetSpritePosition(-200,0);
		bagopen = false;
	}
	if (Ismouseinrange(fMouseX, fMouseY, Getanimalrange(cat)))
	{
		nowhuman = 0;
		xzrwjm->SetSpritePosition(-200.f, 0.f);
		mouse->SetSpritePosition(-200, 0);
		cat->SetSpritePosition(-200, 0);
		bagopen = false;
	}

	
	
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
		fSpeedX = -40.f;	//向左的时候X方向的速度为负值
		human[nowhuman]->mode = 1;
		human[nowhuman]->animation = nowhumanrun;
		human[nowhuman]->changechaoxiang = "left";
		break;
	case KEY_S:
		fSpeedY = 10.f; //向下的时候Y方向的速度为正值
		break;
	case KEY_D:
		fSpeedX = 40.f;//向右的时候X方向的速度为正值
		human[nowhuman]->mode = 1;
		human[nowhuman]->animation = nowhumanrun;;
		human[nowhuman]->changechaoxiang = "right";
		break;
	case KEY_J:
		human[nowhuman]->mode = 2;
		break;
	case KEY_U:
		human[nowhuman]->mode = 4;
		break;
	case KEY_I:
		human[nowhuman]->mode = 5;
		break;
	case KEY_K:
		human[nowhuman]->jumptime = 0;
		human[nowhuman]->up = true;
		human[nowhuman]->down = false;
		break;
	}

	human[nowhuman]->SetSpriteLinearVelocity(fSpeedX, fSpeedY);

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
	{ fSpeedX = 0.f; fSpeedY = 0.f; human[nowhuman]->mode = 3; human[nowhuman]->animation = nowhumansta; break; }
	case KEY_A:
	{ fSpeedX = 0.f; fSpeedY = 0.f;human[nowhuman]->mode = 3; human[nowhuman]->animation = nowhumansta; break; }
	case KEY_S:
	{ fSpeedX = 0.f; fSpeedY = 0.f;human[nowhuman]->mode = 3; human[nowhuman]->animation = nowhumansta; break; }
	case KEY_D:
	{ fSpeedX = 0.f; fSpeedY = 0.f; human[nowhuman]->mode = 3; human[nowhuman]->animation = nowhumansta; break; }
	}
	//cat->sta = true;
	human[nowhuman]->SetSpriteLinearVelocity(fSpeedX, fSpeedY);

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
//AnimalColWorld(cat, map, iColSide, "cat", szName, 117, 13);	
	if(nowhuman==1)
		AnimalColWorld(human[nowhuman], map, iColSide, "mouse", szName, 117, 20);
	else if(nowhuman==0)
		AnimalColWorld(human[nowhuman], map, iColSide, "cat", szName, 117, 13);
	for (int i = 0; i < smalldog.size(); i++)
	{
		Animal *tmp = smalldog[i];
		AutoColWorld(tmp, map, iColSide,tmp->GetName(), szName);
	}
	if (boss != NULL)
	{
		Animal *tmp = boss;
		AutoColWorld(tmp, map, iColSide, tmp->GetName(), szName);
	}
}

