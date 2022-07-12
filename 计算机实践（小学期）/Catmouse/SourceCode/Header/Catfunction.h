#ifndef _CATFUNCTION_H_
#define _CATFUNCTION_H_

#include "CommonClass.h"
#include "LessonX.h"

struct Recangle//范围矩形
{
	float left;
	float right;
	float top;
	float botton;

};





/*
Ismouseinrange：判断鼠标是否在某范围内
参数 MouseX：鼠标横坐标
参数 MouseY：鼠标纵坐标
参数 range：要判断的范围
*/
bool Ismouseinrange(float MouseX, float MouseY, Recangle range);
/*
CalculY:计算加速度对路程改变量
参数:
v0:初速度
t :衰减时间
a :加速度大小
*/
float CalculY(float v0, float t,float a);
/*
Calculhp:计算当前血条长度
参数:
totalhp:精灵总血量
nowhp  :精灵当前血量
length :血条长度（总血量）
*/
float Calculhp(float totalhp, float nowhp, float length);
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
void AnimalJump(Animal *animal, float fDeltaTime, float heigh, float bottom, float v0, float a);
/*
BottonView:如果鼠标在精灵范围内，自动更换另一张图片（放进OnMouseMove函数内即可实现按钮效果）
参数:
sprite:精灵的地址
mousex:横坐标
mousey:纵坐标
zctp  :坐标不在范围内显示的图片名称
drtp  :坐标在范围内显示的图片名称
*/
bool BottonView(CStaticSprite *sprite, float mousex, float mousey, const char* zctp, const char* drtp, bool config=false);
/*
AnimalModeChange:精灵不同模式执行不同操作（1：移动模式；2：攻击模式；3：静止模式）（有怪状态）
参数：
animal:精灵的地址
sta   :精灵静止时播放的图片名称
run   :精灵移动时播放的图片名称
att   :精灵的攻击效果的地址
god   :被攻击的怪物的地址
*/
void AnimalModeChange(Animal *animal, const char*sta, const char*run, CEffect *att, Animal *god, CEffect *jn1, CEffect *jn2, vector<Animal*>gg);
/*
AnimalModeChange:精灵不同模式执行不同操作（1：移动模式；2：攻击模式；3：静止模式）（无怪状态）
参数：
animal:精灵的地址
sta   :精灵静止时播放的图片名称
run   :精灵移动时播放的图片名称
att   :精灵的攻击效果的地址
*/
void AnimalModeChange(Animal *animal, const char*sta, const char*run, CEffect *att);
/*
AnimalChangdirect:精灵改变朝向
参数:
animal:精灵的地址
*/
void AnimalChangdirect(Animal *animal);
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
void AnimalColWorld(Animal *animal, CStaticSprite *map, const int iColSide, const char*name, const char*szName, float maprange, float animalmove);
/*
AutoColWorld:精灵碰撞地图后自动操作（对怪物）
参数:
animal    :精灵的地址
map       :背景的地址
iColSide  :碰撞到的边界 0 左边，1 右边，2 上边，3 下边
name      :精灵的名字
szName    :碰撞到边界的精灵名字
*/
void AutoColWorld(Animal *animal, CStaticSprite *map, const int iColSide, const char*name, const char*szName);

Recangle Getanimalrange(Animal *animal);
Recangle Getanimalrange(CSprite *animal);
Recangle Getanimalrange(CStaticSprite *animal);
Recangle Getanimalrange(CEffect *animal);
/*
AnimalDrawline
参数：
animal :精灵的指针
totalhp:精灵的总血量
length :血条的总长度
*/
void AnimalDrawline(Animal *animal, float totalhp, float length);

#endif // _FUNCTION_H_