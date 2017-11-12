/*!******************************************************************************************************
*	@file 	appuds.h
*	@brief 	appuds.c头文件
*	@author Matt Zhang
*	@version 0.1
*	@date  2012-2-15
*	@warning
*                (c) Copyright 2010, Vast Automotive Technology(Shanghai) Co., Ltd.
*                                       All Rights Reserved
*
**********************************************************************************************************/
#ifndef APPLAYER_UDS_H
#define APPLAYER_UDS_H

#ifdef   APPLAYER_GLOBALS
	#define  APPLAYER_EXT
#else
	#define  APPLAYER_EXT  extern
#endif
#include "NetworkLayerServices_GF.h"
#include "NetworkLayerServices_GF_private.h"

/*--------------------------------变量类型自定义 BEGIN--------------------------------*/
typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;
typedef signed   char  INT8S;
typedef unsigned int   INT16U;
typedef signed   int   INT16S;
typedef unsigned long  INT32U;
typedef signed   long  INT32S;
typedef float          FP32;
typedef double         FP64;
#define BYTEPTR        unsigned char*
/*--------------------------------变量类型自定义END--------------------------------*/
/*
*********************************************************************************************************
*                                                MACROS
*********************************************************************************************************
*/
/*--------------------------------Boot及AppCode定义BEGIN--------------------------------*/
#define APP_CODE    1//Boot程序设置为0；正常程序设置为1
#define UDS_DTC_OPEN 1//1就是使用UDS定义的DTC变量，0就是使用自定义
/*--------------------------------Boot及AppCode定义END----------------------------------*/

/*--------------------------------ECU RESET 地址 BEGIN----------------------------------*/
#define ECU_SWRESET   (void (*)(void))  0x3F7FF6//flash F首地址
/*--------------------------------ECU RESET 地址 END----------------------------------*/

/*--------------------------------带Sub_Function功能服务号定义 BEGIN----------------------------------*/
#define DIAGNOSTIC_SESSION_CONTROL 0x10 /*会话模式*/
#define ECU_RESET 0x11/*ECU RESET*/
#define SECURITY_ACCESS 0x27/*解密*/
#define COMMUNICATION_CONTROL 0x28/*通信*/
#define TESTER_PRESENT 0x3E/*握手*/
#define CONTROL_DTC_SETTING 0x85/*DTC设置*/
#define RESPONSE_ON_EVENT 0x86/*预留*/
#define LINK_CONTROL 0x87 /*预留*/
#define DYNAMICALLY_DEFINE_DATA_IDENTIFIER 0x2C/*预留*/
#define READ_DTC_INFORMATION 0x19/*读取故障码*/
#define ROUTINE_CONTROL 0x31/*流控制*/
/*--------------------------------带Sub_Function功能服务号定义 END-------------------------------------*/

/*--------------------------------不带Sub_Function功能服务号定义 BEGIN----------------------------------*/
#define SECURED_DATA_TRANSMISSTION 0x84/*预留*/
#define READ_DATA_BY_IDENTIFIER 0x22/*DID读取数据*/
#define READ_MEMORY_BY_ADDRESS 0x23/*地址读取数据*/
#define READ_SCALING_DATA_BY_IDENTIFIER 0x24/*预留*/
#define READ_DATA_BY_PERIODIC_IDENTIFIER 0x2A/*预留*/
#define WRITE_DATA_BY_IDENTIFIER 0x2E/*DID写数据*/
#define WRITE_MEMORY_BY_ADDRESS 0x3D/*地址写数据*/
#define CLEAR_DIAGNOSTIC_INFORMATION 0x14/*清除故障码写数据*/
#define INPUT_OUTPUT_CONTROL_BY_IDENTIFIER 0x2F/*输入输出控制*/
#define REQUEST_DOWNLOAD 0x34/*请求下载*/
#define REQUEST_UPLOAD 0x35/*预留*/
#define TRANSFER_DATA 0x36/*发送数据*/
#define REQUEST_TRANSFER_EXIT 0x37/*请求发送退出*/
/*--------------------------------不带Sub_Function功能服务号定义 END-------------------------------------*/


#if APP_CODE==0
#define CODECEF                             4 /*周期与1ms的比例*/
#define CODE_CYCLE                          1 /*程序周期*/
#else
#define CODE_CYCLE                          5 /*程序周期*/
#endif
#define NR_SI                               0x7F/*负回应NSID*/
#define DEFAULT_SESSION                     0x01/*默认会话模式*/
#define PROGRANMMING_SESSION                0x02/*编程会话模式*/
#define EXTEND_SESSION                      0x03/*扩展会话模式*/
#define SAFETY_SESSION                      0x04/*预留*/

#define HARD_RESET                          0x01/*硬启动*/
#define KEYOFFON_RESET                      0x02/*预留*/
#define SW_RESET                            0x03/*预留*/
#define RAPIDSHUTDOWN_ENABLE                0x04/*预留*/
#define RAPIDSHUTDOWN_DISABLE               0x05/*预留*/

#define APPTONET_SENDOK                     0x01/*应用层请求网络层处理数据标志值*/

#define POS_RSP                             0x00/*负反馈标志*/
#define NEG_RSP                             0x01/*正反馈标志*/

#define SEED_KEY_TIMES                      0x02/*解密超限值*/


#define DTCSETTING_ON                       0x01/*更新DTC状态*/
#define DTCSETTING_OFF                      0x02/*不更新DTC状态*/


#define DTCGROUP                            0x00000000 /*故障码组值*/
#define ALLDTCGROUP                         0x00FFFFFF /*故障码组值*/
#define DTCFMT115031                        0x00 /*故障码依照的格式*/
#define DTCFMT14229                         0x01 /*故障码依照的格式*/
#define DTCNUM                              8    /*故障码个数*/
#define MASKSTATUS                          0x7F /*所支持的掩码*/


#if APP_CODE==1
/*-----------------------------APPCODE时间参数限值BEGIN------------------------------*/
#define  AS_TIME                            (110/CODE_CYCLE)
#define  BS_TIME                            (75/CODE_CYCLE)
#define  CR_TIME                            (150/CODE_CYCLE)

#define  P2_CANSERVER                       (50/CODE_CYCLE)   /*回复限值时间*/
#define  P2_FLEXCANSERVER                   (5000/CODE_CYCLE) /*增强型延时时间*/
#define  S3SERVER                           (5000/CODE_CYCLE) /*非默认会话模式限值时间*/
#define  SECUR_LIMIT_TIME                   (10000/CODE_CYCLE)/*加密限值时间*/
/*-----------------------------APPCODE时间参数限值END------------------------------*/
#else
/*-----------------------------BOOTCODE时间参数限值BEGIN------------------------------*/
#define  AS_TIME                            (110*CODECEF/CODE_CYCLE)
#define  BS_TIME                            (75*CODECEF/CODE_CYCLE)
#define  CR_TIME                            (150*CODECEF/CODE_CYCLE)

#define  P2_CANSERVER                       (50*CODECEF/CODE_CYCLE)
#define  P2_FLEXCANSERVER                   ((INT32U)5000*CODECEF/CODE_CYCLE)
#define  S3SERVER                           ((INT32U)5000*CODECEF/CODE_CYCLE)
#define  SECUR_LIMIT_TIME                   ((INT32U)10000*CODECEF/CODE_CYCLE)
/*-----------------------------BOOTCODE时间参数限值END------------------------------*/
#endif
/*-----------------------------Boot刷写AppCode的地址范围BEGIN-----------------------------*/
#define  ERASE_FLASH_SECTORB_ADR            0x3F4000
#define  ERASE_FLASH_SECTORB_LENGTH         0x001FFE

#define  ERASE_FLASH_SECTORF_ADR            0x3EC000
#define  ERASE_FLASH_SECTORF_LENGTH         0x006000

#define  ERASE_FLASH_SECTORD_ADR            0x3F5FFE
#define  ERASE_FLASH_SECTORD_LENGTH         0x000002

#define  ERASE_FLASH_ADRBYTES               4  /*地址支持的Byte数*/
#define  ERASE_FLASH_DATALENBYTES           4  /*长度支持的Byte数*/

#define  WRITE_FLASH_ADRBYTES               4 
#define  WRITE_FLASH_DATALENBYTES           4

#define  MAX_NUM_BLOCK                      216 /*一个Block最大的数据量*/
#define  LEN_MFT                            0x20

/*-----------------------------Boot刷写AppCode的地址范围BEGIN-----------------------------*/

/*-----------------------------EEPROM地址范围BEGIN--------------------------------------*/
#define  ERASE_FLASH_SECTORC_ADR            0x3F2000
#define  ERASE_FLASH_SECTORC_LENGTH         0x002000
#define  ERASE_BASE                         0x3F2000
#define  ECU_SUPPROT_ADDRESSLEN             0x04
#define  MAX_DATANUMBYTE                    0x02
#define  RWDATA_MINADR                      0x3F2000
#define  RWDATA_MAXADR                      0x3F3FFF
#define  MAX_MEMWRITENUM                    100
/*-----------------------------EEPROM地址范围END---------------------------------------*/

/*-----------------------------负面故障码定义BEGIN---------------------------------------*/
#define  SEVICE_NOTSUPPORT_ERR           0x11
#define  SUBFUNCTION_NOTSUPPORT_ERR      0x12
#define  CMD_LENGTH_ERR                  0x13
#define  CONDITION_NOTSURRORT_ERR        0x22
#define  ORDER_ERR                       0x24
#define  OVERRANGE_ERR                   0x31
#define  NOTGETAUTHORITY_ERR             0x33
#define  KEY_ERR                         0x35
#define  UNLOCKOVERTIME_ERR              0x36
#define  UNLOCKDELAY_ERR                 0x37
#define  SESSIONNOTSUPPROT_ERR           0x7F
#define  SESSION_SUB_NOTSUPPROT_ERR      0x7E
#define  FLEXRSPTIME_ERR                 0x78
#define  ERWRMEN_ERR                     0x72
#define  BLOCKSN_ERR                     0x73
#define  TRANDATA_STOP_ERR               0x71
/*-----------------------------负面故障码定义END---------------------------------------*/

/*-----------------------------故障码序号定义BEGIN---------------------------------------*/
#define  U000187   0
#define  U000288   1
#define  U000387   2
#define  U000487   3
#define  P000112   4
#define  P000209   5
#define  P000396   6
#define  P000429   7
/*-----------------------------故障码序号定义END----------------------------------------*/
/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/ 
/*-----------------------------DTC结构体3个Byte定义BEGIN----------------------------------------*/
typedef struct {
INT16U byte1;
INT16U byte2;
INT16U byte3;
}ST_DTC;
/*-----------------------------DTC结构体3个Byte定义END------------------------------------------*/

/*-----------------------------DTC Extend Data结构体4个Byte定义BEGIN----------------------------------------*/
typedef struct {
INT16U FualtCnt;
INT16U PendCnt;
INT16U AgedCnt;
INT16U AgingCnt;
}DTC_EXTENDDATA;
/*-----------------------------DTC Extend Data结构体4个Byte定义END----------------------------------------*/

/*-----------------------------DTC Snapshot Data结构体定义BEGIN----------------------------------------*/
typedef struct {
INT16U SupBatt;
INT32U Odreading;
INT16U CoolTemp;
INT16U IgStatus;
}DTC_SNAPSHOT;
/*-----------------------------DTC Snapshot Data结构体定义END----------------------------------------*/

/*-----------------------------DTC Status 结构体定义BEGIN--------------------------------------------*/
typedef struct {
       union {
      INT8U Byte;
      struct {
        INT8U testFailed    :1;                                       
        INT8U testFailedThisOperationCycle    :1;                                       
        INT8U pendingDTC    :1;                                       
        INT8U confirmedDTC    :1;                                       
        INT8U testNotCompletedSinceLastClear    :1;                                      
        INT8U testFailedSinceLastClear    :1;                                       
        INT8U testNotCompletedThisOperationCycle    :1;                                     
        INT8U warningIndicatorRequested    :1;                                       
      } Bits;
    } Status;
    //INT8U  Severity;
} ST_DTC_STATUS;
/*-----------------------------DTC Status 结构体定义END--------------------------------------------*/

/*-----------------------------Flash擦写状态枚举 结构定义BEGIN--------------------------------------------*/
typedef enum {
  noErr=0,
  WErr  
}WRFlash_Status;
/*-----------------------------Flash擦写状态枚举 结构定义END--------------------------------------------*/
typedef enum {
  TAtype_phiscal=1,
  TAtype_functional
}ETA_type;

typedef enum {
  Mtype_Diagnostics=1,
  Mtype_Rdiagnostics  
}EM_type;
/*-----------------------------解密状态枚举 结构定义BEGIN--------------------------------------------*/
typedef enum{
  Lock=0,
  UnLock_Level, 
  UnLock_Level2,
  UnLock_Level3
}SecurMode; 
/*-----------------------------解密状态枚举 结构定义END----------------------------------------------*/

/*-----------------------------Boot下载流程状态枚举 结构定义BEGIN--------------------------------------------*/
typedef enum{
  Not_Req=0,
  Req_Sucess, 
  Tran_Sucess, 
  Exit_Sucess
}DownLoadr; 
/*-----------------------------Boot下载流程状态枚举结构定义END--------------------------------------------*/

/*-----------------------------Flash片区枚举 结构定义BEGIN--------------------------------------------*/
typedef enum{
  A_Sector=0,
  B_Sector, 
  AB_Sector, 
  F_Sector
}ERASE_SECTOR; 
/*-----------------------------Flash片区枚举 结构定义END--------------------------------------------*/

/*-----------------------------Uds应用层原语 结构定义BEGIN--------------------------------------------*/
typedef struct {
INT8U A_SA;
INT8U A_TA;
ETA_type A_TA_type;
INT8U A_RA;
INT8U A_SI;
INT8U  *IndReceiveMsg_u8_Sig; 
INT16U A_PLength;
}REQ_A_PDU;/*请求原语结构体*/

typedef struct {
INT8U A_SA;
INT8U A_TA;
ETA_type A_TA_type;
INT8U A_RA;
INT8U A_NR_SI;
INT8U A_SI;
INT8U *ReqSendMsg_u8_Tmp;
INT16U A_PLength; 
}RSP_A_PDU,*LPRSP_APDU;/*回应原语结构体*/
/*-----------------------------Uds应用层原语 结构定义END--------------------------------------------*/
APPLAYER_EXT REQ_A_PDU Req_Msg;/*请求结构体变量定义*/
APPLAYER_EXT RSP_A_PDU Rsp_Msg;/*回应结构体变量定义*/

#if APP_CODE==0
APPLAYER_EXT INT8U     Jump_u8_Sig; /*Boot写程序完成不跳转标志位*/
APPLAYER_EXT INT8U     BootApp_u8_Sig;/*20ms检测状态位*/
APPLAYER_EXT INT8U     CANNumb_u8_Sig;/*CAN报文的数量*/
APPLAYER_EXT INT8U     CANIndex_u8_Sig;/*CAN报文存放数组的索引值*/
APPLAYER_EXT INT8U     CANGetOut_u8_Sig;/*CAN报文存放数组的索引值*/
APPLAYER_EXT INT8U     CANRevBuff_u8a160_Par[160];/*存放CAN报文的数组*/
APPLAYER_EXT INT16U    CANFrameLen_u16a20_Par[20];/*CAN报文的长度存储数组*/
APPLAYER_EXT INT16U    CANId_u16a20_Par[20];/*CAN报文的Id存储数组*/
APPLAYER_EXT INT8U     Jump_u8_Sig; /*Boot写程序完成不跳转标志位*/
APPLAYER_EXT INT8U     BootApp_u8_Sig;/*20ms检测状态位*/
#endif
APPLAYER_EXT INT8U     NormalComTx_u8_Sig;/*一般Can通信发送标志位，通过此标志位判断是否关闭Can的发送，Uds的can发送除外*/
APPLAYER_EXT INT8U     NormalComRx_u8_Sig;/*一般Can通信发送标志位，通过此标志位判断是否关闭Can的接收，Uds的can接收除外*/
APPLAYER_EXT INT8U     NetWorkComTx_u8_Sig;/*网络管理Can通信发送标志位*/
APPLAYER_EXT INT8U     NetWorkComRx_u8_Sig;/*网络管理Can通信接收标志位*/

APPLAYER_EXT INT8U   DtcOnOff_u8_Sig;/*DTC更新标志位，如果Dtc关闭更新标志位则DTc信息不在更新*/
APPLAYER_EXT INT8U     UDS_Timeout_u8_Sig; /*超时状态变量*/
APPLAYER_EXT INT8U     STmin_u8_Par; /*ST时间*/
APPLAYER_EXT INT8U     CFCount_u8_Sig; /*CF的计数器*/
APPLAYER_EXT INT8U     SFLength_Ovrn_u8_Sig; /*SF的长度状态*/
APPLAYER_EXT INT8U     CANLength_u8_Sig; /*CAN报文长度*/
APPLAYER_EXT INT8U     FrameSequ_u8_Sig;
APPLAYER_EXT INT8U     FrameErr_u8_Sig;/*帧错误状态*/
APPLAYER_EXT INT8U     FC_RecStatus_u8_Sig;/*FC的状态*/
APPLAYER_EXT INT8U     UDStick_u8_Par;/*基时*/
APPLAYER_EXT INT8U     STminCoef_u8_Par;/*ST时间比例*/

APPLAYER_EXT INT16U    VehicleSpeed_u16_Sig;
APPLAYER_EXT INT16U    EngineSpeed_u16_Sig;

APPLAYER_EXT INT16U    WrCheckSum_u16_Sig;/*Boot刷写程序的校验和*/
APPLAYER_EXT INT8U     SessionMode_u8_Sig;/*会话模式变量*/

APPLAYER_EXT INT16U    PEF_u16_Par;/*AppToBoot标志位位*/
APPLAYER_EXT INT16U    SVF_u16_Par;/*程序完整标志位*/
APPLAYER_EXT INT8U     PefEep_u8_Sig;/*AppToBoot写EEPROM标志位*/


#if UDS_DTC_OPEN==1
APPLAYER_EXT ST_DTC         DtcNumb_u24a8_Par[8];/*故障码结构体变量*/
APPLAYER_EXT ST_DTC_STATUS  DtcStatus_u16a8_Par[8];/*故障码状态结构体变量*/
APPLAYER_EXT ST_DTC_STATUS  LastDtcStatus_u16a8_Par[8];/*上个周期故障码状态结构体变量*/
APPLAYER_EXT DTC_EXTENDDATA DtcExtend_u64a8_Par[8];/*扩展数据结构体变量*/
APPLAYER_EXT DTC_SNAPSHOT   DtcSnapShot_u80a8_Par[8];/*Snapshot数据结构体变量*/
#endif
APPLAYER_EXT INT8U    ParkStatus_u8_Sig;/*Park状态变量和将实际值赋值给这个变量*/
APPLAYER_EXT INT8U    EppStatus_u8_Sig;/*EPP状态变量也是和正常程序交互的变量*/
APPLAYER_EXT INT16U   MotorSpd_u16_Sig;/*电机转速变量也是和正常程序交互的变量*/
APPLAYER_EXT INT16S   MotorSpd_s16_Sig;/*电机转速变量也是和正常程序交互的变量*/

APPLAYER_EXT INT8U    TesterRefNumb_u8a6_Par[6];
APPLAYER_EXT INT8U    Odmeter_u8a3_Sig[3];
APPLAYER_EXT INT8U    Resever_u8a2_Sig[2];
APPLAYER_EXT INT8U    OldSessionMode_u8_Sig;/*老的会话模式*/

APPLAYER_EXT INT8U    EepRomTimes_u8_Sig;


APPLAYER_EXT INT16U   BootTimes_u16_Par;/*Boot刷写次数*/
APPLAYER_EXT INT16U   PifPtcb_u16a16a16_Par[16][8];/*DID:FF10-FF1F*/
APPLAYER_EXT INT16U   BootSwRefNumb_u16a10_Par[5];/*DID:F183*/
APPLAYER_EXT INT16U   ECUPartNumb_u16a6_Par[3];/*DID:F187*/
APPLAYER_EXT INT16U   SysSupplierId_u16a6_Par[3];/*DID:F18A*/
APPLAYER_EXT INT16U   Vin_u16a17_Par[9];/*DID:F190*/
APPLAYER_EXT INT16U   EcuHwNumb_u16a6_Par[3];/*DID:F191*/
APPLAYER_EXT INT16U   EcuHwRefNumb_u16a10_Par[5];/*DID:F192*/
APPLAYER_EXT INT16U   EcuSwRefNumb_u16a10_Par[5];/*DID:F194*/

APPLAYER_EXT INT16U   EcuCalSwNumb_u16a6_Par[3];/*DID:F1A1*/
APPLAYER_EXT INT16U   EcuNetRefNumb_u16a6_Par[3];/*DID:F1A2*/
APPLAYER_EXT INT16U   VehFeature_u16a20_Par[10];/*DID:F1A8*/
APPLAYER_EXT INT16U   EcuMData_u16a3_Par[2];/*DID:F18B*/
APPLAYER_EXT INT16U   EcuSupplierSN_u16a10_Par[5];/*DID:F18C*/



APPLAYER_EXT INT16U   AsTime_Limited_u16_Par;/*网络层时间变量*/
APPLAYER_EXT INT16U   BsTime_Limited_u16_Par;/*网络层时间变量*/
APPLAYER_EXT INT16U   CrTime_Limited_u16_Par;/*网络层时间变量*/

extern const INT16U   EcuAppSwNumb_u16a6_Par[3];/*DID:F1A0*/

/*********************************************************************************************************
*                                               FUNCTIONS
*********************************************************************************************************
*/
APPLAYER_EXT  void SwReset_v_g(void);/*软件复位函数*/
APPLAYER_EXT  void   MailBoxRd_v_g(INT16U MBXnbr);/*Boot Can邮箱接收函数*/
#if APP_CODE==0
APPLAYER_EXT  void   CanOutHandel_v_g(void);/*Boot Can取数据函数*/
APPLAYER_EXT INT16U  CheckAppCode_v_g(void);/*Boot Flash程序校验和函数*/
APPLAYER_EXT INT16U  PFlash_Check(INT32U StartAddr, INT16U Len, INT16U LastValue);/*Boot Flash程序校验计算函数*/
#else
/*------------------------------Dtc------------------------------------*/
#if UDS_DTC_OPEN==1
APPLAYER_EXT void    DtcBackFlashInit_v_g (void);/*DTC EEPROM读取后的初始化函数*/
APPLAYER_EXT void    DtcDual_v_g(INT8U DtcNumb);/*DTC 状态赋值函数*/
APPLAYER_EXT void    DtcCycleDef_v_g(void);/*DTC 周期处理函数*/
APPLAYER_EXT void    ClearDtc_v_g(void);/*DTC 清除函数*/
APPLAYER_EXT void    DTCExtendDual_v_g (void);/*DTC 扩展数据处理函数*/
APPLAYER_EXT void    ClearSignelDtc_v_g(INT8U DtcNumb);/*DTC单个清除函数*/
APPLAYER_EXT void    WDtcSnapshot_v_g(INT8U DtcNumb,INT8U SupBatt,INT32U Odreading,INT8U CoolTemp,INT8U Igstatus );/*DTCSnapshot数据处理函数*/
#endif
#endif
/*------------------------------Crc And seedKey------------------------------------*/
APPLAYER_EXT INT32U  SeedToKey_v_g (INT32U Seed, INT32U Mask);/*SeedKey解密算法*/
APPLAYER_EXT INT32U  GenerateCRC32(BYTEPTR DataBuf, INT32U len, INT32U oldcrc32);/*CRC校验算法*/

/*------------------------------EEPROM And Flash处理函数------------------------------------*/
APPLAYER_EXT void    SaveData_v_g(void);/*写EEPROM函数*/
APPLAYER_EXT void    ReadData_v_g(void);/*读EEPROM函数*/


APPLAYER_EXT void    WriteFlashDual(void);/*写Flash处理函数*/
APPLAYER_EXT void    EraseFlashDual(void);/*擦除Flash处理函数*/
APPLAYER_EXT void    WriteMemDual(void);/*通过地址写EEPROM处理函数*/
APPLAYER_EXT void    ReadMemDual(void);/*通过地址读EEPROM处理函数*/
/*------------------------------EEPROM And Flash处理函数------------------------------------*/
APPLAYER_EXT void    UdsInit_v_g(void);/*初始化函数*/
APPLAYER_EXT void    UDSApp_v_g(void);/*周期执行函数，需要被时序调用*/
APPLAYER_EXT INT8U   AppConFrimNet_v_g(USDATACONFIRM *ConFirmPdu);/*命令确认函数*/
APPLAYER_EXT void    AppReceiveFFind_v_g();/*命令首帧函数*/
APPLAYER_EXT void    TimeDual_v_g(void);/*时间处理函数*/
APPLAYER_EXT void    AppReqNetSend_v_g(RSP_A_PDU AppRspPdu,USDATAREQUEST *AppToNet);/*应用层请求发送与网络层数据交互函数*/
APPLAYER_EXT void    AppSendRspMsg(void);/*应用层发送函数*/
APPLAYER_EXT void    AppRevNetData_v_g(USDATAINDICATION *NetPdu ,REQ_A_PDU AppReqPud);/*网络层接收数据与应用层交互函数*/
APPLAYER_EXT void    AppUdsService_v_g(BYTEPTR Services);/*服务处理函数函数*/
APPLAYER_EXT void    RspPduAdr_v_g(REQ_A_PDU AppReqPdu,RSP_A_PDU *AppRspPdu);/*回应地址处理函数*/

/*-------------------------------Sub_Function 功能服务函数----------------------------------*/
APPLAYER_EXT void   DiagnosticSessionControl_v_g(BYTEPTR RevData);
APPLAYER_EXT void   EcuReset_v_g(BYTEPTR RevData);                                        
APPLAYER_EXT void   SecurityAccess_v_g(BYTEPTR RevData);
APPLAYER_EXT void   CommunicationControl_v_g(BYTEPTR RevData);
APPLAYER_EXT void   ControlDTCSetting_v_g(BYTEPTR RevData);
APPLAYER_EXT void   TesterPresent_v_g(BYTEPTR RevData);
APPLAYER_EXT void   ResponseOnEvent_v_g(BYTEPTR RevData);
APPLAYER_EXT void   LinkControl_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   DynamicallyDefineDataIdentifier_v_g(BYTEPTR RevData);
APPLAYER_EXT void   ReadDtcMsg_v_g(BYTEPTR RevData);
APPLAYER_EXT void   RoutineControl_v_g(BYTEPTR RevData);   
/*-------------------------------WithOut Sub_Function 功能服务函数----------------------------------*/
APPLAYER_EXT void   ClearDiagImfor_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   RequestDownload_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   RequestUpload_v_g(BYTEPTR RevData);   
APPLAYER_EXT void   TansferData_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   RequestTansferExit_v_g(BYTEPTR RevData);  
APPLAYER_EXT void   SecuredDataTransmission_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   ReadDataById_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   ReadMemoryByAddress_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   ReadScalingDataByIdentifier_v_g(BYTEPTR RevData);  
APPLAYER_EXT void   ReadDataByPeriodicIdentifier_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   WriteDataById_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   WriteMemoryByAddress_v_g(BYTEPTR RevData); 
APPLAYER_EXT void   InputOutputControlById(BYTEPTR RevData); 

APPLAYER_EXT void DtcInit_v_s(void);
APPLAYER_EXT void DtcBackFlashInit_v_g (void);

#endif








