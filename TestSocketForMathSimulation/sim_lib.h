#ifndef SIM_LIB_H
#define SIM_LIB_H

#define CONFIG_TYPE_NUMS 2
#define CONFIG_INT_NUMS 2
#define CONFIG_FLOAT_NUMS 11
//#define CONFIG_CHAR_NUMS 20
#define RESULT_TYPE_NUMS 2
#define RESULT_INT_NUMS 6
#define RESULT_FLOAT_NUMS 6
//#define RESULT_CHAR_NUMS 20
#include <iostream>
#include <sstream>
#include <iostream>
#include <type_traits>
#include <utility> 
#include <vector>
// for std::forward
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/serialization/utility.hpp>
//#include <boost/serialization/serialization.hpp>

//#include "ZDTest.h"//这里包含了sim_run
//从进程的状态
enum class ProcStatus
{
	READY_FOR_CALCU = 0,
	START_TO_CALCU,
	OVER,
	SLAVEPROCESS_EXIT,
	EXIT
};


//仿真输入参数
struct ConfigStruct
{
	ProcStatus command;
	int idx;
	//int arg_int[3];//用户仿真模型的输入
	float arg[11];
};


struct ResultStruct
{
	int idx;  //此项必须需要
	int Over;
	int ThitTargetID;
	int Over1;
	int ThitTargetID1;
	int NumYL;
	double Rtg;
	double Voyaget;
	double Tt;
	double Rtg1;
	double Voyaget1;
	double Tt1;
};

//仿真输出参数 SS
struct FinalResultStruct//最终的结果结构体，根据Result判读得到
{
	//int Over;
	//double Rtg;
	//double Voyaget;
	//double Tt;
	//int ThitTargetID;//写文件输出时的顺序是这个
	//为了字节对齐，int和int放在一起
	int idx;
	int Over;
	int ThitTargetID;
	double Rtg;
	double Voyaget;
	double Tt;

};

//--------------------鱼雷初始设定参数（由水下平台发给鱼雷）-----------------------//
typedef struct
{
	int     entityID;	                // 真实批号
	int     EM_YSD;                     // 遭遇攻击模式,0-正常攻击，1-遭遇攻击，模型中还没引入
	int		ELR;                        // 水面目标舷别，-1-左舷，1-右舷
	int     Ss;                         // 自适应选择，0-自适应；1-不自适应
	int     YLLB;                       // 鱼雷雷别：0-战雷；1-操雷,信息规范无
	int     TA;                         // 操雷近程规避 ,信息规范无
	int     HVX;                        // 航行速度/断线速度，0：28kn,1:36kn,2:45kn,3:50kn,4:60kn
	int		GX;						    // 发射管弦别,信息规范无
	int		WGH;					    // 使用方式,0-线导,1-自导,2-齐射(齐射模式：实例化两条鱼雷，初始装订参数中除了一次转角和二次转角的值相反，其余值一样)
	int		FRTAP;				        // 自导方式，1-主被动反潜，2-主被动反舰，3-被动反舰，4-尾流反舰，5-直航反舰。
	int     FYinXinPV;                  // 引信工作频率, 0-f1，1-f2，2-f3，3-f4，模型中还没引入
	int     HC;                         // 水文条件，0-良好，1-恶劣
	int     WLXZ;                       // 尾流攻击选择，0-7：第一至第八条尾流 ,信息规范无
	int     Testsitetype;               // 试验场地，0：湖上，1：海上 ,信息规范无
	double	InitX;				        // 发射X
	double	InitY;				        // 发射深度
	double	InitZ;				        // 发射Z
	double	StartPsin;			    	// 发射航向
	double	StartSpeed;                 // 出管速度 ,信息规范无
	double  Starttheta;                 // 发射俯仰角
	double  Startphi;                   // 发射横滚角
	double  SSetyh;                     // 尾流搜索深度,信息规范无，要与HXSetyh合并
	double  TorMoveRange;               // 机动搜索鱼雷距离,信息规范无
	double	MinDepth;				    // 上限深度,范围7m～100m，最小权值1m；默认值7m
	double	MaxDepth;				    // 下限深度,范围30m～610m，最小权值1m；默认值610m
	double	HXSetyh;					// 搜索深度,主被动反潜：范围20～500m，默认值100m;主被动反舰：范围15～35m，默认值20m;被动反舰：范围15～35m，默认值20m; 尾流反舰：范围7～10m，默认值7m; 直航反舰：范围7～10m，最小权值1m,默认值7m；
	double	MoveSetyh;					// 航行深度,范围20m～400m，最小权值1m；默认值30m ，模型中还没引入
	double	TotalVoyage;				// 鱼雷航程，范围800m～100000m，最小权值1m；战雷、微爆战雷，默认值100000m；操雷、模拟战雷，默认值10000m，
	double	Guidedistance;			    // 自导开机距离，正常攻击模式，范围800m～65000m，默认值800m；遭遇攻击模式，范围500m～65000m，默认值500m；最小权值1m
	double	FirstPsin;					// 一次转角,范围0°～±180°，最小权值0.1°；以发射航向为基准，＋为右，－为左
	double	SecondPsin;					// 二次转角/断线航向角,范围0°～±180°/0°～360°，最小权值0.1° ,以鱼雷完成一次转角后的航向为基准，＋为右，－为左
	double  Voyage_Psin;                // 二次转角前直航距离（必须小于自导开机距离Guidedistance）,范围0m～60000m，最小权值1m
	double  R0_Act;                     // 默认是3000.0 ,信息规范无
	double  R0_Pas;                     // 默认是2000.0 ,信息规范无
	double  TarYsu;                     // 目标属性 ,信息规范无
	double  SearchSpeed;                // 初始搜索速度 ,信息规范无
	double  RadarSet;                   // 中继释放距离，范围300m～65000m，最小权值1m。模型中还没引入
}TorFireParmINValue;

//--------------------鱼雷初始预设定补充信息，模型中还没引入-----------------------//
typedef struct
{
	int     entityID;	   // 真实批号
	int     DPM_C_YSD;     // 反潜单平面跟踪标志，0-双平面，1-单平面
	int     GJBT_C_YSD;    // 反潜攻击本艇标志，0-不攻击，1-攻击
	int     WFX_C_YS;      // 尾流过靶反向跟踪，0-不反向，1-反向
	int     GB_C_YSD;      // 规避停车标志，0-不规避，1-规避
	int     PBCD_C_YSD;    // 屏蔽目标尺度识别结果标志，0-无效，1-点目标，2-线目标
	int     MBLX_C_YSD;    // 目标类型标志，0-真实目标，1-固定靶，2-活动靶
	int     COM4_C_YSD;    // 操雷试验设定组合字
	int     RTZS_YSD;      // 再规划搜索自导方式，0-无效，1-主被动反潜，2-主被动反舰，3-被动反舰，4-尾流反舰
	int     TMZS_YSD;      // 再规划搜索弹道，0-无效，1-圆周，2-直航，3-之字形
	double  HXZS_YSD;      // 再规划搜索航向，范围0～360°，最小权值0.1°
	double  DZS_YSD;       // 再规划搜索距离，范围0m～60000m，最小权值1m
	double  HQSD_YSD;      // 海区深度，范围30m～5000m，最小权值1m
	double  MBFW_YSD;      // 目标参考方位，范围0°～360°，最小权值0.1°；鱼雷发射点指北坐标系
	double  MBR_YSD;       // 目标参考距离，范围0m～60000m，最小权值1m；鱼雷发射点指北坐标系
	double  MBHX_YSD;      // 目标参考航向, 范围0°～360°，最小权值0.1°
	double  MBHS_YSD;      // 目标参考航速, 范围0°～30m/s，最小权值0.5m/s
	double  BHA_C_YSD;     // 保护参数a,范围0m～±30000m，最小权值1m；鱼雷发射点指北坐标系
	double  BHB_C_YSD;     // 保护参数b,范围0m～±30000m，最小权值1m；鱼雷发射点指北坐标系
	double  BHC_C_YSD;     // 保护参数c,范围0m～±30000m，最小权值1m；鱼雷发射点指北坐标系
	double  BHD_C_YSD;     // 保护参数d,范围0m～±30000m，最小权值1m；鱼雷发射点指北坐标系
}TorPluseInValue;

//发射平台、目标初始设定参数
typedef struct
{
	int    entityID;	                // 真实批号
	int    Tar1_Typem;                //型号: 0 –039艇,1-09I艇,2-09III艇,3-航母,4-驱逐,5-护卫舰,6-民用渔船,7-民用货轮,8-其他
	int    Tar_sign;                 //目标标志, 0-点诱饵，1-线诱饵 2-体诱饵，3-真实水面目标，4-真实水下目标，5-水面目标+尾流，6-尾流
	int    LNumLsp;                 // 目标水平亮点数
	int    ANumLsp;                // 目标垂直亮点数
	double	InitBJX;					// 发射X
	double	InitBJY;					// 发射深度
	double	InitBJZ;					// 发射Z
	double	InitBJPsi;					// 初始航向角
	double	InitBJSpeed;				// 速度
	double  Pn;                         // 声源级
	double  LspTsL[5];                   // 目标水平亮点强度
	double  LspTsA[5];                   // 目标垂直亮点强度
	double  Length;					    // 舰船长度
	double	Width;					    // 舰船宽度
	double	WidthTail;			     	// 尾部宽度
	double  High;                       // 目标高度
}BJInitSet;

//海洋环境参数
typedef struct
{
	int      Storm;            // 海况
	int      SeaTopSta;        // 海面状况          
	int      seaBtmSta;        // 海底类型
	int      Kt;               // 温度（声速）数组大小                              
	int      TorC;             // 温度/声速选择标志         
	int      noiseNum;         // 自噪声数组大小
	int    SeaPar_RainFall;    // 雨量大小
	int    SeaPar_FogLevel;    // 雾等级  
	double   Hm;               // 海深
	double   Sa;               // 含盐度	                                                                                   	
	double   Mo;               // 体积混响反向散射系数                              
	double   Ht[30];           // 温度梯度测量深度数组                              
	double   Ct[30];           // 测量深度上对应的声速数组                          
	double   Tt[30];           // 测量深度上对应的温度数组                          
	double   noiseHeight[20];  // 自噪声测量深度
	double   noisePa[20];      // 自噪声强度
	double   soundShade;       // 水声吸收衰减
	double   windVelocity;     // 海面风速
	double   setythYBC;        // 跃变层深度,正值，单位m，若无法给出，赋0值
}ToSonarInitValue;

//水声对抗干扰
typedef struct          //诱饵干扰器参数
{
	long     entityID;	       // 真实批号
	int    Tar_sign;                 //目标标志, 0-点诱饵，1-线诱饵 2-体诱饵，3-真实水面目标，4-真实水下目标，5-水面目标+尾流，6-尾流
	int      flageDecoy;      // 诱饵有效标志位,0:无效 1：有效
	int      DecoyAct;        // 回波有效，即可被鱼雷检测
	int      typeDecoy;       // 诱饵类型（0-574型悬浮式声诱饵；1-575型自航式声诱饵；2-581A型自航式声诱饵，3-通用自航式诱饵，4-拖曳式诱饵 ）
	int      DDmode;          // 弹道模式 （575声诱饵：9种弹道，弹道1到弹道9；581A声诱饵：12种弹道，弹道1到弹道12）
	int      changePsit;       // 变航向标志，不用从界面接值
	int      FRTAPDecoy;      // 工作方式，0-主动，1-被动，2-主被动联合，默认2
	int    LNumLsp;          //水平亮点数
	int    ANumLsp; // 垂直亮点数
	double   Setpsione;       // 初始转角1（0°~±100°，以发射方向为基准）
	double   Setpsitwo;       // 初始转角2
	double   Setpsithree;      // 初始转角3
	double   Setposyone;      // 工作深度1
	double   Setposytwo;      // 工作深度2
	double   Setposythree;     // 工作深度3
	double   Setspeedone;     // 工作速度1
	double   Setspeedtwo;     // 工作速度2
	double   Setspeedthree;    // 工作速度3
	double   Settimeone;      // 变化时间1，通用自航式诱饵用
	double   Settimetwo;      // 变化时间2，通用自航式诱饵用
	double   Settimethree;     // 变化时间3，通用自航式诱饵用
	double   TSR;             // 回波特性，鱼雷主动检测时用 ，574，575：28dB
	double   SLN;             // 辐射噪声，鱼雷被动检测时用 ，574，575：185dB； 581A：184dB
	double   tDUDecoy;        // 诱饵有效工作总时长
	double   tRL0Decoy;        // 诱饵释放时间
	double   POSDecoy[3];      // 发射时刻诱饵位置信息，x/y/z
	double   vDecoy;           // 发射时刻诱饵的真实运动速度 ,单位：节
	double   psiDecoy;          // 发射时刻诱饵的航向角
	double   towedLength;      // 声诱饵的长度，581A声诱饵：80米
	double   LspTsDecoy[5];     // 水平亮点强度 ，581A声诱饵：16，12，5，12，5；575声诱饵：单亮点
	double   ALspTsDecoy[5];   // 垂直亮点强度
	double   simvDecoy;       // 只有0-574声诱饵模拟速度  ,单位：节
	double   lineLength;       // 拖线长度，拖曳式诱饵用
	double   DecoyHigh;       // 高度
}DecoyParm;


typedef struct              //噪声干扰器
{
	long     entityID;       // 真实批号
	double   SPL;            // 噪声干扰器辐射谱级
	double   tDUJammer;      // 干扰器有效工作总时长（重要性能参数）
	double   POSJammer[3];   // 当前仿真时刻干扰器位置信息
	double   tRL0Jammer;     // 干扰器释放时间
	int      flageJammer;    // 干扰器有效标志位,0:无效 1：有效
}JammerParm;


//电磁对抗干扰
/*舰载有源干扰结构体*/
typedef struct
{
	/*通用属性参数*/
	int    entityID;	  //真实批号
	int    flageWork;  //干扰器有效标志位，0-Disable;1-Enable

	double   tRL0Work;   //干扰器释放时间
	double   tDUWork;    //干扰器有效工作总时长，4级海况条件下持续3小时
	/*设计两种布放方式，1.直接给出电磁干扰的布放位置*/
	double  DJx;			  // 大地坐标系，X轴
	double  DJy;			  // 大地坐标系，Y轴
	double  DJz;			  // 高度或深度，0为海平面，深度为负数

  /*设计两种布放方式，2.给出电磁干扰相对目标的布放距离和方位*/
	double  DJ_Tar_Dis; //释放干扰与目标相对距离
	double  DJ_Tar_Angle;//释放干扰与目标航向之间的夹角，左-，右+，0-180

	/*特有属性*/
	double L_Angle;        //水平相控阵，多波束，360°
	double V_Angle;        //俯仰方向覆盖0-24°
	double F_Scout;        //侦察频率2.4GHz-18GHz
	double F_Jam;          //干扰频率8GHz-18GHz
	double Power;          //等效功率1Mw
}Shipborn_AEJ_Parm;

/*箔条干扰结构体*/
typedef struct
{
	/*通用属性参数*/
	int    entityID;	  //真实批号
	int    flageWork;  //干扰器有效标志位，0-Disable;1-Enable

	double  tRL0Work;   //干扰器释放时间
	double  tDUWork;    //干扰器有效工作总时长，4级海况条件下持续3小时
	/*设计两种布放方式，1.直接给出电磁干扰的布放位置*/
	double  DJx;			  // 大地坐标系，X轴
	double  DJy;			  // 大地坐标系，Y轴
	double  DJz;			  // 高度或深度，0为海平面，深度为负数

  /*设计两种布放方式，2.给出电磁干扰相对目标的布放距离和方位*/
	double  DJ_Tar_Dis; //释放干扰与目标相对距离
	double  DJ_Tar_Angle;//释放干扰与目标航向之间的夹角，左-，右+，0-180

	/*特有属性*/
	double Enable_time;    //从布放到形成箔条云的时间间隔
	double RCS_Value;      //1组箔条弹的RCS可以掩护一艘护卫舰,5000平方米
}CJ_Parm;


/*充气角反干扰结构体*/
typedef struct
{
	/*通用属性参数*/
	int    entityID;	  //真实批号
	int    flageWork;  //干扰器有效标志位，0-Disable;1-Enable

	double  tRL0Work;   //干扰器释放时间
	double  tDUWork;    //干扰器有效工作总时长，4级海况条件下持续3小时
	/*设计两种布放方式，1.直接给出电磁干扰的布放位置*/
	double  DJx;			  // 大地坐标系，X轴
	double  DJy;			  // 大地坐标系，Y轴
	double  DJz;			  // 高度或深度，0为海平面，深度为负数

  /*设计两种布放方式，2.给出电磁干扰相对目标的布放距离和方位*/
	double  DJ_Tar_Dis; //释放干扰与目标相对距离
	double  DJ_Tar_Angle;//释放干扰与目标航向之间的夹角，左-，右+，0-180

	/*特有属性*/
	double Enable_time;    //从布放到形成角反干扰的时间间隔
	double RCS_Value;      //单个角反射体不小于2000平方米
}CR_Parm;


/*舷外有源诱饵结构体*/
typedef struct
{
	/*通用属性参数*/
	int    entityID;	  //真实批号
	int    flageWork;  //干扰器有效标志位，0-Disable;1-Enable

	double  tRL0Work;   //干扰器释放时间
	double  tDUWork;    //干扰器有效工作总时长，4级海况条件下持续3小时
	/*设计两种布放方式，1.直接给出电磁干扰的布放位置*/
	double  DJx;			  // 大地坐标系，X轴
	double  DJy;			  // 大地坐标系，Y轴,约100米
	double  DJz;			  // 高度或深度，0为海平面，深度为负数

  /*设计两种布放方式，2.给出电磁干扰相对目标的布放距离和方位*/
	double  DJ_Tar_Dis; //释放干扰与目标相对距离
	double  DJ_Tar_Angle;//释放干扰与目标航向之间的夹角，左-，右+，0-180

	/*特有属性*/
	double L_Angle;        //水平20°
	double V_Angle;        //俯仰20°
	double F_Jam;          //干扰频率8GHz-20GHz
	double Power;          //等效功率10Kw
}OutBoard_AEB_Parm;


//布放策略接口信息
typedef struct              //水声干扰器布放策略接口信息
{
	int    number1;               //目标个数，最多两个
	int    TarID[2];	             //目标真实批号
	int    number2;               //鱼雷个数，最多两个
	int    TorID[2];	                // 鱼雷真实批号
	int    setNumber[10];         //各类型水声干扰器数量设定，0：噪声干扰，1：悬浮诱饵干扰，2：自航式诱饵，3：拖曳式诱饵，4：575型自航式声诱饵，5：581A型自航式声诱饵
	double settime[10];           //水声干扰器布放时间，0：第一个干扰器布放时间。。。
	double setdistance[10];        //水声干扰器布放距离，根据setNumber中各类型的数量信息，进行距离设定
	double setpsi[10];            //水声干扰器布放方位，根据setNumber中各类型的数量信息，进行方位设定
	double Tarpos[6];             //目标位置
	double Tarpsi[2];             //目标航向角
	double Tarspeed[2];           //目标速度
	double Torpos[6];             //鱼雷位置
	double Torpsi[2];             //鱼雷航向角
	double Torspeed[2];           //鱼雷速度
}SetSSGRParm;



typedef struct              //电磁布放策略接口信息
{
	int    number1;               //目标个数，最多两个
	int    TarID[2];	             //目标真实批号
	int    number2;               //无人机个数，最多两个
	int    RadID[2];	             //无人机真实批号,继承鱼雷ID?
	int    setNumber[10];          //各类型电磁干扰器数量设定，0：舰载有源，1：舷外有源，2：箔条干扰，3：充气角反
	double settime[10];            //电磁干扰器布放时间，0：第一个干扰器布放时间。。。
	double setdistance[10];        //电磁干扰器布放距离，根据setNumber中各类型的数量信息，进行距离设定
	double setpsi[10];            //电磁干扰器布放方位，根据setNumber中各类型的数量信息，进行方位设定
	double Tarpos[6];             //目标位置
	double Tarpsi[2];              //目标航向角
	double Tarspeed[2];           //目标速度
	double WRJpos[6];            //无人机位置
	double WRJpsi[2];             //无人机航向角
}SetDCGRParm;


typedef struct              //目标转向机动规避策略接口信息，
{
	int    number1;               //目标个数，最多两个
	int    TarID[2];	             //目标真实批号
	int    number2;               //鱼雷个数，最多两个
	int    TorID[2];	                // 鱼雷真实批号

	double settime[4];            //目标变速变航向设定时间，0~1：目标1信息，2~3：目标2信息
	double Tarpos[6];             //目标位置
	double Tarpsi[2];             //目标航向角
	double Tarspeed[4];           //目标速度，0~1：目标1变速信息，2~3：目标2变速信息
	double TarAngVelocity[2];     //目标转向角速度，0：目标1信息，1：目标2信息
	double Torpos[6];             //鱼雷位置
	double Torpsi[2];             //鱼雷航向角
	double Torspeed[2];           //鱼雷速度
}SetTarChangeParm;


//class TaskInfo {
//public:
//	TaskInfo() {};
//	TaskInfo(int idx,std::vector<TorFireParmINValue> &TorFireParmINValue, std::vector<TorPluseInValue> &TorPluseInValue, std::vector<BJInitSet> BJInitSet
//	, std::vector<ToSonarInitValue> ToSonarInitValue, std::vector<DecoyParm> DecoyParm, std::vector<JammerParm> JammerParm,std::vector<Shipborn_AEJ_Parm> Shipborn_AEJ_Parm,
//	std::vector<CJ_Parm> CJ_Parm, std::vector<CR_Parm> CR_Parm, std::vector<OutBoard_AEB_Parm> OutBoard_AEB_Parm, std::vector<SetSSGRParm> SetSSGRParm,
//	std::vector<SetDCGRParm> SetDCGRParm, std::vector<SetTarChangeParm> SetTarChangeParm)
//		:_idx(idx),_TorFireParmINValue(TorFireParmINValue), _TorPluseInValue(TorPluseInValue) , _BJInitSet(BJInitSet), _ToSonarInitValue(ToSonarInitValue),
//		_DecoyParm(DecoyParm),_JammerParm(JammerParm),_Shipborn_AEJ_Parm(Shipborn_AEJ_Parm), _CJ_Parm(CJ_Parm),_CR_Parm(CR_Parm),_OutBoard_AEB_Parm(OutBoard_AEB_Parm),
//		_SetSSGRParm(SetSSGRParm),_SetDCGRParm(SetDCGRParm),_SetTarChangeParm(SetTarChangeParm){}
//	int get_idx() const { return _idx; }
//	const std::vector<TorFireParmINValue>&  get_TorFireParmINValue() const { return _TorFireParmINValue; }
//	const std::vector<TorPluseInValue>&  get_TorPluseInValue() const { return _TorPluseInValue; }
//	const std::vector<BJInitSet>& 
//	const std::vector<ToSonarInitValue>&
//	const	std::vector<DecoyParm>&
//		const	std::vector<JammerParm>&
//		const	std::vector<Shipborn_AEJ_Parm>&
//		const	std::vector<CJ_Parm>&
//		const	std::vector<CR_Parm>&
//		const	std::vector<OutBoard_AEB_Parm>&
//		const	std::vector<SetSSGRParm>&
//		const	std::vector<SetDCGRParm>&
//		const	std::vector<SetTarChangeParm>&
//private:
//	friend class boost::serialization::access;
//	template<class Archive>
//	void serialize(Archive& ar, const unsigned int version) {
//		ar & final_result & result_vector &idx;
//	}
//	int _idx;
//	std::vector<TorFireParmINValue> _TorFireParmINValue;
//	std::vector<TorPluseInValue> _TorPluseInValue;
//	std::vector<BJInitSet> _BJInitSet;
//	std::vector<ToSonarInitValue> _ToSonarInitValue;
//	std::vector<DecoyParm> _DecoyParm;
//	std::vector<JammerParm> _JammerParm;
//	std::vector<Shipborn_AEJ_Parm> _Shipborn_AEJ_Parm;
//	std::vector<CJ_Parm> _CJ_Parm;
//	std::vector<CR_Parm> _CR_Parm;
//	std::vector<OutBoard_AEB_Parm> _OutBoard_AEB_Parm;
//	std::vector<SetSSGRParm> _SetSSGRParm;
//	std::vector<SetDCGRParm> _SetDCGRParm;
//	std::vector<SetTarChangeParm> _SetTarChangeParm;
//};



class TaskInfo {
public:
	int idx;

	std::vector<TorFireParmINValue> torFireParmINValues;
	std::vector<TorPluseInValue> torPluseInValues;
	std::vector<BJInitSet> bjInitSets;
	std::vector<ToSonarInitValue> toSonarInitValues;
	std::vector<DecoyParm> decoyParms;
	std::vector<JammerParm> jammerParms;
	std::vector<Shipborn_AEJ_Parm> shipbornAEJParms;
	std::vector<CJ_Parm> cjParms;
	std::vector<CR_Parm> crParms;
	std::vector<OutBoard_AEB_Parm> outBoardAEBParms;
	std::vector<SetSSGRParm> setSSGRParms;
	std::vector<SetDCGRParm> setDCGRParms;
	std::vector<SetTarChangeParm> setTarChangeParms;

	// 默认构造函数
	TaskInfo() : idx(0) {}

	// 可变参数模板构造函数，用于初始化成员变量
	template<typename... Vectors>
	TaskInfo(int idxValue, Vectors&&... vectors) : idx(idxValue) { //这里考虑的是可能传入不等长度的vector
		assignVectors(std::forward<Vectors>(vectors)...);
	}

	// 拷贝构造函数，同时拷贝idx和所有vector成员
	TaskInfo(const TaskInfo& other)
		: idx(other.idx),
		torFireParmINValues(other.torFireParmINValues),
		torPluseInValues(other.torPluseInValues),
		bjInitSets(other.bjInitSets),
		toSonarInitValues(other.toSonarInitValues),
		decoyParms(other.decoyParms),
		jammerParms(other.jammerParms),
		shipbornAEJParms(other.shipbornAEJParms),
		cjParms(other.cjParms),
		crParms(other.crParms),
		outBoardAEBParms(other.outBoardAEBParms),
		setSSGRParms(other.setSSGRParms),
		setDCGRParms(other.setDCGRParms),
		setTarChangeParms(other.setTarChangeParms) {
	}

	//// 序列化函数
	//template<class Archive>
	//void serialize(Archive& ar, const unsigned int version) {
	//	ar & idx;
	//	ar & torFireParmINValues;
	//	ar & torPluseInValues;
	//	ar & bjInitSets;
	//	ar & toSonarInitValues;
	//	ar & decoyParms;
	//	ar & jammerParms;
	//	ar & shipbornAEJParms;
	//	ar & cjParms;
	//	ar & crParms;
	//	ar & outBoardAEBParms;
	//	ar & setSSGRParms;
	//	ar & setDCGRParms;
	//	ar & setTarChangeParms;
	//}

private:
	// 递归终止函数
	void assignVectors() {}

	// 递归展开处理每个传入的vector
	template<typename T, typename... Vectors>
	void assignVectors(T&& vector, Vectors&&... vectors) {
		assignVector(std::forward<T>(vector));
		assignVectors(std::forward<Vectors>(vectors)...);
	}

	// 根据vector的类型赋值给相应的成员
	template<typename VectorType>
	void assignVector(VectorType&& vector) {
		assignVectorImpl(std::forward<VectorType>(vector), typename std::decay<VectorType>::type());
	}

	// 用于不同类型vector的特化函数，使用std::is_same在编译时判断类型
	template<typename VectorType>
	void assignVectorImpl(VectorType&& vector, std::vector<TorFireParmINValue>) {
		torFireParmINValues = std::forward<VectorType>(vector);
	}

	template<typename VectorType>
	void assignVectorImpl(VectorType&& vector, std::vector<TorPluseInValue>) {
		torPluseInValues = std::forward<VectorType>(vector);
	}

	template<typename VectorType>
	void assignVectorImpl(VectorType&& vector, std::vector<BJInitSet>) {
		bjInitSets = std::forward<VectorType>(vector);
	}

	template<typename VectorType>
	void assignVectorImpl(VectorType&& vector, std::vector<ToSonarInitValue>) {
		toSonarInitValues = std::forward<VectorType>(vector);
	}

	template<typename VectorType>
	void assignVectorImpl(VectorType&& vector, std::vector<DecoyParm>) {
		decoyParms = std::forward<VectorType>(vector);
	}

	template<typename VectorType>
	void assignVectorImpl(VectorType&& vector, std::vector<JammerParm>) {
		jammerParms = std::forward<VectorType>(vector);
	}

	template<typename VectorType>
	void assignVectorImpl(VectorType&& vector, std::vector<Shipborn_AEJ_Parm>) {
		shipbornAEJParms = std::forward<VectorType>(vector);
	}

	template<typename VectorType>
	void assignVectorImpl(VectorType&& vector, std::vector<CJ_Parm>) {
		cjParms = std::forward<VectorType>(vector);
	}

	template<typename VectorType>
	void assignVectorImpl(VectorType&& vector, std::vector<CR_Parm>) {
		crParms = std::forward<VectorType>(vector);
	}

	template<typename VectorType>
	void assignVectorImpl(VectorType&& vector, std::vector<OutBoard_AEB_Parm>) {
		outBoardAEBParms = std::forward<VectorType>(vector);
	}

	template<typename VectorType>
	void assignVectorImpl(VectorType&& vector, std::vector<SetSSGRParm>) {
		setSSGRParms = std::forward<VectorType>(vector);
	}

	template<typename VectorType>
	void assignVectorImpl(VectorType&& vector, std::vector<SetDCGRParm>) {
		setDCGRParms = std::forward<VectorType>(vector);
	}

	template<typename VectorType>
	void assignVectorImpl(VectorType&& vector, std::vector<SetTarChangeParm>) {
		setTarChangeParms = std::forward<VectorType>(vector);
	}

	// 避免匹配失败的编译错误
	template<typename T>
	struct always_false : std::false_type {};

	template<typename VectorType, typename U>
	void assignVectorImpl(VectorType&& vector, U) {
		static_assert(always_false<U>::value, "Type mismatch in TaskInfo constructor");
	}
};




//namespace boost {
//	namespace serialization {
//
//		template<class Archive>
//		void serialize(Archive& ar, TorFireParmINValue& to, const unsigned int version) {
//			ar & to.ELR;
//			ar & to.EM_YSD;
//			ar & to.entityID;
//			ar & to.FirstPsin;
//			ar & to.FRTAP;
//			ar & to.FYinXinPV;
//			ar & to.Guidedistance;
//			ar & to.GX;
//			ar & to.HC;
//		}
//
//	} // namespace serialization
//} // namespace boost

#endif // !SIM_LIB_H
