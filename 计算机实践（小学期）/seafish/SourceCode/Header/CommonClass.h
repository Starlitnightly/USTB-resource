/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _COMMON_CLASS_H_
#define _COMMON_CLASS_H_
//
#include <windows.h>
/////////////////////////////////////////////////////////////////////////////////
//
// 全局变量、宏定义
#define		MAX_NAME_LEN		128	// 名字长度
/////////////////////////////////////////////////////////////////////////////////
//
// Sprite精灵与世界边界碰撞响应定义( 碰撞之后API OnSpriteColWorldLimit 将被调用 )
enum EWorldLimit
{
	WORLD_LIMIT_OFF,			// 关闭与世界边界的碰撞
	WORLD_LIMIT_NULL,			// 碰撞之后引擎不做任何处理，由各游戏自己处理响应
	WORLD_LIMIT_RIGID,			// 刚性物理碰撞反应
	WORLD_LIMIT_BOUNCE,			// 反弹模式
	WORLD_LIMIT_CLAMP,			// 小幅反弹，逐渐停止模式(比如篮球落地)
	WORLD_LIMIT_STICKY,			// 碰撞之后静止
	WORLD_LIMIT_KILL,			// 碰撞之后精灵将被删除

	WORLD_LIMIT_INVALID,		//	无效值
};
/////////////////////////////////////////////////////////////////////////////////
//
/// 精灵与精灵之间、精灵与地图中其它精灵之间的碰撞响应( 碰撞之后API OnSpriteColSprite 将被调用 )
enum ECollisionResponse
{
	COL_RESPONSE_OFF,			//	关闭碰撞响应(不调用OnSpriteColSprite)

	COL_RESPONSE_RIGID,			//	刚性物理碰撞响应
	COL_RESPONSE_BOUNCE,		//	反弹模式
	COL_RESPONSE_CLAMP,			//	小幅反弹，逐渐停止模式(比如篮球落地)
	COL_RESPONSE_STICKY,		//	碰撞之后静止
	COL_RESPONSE_KILL,			//	碰撞之后精灵将被删除
	COL_RESPONSE_CUSTOM,		//	碰撞之后引擎不做任何处理，由各游戏自己处理响应

	COL_RESPONSE_INVALID,		//	无效值
};
//================================================================================
//
// 鼠标按键值定义
enum MouseTypes 
{
	MOUSE_LEFT		=	0,		// 左键
	MOUSE_RIGHT		=	1,		// 右键
	MOUSE_MIDDLE	=	2		// 中键
};
/////////////////////////////////////////////////////////////////////////////////
//
// 键盘KEY值定义
enum KeyCodes 
{
	KEY_NULL          = 0x000,     ///< Invalid KeyCode
	KEY_BACKSPACE     = 0x001,
	KEY_TAB           = 0x002,
	KEY_ENTER         = 0x003,
	KEY_CONTROL       = 0x004,
	KEY_ALT           = 0x005,
	KEY_SHIFT         = 0x006,
	KEY_PAUSE         = 0x007,
	KEY_CAPSLOCK      = 0x008,
	KEY_ESCAPE        = 0x009,
	KEY_SPACE         = 0x00a,
	KEY_PAGE_DOWN     = 0x00b,
	KEY_PAGE_UP       = 0x00c,
	KEY_END           = 0x00d,
	KEY_HOME          = 0x00e,
	KEY_LEFT          = 0x00f,
	KEY_UP            = 0x010,
	KEY_RIGHT         = 0x011,
	KEY_DOWN          = 0x012,
	KEY_PRINT         = 0x013,
	KEY_INSERT        = 0x014,
	KEY_DELETE        = 0x015,
	KEY_HELP          = 0x016,

	KEY_0             = 0x017,
	KEY_1             = 0x018,
	KEY_2             = 0x019,
	KEY_3             = 0x01a,
	KEY_4             = 0x01b,
	KEY_5             = 0x01c,
	KEY_6             = 0x01d,
	KEY_7             = 0x01e,
	KEY_8             = 0x01f,
	KEY_9             = 0x020,

	KEY_A             = 0x021,
	KEY_B             = 0x022,
	KEY_C             = 0x023,
	KEY_D             = 0x024,
	KEY_E             = 0x025,
	KEY_F             = 0x026,
	KEY_G             = 0x027,
	KEY_H             = 0x028,
	KEY_I             = 0x029,
	KEY_J             = 0x02a,
	KEY_K             = 0x02b,
	KEY_L             = 0x02c,
	KEY_M             = 0x02d,
	KEY_N             = 0x02e,
	KEY_O             = 0x02f,
	KEY_P             = 0x030,
	KEY_Q             = 0x031,
	KEY_R             = 0x032,
	KEY_S             = 0x033,
	KEY_T             = 0x034,
	KEY_U             = 0x035,
	KEY_V             = 0x036,
	KEY_W             = 0x037,
	KEY_X             = 0x038,
	KEY_Y             = 0x039,
	KEY_Z             = 0x03a,

	KEY_TILDE         = 0x03b,
	KEY_MINUS         = 0x03c,
	KEY_EQUALS        = 0x03d,
	KEY_LBRACKET      = 0x03e,
	KEY_RBRACKET      = 0x03f,
	KEY_BACKSLASH     = 0x040,
	KEY_SEMICOLON     = 0x041,
	KEY_APOSTROPHE    = 0x042,
	KEY_COMMA         = 0x043,
	KEY_PERIOD        = 0x044,
	KEY_SLASH         = 0x045,
	KEY_NUMPAD0       = 0x046,
	KEY_NUMPAD1       = 0x047,
	KEY_NUMPAD2       = 0x048,
	KEY_NUMPAD3       = 0x049,
	KEY_NUMPAD4       = 0x04a,
	KEY_NUMPAD5       = 0x04b,
	KEY_NUMPAD6       = 0x04c,
	KEY_NUMPAD7       = 0x04d,
	KEY_NUMPAD8       = 0x04e,
	KEY_NUMPAD9       = 0x04f,
	KEY_MULTIPLY      = 0x050,
	KEY_ADD           = 0x051,
	KEY_SEPARATOR     = 0x052,
	KEY_SUBTRACT      = 0x053,
	KEY_DECIMAL       = 0x054,
	KEY_DIVIDE        = 0x055,
	KEY_NUMPADENTER   = 0x056,

	KEY_F1            = 0x057,
	KEY_F2            = 0x058,
	KEY_F3            = 0x059,
	KEY_F4            = 0x05a,
	KEY_F5            = 0x05b,
	KEY_F6            = 0x05c,
	KEY_F7            = 0x05d,
	KEY_F8            = 0x05e,
	KEY_F9            = 0x05f,
	KEY_F10           = 0x060,
	KEY_F11           = 0x061,
	KEY_F12           = 0x062,
	KEY_F13           = 0x063,
	KEY_F14           = 0x064,
	KEY_F15           = 0x065,
	KEY_F16           = 0x066,
	KEY_F17           = 0x067,
	KEY_F18           = 0x068,
	KEY_F19           = 0x069,
	KEY_F20           = 0x06a,
	KEY_F21           = 0x06b,
	KEY_F22           = 0x06c,
	KEY_F23           = 0x06d,
	KEY_F24           = 0x06e,

	KEY_NUMLOCK       = 0x06f,
	KEY_SCROLLLOCK    = 0x070,
	KEY_LCONTROL      = 0x071,
	KEY_RCONTROL      = 0x072,
	KEY_LALT          = 0x073,
	KEY_RALT          = 0x074,
	KEY_LSHIFT        = 0x075,
	KEY_RSHIFT        = 0x076,
	KEY_WIN_LWINDOW   = 0x077,
	KEY_WIN_RWINDOW   = 0x078,
	KEY_WIN_APPS      = 0x079,
	KEY_OEM_102       = 0x080,

	KEY_MAC_OPT       = 0x090,
	KEY_MAC_LOPT      = 0x091,
	KEY_MAC_ROPT      = 0x092,

	KEY_BUTTON0       = 0x0100,
	KEY_BUTTON1       = 0x0101,
	KEY_BUTTON2       = 0x0102,
	KEY_BUTTON3       = 0x0103,
	KEY_BUTTON4       = 0x0104,
	KEY_BUTTON5       = 0x0105,
	KEY_BUTTON6       = 0x0106,
	KEY_BUTTON7       = 0x0107,
	KEY_BUTTON8       = 0x0108,
	KEY_BUTTON9       = 0x0109,
	KEY_BUTTON10      = 0x010A,
	KEY_BUTTON11      = 0x010B,
	KEY_BUTTON12      = 0x010C,
	KEY_BUTTON13      = 0x010D,
	KEY_BUTTON14      = 0x010E,
	KEY_BUTTON15      = 0x010F,
	KEY_BUTTON16      = 0x0110,
	KEY_BUTTON17      = 0x0111,
	KEY_BUTTON18      = 0x0112,
	KEY_BUTTON19      = 0x0113,
	KEY_BUTTON20      = 0x0114,
	KEY_BUTTON21      = 0x0115,
	KEY_BUTTON22      = 0x0116,
	KEY_BUTTON23      = 0x0117,
	KEY_BUTTON24      = 0x0118,
	KEY_BUTTON25      = 0x0119,
	KEY_BUTTON26      = 0x011A,
	KEY_BUTTON27      = 0x011B,
	KEY_BUTTON28      = 0x011C,
	KEY_BUTTON29      = 0x011D,
	KEY_BUTTON30      = 0x011E,
	KEY_BUTTON31      = 0x011F,
	KEY_ANYKEY         = 0xfffe
};
//////////////////////////////////////////////////////////////////////////////
//
// 类：CSprite
// 所有精灵的基类。包括下面的静态精灵，动态精灵，文字，特效等均由此类继承下去
// 一般的图片精灵从本类继承下去即可。只有特殊的精灵，比如带动画的精灵，才需要从动态精灵继承下去
//
class CSprite
{
private:
	char		m_szName[MAX_NAME_LEN];		// 精灵名字

public:

	// 构造函数，需要传入一个非空的精灵名字字符串。如果传入的是地图里摆放好的精灵名字，则此类即与地图里的精灵绑定
	// 如果传入的是一个新的精灵名字，则需要调用成员函数 CloneSprite，复制一份精灵对象实例，才与实际的地图精灵关联起来
	// szCloneName : 预先存在于场景中，需要克隆的精灵名字
	CSprite( const char *szName );
	CSprite( const char *szName, const char *szCloneName );
	virtual ~CSprite();

	// GetName
	// 返回值：返回精灵名字
	const char *GetName();


	// CloneSprite：复制(创建)一个精灵。精灵的创建方式：先在地图中摆放一个精灵做为模板，设置好各项参数，然后在代码里使用此函数克隆一个实例
	// 返回值：true表示克隆成功，false克隆失败。失败的原因可能是在地图中未找到对应名字的精灵
	// 参数 szSrcName：地图中用做模板的精灵名字
	//
	bool		CloneSprite( const char *szSrcName );

	// DeleteSprite：在地图中删除与本对象实例关联的精灵
	//
	void		DeleteSprite();

	// SetSpriteVisible：设置精灵隐藏或者显示(可见不可见)
	// 参数 bVisible：true 可见 false不可见
	//
	void		SetSpriteVisible( const bool bVisible );

	// IsSpriteVisible：获取该精灵当前是否可见
	//
	bool		IsSpriteVisible();

	// SetSpriteEnable：禁止或者启用该精灵。被禁止的精灵将不参与任何响应，包括不移动，没有碰撞等，仅仅是在地图中显示
	// 参数 bEnable：true启用 false禁止
	//
	void		SetSpriteEnable( const bool bEnable );

	// SetSpriteScale：设置精灵的缩放值
	// 参数 fScale：缩放值。大于0的值
	//
	void		SetSpriteScale( const float fScale );

	// IsPointInSprite：判断某个坐标点是否位于精灵内部
	// 参数 fPosX：X坐标点
	// 参数 fPosY：Y坐标点
	//
	bool 		IsPointInSprite( const float fPosX, const float fPosY );

	// SetSpritePosition：设置精灵位置
	// 参数 fPosX：X坐标
	// 参数 fPosY：Y坐标
	//
	void		SetSpritePosition( const float fPosX, const float fPosY );

	// SetSpritePositionX：只设置精灵X坐标
	// 参数 fPosX：X坐标
	//
	void		SetSpritePositionX( const float fPosX );

	// SetSpritePositionY：只设置精灵Y坐标
	// 参数 fPosY：Y坐标
	//
	void		SetSpritePositionY( const float fPosY );

	// GetSpritePositionX：获取精灵X坐标
	// 返回值：精灵的X坐标
	//
	float		GetSpritePositionX();

	// GetSpritePositionY：获取精灵Y坐标
	// 返回值：精灵的Y坐标
	//
	float		GetSpritePositionY();

	// GetSpriteLinkPointPosX：获取精灵链接点X坐标。链接点是依附于精灵的一个坐标点，可以在编辑器里增加或者删除
	// 参数 iId：链接点序号，第一个为1，后面依次递加
	//
	float		GetSpriteLinkPointPosX( const int iId );

	// GetSpriteLinkPointPosY：获取精灵链接点Y坐标。链接点是依附于精灵的一个坐标点，可以在编辑器里增加或者删除
	// 参数 iId：链接点序号，第一个为1，后面依次递加
	//
	float		GetSpriteLinkPointPosY( const int iId );

	// SetSpriteRotation：设置精灵的旋转角度
	// 参数 fRot：旋转角度，范围0 - 360
	//
	void		SetSpriteRotation( const float fRot );

	// GetSpriteRotation：获取精灵的旋转角度
	// 返回值：精灵的旋转角度
	//
	float		GetSpriteRotation();

	// SetSpriteAutoRot：设置精灵按照指定速度自动旋转
	// 参数 fRotSpeed：旋转速度
	//
	void 		SetSpriteAutoRot( const float fRotSpeed );

	// SetSpriteWidth：设置精灵外形宽度
	// 参数 fWidth：宽度值，大于0
	//
	void		SetSpriteWidth( const float fWidth );

	// GetSpriteWidth：获取精灵外形宽度
	// 返回值：精灵宽度值
	//
	float		GetSpriteWidth();

	// SetSpriteHeight：设置精灵外形高度
	// 参数 fHeight：精灵高度值
	//
	void		SetSpriteHeight( const float fHeight );

	// GetSpriteHeight：获取精灵外形高度
	// 返回值：精灵高度值
	//
	float		GetSpriteHeight();

	// SetSpriteFlipX：设置精灵图片X方向翻转显示
	// 参数 bFlipX：true 翻转 false不翻转(恢复原来朝向)
	//
	void		SetSpriteFlipX( const bool bFlipX );

	// GetSpriteFlipX：获取当前精灵图片X方向是否是翻转显示
	// 返回值：true 翻转 false不翻转
	//
	bool		GetSpriteFlipX();

	// SetSpriteFlipY：设置精灵图片Y方向翻转显示
	// 参数 bFlipY：true 翻转 false不翻转(恢复原来朝向)
	//
	void		SetSpriteFlipY( const bool bFlipY );

	// GetSpriteFlipY：获取当前精灵图片Y方向是否是翻转显示
	// 返回值：true 翻转 false不翻转
	//
	bool		GetSpriteFlipY();

	// SetSpriteFlip：同时设置精灵翻转X及Y方向
	// 参数 bFlipX：true 翻转 false不翻转(恢复原来朝向)
	// 参数 bFlipY：true 翻转 false不翻转(恢复原来朝向)
	//
	void		SetSpriteFlip( const bool bFlipX, const bool bFlipY );

	// SetSpriteLifeTime：设置精灵的生命时长，时间到了之后将自动被删除
	// 参数 fLifeTime：生命时长，单位 秒
	//
	void		SetSpriteLifeTime( const float fLifeTime );

	// GetSpriteLifeTime：获取精灵生命时长
	// 返回值：生命时长，单位 秒
	//
	float		GetSpriteLifeTime();	


	// SpriteMoveTo：让精灵按照给定速度移动到给定坐标点
	// 参数 fPosX：移动的目标X坐标值
	// 参数 fPosY：移动的目标Y坐标值
	// 参数 fSpeed：移动速度
	// 参数 bAutoStop：移动到终点之后是否自动停止
	//
	void		SpriteMoveTo( const float fPosX, const float fPosY, const float fSpeed, const bool bAutoStop );

	// SpriteRotateTo：让精灵按照给定速度旋转到给定的角度
	// 参数 fRotation：给定的目标旋转值
	// 参数 fRotSpeed：旋转速度
	// 参数 bAutoStop：旋转到终点之后是否自动停止
	//
	void		SpriteRotateTo( const float fRotation, const float fRotSpeed, const bool bAutoStop );

	// SetSpriteWorldLimit：设置精灵的世界边界坐标限制及碰撞模式
	// 参数 Limit：碰撞到世界边界之后的响应模式，如果为OFF，则是关闭世界边界碰撞。其它值见 EWorldLimit
	// 参数 fLeft：边界的左边X坐标
	// 参数 fTop：边界的上边Y坐标
	// 参数 fRight：边界的右边X坐标
	// 参数 fBottom：边界的下边Y坐标
	//
	void		SetSpriteWorldLimit( const EWorldLimit Limit, const float fLeft, const float fTop, const float fRight, const float fBottom );

	// SetSpriteWorldLimitMode：设置精灵的世界边界碰撞模式
	// 参数 Limit：碰撞到世界边界之后的响应模式，如果为OFF，则是关闭世界边界碰撞。其它值见 EWorldLimit
	//
	void		SetSpriteWorldLimitMode( const EWorldLimit Limit );

	// SetSpriteWorldLimitMin：设置精灵的世界边界上边及左边坐标限制
	// 参数 fLeft：边界的左边X坐标
	// 参数 fTop：边界的上边Y坐标
	//
	void		SetSpriteWorldLimitMin( const float fLeft, const float fTop );

	// SetSpriteWorldLimitMax：设置精灵的世界边界下边及右边坐标限制
	// 参数 fRight：边界的右边X坐标
	// 参数 fBottom：边界的下边Y坐标
	//
	void		SetSpriteWorldLimitMax( const float fRight, const float fBottom );

	// GetSpriteWorldLimitLeft：获取精灵世界边界左边界限制
	//
	float		GetSpriteWorldLimitLeft();

	// GetSpriteWorldLimitTop：获取精灵世界边界上边界限制
	//
	float		GetSpriteWorldLimitTop();

	// GetSpriteWorldLimitRight：获取精灵世界边界右边界限制
	//
	float		GetSpriteWorldLimitRight();

	// GetSpriteWorldLimitBottom：获取精灵世界边界下边界限制
	//
	float		GetSpriteWorldLimitBottom();

	// SetSpriteCollisionSend：设置精灵是否可以发送(产生)碰撞
	// 精灵的碰撞方式为：当A移动中碰上B时，如果A是可以产生碰撞的，B是可以接受碰撞的，则这2个物体会产生碰撞，精灵碰撞的API将被调用。否则无碰撞发生
	// 参数 bSend：true 可以产生 false 不产生
	//
	void 		SetSpriteCollisionSend( const bool bSend );

	// SetSpriteCollisionReceive：设置精灵是否可以接受碰撞
	// 精灵的碰撞方式为：当A移动中碰上B时，如果A是可以产生碰撞的，B是可以接受碰撞的，则这2个物体会产生碰撞，精灵碰撞的API将被调用。否则无碰撞发生
	// 参数 bReceive：true 可以接受 false 不接受
	//
	void 		SetSpriteCollisionReceive( const bool bReceive );

	// SetSpriteCollisionActive：同时设置精灵是否可以产生及接受碰撞
	// 精灵的碰撞方式为：当A移动中碰上B时，如果A是可以产生碰撞的，B是可以接受碰撞的，则这2个物体会产生碰撞，精灵碰撞的API将被调用。否则无碰撞发生
	// 参数 bSend：true 可以产生 false 不产生
	// 参数 bReceive：true 可以接受 false 不接受
	//
	void 		SetSpriteCollisionActive( const bool bSend, const bool bReceive );

	// SetSpriteCollisionPhysicsSend：设置精灵是否可以发送(产生)物理碰撞
	// 参数 bSend：true 可以产生 false 不产生
	//
	void 		SetSpriteCollisionPhysicsSend( const bool bSend );

	// SetSpriteCollisionPhysicsReceive：设置精灵是否可以接受物理碰撞
	// 参数 bReceive：true 可以接受 false 不接受
	//
	void 		SetSpriteCollisionPhysicsReceive( const bool bReceive );

	// GetSpriteCollisionSend：获取精灵当前是否是可以产生碰撞
	// 返回值：true 可以产生 false 不产生
	//
	bool 		GetSpriteCollisionSend();

	// GetSpriteCollisionReceive：获取精灵当前是否是可以接受碰撞
	// 返回值：true 可以接受 false 不接受
	//
	bool 		GetSpriteCollisionReceive();

	// SetSpriteCollisionResponse：设置精灵与精灵的碰撞响应模式
	// 参数 Response：响应模式，如果为OFF，则为关闭碰撞响应，碰撞API将不会被调用。其它值见 ECollisionResponse
	//
	void		SetSpriteCollisionResponse( const ECollisionResponse Response );

	// SetSpriteCollisionMaxIterations：设置精灵碰撞之后的最大反弹次数
	// 参数 iTimes：反弹次数
	//
	void		SetSpriteCollisionMaxIterations( const int iTimes );

	// SetSpriteForwardMovementOnly：设置精灵是否只能朝前移动
	// 参数 bForward：true 只能朝前移动 false 可以朝其他方向移动
	//
	void		SetSpriteForwardMovementOnly( const bool bForward );

	// GetSpriteForwardMovementOnly：获取精灵当前是否只能朝前移动
	// 返回值：true 只能朝前移动 false 可以朝其它方向移动
	//
	bool		GetSpriteForwardMovementOnly();

	// SetSpriteForwardSpeed：设置精灵向前的速度
	// 参数 fSpeed：速度
	//
	void		SetSpriteForwardSpeed( const float fSpeed );

	// SetSpriteImpulseForce：设置精灵瞬间推力
	// 参数 fForceX：X方向推力大小
	// 参数 fForceY：Y方向推力大小
	// 参数 bGravitic：是否计算重力
	//
	void 		SetSpriteImpulseForce( const float fForceX, const float fForceY, const bool bGravitic );

	// SetSpriteImpulseForcePolar：按角度朝向设置精灵瞬间推力
	// 参数 fPolar：角度朝向
	// 参数 fForce：推力大小
	// 参数 bGravitic：是否计算重力
	//
	void 		SetSpriteImpulseForcePolar( const float fPolar, const float fForce, const bool bGravitic );

	// SetSpriteConstantForceX：设置精灵X方向常量推力
	// 参数 fForceX：X方向推力大小
	//
	void 		SetSpriteConstantForceX( const float fForceX );

	// SetSpriteConstantForceY：设置精灵Y方向常量推力
	// 参数 fForceY：Y方向推力大小
	//
	void 		SetSpriteConstantForceY( const float fForceY );

	// SetSpriteConstantForceGravitic：精灵在计算常量推力的时候，是否计算重力
	// 参数 bGravitic：是否计算重力
	//
	void 		SetSpriteConstantForceGravitic( const bool bGravitic );

	// SetSpriteConstantForce：设置精灵常量推力
	// 参数 fForceX：X方向推力大小
	// 参数 fForceY：Y方向推力大小
	// 参数 bGravitic：是否计算重力
	//
	void 		SetSpriteConstantForce( const float fForceX, const float fForceY, const bool bGravitic );

	// SetSpriteConstantForcePolar：按角度朝向设置精灵常量推力
	// 参数 fPolar：角度朝向
	// 参数 fForce：推力大小
	// 参数 bGravitic：是否计算重力
	//
	void 		SetSpriteConstantForcePolar( const float fPolar, const float fForce, const bool bGravitic );

	// StopSpriteConstantForce：停止精灵常量推力
	//
	void 		StopSpriteConstantForce();

	// SetSpriteForceScale：按倍数缩放精灵当前受的推力
	// 参数 fScale：缩放值
	//
	void 		SetSpriteForceScale( const float fScale );

	// SetSpriteAtRest：暂停/继续精灵的各种受力计算
	// 参数 bRest：true 暂停 false 继续
	//
	void 		SetSpriteAtRest( const bool bRest );

	// GetSpriteAtRest：获取精灵当前是否在暂停中
	// 返回值：true 暂停中 false 正常
	//
	bool 		GetSpriteAtRest( );

	// SetSpriteFriction：设置精灵摩擦力
	// 参数 fFriction：摩擦力大小
	//
	void 		SetSpriteFriction( const float fFriction );

	// SetSpriteRestitution：设置精灵弹力
	// 参数 fRestitution：弹力值大小
	//
	void 		SetSpriteRestitution( const float fRestitution );

	// SetSpriteMass：设置精灵质量
	// 参数 fMass：质量大小
	//
	void 		SetSpriteMass( const float fMass );

	// GetSpriteMass：获取精灵质量
	// 返回值 ：质量大小
	//
	float 		GetSpriteMass();

	// SetSpriteAutoMassInertia：开启或者关闭精灵惯性
	// 参数 bStatus：true 开启 false 关闭
	//
	void 		SetSpriteAutoMassInertia( const bool bStatus );

	// SetSpriteInertialMoment：设置精灵惯性大小
	// 参数 fInert：惯性大小
	//
	void 		SetSpriteInertialMoment( const float fInert );

	// SetSpriteDamping：设置精灵衰减值
	// 参数 fDamp：衰减值大小
	//
	void 		SetSpriteDamping( const float fDamp );

	// SetSpriteImmovable：设置精灵是否不可移动
	// 参数 bImmovable：true 不可以移动 false 可以移动
	//
	void 		SetSpriteImmovable( const bool bImmovable );

	// GetSpriteImmovable：获取精灵当前是否不可以移动
	// 返回值：true 不可以移动 false 可以移动
	//
	bool 		GetSpriteImmovable();

	// SetSpriteLinearVelocity：设置精灵移动速度
	// 参数 fVelX：X方向速度
	// 参数 fVelY：Y方向速度
	//
	void 		SetSpriteLinearVelocity( const float fVelX, const float fVelY );

	// SetSpriteLinearVelocityX：设置精灵X方向移动速度
	// 参数 fVelX：X方向速度
	//
	void 		SetSpriteLinearVelocityX( const float fVelX );

	// SetSpriteLinearVelocityY：设置精灵Y方向移动速度
	// 参数 fVelY：Y方向速度
	//
	void 		SetSpriteLinearVelocityY( const float fVelY );

	// SetSpriteLinearVelocityPolar：按角度朝向设置精灵移动速度
	// 参数 fSpeed：移动速度
	// 参数 fPolar：角度朝向
	//
	void 		SetSpriteLinearVelocityPolar( const float fSpeed, const float fPolar );

	// SetSpriteAngularVelocity：设置精灵角度旋转速度
	// 参数 fAngular：角度旋转速度
	//
	void 		SetSpriteAngularVelocity( const float fAngular );

	// SetSpriteMinLinearVelocity：设置精灵最小速度
	// 参数 fMin：最小速度值
	//
	void 		SetSpriteMinLinearVelocity( const float fMin );

	// SetSpriteMaxLinearVelocity：设置精灵最大速度
	// 参数 fMax：最大速度值
	//
	void 		SetSpriteMaxLinearVelocity( const float fMax );

	// SetSpriteMinAngularVelocity：设置精灵最小角速度
	// 参数 fMin：最小角速度
	//
	void 		SetSpriteMinAngularVelocity( const float fMin );

	// SetSpriteMaxAngularVelocity：设置精灵最大角速度
	// 参数 fMax：最大角速度
	//
	void 		SetSpriteMaxAngularVelocity( const float fMax );

	// GetSpriteLinearVelocityX：获取精灵X方向速度
	// 返回值：X方向速度
	//
	float 		GetSpriteLinearVelocityX();

	// GetSpriteLinearVelocityY：获取精灵Y方向速度
	// 返回值：Y方向速度
	//
	float 		GetSpriteLinearVelocityY();


	// SpriteMountToSprite：将一个精灵绑定到另一个精灵上，暂时的成为另一个精灵的一部分，跟随其运动等
	// 参数 szDstName：承载绑定的母体精灵名字
	// 参数 fOffSetX：绑定偏移X
	// 参数 fOffsetY：绑定偏移Y
	// 返回值：返回一个绑定ID
	//
	int			SpriteMountToSprite( const char *szDstName, const float fOffSetX, const float fOffsetY );

	// SpriteMountToSpriteLinkPoint：将一个精灵绑定到另一个精灵上，绑定位置为指定的链接点，暂时的成为另一个精灵的一部分，跟随其运动等
	// 参数 szDstName：承载绑定的母体精灵名字
	// 参数 iPointId：链接点序号
	// 返回值：返回一个绑定ID
	//
	int			SpriteMountToSpriteLinkPoint( const char *szDstName, const int iPointId );

	// SetSpriteMountRotation：设置精灵的绑定朝向，即相对于母体的朝向
	// 参数 fRot：角度朝向，0 - 360
	//
	void		SetSpriteMountRotation( const float fRot );

	// GetSpriteMountRotation：获取精灵的绑定朝向，即相对于母体的朝向
	// 返回值：角度朝向
	//
	float		GetSpriteMountRotation();

	// SetSpriteAutoMountRotation：设置精灵绑定之后自动旋转
	// 参数 fRot：旋转速度
	//
	void		SetSpriteAutoMountRotation( const float fRot );

	// GetSpriteAutoMountRotation：获取精灵绑定之后的自动旋转值
	// 返回值：旋转速度
	//
	float		GetSpriteAutoMountRotation();

	// SetSpriteMountForce：绑定至另一个精灵时，附加的作用力
	// 参数 fFroce：作用力
	//
	void		SetSpriteMountForce( const float fForce );

	// SetSpriteMountTrackRotation：绑定的精灵是否跟随母体旋转
	// 参数 bTrackRotation：true 跟随 false 不跟随
	//
	void		SetSpriteMountTrackRotation( const bool bTrackRotation );

	// SetSpriteMountOwned：母体被删除的时候，绑定的精灵是否也跟着被删除
	// 参数 bMountOwned：true 跟着 false 不跟着
	//
	void		SetSpriteMountOwned( const bool bMountOwned );

	// SetSpriteMountInheritAttributes：绑定的时候，是否继承母体的属性
	// 参数 bInherAttr：true 继承 false 不继承
	//
	void		SetSpriteMountInheritAttributes( const bool bInherAttr );

	// SpriteDismount：将已经绑定的精灵进行解绑
	//
	void		SpriteDismount();

	// GetSpriteIsMounted：判断精灵是否绑定在另一个精灵上
	// 返回值：true 绑定 false 不绑定
	//
	bool		GetSpriteIsMounted();

	// GetSpriteMountedParent：获取绑定的母体精灵的名字
	// 返回值：母体精灵名字，如果未绑定，则返回空字符串
	//
	const char*	GetSpriteMountedParent();


	// SetSpriteColorRed：更改精灵显示颜色中的红色。默认精灵的红绿蓝三颜色的值均为255，修改其中一项将可以改变其颜色
	// 参数 iCol：颜色范围 0 - 255
	//
	void		SetSpriteColorRed( const int iCol );

	// SetSpriteColorGreen：更改精灵显示颜色中的绿色。默认精灵的红绿蓝三颜色的值均为255，修改其中一项将可以改变其颜色
	// 参数 iCol：颜色范围 0 - 255
	//
	void		SetSpriteColorGreen( const int iCol );

	// SetSpriteColorBlue：更改精灵显示颜色中的蓝色。默认精灵的红绿蓝三颜色的值均为255，修改其中一项将可以改变其颜色
	// 参数 iCol：颜色范围 0 - 255
	//
	void		SetSpriteColorBlue( const int iCol );

	// SetSpriteColorAlpha：设置精灵透明度
	// 参数 iCol：透明度，值0 - 255，从完全透明至完全不透明
	//
	void		SetSpriteColorAlpha( const int iCol );

	// GetSpriteColorRed：获取精灵显示颜色中的红色值
	// 返回值：颜色值
	//
	int			GetSpriteColorRed();

	// GetSpriteColorGreen：获取精灵显示颜色中的绿色值
	// 返回值：颜色值
	//
	int			GetSpriteColorGreen();

	// GetSpriteColorBlue：获取精灵显示颜色中的蓝色值
	// 返回值：颜色值
	//
	int			GetSpriteColorBlue();

	// GetSpriteColorAlpha：获取精灵透明度
	// 返回值：透明度
	//
	int			GetSpriteColorAlpha();
};
//////////////////////////////////////////////////////////////////////////////
//
// 类：CStaticSprite
// 静态精灵(静态图片显示)，从CSprite精灵基类继承下来，比基类多了几个控制精灵图片显示的函数
// 
class CStaticSprite : public CSprite
{
public:
	CStaticSprite( const char *szName );
	CStaticSprite( const char *szName, const char *szCloneName );
	~CStaticSprite();

	// SetStaticSpriteImage：设置/更改静态精灵的显示图片
	// 参数 szImageName：图片名字
	// 参数 iFrame：该图片的显示帧数。为编辑器预览图里显示的1/N，范围为 0 到 N - 1
	//
	void		SetStaticSpriteImage( const char *szImageName, const int iFrame );

	// SetStaticSpriteFrame：设置静态精灵当前图片的显示帧数
	// 参数 iFrame：该图片的显示帧数。为编辑器预览图里显示的1/N，范围为 0 到 N - 1
	//
	void		SetStaticSpriteFrame( const int iFrame );
	//

	// GetStaticSpriteImage：获取精灵当前显示的图片名字
	// 返回值：图片名字
	//
	const char* GetStaticSpriteImage();

	// GetStaticSpriteFrame：获取精灵当前显示的图片帧数
	// 返回值：帧数
	//
	int			GetStaticSpriteFrame();
};
//////////////////////////////////////////////////////////////////////////////
//
// 类：CAnimateSprite
// 动态精灵(带图片动画)，从CSprite精灵基类继承下来，比基类多了几个控制图片动画的函数
//
class CAnimateSprite : public CSprite
{
public:
	CAnimateSprite( const char *szName );
	CAnimateSprite( const char *szName, const char *szCloneName );
	~CAnimateSprite();

	// SetAnimateSpriteFrame：设置动态精灵的动画帧数
	// 参数 iFrame：动画帧数
	//
	void		SetAnimateSpriteFrame( const int iFrame );

	// GetAnimateSpriteAnimationName：获取动态精灵当前动画名字
	// 返回值：动画名字
	//
	const char* GetAnimateSpriteAnimationName();

	// GetAnimateSpriteAnimationTime：获取动画精灵当前动画时间长度
	// 返回值：长度，单位秒
	//
	float		GetAnimateSpriteAnimationTime();

	// IsAnimateSpriteAnimationFinished：判断动态精灵当前动画是否播放完毕，只针对非循环动画而言
	// 返回值：true 完毕 false 未完毕
	//
	bool		IsAnimateSpriteAnimationFinished();

	// AnimateSpritePlayAnimation：动画精灵播放动画
	// 参数 szAnim：动画名字
	// 参数 bRestore：播放完毕后是否恢复当前动画
	// 返回值：是否播放成功
	//
	bool		AnimateSpritePlayAnimation( const char *szAnim, const bool bRestore );
};
//////////////////////////////////////////////////////////////////////////////
//
// 类：CTextSprite
// 文字精灵，亦属于精灵中的一种。基本用法：在地图里摆放一个“文字”物体，起个名字
// 然后在代码里定义一个文字精灵的对象实例，将此名字做为构造函数的参数，然后调用对应的成员函数更新文字显示即可
//
class CTextSprite : public CSprite
{
public:
	CTextSprite( const char *szName );
	CTextSprite( const char *szName, const char *szCloneName );
	~CTextSprite();


	// SetTextValue：文字精灵显示某个数值
	// 参数 iValue：要显示的数值
	//
	void		SetTextValue( int iValue );

	// SetTextValueFloat：文字精灵显示某个浮点数值
	// 参数 fValue：要显示的数值
	//
	void		SetTextValueFloat( float fValue );

	// SetTextString：文字精灵显示某个字符串文字
	// 参数 szStr：要显示的字符串
	//
	void		SetTextString( const char *szStr );

	// SetTextChar：文字精灵显示某个字符
	// 参数 szChar：要显示的字符
	//
	void		SetTextChar( char szChar );
};
/////////////////////////////////////////////////////////////////////////////
//
// 类：CEffect
// 特效精灵，属于精灵中的一种。用法和文字精灵一样，先在地图里摆放一个特效做为模板，并命名
// 然后在代码里定义一个特效精灵的对象实例即可使用
class CEffect : public CSprite
{
	char		m_szCloneName[MAX_NAME_LEN];		// 在地图中预先摆放好的用做克隆的特效名字
	float		m_fTime;							// 非循环特效：生命时长；循环特效：循环时长
public:
	
	// 构造函数 
	// 参数 szCloneName：地图里摆放好的特效名字
	// 参数 szMyName：新的特效名字。注意：如果是循环特效，那么必须一个循环特效就定义一个对象实例，用不同的名字
	//                否则如果一个同名的循环特效被播放多次，在删除的时候会出问题。非循环特效则可以用一个实例多次播放
	// 参数 fTime：非循环特效：生命时长；循环特效：循环时长
	//
	CEffect( const char *szCloneName, const char *szMyName, const float fTime );
	~CEffect();

	// GetCloneName：获取用做克隆的特效名字
	// 
	const char*	GetCloneName();

	// GetTime：返回特效循环时长或者生命时长
	//
	float		GetTime();

	// PlayEffect：播放一个不循环的特效，播放完毕之后该特效自动删除
	// 播放非循环特效的时候，可以使用一个CEffect的对象实例，播放多个特效
	// 参数 fPosX：播放的X坐标
	// 参数 fPosY：播放的Y坐标
	// 参数 fRotation：播放的角度朝向
	//
	void		PlayEffect( const float fPosX, const float fPosY, const float fRotation);

	// PlayLoopEffect：播放一个循环特效，不需要该特效的时候，需要自己调用API进行删除
	// 参数 fPosX：播放的X坐标
	// 参数 fPosY：播放的Y坐标
	// 参数 fRotation：播放的角度朝向
	//
	void		PlayLoopEffect( const float fPosX, const float fPosY, const float fRotation);

	// DeleteEffect：删除一个正在播放的特效，只有循环特效才需要手动删除
	//
	void		DeleteEffect(); 
};
/////////////////////////////////////////////////////////////////////////////
//
// 类：CSound
// 播放声音的类，定义一个对象实例，调用播放函数即可实现声音的播放
// 
class CSound
{
private:
	char		m_szName[MAX_NAME_LEN];	// 声音名
	int			m_iSoundId;				// 引擎播放声音的时候，返回的ID
	bool		m_bLoop;				// bLoop : 是否循环播放。如果为循环音效，则在CSound实例析构的时候，自动调用StopSound停止此声音的播放
	float		m_fVolume;				// 音量大小，0-1。1为声音文件的原声大小

public:

	// 构造函数
	// 参数 szName：声音的路径及名称，具体值请在编辑器的资源 -> 添加声音那里查看本项目里的声音资源，完整按照那个路径值填写即可
	// 参数 bLoop：是否循环播放。如果是循环播放的声音，需要手动调用API停止播放
	// 参数 fVolume：音量大小，0-1。1为声音文件的原声大小
	//
	CSound( const char *szName, const bool bLoop, const float fVolume );
	~CSound();

	// GetName：获取声音名字
	//
	const char*	GetName();

	// PlaySound：播放该声音
	//
	void		PlaySound();

	// StopSound：停止该声音的播放
	// 非循环的播放完之后将自动停止，所以一般不需要调用此函数。只有循环的声音才需要调用。对于循环音效，在析构函数里也会自动调用此函数
	//
	void		StopSound();
	
	// StopAllSound：停止播放所有声音
	// 静态函数，可以以此种方式调用：CSound::StopAllSound，以停止游戏中所有正在播放的声音
	//
	static void	StopAllSound();
};

////////////////////////////////////////////////////////////////////////////////
//
// 类：CSystem
// 系统相关功能的类. 函数调用方法 CSystem::函数名();
//
class CSystem
{
public:
	CSystem();
	~CSystem();

	// OnMouseMove：鼠标移动后将被调用的函数，可在此函数体里(Main.cpp)增加自己的响应代码
	// 参数 fMouseX, fMouseY：为鼠标当前坐标
	//
	static void		OnMouseMove( const float fMouseX, const float fMouseY );

	// OnMouseClick：鼠标按下后将被调用的函数，可在此函数体里(Main.cpp)增加自己的响应代码
	// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
	// 参数 fMouseX, fMouseY：为鼠标当前坐标
	//
	static void		OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY );

	// OnMouseUp：鼠标按下后将被调用的函数，可在此函数体里(Main.cpp)增加自己的响应代码
	// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
	// 参数 fMouseX, fMouseY：为鼠标当前坐标
	//
	static void		OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY );

	// OnKeyDown：键盘被按下后将被调用的函数，可在此函数体里(Main.cpp)增加自己的响应代码
	// 参数 iKey：被按下的键，值见 enum KeyCodes 宏定义
	// 参数 bAltPress, bShiftPress，bCtrlPress：键盘上的功能键Alt，Ctrl，Shift当前是否也处于按下状态
	//
	static void		OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress );

	// OnKeyUp：键盘按键弹起后将被调用的函数，可在此函数体里(Main.cpp)增加自己的响应代码
	// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
	//
	static void		OnKeyUp( const int iKey );

	// OnSpriteColSprite：精灵与精灵碰撞后将被调用的函数，可在此函数体里(Main.cpp)增加自己的响应代码
	// 精灵之间要产生碰撞，必须在编辑器或者代码里设置精灵发送及接受碰撞
	// 参数 szSrcName：发起碰撞的精灵名字
	// 参数 szTarName：被碰撞的精灵名字
	//
	static void		OnSpriteColSprite( const char *szSrcName, const char *szTarName );

	// OnSpriteColWorldLimit：精灵与世界边界碰撞后将被调用的函数，可在此函数体里(Main.cpp)增加自己的响应代码
	// 精灵之间要产生碰撞，必须在编辑器或者代码里设置精灵的世界边界限制
	// 参数 szName：碰撞到边界的精灵名字
	// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
	//
	static void		OnSpriteColWorldLimit( const char *szName, const int iColSide );

	// MakeSpriteName: 将前面的字符串与后面的数字整合成一个字符串。
	// 参数 szPrev：一个非空字符串，最长不能超过20个英文字符。名字前面的字符。
	// 参数 iId：一个数字
	// 返回值：返回一个字符串，比如传入("xxx", 2),则返回"xxx2"
	//
	static char* MakeSpriteName(const char *szPrev, const int iId);

	// CursorOff：关闭鼠标不显示。此API隐藏的是整个Windows的鼠标，除非调用开启鼠标的API dCursorOn，否则鼠标将一直不显示
	//
	static void		CursorOff();

	// CursorOn：开启鼠标显示。将API dCursorOff关闭的鼠标重新开启显示
	//
	static void		CursorOn();

	// IsCursorOn：当前鼠标是开启还是关闭。对应的是用API dCursorOff和dCursorOn开启或者关闭的操作
	// 返回值：true为开启状态，false为关闭状态
	//
	static bool		IsCursorOn();

	// ShowCursor：隐藏/显示鼠标。此API只是隐藏本程序窗口内的鼠标，移动到窗口外的时候，鼠标还是会显示
	// 参数 bShow：true 为显示，false 为隐藏
	//
	static void		ShowCursor( const bool bShow );

	// IsShowCursor：当前鼠标是显示还是隐藏。对应的是用API ShowCursor隐藏或者显示的操作
	// 返回值：true为开启状态，false为关闭状态
	//
	static bool		IsShowCursor();

	// SetWindowTitle：设置窗口名字/标题
	// 参数 szTitle：非空字符串
	//
	static void		SetWindowTitle( const char *szTitle );

	// ResizeWindow：更改窗口大小
	// 参数 iWidth：宽度，大于0小于等于1920
	// 参数 iHeight：高度，大于0小于等于1080
	//
	static void		ResizeWindow(int iWidth, int iHeight);

	// GetHwnd：获取窗口句柄
	// 返回值：窗口句柄
	//
	static void		*GetHwnd();

	// Random：获取一个大于等于0的随机数
	// 返回值：int，范围0 - 2147483648
	//
	static int		Random();

	// RandomRange：获取一个位于参数1到参数2之间的随机数
	// 返回值：int，范围iMin - iMax
	// 参数 iMin：小于iMax的整数
	// 参数 iMax：大于iMin的整数
	//
	static int		RandomRange( const int iMin, const int iMax );

	// CalLineRotation：计算两点连线的直线的旋转角度
	// 返回值：角度，范围0 - 360
	// 参数 fStartX：起始坐标X
	// 参数 fStartY：起始坐标Y
	// 参数 fEndX：终点坐标X
	// 参数 fEndY：终点坐标Y
	//
	static float	CalLineRotation( const float fStartX, const float fStartY, const float fEndX, const float fEndY );

	// RotationToVectorX：计算某个角度对应的直线向量的X方向
	// 参数 fRotation：角度，范围0 - 360
	// 返回值 ：该直线向量的X值
	//
	static float	RotationToVectorX( const float fRotation );

	// RotationToVectorY：计算某个角度对应的直线向量的Y方向
	// 参数 fRotation：角度，范围0 - 360
	// 返回值 ：该直线向量的Y值
	//
	static float	RotationToVectorY( const float fRotation );

	// DrawLine：在两点之间画一条线
	// 参数 fStartX：起始坐标X
	// 参数 fStartY：起始坐标Y
	// 参数 fEndX：终点坐标X
	// 参数 fEndY：终点坐标Y
	// 参数 fLineWidth：线的粗细，大于等于1
	// 参数 iLayer：改线所在的层，与编辑器里设置的精灵的层级是同一个概念。范围0 - 31。
	// 参数 iRed, iGreen, iBlue : 红绿蓝三原色的颜色值，范围 0 - 255
	// 参数 iAlpha：线的透明度，范围0-255. 0为全透明，255为不透明
	//
	static void		DrawLine( const float fStartX, const float fStartY, const float fEndX, const float fEndY, const float fLineWidth, const int iLayer, const int iRed, const int iGreen, const int iBlue, const int iAlpha );

	// DrawTriangle：画一个三角形
	// 参数 fX1,fX2,fX3：三角形上三个点的X坐标
	// 参数 fY1,fY2,fY3：三角形上三个点的Y坐标
	// 参数 fLineWidth：线的粗细，大于等于1
	// 参数 iLayer：该三角形所在的层，与编辑器里设置的精灵的层级是同一个概念。范围0 - 31。
	// 参数 iRed, iGreen, iBlue : 红绿蓝三原色的颜色值，范围 0 - 255
	// 参数 iAlpha：三角形的透明度，范围0-255. 0为全透明，255为不透明
	//
	static void		DrawTriangle( const float fX1, const float fY1, const float fX2, const float fY2, const float fX3, const float fY3, const float fLineWidth, const int iLayer, const int iRed, const int iGreen, const int iBlue, const int iAlpha );

	// DrawRect：画一个矩形
	// 参数 fUpperX：左上角坐标X
	// 参数 fUpperY：左上角坐标Y
	// 参数 fLowerX：右下角坐标X
	// 参数 fLowerY：右下角坐标Y
	// 参数 fLineWidth：线的粗细，大于等于1
	// 参数 iLayer：该矩形所在的层，与编辑器里设置的精灵的层级是同一个概念。范围0 - 31。
	// 参数 iRed, iGreen, iBlue : 红绿蓝三原色的颜色值，范围 0 - 255
	// 参数 iAlpha：矩形的透明度，范围0-255. 0为全透明，255为不透明
	//
	static void		DrawRect( const float fUpperX, const float fUpperY, const float fLowerX, const float fLowerY, const float fLineWidth, const int iLayer, const int iRed, const int iGreen, const int iBlue, const int iAlpha );

	// DrawCircle：画一个圆
	// 参数 fCenterX：圆心坐标X
	// 参数 fCenterY：圆心坐标Y
	// 参数 fRadius：圆的半径
	// 参数 iSegment：圆弧段数，范围4-72. 比如传入6，将得到一个6边形，段数越大越圆滑，但是画图效率越低
	// 参数 fLineWidth：线的粗细，大于等于1
	// 参数 iLayer：该圆所在的层，与编辑器里设置的精灵的层级是同一个概念。范围0 - 31。
	// 参数 iRed, iGreen, iBlue : 红绿蓝三原色的颜色值，范围 0 - 255
	// 参数 iAlpha：圆的透明度，范围0-255. 0为全透明，255为不透明
	//
	static void		DrawCircle( const float fCenterX, const float fCenterY, const float fRadius, const int iSegment, const float fLineWidth, const int iLayer, const int iRed, const int iGreen, const int iBlue, const int iAlpha );

	// GetScreenLeft：获取世界边界之左边X坐标
	// 返回值：左边界X坐标
	//
	static float	GetScreenLeft();

	// GetScreenTop：获取世界边界之上边Y坐标
	// 返回值：上边界Y坐标
	//
	static float	GetScreenTop();

	// GetScreenRight：获取世界边界之右边X坐标
	// 返回值：右边界X坐标
	//
	static float	GetScreenRight();

	// GetScreenBottom：获取世界边界之下边Y坐标
	// 返回值：下边界Y坐标
	//
	static float	GetScreenBottom();

	// LoadMap：载入新场景。注意，载入新场景的时候，旧场景的所有精灵都将被引擎删除掉，所以所有在程序中创建、复制出来的精灵都必须在调用本API之前先删除掉
	// 参数 szName：场景名字。即新建场景保存的时候取的名字，必须带小写的后缀 -- xxx.t2d。不用带路径
	//
	static void		LoadMap( const char *szName );

	//////////////////////////////////////////////////////////////////////////////////////////
	//
	// 以下API为系统API，请勿自己调用
	//
	//////////////////////////////////////////////////////////////////////////////////////////

	// GetTimeDelta：获取两次调用本函数之间的时间差
	// 返回值：float，单位 秒
	//
	static float	GetTimeDelta();
	// EngineMainLoop：引擎主循环函数。请勿自己调用
	//
	static bool		EngineMainLoop();
	// InitGameEngine：初始化引擎，请勿自己调用
	//
	static bool		InitGameEngine( HINSTANCE hInstance, LPSTR lpCmdLine );
	static bool		InitGameEngineEx( HINSTANCE hInstance, LPSTR lpCmdLine );
	// ShutdownGameEngine：关闭引擎，请勿自己调用
	//
	static void		ShutdownGameEngine();
};

//
#endif // _COMMON_API_H_