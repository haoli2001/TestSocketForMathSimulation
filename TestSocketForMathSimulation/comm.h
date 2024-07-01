#ifndef COMM
#define COMM
enum class CommCommand {
	CONFIG_DATA = 0,            //配置数据命令
	CALCU = 1,                   //计算命令
	STOP = 2,                    //暂停计算命令
	EXIT = 3,                     //退出命令
	RESOURCE = 4,               //请求服务器资源
	RESULT = 5,                  //回报计算结果命令
	STATUS = 6,                  //查询服务器状态命令
	YES = 7,
	NO = 8,
	ALIVE = 9                    //心跳检测命令
};

enum class ConfigCommand {     //配置数据结构体命令
	TorFireParmINValue = 0,
	TorPluseInValue = 1,
	BJInitSet = 2,
	ToSonarInitValue = 3,
	DecoyParm = 4,
	JammerParm = 5,
	Shipborn_AEJ_Parm = 6,
	CJ_Parm = 7,
	CR_Parm = 8,
	OutBoard_AEB_Parm = 9,
	SetSSGRParm = 10,
	SetDCGRParm = 11,
	SetTarChangeParm = 12,
	Over = 13

};
enum class ServerStatus {                         //服务器状态
	MANAGE_CONNECT_SUCCESS = 0,          //管理端口连接成功
	MANAGE_CONNECT_FAIL = 1,              //管理端口连接失败
	READY_FOR_CALCU = 2,                   //准备计算
	CALCU_ING = 3,                          //正在计算
	CALCU_OVER = 4,                        //计算结束
	EXIT = 5                                //退出
};

struct Frame
{
	CommCommand command;
	int length;
	ServerStatus serverstatus;
	char task_folder[1024];//frame帧新增任务文件夹路径，用于保存计算过程中的中间过程数据
};

struct Resource
{
	float cpu_usage_rate;	//cpu占用率
	float mem_usage_rate;	//内存占用率
};
struct TotalResource
{
	Resource resource_1;
	Resource resource_2;
	Resource resource_3;
};

//第0条是全结构体每个长度都不为0
//第0条之后是相应不同结构体的个数，只有修改的!紧跟相应结构体的数据
struct ConfigInfo
{
	int idx;
	ConfigCommand configcommand;
	int length;

};

struct Header
{
	int gk_num;//工况总数目
	int xd_num;//当前发送任务的工况条次的想定总数目
	int gk_idx;//工况索引
	int xd_idx;//想定索引
	int TorFireParmINValuelength;//每个结构体的个数
	int TorPluseInValuelength;
	int BJInitSetlength;
	int ToSonarInitValuelength;
	int DecoyParmlength;
	int JammerParmlength;
	int Shipborn_AEJ_Parmlength;
	int CJ_Parmlength;
	int CR_Parmlength;
	int OutBoard_AEB_Parmlength;
	int SetSSGRParmlength;
	int SetDCGRParmlength;
	int SetTarChangeParmlength;
};


//char data[1024];

#endif // COMM
