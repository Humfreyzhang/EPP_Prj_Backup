/*!******************************************************************************************************
*	@file 	AppLayer_Uds.c
*	@brief 	AppLayer_Uds 源文件
*	@author Matt Zhang
*	@version 1.0
*	@date  2015-9-3
*	@warning  
*                (c) Copyright 2015, KAIT Automotive Technology(Suzhou) Co., Ltd.
*                                       All Rights Reserved
*	@note	
- 
*********************************************************************************************************
*/
#define  APPLAYER_GLOBALS
#include "AppLayer_Uds.h"
#include "DSP2803x_Device.h"
#include "interface_other.h"
#include "DSP2803x_function.h"
#include "interface_file.h"

//#include "F2803x_EEPROM.h"
//#include "EPC_parameter.h"     // DSP28 Headerfile Include File
//#include "EPC_AppECan.h"
//#include "EPC_AppFaultProcess.h"
//#include "EPC_AppSequence.h"
//#include "EPC_AppADC.h"
//#pragma DATA_SECTION(DtcNumb_u24a8_Par,     "EEPROM");
//#pragma DATA_SECTION(DtcStatus_u16a8_Par,     "EEPROM");
#pragma DATA_SECTION(LastDtcStatus_u16a8_Par,     "EEPROM");
//#pragma DATA_SECTION(DtcExtend_u64a8_Par,     "EEPROM");
//#pragma DATA_SECTION(DtcSnapShot_u80a8_Par,     "EEPROM");
#pragma DATA_SECTION(BootTimes_u16_Par,     "EEPROM");
#pragma DATA_SECTION(PifPtcb_u16a16a16_Par,     "EEPROM");
#pragma DATA_SECTION(BootSwRefNumb_u16a10_Par,     "EEPROM");
#pragma DATA_SECTION(ECUPartNumb_u16a6_Par,     "EEPROM");
#pragma DATA_SECTION(SysSupplierId_u16a6_Par,     "EEPROM");
#pragma DATA_SECTION(Vin_u16a17_Par,     "EEPROM");
#pragma DATA_SECTION(EcuHwNumb_u16a6_Par,     "EEPROM");
#pragma DATA_SECTION(EcuHwRefNumb_u16a10_Par,     "EEPROM");
#pragma DATA_SECTION(EcuSwRefNumb_u16a10_Par,     "EEPROM");
#pragma DATA_SECTION(EcuCalSwNumb_u16a6_Par,     "EEPROM");
#pragma DATA_SECTION(EcuNetRefNumb_u16a6_Par,     "EEPROM");
#pragma DATA_SECTION(VehFeature_u16a20_Par,     "EEPROM");
#pragma DATA_SECTION(EcuMData_u16a3_Par,     "EEPROM");
#pragma DATA_SECTION(EcuSupplierSN_u16a10_Par,     "EEPROM");
#pragma DATA_SECTION(PifBlockNumb_u16_Sig,     "EEPROM");


/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/
/*-------------------Crc32校验表格-----------------------*/
#if 0
unsigned long  crc_32_tab[256] =
{
0X00000000L,  0X04c11db7L,  0X09823b6eL,  0X0d4326d9L,  
0X130476dcL,  0X17c56b6bL,  0X1a864db2L,  0X1e475005L,  
0X2608edb8L,  0X22c9f00fL,  0X2f8ad6d6L,  0X2b4bcb61L,  
0X350c9b64L,  0X31cd86d3L,  0X3c8ea00aL,  0X384fbdbdL,  
0X4c11db70L,  0X48d0c6c7L,  0X4593e01eL,  0X4152fda9L,  
0X5f15adacL,  0X5bd4b01bL,  0X569796c2L,  0X52568b75L,
0X6a1936c8L,  0X6ed82b7fL,  0X639b0da6L,  0X675a1011L,  
0X791d4014L,  0X7ddc5da3L,  0X709f7b7aL,  0X745e66cdL,  
0X9823b6e0L,  0X9ce2ab57L,  0X91a18d8eL,  0X95609039L,  
0X8b27c03cL,  0X8fe6dd8bL,  0X82a5fb52L,  0X8664e6e5L,  
0Xbe2b5b58L,  0Xbaea46efL,  0Xb7a96036L,  0Xb3687d81L,  
0Xad2f2d84L,  0Xa9ee3033L,  0Xa4ad16eaL,  0Xa06c0b5dL,
0Xd4326d90L,  0Xd0f37027L,  0Xddb056feL,  0Xd9714b49L,  
0Xc7361b4cL,  0Xc3f706fbL,  0Xceb42022L,  0Xca753d95L,  
0Xf23a8028L,  0Xf6fb9d9fL,  0Xfbb8bb46L,  0Xff79a6f1L,  
0Xe13ef6f4L,  0Xe5ffeb43L,  0Xe8bccd9aL,  0Xec7dd02dL,  
0X34867077L,  0X30476dc0L,  0X3d044b19L,  0X39c556aeL,  
0X278206abL,  0X23431b1cL,  0X2e003dc5L,  0X2ac12072L,  
0X128e9dcfL,  0X164f8078L,  0X1b0ca6a1L,  0X1fcdbb16L,  
0X018aeb13L,  0X054bf6a4L,  0X0808d07dL,  0X0cc9cdcaL,  
0X7897ab07L,  0X7c56b6b0L,  0X71159069L,  0X75d48ddeL,  
0X6b93dddbL,  0X6f52c06cL,  0X6211e6b5L,  0X66d0fb02L,  
0X5e9f46bfL,  0X5a5e5b08L,  0X571d7dd1L,  0X53dc6066L,
0X4d9b3063L,  0X495a2dd4L,  0X44190b0dL,  0X40d816baL,  
0Xaca5c697L,  0Xa864db20L,  0Xa527fdf9L,  0Xa1e6e04eL,  
0Xbfa1b04bL,  0Xbb60adfcL,  0Xb6238b25L,  0Xb2e29692L,  
0X8aad2b2fL,  0X8e6c3698L,  0X832f1041L,  0X87ee0df6L,  
0X99a95df3L,  0X9d684044L,  0X902b669dL,  0X94ea7b2aL,  
0Xe0b41de7L,  0Xe4750050L,  0Xe9362689L,  0Xedf73b3eL,
0Xf3b06b3bL,  0Xf771768cL,  0Xfa325055L,  0Xfef34de2L,  
0Xc6bcf05fL,  0Xc27dede8L,  0Xcf3ecb31L,  0Xcbffd686L,  
0Xd5b88683L,  0Xd1799b34L,  0Xdc3abdedL,  0Xd8fba05aL,  
0X690ce0eeL,  0X6dcdfd59L,  0X608edb80L,  0X644fc637L,  
0X7a089632L,  0X7ec98b85L,  0X738aad5cL,  0X774bb0ebL,  
0X4f040d56L,  0X4bc510e1L,  0X46863638L,  0X42472b8fL,  
0X5c007b8aL,  0X58c1663dL,  0X558240e4L,  0X51435d53L,  
0X251d3b9eL,  0X21dc2629L,  0X2c9f00f0L,  0X285e1d47L,  
0X36194d42L,  0X32d850f5L,  0X3f9b762cL,  0X3b5a6b9bL,  
0X0315d626L,  0X07d4cb91L,  0X0a97ed48L,  0X0e56f0ffL,  
0X1011a0faL,  0X14d0bd4dL,  0X19939b94L,  0X1d528623L,
0Xf12f560eL,  0Xf5ee4bb9L,  0Xf8ad6d60L,  0Xfc6c70d7L,  
0Xe22b20d2L,  0Xe6ea3d65L,  0Xeba91bbcL,  0Xef68060bL,  
0Xd727bbb6L,  0Xd3e6a601L,  0Xdea580d8L,  0Xda649d6fL,  
0Xc423cd6aL,  0Xc0e2d0ddL,  0Xcda1f604L,  0Xc960ebb3L,  
0Xbd3e8d7eL,  0Xb9ff90c9L,  0Xb4bcb610L,  0Xb07daba7L,  
0Xae3afba2L,  0Xaafbe615L,  0Xa7b8c0ccL,  0Xa379dd7bL,
0X9b3660c6L,  0X9ff77d71L,  0X92b45ba8L,  0X9675461fL,  
0X8832161aL,  0X8cf30badL,  0X81b02d74L,  0X857130c3L,  
0X5d8a9099L,  0X594b8d2eL,  0X5408abf7L,  0X50c9b640L,  
0X4e8ee645L,  0X4a4ffbf2L,  0X470cdd2bL,  0X43cdc09cL,  
0X7b827d21L,  0X7f436096L,  0X7200464fL,  0X76c15bf8L,  
0X68860bfdL,  0X6c47164aL,  0X61043093L,  0X65c52d24L,  
0X119b4be9L,  0X155a565eL,  0X18197087L,  0X1cd86d30L,  
0X029f3d35L,  0X065e2082L,  0X0b1d065bL,  0X0fdc1becL,  
0X3793a651L,  0X3352bbe6L,  0X3e119d3fL,  0X3ad08088L,  
0X2497d08dL,  0X2056cd3aL,  0X2d15ebe3L,  0X29d4f654L,  
0Xc5a92679L,  0Xc1683bceL,  0Xcc2b1d17L,  0Xc8ea00a0L,
0Xd6ad50a5L,  0Xd26c4d12L,  0Xdf2f6bcbL,  0Xdbee767cL,
0Xe3a1cbc1L,  0Xe760d676L,  0Xea23f0afL,  0Xeee2ed18L,
0Xf0a5bd1dL,  0Xf464a0aaL,  0Xf9278673L,  0Xfde69bc4L,
0X89b8fd09L,  0X8d79e0beL,  0X803ac667L,  0X84fbdbd0L,
0X9abc8bd5L,  0X9e7d9662L,  0X933eb0bbL,  0X97ffad0cL,
0Xafb010b1L,  0Xab710d06L,  0Xa6322bdfL,  0Xa2f33668L,
0Xbcb4666dL,  0Xb8757bdaL,  0Xb5365d03L,  0Xb1f740b4L

};
#endif


/*------------F1A0、F1A1、F1A2可以通过刷新程序更新、请根据客户的要求自行修改下面数组的值、具体代表的DID请参考h文件-----------------------*/
//ASCII加5个BCD
//20160309上汽提供
//零件号：C0006858400，硬件号F191：E6900610001,软件号F1A0：E6900620001，标定号：E6900630001,F18A:P0110900000

uint16_T ECUPartNumb_u16a6_Par[3]={0x43,0x00,0x06,0x85,0x84,0x00};		//C0006858400   LJH0226
uint16_T EcuHwNumb_u16a6_Par[3]={0x45,0x69,0x00,0x61,0x00,0x01};			//硬件号
uint16_T EcuCalSwNumb_u16a6_Par[3]={0x45,0x69,0x00,0x63,0x00,0x01};		//标定号
uint16_T SysSupplierId_u16a6_Par[3]={0x50,0x01,0x10,0x09,0x00,0x00};


static uint16_T  PifBlockNumb_u16_Sig;/*F110-F11F写的索引值*/

//static uint8_T   WrDidBackUp_Sig[2]={0};/*用于记录WrId*/
static uint32_T  Level1Mask_u32_Sig=0xC66969C6;/*1级解密掩码*/
static uint32_T  Level2Mask_u32_Sig=0x69F6F669;/*2级解密掩码*/
static uint32_T  Seed_u32_Sig=0;/*32位Seed*/
//static uint16_T  BootEepFlag_u16_Par;/*boot程序写过EEPROM标志*/
//static uint16_T  AppEepFlag_u16_Par;/*AppCode程序写过EEPROM标志*/
/*----------------原语信息-----------------*/
static uint8_T   AdrType_u8_Sig;/*寻址方式*/
static uint8_T   Mtype_u8_Sig;/*寻址方式*/
static uint8_T   SI_u8_Tmp;/*服务号*/
static uint8_T   NegRsp_u8_Sig;/*负面回应服务号*/
static uint8_T   DefSub_u8_Tmp;/*用于判断是否为Sub功能的服务*/
static uint8_T   RspFmt_u8_Sig;/*回应模式*/
static uint8_T   supPosRspMsgIndBit_u8_Tmp;/*提取服务Sub-funtion的最高位用于判断是否要回应*/
static uint16_T  RevMsgLen_u16_Sig;/*接收的长度*/
static uint16_T  RspMsgLen_u16_Sig;/*回应的长度*/
/*----------------Reset模式变量-----------------*/
static uint8_T   ResetMode_u8_Sig;/*Reset模式*/
/*----------------解密服务数据-----------------*/
static uint8_T   LockMode_u8_Sig=0;/*解密状态*/
static uint16_T  UnlockLimitTime_u16_Sig;/*解密错误次数*/
static uint8_T   UnLockTimeOver_u8_Sig;/*解密超限标志*/
static uint8_T   ScurReqTimes_u8_Sig=0;/*用于记录27服务是否被请求过*/
/*----------------AppLayer Time Control-----------------*/
static uint8_T   P2CntStart_u8_Sig=0 ;/*50ms超时计数开始标志*/
static uint8_T   P2FlexCntStart_u8_Sig=0;/*5000ms超时计数开始标志*/
static uint16_T  P2Sever_u16_Sig=0;/*50ms超时计数器*/
static uint16_T  P2FlexSever_u16_Sig=0;/*5000ms超时计数器*/
static uint16_T  S3Sever_u16_Sig=0;/*5000ms非默认会话模式计时*/
static uint32_T  Secur_u32_Sig=0;/*解密被锁后解锁时间*/
/*----------------Mem Data-----------------*/
static uint32_T  MemAdr_u32_Sig=0;
static uint16_T  MemDataLen_u16_Sig=0;
static uint8_T   WMemDataFLag_u8_Sig=0;/*写MEM数据标志位*/
static uint8_T   RMemDataFLag_u8_Sig=0;/*读MEM数据标志位*/
static uint8_T   BackUpMemInfor_u8_Sig[6];/*记录MEM信息数据*/
static uint16_T  BackUpPosLen_u16_Sig;/*记录正回应的长度*/
static uint16_T  MemData_u16_Sig[120];/*读写MEM数据Buffer*/
static uint8_T   adrLenFmtId_u8_Sig;/*地址格式长度*/
static uint8_T   BackSub_u8_Sig;/*Sub_Funtion备份*/
static uint32_T  crcData_u32_Sig;/*Crc校验值*/
static uint8_T   BackUpExit_u8_Sig=0 ;/*下载退出标志记录*/
/*----------------BootLoader DownLoad Code Para-----------------*/
#if APP_CODE==0
static uint8_T    WFlashFlag_u8_Sig=0;/*写Flash标志位*/
static uint8_T    BlockCnt_u8_Sig=0 ;/*块计数器*/
static uint8_T    ReqTranExitStatus_u8_Sig=0;/*请求状态*/
static uint8_T    EndHex_u8_Sig=0;/*Hex最后标志位*/

static uint8_T    TranBlock_u8_Sig=0;/*Block的计数*/
static uint8_T    TranBuff_u8_Sig[500];/*Block数据存放Buffer*/
static uint16_T   FlashWBuffer_u16_Sig[200];/*写Flash数据Buffer*/
static uint16_T   BootWFalshLen_u16_Sig=0;/*写Flash数据长度*/
static uint32_T   TransferLen_u32_Sig=0;/*发送的长度*/
static uint32_T   WriteMemLen_u32_Sig=0;/*请求写地址长度*/
static uint32_T   TranRevCnt_u32_Sig=0;/*写Flash数据Buffer计数变量*/
static uint32_T   WFlashAdr_u32_Sig=0;/*写Flash起始地址*/
static uint32_T   FlashLen_u32_Sig=0;/*写Flash所有数据的长度限值*/
#endif

static uint8_T    EraseFStatus_u8_Sg=0;/*擦除Flash状态*/
static uint8_T    EraseABStatus_u8_Sg=0;/*擦除Flash状态*/
static uint8_T    EFlashFlag_u8_Sig=0;/*擦除Flash标志位*/
static uint8_T    EraseDid_u8_Sig[2];/*擦除Flash标志位*/
static uint16_T   EraseSector_u8_Sig=0;/*擦除的Flash扇区*/
/*----------------Flash define-----------------*/
static uint16_T   SIS_u16_Sig;/*程序完整性*/
static uint16_T   SCS_u16_Sig;/*程序兼容性*/

/*----------------EEPROM Marks-----------------*/
#if APP_CODE==1
static uint8_T    DtcEep_u8_Sig;/*DTC写EEPROM标志位*/
#endif
//static uint8_T    DidEep_u8_Sig;/*Did写EEPROM标志位*/
static uint8_T    SvfEep_u8_Sig;/*SVF写EEPROM标志位*/


/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/
#if APP_CODE==1
static void   DtcInit_v_s(void);/*DTC初始化函数*/
static void   Progam_v_s();/*AppToBoot函数*/
#endif

static uint16_T EraseSector_v_s(uint16_T sector);/*擦除Flash扇区函数*/
static uint8_T  ResponseMechanism_v_s() ;/*判断是否回应函数*/
/*
*********************************************************************************************************
*                                             C ENTRY POINT
*********************************************************************************************************
*/

void Service_RamdomGen(void)
{
	uint32_T temp1, temp2, temp3;

	temp1 = IO_Get_SystemTimerValue();
	temp2 = Seed_u32_Sig^ 0xA55A5AA5 + (temp1*65536)^0x5AA5A5A5 + temp1;
	temp3 = temp2 + Seed_u32_Sig;
	Seed_u32_Sig = temp3;
}


/*!******************************************************************************************************
*	@fn void UdsInit_v_g(void)
*	@brief	Uds初始化函数
*	@author Matt Zhang
*	@param[in]	void
*	@return	void
*	@note
*	Uds网络层及应用层所有初始化
*********************************************************************************************************
*/
void UdsInit_v_g(void)
{	
	

NetworkLayerServices_GF_initialize();/*Network初始化*/
Req_Msg.IndReceiveMsg_u8_Sig=&UdsIndication.MessageData[0];/*指针初始化*/
Rsp_Msg.ReqSendMsg_u8_Tmp=&UdsRequest.MessageData[0];/*指针初始化*/
RequestCmd_u8_Sig          = 0;
VehicleSpeed_u16_Sig       = 0;
EngineSpeed_u16_Sig        = 0;


AdrType_u8_Sig             = 0;
Mtype_u8_Sig               = 0;
WrCheckSum_u16_Sig         = 0;
RspMsgLen_u16_Sig          = 0;
ResetMode_u8_Sig           = 0;
SI_u8_Tmp                  = 0;
NegRsp_u8_Sig              = 0;
DefSub_u8_Tmp              = 0;
RspFmt_u8_Sig              = 0;
RevMsgLen_u16_Sig          = 0;
OldSessionMode_u8_Sig      = DEFAULT_SESSION;
SessionMode_u8_Sig         = DEFAULT_SESSION;
supPosRspMsgIndBit_u8_Tmp  = 0;

LockMode_u8_Sig            = Lock;
UnlockLimitTime_u16_Sig    = 0;
UnLockTimeOver_u8_Sig      = 0;


NormalComTx_u8_Sig         = 1;
NormalComRx_u8_Sig         = 1;
NetWorkComTx_u8_Sig        = 1;
NetWorkComRx_u8_Sig        = 1;

P2FlexCntStart_u8_Sig      = 0;
P2Sever_u16_Sig            = 0;
P2FlexSever_u16_Sig        = 0;
S3Sever_u16_Sig            = 0;
P2CntStart_u8_Sig          = 0;
Secur_u32_Sig              = 0;
ScurReqTimes_u8_Sig        = 0;
BackSub_u8_Sig             = 0;
#if APP_CODE==0
CANNumb_u8_Sig             = 0;
CANIndex_u8_Sig            = 0;
CANGetOut_u8_Sig           = 0;
Jump_u8_Sig                = 0;
BootApp_u8_Sig             = 0;
BlockCnt_u8_Sig            = 1;
TransferLen_u32_Sig        = 0;
WriteMemLen_u32_Sig        = 0;
ReqTranExitStatus_u8_Sig   = 0;
TranRevCnt_u32_Sig         = 0;
WFlashFlag_u8_Sig          = 0;
FC_RecStatus_u8_Sig=0;
#endif
#if APP_CODE==1
DtcEep_u8_Sig              = 0;
#endif
EepRomTimes_u8_Sig		   = 0;
PEF_u16_Par                = 0;
SVF_u16_Par                = 0;
//BootTimes_u16_Par          = 0;
SIS_u16_Sig                = 1;
SCS_u16_Sig                = 1;
//DidEep_u8_Sig              = 0;
PefEep_u8_Sig              = 0;
SvfEep_u8_Sig              = 0;

WMemDataFLag_u8_Sig        = 0;
RMemDataFLag_u8_Sig        = 0;
EppStatus_u8_Sig           = 0;
AsTime_Limited_u16_Par     = AS_TIME;
BsTime_Limited_u16_Par     = BS_TIME;
CrTime_Limited_u16_Par     = CR_TIME;
UDS_Timeout_u8_Sig         = 0;
CFCount_u8_Sig             = 0;
SFLength_Ovrn_u8_Sig       = 0;
CANLength_u8_Sig           = 0;
FrameSequ_u8_Sig           = 0;
FrameErr_u8_Sig            = 0;
UDStick_u8_Par             = CODE_CYCLE;

//PifBlockNumb_u16_Sig       = 0;
#if APP_CODE==1
STminCoef_u8_Par           = 1;
STmin_u8_Par               = 0x14;
#else
STminCoef_u8_Par           = CODECEF;
STmin_u8_Par               = 0x01;
#endif

#if APP_CODE==1
DtcOnOff_u8_Sig           = DTCSETTING_ON;
DtcInit_v_s();/*DTC初始化*/
#endif
//ReadData_v_g();/*读取EEPROM*/

#if APP_CODE==1
DtcBackFlashInit_v_g();/*DTCEEPROM后初始化*/
#endif


}
/*!******************************************************************************************************
*	@fn uint8_T AppConFrimNet_v_g(USDATACONFIRM *ConFirmPdu)
*	@brief	Uds确认原语函数
*	@author Matt Zhang
*	@param[in]	ConFirmPdu 网络层确认原语结构体
*	@return	uint8_T
*	@note 
*	用于命令回复确认后判断会话模式
*********************************************************************************************************
*/
uint8_T AppConFrimNet_v_g(USDATACONFIRM *ConFirmPdu)
{
  /*-------------------判断此次的回应是不是成功。且服务是不是会话模式----------------------*/
  if(ConFirmPdu->N_Result==N_OK && SI_u8_Tmp==DIAGNOSTIC_SESSION_CONTROL && RspFmt_u8_Sig==POS_RSP) 
  {
    LockMode_u8_Sig=Lock;
  }
  /*-------------------判断此次的回应是不是成功。且老的会话模式和当前会话模式是否一致----------------------*/
  if(ConFirmPdu->N_Result==N_OK && OldSessionMode_u8_Sig!=SessionMode_u8_Sig && RspFmt_u8_Sig==POS_RSP) 
  {
    LockMode_u8_Sig=Lock;
    OldSessionMode_u8_Sig=SessionMode_u8_Sig;
  } 
  
  return 1;
}
/*!******************************************************************************************************
*	@fn	void AppRevNetData_v_g(USDATAINDICATION *NetPdu ,REQ_A_PDU AppReqPud)
*	@brief	网络层接收数据和应用层交互函数
*	@author Matt Zhang
*	@param[in]	*NetPdu 网络层接收原语结构体参数  ，AppReqPud应用层结构体参数
*	@return	void
*	@note 
- 将网络层获取的完整数据给应用层
*********************************************************************************************************
*/
void AppRevNetData_v_g(USDATAINDICATION *NetPdu ,REQ_A_PDU AppReqPud)     
{
  if(NetPdu->Mtype==Mtype_Diagnostics && NetPdu->N_Result==N_OK)/*判断诊断方式及数据接收是否OK*/
   {
     Mtype_u8_Sig=Mtype_Diagnostics;/*诊断方式赋值*/
     
   }
   if(NetPdu->Mtype==Mtype_Rdiagnostics && NetPdu->N_Result==N_OK) {/*判断诊断方式及数据接收是否OK*/
   
     AppReqPud.A_RA      =NetPdu->N_AE; /*网关地址赋值*/
     Mtype_u8_Sig        =Mtype_Rdiagnostics;/*诊断方式赋值*/
   }
   
  if(NetPdu->N_Result==N_OK) {/*判断接收的数据是否OK*/
     
     P2CntStart_u8_Sig     =1;/*回应时间计时*/
     
     AppReqPud.A_TA_type =NetPdu->N_TAtype; /*获取寻址方式信息*/
     AdrType_u8_Sig      =AppReqPud.A_TA_type; /*获取寻址方式信息*/
     AppReqPud.A_SA      =NetPdu->N_SA;/*源地址信息*/
     AppReqPud.A_TA      =NetPdu->N_TA; /*目标地址信息*/
     
     AppReqPud.A_PLength   =NetPdu->Length; /*获取数据长度*/
     RevMsgLen_u16_Sig   =AppReqPud.A_PLength; /*获取数据长度*/
   
     AppReqPud.IndReceiveMsg_u8_Sig=&NetPdu->MessageData[0];/*数据赋值*/
     
     RspPduAdr_v_g(AppReqPud,&Rsp_Msg);   /*地址信息处理*/
  }
}

/*!******************************************************************************************************
*	@fn	void RspPduAdr_v_g(REQ_A_PDU AppReqPdu,RSP_A_PDU *AppRspPdu)
*	@brief	将请求服务的地址转换成回应命令的地址函数
*	@author Matt Zhang
*	@param[in]	*AppRspPdu 应用层回应命令结构体  ，AppReqPud应用层请求结构体参数
*	@return	void
*	@note 
-
*********************************************************************************************************
*/
void RspPduAdr_v_g(REQ_A_PDU AppReqPdu,RSP_A_PDU *AppRspPdu)
{
 AppRspPdu->A_SA      =AppReqPdu.A_TA;  /*将目标地址赋值给回应报文的源地址*/
 AppRspPdu->A_TA      =AppReqPdu.A_SA;  /*将源地址赋值给回应报文的目标地址*/
 AppRspPdu->A_TA_type =AppReqPdu.A_TA_type;/*寻址方式赋值*/
 if(Mtype_u8_Sig==Mtype_Rdiagnostics) /*判断是否为远程请求*/
 {
  AppRspPdu->A_RA=AppReqPdu.A_RA; /*中间网关赋值*/
 } 
 
}

/*!******************************************************************************************************
*	@fn	void AppReqNetSend_v_g(RSP_A_PDU AppRspPdu,USDATAREQUEST *AppToNet)
*	@brief	将应用层回应命令参数交给网络层，并让网络层发送数据
*	@author Matt Zhang
*	@param[in]	AppRspPdu 应用层回应命令结构体  ，AppToNet网络层回应命令结构体
*	@return	void
*	@note 
-
*********************************************************************************************************
*/
void AppReqNetSend_v_g(RSP_A_PDU AppRspPdu,USDATAREQUEST *AppToNet)
{                                                                                            
  AppToNet->N_SA        =AppRspPdu.A_SA;/*源地址赋值*/
  AppToNet->N_TA        =AppRspPdu.A_TA;/*目标地址赋值*/
  AppToNet->N_TAtype    =AppRspPdu.A_TA_type;/*寻址方式赋值*/
  AppRspPdu.A_PLength  =RspMsgLen_u16_Sig;/*长度赋值*/
 
 
 if(Mtype_u8_Sig==Mtype_Rdiagnostics) /*判断是否为远程请求*/
 { 
  AppToNet->Mtype =Mtype_Rdiagnostics;
  AppToNet->N_AE  =AppRspPdu.A_RA;/*中间网关赋值*/
 }
 else
 {
  AppToNet->Mtype =Mtype_Diagnostics;
 }
 
   /*-------------------负面回应赋值----------------------*/
 if(RspFmt_u8_Sig==NEG_RSP) 
 {
   AppRspPdu.A_NR_SI= NR_SI;
   AppRspPdu.A_SI   = SI_u8_Tmp;
   __byte(&AppToNet->MessageData[0], LSB)=AppRspPdu.A_NR_SI;
   __byte(&AppToNet->MessageData[0], MSB)=AppRspPdu.A_SI;
   __byte(&AppToNet->MessageData[1], LSB)=NegRsp_u8_Sig;
   AppToNet->Length=AppRspPdu.A_PLength+1;
 } 
 /*-------------------正面回应赋值----------------------*/
 if(RspFmt_u8_Sig==POS_RSP)
 {
   AppRspPdu.A_SI   = SI_u8_Tmp+0x40;
   AppToNet->Length=AppRspPdu.A_PLength+1;
   __byte(&AppToNet->MessageData[0], LSB)= AppRspPdu.A_SI;
 } 
 
 RequestCmd_u8_Sig=APPTONET_SENDOK;/*请求网络层发送标志位*/

 if(P2CntStart_u8_Sig==1)/*判断是否一开始计时*/
 {
    P2CntStart_u8_Sig = 0;
 }
 
 if(P2FlexCntStart_u8_Sig==1)/*判断是否一开始计时*/
 {
 	P2FlexCntStart_u8_Sig = 0;
 }

}

/*!******************************************************************************************************
*	@fn	void DiagnosticSessionControl_v_g(BYTEPTR RevData)
*	@brief	会话模式服务函数
*	@author Matt Zhang
*	@param[in]	RevData为应用请求数据指针
*	@return	void
*	@note 
-
*********************************************************************************************************
*/
void DiagnosticSessionControl_v_g(BYTEPTR RevData) 
 {
   uint8_T subFunction;
   /*---------------获取命令数值----------------*/
   subFunction=__byte(RevData, MSB);/*sub_funtion赋值*/
   RspFmt_u8_Sig=POS_RSP; /*回应类型赋值*/
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*回应状态赋值*/
   subFunction=subFunction&0x7F;/*Sub_Funtion去高位处理*/
   SI_u8_Tmp=DIAGNOSTIC_SESSION_CONTROL;/*Sub_Funtion去高位处理*/
   OldSessionMode_u8_Sig = SessionMode_u8_Sig;/*当前会话模式赋值给老的会话模式*/
   DefSub_u8_Tmp=0x01;/*Sub服务标志位置1*/
  /*--------------正回应数据赋值----------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction;
   //Rsp_Msg.ReqSendMsg_u8_Tmp [2]=00;
   //Rsp_Msg.ReqSendMsg_u8_Tmp [3]=0x32;
   //Rsp_Msg.ReqSendMsg_u8_Tmp [4]=0x01;
   //Rsp_Msg.ReqSendMsg_u8_Tmp [5]=0xF4;
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, subFunction);
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], LSB, 0x00);
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], MSB, 0x32);
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], LSB, 0x01);
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], MSB, 0xF4);

   /*----------------Len Nor Right--------------*/
   if(RevMsgLen_u16_Sig!=2)/*长度不足服务需求的长度*/ 
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/  
   } 
   /*----------------SubFun Not Support--------------*/
   if((subFunction<0x01 || subFunction>=0x04) &&RspFmt_u8_Sig!=NEG_RSP)/*不支持的Sub-Function*/
   {
     RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR; /*Sub不支持错误码0x12*/
   }
   /*0x01  Default Session; 0x02  Programming Session; 0x03  Extend Session*/
   if(subFunction==DEFAULT_SESSION && RspFmt_u8_Sig!=NEG_RSP)/*判断请求是否为默认会话*/
   {
      SessionMode_u8_Sig= DEFAULT_SESSION;/*会话模式赋值*/
      NormalComTx_u8_Sig = 1;/*打开通信发送*/
      NormalComRx_u8_Sig = 1;/*打开通信接收*/
   
   } 
   if(subFunction==PROGRANMMING_SESSION && RspFmt_u8_Sig!=NEG_RSP) {/*判断请求是否为编程会话*/
#if APP_CODE==0
      SessionMode_u8_Sig = PROGRANMMING_SESSION;/*会话模式赋值*/
      NormalComTx_u8_Sig = 1;/*打开通信发送*/
      NormalComRx_u8_Sig = 1;/*打开通信接收*/
#else
      PEF_u16_Par = 1;/*AppToBoot置位*/
      PefEep_u8_Sig=1;/*写EEPROM标志位*/
#endif
	 unClearRam.reset_cnt = 0;
     unClearRam.Pattern[0] = 0x3223;
	 unClearRam.Pattern[1] = 0x5AA5;
	 ResetMode_u8_Sig = SW_RESET;

   }
   
   if(subFunction==EXTEND_SESSION && RspFmt_u8_Sig!=NEG_RSP) {/*判断请求是否为扩展会话*/
      SessionMode_u8_Sig= EXTEND_SESSION;/*会话模式赋值*/
   }
   
   if(SessionMode_u8_Sig!=OldSessionMode_u8_Sig && supPosRspMsgIndBit_u8_Tmp==0x80)
   {
	   LockMode_u8_Sig=Lock;/*会话模式切换服务加锁*/

   }

   if (RspFmt_u8_Sig==NEG_RSP  ) /*判断回应类型是否是负面回应*/
   {
     RspMsgLen_u16_Sig=2;/*发送数据的长度*/
   } 
   else {
     RspMsgLen_u16_Sig=5;/*发送数据的长度*/
   } 
 }
/*!******************************************************************************************************
*	@fn	void EcuReset_v_g(BYTEPTR RevData)
*	@brief	复位服务函数
*	@author Matt Zhang
*	@param[in]	RevData为应用请求数据指针
*	@return	void
*	@note 
-
*********************************************************************************************************
*/
void EcuReset_v_g(BYTEPTR RevData) 
 {
   uint8_T subFunction;
   /*----------------获取命令数值--------------*/
   subFunction=__byte(RevData, MSB);/*sub_funtion赋值*/
   RspFmt_u8_Sig=POS_RSP; /*回应类型赋值*/
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*回应状态赋值*/
   subFunction=subFunction&0x7F;/*Sub_Funtion去高位处理*/
   SI_u8_Tmp=ECU_RESET;
   DefSub_u8_Tmp=0x01;/*Sub服务标志位置1*/
   /*--------------正回应数据赋值----------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction;
   
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, subFunction);
   /*----------------Len Nor Right--------------*/
   if(RevMsgLen_u16_Sig!=2)
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=CMD_LENGTH_ERR;    /*长度不对错误码0x13*/
   }
   /*----------------SubFun Not Support--------------*/ 
   if((subFunction<HARD_RESET||subFunction>RAPIDSHUTDOWN_DISABLE)&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR; /*Sub错误码0x12*/
   	
   }
   /*----------------SeCur Level1 UnLock Err--------------*/ 
   if(LockMode_u8_Sig!=UnLock_Level &&  SessionMode_u8_Sig==EXTEND_SESSION && AdrType_u8_Sig==TAtype_phiscal && RspFmt_u8_Sig!=NEG_RSP)
   {
   	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;  /*安全不通过0x33*/
   	
   }
   /*----------------SeCur Level2 UnLock Err--------------*/ 
   if(LockMode_u8_Sig!=UnLock_Level2 &&  SessionMode_u8_Sig==PROGRANMMING_SESSION && AdrType_u8_Sig==TAtype_phiscal && RspFmt_u8_Sig!=NEG_RSP)
   {
   	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;  /*安全不通过0x33*/
   	
   }
   
   /*-----------------------------对子功能进行判断--------------------------------*/
   
   /*0x01  hard Reset*/
   if(subFunction==HARD_RESET && RspFmt_u8_Sig!=NEG_RSP )
   {
   ResetMode_u8_Sig = HARD_RESET;/*复位类型赋值*/
   } 
   /*0x02  Key_Off_On Reset*/
   else if(subFunction==KEYOFFON_RESET && RspFmt_u8_Sig!=NEG_RSP) {
   ResetMode_u8_Sig = KEYOFFON_RESET;/*复位类型赋值*/
   }
   /*0x03  Sw Reset*/
   else if(subFunction==SW_RESET && RspFmt_u8_Sig!=NEG_RSP) {

	ResetMode_u8_Sig=SW_RESET;/*复位类型赋值*/
   }
   /*0x04  RapidShutDown enable*/
   else if(subFunction==RAPIDSHUTDOWN_ENABLE && RspFmt_u8_Sig!=NEG_RSP)
   {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CONDITION_NOTSURRORT_ERR;  /*条件不满足错误码0x22*/
   }
   /*0x05  RapidShutDown disable*/
   else if(subFunction==RAPIDSHUTDOWN_DISABLE && RspFmt_u8_Sig!=NEG_RSP)
   {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CONDITION_NOTSURRORT_ERR;  /*条件不满足错误码0x22*/
   } 
   else {
    
   }
   
   if(RspFmt_u8_Sig==NEG_RSP  )  /*判断回应类型是否是负面回应*/
   {
     RspMsgLen_u16_Sig=2;/*发送数据的长度*/
   } 
   else {
     RspMsgLen_u16_Sig=1;/*发送数据的长度*/
   }
 }
/*!******************************************************************************************************
*	@fn	void SecurityAccess_v_g(BYTEPTR RevData)
*	@brief 请求解密服务函数
*	@author Matt Zhang
*	@param[in]	RevData为应用请求数据指针
*	@return	void
*	@note 
-
*********************************************************************************************************
*/
void SecurityAccess_v_g(BYTEPTR RevData)
 {

   static uint8_T   seedReqmrk=0;
   static uint32_T  TestetKey;/*诊断仪发送的Key值*/
   static uint32_T  EcuKey=0;/*ECU计算的Key值*/
   static uint8_T   seedSub_u8_Tmp;
   uint8_T subFunction;
   /*--------------获取命令数值-----------*/
   subFunction=__byte(RevData, MSB);/*sub_funtion赋值*/
   RspFmt_u8_Sig=POS_RSP; /*回应类型赋值*/
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*回应状态赋值*/
   subFunction=subFunction&0x7F;/*Sub_Funtion去高位处理*/
   SI_u8_Tmp=SECURITY_ACCESS;
   DefSub_u8_Tmp=0x01;/*Sub服务标志位置1*/
   /*--------------正回应数据赋值----------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction; 
   
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, subFunction);
   /*----------------Session Not Support--------------*/ 
   if(SessionMode_u8_Sig==DEFAULT_SESSION || AdrType_u8_Sig!=TAtype_phiscal)
   {
   	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*会话模式不支持错误码0x7F*/
   }
   /*----------------Len Err--------------*/ 
   if((subFunction&0x01)==0x01 && RevMsgLen_u16_Sig!=2 && RspFmt_u8_Sig!=NEG_RSP)/*长度不足服务需求的长度*/ 
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/  
   } 
   /*----------------subFun Err--------------*/ 
   if(subFunction!=0x01 && subFunction!=0x05  \
   &&subFunction!=0x02 && subFunction!=0x06 &&  RspFmt_u8_Sig!=NEG_RSP )
   {
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR;  /*sub不支持错误码0x12*/
   	
   }
    /*----------------Session Not Support Sub--------------*/ 
   if(SessionMode_u8_Sig!=EXTEND_SESSION && (subFunction==01||subFunction==0x09||subFunction==02||subFunction==0x0A)&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SESSION_SUB_NOTSUPPROT_ERR; /*sub不支持错误码0x12*/
   }
   
   /*----------------Session Not Support Sub--------------*/ 
   if(SessionMode_u8_Sig!=PROGRANMMING_SESSION && (subFunction==0x05||subFunction==0x06)&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SESSION_SUB_NOTSUPPROT_ERR;  /*sub不支持错误码0x12*/
   }
   /*----------------Sequence Err--------------*/
   if(seedReqmrk==0 &&(subFunction==0x06 ||subFunction==02||subFunction==0x0A ) && RspFmt_u8_Sig!=NEG_RSP) {
      RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=ORDER_ERR;  /*顺序错误错误码0x24*/
   }
   if((subFunction&0x01)==0x00 &&seedReqmrk==1&& ((seedSub_u8_Tmp ==0x01 &&subFunction!=0x02 )||(seedSub_u8_Tmp==0x05 &&subFunction!=0x06 ) ||(seedSub_u8_Tmp ==0x09 &&subFunction!=0x0A ))&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=ORDER_ERR;  /*顺序错误错误码0x24*/
   }  
   /*----------------Key Frame Len Err--------------*/
   if((subFunction&0x01)==0x00 && RevMsgLen_u16_Sig!=6 && RspFmt_u8_Sig!=NEG_RSP)/*长度不足服务需求的长度*/ 
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=KEY_ERR;  /*长度不对错误码0x35*/  
   } 
   /*----------------SeedKey OverTime--------------*/
   if(ScurReqTimes_u8_Sig==1 && UnLockTimeOver_u8_Sig==1 &&\
    UnlockLimitTime_u16_Sig==SEED_KEY_TIMES && RspFmt_u8_Sig!=NEG_RSP)
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=UNLOCKDELAY_ERR;  /*解密功能延时错误码0x37*/
   }
   
   if(UnlockLimitTime_u16_Sig!=0 && ScurReqTimes_u8_Sig==0 && RspFmt_u8_Sig!=NEG_RSP)
   {
   	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=UNLOCKDELAY_ERR;  /**解密功能延时错误码0x37*/
   }
   
   /*-----------------------请求Seed子服务-------------------------------------*/
   
   if((subFunction&0x01)==0x01 &&   subFunction<=0x41 && RspFmt_u8_Sig!=NEG_RSP) {
   RspMsgLen_u16_Sig=5; /*正面回应的长度*/
   if(LockMode_u8_Sig == Lock) {/*判断是否解锁*/
   /*---------------------Seed随机赋值----------------------------------*/
   Service_RamdomGen();
   //Rsp_Msg.ReqSendMsg_u8_Tmp[2]=__byte(&Seed_u32_Sig,0);
   //Rsp_Msg.ReqSendMsg_u8_Tmp[3]=__byte(&Seed_u32_Sig,1);
   //Rsp_Msg.ReqSendMsg_u8_Tmp[4]=__byte(&Seed_u32_Sig,2);
   //Rsp_Msg.ReqSendMsg_u8_Tmp[5]=__byte(&Seed_u32_Sig,3);

   CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], &Seed_u32_Sig, LSB, LSB, 4);
   /*---------------------4个8位的Seed整合成32位----------------------------------*/
   //Seed_u32_Sig=Rsp_Msg.ReqSendMsg_u8_Tmp[2]&0xFF;
   //Seed_u32_Sig=(Seed_u32_Sig<<8)+(Rsp_Msg.ReqSendMsg_u8_Tmp[3]&0xFF);
   //Seed_u32_Sig=(Seed_u32_Sig<<8)+(Rsp_Msg.ReqSendMsg_u8_Tmp[4]&0xFF);
   //Seed_u32_Sig=(Seed_u32_Sig<<8)+(Rsp_Msg.ReqSendMsg_u8_Tmp[5]&0xFF);
   EcuKey=0;
   /*---------------------判断解密等级----------------------------------*/
   if(subFunction==0x01)
   {
	   EcuKey =SeedToKey_v_g(Seed_u32_Sig,Level1Mask_u32_Sig);/*解密算法得到Key*/
   }
   if(subFunction==0x05)
   {
	   EcuKey =SeedToKey_v_g(Seed_u32_Sig,Level2Mask_u32_Sig);/*解密算法得到Key*/
   }
   seedReqmrk=1;
   TestetKey = 0;/*诊断仪Key置0*/
   seedSub_u8_Tmp = subFunction;/*记录Seed的Sub*/
   } 
   else {
   /*---------------------已解密全部回复为0----------------------------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [2]=0x00; 
   //Rsp_Msg.ReqSendMsg_u8_Tmp [3]=0x00; 
   //Rsp_Msg.ReqSendMsg_u8_Tmp [4]=0x00; 
   //Rsp_Msg.ReqSendMsg_u8_Tmp [5]=0x00;

   Rsp_Msg.ReqSendMsg_u8_Tmp [1]=0x0000; 
   Rsp_Msg.ReqSendMsg_u8_Tmp [2]=0x0000; 

   RspFmt_u8_Sig=POS_RSP; 
   }
  }
   
   /*-------------------------------解密Key子服务-------------------------------------*/
   if((subFunction&0x01)==0x00 &&   subFunction<=0x42 && RspFmt_u8_Sig!=NEG_RSP) {
      /*--------------Key数据整合---------------------*/
      TestetKey=RevData[1];
      TestetKey=(TestetKey<<8)+RevData[2];
      TestetKey=(TestetKey<<8)+RevData[3];
      TestetKey=(TestetKey<<8)+RevData[4];

      if(EcuKey!=TestetKey) {/*密匙判断*/
      RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=KEY_ERR;  /*密匙错误错误码0x35*/
      } 
      else {
       
       if(subFunction ==0x02)/*判断Sub*/
       {
       	LockMode_u8_Sig=UnLock_Level; /*解密等级赋值*/
       }
       if(subFunction ==0x06)/*判断Sub*/
       {
       	LockMode_u8_Sig=UnLock_Level2;/*解密等级赋值*/
       }
       if(subFunction ==0x0A)/*判断Sub*/
       {
       	LockMode_u8_Sig=UnLock_Level3;/*解密等级赋值*/
       }
        UnlockLimitTime_u16_Sig=0;/*解密错误次数清零*/
        RspMsgLen_u16_Sig=1;/*发送数据的长度*/
      } 
      if(LockMode_u8_Sig == Lock && UnLockTimeOver_u8_Sig!=1) {/*解密错误判断*/
      UnlockLimitTime_u16_Sig++;/*解密错误次数计数*/
      if(UnlockLimitTime_u16_Sig==SEED_KEY_TIMES) {/*解密错误次数上限判断*/
      UnLockTimeOver_u8_Sig=1;/*解密错误次数上限标志位置1*/
      RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=UNLOCKOVERTIME_ERR;  /*解密次数超限*/ 
      }
   }
   
   }

   if(RspFmt_u8_Sig==NEG_RSP  ) { /*判断回应类型是否是负面回应*/
   	 seedReqmrk   = 0;   
   	 EcuKey       = 0;
     RspMsgLen_u16_Sig=2;/*发送数据的长度*/
   } 
   else {
     
   } 
 }
 
/*!******************************************************************************************************
*	@fn	 void ControlDTCSetting_v_g(BYTEPTR RevData)
*	@brief DTC设置服务函数
*	@author Matt Zhang
*	@param[in]	RevData为应用请求数据指针
*	@return	void
*	@note 
-
*********************************************************************************************************
*/
 void ControlDTCSetting_v_g(BYTEPTR RevData)
 {
   uint8_T subFunction;
   
   /*--------------获取命令数值-----------*/
   subFunction=__byte(RevData, MSB);/*sub_funtion赋值*/
   RspFmt_u8_Sig=POS_RSP; /*回应类型赋值*/
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*回应状态赋值*/
   subFunction=subFunction&0x7F;/*Sub_Funtion去高位处理*/
   SI_u8_Tmp=CONTROL_DTC_SETTING;
   DefSub_u8_Tmp=0x01;/*Sub服务标志位置1*/
   /*--------------正回应数据赋值----------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction;
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, subFunction);
  /*----------------Session Not Support--------------*/  
   if(SessionMode_u8_Sig!=EXTEND_SESSION)
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*会话模式不支持错误码0x7F*/
   } 
  /*----------------Len Err-------------------------*/  
   if(RevMsgLen_u16_Sig!=2 && RspFmt_u8_Sig!=NEG_RSP)/*长度不足服务需求的长度*/ 
   {
     RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/  
   } 
   /*----------------SubFun Err-------------------------*/   
   if(subFunction!=DTCSETTING_ON && subFunction!=DTCSETTING_OFF && RspFmt_u8_Sig!=NEG_RSP)
   {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR;/*sub不支持错误码0x12*/
   	
   }
  /*----------------Sub_Function -------------------------*/
   if(subFunction==DTCSETTING_ON && RspFmt_u8_Sig!=NEG_RSP)  /*On DTC Setting*/
   {
     DtcOnOff_u8_Sig=DTCSETTING_ON;
   } 
   else if(subFunction==DTCSETTING_OFF && RspFmt_u8_Sig!=NEG_RSP )/*Off DTC Setting*/ 
   {
     DtcOnOff_u8_Sig=DTCSETTING_OFF; 
   } 
   else {
    
   }
   
   if(RspFmt_u8_Sig==NEG_RSP  ) {/*判断回应类型是否是负面回应*/
     RspMsgLen_u16_Sig=2;/*发送数据的长度*/
   } 
   else {
     RspMsgLen_u16_Sig=1;/*发送数据的长度*/
   } 
 }
 /*!******************************************************************************************************
 *	@fn	 void CommunicationControl_v_g(BYTEPTR RevData)
 *	@brief 通信控制服务函数
 *	@author Matt Zhang
 *	@param[in]	RevData为应用请求数据指针
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void CommunicationControl_v_g(BYTEPTR RevData)
 {
   uint8_T subFunction;
   uint8_T comType;
   uint8_T txStatus;
   uint8_T rxStatus;
   
   /*-------------------获取命令数值-----------------------*/
   subFunction=__byte(RevData, MSB);/*sub_funtion赋值*/
   comType=RevData[1];/*通信类型赋值*/
   RspFmt_u8_Sig=POS_RSP;/*回应类型赋值*/
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*回应状态赋值*/
   subFunction=subFunction&0x7F; /*Sub_Funtion去高位处理*/
   SI_u8_Tmp=COMMUNICATION_CONTROL;
   DefSub_u8_Tmp=0x01;/*Sub服务标志位置1*/
   /*----------------正回应数据赋值-------------------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction;
   
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, subFunction);
 /*----------------Session Not Support--------------*/  
   if(SessionMode_u8_Sig!=EXTEND_SESSION)
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*会话模式不支持错误码0x7F*/
   }
 /*----------------Len Err-------------------------*/  
   if(RevMsgLen_u16_Sig!=3 && RspFmt_u8_Sig!=NEG_RSP ) 
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 
   } 
/*----------------SubFun Err-------------------------*/    
   if(subFunction!=0x00 && subFunction!=0x03 && RspFmt_u8_Sig!=NEG_RSP)
   {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR; /*sub不支持错误码0x12*/
   }
/*----------------ComType Err-------------------------*/   
   if((comType<0x01 || comType>0x03 )&& RspFmt_u8_Sig!=NEG_RSP)
   {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=OVERRANGE_ERR; /*值超范围错误码0x31*/
   }
 /*----------------Sub Function处理------------------------*/

   if(RspFmt_u8_Sig!=NEG_RSP ) {
      
   if(subFunction ==0x00) {  /*Tx和Rx都Enable*/
      txStatus=1;
      rxStatus=1;
   } 
   else if (subFunction ==0x01) {/*Tx Enable 和 Rx Disable*/
      txStatus=1;
      rxStatus=0;
    
   }
   else if (subFunction ==0x02) { /*Tx Disable 和 Rx Enable*/
      txStatus=0;
      rxStatus=1;
    
   }
   else if (subFunction ==0x03) { /*Tx和Rx都Disable*/
      txStatus=0;
      rxStatus=0;
    
   } 
   else
   {
   	
   	
   }
 
   }
   
   if(RspFmt_u8_Sig!=NEG_RSP ) {
   
   if(comType==0x01) {/*一般通信*/
   NormalComTx_u8_Sig = txStatus;/*我们这里只用到一般通信，当NormalComTx_u8_Sig为1时才能发送除UDS报文之外的报文*/
   NormalComRx_u8_Sig = rxStatus;/*当NormalComRx_u8_Sig为1时才能接收除UDS报文之外的报文*/
   }
   
   else if(comType==0x02) {/*一般通信*/
   NetWorkComTx_u8_Sig = txStatus;
   NetWorkComRx_u8_Sig = rxStatus;
   }
   
   else if(comType==0x03) {/*一般通信*/
   NormalComTx_u8_Sig =  txStatus;
   NormalComRx_u8_Sig =  rxStatus;
   NetWorkComTx_u8_Sig = txStatus;
   NetWorkComRx_u8_Sig = rxStatus; 
   } 
   
   else {
   
   }
   
   }
    
     
   if(RspFmt_u8_Sig==NEG_RSP  ) {/*判断回应类型是否是负面回应*/
     RspMsgLen_u16_Sig=2;/*发送数据的长度*/
   } 
   else {
     RspMsgLen_u16_Sig=1;/*发送数据的长度*/
   }    
     
}
/*!******************************************************************************************************
*	@fn	  void TesterPresent_v_g(BYTEPTR RevData)
*	@brief 握手函数、一般是为了不让会话模式转换默认会话
*	@author Matt Zhang
*	@param[in]	RevData为应用请求数据指针
*	@return	void
*	@note 
-
*********************************************************************************************************
*/  
 void TesterPresent_v_g(BYTEPTR RevData) 
 {
   uint8_T subFunction;
   /*---------------------获取命令数值----------------------*/
   subFunction=__byte(RevData, MSB);/*sub_funtion赋值*/
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*回应状态赋值*/
   subFunction=subFunction&0x7F;/*Sub_Funtion去高位处理*/
   RspFmt_u8_Sig=POS_RSP;/*回应类型赋值*/
   SI_u8_Tmp=TESTER_PRESENT;
   DefSub_u8_Tmp=0x01;/*Sub服务标志位置1*/
   /*----------------正回应数据赋值-------------------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction;
   
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, subFunction);
   /*----------------Len Err--------------*/
   if(RevMsgLen_u16_Sig!=2) 
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 
   } 
   /*----------------Sub Not　Support--------------*/
   if(RspFmt_u8_Sig!=NEG_RSP && subFunction!=0x00 ) 
   {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR; /*Sub不支持错误码0x12*/
   }

   if(RspFmt_u8_Sig==NEG_RSP  ) {/*判断回应类型是否是负面回应*/
     RspMsgLen_u16_Sig=2;/*发送数据的长度*/
   } 
   else {
     RspMsgLen_u16_Sig=1;/*发送数据的长度*/
   }  
   
 }
 
 /*!******************************************************************************************************
 *	@fn	 void ClearDiagImfor_v_g(BYTEPTR RevData)
 *	@brief 清除故障码函数
 *	@author Matt Zhang
 *	@param[in]	RevData为应用请求数据指针
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void ClearDiagImfor_v_g(BYTEPTR RevData) 
{
  
uint32_T dtcGroup;/*故障码组变量定义*/
SI_u8_Tmp=CLEAR_DIAGNOSTIC_INFORMATION;
DefSub_u8_Tmp=0x00;/*Sub状态位赋值*/
RspFmt_u8_Sig=POS_RSP;/*回应类型赋值*/
/*------------------Dtc Group 组合赋值*---------------------*/
dtcGroup=RevData[0];
dtcGroup=(dtcGroup<<8)+RevData[1];
dtcGroup=(dtcGroup<<8)+RevData[2];
/*-----------------------Session Not Support--------------*/
if(SessionMode_u8_Sig==PROGRANMMING_SESSION)
{
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*会话模式不对错误码0x7F*/
}
/*----------------Len Err--------------*/ 
   
if(RevMsgLen_u16_Sig!=4 && RspFmt_u8_Sig !=NEG_RSP) 
{
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 
} 
/*----------------Group Err--------------*/ 
if(dtcGroup!=DTCGROUP && dtcGroup!=ALLDTCGROUP && RspFmt_u8_Sig !=NEG_RSP)
{
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=OVERRANGE_ERR; /*参数范围不对错误码0x31*/
	
}
/*----------------Condition Err--------------*/ 
if(VehicleSpeed_u16_Sig!=0 && RspFmt_u8_Sig !=NEG_RSP ) {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CONDITION_NOTSURRORT_ERR;  /*条件不对错误码0x22*/
 }
 
if(RspFmt_u8_Sig !=NEG_RSP) {
#if APP_CODE ==1
   ClearDtc_v_g();/*在这里调用清除故障码函数*/
#endif   
}

if(RspFmt_u8_Sig==NEG_RSP  ) {/*判断回应类型是否是负面回应*/
   RspMsgLen_u16_Sig=2;/*发送数据的长度*/
} 
else {
   RspMsgLen_u16_Sig=0;/*发送数据的长度*/
}  



}
/*!******************************************************************************************************
 *	@fn	 void ReadDtcMsg_v_g(BYTEPTR RevData)
 *	@brief 读取故障码信息函数
 *	@author Matt Zhang
 *	@param[in]	RevData为应用请求数据指针
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void ReadDtcMsg_v_g(BYTEPTR RevData)
{
	
   uint8_T  subFunction;
   uint8_T  dtcStatusMark;
   uint8_T  dtcStatus;
   uint8_T  dtcNumcycle;
   uint16_T dtcMarkNum=0;
   uint16_T ExtendIndex=0;
   uint16_T SnapIndex=0;
   #define DTCHIGTBYTE    RevData[1]
   #define DTCLOWBYTE     RevData[2]
   #define DTCFAILUREBYTE RevData[3]
   uint8_T temp;
   /*-----------------------获取命令数值----------------------*/
   RspFmt_u8_Sig=POS_RSP;/*回应类型赋值*/
   subFunction=__byte(RevData, MSB);/*Sub_Function赋值*/
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*回应类型赋值*/
   subFunction=subFunction&0x7F;/*回应类型赋值*/
   SI_u8_Tmp=READ_DTC_INFORMATION; /*回应类型赋值*/
   DefSub_u8_Tmp=0x01;
   /*-----------------------回应数组赋值----------------------*/
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction;
   
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, subFunction);
   /*-----------------------Session Not Support----------------------*/
   if(SessionMode_u8_Sig==PROGRANMMING_SESSION)
   {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*会话模式不支持错误码0x7F*/
   }
   /*-----------------------Len Err-------------------------------*/
   if(RevMsgLen_u16_Sig<2&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 
   }
   if((subFunction==0x01  || subFunction==0x02) && RevMsgLen_u16_Sig!=3 && RspFmt_u8_Sig!=NEG_RSP)
   {
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 
   }
   
   if(subFunction==0x0A && RevMsgLen_u16_Sig!=2&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 
   }
   
   if((subFunction==0x06 ||subFunction==0x04 ) && RevMsgLen_u16_Sig!=6&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 
   }
   
   /*-----------------------Sub Not Support-------------------------------*/
   if(subFunction!=0x01 && subFunction!=0x02 &&subFunction!=0x04&& subFunction!=0x06 && subFunction!=0x0A&& RspFmt_u8_Sig!=NEG_RSP)
   {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR;  /*Sub不支持错误码0x12*/
   }
   /*-------------------------------Condition Err--------------------------*/
   if(VehicleSpeed_u16_Sig!=0 && RspFmt_u8_Sig!=NEG_RSP ) {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=CONDITION_NOTSURRORT_ERR;  /*条件不满足错误码0x22*/
   } 
   /*-----------------------------Sub_Function处理-------------------------*/
   if(RspFmt_u8_Sig!=NEG_RSP)
   {
   	switch(subFunction) {
   	/*-------------------------------读取符合掩码状态的故障码数--------------------*/
   	case 0x01:
   	for(dtcNumcycle=0;dtcNumcycle<DTCNUM;dtcNumcycle++) 
    {
       dtcStatus=DtcStatus_u16a8_Par[dtcNumcycle].Status.Byte; /*读取故障码状态，如果有自己定义的替换成自己的*/
       if((dtcStatus&dtcStatusMark)!=0) { /*故障码状态判断*/
         dtcMarkNum++;/*计数*/
       }
    }
   	/*-----------------------------回应数据和长度赋值--------------------------*/
    //Rsp_Msg.ReqSendMsg_u8_Tmp [2]= MASKSTATUS;/*掩码赋值，如果有自己定义的替换成自己的*/
    //Rsp_Msg.ReqSendMsg_u8_Tmp [3]= DTCFMT14229;
    //Rsp_Msg.ReqSendMsg_u8_Tmp [4]=(uint8_T)(dtcMarkNum>>8);
    //Rsp_Msg.ReqSendMsg_u8_Tmp [5]=(uint8_T)dtcMarkNum;

	temp = (uint8_T)(dtcMarkNum>>8);
	Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], LSB, MASKSTATUS);
	Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], MSB, DTCFMT14229);
	Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], LSB, temp);
	temp = (uint8_T)(dtcMarkNum);
	Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], MSB, temp);
    RspMsgLen_u16_Sig = 5;
   	break;
   	
   	case 0x02:
   /*-----------------------------读取符合掩码状态的故障码及状态-------------------*/
   	dtcStatusMark =RevData[1];
   	for(dtcNumcycle=0;dtcNumcycle<DTCNUM;dtcNumcycle++) 
    {
    dtcStatus=DtcStatus_u16a8_Par[dtcNumcycle].Status.Byte; /*获取故障码状态,如果有自己定义的替换成自己的*/
    if((dtcStatus&dtcStatusMark)!=0) {/*故障码状态判断*/
    /*----------------------将故障码及状态赋值给回应数组--------------------------*/
    //Rsp_Msg.ReqSendMsg_u8_Tmp [3+(dtcMarkNum<<2)]=(uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte1;/*故障码如果有自己定义请替换成自己的*/
    //Rsp_Msg.ReqSendMsg_u8_Tmp [4+(dtcMarkNum<<2)]=(uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte2;/*故障码如果有自己定义请替换成自己的*/
    //Rsp_Msg.ReqSendMsg_u8_Tmp [5+(dtcMarkNum<<2)]=(uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte3;/*故障码如果有自己定义请替换成自己的*/
    //Rsp_Msg.ReqSendMsg_u8_Tmp [6+(dtcMarkNum<<2)]=(uint8_T)dtcStatus;
    dtcMarkNum++;
       }
    }
    //Rsp_Msg.ReqSendMsg_u8_Tmp [2]= MASKSTATUS;/*掩码赋值，如果有自己定义的替换成自己的*/
	
	Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], LSB, MASKSTATUS);
    RspMsgLen_u16_Sig = 2+(dtcMarkNum<<2);/*掩码赋值*/
   	break;
   	
   	case 0x04:
   /*-----------------------------读取故障码的Snapshot数据--------------------------*/
    for(dtcNumcycle=0;dtcNumcycle<DTCNUM;dtcNumcycle++) 
    {       
     if(DTCHIGTBYTE==((uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte1) && DTCLOWBYTE==((uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte2) \
     && DTCFAILUREBYTE==((uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte3))/*判断故障码是否有符合的，如果有自己定义的替换成自己的*/
     {
     dtcStatus=(uint8_T)DtcStatus_u16a8_Par[dtcNumcycle].Status.Byte;/*获取故障码状态,如果有自己定义的替换成自己的*/
     SnapIndex = dtcNumcycle;
   /*-------------故障码及状态赋值----------------*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [2]=DTCHIGTBYTE;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [3]=DTCLOWBYTE;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [4]=DTCFAILUREBYTE;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [5]=dtcStatus;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [6]=0x01;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [7]=0x04;
	 
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], LSB, DTCHIGTBYTE);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], MSB, DTCLOWBYTE);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], LSB, DTCFAILUREBYTE);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], MSB, dtcStatus);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[3], LSB, 0x01);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[3], MSB, 0x04);
     dtcMarkNum++;
     }
   
    }
    /*-------------Snap数据赋值给回应数组----------------*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [8]=0x01;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [9]=0x12;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [10]=(uint8_T)DtcSnapShot_u80a8_Par[SnapIndex].SupBatt;/*电压,如果有自己定义的替换成自己的*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [11]=0xE1;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [12]=0x01;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [13]=(uint8_T)((DtcSnapShot_u80a8_Par[SnapIndex].Odreading &0xFF0000)>>16);/*里程数,如果有自己定义的替换成自己的*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [14]=(uint8_T)((DtcSnapShot_u80a8_Par[SnapIndex].Odreading &0x00FF00)>>8);/*里程数,如果有自己定义的替换成自己的*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [15]=(uint8_T)(DtcSnapShot_u80a8_Par[SnapIndex].Odreading&0x0000FF);/*里程数,如果有自己定义的替换成自己的*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [16]=0xD0;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [17]=0x01;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [18]=(uint8_T)DtcSnapShot_u80a8_Par[SnapIndex].IgStatus;/*Ig状态,如果有自己定义的替换成自己的*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [19]=0x01;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [20]=0x0C;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [21]=(uint8_T)DtcSnapShot_u80a8_Par[SnapIndex].CoolTemp;/*温度,如果有自己定义的替换成自己的*/

	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[4], LSB, 0x01);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[4], MSB, 0x12);

	 temp = (uint8_T)DtcSnapShot_u80a8_Par[SnapIndex].SupBatt;
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[5], LSB, temp);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[5], MSB, 0xE1);
	 
	 temp = (uint8_T)((DtcSnapShot_u80a8_Par[SnapIndex].Odreading &0xFF0000)>>16);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[6], LSB, 0x01);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[6], MSB, temp);

 	 temp = (uint8_T)((DtcSnapShot_u80a8_Par[SnapIndex].Odreading &0x00FF00)>>8);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[7], LSB, temp);
 	 temp = (uint8_T)((DtcSnapShot_u80a8_Par[SnapIndex].Odreading &0xFF0000));
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[7], MSB, temp);

	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[8], LSB, 0xD0);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[8], MSB, 0x01);

	 temp = (uint8_T)DtcSnapShot_u80a8_Par[SnapIndex].IgStatus;
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[9], LSB, temp);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[9], MSB, 0x01);

	 temp = (uint8_T)DtcSnapShot_u80a8_Par[SnapIndex].CoolTemp;
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[10], LSB, 0x0C);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[10], MSB, temp);

     RspMsgLen_u16_Sig =21;
   	 if(dtcMarkNum == 0)/*判断支持DTC是否为0*/
     {
       RspFmt_u8_Sig=NEG_RSP;
       NegRsp_u8_Sig=OVERRANGE_ERR;/*报错参数超范围错误码0x31*/
     }
   	break;
   	
   	case 0x06:
   	/*-----------------------------读取故障码的Extend数据--------------------------*/
    for(dtcNumcycle=0;dtcNumcycle<DTCNUM;dtcNumcycle++) 
    {       
     if(DTCHIGTBYTE==((uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte1) && DTCLOWBYTE==((uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte2) \
     && DTCFAILUREBYTE==((uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte3))/*判断故障码是否有符合的，如果有自己定义的替换成自己的*/
     {
     dtcStatus=(uint8_T)DtcStatus_u16a8_Par[dtcNumcycle].Status.Byte;/*获取故障码状态,如果有自己定义的替换成自己的*/
     ExtendIndex = dtcNumcycle;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [2]=DTCHIGTBYTE;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [3]=DTCLOWBYTE;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [4]=DTCFAILUREBYTE;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [5]=dtcStatus;
     //Rsp_Msg.ReqSendMsg_u8_Tmp [6]=0x01;

	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], LSB, DTCHIGTBYTE);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], MSB, DTCLOWBYTE);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], LSB, DTCFAILUREBYTE);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[2], MSB, dtcStatus);
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[3], LSB, 0x01);
	 
        dtcMarkNum++;
     }
   
    }
     //Rsp_Msg.ReqSendMsg_u8_Tmp [7]=(uint8_T)DtcExtend_u64a8_Par[ExtendIndex].FualtCnt;/*故障计数,如果有自己定义的替换成自己的*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [8]=(uint8_T)DtcExtend_u64a8_Par[ExtendIndex].PendCnt;/*未确认故障计数,如果有自己定义的替换成自己的*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [9]=(uint8_T)DtcExtend_u64a8_Par[ExtendIndex].AgedCnt;/*已经轮询到最大值的次数,如果有自己定义的替换成自己的*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [10]=(uint8_T)DtcExtend_u64a8_Par[ExtendIndex].AgingCnt;/*轮询次数,如果有自己定义的替换成自己的*/

	 temp = (uint8_T)DtcExtend_u64a8_Par[ExtendIndex].FualtCnt;
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[3], MSB, temp);

	 temp = (uint8_T)DtcExtend_u64a8_Par[ExtendIndex].PendCnt;
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[4], LSB, temp);
	 temp = (uint8_T)DtcExtend_u64a8_Par[ExtendIndex].AgedCnt;
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[4], MSB, temp);
	 temp = (uint8_T)DtcExtend_u64a8_Par[ExtendIndex].AgingCnt;
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[5], LSB, temp);


	 RspMsgLen_u16_Sig =10;
 	 if(dtcMarkNum == 0)/*判断支持DTC是否为0*/
     {
       RspFmt_u8_Sig=NEG_RSP;
       NegRsp_u8_Sig=OVERRANGE_ERR;/*报错参数超范围错误码0x31*/
     }
   	break;
   	
   	case 0x0A:
   	/*-----------------------------读取所有故障码状态--------------------------*/
   	for(dtcNumcycle=0;dtcNumcycle<DTCNUM;dtcNumcycle++) 
    {
     dtcStatus=DtcStatus_u16a8_Par[dtcNumcycle].Status.Byte;/*获取故障码状态,如果有自己定义的替换成自己的*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [3+(dtcNumcycle<<2)]=(uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte1;/*故障码如果有自己定义请替换成自己的*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [4+(dtcNumcycle<<2)]=(uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte2;/*故障码如果有自己定义请替换成自己的*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [5+(dtcNumcycle<<2)]=(uint8_T)DtcNumb_u24a8_Par[dtcNumcycle].byte3;/*故障码如果有自己定义请替换成自己的*/
     //Rsp_Msg.ReqSendMsg_u8_Tmp [6+(dtcNumcycle<<2)]=dtcStatus;
    }
     //Rsp_Msg.ReqSendMsg_u8_Tmp [2]= MASKSTATUS;
	 
	 Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], LSB, MASKSTATUS);
     RspMsgLen_u16_Sig = 2+(DTCNUM<<2);/*掩码赋值，如果有自己定义的替换成自己的*/
   	break;
   	
   	default:
   	
   	break;
   		
   	}
   	
   }
  
   
if(RspFmt_u8_Sig==NEG_RSP  ) {/*判断回应类型是否是负面回应*/
  RspMsgLen_u16_Sig=2;/*发送数据的长度*/
} 
else {

}  

}
/*!******************************************************************************************************
 *	@fn	 void ReadDataById_v_g(BYTEPTR RevData)
 *	@brief 根据DATAID读取数据函数
 *	@author Matt Zhang
 *	@param[in]	RevData为应用请求数据指针
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void ReadDataById_v_g(BYTEPTR RevData)
{
 uint16_T  idNum=0;
 uint16_T  dataId=0;
 uint16_T  defIdNum=0;
 uint8_T   i;
 
 SI_u8_Tmp=READ_DATA_BY_IDENTIFIER;
 DefSub_u8_Tmp=0x00;/*Sub状态位赋值*/
 RspFmt_u8_Sig=POS_RSP;/*回应类型赋值*/
 /*-----------------------Len Err----------------------*/
 if((RevMsgLen_u16_Sig%2)==0 || RevMsgLen_u16_Sig<2) 
 {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 
 } 
 /*-----------------------最多不超过3个DID读取----------------------*/
 if(RspFmt_u8_Sig!=NEG_RSP)
 {
 //idNum =(RevMsgLen_u16_Sig-1)>>1; 
 if(RevMsgLen_u16_Sig!=3) {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*Length error 0x13*/
 }
 }		
if(RspFmt_u8_Sig!=NEG_RSP)
{
/*-----------------------DID获取及处理---------------------------*/
 //for(i=0;i<idNum;i++) {
 //dataId=RevData[0+(i<<1)];
 //dataId=(dataId<<8)+RevData[1+(i<<1)];
 dataId = __byte(&RevData[0], MSB)*256;
 dataId += __byte(&RevData[1], LSB);

 switch(dataId) {
  case 0xF110: /*---PIF Pointer to Current Block---*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
  						   &RevData[0],
  						   MSB,
  						   MSB,
  						   2);

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
  						   &PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][0],
  						   MSB,
  						   LSB,
  						   16);
  defIdNum=18;
  break;
  
  case 0xF111:/*---PIF Spe Blocks---*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[1][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF112:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[2][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF113:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[3][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF114:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[4][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF115:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[5][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF116:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[6][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF117:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[7][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF118:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[8][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF119:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[9][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF11A:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[10][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF11B:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[11][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF11C:/*---SoftWare Version---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[12][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF11D:/*---SoftWare Version---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[13][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF11E:/*---SoftWare Version---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[14][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF11F:/*---PIF Spe Blocks---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &PifPtcb_u16a16a16_Par[15][0],
							MSB,
							LSB,
							16);
  defIdNum=18;
  break;
  
  case 0xF183:/*---ECU BootLoader Software Reference Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
						   &BootSwRefNumb_u16a10_Par[0],
							MSB,
							LSB,
							10);
  defIdNum=12;
  
  break;
  
  
  case 0xF187:/*---ECU Part Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &ECUPartNumb_u16a6_Par[0],
              MSB,
              LSB,
              6);
  defIdNum=8;
  break;
  
  case 0xF18A:/*---System Supplier Id---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &SysSupplierId_u16a6_Par[0],
              MSB,
              LSB,
              6);
  defIdNum=8;
  break;
  
  case 0xF190:/*---VIN---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &Vin_u16a17_Par[0],
              MSB,
              LSB,
              17);
  defIdNum=19;
  break;
  
  case 0xF191:/*---ECU HardWare Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuHwNumb_u16a6_Par[0],
              MSB,
              LSB,
              6);
  defIdNum=8;
  break;
  
  case 0xF192:/*---Supplier Ecu HardWare Reference Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuHwRefNumb_u16a10_Par[0],
              MSB,
              LSB,
              10);
  defIdNum=12;
  break;
  
  case 0xF194:/*---Supplier Ecu SoftWare Reference Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuSwRefNumb_u16a10_Par[0],
              MSB,
              LSB,
              10);
  defIdNum=12;
  break;

  case 0xF1A0:/*---Ecu Application Software Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuAppSwNumb_u16a6_Par[0],
              MSB,
              LSB,
              6);
  defIdNum=8;
  break;
  
  
  case 0xF1A1:/*---Ecu Calibration Software Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuCalSwNumb_u16a6_Par[0],
              MSB,
              LSB,
              6);
  defIdNum=8;
  break;
  
  case 0xF1A2:/*---ECU Net Reference Number---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuNetRefNumb_u16a6_Par[0],
              MSB,
              LSB,
              6);
  defIdNum=8;
  break;
  
  case 0xF1A8:/*---Vehicle Feature Information---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &VehFeature_u16a20_Par[0],
              MSB,
              LSB,
              20);
  defIdNum=22;
  break;
  
  case 0xF18B:/*---Ecu Manufacture Data---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuMData_u16a3_Par[0],
              MSB,
              LSB,
              3);
  defIdNum=5;
  break;
  
  case 0xF18C:/*---VINDataId---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EcuSupplierSN_u16a10_Par[0],
              MSB,
              LSB,
              10);
  defIdNum=12;
  break;
  case 0xAFFC:/*---Bootloader刷写次数---*/

  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &BootTimes_u16_Par,
              MSB,
              LSB,
              2);
  defIdNum=4;
  break; 
  case 0xAFFD:/*---软件完整---*/
/*  Rsp_Msg.ReqSendMsg_u8_Tmp[1+defIdNum]=RevData[0+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[2+defIdNum]=RevData[1+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[3+defIdNum]=(uint8_T)SIS_u16_Sig;*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &SIS_u16_Sig,
              MSB,
              LSB,
              1);
  defIdNum=3;  
  break; 
  case 0xAFFE:/*---软件兼容---*/
/*  Rsp_Msg.ReqSendMsg_u8_Tmp[1+defIdNum]=RevData[0+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[2+defIdNum]=RevData[1+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[3+defIdNum]=(uint8_T)SCS_u16_Sig;*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &SCS_u16_Sig,
              MSB,
              LSB,
              1);
  defIdNum=3; 
  break;   
  case 0xAFFF:/*---软件有效---*/
/*  Rsp_Msg.ReqSendMsg_u8_Tmp[1+defIdNum]=RevData[0+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[2+defIdNum]=RevData[1+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[3+defIdNum]=(uint8_T)SVF_u16_Par;*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &SVF_u16_Par,
              MSB,
              LSB,
              1);
  defIdNum=3;
  break;
  
  case 0xD110:/*---MotorSpeed---*/

 #if APP_CODE ==0
//  MotorSpd_u16_Sig= g_CANDataVar.nEngine_RMP_dCAN;  /*这里的赋值可以自己去修改*/
  MotorSpd_u16_Sig= g_CANDataVar.nEngine_RMP_dCAN*2;  // factor:0.5, intel  20160306 by ljh.
 #endif
/*  Rsp_Msg.ReqSendMsg_u8_Tmp[1+defIdNum]=RevData[0+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[2+defIdNum]=RevData[1+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[3+defIdNum]=(uint8_T)(MotorSpd_u16_Sig>>8);
  Rsp_Msg.ReqSendMsg_u8_Tmp[4+defIdNum]=(uint8_T)(MotorSpd_u16_Sig);*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &MotorSpd_u16_Sig,
              MSB,
              LSB,
              2);

  defIdNum=4;
  break; 
  case 0xD002:/*---Park Status---*/
#if APP_CODE ==0
	  ParkStatus_u8_Sig=(g_CANDataVar.nParkLock_St_dCAN<<5)+(CanDataVar.bit.nPark_Active<<4)+(CanDataVar.bit.nDrive_Ready<<3)+(g_CANDataVar.nParkReq_dCAN<<1);
 // ParkStatus_u8_Sig=  g_CANDataVar.nParkReq_dCAN; /*这里的赋值可以自己去修改*/
#endif
/*  Rsp_Msg.ReqSendMsg_u8_Tmp[1+defIdNum]=RevData[0+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[2+defIdNum]=RevData[1+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[3+defIdNum]=ParkStatus_u8_Sig;*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &ParkStatus_u8_Sig,
              MSB,
              LSB,
              1);
  defIdNum=3;  
  break; 

  case 0xD003:/*---EPP Status---*/
#if APP_CODE ==0
	//  EppStatus_u8_Sig=  eppstatus; /*这里的赋值可以自己去修改,修改好请将前面的注释双斜杠去除*/
	//  EppStatus_u8_Sig= CanDataVar.bit.nPark_Active;				//ljh 20160224
	//20160306 ljh
  EppStatus_u8_Sig=((FltSt1Var.FLTST1.bit.nMot_Jam_Middle_Fault<<5)+(FltSt1Var.FLTST1.bit.nPark_Stalled_Fault<<4)+(FltSt1Var.FLTST1.bit.nUnpark_Stalled_Fault<<3)+(FltSt1Var.FLTST1.bit.nNo_Load_Fault<<2))&0x3C;
#endif
/*  Rsp_Msg.ReqSendMsg_u8_Tmp[1+defIdNum]=RevData[0+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[2+defIdNum]=RevData[1+i*2];
  Rsp_Msg.ReqSendMsg_u8_Tmp[3+defIdNum]=EppStatus_u8_Sig;*/
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
             &RevData[0],
             MSB,
             MSB,
             2);
  
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], 
               &EppStatus_u8_Sig,
              MSB,
              LSB,
              1);
  defIdNum=3;
  break;
  default:
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=OVERRANGE_ERR;  /*数据范围超限错误码0x31*/
  break;
  
 }
  
 //}
 
 }
if(RspFmt_u8_Sig==NEG_RSP  ) {/*判断回应类型是否是负面回应*/
  RspMsgLen_u16_Sig=2;/*发送数据的长度*/
} 
else {
  RspMsgLen_u16_Sig=defIdNum;/*发送数据的长度*/
} 
 
}
/*!******************************************************************************************************
 *	@fn	void WriteDataById_v_g(BYTEPTR RevData)
 *	@brief 根据DATAID写数据函数
 *	@author Matt Zhang
 *	@param[in]	RevData为应用请求数据指针
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */

void WriteDataById_v_g(BYTEPTR RevData)
{
uint16_T dataId;

SI_u8_Tmp=WRITE_DATA_BY_IDENTIFIER;
DefSub_u8_Tmp=0x00;/*Sub状态位赋值*/
RspFmt_u8_Sig=POS_RSP;/*回应类型赋值*/


dataId = __byte(&RevData[0], MSB)*256;
dataId += __byte(&RevData[1], LSB);

//WrDidBackUp_Sig[0]=RevData[0];/*DID赋值*/
//WrDidBackUp_Sig[1]=RevData[1];/*DID赋值*/
//LockMode_u8_Sig= UnLock_Level;
//SessionMode_u8_Sig=EXTEND_SESSION;

/*-----------------------Seesion Not Support----------------------*/
if(SessionMode_u8_Sig==DEFAULT_SESSION || AdrType_u8_Sig!=TAtype_phiscal)
{
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*会话模式不对错误码0x7F*/
}
/*-----------------------SeedKey Err----------------------*/
if(LockMode_u8_Sig!=UnLock_Level &&  SessionMode_u8_Sig==EXTEND_SESSION && RspFmt_u8_Sig!=NEG_RSP)
{
	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;  /*未解密错误码0x33*/
	
}
if(LockMode_u8_Sig!=UnLock_Level2 &&  SessionMode_u8_Sig==PROGRANMMING_SESSION && RspFmt_u8_Sig!=NEG_RSP)
{
	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;  /*未解密错误码0x33*/
	
}

if(RspFmt_u8_Sig!=NEG_RSP)
{
 switch(dataId) {
  case 0xF110:/*---PIF---*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=19)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 		
  }
  else
  {
  PifBlockNumb_u16_Sig++;/*block计数*/
  if(PifBlockNumb_u16_Sig==16)
  {
	 PifBlockNumb_u16_Sig=2;/*当15个都写满了后从第2个开始写*/
  }
  /*---PIF Pointer to Current Block---*/
  #if 0
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][0]   =RevData[2];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][1]   =RevData[3];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][2]   =RevData[4];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][3]   =RevData[5];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][4]   =RevData[6];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][5]   =RevData[7];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][6]   =RevData[8];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][7]   =RevData[9];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][8]   =RevData[10];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][9]   =RevData[11];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][10]  =RevData[12];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][11]  =RevData[13];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][12]  =RevData[14];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][13]  =RevData[15];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][14]  =RevData[16];
  PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][15]  =RevData[17];
  #endif
  CopyMemory_WithNone_Byte(&PifPtcb_u16a16a16_Par[PifBlockNumb_u16_Sig][0], 
               &RevData[1],
              LSB,
              MSB,
              16);
  
  //DidEep_u8_Sig=1;/*写DID标志位*/
 #if APP_CODE==0
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=FLEXRSPTIME_ERR;  /*写EEPROM延时 0x78*/
 #endif
  }
  break;
  
  case 0xA300:/*---ECU Part Numb---F187*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=9)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 		
  }
  else
  {
  #if 0
  ECUPartNumb_u16a6_Par[0] =RevData[2];
  ECUPartNumb_u16a6_Par[1] =RevData[3];
  ECUPartNumb_u16a6_Par[2] =RevData[4];
  ECUPartNumb_u16a6_Par[3] =RevData[5];
  ECUPartNumb_u16a6_Par[4] =RevData[6];
  ECUPartNumb_u16a6_Par[5] =RevData[7];	
  #endif
  CopyMemory_WithNone_Byte(&ECUPartNumb_u16a6_Par[0], 
           &RevData[1],
          LSB,
          MSB,
          6);

  }
 
  break;

  case 0xA301:/*---Supper ID---F18A*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=9)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 		
  }
  else
  {

  CopyMemory_WithNone_Byte(&SysSupplierId_u16a6_Par[0], 
       &RevData[1],
      LSB,
      MSB,
      6);
  //DidEep_u8_Sig=1;/*写DID标志位*/

  }
  break;

  case 0xA302:/*---Manufacture Data---F18B*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=6)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 		
  }
  else
  {

  CopyMemory_WithNone_Byte(&EcuMData_u16a3_Par[0], 
       &RevData[1],
      LSB,
      MSB,
      3);
  //DidEep_u8_Sig=1;/*写DID标志位*/

  }
  break;

  case 0xA303:/*---Supplier serial number---F18C*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=13)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 		
  }
  else
  {

  CopyMemory_WithNone_Byte(&EcuSupplierSN_u16a10_Par[0], 
       &RevData[1],
      LSB,
      MSB,
      10);
  //DidEep_u8_Sig=1;/*写DID标志位*/

  }
  break;

  case 0xA304:/*---Hardware version---F191*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=9)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 		
  }
  else
  {

  CopyMemory_WithNone_Byte(&EcuHwNumb_u16a6_Par[0], 
       &RevData[1],
      LSB,
      MSB,
      6);
  //DidEep_u8_Sig=1;/*写DID标志位*/

  }
  break;
  
  case 0xF190:/*---VIN---*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=20)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 		
  }
  else
  {

  CopyMemory_WithNone_Byte(&Vin_u16a17_Par[0], 
       &RevData[1],
      LSB,
      MSB,
      17);
  //DidEep_u8_Sig=1;/*写DID标志位*/
 #if APP_CODE==0
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=FLEXRSPTIME_ERR; /*写EEPROM延时 0x78*/
 #endif
  }
  
  break;
  
  
  case 0xF1A8:/*---VehFeature---*/
  /*-----------------------Len Err----------------------*/
  if(RevMsgLen_u16_Sig!=23)
  {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 		
  }
  else
  {
  #if 0
  VehFeature_u16a20_Par[0]  =RevData[2];
  VehFeature_u16a20_Par[1]  =RevData[3];
  VehFeature_u16a20_Par[2]  =RevData[4];
  VehFeature_u16a20_Par[3]  =RevData[5];
  VehFeature_u16a20_Par[4]  =RevData[6];
  VehFeature_u16a20_Par[5]  =RevData[7];	
  VehFeature_u16a20_Par[6]  =RevData[8];
  VehFeature_u16a20_Par[7]  =RevData[9];
  VehFeature_u16a20_Par[8]  =RevData[10];
  VehFeature_u16a20_Par[9]  =RevData[11];
  VehFeature_u16a20_Par[10] =RevData[12];
  VehFeature_u16a20_Par[11] =RevData[13];
  VehFeature_u16a20_Par[12] =RevData[14];	
  VehFeature_u16a20_Par[13] =RevData[15];
  VehFeature_u16a20_Par[14] =RevData[16];
  VehFeature_u16a20_Par[15] =RevData[17];
  VehFeature_u16a20_Par[16] =RevData[18];
  VehFeature_u16a20_Par[17] =RevData[19];
  VehFeature_u16a20_Par[18] =RevData[20];
  VehFeature_u16a20_Par[19] =RevData[21];
  #endif
  CopyMemory_WithNone_Byte(&VehFeature_u16a20_Par[0], 
       &RevData[1],
      LSB,
      MSB,
      20);
  //DidEep_u8_Sig=1;/*写DID标志位*/
 #if APP_CODE==0
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=FLEXRSPTIME_ERR; /*写EEPROM延时 0x78*/
 #endif

  }
  break;
  
  
  default:
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=OVERRANGE_ERR;/*数据超范围错误码 0x78*/
  break;
  
 }	
 
}

if(RspFmt_u8_Sig==NEG_RSP  ) {
  RspMsgLen_u16_Sig=2;/*发送数据的长度*/
} 
else {
  RspMsgLen_u16_Sig=2;/*发送数据的长度*/
  //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=RevData[0];
  //Rsp_Msg.ReqSendMsg_u8_Tmp [2]=RevData[1];
  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],
					   &RevData[0],
					   MSB,
					   MSB,
					   2);

} 
}
/*!******************************************************************************************************
 *	@fn	void ReadMemoryByAddress_v_g(BYTEPTR RevData)
 *	@brief 通过地址读取数据
 *	@author Matt Zhang
 *	@param[in]	RevData为应用请求数据指针
 *	@return	void
 *	@note
 -目前支持的地址是EEPROM的地址
 *********************************************************************************************************
 */
void ReadMemoryByAddress_v_g(BYTEPTR RevData) {
#define RM_ADRBYTES (RevData[0]&0x0F)
#define RM_DATALENBYTES (RevData[0]>>4)
uint8_T  cmdLen;
uint32_T memAdr;
uint16_T dataLen;

RspFmt_u8_Sig=POS_RSP;/*回应类型赋值*/
SI_u8_Tmp=READ_MEMORY_BY_ADDRESS;
DefSub_u8_Tmp=0x00;/*Sub状态赋值*/

cmdLen=ECU_SUPPROT_ADDRESSLEN+MAX_DATANUMBYTE+2;/*命令要求的最小长度*/
/*-----------地址获取----------------*/
memAdr=RevData[1];
memAdr=(memAdr<<8)+RevData[2];
memAdr=(memAdr<<8)+RevData[3];
memAdr=(memAdr<<8)+RevData[4];
/*-----------数据长度获取----------------*/
dataLen=RevData[5];
dataLen=(dataLen<<8)+RevData[6];
dataLen=dataLen>>1;
MemAdr_u32_Sig=memAdr;/*地址赋值*/
MemDataLen_u16_Sig =dataLen;/*数据长度赋值*/
/*-----------------------Session Not Support----------------------*/
if(((SessionMode_u8_Sig==DEFAULT_SESSION) && (AdrType_u8_Sig!=TAtype_phiscal))|| ((SessionMode_u8_Sig==EXTEND_SESSION) && (AdrType_u8_Sig!=TAtype_phiscal)) \
||(SessionMode_u8_Sig==PROGRANMMING_SESSION))
{
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*会话模式不支持为0x7F*/
	
}
/*-----------------------Len Err----------------------*/
if(RevMsgLen_u16_Sig!=cmdLen && RspFmt_u8_Sig!=NEG_RSP) {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/  
}
/*----------------------SeedKey Err----------------------*/
if(LockMode_u8_Sig!=UnLock_Level &&  SessionMode_u8_Sig==EXTEND_SESSION && RspFmt_u8_Sig!=NEG_RSP)
{
	RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;  /*未解密错误码为0x33*/
	
}
/*----------------------Condition Err----------------------*/
if((RM_ADRBYTES!=ECU_SUPPROT_ADDRESSLEN ||RM_DATALENBYTES!=MAX_DATANUMBYTE)&&RspFmt_u8_Sig!= NEG_RSP) {
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=OVERRANGE_ERR;  /*地址格式及长度格式不对错误码0x31*/
}

if(dataLen>MAX_MEMWRITENUM &&RspFmt_u8_Sig!= NEG_RSP) {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=OVERRANGE_ERR;  /*长度超限错误码0x31*/
}
if((memAdr<RWDATA_MINADR ||(memAdr+dataLen-1)>RWDATA_MAXADR) && RspFmt_u8_Sig!= NEG_RSP  )
{
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=OVERRANGE_ERR;   /*地址超限错误码0x31*/
}


if(RspFmt_u8_Sig!= NEG_RSP) { 
 RMemDataFLag_u8_Sig = 1;/*地址读数据标志位置位*/
 RspFmt_u8_Sig=NEG_RSP;
 NegRsp_u8_Sig=FLEXRSPTIME_ERR; /*写EEPROM延时0x78*/
}


if(RspFmt_u8_Sig==NEG_RSP  ) {
  RspMsgLen_u16_Sig=2;/*发送数据的长度*/
} 
else {
} 

}

/*!******************************************************************************************************
 *	@fn	void WriteMemoryByAddress_v_g(BYTEPTR RevData)
 *	@brief 通过地址写数据
 *	@author Matt Zhang
 *	@param[in]	RevData为应用请求数据指针
 *	@return	void
 *	@note
 -目前支持的地址是EEPROM的地址
 *********************************************************************************************************
 */
void WriteMemoryByAddress_v_g(BYTEPTR RevData) {
#define WM_ADRBYTES (RevData[0]&0x0F)
#define WM_DATALENBYTES (RevData[0]>>4)
uint8_T    cmdLen;
uint32_T   memAdr;
uint16_T   dataLen;
uint16_T   Index;
uint16_T   cnt;
RspFmt_u8_Sig=POS_RSP;/*回应类型赋值*/
SI_u8_Tmp=WRITE_MEMORY_BY_ADDRESS;
DefSub_u8_Tmp=0x00;/*Sub状态赋值*/

Index=ECU_SUPPROT_ADDRESSLEN+MAX_DATANUMBYTE+1;/*写EEPROM起始元素*/

adrLenFmtId_u8_Sig =RevData[0];
/*---------------------获取地址--------------------------------*/
memAdr=RevData[1];
memAdr=(memAdr<<8)+RevData[2];
memAdr=(memAdr<<8)+RevData[3];
memAdr=(memAdr<<8)+RevData[4];
/*---------------------地址记录--------------------------------*/
BackUpMemInfor_u8_Sig[0]=RevData[1];/*地址记录*/
BackUpMemInfor_u8_Sig[1]=RevData[2];/*地址记录*/
BackUpMemInfor_u8_Sig[2]=RevData[3];/*地址记录*/
BackUpMemInfor_u8_Sig[3]=RevData[4];/*地址记录*/
/*---------------------获取地址--------------------------------*/
dataLen=RevData[5];
dataLen=(dataLen<<8)+RevData[6];
cmdLen=ECU_SUPPROT_ADDRESSLEN+MAX_DATANUMBYTE+2+dataLen;/*命令长度*/
dataLen=dataLen>>1;
/*---------------------获取地址--------------------------------*/
BackUpMemInfor_u8_Sig[4] =RevData[5]; /*长度记录*/
BackUpMemInfor_u8_Sig[5] =RevData[6]; /*长度记录*/
MemAdr_u32_Sig=memAdr;/*地址赋值*/
MemDataLen_u16_Sig =dataLen;/*数据长度*/


/*----------------------Session Not Support----------------------*/
if(SessionMode_u8_Sig!=EXTEND_SESSION || AdrType_u8_Sig!=TAtype_phiscal)
{
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*会话模式错误码0x7F*/
}
/*----------------------Len Err----------------------*/
if(RevMsgLen_u16_Sig!=cmdLen && RspFmt_u8_Sig!=NEG_RSP) {
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/  
}
/*----------------------SeedKey Err----------------------*/
if(LockMode_u8_Sig!=UnLock_Level &&  SessionMode_u8_Sig==EXTEND_SESSION && RspFmt_u8_Sig!=NEG_RSP)
{
   RspFmt_u8_Sig=NEG_RSP;
   NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;  /*未解密错误码0x33*/
	
}
/*----------------------Over Range----------------------*/
if((WM_ADRBYTES!=ECU_SUPPROT_ADDRESSLEN ||WM_DATALENBYTES!=MAX_DATANUMBYTE) && RspFmt_u8_Sig!= NEG_RSP) {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=OVERRANGE_ERR;  /*格式不对错误码0x31*/
}

if(dataLen>MAX_MEMWRITENUM && RspFmt_u8_Sig!= NEG_RSP) {
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=OVERRANGE_ERR;  /*长度超限错误码0x31*/
}
if((memAdr<RWDATA_MINADR ||(memAdr+dataLen-1)>RWDATA_MAXADR) && RspFmt_u8_Sig!= NEG_RSP  )
{
 RspFmt_u8_Sig=NEG_RSP;
 NegRsp_u8_Sig=OVERRANGE_ERR;/*长度超限错误码0x31*/
}

if(RspFmt_u8_Sig!= NEG_RSP) {
for(cnt=0;cnt<dataLen;cnt++)
{
	MemData_u16_Sig[cnt]= RevData[Index+(cnt*2)];/*赋值写地址值*/
	MemData_u16_Sig[cnt]=(MemData_u16_Sig[cnt]<<8)+RevData[Index+1+(cnt*2)];/*赋值写地址值*/
}
 WMemDataFLag_u8_Sig = 1;/*写地址标志位置位*/
 BackUpPosLen_u16_Sig=ECU_SUPPROT_ADDRESSLEN+MAX_DATANUMBYTE+1;/*记录正常回应的长度*/
 RspFmt_u8_Sig=NEG_RSP;
 NegRsp_u8_Sig=FLEXRSPTIME_ERR; /*延时码0x78*/
}

if(RspFmt_u8_Sig==NEG_RSP  ) {
  RspMsgLen_u16_Sig=2;/*发送数据的长度*/
} 
else {
} 

}

/*!******************************************************************************************************
 *	@fn	void InputOutputControlById(BYTEPTR RevData)
 *	@brief 输入输出函数
 *	@author Matt Zhang
 *	@param[in]	RevData为应用请求数据指针
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */

void InputOutputControlById(BYTEPTR RevData) 
{
#define CONTROLPAPA RevData[2]
uint16_T dataId=0;
RspFmt_u8_Sig=POS_RSP;/*回应类型赋值*/
SI_u8_Tmp=INPUT_OUTPUT_CONTROL_BY_IDENTIFIER;
DefSub_u8_Tmp=0x00;/*Sub状态赋值*/

dataId= RevData[0];/*DID 获取数值*/
dataId=(dataId<<8)+  RevData[1];/*DID 获取数值*/
/*----------------------Session Not Support----------------------*/
if(SessionMode_u8_Sig!=EXTEND_SESSION || AdrType_u8_Sig!=TAtype_phiscal)
{
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;  /*会话模式错误码0x7F*/
}
/*---------------------Len Err----------------------*/
if(RevMsgLen_u16_Sig<5 && RspFmt_u8_Sig!=NEG_RSP )
{
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=CMD_LENGTH_ERR;  /*长度不对错误码0x13*/ 	
}
/*---------------------SeedKey Err----------------------*/
if(SessionMode_u8_Sig==EXTEND_SESSION && LockMode_u8_Sig!=UnLock_Level && RspFmt_u8_Sig!=NEG_RSP)
{
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;  /*未解密错误码0x33*/
}
/*---------------------Condition Err----------------------*/
if(CONTROLPAPA!=0x00 && CONTROLPAPA!=0x02 && CONTROLPAPA!=0x03 && RspFmt_u8_Sig!=NEG_RSP)
{
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CONDITION_NOTSURRORT_ERR;/*条件不满足错误码0x22*/
}
if(RspFmt_u8_Sig!=NEG_RSP)
{
 	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=OVERRANGE_ERR;  /*目前没有支持的DID，所以全部错误码0x31*/
}

if(RspFmt_u8_Sig==NEG_RSP  ) {
  RspMsgLen_u16_Sig=2;/*发送数据的长度*/
} 
else {
} 
}
/*!******************************************************************************************************
 *	@fn	void RoutineControl_v_g(BYTEPTR RevData)
 *	@brief 流控制函数
 *	@author Matt Zhang
 *	@param[in]	RevData为应用请求数据指针
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void RoutineControl_v_g(BYTEPTR RevData) 
{
   #define ROUTINE_ADRBYTES (__byte(&RevData[2], LSB)&0x0F)
   #define ROUTINE_DATALENBYTES (__byte(&RevData[2], LSB)>>4)
   uint8_T  subFunction;
   uint8_T  routineId;

   RspFmt_u8_Sig=POS_RSP;/*回应类型赋值*/
   //subFunction=RevData[0];/*Sub赋值*/
   subFunction=__byte(RevData, MSB);
   supPosRspMsgIndBit_u8_Tmp=0x80 & subFunction;/*回应状态赋值*/
   subFunction=subFunction&0x7F;/*Sub_Funtion去高位处理*/
   SI_u8_Tmp=ROUTINE_CONTROL; 
   DefSub_u8_Tmp=0x01;	/*Sub状态赋值*/
   
   //Rsp_Msg.ReqSendMsg_u8_Tmp [1]=subFunction;/*回应数据赋值*/
   Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0],MSB,subFunction);
   /*----------------DID赋值-----------------*/
   routineId = __byte(&RevData[1], LSB)*256;
   routineId +=__byte(&RevData[1], MSB);
   //routineId = (routineId<<8)+RevData[2];

   /*----------------------Sub Not Support----------------------*/
   if(subFunction!=0x01 && RspFmt_u8_Sig!=NEG_RSP)
   {
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR;  /*长度不对错误码0x13*/ 	
   }
   /*----------------------SeedKey Err----------------------*/
   if(SessionMode_u8_Sig==EXTEND_SESSION &&(LockMode_u8_Sig!=UnLock_Level)&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;
   }
   
   /*----------------------DID Err----------------------*/
   if((routineId!=0xAF10)&& RspFmt_u8_Sig!=NEG_RSP)
   {
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=OVERRANGE_ERR;  	
   }
  
   if(RspFmt_u8_Sig!=NEG_RSP)
   {
   	switch(routineId)
   	{
   		
   		case 0xAF10:/*程序兼容性*/

		CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], &RevData[1], LSB, LSB, 2);
		EEPROM_Backup();
   		break;
   		
   		default:
			RspFmt_u8_Sig = NEG_RSP;

   		break;
   	}
   } 
   
   if(RspFmt_u8_Sig==NEG_RSP)
   {
	  RspMsgLen_u16_Sig = 2;
   }
   else{
      RspMsgLen_u16_Sig = 3; 
   }
 }
 

#if APP_CODE==0
/*!******************************************************************************************************
 *	@fn	void RequestDownload_v_g(BYTEPTR RevData)
 *	@brief 请求下载函数
 *	@author Matt Zhang
 *	@param[in]	RevData为应用请求数据指针
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void RequestDownload_v_g(BYTEPTR RevData) 
{
#define  DATAFMT            RevData[0]
#define  RQ_ADRBYTES       (RevData[1]&0x0F)
#define  RQ_DATALENBYTES   (RevData[1]>>4)
uint8_T    cmdLen;
uint32_T   dnloadAdr;
uint32_T   dnloadLen;
uint16_T   maxBlock;

RspFmt_u8_Sig=POS_RSP;/*回应类型赋值*/
SI_u8_Tmp=REQUEST_DOWNLOAD;
DefSub_u8_Tmp=0x00;	/*Sub状态赋值*/
cmdLen = WRITE_FLASH_ADRBYTES+WRITE_FLASH_DATALENBYTES+3;/*命令长度赋值*/

/*-------------下载地址赋值-----------------------*/
dnloadAdr=RevData[2];
dnloadAdr=(dnloadAdr<<8)+RevData[3];
dnloadAdr=(dnloadAdr<<8)+RevData[4];
dnloadAdr=(dnloadAdr<<8)+RevData[5];
/*-------------下载长度赋值-----------------------*/
dnloadLen=RevData[6];
dnloadLen=(dnloadLen<<8)+RevData[7];
dnloadLen=(dnloadLen<<8)+RevData[8];
dnloadLen=(dnloadLen<<8)+RevData[9];
dnloadLen=dnloadLen>>1;
/*-------------Session Not Support-----------------------*/
if(SessionMode_u8_Sig!=PROGRANMMING_SESSION || AdrType_u8_Sig!=TAtype_phiscal)
{
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;
}
/*-----------------------Len Err-----------------------*/
if(RevMsgLen_u16_Sig!= cmdLen && RspFmt_u8_Sig!=NEG_RSP)
{ 
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CMD_LENGTH_ERR;
}
/*-----------------------SeedKey Err-----------------------*/
if(SessionMode_u8_Sig==PROGRANMMING_SESSION && LockMode_u8_Sig!=UnLock_Level2 && RspFmt_u8_Sig!=NEG_RSP)
{
     RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;
}
/*-----------------------Over Range-----------------------*/
if(DATAFMT!=0x00  && RspFmt_u8_Sig!= NEG_RSP)
{
    RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=OVERRANGE_ERR;
}
/*-----------------------Over Range-----------------------*/
if((RQ_ADRBYTES!=WRITE_FLASH_ADRBYTES || RQ_DATALENBYTES!=WRITE_FLASH_DATALENBYTES) && RspFmt_u8_Sig!= NEG_RSP) {
       RspFmt_u8_Sig=NEG_RSP;
       NegRsp_u8_Sig=OVERRANGE_ERR;
 }
/*-----------------------Over Range-----------------------*/
if((dnloadAdr+dnloadLen)>(ERASE_FLASH_SECTORB_ADR+ERASE_FLASH_SECTORB_LENGTH+ERASE_FLASH_SECTORD_LENGTH) && RspFmt_u8_Sig!= NEG_RSP)
{
   	    RspFmt_u8_Sig=NEG_RSP;
        NegRsp_u8_Sig=OVERRANGE_ERR;  
}
/*-----------------------Over Range-----------------------*/
if( dnloadAdr<ERASE_FLASH_SECTORF_ADR&& RspFmt_u8_Sig!= NEG_RSP)
{
   	    RspFmt_u8_Sig=NEG_RSP;
        NegRsp_u8_Sig=OVERRANGE_ERR;  
}
/*-----------------------Over Range-----------------------*/
if(dnloadAdr<(ERASE_FLASH_SECTORF_ADR+ERASE_FLASH_SECTORF_LENGTH)\
&&(dnloadAdr+dnloadLen)>(ERASE_FLASH_SECTORF_ADR+ERASE_FLASH_SECTORF_LENGTH)&& RspFmt_u8_Sig!= NEG_RSP)
{
   	    RspFmt_u8_Sig=NEG_RSP;
        NegRsp_u8_Sig=OVERRANGE_ERR;  
}
/*-----------------------Over Range-----------------------*/
if(dnloadAdr>=ERASE_FLASH_SECTORC_ADR && dnloadAdr<ERASE_FLASH_SECTORB_ADR&& RspFmt_u8_Sig!= NEG_RSP)
{
   	    RspFmt_u8_Sig=NEG_RSP;
        NegRsp_u8_Sig=OVERRANGE_ERR; 
}
/*-----------------------Over Range-----------------------*/
if((dnloadAdr+dnloadLen)>=ERASE_FLASH_SECTORC_ADR && (dnloadAdr+dnloadLen)<ERASE_FLASH_SECTORB_ADR\
&& RspFmt_u8_Sig!= NEG_RSP)
{
   	    RspFmt_u8_Sig=NEG_RSP;
        NegRsp_u8_Sig=OVERRANGE_ERR; 
} 
/*-----------------------Over Range-----------------------*/
if(dnloadAdr== ERASE_FLASH_SECTORD_ADR && dnloadLen!=ERASE_FLASH_SECTORD_LENGTH && RspFmt_u8_Sig!= NEG_RSP  )
{
     RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=OVERRANGE_ERR;  	
}
/*-----------------------Over Range-----------------------*/
if(RspFmt_u8_Sig!= NEG_RSP)
{
	/*-----------------------判断是否最后一条数据-----------------------*/
	if(dnloadAdr== ERASE_FLASH_SECTORD_ADR && dnloadLen==ERASE_FLASH_SECTORD_LENGTH)
	{
		EndHex_u8_Sig=1;/*最后一条数据置位*/
	}
	else
	{
		EndHex_u8_Sig=0;
	}
	maxBlock = MAX_NUM_BLOCK;/*最大Block数据赋值*/
	Rsp_Msg.ReqSendMsg_u8_Tmp [1]=LEN_MFT;/*格式赋值*/
	Rsp_Msg.ReqSendMsg_u8_Tmp [2]=(uint8_T)(maxBlock>>8);/*Block大小赋值给回应数组*/
	Rsp_Msg.ReqSendMsg_u8_Tmp [3]=(uint8_T)(maxBlock);/*Block大小赋值给回应数组*/
	WFlashAdr_u32_Sig = dnloadAdr;/*地址赋值*/
    WriteMemLen_u32_Sig=dnloadLen;/*长度赋值*/
    ReqTranExitStatus_u8_Sig = Req_Sucess;/*流程状态赋值*/
    TransferLen_u32_Sig = 0;/*发送长度清0*/
    BlockCnt_u8_Sig=1;/*Block值置1*/
    TranRevCnt_u32_Sig = 0;/*发送数据计数清0*/
    crcData_u32_Sig = 0;/*Crc校验值赋值0*/
}


if(RspFmt_u8_Sig==NEG_RSP  ) {
  RspMsgLen_u16_Sig=2;/*发送数据的长度*/
} 
else {
  RspMsgLen_u16_Sig=3;/*发送数据的长度*/
} 

}
/*!******************************************************************************************************
 *	@fn	void TansferData_v_g(BYTEPTR RevData)
 *	@brief 发送数据函数
 *	@author Matt Zhang
 *	@param[in]	RevData为应用请求数据指针
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void TansferData_v_g(BYTEPTR RevData)
{
#define  BLOCKCOUNTER      RevData[0] 
uint16_T wflashlen;
uint8_T  cnt;
RspFmt_u8_Sig=POS_RSP;/*回应类型赋值*/
SI_u8_Tmp=TRANSFER_DATA;
DefSub_u8_Tmp=0x00;	/*Sub状态赋值*/
TranRevCnt_u32_Sig = 0;/*发送计数清0*/
/*-------------Session Not Support-----------------------*/
if(SessionMode_u8_Sig!=PROGRANMMING_SESSION || AdrType_u8_Sig!=TAtype_phiscal)
{
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;
}
/*----------------------Len Err-------------------------*/
if(RevMsgLen_u16_Sig>MAX_NUM_BLOCK && RspFmt_u8_Sig!=NEG_RSP)
{ 
   	 RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=CMD_LENGTH_ERR;
}
/*----------------------SeedKey Err-------------------------*/
if(SessionMode_u8_Sig==PROGRANMMING_SESSION && LockMode_u8_Sig!=UnLock_Level2 && RspFmt_u8_Sig!=NEG_RSP)
{
     RspFmt_u8_Sig=NEG_RSP;
     NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;
}
/*----------------------Order Err-------------------------*/
if((ReqTranExitStatus_u8_Sig != Req_Sucess && ReqTranExitStatus_u8_Sig != Tran_Sucess)&& RspFmt_u8_Sig!=NEG_RSP)
{
	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=ORDER_ERR;
}
/*----------------------Block Cnt Err-------------------------*/
if(BlockCnt_u8_Sig!=BLOCKCOUNTER && RspFmt_u8_Sig!=NEG_RSP)
{
 	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=BLOCKSN_ERR;
}
/*----------------------Len To long-------------------------*/
if(TransferLen_u32_Sig>WriteMemLen_u32_Sig && RspFmt_u8_Sig!=NEG_RSP)
{
	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=TRANDATA_STOP_ERR;
}

if(RspFmt_u8_Sig!=NEG_RSP)
{
WFlashFlag_u8_Sig=1;/*写Flash标志位*/
wflashlen = RevMsgLen_u16_Sig-2;/*获取有效数据长度*/
wflashlen= wflashlen>>1;/*写Flash的长度*/
for(cnt=0;cnt<wflashlen;cnt++)
{
	FlashWBuffer_u16_Sig[cnt]= RevData[1+(cnt*2)];/*写FlashBuffer数据赋值*/
	FlashWBuffer_u16_Sig[cnt]=(FlashWBuffer_u16_Sig[cnt]<<8)+RevData[2+(cnt*2)];/*写FlashBuffer数据赋值*/

	TranBuff_u8_Sig[TranRevCnt_u32_Sig]=RevData[1+(cnt*2)];/*Crc需要校验的数据赋值*/
	TranBuff_u8_Sig[TranRevCnt_u32_Sig+1]=RevData[2+(cnt*2)];/*Crc需要校验的数据赋值*/
	TranRevCnt_u32_Sig=TranRevCnt_u32_Sig+2;
	FlashLen_u32_Sig=FlashLen_u32_Sig+2;/*整个写Flash的数据长度计算*/
}
/*--------------------------------CRC校验计算-------------------------------*/
crcData_u32_Sig=GenerateCRC32(TranBuff_u8_Sig, wflashlen, crcData_u32_Sig);
crcData_u32_Sig=0xFFFFFFFF-crcData_u32_Sig;

BootWFalshLen_u16_Sig = wflashlen;/*Boot写Flash长度*/
TransferLen_u32_Sig = TransferLen_u32_Sig+wflashlen;/*每一个请求总共发送的数据长度*/
TranBlock_u8_Sig=BLOCKCOUNTER;
RspFmt_u8_Sig=NEG_RSP;
NegRsp_u8_Sig=FLEXRSPTIME_ERR;  /*延时0x78*/
if(BlockCnt_u8_Sig<0xFF)
{
BlockCnt_u8_Sig++;/*block counter计数*/
}
else
{
BlockCnt_u8_Sig=0;		
}
ReqTranExitStatus_u8_Sig = Tran_Sucess;/*流程赋值*/
}

if(RspFmt_u8_Sig==NEG_RSP)
{
 RspMsgLen_u16_Sig=2;/*发送数据的长度*/
}
else
{
 RspMsgLen_u16_Sig=1;/*发送数据的长度*/
}
}
/*!******************************************************************************************************
 *	@fn	void RequestTansferExit_v_g(BYTEPTR RevData)
 *	@brief 请求数据传送退出函数
 *	@author Matt Zhang
 *	@param[in]	RevData为应用请求数据指针
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void RequestTansferExit_v_g(BYTEPTR RevData)
{
#define  CRCTYPE      RevData[0] 

RspFmt_u8_Sig=POS_RSP;/*回应类型赋值*/
SI_u8_Tmp=REQUEST_TRANSFER_EXIT;
DefSub_u8_Tmp=0x00;	/*Sub状态赋值*/
BackUpExit_u8_Sig = CRCTYPE;/*记录请求类型*/
/*-------------Session Not Support-----------------------*/
if(SessionMode_u8_Sig!=PROGRANMMING_SESSION || AdrType_u8_Sig!=TAtype_phiscal)
{
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=SESSIONNOTSUPPROT_ERR;
}
/*-------------Len Err-----------------------*/
if(RevMsgLen_u16_Sig!=2 && RspFmt_u8_Sig!=NEG_RSP)
{ 
   	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=CMD_LENGTH_ERR;
}
/*-------------Len Err-----------------------*/
if(CRCTYPE!=0x00 && CRCTYPE!=0x01 && RspFmt_u8_Sig!=NEG_RSP)
{
	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=SUBFUNCTION_NOTSUPPORT_ERR;
}
/*-------------SeedKey Err-----------------------*/
if(SessionMode_u8_Sig==PROGRANMMING_SESSION && LockMode_u8_Sig!=UnLock_Level2 && RspFmt_u8_Sig!=NEG_RSP)
{
      RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=NOTGETAUTHORITY_ERR;
}
/*-------------Order Err-----------------------*/
if(ReqTranExitStatus_u8_Sig!=Tran_Sucess&& RspFmt_u8_Sig!=NEG_RSP)
{
 	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=ORDER_ERR;
}
/*----------------------Data Len Err-------------------------*/
if(TransferLen_u32_Sig!=WriteMemLen_u32_Sig && RspFmt_u8_Sig!=NEG_RSP)
{
	  RspFmt_u8_Sig=NEG_RSP;
      NegRsp_u8_Sig=ORDER_ERR;
}

if(RspFmt_u8_Sig!=NEG_RSP)
{
	Rsp_Msg.ReqSendMsg_u8_Tmp [1]=CRCTYPE;/*Crc Type赋值*/
	
	switch(CRCTYPE)
	{
		case 0:
		RspMsgLen_u16_Sig=1;/*发送数据的长度*/
		break;
		case 1:
		/*-------------Crc 赋值回应数组---------------*/
        Rsp_Msg.ReqSendMsg_u8_Tmp [2]=(uint8_T)(crcData_u32_Sig>>24);
        Rsp_Msg.ReqSendMsg_u8_Tmp [3]=(uint8_T)(crcData_u32_Sig>>16);
        Rsp_Msg.ReqSendMsg_u8_Tmp [4]=(uint8_T)(crcData_u32_Sig>>8);
        Rsp_Msg.ReqSendMsg_u8_Tmp [5]=(uint8_T)(crcData_u32_Sig);
        RspMsgLen_u16_Sig=5;/*发送数据的长度（除去SI和N_SI）*/ 	
		break;
		
		default:
		break;
	
	}	
	if(EndHex_u8_Sig==1)/*最终数据标志位判断*/
	{
	if(FlashLen_u32_Sig>52800)/*总的长度判断*/
	{
	 SvfEep_u8_Sig=1;/*SVF写EEPROM标志位*/
	 SVF_u16_Par=1;/*SVF置位*/
	 Jump_u8_Sig =1;/*跳转标志位置位*/
	 RspFmt_u8_Sig=NEG_RSP;
	 NegRsp_u8_Sig=FLEXRSPTIME_ERR;  /*延时0x78*/
	 FlashLen_u32_Sig = 0;/*总长度清0*/
	}
	 EndHex_u8_Sig = 0;	
	}
    ReqTranExitStatus_u8_Sig = Exit_Sucess;/*流程赋值*/
    TransferLen_u32_Sig = 0;/*实际发送数据长度清0*/

    BlockCnt_u8_Sig=1;/*块计数值置位1*/
    WriteMemLen_u32_Sig=0;/*要求发送数据长度清0*/


}

if(RspFmt_u8_Sig==NEG_RSP)
{
 RspMsgLen_u16_Sig=2;/*发送数据的长度*/
}
else
{
 
}

}

#endif
/*!******************************************************************************************************
 *	@fn	void AppUdsService_v_g(BYTEPTR Services)
 *	@brief 服务函数调度函数
 *	@author Matt Zhang
 *	@param[in]	Services为应用请求数据指针
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void AppUdsService_v_g(BYTEPTR Services) 
{
 #define   ServiceId   __byte(Services,0)
 //uint8_T ServiceId;
 //ServiceId = __byte(&Services[0],0);
 
 RspFmt_u8_Sig=POS_RSP;
 switch(ServiceId) 
 {  
 
  /*With Sub-Function UDS Service*/
  case DIAGNOSTIC_SESSION_CONTROL:/*会话模式切换*/
  DiagnosticSessionControl_v_g(Services);
  break;
  
  case ECU_RESET:/*ECU重启服务*/
  EcuReset_v_g(Services);
  break;
  
  case SECURITY_ACCESS:   /*安全进入服务*/
  SecurityAccess_v_g(Services);
  break;
  
  case COMMUNICATION_CONTROL: /*通信服务控制*/
  CommunicationControl_v_g(Services);
  break;
  
  case CONTROL_DTC_SETTING:   /*控制DTC*/
  ControlDTCSetting_v_g(Services);
  break;
  
  case TESTER_PRESENT:   /*握手*/
  TesterPresent_v_g(Services);
  break;

  case READ_DTC_INFORMATION: /*读取DTC信息*/
  ReadDtcMsg_v_g(Services);
  break;
  

  case ROUTINE_CONTROL: /*流控制*/
#if APP_CODE==1
  RoutineControl_v_g(Services);
#endif
  break;
  
  /*Without Sub-Function UDS Service*/ 
  case READ_DATA_BY_IDENTIFIER: /*通过DID读取数据*/
  ReadDataById_v_g(Services);
  break;

  case READ_MEMORY_BY_ADDRESS : /*通过地址读取数据*/
  ReadMemoryByAddress_v_g(Services);
  break;
  
  case WRITE_DATA_BY_IDENTIFIER:/*通过DID写数据*/
  WriteDataById_v_g(Services);
  break;
                             
  case WRITE_MEMORY_BY_ADDRESS:/*通过地址写数据*/
  WriteMemoryByAddress_v_g(Services);
  break;
  
  case CLEAR_DIAGNOSTIC_INFORMATION:/*清除故障码*/
  ClearDiagImfor_v_g(Services);
  break;
  
  case INPUT_OUTPUT_CONTROL_BY_IDENTIFIER:/*输入输出控制*/
  InputOutputControlById(Services); 
  break;
  default:
  SI_u8_Tmp=ServiceId;
  RspFmt_u8_Sig=NEG_RSP;
  NegRsp_u8_Sig=SEVICE_NOTSUPPORT_ERR; 
  RspMsgLen_u16_Sig = 2; 
  break;  
 }
 
}
/*!******************************************************************************************************
 *	@fn	void AppSendRspMsg(void)
 *	@brief 应用层发送回应数据函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void AppSendRspMsg(void) 
{                      
 AppReqNetSend_v_g(Rsp_Msg,&UdsRequest); 
}
/*!******************************************************************************************************
 *	@fn	void UDSApp_v_g(void)
 *	@brief Uds执行函数，需要放在时序中调度
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void UDSApp_v_g(void) 
{
#if APP_CODE==0
	/* ---------Can取报文函数---------------*/
	CanOutHandel_v_g();
#endif
	/*------------- 网络层执行函数------------*/
 	NetworkLayerServices_GF_step();
 	/*------------- 时间处理函数------------*/
 	TimeDual_v_g();
 #if APP_CODE==0
 	/*------------- 写Flash处理函数------------*/
 	WriteFlashDual();
 	/*------------- 擦除Flash处理函数------------*/
 	EraseFlashDual();
 #endif
 #if APP_CODE==1
 	/*------------- Dtc处理函数------------*/
     DtcCycleDef_v_g();
 #endif
     /*-------------写EEPROM处理函数------------*/
 	 //SaveData_v_g();
 	/*------------- Reset处理函数------------*/
     SwReset_v_g();
     /*-------------根据地址读数据处理函数------------*/
 	 ReadMemDual();
 	 /*-------------根据地址写数据处理函数------------*/
 	 //WriteMemDual();
 	 /*-------------首帧判断------------*/
	if(IndicationCmd_u8_Sig==1){ 	
	  IndicationCmd_u8_Sig=0;
	  AppReceiveFFind_v_g();/*首帧处理函数*/
	}
	 /*-------------数据确认完整判断------------*/
	if(IndicationCmd_u8_Sig==2){ 	
	  IndicationCmd_u8_Sig = 0;
	  P2CntStart_u8_Sig    = 1;/*回应计时标志置位*/
	  S3Sever_u16_Sig      = 0;/*会话模式计时清0*/
	  AppRevNetData_v_g(&UdsIndication,Req_Msg);/*应用层获取数值*/
	  if(UDS_Timeout_u8_Sig ==0 && SFLength_Ovrn_u8_Sig==0 \
			&&  FrameErr_u8_Sig==0)/*判断有无报错*/
	  {
	  AppUdsService_v_g(Req_Msg.IndReceiveMsg_u8_Sig); /*服务函数处理*/
	  }
	  if(!ResponseMechanism_v_s() && UDS_Timeout_u8_Sig ==0 && SFLength_Ovrn_u8_Sig==0 \
			&&  FrameErr_u8_Sig==0 )/*判断有无报错及是否要回应*/
	  {
	     AppSendRspMsg();/*请求网络层发送数据*/
	  }

	}

	if(ConfirmCmd_u8_Sig==1){
	  ConfirmCmd_u8_Sig=0;
	  AppConFrimNet_v_g(&UdsConfirm);/*确认函数处理*/
	}
}  

/*!******************************************************************************************************
 *	@fn	uint8_T ResponseMechanism_v_s()
 *	@brief 回应机制函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	uint8_T 是否回应状态位
 *	@note
 -
 *********************************************************************************************************
 */
uint8_T ResponseMechanism_v_s() 
{
/*-----------------------------------------------------
*在TAtype_phiscal模式只有suppress-PosRspMsg-Indication-Bit为真时，ID和Sub都支持，且至少有一个参数是支持的
*在TAtype_functional模式，suppress-PosRspMsg-Indication-Bit为假，ID不支持、Sub不支持，一个参数都不支持的 
*在TAtype_functional模式，suppress-PosRspMsg-Indication-Bit为真，ID不支持、Sub不支持，一个参数都不支持的、至少有一个参数支持 
-------------------------------------------------------*/
 if (AdrType_u8_Sig==TAtype_phiscal)
 {
   if(supPosRspMsgIndBit_u8_Tmp==0x80 && RspFmt_u8_Sig==POS_RSP && DefSub_u8_Tmp==0x01)
   {
   	return 1;
   }
 	
 }
 if(AdrType_u8_Sig==TAtype_functional)
 {
   if(NegRsp_u8_Sig==SUBFUNCTION_NOTSUPPORT_ERR && DefSub_u8_Tmp==0x01)
   {
   	return 1;
   }
   
   if(NegRsp_u8_Sig==SESSIONNOTSUPPROT_ERR && DefSub_u8_Tmp==0x01)
   {
   	return 1;
   }
   
 }
return 0;
}
/*!******************************************************************************************************
 *	@fn	void  AppReceiveFFind_v_g()
 *	@brief 应用层首帧处理函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void  AppReceiveFFind_v_g()
{
	  P2CntStart_u8_Sig    = 1;/*回应计时标志置位*/
	  S3Sever_u16_Sig      = 0;/*会话模式计时清0*/
}
/*!******************************************************************************************************
 *	@fn	void TimeDual_v_g(void)
 *	@brief 应用层时间机制处理函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void TimeDual_v_g(void)
{
 if(P2CntStart_u8_Sig==1) {/*判断计时是否开始*/
    P2Sever_u16_Sig++;/*计数器累加*/
    if(P2Sever_u16_Sig==P2_CANSERVER) {/*判断计数器是否达到设定值*/
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=FLEXRSPTIME_ERR;/*回应增强延时命令*/
    RspMsgLen_u16_Sig = 2;/*回应长度*/
    P2FlexCntStart_u8_Sig=1;/*增强型延时开启*/
    }
  } 
  else {
    P2Sever_u16_Sig=0; /*计数器清0*/
  }
  
  if(P2FlexCntStart_u8_Sig==1) {/*判断计时是否开始*/
    P2FlexSever_u16_Sig++;
    if(P2FlexSever_u16_Sig==P2_FLEXCANSERVER ) {/*判断计数器是否达到设定值*/
    RspFmt_u8_Sig=NEG_RSP;
    NegRsp_u8_Sig=FLEXRSPTIME_ERR; /*回应增强延时命令*/
    RspMsgLen_u16_Sig = 2;	/*回应长度*/
    }
    else
    {
    P2FlexSever_u16_Sig = 0;	
    }
    
  } 
  else {
   P2FlexSever_u16_Sig=0; /*计数器清0*/
  }
  
  if(SessionMode_u8_Sig!= DEFAULT_SESSION ) {/*判断会话模式是否是默认会话模式*/
    S3Sever_u16_Sig++;/*计数器计数*/
    if(S3Sever_u16_Sig==S3SERVER) {/*判断计数器是否达到设定值*/
    SessionMode_u8_Sig = DEFAULT_SESSION;
    EraseFStatus_u8_Sg=0;
    EraseABStatus_u8_Sg=0;
    LockMode_u8_Sig=Lock;
    NormalComTx_u8_Sig = 1;
    NormalComRx_u8_Sig = 1;
    }
  } 
  else
  {
  	S3Sever_u16_Sig=0;	
  }
  
  /*--------------------------判断解密次数是否达上限-------------------------------*/
if(UnLockTimeOver_u8_Sig==1 && UnlockLimitTime_u16_Sig==SEED_KEY_TIMES && ScurReqTimes_u8_Sig!=0)
  {
  	Secur_u32_Sig++;/*计数器计数*/
  	if(Secur_u32_Sig==SECUR_LIMIT_TIME)/*判断计数值*/
  	{
  		UnlockLimitTime_u16_Sig--;/*解密错误次数减去1*/
  		UnLockTimeOver_u8_Sig = 0;
  		Secur_u32_Sig=0;/*计数器清0*/
  	}
  }
  
 /*----------------------Power On /Reset----------------------------------*/ 
 if(UnlockLimitTime_u16_Sig!=0 && ScurReqTimes_u8_Sig==0)
  {
  	if(UnlockLimitTime_u16_Sig>SECUR_LIMIT_TIME)
    {
	   UnlockLimitTime_u16_Sig=SEED_KEY_TIMES;
    }
  	Secur_u32_Sig++;/*计数器计数*/
  	if(Secur_u32_Sig==SECUR_LIMIT_TIME)/*判断计数值*/
  	{
  		UnlockLimitTime_u16_Sig--;/*解密错误次数减去1*/
  		UnLockTimeOver_u8_Sig = 0;
  		ScurReqTimes_u8_Sig=1;
  		Secur_u32_Sig=0;
  	}
  }
} 


/*!******************************************************************************************************
 *	@fn	uint32_T  GenerateCRC32(BYTEPTR DataBuf, uint32_T len, uint32_T oldcrc32)
 *	@brief CRC32校验函数
 *	@author Matt Zhang
 *	@param[in]	DataBuf校验的数据指针，len校验的数据长度，oldcrc32校验值变量
 *	@return	uint32_T校验值
 *	@note
 -
 *********************************************************************************************************
 */
uint32_T  GenerateCRC32(BYTEPTR DataBuf, uint32_T len, uint32_T oldcrc32)
{
	unsigned long i; 
	for(i=0; i<len; ++i) 
	{    
    // oldcrc32 = ((oldcrc32<<8))^crc_32_tab[(long)((oldcrc32>>24)^DataBuf[i])];  
    }  
    
    return oldcrc32; 
}
/*!******************************************************************************************************
 *	@fn	uint32_T seedToKey (uint32_T seed, uint32_T MASK)
 *	@brief SeedKey校验函数
 *	@author Matt Zhang
 *	@param[in]	seed种子，MASK校验掩码
 *	@return	uint32_T为Key
 *	@note
 -
 *********************************************************************************************************
 */
 uint32_T SeedToKey_v_g (uint32_T Seed, uint32_T Mask)
{
uint32_T key = 0;
int i;
if (Seed !=0 )
{
for ( i=0; i<35; i++ )
{
if (Seed & 0x80000000)
{
	Seed = Seed <<1;
	Seed = Seed^Mask;
}
else
{
	Seed = Seed << 1;
}
}
key = Seed;
}
return key;
}

#if APP_CODE==1 
/*!******************************************************************************************************
 *	@fn	void DtcInit_v_s(void)
 *	@brief DTC初始化函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
#if UDS_DTC_OPEN==1
void DtcInit_v_s(void)
{

/*-----------------------故障码及状态初始化--------------------*/
   DtcNumb_u24a8_Par[U000187].byte1        = 0xC0;
   DtcNumb_u24a8_Par[U000187].byte2        = 0x01;
   DtcNumb_u24a8_Par[U000187].byte3        = 0x87;
   DtcStatus_u16a8_Par[U000187].Status.Byte  = 0x50;
   
   DtcNumb_u24a8_Par[U000387].byte1        = 0xC0;
   DtcNumb_u24a8_Par[U000387].byte2        = 0x03;
   DtcNumb_u24a8_Par[U000387].byte3        = 0x87;
   DtcStatus_u16a8_Par[U000387].Status.Byte  = 0x50;
   
   DtcNumb_u24a8_Par[U000288].byte1        = 0xC0;
   DtcNumb_u24a8_Par[U000288].byte2        = 0x02;
   DtcNumb_u24a8_Par[U000288].byte3        = 0x88;
  //DtcStatus_u16a8_Par[U000288].Severity=0x00;
   DtcStatus_u16a8_Par[U000288].Status.Byte  = 0x50;
   
   DtcNumb_u24a8_Par[P000112].byte1        = 0x00;
   DtcNumb_u24a8_Par[P000112].byte2        = 0x01;
   DtcNumb_u24a8_Par[P000112].byte3        = 0x12;
   //DtcStatus_u16a8_Par[U000111].Severity=0x00;
   DtcStatus_u16a8_Par[P000112].Status.Byte  = 0x50;
   
   
   DtcNumb_u24a8_Par[P000209].byte1        = 0x00;
   DtcNumb_u24a8_Par[P000209].byte2        = 0x02;
   DtcNumb_u24a8_Par[P000209].byte3        = 0x09;
   //DtcStatus_u16a8_Par[U000212].Severity=0x00;
   DtcStatus_u16a8_Par[P000209].Status.Byte  = 0x50;
   
   
   DtcNumb_u24a8_Par[P000396].byte1        = 0x00;
   DtcNumb_u24a8_Par[P000396].byte2        = 0x03;
   DtcNumb_u24a8_Par[P000396].byte3        = 0x96;
   //DtcStatus_u16a8_Par[U000313].Severity=0x00;
   DtcStatus_u16a8_Par[P000396].Status.Byte  = 0x50;
   
   
   DtcNumb_u24a8_Par[U000487].byte1        = 0xC0;
   DtcNumb_u24a8_Par[U000487].byte2        = 0x04;
   DtcNumb_u24a8_Par[U000487].byte3        = 0x87;
   //DtcStatus_u16a8_Par[U000414].Severity=0x00;
   DtcStatus_u16a8_Par[U000487].Status.Byte  = 0x50;
   
   DtcNumb_u24a8_Par[P000429].byte1        = 0x00;
   DtcNumb_u24a8_Par[P000429].byte2        = 0x04;
   DtcNumb_u24a8_Par[P000429].byte3        = 0x29;
   //DtcStatus_u16a8_Par[U000515].Severity=0x00;
   DtcStatus_u16a8_Par[P000429].Status.Byte  = 0x50;
  
   /*-----------------------故障码Extend数据初始化--------------------*/
  
   DtcExtend_u64a8_Par[U000187].FualtCnt       = 0x00;
   DtcExtend_u64a8_Par[U000187].PendCnt        = 0x00;
   DtcExtend_u64a8_Par[U000187].AgedCnt        = 0x00;
   DtcExtend_u64a8_Par[U000187].AgingCnt=0x00;
   
   DtcExtend_u64a8_Par[U000387].FualtCnt       = 0x00;
   DtcExtend_u64a8_Par[U000387].PendCnt        = 0x00;
   DtcExtend_u64a8_Par[U000387].AgedCnt        = 0x00;
   DtcExtend_u64a8_Par[U000387].AgingCnt=0x00;
   
   DtcExtend_u64a8_Par[U000288].FualtCnt       = 0x00;
   DtcExtend_u64a8_Par[U000288].PendCnt        = 0x00;
   DtcExtend_u64a8_Par[U000288].AgedCnt        = 0x00;
   DtcExtend_u64a8_Par[U000288].AgingCnt=0x00;
   
   DtcExtend_u64a8_Par[P000112].FualtCnt       = 0x00;
   DtcExtend_u64a8_Par[P000112].PendCnt        = 0x00;
   DtcExtend_u64a8_Par[P000112].AgedCnt        = 0x00;
   DtcExtend_u64a8_Par[P000112].AgingCnt=0x00;

   
   
   DtcExtend_u64a8_Par[P000209].FualtCnt        = 0x00;
   DtcExtend_u64a8_Par[P000209].PendCnt         = 0x00;
   DtcExtend_u64a8_Par[P000209].AgedCnt         = 0x00;
   DtcExtend_u64a8_Par[P000209].AgingCnt=0x00;
   
   
   DtcExtend_u64a8_Par[P000396].FualtCnt        = 0x00;
   DtcExtend_u64a8_Par[P000396].PendCnt         = 0x00;
   DtcExtend_u64a8_Par[P000396].AgedCnt         = 0x00;
   DtcExtend_u64a8_Par[P000396].AgingCnt=0x00;
   
   
   DtcExtend_u64a8_Par[U000487].FualtCnt        = 0x00;
   DtcExtend_u64a8_Par[U000487].PendCnt         = 0x00;
   DtcExtend_u64a8_Par[U000487].AgedCnt         = 0x00;
   DtcExtend_u64a8_Par[U000487].AgingCnt=0x00;

   
   DtcExtend_u64a8_Par[P000429].FualtCnt        = 0x00;
   DtcExtend_u64a8_Par[P000429].PendCnt         = 0x00;
   DtcExtend_u64a8_Par[P000429].AgedCnt         = 0x00;
   DtcExtend_u64a8_Par[P000429].AgingCnt        = 0x00;
   /*-----------------------故障码Snapshot数据初始化--------------------*/
   
   DtcSnapShot_u80a8_Par[U000288].SupBatt       =0x00;
   DtcSnapShot_u80a8_Par[U000288].Odreading     =0x00;
   DtcSnapShot_u80a8_Par[U000288].IgStatus      =0x00;
   DtcSnapShot_u80a8_Par[U000288].CoolTemp      =0x00;
   
   DtcSnapShot_u80a8_Par[P000112].SupBatt       =0x00;
   DtcSnapShot_u80a8_Par[P000112].Odreading     =0x00;
   DtcSnapShot_u80a8_Par[P000112].IgStatus      =0x00;
   DtcSnapShot_u80a8_Par[P000112].CoolTemp      =0x00;
   
   
   DtcSnapShot_u80a8_Par[P000209].SupBatt       =0x00;
   DtcSnapShot_u80a8_Par[P000209].Odreading     =0x00;
   DtcSnapShot_u80a8_Par[P000209].IgStatus      =0x00;
   DtcSnapShot_u80a8_Par[P000209].CoolTemp      =0x00;
   
   DtcSnapShot_u80a8_Par[P000396].SupBatt       =0x00;
   DtcSnapShot_u80a8_Par[P000396].Odreading     =0x00;
   DtcSnapShot_u80a8_Par[P000396].IgStatus      =0x00;
   DtcSnapShot_u80a8_Par[P000396].CoolTemp      =0x00;
   
   DtcSnapShot_u80a8_Par[U000487].SupBatt       =0x00;
   DtcSnapShot_u80a8_Par[U000487].Odreading     =0x00;
   DtcSnapShot_u80a8_Par[U000487].IgStatus      =0x00;
   DtcSnapShot_u80a8_Par[U000487].CoolTemp      =0x00;
   
   DtcSnapShot_u80a8_Par[P000429].SupBatt       =0x00;
   DtcSnapShot_u80a8_Par[P000429].Odreading     =0x00;
   DtcSnapShot_u80a8_Par[P000429].IgStatus      =0x00;
   DtcSnapShot_u80a8_Par[P000429].CoolTemp      =0x00;
   

   

}
/*!******************************************************************************************************
 *	@fn	void DtcCycleDef_v_g()
 *	@brief Dtc执行函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void DtcCycleDef_v_g(void)
{
	uint8_T canBuserr;
	uint8_T nXerr;
	uint8_T nParkerr;
	uint8_T nUnParkerr;
	uint8_T overTemperr;
	uint8_T nNoLoaderr;
	uint8_T losPcuerr;
	uint8_T losVcmerr;
#if 0
    losPcuerr = 0;//需要将状态位赋值
    losVcmerr = 0;//需要将状态位赋值
	canBuserr =FltSt1Var.FLTST1.bit.nCAN_Bus_Error ;
	nXerr     = FltSt1Var.FLTST1.bit.nMot_Jam_Middle_Fault ;
	nParkerr  = FltSt1Var.FLTST1.bit.nPark_Stalled_Fault;
	nUnParkerr= FltSt1Var.FLTST1.bit.nUnpark_Stalled_Fault;
	nNoLoaderr = FltSt1Var.FLTST1.bit.nNo_Load_Fault;
	overTemperr =FltStVar.FLTST.bit.nOverTemp_Limit;
	#endif
   if(DtcOnOff_u8_Sig==DTCSETTING_ON)
   {
   	if(losPcuerr==1)
	{
	 DtcDual_v_g(U000387);/*losPcuerr*/
	  //WDtcSnapshot_v_g();//需要将Snapshot对应的参数代入函数中，具体看WDtcSnapshot_v_g函数描述
	}
	if(losVcmerr==1)
	{
	  DtcDual_v_g(U000487);/*losVcmerr*/
	  //WDtcSnapshot_v_g();
	}	
	if(canBuserr==1)
	{
	  DtcDual_v_g(U000288);/*CAN_Bus_Error*/
	  //WDtcSnapshot_v_g();
	}
	if(nXerr==1)
	{
	  DtcDual_v_g(P000112);/*Mot_Jam_Middle_Fault*/
	  //WDtcSnapshot_v_g();
	}
	if(nParkerr==1)
	{
	  DtcDual_v_g(P000209);/*Park_Stalled_Fault*/
	  //WDtcSnapshot_v_g();
	}
	if(nUnParkerr==1)
	{
	 DtcDual_v_g(P000396);/*Unpark_Stalled_Fault*/
	 //WDtcSnapshot_v_g();
	}
	if(nNoLoaderr==1)
	{
	 DtcDual_v_g(U000187);/*No_Load_Fault*/
	 //WDtcSnapshot_v_g();
	}
	if(overTemperr==1)
	{
	DtcDual_v_g(P000429);/*OverTemp_Limit*/
	//WDtcSnapshot_v_g();
	}

    if(canBuserr==1 || nXerr==1||nParkerr==1||nUnParkerr==1\
    ||nNoLoaderr==1||overTemperr==1||losPcuerr==1||losVcmerr==1)
    {
    DtcEep_u8_Sig=1;/*写EEPROM标志位*/
    }
}
else
{
}
}

/*!******************************************************************************************************
 *	@fn	void DtcDual_v_g(uint8_T DtcNumb)
 *	@brief Dtc故障处理
 *	@author Matt Zhang
 *	@param[in]	DtcNumb为DTC的序号
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void DtcDual_v_g(uint8_T DtcNumb)
{
  DtcStatus_u16a8_Par[DtcNumb].Status.Bits.testFailed= 1; /*确认测试失败赋值*/
  DtcStatus_u16a8_Par[DtcNumb].Status.Bits.testFailedThisOperationCycle=1;/*本次工作循环周期测试失败赋值*/
  DtcStatus_u16a8_Par[DtcNumb].Status.Bits.testFailedSinceLastClear= 1;/*从上次清除开始测试失败赋值*/
  DtcStatus_u16a8_Par[DtcNumb].Status.Bits.pendingDTC= 1;/*未确认失败赋值*/
  DtcStatus_u16a8_Par[DtcNumb].Status.Bits.confirmedDTC=1;/*确认赋值*/
}
/*!******************************************************************************************************
 *	@fn	void DtcBackFlashInit_v_g (void)
 *	@brief读取EEPROM后DTC处理函数
 *	@author Matt Zhang
 *	@param[in]	viod
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void DtcBackFlashInit_v_g (void)
{
/*--记录上一次的DTC状态--*/
LastDtcStatus_u16a8_Par[U000187].Status.Byte = DtcStatus_u16a8_Par[U000187].Status.Byte;
LastDtcStatus_u16a8_Par[U000387].Status.Byte = DtcStatus_u16a8_Par[U000387].Status.Byte;
LastDtcStatus_u16a8_Par[U000288].Status.Byte = DtcStatus_u16a8_Par[U000288].Status.Byte;
LastDtcStatus_u16a8_Par[P000112].Status.Byte = DtcStatus_u16a8_Par[P000112].Status.Byte;
LastDtcStatus_u16a8_Par[P000209].Status.Byte = DtcStatus_u16a8_Par[P000209].Status.Byte;
LastDtcStatus_u16a8_Par[P000396].Status.Byte = DtcStatus_u16a8_Par[P000396].Status.Byte;
LastDtcStatus_u16a8_Par[U000487].Status.Byte = DtcStatus_u16a8_Par[U000487].Status.Byte;
LastDtcStatus_u16a8_Par[P000429].Status.Byte = DtcStatus_u16a8_Par[P000429].Status.Byte;
/*--读取EEPROM后所要的初始化--*/
DtcStatus_u16a8_Par[U000187].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[U000187].Status.Bits.testNotCompletedThisOperationCycle = 1;

DtcStatus_u16a8_Par[U000387].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[U000387].Status.Bits.testNotCompletedThisOperationCycle = 1;

DtcStatus_u16a8_Par[U000288].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[U000288].Status.Bits.testNotCompletedThisOperationCycle = 1;

DtcStatus_u16a8_Par[P000112].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[P000112].Status.Bits.testNotCompletedThisOperationCycle = 1;

DtcStatus_u16a8_Par[P000209].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[P000209].Status.Bits.testNotCompletedThisOperationCycle = 1;

DtcStatus_u16a8_Par[P000396].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[P000396].Status.Bits.testNotCompletedThisOperationCycle = 1;

DtcStatus_u16a8_Par[U000487].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[U000487].Status.Bits.testNotCompletedThisOperationCycle = 1;

DtcStatus_u16a8_Par[P000429].Status.Bits.testFailedThisOperationCycle  = 0;
DtcStatus_u16a8_Par[P000429].Status.Bits.testNotCompletedThisOperationCycle = 1;



}

/*!******************************************************************************************************
 *	@fn	void ClearSignelDtc_v_g(uint8_T DtcNumb)
 *	@brief单个清除故障码处理函数
 *	@author Matt Zhang
 *	@param[in]	DtcNumb为DTC的序号
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void ClearSignelDtc_v_g(uint8_T DtcNumb)
{
	 DtcStatus_u16a8_Par[DtcNumb].Status.Byte  = 0x00;/*状态置0*/
	 DtcExtend_u64a8_Par[DtcNumb].FualtCnt = 0; /*未确认计数清0*/
     DtcExtend_u64a8_Par[DtcNumb].PendCnt  = 0;/*未确认计数清0*/
     LastDtcStatus_u16a8_Par[DtcNumb].Status.Byte = DtcStatus_u16a8_Par[DtcNumb].Status.Byte;
     DtcSnapShot_u80a8_Par[DtcNumb].SupBatt       =0x00;/*Snapshot数据清0*/
     DtcSnapShot_u80a8_Par[DtcNumb].Odreading     =0x00;/*Snapshot数据清0*/
     DtcSnapShot_u80a8_Par[DtcNumb].IgStatus      =0x00;/*Snapshot数据清0*/
     DtcSnapShot_u80a8_Par[DtcNumb].CoolTemp      =0x00;/*Snapshot数据清0*/

}
/*!******************************************************************************************************
 *	@fn	void WDtcSnapshot_v_g(uint8_T DtcNumb,uint8_T SupBatt,uint32_T Odreading,uint8_T CoolTemp,uint8_T Igstatus )
 *	@brief SnapShot处理函数
 *	@author Matt Zhang
 *	@param[in]	DtcNumb为DTC的序号，SupBatt供电电压，Odreading公里数，CoolTemp为温度，Igstatus为Ig的状态
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void WDtcSnapshot_v_g(uint8_T DtcNumb,uint8_T SupBatt,uint32_T Odreading,uint8_T CoolTemp,uint8_T Igstatus )
{
	 DtcSnapShot_u80a8_Par[DtcNumb].SupBatt       =SupBatt;/*电压赋值*/
     DtcSnapShot_u80a8_Par[DtcNumb].Odreading     =Odreading;/*里程赋值*/
     DtcSnapShot_u80a8_Par[DtcNumb].IgStatus      =CoolTemp;/*温度赋值*/
     DtcSnapShot_u80a8_Par[DtcNumb].CoolTemp      =Igstatus;/*Ig赋值*/

}


/*!******************************************************************************************************
 *	@fn	void  DTCExtendDual_v_g (void)
 *	@brief Extend数据处理函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void  DTCExtendDual_v_g (void)
{
  uint8_T i;

  for(i = 0; i <DTCNUM; i++){
    if (DtcStatus_u16a8_Par[i].Status.Bits.testFailedThisOperationCycle == 0){/*判断当前周期是否测试失败*/
      DtcExtend_u64a8_Par[i].AgingCnt = DtcExtend_u64a8_Par[i].AgingCnt + 1;  /*年龄次数加1*/
      
        if(DtcExtend_u64a8_Par[i].AgingCnt>= 40){/*年龄次是否大于40*/
          DtcExtend_u64a8_Par[i].AgedCnt = DtcExtend_u64a8_Par[i].AgedCnt + 1;/*老化年龄加1*/
          if(DtcExtend_u64a8_Par[i].AgedCnt==256)/*老化年龄是否为256*/
          {
          	 DtcExtend_u64a8_Par[i].AgedCnt=0;/*老化年龄清0*/
          }
          /*--- 当Aged Counter不为0时清除DTC信息 --- */
          ClearSignelDtc_v_g(i);
          DtcExtend_u64a8_Par[i].AgingCnt = 0;   
        } 
        if(LastDtcStatus_u16a8_Par[i].Status.Bits.pendingDTC==1)/*判断未确认状态是否为1*/
        {
         
          if(DtcExtend_u64a8_Par[i].PendCnt<255)/*判断计数是否小于255*/
          {
          	  DtcExtend_u64a8_Par[i].PendCnt++; /*计数加1*/
          }
        }
        else
        {
          DtcStatus_u16a8_Par[i].Status.Bits.pendingDTC=0; /*计数清0*/
        }
        
    }   
    else
    {
         DtcExtend_u64a8_Par[i].AgingCnt=0;/*年龄次数清0*/
         if(DtcExtend_u64a8_Par[i].PendCnt<255)/*判断计数是否小于255*/
          {
                   	  DtcExtend_u64a8_Par[i].PendCnt++; /*计数加1*/
         }
         
         if(DtcExtend_u64a8_Par[i].FualtCnt<255)/*判断计数是否小于255*/
         {
          DtcExtend_u64a8_Par[i].FualtCnt++;/*计数加1*/
         }
    }
    /* --- 以下两个bit不写EEPROM，所以改为0 --- */
    DtcStatus_u16a8_Par[i].Status.Bits.testFailedThisOperationCycle = 0;
    DtcStatus_u16a8_Par[i].Status.Bits.testNotCompletedThisOperationCycle = 0;
  }
    
}

/*!******************************************************************************************************
 *	@fn	void ClearDtc_v_g(void)
 *	@brief 清除所有故障码函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void ClearDtc_v_g(void)
{
/*--------------清除所有故障码-----------*/
ClearSignelDtc_v_g(U000187);
ClearSignelDtc_v_g(U000387);
ClearSignelDtc_v_g(U000288);
ClearSignelDtc_v_g(P000112);
ClearSignelDtc_v_g(P000209);
ClearSignelDtc_v_g(P000396);
ClearSignelDtc_v_g(U000487);
ClearSignelDtc_v_g(P000429);
}
#endif
#endif
/*!******************************************************************************************************
 *	@fn	void ReadData_v_g(void)
 *	@brief 读取EEPROM函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
// void ReadData_v_g(void)
// {
//     EEPROM_Read((uint16_T*)&BootEepFlag_u16_Par,(uint16_T*)(ERASE_BASE+408),1);
// 	EEPROM_Read((uint16_T*)&AppEepFlag_u16_Par,(uint16_T*)(ERASE_BASE+409),1);
//     if(BootEepFlag_u16_Par==1 || AppEepFlag_u16_Par==1)
//     {
// 	EEPROM_Read((uint16_T*)BootSwRefNumb_u16a10_Par,(uint16_T*)(ERASE_BASE),10);
// 	EEPROM_Read((uint16_T*)PifPtcb_u16a16a16_Par,(uint16_T*)(ERASE_BASE+10),256);
// 	EEPROM_Read((uint16_T*)ECUPartNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+266),6);
// 	EEPROM_Read((uint16_T*)SysSupplierId_u16a6_Par,(uint16_T*)(ERASE_BASE+272),6);
// 	EEPROM_Read((uint16_T*)EcuHwNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+278),6);
// 	EEPROM_Read((uint16_T*)EcuHwRefNumb_u16a10_Par,(uint16_T*)(ERASE_BASE+284),10);
// 	EEPROM_Read((uint16_T*)EcuSwRefNumb_u16a10_Par,(uint16_T*)(ERASE_BASE+294),10);
// #if APP_CODE==0
// 	EEPROM_Read((uint16_T*)EcuAppSwNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+304),6);
// 	EEPROM_Read((uint16_T*)EcuCalSwNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+310),6);
// 	EEPROM_Read((uint16_T*)EcuNetRefNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+316),6);
// #endif
// 	EEPROM_Read((uint16_T*)VehFeature_u16a20_Par,(uint16_T*)(ERASE_BASE+322),20);
// 	EEPROM_Read((uint16_T*)EcuSupplierSN_u16a10_Par,(uint16_T*)(ERASE_BASE+342),10);
// 	EEPROM_Read((uint16_T*)EcuMData_u16a3_Par,(uint16_T*)(ERASE_BASE+352),3);
// 	EEPROM_Read((uint16_T*)Vin_u16a17_Par,(uint16_T*)(ERASE_BASE+355),17);
// 	EEPROM_Read((uint16_T*)&PifBlockNumb_u16_Sig,(uint16_T*)(ERASE_BASE+372),1);
//     }
//    if(BootEepFlag_u16_Par==1)
//    {
// 	EEPROM_Read((uint16_T*)&SVF_u16_Par,(uint16_T*)(ERASE_BASE+373),1);
// 	EEPROM_Read((uint16_T*)&BootTimes_u16_Par,(uint16_T*)(ERASE_BASE+374),1);
// 	EEPROM_Read((uint16_T*)&SIS_u16_Sig,(uint16_T*)(ERASE_BASE+375),1);
// 	EEPROM_Read((uint16_T*)&SCS_u16_Sig,(uint16_T*)(ERASE_BASE+376),1);
// 	EEPROM_Read((uint16_T*)&WrCheckSum_u16_Sig,(uint16_T*)(ERASE_BASE+410),1);

//    }

// 	if(AppEepFlag_u16_Par==1)
// 	{
//     EEPROM_Read((uint16_T*)&PEF_u16_Par,(uint16_T*)(ERASE_BASE+412),1);
//     /*下面DTC三部分有自定义的可以自己定义变量和写EEPROM地址，确保不和上面地址及Flash地址冲突就可以*/
// #if UDS_DTC_OPEN==1
// 	EEPROM_Read((uint16_T*)DtcStatus_u16a8_Par,(uint16_T*)(ERASE_BASE+378),8);
// 	EEPROM_Read((uint16_T*)DtcExtend_u64a8_Par,(uint16_T*)(ERASE_BASE+380),32);
// 	EEPROM_Read((uint16_T*)DtcSnapShot_u80a8_Par,(uint16_T*)(ERASE_BASE+413),40);
// #endif
// 	}
	
		
// }
/*!******************************************************************************************************
 *	@fn	void ReadData_v_g(void)
 *	@brief 写EEPROM函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
// void SaveData_v_g(void)
// {
// /*-------------------dtc Eep--------------------------*/
// uint16_T Status;
// static uint8_T cnt=0;
// static uint8_T cnteep=0;
// #if APP_CODE==0
// if(SvfEep_u8_Sig==1|| DidEep_u8_Sig==1 || (PefEep_u8_Sig==1 && SessionMode_u8_Sig==DEFAULT_SESSION))
// {
// cnt++;	
// }
// #endif
// #if APP_CODE==0
// if((SvfEep_u8_Sig==1 || DidEep_u8_Sig==1 || PefEep_u8_Sig==1) && cnt==4)
// {
// BootEepFlag_u16_Par=1;
// if(SvfEep_u8_Sig==1 && SVF_u16_Par==1)/*判断写Flash是否成功及完整性标志置位*/
// {
// 	SIS_u16_Sig=SIS_u16_Sig&0xFE;/*完整性置位*/
//     SCS_u16_Sig=SIS_u16_Sig&0xFE;/*兼容性置位*/
// 	SVF_u16_Par=1;
//     if(BootTimes_u16_Par <65535)
// 	{
//     	 BootTimes_u16_Par++;/*刷写次数加1*/
// 	}
// }

// #else
// //if(g_CANDataVar.nParkLock_St_dCAN==1)
// //{
// //EepRomTimes_u8_Sig=0;
// //}
// if(PEF_u16_Par==1)
// {
// 	cnt++;
// }
// //ljh 20160225
// if(EepRomTimes_u8_Sig==0 && g_AdcCalVar.nV_Ign_ConF <= 55)
// {
// 	cnteep++;
// }
// if(g_AdcCalVar.nV_Ign_ConF > 55)	cnteep=0;
// /*if((g_CANDataVar.nEngine_RMP_dCAN<200 && EepRomTimes_u8_Sig==0\
// 		&& g_CANDataVar.nParkLock_St_dCAN==2 && cnteep==200 ) || (g_CANDataVar.nEngine_RMP_dCAN<200&&PEF_u16_Par==1 && cnt==2))*/		//ljh 20160225
// if((g_AdcCalVar.nV_Ign_ConF <= 55 && cnteep==20 && EepRomTimes_u8_Sig==0 )||(PEF_u16_Par==1 && cnt==2))
// {
// cnteep=0;
// AppEepFlag_u16_Par=1;/*App 写EEPROM标志位赋值*/
// if(DtcOnOff_u8_Sig==DTCSETTING_ON)
// {
// DTCExtendDual_v_g();/*extend 数据处理*/
// }
// #endif
// cnt=0;
// DINT;
// Status=EEPROM_Erase(SECTORC);/*擦除EEPROM*/
// EEPROM_Write((uint16_T*)&BootEepFlag_u16_Par,(uint16_T*)(ERASE_BASE+408),1);
// EEPROM_Write((uint16_T*)&AppEepFlag_u16_Par,(uint16_T*)(ERASE_BASE+409),1);
// EEPROM_Write((uint16_T*)&WrCheckSum_u16_Sig,(uint16_T*)(ERASE_BASE+410),1);
// EEPROM_Write((uint16_T*)BootSwRefNumb_u16a10_Par,(uint16_T*)(ERASE_BASE),10);
// EEPROM_Write((uint16_T*)PifPtcb_u16a16a16_Par,(uint16_T*)(ERASE_BASE+10),256);
// EEPROM_Write((uint16_T*)ECUPartNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+266),6);
// EEPROM_Write((uint16_T*)SysSupplierId_u16a6_Par,(uint16_T*)(ERASE_BASE+272),6);
// EEPROM_Write((uint16_T*)EcuHwNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+278),6);
// EEPROM_Write((uint16_T*)EcuHwRefNumb_u16a10_Par,(uint16_T*)(ERASE_BASE+284),10);
// EEPROM_Write((uint16_T*)EcuSwRefNumb_u16a10_Par,(uint16_T*)(ERASE_BASE+294),10);
// EEPROM_Write((uint16_T*)EcuAppSwNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+304),6);
// EEPROM_Write((uint16_T*)EcuCalSwNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+310),6);
// EEPROM_Write((uint16_T*)EcuNetRefNumb_u16a6_Par,(uint16_T*)(ERASE_BASE+316),6);
// EEPROM_Write((uint16_T*)VehFeature_u16a20_Par,(uint16_T*)(ERASE_BASE+322),20);
// EEPROM_Write((uint16_T*)EcuSupplierSN_u16a10_Par,(uint16_T*)(ERASE_BASE+342),10);
// EEPROM_Write((uint16_T*)EcuMData_u16a3_Par,(uint16_T*)(ERASE_BASE+352),3);
// EEPROM_Write((uint16_T*)Vin_u16a17_Par,(uint16_T*)(ERASE_BASE+355),17);
// EEPROM_Write((uint16_T*)&PifBlockNumb_u16_Sig,(uint16_T*)(ERASE_BASE+372),1);
// EEPROM_Write((uint16_T*)&SVF_u16_Par,(uint16_T*)(ERASE_BASE+373),1);
// EEPROM_Write((uint16_T*)&BootTimes_u16_Par,(uint16_T*)(ERASE_BASE+374),1);
// EEPROM_Write((uint16_T*)&SIS_u16_Sig,(uint16_T*)(ERASE_BASE+375),1);
// EEPROM_Write((uint16_T*)&SCS_u16_Sig,(uint16_T*)(ERASE_BASE+376),1);
// EEPROM_Write((uint16_T*)&PEF_u16_Par,(uint16_T*)(ERASE_BASE+412),1);
// /*下面DTC三部分有自定义的可以自己定义变量和写EEPROM地址，确保不和上面地址及Flash地址冲突就则可以*/
// #if UDS_DTC_OPEN==1
// EEPROM_Write((uint16_T*)DtcStatus_u16a8_Par,(uint16_T*)(ERASE_BASE+378),8);
// EEPROM_Write((uint16_T*)DtcExtend_u64a8_Par,(uint16_T*)(ERASE_BASE+380),32);
// EEPROM_Write((uint16_T*)DtcSnapShot_u80a8_Par,(uint16_T*)(ERASE_BASE+413),40);
// #endif
// #if APP_CODE==1
// Progam_v_s();/*reset*/
// #endif
// if(SvfEep_u8_Sig==1 && SVF_u16_Par==1)/*判断程序完整性且写EEPROM标志位是否为1*/
// {
// 	RspFmt_u8_Sig =POS_RSP;/*回应类型赋值*/
// 	if(BackUpExit_u8_Sig==1)
// 	{

// 		/*--------------------------回应数据赋值----------------------*/
// 	  Rsp_Msg.ReqSendMsg_u8_Tmp [1]=BackUpExit_u8_Sig;
// 	  Rsp_Msg.ReqSendMsg_u8_Tmp [2]=(uint8_T)(crcData_u32_Sig>>24);
// 	  Rsp_Msg.ReqSendMsg_u8_Tmp [3]=(uint8_T)(crcData_u32_Sig>>16);
// 	  Rsp_Msg.ReqSendMsg_u8_Tmp [4]=(uint8_T)(crcData_u32_Sig>>8);
// 	  Rsp_Msg.ReqSendMsg_u8_Tmp [5]=(uint8_T)(crcData_u32_Sig);
// 	  RspMsgLen_u16_Sig = 5;/*长度赋值*/
// 	}
// 	else
// 	{

// 	/*--------------------------回应数据赋值----------------------*/
// 		Rsp_Msg.ReqSendMsg_u8_Tmp [1]=BackUpExit_u8_Sig;
// 		RspMsgLen_u16_Sig = 1;
// 	}
// 	if(!ResponseMechanism_v_s())
// 	{
// 		  AppSendRspMsg();/*请求网络层发送数据*/
// 	}

// }
// if(DidEep_u8_Sig==1)/*判断DID写EEPROM标志位*/
// {
// /*--------------------------回应数据赋值----------------------*/
// Rsp_Msg.ReqSendMsg_u8_Tmp [1]=WrDidBackUp_Sig[0];
// Rsp_Msg.ReqSendMsg_u8_Tmp [2]=WrDidBackUp_Sig[1];	
// RspFmt_u8_Sig =POS_RSP;/*回应类型赋值*/
// RspMsgLen_u16_Sig = 2;/*长度赋值*/
// if(!ResponseMechanism_v_s())
// {
// 	  AppSendRspMsg();/*请求网络层发送数据*/
// }
// }
// SvfEep_u8_Sig=0;
// DidEep_u8_Sig=0;
// PefEep_u8_Sig=0;

// if(g_AdcCalVar.nV_Ign_ConF <= 55){
// 	EepRomTimes_u8_Sig=1;
// 	}
// delay_ms(9.0L);			//20160310  ljh
// EINT;
// }
// }
#if APP_CODE==0

/*!******************************************************************************************************
 *	@fn	uint16_T PFlash_Check(uint32_T StartAddr, uint16_T Len, uint16_T LastValue)
 *	@brief 写EEPROM函数
 *	@author Matt Zhang
 *	@param[in]	StartAddr起始地址，Len需要校验的长度，LastValue校验和变量
 *	@return	uint16_T校验和
 *	@note
 -
 *********************************************************************************************************
 */

uint16_T PFlash_Check(uint32_T StartAddr, uint16_T Len, uint16_T LastValue)
{
	 uint32_T start = StartAddr;
	 uint32_T len   = Len;
	 uint16_T checksum = LastValue;
	 uint16_T cnt;

	 for( cnt=0;cnt<len;cnt++)
	 {
	 checksum += *((uint16_T far*)(start+cnt));/*从起始地址取设定长度的数据累加*/
	 }

	 return checksum;/*返回校验和*/

}


/*!******************************************************************************************************
*	@fn void CommunicationControl_v_g(UDSBYTEPTR SubFun)
*	@brief 控制发送和接受通信(非诊断通信)
*	@param[in]	SubFun
*	@return	void
*	@note
*		-
*********************************************************************************************************
*/
uint16_T CheckAppCode_v_g(void)
{

	  uint16_T checksum = 0;
	  DINT;
	  checksum = PFlash_Check(0x3EC000, 0x6000, checksum);/*设定好算取F区的校验和*/

	  checksum = PFlash_Check(0x3F4000, 0x2000, checksum);/*F区和B区累加校验和*/

      EINT;
	  return checksum;/*返回校验值*/
}

/*!******************************************************************************************************
 *	@fn	void WriteFlashDual(void)
 *	@brief 写Flash处理函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void WriteFlashDual(void)
{
    uint16_T Status;
    static uint8_T cnt=0;
    if(WFlashFlag_u8_Sig==1)/*判断写Flash标志位是否为1*/
    {
	cnt++;/*计数器加1*/
    }
	if(WFlashFlag_u8_Sig==1 && cnt==4)/*判断Flash和计数值是否达到设定值*/
	{
		cnt=0;
		DINT;/*关中断*/
		Status =Boot(WFlashAdr_u32_Sig, FlashWBuffer_u16_Sig, BootWFalshLen_u16_Sig);/*写Flash*/
		if(EndHex_u8_Sig==1)/*判断是否最后一条请求*/
		{
		WrCheckSum_u16_Sig = CheckAppCode_v_g();/*计算校验和*/
		}
		EINT;
        WFlashAdr_u32_Sig= WFlashAdr_u32_Sig+BootWFalshLen_u16_Sig;/*写Flash长度累加*/
        if(Status!=noErr)/*判断写Flash状态是否正确*/
        {
          RspFmt_u8_Sig=NEG_RSP;
          NegRsp_u8_Sig=ERWRMEN_ERR;  /*写Flash错误*/
        }
        else
        {
          RspFmt_u8_Sig =POS_RSP;/*回应类型赋值*/
          Rsp_Msg.ReqSendMsg_u8_Tmp [1] =TranBlock_u8_Sig;	
        }
		WFlashFlag_u8_Sig = 0;/*写Flash标志位清0*/
		 
	    if(RspFmt_u8_Sig==NEG_RSP)
        {
 	     RspMsgLen_u16_Sig = 2;
        }	
        else
        {
  	     RspMsgLen_u16_Sig = 1;
        }
        if(!ResponseMechanism_v_s())
	    {
	     AppSendRspMsg();
	    }
  
	}

}
/*!******************************************************************************************************
 *	@fn	void EraseFlashDual(void)
 *	@brief 擦除Flash处理函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void EraseFlashDual(void)
{
    uint16_T Status;
    static uint8_T cnt=0;
    if(EFlashFlag_u8_Sig==1)/*判断擦Flash标志位是否为1*/
    {
    	cnt++;
    }
    
	if(EFlashFlag_u8_Sig==1 && cnt==4)/*判断擦Flash标志位及计数值*/
	{
		
		cnt=0;
		DINT;
		Status = EraseSector_v_s(EraseSector_u8_Sig);/*擦除flash*/
		EINT;
        if(Status!=noErr)/*判断擦Flash状态是否正确*/
        {
          RspFmt_u8_Sig=NEG_RSP;
          NegRsp_u8_Sig=ERWRMEN_ERR;  /*擦flash错误*/
        }
        else
        {
       /*----------------正面回应赋值---------------*/
        Rsp_Msg.ReqSendMsg_u8_Tmp [1]=BackSub_u8_Sig;
        Rsp_Msg.ReqSendMsg_u8_Tmp [2]=EraseDid_u8_Sig[0];
   		Rsp_Msg.ReqSendMsg_u8_Tmp [3]=EraseDid_u8_Sig[1];	
   		RspFmt_u8_Sig =POS_RSP;
   		RspMsgLen_u16_Sig = 3;
        }
		EFlashFlag_u8_Sig = 0;/*清除擦Flash标志位*/
		
	    if(RspFmt_u8_Sig==NEG_RSP)
        {
 	     RspMsgLen_u16_Sig = 2;
        }
        
        if(!ResponseMechanism_v_s())
	    {
	     AppSendRspMsg();
	    }
	}

}
/*!******************************************************************************************************
 *	@fn	uint16_T EraseSector_v_s(uint16_T sector)
 *	@brief 擦除Flash函数
 *	@author Matt Zhang
 *	@param[in]	sector擦除的扇区
 *	@return	uint16_T擦除状态值
 *	@note
 -
 *********************************************************************************************************
 */
uint16_T EraseSector_v_s(uint16_T sector)
{
	uint16_T Status;
	switch(sector)
	{
		case A_Sector:
		//Status=AppFlash_Erase(SECTORA); /*擦除A区*/
		break;
		case B_Sector:
		//Status=AppFlash_Erase(SECTORB);/*擦除B区*/
		break;
		case AB_Sector:
		//Status=AppFlash_Erase(SECTORB);/*擦除B区*/
		break;
		case F_Sector:
		//Status=AppFlash_Erase(SECTORF)|AppFlash_Erase(SECTORE)|AppFlash_Erase(SECTORD)|AppFlash_Erase(SECTORB);/*擦除F、E、D、B区*/
		break;
	}
	
	return Status;
}

#endif
/*!******************************************************************************************************
 *	@fn	void ReadMemDual(void)
 *	@brief 读取内存地址数据处理函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void ReadMemDual(void)
{
uint16_T Index=0;
static uint8_T cnt=0;
if( RMemDataFLag_u8_Sig ==1)/*判断地址读数据标志位是否为1*/
{
	cnt++;
}
	if( RMemDataFLag_u8_Sig ==1 && cnt==4)/*判断地址读数据标志位是否为1且计数值达到*/
	{
		cnt=0;
		DINT;
		/*---------------------读取数据-----------------------*/
        //EEPROM_Read((uint16_T*)MemData_u16_Sig,(uint16_T*)MemAdr_u32_Sig,MemDataLen_u16_Sig);
        EINT;
      
        RspFmt_u8_Sig =POS_RSP;
        /*---------------------读取的数据赋值给回应数组-----------------------*/
        for(Index=0;Index<MemDataLen_u16_Sig;Index++)
        {
          	//Rsp_Msg.ReqSendMsg_u8_Tmp [1+(Index<<1)] =(uint8_T)(MemData_u16_Sig[Index]>>8);
          	//Rsp_Msg.ReqSendMsg_u8_Tmp [2+(Index<<1)] =(uint8_T)(MemData_u16_Sig[Index]&0xFF);

			//Set_Byte();
        }
		RMemDataFLag_u8_Sig = 0;
	    if(RspFmt_u8_Sig==NEG_RSP)
        {
 	     RspMsgLen_u16_Sig = 2;
        }	
        else
        {
  	     RspMsgLen_u16_Sig = MemDataLen_u16_Sig<<1;
        }
        if(!ResponseMechanism_v_s())
	    {
	     AppSendRspMsg();
	    }
  
	}

}
/*!******************************************************************************************************
 *	@fn	void WriteMemDual(void)
 *	@brief 写内存地址数据处理函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void WriteMemDual(void)
{

uint16_T Status;
uint16_T Index=0;
static uint8_T cnt=0;
if( WMemDataFLag_u8_Sig ==1)/*判断地址写数据标志位是否为1*/
{
	cnt++;
}
	if( WMemDataFLag_u8_Sig ==1 && cnt==4)/*判断地址写数据标志位是否为1且计数值达到*/
	{
		cnt=0;
		DINT;
        //Status=EEPROM_Erase(SECTORC);/*擦除EEPROm*/
       
        if(Status!=noErr)/*判断擦除EEPROm是否正确*/
        {
          RspFmt_u8_Sig=NEG_RSP;
          NegRsp_u8_Sig=ERWRMEN_ERR;
        }
        else
        {

        /*--------------------通过地址写EEPROM---------------------*/
          //Status=EEPROM_Write((uint16_T*)MemData_u16_Sig,(uint16_T*)MemAdr_u32_Sig,MemDataLen_u16_Sig);
        }
        EINT;
        if(Status!=noErr)/*判断写EEPROm是否正确*/
        {
          RspFmt_u8_Sig=NEG_RSP;
          NegRsp_u8_Sig=ERWRMEN_ERR;  /*长度不对错误码0x13*/  
        }
        else
        {
          RspFmt_u8_Sig =POS_RSP;
          //Rsp_Msg.ReqSendMsg_u8_Tmp [1] =adrLenFmtId_u8_Sig;
		  Set_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[0], MSB, adrLenFmtId_u8_Sig);
          //for(Index=1;Index<BackUpPosLen_u16_Sig;Index++)
          //{
          //	Rsp_Msg.ReqSendMsg_u8_Tmp [1+Index] =BackUpMemInfor_u8_Sig[Index-1];
          //}
		  CopyMemory_WithNone_Byte(&Rsp_Msg.ReqSendMsg_u8_Tmp[1], &BackUpMemInfor_u8_Sig, LSB, LSB, (BackUpPosLen_u16_Sig -1));
        }
		WMemDataFLag_u8_Sig = 0;
	    if(RspFmt_u8_Sig==NEG_RSP)
        {
 	     RspMsgLen_u16_Sig = 2;
        }	
        else
        {
  	     RspMsgLen_u16_Sig = BackUpPosLen_u16_Sig;
        }
        if(!ResponseMechanism_v_s())
	    {
	     AppSendRspMsg();
	    }
  
	}

}
/*!******************************************************************************************************
 *	@fn	void SwReset_v_g(void)
 *	@brief SwREset处理函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void SwReset_v_g(void)
{
	static uint8_T cnt =0;
	if(ResetMode_u8_Sig==SW_RESET ||  ResetMode_u8_Sig == HARD_RESET)/*判断Reset类型是否为Sw或Hw*/
	{
		 cnt++;
	}
	/*判断Reset类型是否为Sw或Hw且计数值判断*/
    if(ResetMode_u8_Sig == HARD_RESET && cnt ==4)
	{
		cnt=0;
	    DINT;
		IER = 0x0000;
		IFR = 0x0000;
		(*ECU_SWRESET)();//Reset
	}
	else if(ResetMode_u8_Sig == SW_RESET && cnt ==4)
	{   
		cnt=0;
	    DINT;
		IER = 0x0000;
		IFR = 0x0000;
		while(1)
		{};
	}
}

#if APP_CODE==1
/*!******************************************************************************************************
 *	@fn	void SwReset_v_g(void)
 *	@brief Boot_SwREset处理函数
 *	@author Matt Zhang
 *	@param[in]	void
 *	@return	void
 *	@note
 -
 *********************************************************************************************************
 */
void Progam_v_s(void)
{

    if(PEF_u16_Par==1 )/*判断APPtoBoot标志位是否为1*/
	{
		DINT;
		IER = 0x0000;
		IFR = 0x0000;
		(*ECU_SWRESET)();// Reset

	}
}
#endif
