
#include "Catfunction.h"






/*
Getanimalrange:获取精灵的范围
参数：
animal:对应精灵的地址
返回值：
recangle：精灵的上下左右四个边界值
*/
Recangle Getanimalrange(Animal *animal)
{
	Recangle recangle;
	recangle.left = animal->GetSpritePositionX() - animal->GetSpriteWidth() / 2;
	recangle.right = animal->GetSpritePositionX() + animal->GetSpriteWidth() / 2;
	recangle.top = animal->GetSpritePositionY() - animal->GetSpriteHeight() / 2;
	recangle.botton = animal->GetSpritePositionY() + animal->GetSpriteHeight() / 2;
	return recangle;
}

Recangle Getanimalrange(CSprite *animal)
{
	Recangle recangle;
	recangle.left = animal->GetSpritePositionX() - animal->GetSpriteWidth() / 2;
	recangle.right = animal->GetSpritePositionX() + animal->GetSpriteWidth() / 2;
	recangle.top = animal->GetSpritePositionY() - animal->GetSpriteHeight() / 2;
	recangle.botton = animal->GetSpritePositionY() + animal->GetSpriteHeight() / 2;
	return recangle;
}

Recangle Getanimalrange(CStaticSprite *animal)
{
	Recangle recangle;
	recangle.left = animal->GetSpritePositionX() - animal->GetSpriteWidth() / 2;
	recangle.right = animal->GetSpritePositionX() + animal->GetSpriteWidth() / 2;
	recangle.top = animal->GetSpritePositionY() - animal->GetSpriteHeight() / 2;
	recangle.botton = animal->GetSpritePositionY() + animal->GetSpriteHeight() / 2;
	return recangle;
}
Recangle Getanimalrange(CEffect *animal)
{
	Recangle recangle;
	recangle.left = animal->GetSpritePositionX() - animal->GetSpriteWidth() / 2;
	recangle.right = animal->GetSpritePositionX() + animal->GetSpriteWidth() / 2;
	recangle.top = animal->GetSpritePositionY() - animal->GetSpriteHeight() / 2;
	recangle.botton = animal->GetSpritePositionY() + animal->GetSpriteHeight() / 2;
	return recangle;
}

/*
Ismouseinrange:判断某坐标是否在某个范围内
参数：
MouseX:横坐标
MouseY:纵坐标
range :某范围
返回值：
true ：在此范围
false：不在此范围
*/
bool Ismouseinrange(float MouseX, float MouseY, Recangle range)
{
	if ((MouseX > range.left && MouseX < range.right) && (MouseY > range.top && MouseY < range.botton))
		return true;
	else
		return false;
}
/*
BottonView:如果鼠标在精灵范围内，自动更换另一张图片（放进OnMouseMove函数内即可实现按钮效果）
参数:
sprite:精灵的地址
mousex:横坐标
mousey:纵坐标
zctp  :坐标不在范围内显示的图片名称
drtp  :坐标在范围内显示的图片名称
*/
bool BottonView(CStaticSprite *sprite, float mousex, float mousey, const char* zctp, const char* drtp,bool config)
{
	if (Ismouseinrange(mousex, mousey, Getanimalrange(sprite)))//如果坐标在范围内
	{
		sprite->SetStaticSpriteImage(drtp, 0);//精灵更换名字为（drtp（传入的图片名称））的图片
		return true;
	}
	else
	{
		if (config == false)
		{
			sprite->SetStaticSpriteImage(zctp, 0);//精灵更换名字为（zctp（传入的图片名称））的图片
			return false;
		}
		else { sprite->SetStaticSpriteImage(drtp, 0); return true; }
	}
}
/*
CalculY:计算加速度对路程改变量
参数:
v0:初速度
t :衰减时间
a :加速度大小
*/
float CalculY(float v0, float t,float a)
{
	return (v0 * t) - (a * t*t / 2);
}
/*
Calculhp:计算当前血条长度
参数:
totalhp:精灵总血量
nowhp  :精灵当前血量
length :血条长度（总血量）
*/
float Calculhp(float totalhp, float nowhp, float length)
{
	return (nowhp / totalhp)*length;
}
/*
AnimalJump:精灵跳跃（放进gamerun函数内）
参数:
animal    :进行跳跃操作的精灵的地址
fDeltaTime:引擎刷新屏幕的时间差
heigh     :跳跃的最高位置
bottom    :地面的位置
v0        :初速度
a         :加速度
*/
void AnimalJump(Animal *animal, float fDeltaTime,float heigh,float bottom,float v0,float a)
{
	if (animal->up == true && animal->down == false)//精灵当前为跳起状态而不是落下状态
	{
		animal->jumptime += fDeltaTime;//计算跳跃持续时间
		animal->SetSpritePositionY(animal->GetSpritePositionY() - CalculY(v0, animal->jumptime, a));//动态设置精灵位置
		if (animal->GetSpritePositionY() < heigh)//如果到达顶点
		{
			animal->up = false;
			animal->down = true;
			animal->jumptime = 0;//更新跳跃持续时间进入落下状态
		}
	}
	else if (animal->up == false && animal->down == true)//精灵当前为落下状态而不是跳起状态
	{
		animal->jumptime += fDeltaTime;
		animal->SetSpritePositionY(animal->GetSpritePositionY() + CalculY(v0, animal->jumptime, a));
		if (animal->GetSpritePositionY() > bottom)
		{
			animal->SetSpritePositionY(bottom);
			animal->jumptime = 0;
			animal->down = false;//精灵不在空中
		}
	}

}
/*
AnimalModeChange:精灵不同模式执行不同操作（1：移动模式；2：攻击模式；3：静止模式）
参数：
animal:精灵的地址
sta   :精灵静止时播放的图片名称
run   :精灵移动时播放的图片名称
att   :精灵的攻击效果的地址
god   :被攻击的怪物的地址
*/
void AnimalModeChange(Animal *animal, const char*sta, const char*run, CEffect *att,Animal *god,CEffect *jn1, CEffect *jn2, vector<Animal*>gg)
{
	if (animal->mode == 1)//移动模式
	{
		if (strcmp(animal->animation, run) == 0)//如果精灵当前动画为移动动画
		{
			if (animal->IsAnimateSpriteAnimationFinished())//如果精灵当前动画播放完毕
			{
				animal->AnimateSpritePlayAnimation(run, true);//播放移动动画
			}
		}
		else//如果精灵当前动画不为移动动画
		{
			animal->AnimateSpritePlayAnimation(run, true);//播放移动动画
		}

	}
	else if (animal->mode == 2)//攻击模式
	{
		char *tmpchar;//临时字符串
		tmpchar = CSystem::MakeSpriteName("eff", 1);//临时字符串命名
		Animal *tmp = new Animal(tmpchar);//临时攻击判断用指针
		att->PlayEffect(animal->GetSpriteLinkPointPosX(1), animal->GetSpriteLinkPointPosY(1), 0);//播放攻击特效
		tmp->CloneSprite("mouse_att_eff");//克隆攻击特效到临时攻击判断用指针
		tmp->SetSpritePosition(animal->GetSpriteLinkPointPosX(1), animal->GetSpriteLinkPointPosY(1));//将临时攻击判断用指针与攻击特效放在同一个位置
		Recangle attrange;//临时攻击范围
		attrange.left = tmp->GetSpriteLinkPointPosX(3) - 6;
		attrange.right = tmp->GetSpriteLinkPointPosX(3) + 6;
		attrange.top = tmp->GetSpriteLinkPointPosY(3) - 6;
		attrange.botton = tmp->GetSpriteLinkPointPosY(3) + 6;
		if (Ismouseinrange(god->GetSpriteLinkPointPosX(3), god->GetSpriteLinkPointPosY(3), attrange))//如果怪物的被攻击点（第三个链接点）在攻击范围内
		{
			god->hp -= animal->att;//怪物掉血
		}
		tmp->DeleteSprite();//删除临时攻击判断用指针
		delete tmp;

	}
	else if (animal->mode == 3)//静止模式
	{
		if (strcmp(animal->animation, sta) == 0)
		{

			if (animal->IsAnimateSpriteAnimationFinished())
			{
				animal->AnimateSpritePlayAnimation(sta, true);

			}
		}
		else
		{

			animal->AnimateSpritePlayAnimation(sta, true);
		}


	}
	else if (animal->mode == 4)//技能1
	{
		if ((animal->mp - 100) > 0)
		{
			animal->mp -= 100;
			PlaySound("shasha.wav", NULL, SND_FILENAME | SND_ASYNC);
			char *tmpchar;//临时字符串
			tmpchar = CSystem::MakeSpriteName("eff", 1);//临时字符串命名
			Animal *tmp = new Animal(tmpchar);//临时攻击判断用指针
			jn1->PlayEffect(animal->GetSpriteLinkPointPosX(1), animal->GetSpriteLinkPointPosY(1), 0);//播放攻击特效
			tmp->CloneSprite("steam");//克隆攻击特效到临时攻击判断用指针
			tmp->SetSpritePosition(animal->GetSpriteLinkPointPosX(1), animal->GetSpriteLinkPointPosY(1));//将临时攻击判断用指针与攻击特效放在同一个位置
			Recangle attrange;//临时攻击范围
			attrange.left = tmp->GetSpriteLinkPointPosX(3) - 30;
			attrange.right = tmp->GetSpriteLinkPointPosX(3) + 30;
			attrange.top = tmp->GetSpriteLinkPointPosY(3) - 30;
			attrange.botton = tmp->GetSpriteLinkPointPosY(3) + 30;
			for (int i = 0; i < gg.size(); i++)
			{
				if (Ismouseinrange(gg[i]->GetSpriteLinkPointPosX(3), gg[i]->GetSpriteLinkPointPosY(3), attrange))//如果怪物的被攻击点（第三个链接点）在攻击范围内
				{
					gg[i]->hp -= 400;//怪物掉血
				}
			}
			tmp->DeleteSprite();//删除临时攻击判断用指针
			delete tmp;
			animal->mode = 3;
		}

	}
	else if (animal->mode == 5)//技能2
	{
		if ((animal->mp - 300) > 0)
		{
			animal->mp -= 300;
			PlaySound("boom.wav", NULL, SND_FILENAME | SND_ASYNC);
			char *tmpchar;//临时字符串
			tmpchar = CSystem::MakeSpriteName("eff", 1);//临时字符串命名
			Animal *tmp = new Animal(tmpchar);//临时攻击判断用指针
			jn2->PlayEffect(animal->GetSpriteLinkPointPosX(1), animal->GetSpriteLinkPointPosY(1), 0);//播放攻击特效
			tmp->CloneSprite("miaosha");//克隆攻击特效到临时攻击判断用指针
			tmp->SetSpritePosition(animal->GetSpriteLinkPointPosX(1), animal->GetSpriteLinkPointPosY(1));//将临时攻击判断用指针与攻击特效放在同一个位置
			Recangle attrange;//临时攻击范围
			attrange.left = tmp->GetSpriteLinkPointPosX(3) - 10;
			attrange.right = tmp->GetSpriteLinkPointPosX(3) + 10;
			attrange.top = tmp->GetSpriteLinkPointPosY(3) - 10;
			attrange.botton = tmp->GetSpriteLinkPointPosY(3) + 10;
			for (int i = 0; i < gg.size(); i++)
			{
				if (Ismouseinrange(gg[i]->GetSpriteLinkPointPosX(3), gg[i]->GetSpriteLinkPointPosY(3), attrange))//如果怪物的被攻击点（第三个链接点）在攻击范围内
				{
					gg[i]->hp -= 3000;//怪物掉血
				}
			}
			tmp->DeleteSprite();//删除临时攻击判断用指针
			delete tmp;
			animal->mode = 3;
		}

	}
}

void AnimalModeChange(Animal *animal, const char*sta, const char*run, CEffect *att)
{
	if (animal->mode == 1)
	{
		if (strcmp(animal->animation, run) == 0)
		{
			if (animal->IsAnimateSpriteAnimationFinished())
			{
				animal->AnimateSpritePlayAnimation(run, true);
			}
		}
		else
		{
			animal->AnimateSpritePlayAnimation(run, true);
		}

	}
	else if (animal->mode == 2)
	{

		att->PlayEffect(animal->GetSpriteLinkPointPosX(1), animal->GetSpriteLinkPointPosY(1), 0);

	}
	else if (animal->mode == 3)
	{
		if (strcmp(animal->animation, sta) == 0)
		{

			if (animal->IsAnimateSpriteAnimationFinished())
			{
				animal->AnimateSpritePlayAnimation(sta, true);

			}
		}
		else
		{

			animal->AnimateSpritePlayAnimation(sta, true);
		}


	}
}

/*
AnimalChangdirect:精灵改变朝向
参数:
animal:精灵的地址
*/
void AnimalChangdirect(Animal *animal)
{
	if (animal->changechaoxiang == "right")//如果精灵朝向为右
	{
		animal->SetSpriteFlipX(true);//更改朝向为右
		animal->nowchaoxiang = animal->changechaoxiang;//将精灵当前朝向设置为右
	}
	else
	{
		animal->SetSpriteFlipX(false);
	}
}
/*
AnimalColWorld:精灵碰撞地图后操作内容
参数：
animal    :精灵的地址
map       :背景的地址
iColSide  :碰撞到的边界 0 左边，1 右边，2 上边，3 下边
name      :精灵的名字
szName    :碰撞到边界的精灵名字
maprange  :地图大小
animalmove:精灵碰撞地图后边界自动后退的值
*/
void AnimalColWorld(Animal *animal,CStaticSprite *map,const int iColSide,const char*name,const char*szName,float maprange,float animalmove)
{
	if (strcmp(szName, name) == 0)
	{
		if (animal->GetSpriteLinearVelocityX() != 0)
		{
			switch (iColSide)
			{
			case 0:
			{
				if (map->GetSpritePositionX() >= -maprange && map->GetSpritePositionX() <= maprange)
				{
					if (map->GetSpritePositionX() == maprange)
						map->SetSpritePositionX(map->GetSpritePositionX());
					else
						map->SetSpritePositionX(map->GetSpritePositionX() + 1);
					animal->SetSpritePositionX(CSystem::GetScreenLeft() + animalmove);
				}
				break;
			}
			case 1:
			{
				if (map->GetSpritePositionX() >= -maprange && map->GetSpritePositionX() <= maprange)
				{
					if (map->GetSpritePositionX() == -maprange)
						map->SetSpritePositionX(map->GetSpritePositionX());
					else
						map->SetSpritePositionX(map->GetSpritePositionX() - 1);
					animal->SetSpritePositionX(CSystem::GetScreenRight() - animalmove);
				}
				break;
			}
			case 2:
			{
				
				break;
			}
			}
		}
	}
}
/*
AutoColWorld:精灵碰撞地图后自动操作（对怪物）
参数:
animal    :精灵的地址
map       :背景的地址
iColSide  :碰撞到的边界 0 左边，1 右边，2 上边，3 下边
name      :精灵的名字
szName    :碰撞到边界的精灵名字
*/
void AutoColWorld(Animal *animal, CStaticSprite *map, const int iColSide, const char*name, const char*szName)
{
	if (strcmp(szName, name) == 0)//如果目标精灵为碰撞精灵
	{
		if (animal->GetSpriteLinearVelocityX() != 0)//如果精灵速度不为0
		{
			switch (iColSide)//判断边界
			{
			case 0://左边
			{
				animal->changechaoxiang = "right";//朝向改为右
				AnimalChangdirect(animal);
				animal->SetSpriteLinearVelocity(10.f, 0);
				break;
			}
			case 1://右边
			{
				animal->changechaoxiang = "left";//朝向改为左
				AnimalChangdirect(animal);
				animal->SetSpriteLinearVelocity(-10.f, 0);
				break;
			}
			case 2:
			{

				break;
			}
			}
		}
	}
}
/*
AnimalDrawline
参数：
animal :精灵的指针
totalhp:精灵的总血量
length :血条的总长度
*/
void AnimalDrawline(Animal *animal, float totalhp,float length)
{
	CSystem::DrawLine(animal->GetSpriteLinkPointPosX(2), animal->GetSpriteLinkPointPosY(2), animal->GetSpriteLinkPointPosX(2) + Calculhp(totalhp, animal->hp, length), animal->GetSpriteLinkPointPosY(2), 4, 0, 191, 0, 0, 255);//画血条		
	CSystem::DrawLine(animal->GetSpriteLinkPointPosX(2), animal->GetSpriteLinkPointPosY(2)+0.25, animal->GetSpriteLinkPointPosX(2) + Calculhp(totalhp, totalhp, length), animal->GetSpriteLinkPointPosY(2)+0.25, 1, 0,0,0,10, 255);
	CSystem::DrawLine(animal->GetSpriteLinkPointPosX(2), animal->GetSpriteLinkPointPosY(2) -0.25 ,animal->GetSpriteLinkPointPosX(2) + Calculhp(totalhp, totalhp, length), animal->GetSpriteLinkPointPosY(2) -0.25 ,1, 0, 0,0,10, 255);
	CSystem::DrawLine(animal->GetSpriteLinkPointPosX(2), animal->GetSpriteLinkPointPosY(2) -0.25 ,animal->GetSpriteLinkPointPosX(2), animal->GetSpriteLinkPointPosY(2) +0.25, 1, 0, 0,0,10, 255);
	CSystem::DrawLine(animal->GetSpriteLinkPointPosX(2) + Calculhp(totalhp, totalhp, length), animal->GetSpriteLinkPointPosY(2) -0.25 ,animal->GetSpriteLinkPointPosX(2) + Calculhp(totalhp, totalhp, length), animal->GetSpriteLinkPointPosY(2) +0.25, 1, 0, 0,0,10, 255);
	CSystem::DrawLine(animal->GetSpriteLinkPointPosX(2) + Calculhp(totalhp, totalhp, length)/2, animal->GetSpriteLinkPointPosY(2) - 0.25, animal->GetSpriteLinkPointPosX(2) + Calculhp(totalhp, totalhp, length)/2, animal->GetSpriteLinkPointPosY(2) + 0.25, 1, 0, 0,0,10, 255);
}



