					 /*!******************************************************************************************************
*	@file 	eee.h
*	@brief 	eee.cÍ·ÎÄ¼þ
*	@author Colin Lee
*	@version 1.0
*	@date  2010-8-10
*	@warning  
*                (c) Copyright 2010, Vast Automotive Technology(Shanghai) Co., Ltd.
*                                       All Rights Reserved
*	@note
*********************************************************************************************************
*/

#ifndef  NL_H
#define  NL_H

#ifdef   NL_GLOBALS
	#define  NL_EXT
#else
	#define  NL_EXT  extern
#endif

/*
*********************************************************************************************************
*                                            VARIABLES  PROCESSOR SPECIFICS
*********************************************************************************************************
*/
#define	MaxBufferSize	255
#define SingleFrame	0
#define FirstFrame	1
#define ConsecutiveFrame	2
#define FlowControl	3

#define ContinuedToSend	0 
#define Wait	1 
#define OverFlow	2 
        
#define FUNCTIONAL_ID	0x7DF 
#define PHYSICAL_ID     0x703
                  
extern unsigned char RequestCmd_u8_Sig;
extern unsigned char IndicationCmd_u8_Sig;
extern unsigned char ConfirmCmd_u8_Sig;
extern uint16_T  RXbuffer_u8a8_Sig[4];
extern unsigned char RecFlag_u8_Sig;
extern unsigned long RecID_u8_Sig;
/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/
extern unsigned char UdsSend(unsigned char length,unsigned char* buffer);
#endif                                                                  /* End of file                                              */

