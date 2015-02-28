/******************************************************************************

                  ��Ȩ���� (C), 2003-2013, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : phyerrorlog.h
  �� �� ��   : ����
  ��    ��   : ����ȫ/57356
  ��������   : 2013��9��21��
  ����޸�   :
  ��������   : ����ERRORLOG������ģʽ�ϱ�ʹ�õ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��09��21��
    ��    ��   : ����ȫ/57356
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __PHY_ERRORLOG_H__
#define __PHY_ERRORLOG_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "omerrorlog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/



#define PHY_ERR_LOG_CTRL_LEVEL_NULL             (0)                             /* ErrLog�ȼ�δ����*/
#define PHY_ERR_LOG_CTRL_LEVEL_CRITICAL         (1)                             /* ErrLog�ȼ�Ϊ���� */
#define PHY_ERR_LOG_CTRL_LEVEL_MAJOR            (2)                             /* ErrLog�ȼ�Ϊ��Ҫ */
#define PHY_ERR_LOG_CTRL_LEVEL_MINOR            (3)                             /* ErrLog�ȼ�Ϊ��Ҫ */
#define PHY_ERR_LOG_CTRL_LEVEL_WARNING          (4)                             /* ErrLog�ȼ�Ϊ��ʾ */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : PHY_ERR_LOG_ALM_TYPE_ENUM
 ö��˵��  : ���ϸ澯����
 1.��    ��   : 2013��09��23��
   ��    ��   : luoqingquan
   �޸�����   : �½�
*****************************************************************************/
enum PHY_ERR_LOG_ALM_TYPE_ENUM
{
    PHY_ERR_LOG_ALM_TYPE_COMMUNICATION    = 0x00,                               /* ͨ�� */
    PHY_ERR_LOG_ALM_TYPE_TRAFFIC_QUALITY  = 0x01,                               /* ҵ������ */
    PHY_ERR_LOG_ALM_TYPE_DEAL_WRONG       = 0x02,                               /* �������� */
    PHY_ERR_LOG_ALM_TYPE_DEVICE_FAILURE   = 0x03,                               /* �豸���� */
    PHY_ERR_LOG_ALM_TYPE_ENV_FAILURE      = 0x04,                               /* �������� */
    PHY_ERR_LOG_ALM_TYPE_BUTT
};
typedef VOS_UINT16 PHY_ERR_LOG_ALM_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHY_ERR_LOG_ALM_ID_ENUM
 ö��˵��  : ���ϸ澯ID
 1.��    ��   : 2013��09��23��
   ��    ��   : luoqingquan
   �޸�����   : �½�
*****************************************************************************/
enum PHY_ERR_LOG_ALM_ID_ENUM
{
    PHY_ERR_LOG_ALM_WCDMA_OUT_SYNC      = 0x01,                                 /* ʧ�� */
    PHY_ERR_LOG_ALM_WCDMA_BCCH_FAIL     = 0x02,                                 /* BCCHʧ�� */
    PHY_ERR_LOG_ALM_WCDMA_RL_FAIL       = 0x03,                                 /* ��·ʧ�� */
    PHY_ERR_LOG_ALM_GSM_DEC_FAIL        = 0x04,                                 /* DSC��¼ */
    PHY_ERR_LOG_ALM_GSM_RXLEV_MEAS      = 0x05,                                 /* ������¼ */
    PHY_ERR_LOG_ALM_GSM_FB_SB_IND       = 0x06,                                 /* ������¼ */
    PHY_ERR_LOG_ALM_ID_BUTT
};
typedef VOS_UINT16 PHY_ERR_LOG_ALM_ID_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHY_FTM_LOG_ID_ENUM
 ö��˵��  : ����ģʽ�ϱ��Ĺ���ID
 1.��    ��   : 2013��08��27��
   ��    ��   : l57356
   �޸�����   : �½�
*****************************************************************************/
enum PHY_FTM_LOG_ID_ENUM
{
    PHY_FTM_LOG_ID_WPHY,
    PHY_FTM_LOG_ID_GPHY,

    PHY_FTM_LOG_ID_BUTT,
};
typedef PHY_UINT16 PHY_FTM_LOG_ID_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHY_WCDMA_RL_OUT_OF_SYNC_REASON_ENUM
 ö��˵��  : ע�������Ϣ
 1.��    ��   : 2013��09��21��
   ��    ��   : l57356
   �޸�����   : �½�
*****************************************************************************/
enum PHY_WCDMA_RL_OUT_OF_SYNC_REASON_ENUM
{
    PHY_WCDMA_RL_OUT_OF_SYNC_REASON_DEMOD        = 0x00,                        /* �ϱ�ԭ��Ϊ��� */
    PHY_WCDMA_RL_OUT_OF_SYNC_REASON_DECODE       = 0x01,                        /* �ϱ�ԭ��Ϊ���� */
    PHY_WCDMA_RL_OUT_OF_SYNC_REASON_BUTT
};
typedef VOS_UINT16 PHY_WCDMA_RL_OUT_OF_SYNC_REASON_ENUM_UINT16;



/*****************************************************************************
 ö����    : PHY_WCDMA_BCCH_FAIL_REASON_ENUM
 ö��˵��  : ע�������Ϣ
 1.��    ��   : 2013��09��21��
   ��    ��   : l57356
   �޸�����   : �½�
*****************************************************************************/
enum PHY_WCDMA_BCCH_FAIL_REASON_ENUM
{
    PHY_WCDMA_BCCH_FAIL_REASON_SFN_UPDATE_FAIL   = 0x00,                        /* �ϱ�ԭ��ΪSFN���� */
    PHY_WCDMA_BCCH_FAIL_REASON_CRC_ERR           = 0x01,                        /* �ϱ�ԭ��ΪCRC���� */
    PHY_WCDMA_BCCH_FAIL_REASON_SCHEDULE_FAIL     = 0x02,                        /* �ϱ�ԭ��Ϊ���ȴ��� */
    PHY_WCDMA_BCCH_FAIL_REASON_WORK_TIME_ERR     = 0x03,                        /* �ϱ�ԭ��Ϊ��ʱ���� */
    PHY_WCDMA_BCCH_FAIL_REASON_BUTT
};
typedef VOS_UINT16 PHY_WCDMA_BCCH_FAIL_REASON_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHY_GSM_RPT_REASON_ENUM
 ö��˵��  : ע�������Ϣ
 1.��    ��   : 2013��09��21��
   ��    ��   : l57356
   �޸�����   : �½�
*****************************************************************************/
enum PHY_GSM_RPT_REASON_ENUM
{
    PHY_GSM_RPT_REASON_DSC                      = 0x00,                         /* �ϱ�ԭ��ΪDSC���� */
    PHY_GSM_RPT_REASON_CRC_ERR                  = 0x01,                         /* �ϱ�ԭ��ΪCRC���� */
    PHY_GSM_RPT_REASON_BUTT
};
typedef VOS_UINT16 PHY_GSM_RPT_REASON_ENUM_UINT16;



/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/



/*******************************************************************************
 �ṹ��    : PHY_WCDMA_ERRLOG_FG_INFO_STRU
 �ṹ˵��  : WCDMA���ɺ͸��º��ϱ�����Ϣ�ṹ��
 1.��    ��   : 2013��09��21��
   ��    ��   : l57356
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulFgPos;
    VOS_UINT32                                  ulFgPower;
}PHY_WCDMA_ERRLOG_FG_INFO_STRU;


/*******************************************************************************
 �ṹ��    : PHY_ERRLOG_WCDMA_RL_OUT_OF_SYNC_EVENT_STRU
 �ṹ˵��  : WCDMA���ɺ͸��º��ϱ�����Ϣ�ṹ��
 1.��    ��   : 2013��09��21��
   ��    ��   : l57356
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                      stHeader;
    PHY_WCDMA_RL_OUT_OF_SYNC_REASON_ENUM_UINT16 enRlOutOfSyncReason;
    VOS_INT16                                   sTxPwr;
    VOS_INT16                                   sCQI;
    VOS_INT16                                   sRsv;
    VOS_UINT32                                  ulDemodSyncInfo;
    VOS_UINT32                                  ulDecSyncInfo;
    VOS_UINT32                                  ulDecOutSyncInfo;
    VOS_UINT16                                  usFgEn;
    VOS_UINT16                                  usFgLock;
    PHY_WCDMA_ERRLOG_FG_INFO_STRU               stFgInfo;
}PHY_ERRLOG_WCDMA_RL_OUT_OF_SYNC_EVENT_STRU;



/*******************************************************************************
 �ṹ��    : PHY_ERRLOG_WCDMA_RL_FAIL_EVENT_STRU
 �ṹ˵��  : WCDMA���ɺ͸��º��ϱ�����Ϣ�ṹ��
 1.��    ��   : 2013��09��21��
   ��    ��   : l57356
   �޸�����   : �½�
*******************************************************************************/

typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_WCDMA_BCCH_FAIL_REASON_ENUM_UINT16  enBcchFailReason;
    VOS_INT16                               sRsv;
    VOS_UINT16                              usFgEn;
    VOS_UINT16                              usFgLock;
    PHY_WCDMA_ERRLOG_FG_INFO_STRU           astFgInfo[3];
    VOS_UINT16                              usBcchCrcErrNum;
    VOS_UINT16                              usBgSchdlFailNum;
}PHY_ERRLOG_WCDMA_BCCH_FAIL_EVENT_STRU;




/*******************************************************************************
 �ṹ��    : PHY_ERRLOG_WCDMA_RL_FAIL_EVENT_STRU
 �ṹ˵��  : WCDMA���ɺ͸��º��ϱ�����Ϣ�ṹ��
 1.��    ��   : 2013��09��21��
   ��    ��   : l57356
   �޸�����   : �½�
*******************************************************************************/

typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    VOS_INT16                               sTxPwr;
    VOS_INT16                               sCQI;
    VOS_UINT32                              ulDemodSyncInfo;
    VOS_UINT32                              ulDecSyncInfo;
    VOS_UINT32                              ulDecOutSyncInfo;
    VOS_UINT16                              usFgEn;
    VOS_UINT16                              usFgLock;
    PHY_WCDMA_ERRLOG_FG_INFO_STRU           stFgInfo;
}PHY_ERRLOG_WCDMA_RL_FAIL_EVENT_STRU;





/*******************************************************************************
 �ṹ��    : PHY_ERRLOG_GSM_DECODE_FAIL_EVENT_STRU
 �ṹ˵��  : GSM���ɺ͸��º��ϱ�����Ϣ�ṹ��
 1.��    ��   : 2013��09��21��
   ��    ��   : l57356
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_GSM_RPT_REASON_ENUM_UINT16          enRptReason;
    VOS_UINT16                              usArfcn;
    VOS_UINT16                              usRxlev;
    VOS_UINT16                              usDscInitValue;
    VOS_UINT32                              ulCurFn;
    VOS_UINT16                              usAfc;
    VOS_UINT16                              usTxPwr;
    VOS_UINT16                              usCI;
    VOS_INT16                               sToa;
    VOS_UINT32                              ulCarrirIn;
    VOS_UINT32                              ulInterfereIn;
    VOS_UINT32                              ulCarrirOut;
    VOS_UINT32                              ulInterfereOut;
    VOS_UINT32                              ulLsDcValue;
    VOS_UINT32                              ulRemoveDc;
    VOS_UINT32                              ulBurstRemoveDc;
    VOS_UINT32                              aulDemodData[2];
}PHY_ERRLOG_GSM_DECODE_FAIL_EVENT_STRU;




/*******************************************************************************
 �ṹ��    : PHY_ERRLOG_GSM_DECODE_FAIL_EVENT_STRU
 �ṹ˵��  : GSM���ɺ͸��º��ϱ�����Ϣ�ṹ��
 1.��    ��   : 2013��09��21��
   ��    ��   : l57356
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    VOS_UINT16                              usArfcn;
    VOS_UINT16                              usAfc;
    VOS_UINT32                              ulCurFn;
    VOS_UINT32                              uwReg5250;
    VOS_UINT32                              uwDrssi;
    VOS_UINT32                              uwFastDrssi;
    VOS_UINT32                              ulLsDcValue;
    VOS_UINT32                              ulRemoveDc;
    VOS_UINT32                              ulBurstRemoveDc;
}PHY_ERRLOG_GSM_RXLEV_MEAS_EVENT_STRU;




/*******************************************************************************
 �ṹ��    : PHY_ERRLOG_GSM_FB_SB_EVENT_STRU
 �ṹ˵��  : GSM���ɺ͸��º��ϱ�����Ϣ�ṹ��
 1.��    ��   : 2013��09��21��
   ��    ��   : l57356
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    VOS_UINT16                              usArfcn;
    VOS_UINT16                              usAfc;
    VOS_UINT32                              ulSrchMode;
    VOS_UINT32                              ulRptStatus;
    VOS_UINT32                              ulSbData;
    VOS_UINT32                              ulCurFn;
    VOS_UINT32                              ulReg5250;
    VOS_UINT32                              ulDrssi;
    VOS_UINT32                              ulFastDrssi;
    VOS_UINT32                              ulLsDcValue;
    VOS_UINT32                              ulRemoveDc;
    VOS_UINT32                              ulBurstRemoveDc;
    VOS_UINT32                              aulDemodData[2];
}PHY_ERRLOG_GSM_FB_SB_EVENT_STRU;




/*******************************************************************************
 �ṹ��    : PHY_FTM_WCDMA_DCH_PARA_EVENT_STRU
 �ṹ˵��  : WCDMA���ɺ͸��º��ϱ�����Ϣ�ṹ��
 1.��    ��   : 2013��09��21��
   ��    ��   : l57356
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_FTM_HEADER_STRU                      stHeader;
    VOS_INT16                               sTxPwr;
    VOS_INT16                               sCQI;
    VOS_UINT32                              ulErrBlk;
    VOS_UINT32                              ulDecBlk;
}PHY_FTM_WCDMA_DCH_PARA_EVENT_STRU;


/*******************************************************************************
 �ṹ��    : PHY_FTM_GSM_DCH_PARA_EVENT_STRU
 �ṹ˵��  : GSM���ɺ͸��º��ϱ�����Ϣ�ṹ��
 1.��    ��   : 2013��09��21��
   ��    ��   : l57356
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_FTM_HEADER_STRU                      stHeader;
    VOS_UINT16                              usTxPwr;
    VOS_UINT16                              usErrBlk;
    VOS_UINT16                              usDecBlk;
}PHY_FTM_GSM_DCH_PARA_EVENT_STRU;



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
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

#endif /* end of phyerrorlog.h */

