/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : AtAdsInterface.h
  版 本 号   : 初稿
  生成日期   : 2011年12月6日
  最近修改   :
  功能描述   : AT和ADS之间的接口
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月6日
    修改内容   : 创建文件

******************************************************************************/

#ifndef __ATADSINTERFACE_H__
#define __ATADSINTERFACE_H__

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
枚举名    : AT_ADS_MSG_ID_ENUM
枚举说明  : AT与ADS之间的消息

  1.日    期   : 2011年12月6日
    修改内容   : 定义AT与ADS之间的消息ID
*****************************************************************************/
enum AT_ADS_MSG_ID_ENUM
{
    ID_AT_ADS_PDP_STATUS_IND,                                                   /* PDP状态消息*/
    ID_AT_ADS_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32  AT_ADS_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : AT_ADS_PDP_STATUS_ENUM
 枚举说明  : AT发给ADS的PDP激活与去激活指示

  1.日    期   : 2011年12月6日
    修改内容   : 定义PDP的状态
  2.日    期   : 2012年2月17日
    修改内容   : V7R1C50项目，新增PDP修改成功的枚举
*****************************************************************************/
enum AT_ADS_PDP_STATUS_ENUM
{
    AT_ADS_PDP_STATUS_ACT,                                                      /* PDP激活成功 */
    AT_ADS_PDP_STATUS_MODIFY,                                                   /* PDP修改成功 */
    AT_ADS_PDP_STATUS_DEACT,                                                    /* PDP去激活成功 */
    AT_ADS_PDP_STATUS_BUTT
};
typedef VOS_UINT8 AT_PDP_STATUS_ENUM_UINT8;

/*****************************************************************************
枚举名    : AT_ADS_QCI_TYPE_ENUM
枚举说明  : AT向ADS发送PDP状态指示时所使用的QCI枚举

  1.日    期   : 2012年2月23日
    修改内容   : V7R1C50 IPC项目新增
*****************************************************************************/
typedef enum
{
    AT_ADS_QCI_TYPE_QCI1_GBR           = 0,
    AT_ADS_QCI_TYPE_QCI2_GBR           = 1,
    AT_ADS_QCI_TYPE_QCI3_GBR           = 2,
    AT_ADS_QCI_TYPE_QCI4_GBR           = 3,
    AT_ADS_QCI_TYPE_QCI5_NONGBR        = 4,
    AT_ADS_QCI_TYPE_QCI6_NONGBR        = 5,
    AT_ADS_QCI_TYPE_QCI7_NONGBR        = 6,
    AT_ADS_QCI_TYPE_QCI8_NONGBR        = 7,
    AT_ADS_QCI_TYPE_QCI9_NONGBR        = 8,

    AT_ADS_QCI_TYPE_BUTT
}AT_ADS_QCI_TYPE_ENUM;

typedef VOS_UINT8 AT_ADS_QCI_TYPE_ENUM_UINT8;


/*****************************************************************************
 结构名称: AT_ADS_PDP_TYPE_ENUM
 结构说明: PDP类型
 1.日    期   : 2013年05月22日
   修改内容   : 创建文件
*****************************************************************************/
typedef enum
{
    AT_ADS_PDP_IPV4                        = 0x01,                              /* IPV4类型 */
    AT_ADS_PDP_IPV6                        = 0x02,                              /* IPV6类型 */
    AT_ADS_PDP_IPV4V6                      = 0x03,                              /* IPV4V6类型 */
    AT_ADS_PDP_PPP                         = 0x04,                              /* PPP类型 */

    AT_ADS_PDP_TYPE_BUTT                   = 0xFF
}AT_ADS_PDP_TYPE_ENUM;
typedef VOS_UINT8 AT_ADS_PDP_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
结构名    : AT_ADS_PDP_STATUS_IND_STRU
结构说明  : AT给ADS当前PDP状态的指示

  1.日    期   : 2011年12月6日
    修改内容   : 定义AT给ADS当前PDP状态的指示
  2.日    期   : 2012年02月20日
    修改内容   : 增加数据传输优先级QCI
  3.日    期   : 2012年12月13日
    修改内容   : DSDA Phase II:增加ModemId
  4.日    期   : 2013年05月22日
    修改内容   : V3R3 PPP RPOJECT:增加PDP TYPE
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */
    AT_ADS_MSG_ID_ENUM_UINT32           enMsgId;                                /* 消息类型 */
    MODEM_ID_ENUM_UINT16                enModemId;                              /* Modem Id*/
    VOS_UINT8                           ucRabId;                                /* Rab Id*/
    AT_PDP_STATUS_ENUM_UINT8            enPdpStatus;                            /* PDP状态*/
    AT_ADS_QCI_TYPE_ENUM_UINT8          enQciType;                              /* QCI */
    AT_ADS_PDP_TYPE_ENUM_UINT8          enPdpType;                              /* PDP类型 */
    VOS_UINT8                           aucRsv[2];
}AT_ADS_PDP_STATUS_IND_STRU;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/






#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

