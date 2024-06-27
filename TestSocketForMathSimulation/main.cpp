#include "comm.h"
#include "sim_lib.h"
#include"socketFunctions.h"
#include <winsock2.h>
#include <vector>

int main() {
    init_socket();
    int sockfd = create_socket();
    if (sockfd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to server" << std::endl;
        CloseSocket(sockfd);
        return 1;
    }

    // 测试math_simulation通信接口
    //先发送一个Frame，Frame.command = CommCommand::CONFIG_DATA，length为几条任务
    //循环length次，每次首先发送一个Header，header.idx = i
    //header的其余部分为每个结构体的个数
    //然后发送相应的结构体
    //发送结构体顺序必须按照以下顺序
    //TorFireParmINValue、TorPluseInValue、BJInitSet、ToSonarInitValue、DecoyParm、JammerParm、Shipborn_AEJ_Parm、CJ_Parm、CR_Parm、OutBoard_AEB_Parm、SetSSGRParm、SetDCGRParm、SetTarChangeParm
    TorFireParmINValue torFireParmINValue{};
    torFireParmINValue.ELR = -1;
    TorPluseInValue torPluseInValue{};
    torPluseInValue.BHA_C_YSD=15000;
    BJInitSet bjInitSet{};
    bjInitSet.ANumLsp = 2;
    ToSonarInitValue toSonarInitValue{};
    toSonarInitValue.Storm = 1;
    DecoyParm decoyParm{};
    decoyParm.ALspTsDecoy[0] = 1.0;
    JammerParm jammerParm{};
    jammerParm.entityID = 1;
    Shipborn_AEJ_Parm shipborn_AEJ_Parm{};
    shipborn_AEJ_Parm.DJx = 5.6;
    CJ_Parm cj_Parm{};
    cj_Parm.DJx = 3.3;
    CR_Parm cr_Parm{};
    cr_Parm.DJx = 8.5;
    OutBoard_AEB_Parm outBoard_AEB_Parm{};
    outBoard_AEB_Parm.DJx = 6.7;    
    SetSSGRParm setSSGRParm{};
    setSSGRParm.number1 = 2;
    SetDCGRParm setDCGRParm{};
    setDCGRParm.number1 = 2;
    SetTarChangeParm setTarChangeParm{};
    setTarChangeParm.number1 = 2;
    Frame frame{};
    frame.command = CommCommand::CONFIG_DATA;
    int length = 2;
    frame.length = length;
    send_frame(sockfd, reinterpret_cast<char*>(&frame), sizeof(Frame));
    for (int i = 1; i < length+1; i++)
    {

        //初始化各个结构体  测试用
        std::vector<TorFireParmINValue> TorFireParmINValueVector(i,torFireParmINValue);
      
        std::vector<TorPluseInValue> TorPluseInValueVector(i+1, torPluseInValue);
        
        std::vector<BJInitSet> BJInitSetVector(i+2, bjInitSet);
       
        std::vector<ToSonarInitValue> ToSonarInitValueVector(i, toSonarInitValue);
       
        std::vector<DecoyParm> DecoyParmVector(i, decoyParm);
        
        std::vector<JammerParm> JammerParmVector(i, jammerParm);
        
        std::vector<Shipborn_AEJ_Parm> Shipborn_AEJ_ParmVector(i, shipborn_AEJ_Parm);
        
        std::vector<CJ_Parm> CJ_ParmVector(i, cj_Parm);
        
        std::vector<CR_Parm> CR_ParmVector(i, cr_Parm);
        
        std::vector<OutBoard_AEB_Parm> OutBoard_AEB_ParmVector(i, outBoard_AEB_Parm);
        
        std::vector<SetSSGRParm> SetSSGRParmVector(i, setSSGRParm);
        
        std::vector<SetDCGRParm> SetDCGRParmVector(i, setDCGRParm);
       
        std::vector<SetTarChangeParm> SetTarChangeParmVector(i*2, setTarChangeParm);

        //初始化header，标识每个结构体的个数
        Header header{};
        header.idx = i - 1;
        header.TorFireParmINValuelength = TorFireParmINValueVector.size();
        header.TorPluseInValuelength = TorPluseInValueVector.size();
        header.BJInitSetlength = BJInitSetVector.size();
        header.ToSonarInitValuelength = ToSonarInitValueVector.size();
        header.DecoyParmlength = DecoyParmVector.size();
        header.JammerParmlength = JammerParmVector.size();
        header.Shipborn_AEJ_Parmlength = Shipborn_AEJ_ParmVector.size();
        header.CJ_Parmlength = CJ_ParmVector.size();
        header.CR_Parmlength = CR_ParmVector.size();
        header.OutBoard_AEB_Parmlength = OutBoard_AEB_ParmVector.size();
        header.SetSSGRParmlength = SetSSGRParmVector.size();
        header.SetDCGRParmlength = SetDCGRParmVector.size();
        header.SetTarChangeParmlength = SetTarChangeParmVector.size();
        //发送header帧
        send_frame(sockfd, reinterpret_cast<char*>(&header), sizeof(Header));
        //顺序发送各个结构体vector的数据，注意是.data(),不能取地址为&vector
        send_frame(sockfd, reinterpret_cast<char*>(TorFireParmINValueVector.data()), TorFireParmINValueVector.size() * sizeof(TorFireParmINValue));
        send_frame(sockfd, reinterpret_cast<char*>(TorPluseInValueVector.data()), TorPluseInValueVector.size() * sizeof(TorPluseInValue));
        send_frame(sockfd, reinterpret_cast<char*>(BJInitSetVector.data()), BJInitSetVector.size() * sizeof(BJInitSet));
        send_frame(sockfd, reinterpret_cast<char*>(ToSonarInitValueVector.data()), ToSonarInitValueVector.size() * sizeof(ToSonarInitValue));
        send_frame(sockfd, reinterpret_cast<char*>(DecoyParmVector.data()), DecoyParmVector.size() * sizeof(DecoyParm));
        send_frame(sockfd, reinterpret_cast<char*>(JammerParmVector.data()), JammerParmVector.size() * sizeof(JammerParm));
        send_frame(sockfd, reinterpret_cast<char*>(Shipborn_AEJ_ParmVector.data()), Shipborn_AEJ_ParmVector.size() * sizeof(Shipborn_AEJ_Parm));
        send_frame(sockfd, reinterpret_cast<char*>(CJ_ParmVector.data()), CJ_ParmVector.size() * sizeof(CJ_Parm));
        send_frame(sockfd, reinterpret_cast<char*>(CR_ParmVector.data()), CR_ParmVector.size() * sizeof(CR_Parm));
        send_frame(sockfd, reinterpret_cast<char*>(OutBoard_AEB_ParmVector.data()), OutBoard_AEB_ParmVector.size() * sizeof(OutBoard_AEB_Parm));
        send_frame(sockfd, reinterpret_cast<char*>(SetSSGRParmVector.data()), SetSSGRParmVector.size() * sizeof(SetSSGRParm));
        send_frame(sockfd, reinterpret_cast<char*>(SetDCGRParmVector.data()), SetDCGRParmVector.size() * sizeof(SetDCGRParm));
        send_frame(sockfd, reinterpret_cast<char*>(SetTarChangeParmVector.data()), SetTarChangeParmVector.size() * sizeof(SetTarChangeParm));

    }

    CloseSocket(sockfd);

    return 0;
}