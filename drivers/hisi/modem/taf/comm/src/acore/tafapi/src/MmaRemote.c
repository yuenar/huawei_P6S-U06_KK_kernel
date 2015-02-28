/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MMA_APPRemote.c
  Version      : V200R002
  Date         : 2005-09-10
  Description  : 该C文件给出了MMA模块的远端实现
                        1、完成形成数据打包传送至mux，
                        2、处理上报的事件与数据传至APP或AT


  Function List:
        1) Taf_DefPhAccessMode
        2) Taf_DefPhBand
        3) Taf_DefPhClassType
        4) Taf_DefPhMode
        5) Taf_InitEventInfoOP
        6) Taf_MmaGetInfo
        7) Taf_PhoneAttach
        8) Taf_PhoneDetach
        9) Taf_PhonePinHandle
       10) Taf_PhonePlmnList
       11) Taf_PhonePlmnResel
       12) Taf_PhonePlmnUserSel
       13) Taf_PhoneStart
       14) Taf_PhoneStartInfoInd
       15) Taf_PhoneStop

  History      :
  1. Date:2005-09-10
     Modification:Create

  1.日    期   : 2006年2月23日
    修改内容   : ARM内存操作必须要从4字节开始的位置获取,Taf_PhonePlmnUserSel
                 函数中添加填充位.问题单号:A32D02119

  2.日    期   : 2006年3月24日
    修改内容   : 问题单号：A32D02738

  3. x51137 A32D06630 2006/10/25
Date         Updated By      PR Number
2006-10-26   Li Jilin        A32D06630
  5.日    期   : 2007年02月11日
    修改内容   : 问题单号:A32D08708
  6.Date        : 2007-10-16
    Modification: 问题单A32D13062(文档校对发现问题)
  7.日    期   : 2007年10月9日
    修改内容   : 新生成函数，A32D13994
  8.日    期   : 2008年3月17日
    修改内容   : 问题单号:AT2D02570,NAS B005版本新增需求合入
  9.日    期   : 2008年06月17日
    修改内容   : 问题单号：AT2D03804,
                 新增 ^HS命令
************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "Taf_Tafm_Remote.h"
#include "ATCmdProc.h"
#include "PsCommonDef.h"
#include "NVIM_Interface.h"
#include "TafClientApi.h"


/* #include "MnComm.h" */
#include "MnCommApi.h"


#include "AtParse.h"

#ifdef  __cplusplus
 #if  __cplusplus
extern "C" {
 #endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/

/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID PS_FILE_ID_MMA_REMOTE_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
   2 全局变量定义
*****************************************************************************/

/*****************************************************************************
   3 函数实现
*****************************************************************************/


/**********************************************************
 Function:       Taf_DefPhServiceMode
 Description:    业务模式设置
 Calls:          APP/AT
 Data Accessed:
 Data Updated:
 Input:      ClientId     - APP/AT标识
             OpId         - 操作标识
             ServiceMode  - 通信参数
 Output:
 Return:         TAF_SUCCESS - 成功
                 TAF_FAILURE - 失败
 Others:
    1.Date        : 2007-10-16
      Modification: 问题单A32D13062(文档校对发现问题)
**********************************************************/
TAF_UINT32  Taf_DefPhClassType ( MN_CLIENT_ID_T       ClientId,
                                 MN_OPERATION_ID_T    OpId,
                                 TAF_PH_MS_CLASS_TYPE MsClass)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_MS_CLASS,
                                   &MsClass,
                                   sizeof(TAF_PH_MS_CLASS_TYPE),
                                   I0_WUEPS_PID_MMA);
}

/*****************************************************************************
 函 数 名  : Taf_DefPhMode
 功能描述  :  设置终端功能级别（＋CFUN华三新增需求），
              通过设置回调函数返回
 输入参数  :  ClientId  - APP/AT标识
              OpId      - 操作标识
              PhModeSet - 手机操作模式
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年8月25日
    修改内容   : V200R001版本新生成函数

*****************************************************************************/
VOS_UINT32 Taf_DefPhMode(MN_CLIENT_ID_T   ClientId,
                         MN_OPERATION_ID_T   OpId,
                         TAF_PH_OP_MODE_STRU PhModeSet)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_FUN,
                                   &PhModeSet,
                                   sizeof(TAF_PH_OP_MODE_STRU),
                                   I0_WUEPS_PID_MMA);
}

/*****************************************************************************
 函 数 名  : Taf_PhonePinHandle
 功能描述  : +CPIN USIM提供的PIN操做的API
             void Api_PIN_Handle(VOS_UINT8 ucClientId,VOS_UINT8 ucCmdType, VOS_UINT8
             ucPINType,\
             VOS_UINT8 *pucOldPIN, VOS_UINT8 *pucNewPIN)；
 输入参数  : ClientId - APP/AT标识
                 OpId - 操作标识
*pPinData - 手机PIN码操作数据结构
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年8月25日
    修改内容   : V200R001版本生成函数
  2.日    期   : 2007年10月16日
    修改内容   : 问题单A32D13062(文档校对发现问题)
*****************************************************************************/
TAF_UINT32 Taf_PhonePinHandle ( MN_CLIENT_ID_T          ClientId,
                                MN_OPERATION_ID_T       OpId,
                                TAF_PH_PIN_DATA_STRU   *pPinData)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_OP_PIN_REQ,
                                   pPinData,
                                   sizeof(TAF_PH_PIN_DATA_STRU),
                                   I0_WUEPS_PID_MMA);
}


/*****************************************************************************
 函 数 名  : Taf_MePersonalisationHandle
 功能描述  : 锁卡状态查询
 输入参数  : pMsg  消息块
 输出参数  : ClientId - APP/AT标识
             OpId - 操作标识
 返 回 值  : 成功，失败
 修改历史      :
  1.日    期   : 2007年9月28日
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 Taf_MePersonalisationHandle(MN_CLIENT_ID_T          ClientId,
                                       MN_OPERATION_ID_T                 OpId,
                                       TAF_ME_PERSONALISATION_DATA_STRU *pMePersonalData)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_ME_PERSONAL_REQ,
                                   pMePersonalData,
                                   sizeof(TAF_ME_PERSONALISATION_DATA_STRU),
                                   I0_WUEPS_PID_MMA);
}

/**********************************************************/
/*                      电话管理API                       */
/**********************************************************/

/**********************************************************
 Function:       Taf_PhonePlmnResel
 Description:    PLMN重选
 Calls:          APP/AT
 Data Accessed:  2005-09-16
 Data Updated:
 Input:          ClientId  - APP/AT标识
                 OpId      - 操作标识
                 ReselType - 重选类型
 Output:
 Return:         TAF_SUCCESS - 成功
                 TAF_FAILURE - 失败
 Others:
    1.Date        : 2007-10-16
      Modification: 问题单A32D13062(文档校对发现问题)
**********************************************************/
TAF_UINT32 Taf_PhonePlmnResel ( MN_CLIENT_ID_T           ClientId,
                                MN_OPERATION_ID_T        OpId,
                                TAF_PLMN_RESEL_MODE_TYPE ReselType)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_PLMN_RESEL,
                                   &ReselType,
                                   sizeof(TAF_PLMN_RESEL_MODE_TYPE),
                                   I0_WUEPS_PID_MMA);
}

VOS_UINT32 TAF_PhonePlmnUserSel(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    VOS_UINT16                          usOprNameLen,
    VOS_UINT8                          *pucOperName,
    AT_COPS_FORMAT_TYPE                 ucFormatType,
    TAF_PH_RA_MODE                      AccessMode
)
{
    VOS_UINT32                           ulRst;
    VOS_UINT32                           ulGetOperNameRst;
    TAF_PLMN_USER_SEL_STRU               stPlmnUserSel;

    /* 参数为空 */
    if (0 == usOprNameLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stPlmnUserSel.ucFormatType = ucFormatType;
    stPlmnUserSel.ucAccessMode = AccessMode;

    /* 根据输入PLMN的类型来保存到TAF_PLMN_USER_SEL_STRU结构中，发送到MMA模块，有MMA进行转换并处理指定搜。 */
    ulGetOperNameRst = AT_GetOperatorNameFromParam(&stPlmnUserSel.usOperNameLen,
                                                    stPlmnUserSel.ucOperName,
                                                    sizeof(stPlmnUserSel.ucOperName),
                                                    stPlmnUserSel.ucFormatType);

    if (AT_OK != ulGetOperNameRst )
    {
        return ulGetOperNameRst;
    }

    /* 发送消息 TAF_MSG_MMA_PLMN_USER_SEL 给 MMA 处理，
       该消息带TAF_PLMN_USER_SEL_STRU类型的参数结构 */
    ulRst = MN_FillAndSndAppReqMsg(ClientId,
                                   OpId,
                                   TAF_MSG_MMA_PLMN_USER_SEL,
                                   (VOS_UINT8*)&stPlmnUserSel, /*要求查询PS的注册状态。*/
                                   sizeof(TAF_PLMN_USER_SEL_STRU),
                                   I0_WUEPS_PID_MMA);


    if (TAF_SUCCESS == ulRst )
    {
        return AT_OK;
    }

    return AT_ERROR;
}

/*****************************************************************************
 函 数 名  : Taf_PhoneAttach
 功能描述  : +CGATT ATTACH，通过操作结果回调函数上报返回结果
 输入参数  : ClientId    - APP/AT标识
             OpId        - 操作标识
             AttachType  - 附着类型
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年8月25日
    修改内容   :V200R001版本 新生成函数
  2.日    期   : 2007年10月16日
    修改内容   : 问题单A32D13062(文档校对发现问题)

*****************************************************************************/
TAF_UINT32 Taf_PhoneAttach ( MN_CLIENT_ID_T     ClientId,
                             MN_OPERATION_ID_T  OpId,
                             TAF_PH_ATTACH_TYPE AttachType)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_ATTACH,
                                   &AttachType,
                                   sizeof(TAF_PH_ATTACH_TYPE),
                                   I0_WUEPS_PID_MMA);
}

/**********************************************************
 Function:       Taf_PhonePlmnList
 Description:    可用PLMN搜索
 Calls:          APP/AT
 Data Accessed:  2005-09-16
 Data Updated:
 Input:          ClientId - APP/AT标识
                 OpId     - 操作标识
                 ListType - 搜索类型
 Output:
 Return:         TAF_SUCCESS - 成功
                 TAF_FAILURE - 失败
 Others:
    1.Date        : 2007-10-16
    Modification: 问题单A32D13062(文档校对发现问题)
**********************************************************/
TAF_UINT32 Taf_PhonePlmnList ( MN_CLIENT_ID_T           ClientId,
                               MN_OPERATION_ID_T        OpId,
                               TAF_AVAIL_PLMN_LIST_TYPE ListType)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_PLMN_LIST,
                                   &ListType,
                                   sizeof(TAF_AVAIL_PLMN_LIST_TYPE),
                                   I0_WUEPS_PID_MMA);
}



VOS_UINT32 TAF_AbortPlmnListReq (
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId
)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_PLMN_LIST_ABORT_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_MMA );
}


/*****************************************************************************
 函 数 名  : Taf_PhoneDetach
 功能描述  : +CGATT DETACH，通过操作结果回调函数上报返回结果
 输入参数  : ClientId   - APP/AT标识
             OpId       - 操作标识
             DetachType - 解除类型
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年8月25日
    修改内容   : V200R001版本新生成函数
  2.日    期   : 2007年10月16日
    修改内容   : 问题单A32D13062(文档校对发现问题)
*****************************************************************************/
TAF_UINT32 Taf_PhoneDetach ( MN_CLIENT_ID_T     ClientId,
                             MN_OPERATION_ID_T  OpId,
                             TAF_PH_DETACH_TYPE DetachType)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_DETACH,
                                   &DetachType,
                                   sizeof(TAF_PH_DETACH_TYPE),
                                   I0_WUEPS_PID_MMA);
}

/*****************************************************************************
 函 数 名  : Taf_PhoneStartInfoInd
 功能描述  : 启动接入层主动上报消息，该函数用于设定是否上报信号质量，小区ID等信息，
             返回系统信息反馈事件判定设置成功与否。
 输入参数  : stStartInfoInd -- 参看接口定义
 输出参数  : 无
 返 回 值  : VOS_UINT32 -- 0:设置成功
                           1:设置失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年12月13日
    修改内容   : 新生成函数
  2.日    期   : 2007年10月16日
    修改内容   : 问题单A32D13062(文档校对发现问题)
*****************************************************************************/
TAF_UINT32 Taf_PhoneStartInfoInd ( MN_CLIENT_ID_T          ClientId,
                                   MN_OPERATION_ID_T       OpId,
                                   TAF_START_INFO_IND_STRU StartInfoInd)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_INFO_REPORT,
                                   &StartInfoInd,
                                   sizeof(TAF_START_INFO_IND_STRU),
                                   I0_WUEPS_PID_MMA);
}

/*****************************************************************************
 函 数 名  : TAF_DefQuickStart
 功能描述  : 设置快速开机
 输入参数  : MN_CLIENT_ID_T ClientId
             MN_OPERATION_ID_T   OpId
             TAF_UINT32 ulSetValue
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月9日
    修改内容   : 新生成函数
*****************************************************************************/
TAF_UINT32 TAF_DefQuickStart(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, TAF_UINT32 ulSetValue)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_SET_QUICKSTART,
                                   &ulSetValue,
                                   sizeof(TAF_UINT32),
                                   I0_WUEPS_PID_MMA);
}


TAF_UINT32 Taf_DefPhAutoAttach(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, TAF_UINT32 ulSetValue)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_SET_AUTOATTACH,
                                   &ulSetValue,
                                   sizeof(TAF_UINT32),
                                   I0_WUEPS_PID_MMA);
}

/*****************************************************************************
 函 数 名  : TAF_DefLoadDefault
 功能描述  : 恢复出厂配置
 输入参数  : MN_CLIENT_ID_T ClientId
             MN_OPERATION_ID_T   OpId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月22日
    修改内容   : creat function
*****************************************************************************/
TAF_UINT32 TAF_DefLoadDefault(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_SET_LOADDEFAULT,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_MMA);
}

/*****************************************************************************
 函 数 名  : Taf_UsimRestrictedAccessCommand
 功能描述  : 用于支持受限制的卡操作命令
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年10月25日
    修改内容   : 新生成函数
*****************************************************************************/
TAF_UINT32 Taf_UsimRestrictedAccessCommand(MN_CLIENT_ID_T               ClientId,
                                           MN_OPERATION_ID_T            OpId,
                                           TAF_SIM_RESTRIC_ACCESS_STRU *pPara)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_USIM_RESTRICTED_ACCESS,
                                   pPara,
                                   sizeof(TAF_SIM_RESTRIC_ACCESS_STRU),
                                   I0_WUEPS_PID_MMA);
}



/*****************************************************************************
 函 数 名  : Taf_IndPhFreq
 功能描述  : 指定频点搜网
 输入参数  : MN_CLIENT_ID_T ClientId
             MN_OPERATION_ID_T   OpId
             TAF_IND_FREQ_STRU Freq
 输出参数  : TAF_SUCCESS or TAF_FAILURE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年10月24日
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Taf_IndPhFreq(MN_CLIENT_ID_T     ClientId,
                         MN_OPERATION_ID_T        OpId,
                         TAF_IND_FREQ_STRU        Freq)
{
    VOS_UINT16 temp_Freq;
    VOS_UINT16 temp_value;

    switch (Freq.RatType)
    {
    case TAF_SYS_SUBMODE_GSM:
        temp_value   = Freq.GsmBand;
        temp_value <<= 12;
        temp_Freq   = temp_value;
        temp_value  = Freq.IndFreq;
        temp_value &= 0x0fff;
        temp_Freq |= temp_value;

        /* write temp_GSM_Freq to NVIM */
        if (NV_OK != NV_Write( en_NV_Item_Gsm_Ind_Freq, &temp_Freq, sizeof(VOS_UINT16)))
        {
            return TAF_FAILURE;
        }

        break;

    case TAF_SYS_SUBMODE_WCDMA:

        /*write Freq to NVIM */
        temp_Freq = Freq.IndFreq;
        if (NV_OK != NV_Write( en_NV_Item_Wcdma_Ind_Freq, &temp_Freq, sizeof(VOS_UINT16)))
        {
            return TAF_FAILURE;
        }

        break;

    default:
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}

/*****************************************************************************
 函 数 名  : Taf_FplmnHandle
 功能描述  : FPLMN通用操作处理
 输入参数  :  ClientId  - APP/AT标识
              OpId      - 操作标识
              PhModeSet - 手机操作模式
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
1.日    期   : 2007年10月9日
  修改内容   : 新生成函数，A32D13994
*****************************************************************************/
TAF_UINT32 Taf_FplmnHandle(MN_CLIENT_ID_T            ClientId,
                           MN_OPERATION_ID_T         OpId,
                           TAF_PH_FPLMN_OPERATE_STRU stFplmnOperate)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_FPLMN_HANDLE,
                                   &stFplmnOperate,
                                   sizeof(TAF_PH_FPLMN_OPERATE_STRU),
                                   I0_WUEPS_PID_MMA);
}


VOS_UINT32 Taf_SysCfgHandle(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_PH_SYS_CFG_EX_STRU              stSysCfg
)
{

    return MN_FillAndSndAppReqMsg(ClientId,
                                  OpId,
                                  TAF_MSG_MMA_SYSCFG_HANDLE,
                                  &stSysCfg,
                                  sizeof(stSysCfg),
                                  I0_WUEPS_PID_MMA);
}



VOS_UINT32 Taf_NetScanHandle(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_MMA_NET_SCAN_REQ_STRU          *pstNetScan
)
{
    return MN_FillAndSndAppReqMsg(usClientId,
                                  ucOpId,
                                  TAF_MSG_MMA_NET_SCAN_REQ,
                                  pstNetScan,
                                  sizeof(TAF_MMA_NET_SCAN_REQ_STRU),
                                  I0_WUEPS_PID_MMA);
}



VOS_UINT32 Taf_AbortNetScan (
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
)
{
    return MN_FillAndSndAppReqMsg( usClientId,
                                   ucOpId,
                                   TAF_MSG_MMA_ABORT_NET_SCAN_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_MMA );
}


/*****************************************************************************
 函 数 名  : TAF_QryUsimInfo
 功能描述  :
 输入参数  :
 输出参数  : Icctype
 返 回 值  : TAF_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年9月19日
    修改内容   : 新增函数,查询USIM卡的相关信息

*****************************************************************************/
TAF_UINT32 TAF_QryUsimInfo(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_PH_QRY_USIM_INFO_STRU           *pstInfo
)
{
    if ( (TAF_PH_ICC_UNKNOW == pstInfo->Icctype)
      || (pstInfo->Icctype > TAF_PH_ICC_USIM))
    {
        return TAF_FAILURE;
    }

    if (pstInfo->enEfId > TAF_PH_OPL_FILE)
    {
        return TAF_FAILURE;
    }
    return MN_FillAndSndAppReqMsg( ClientId,
                             OpId,
                             TAF_MSG_MMA_USIM_INFO,
                             pstInfo,
                             sizeof(TAF_PH_QRY_USIM_INFO_STRU),
                             I0_WUEPS_PID_MMA);

}

/*****************************************************************************
 函 数 名  : TAF_QryCpnnInfo
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  : TAF_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年9月19日
    修改内容   : 新增函数,查询USIM卡的相关信息

*****************************************************************************/
TAF_UINT32 TAF_QryCpnnInfo(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_PH_ICC_TYPE                     IccType
)
{
    if ( (TAF_PH_ICC_UNKNOW == IccType)
      || (IccType > TAF_PH_ICC_USIM))
    {
        return TAF_FAILURE;
    }

    return MN_FillAndSndAppReqMsg( ClientId,
                             OpId,
                             TAF_MSG_MMA_CPNN_INFO,
                             &IccType,
                             sizeof(IccType),
                             I0_WUEPS_PID_MMA);
}


VOS_UINT32 Taf_SetEOPlmnHandle(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_MMA_SET_EOPLMN_LIST_STRU       *pstEOPlmnCfg
)
{

    return MN_FillAndSndAppReqMsg(ClientId,
                                  OpId,
                                  TAF_MSG_MMA_EOPLMN_SET_REQ,
                                  pstEOPlmnCfg,
                                  sizeof(TAF_MMA_SET_EOPLMN_LIST_STRU),
                                  I0_WUEPS_PID_MMA);
}

#ifdef  __cplusplus
 #if  __cplusplus
}
 #endif
#endif
