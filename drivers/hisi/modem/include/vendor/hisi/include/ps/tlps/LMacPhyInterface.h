

#ifndef __LMACLPHYINTERFACE_H__
#define __LMACLPHYINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#ifndef LPS_RTT
#include "vos.h"
#endif
#include "memmap_base.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#ifdef LPS_RTT
#define VOS_WIN32   (1)
#define VOS_OS_VER  (3)
#endif

#define LMAC_FEATURE_OFF        (0)
#define LMAC_FEATURE_ON         (1)
#define FEATURE_LMAC_LPHY_R10_CR     LMAC_FEATURE_OFF

/*�ú��ʱ��V7R1�ĵڶ����汾(2011��12��֮��İ汾)��������MBMS��Pilot�汾*/
/*#ifdef PRODUCT_CFG_BOARD_TYPE_HI6920CS_P500 */

/*PS�Ѿ����ú�ɾ����Ϊ�˱��ֽӿ�һ���ԣ���ǰֻ�ڽӿ��ļ��ж���,�������ú�ɾ��*/
#define LTE_UECAP5_MBMS_VERSION


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define ULLMAC_LPHY_MSG_HDR                (0x000009c0)
#define LPHY_ULLMAC_MSG_HDR                (0x00000a00)

#define DLLMAC_LPHY_MSG_HDR                (0x00000a40)
#define LPHY_DLLMAC_MSG_HDR                (0x00000a80)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_MSG_TYPE_ENUM
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : MAC��PHY��Ľӿ���Ϣ
*****************************************************************************/
enum LMAC_LPHY_MSG_TYPE_ENUM
{
    ID_LMAC_LPHY_ACCESS_REQ               = (ULLMAC_LPHY_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LMAC_LPHY_ACCESS_REQ_STRU */   /* MAC��PHY����������뷢���������Ϣ��ϢID */
    ID_LMAC_LPHY_ACCESS_CNF               = (LPHY_ULLMAC_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LMAC_LPHY_ACCESS_CNF_STRU */   /* MAC��PHY����������뷢���������Ϣȷ����ϢID */

    ID_LMAC_LPHY_SR_DATA_REQ              = (ULLMAC_LPHY_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LMAC_LPHY_SR_DATA_REQ_STRU */ /* MAC��������������ϢID */
    ID_LMAC_LPHY_SR_DATA_CNF              = (LPHY_ULLMAC_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LMAC_LPHY_SR_DATA_CNF_STRU */   /* MAC������������ȷ����ϢID */

    ID_LMAC_LPHY_UL_GRANT_HARQ_IND        = (LPHY_ULLMAC_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LMAC_LPHY_UL_GRANT_HARQ_IND_STRU */   /* MAC����������Ȩ�����з�����Ϣ��ָʾ��ϢID */
    ID_LMAC_LPHY_PDCCH_ORDER_IND          = (LPHY_ULLMAC_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice LMAC_LPHY_PDCCH_ORDER_IND_STRU */   /* MAC����PDCCH OReder�ķǾ������ר��Preamble����ϢID */
    ID_LMAC_LPHY_PDCCH_ORDER_SUCC_IND     = (LPHY_ULLMAC_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice LMAC_LPHY_PDCCH_ORDER_SUCC_IND_STRU */   /* MAC����PDCCH OReder�ľ������ �ɹ�*/
    ID_LMAC_LPHY_RAR_TIMEOUT_IND          = (LPHY_ULLMAC_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice LMAC_LPHY_RAR_TIMEOUT_IND_STRU */   /* PHY����RAR��ʱͳ��ָʾ��Ϣ*/

    ID_LMAC_LPHY_RA_ACK_REQ               = (ULLMAC_LPHY_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LMAC_LPHY_RA_ACK_REQ_STRU */   /* MACָʾPHY���ھ��������ACK����ϢID */

    ID_LMAC_LPHY_SPS_RELEASE_REQ          = (ULLMAC_LPHY_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice LMAC_LPHY_SPS_RELEASE_REQ_STRU */   /* MACָʾPHY�ͷŰ뾲̬������Ȩ��Ϣ����ϢID */
    ID_LMAC_LPHY_SPS_RELEASE_CNF          = (LPHY_ULLMAC_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice LMAC_LPHY_SPS_RELEASE_CNF_STRU */   /* MACָʾPHY�ͷŰ뾲̬������Ȩ��Ϣȷ�ϵ���ϢID */

    ID_LMAC_LPHY_RAR_CONFIG_REQ           = (ULLMAC_LPHY_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice LMAC_LPHY_RAR_CONFIG_REQ_STRU */   /* MAC��PHY�������������Ӧ��������Ϣ��ϢID */
    ID_LMAC_LPHY_RAR_CONFIG_CNF           = (LPHY_ULLMAC_MSG_HDR + 0x07),       /* _H2ASN_MsgChoice LMAC_LPHY_RAR_CONFIG_CNF_STRU */   /* MAC��PHY�������������Ӧ��������Ϣȷ����ϢID */

    ID_LMAC_LPHY_CRNTI_CONFIG_REQ         = (ULLMAC_LPHY_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice LMAC_LPHY_CRNTI_CONFIG_REQ_STRU */   /* MAC����C-RNTIֵ����ϢID */
    ID_LMAC_LPHY_CRNTI_CONFIG_CNF         = (LPHY_ULLMAC_MSG_HDR + 0x08),       /* _H2ASN_MsgChoice LMAC_LPHY_CRNTI_CONFIG_CNF_STRU */   /* MAC����C-RNTIֵȷ����ϢID */

    ID_LMAC_LPHY_TA_TIMER_REQ             = (ULLMAC_LPHY_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice LMAC_LPHY_TA_TIMER_REQ_STRU */   /* MACָʾPHY����TA Timer�Ƿ�ʱ�����е���ϢID */
    ID_LMAC_LPHY_TA_TIMER_CNF             = (LPHY_ULLMAC_MSG_HDR + 0x09),       /* _H2ASN_MsgChoice LMAC_LPHY_TA_TIMER_CNF_STRU */   /* MACָʾPHY����TA Timer�Ƿ�ʱ��������Ϣȷ�ϵ���ϢID */

    ID_LMAC_LPHY_DATA_REQ                 = (ULLMAC_LPHY_MSG_HDR + 0x07),       /* _H2ASN_MsgChoice LMAC_LPHY_DATA_REQ_STRU */   /* MAC��PHY���͵�PUSCH���ݵ���ϢID */

    ID_LMAC_LPHY_TA_REQ                   = (DLLMAC_LPHY_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LMAC_LPHY_TA_REQ_STRU */   /* MAC����TAֵ����ϢID */
    ID_LMAC_LPHY_TA_CNF                   = (LPHY_DLLMAC_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LMAC_LPHY_TA_CNF_STRU */   /* MAC����TAֵȷ����ϢID */

    ID_LMAC_LPHY_CONNECTED_DRX_REQ        = (DLLMAC_LPHY_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LMAC_LPHY_CONNECTED_DRX_REQ_STRU */   /* MACָʾPHY����̬�µ�DRX����ϢID */
    ID_LMAC_LPHY_CONNECTED_DRX_CNF        = (LPHY_DLLMAC_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LMAC_LPHY_CONNECTED_DRX_CNF_STRU */   /* MACָʾPHY����̬�µ�DRX��ȷ����ϢID*/

    ID_LMAC_LPHY_MTCH_STOP_REQ            = (DLLMAC_LPHY_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LMAC_LPHY_MTCH_STOP_REQ_STRU */   /* MACָʾPHYֹͣ��ӦPMCH����ϢID */

    ID_LMAC_LPHY_DATA_IND                 = (LPHY_DLLMAC_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LMAC_LPHY_DATA_IND_STRU */   /* MAC����PHY���͵�PDSCH���ݵ���ϢID */
    ID_LMAC_LPHY_BCCH_DATA_IND            = (LPHY_DLLMAC_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice LMAC_LPHY_BCCH_DATA_IND_STRU */   /* MAC����PHY���͵�SIB�㲥���ݵ���ϢID */
    ID_LMAC_LPHY_PCH_DATA_IND             = (LPHY_DLLMAC_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice LMAC_LPHY_PCH_DATA_IND_STRU */   /* MAC����PHY���͵�Ѱ�����ݵ���ϢID  */
    ID_LMAC_LPHY_PBCH_DATA_IND            = (LPHY_DLLMAC_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice LMAC_LPHY_PBCH_IND_STRU */   /* MAC����PHY���͵�MIB�㲥���ݵ���ϢID */
    ID_LMAC_LPHY_MCH_DATA_IND             = (LPHY_DLLMAC_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice LMAC_LPHY_MCH_DATA_IND_STRU */   /* MAC����PHY���͵�MIB�㲥���ݵ���ϢID */

    ID_LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND  = (LPHY_ULLMAC_MSG_HDR + 0x0a),       /* _H2ASN_MsgChoice LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND_STRU */   /* DSP֪ͨMAC����PDCCHָʾ�����а뾲̬�ͷ�*/

    ID_LMAC_LPHY_MSG_TYPE_END
};
typedef         VOS_UINT32          LMAC_LPHY_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : LTE_ACESS_TYPE_ENUM
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : MAC��PHY��������������
*****************************************************************************/
enum LTE_ACESS_TYPE_ENUM
{
    LTE_ACCESS_CONN_OR_REEST_REQ        = 0x00,                                 /*��ʼ�������ؽ���������*/
    LTE_ACCESS_CONTENT_MAC_REQ          = 0x01,                                 /*MAC��������̬��������*/
    LTE_ACCESS_CONTENT_PDCCH_ORDER_REQ  = 0x02,                                 /*PDCCH Order��������̬��������*/
    LTE_ACCESS_NONCONTENT_REQ           = 0x03,                                 /*�л���PDCCH Order�����Ǿ�������*/
    LTE_ACESS_TYPE_BUTT
};
typedef         VOS_UINT8           LTE_ACESS_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LTE_RNTI_TYPE_ENUM
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : MAC��PHY���RNTI����
*****************************************************************************/
enum LTE_RNTI_TYPE_ENUM
{
    LTE_RA_RNTI                         = 0,                                    /*����RAR(PDSCH)��ʹ��RNTI*/
    LTE_P_RNTI                          ,                                       /*Ѱ��ʹ�õ�RNTI*/
    LTE_SI_RNTI                         ,                                       /*�㲥ʹ�õ�RNTI*/
    LTE_C_RNTI                          ,                                       /*�����ʹ�õ�C-RNTI*/
    LTE_SPS_RNTI                        ,                                       /*�뾲̬����ʹ�õ�RNTI*/
    LTE_TC_RNTI                         ,                                       /*������������ʹ�õ���ʱC-RNTI������Msg3���ţ�Msg4����*/
    LTE_TPC_PUCCH_RNTI                  ,                                       /*����ʹ��RNTI*/
    LTE_TPC_PUSCH_RNTI                  ,                                       /*����ʹ��RNTI*/
    LTE_M_RNTI                          ,                                       /*MBMSʹ��RNTI*/
    LTE_RNTI_TYPE_BUTT
};
typedef         VOS_UINT8           LTE_RNTI_TYPE_ENUM_UINT8;

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
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_ACCESS_REQ_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ������뷢���������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucPreambleIndex;                        /*MACȷ����Preamble ID*/
    VOS_UINT8                           ucPrachIndex;                           /*MACȷ����Prach Resource Index*/
    VOS_INT32                           lTxPower;                               /*MACȷ����Preamble���͹���(������·��)*/
    VOS_UINT32                          ulRARarTimeWindow;                      /*���������Ӧ��Ϣ���մ�*/
}LMAC_LPHY_ACCESS_REQ_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_ACCESS_CNF_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ������뷢���������Ϣȷ�����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                               /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT16                          usSFN;                                  /*����Preamble��Ӧ�տ�֡��*/

    VOS_UINT16                          usSubFrameNum;                          /*����Preamble��Ӧ�տ���֡��*/
    VOS_UINT8                           aucRev[2];
}LMAC_LPHY_ACCESS_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_RAR_CONFIG_REQ_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : �����Ӧ��Ϣ������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
#if (VOS_OS_VER == VOS_WIN32)
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
#endif
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    LTE_ACESS_TYPE_ENUM_UINT8           enLteAccessType;                        /*�������ģʽָʾ*/
    VOS_UINT8                           aucRev1[1];

    VOS_UINT16                          usTrnti;                                /*��ʱC-RNTI*/
    VOS_UINT16                          usTa;                                   /*TAֵ*/

    VOS_UINT16                          usTaRecSysFn;                           /*����Taֵ��ϵͳ֡��*/
    VOS_UINT16                          usTaRecSubFn;                           /*����Taֵ��ϵͳ��֡��*/

    VOS_UINT16                          usDetalPrampup;                         /*��Ϣ3���书�ʲ������ӣ���λbd*/
    VOS_INT16                           sPreambleInitTargetPwr;                 /*Preamble��eNB���������չ���*/

    VOS_UINT32                          ulRarUlGrant;                           /*0-19����λ��20���ص�������Ȩ��Ϣ*/
} LMAC_LPHY_RAR_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_RAR_CONFIG_CNF_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : �����Ӧ��Ϣ����ȷ����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
#if (VOS_OS_VER == VOS_WIN32)
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
#endif
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucHarqId;
    VOS_UINT8                           ucRev;
} LMAC_LPHY_RAR_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DATA_REQ_HEAD_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : �������ݷ��͵����ݽṹͷ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usMacDataValid;                         /*MAC�´������Ƿ���Ч��־��0:��Ч 1:��Ч */
    VOS_UINT16                          usPhroffset;                            /* 0:��Ч, ����ֵ��Ч��������ͷ��ƫ��*/

    VOS_UINT16                          usTbSize;                               /*��λBit��Pilot�汾���ֽ�*/
    VOS_UINT8                           ucHarqId;
    VOS_UINT8                           aucRev1[1];                             /*Ԥ����*/
    VOS_UINT8                           aucRev2[4];                             /*Ԥ����*/

}LMAC_LPHY_DATA_REQ_HEAD_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DATA_REQ_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : �������ݷ��͵����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_DATA_REQ_HEAD_STRU        stMacPhyDataReqHead;

    VOS_UINT8                           aucData[4];                              /*ʵ������*/

} LMAC_LPHY_DATA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DATA_IND_HEAD_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : �������ݽ��յ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT32 bitFrameType             :4;                                     /*֡����*/
    VOS_UINT32 bitHarqProcNum           :4;                                     /*���̺�*/
    VOS_UINT32 bitTbSize                :17;                                    /*���ݿ��С,��λ:Bit*/
    VOS_UINT32 bitRecv1                 :3;                                     /*�����ֶ�*/
    VOS_UINT32 bitTranNum               :4;                                     /*��������*/

#ifndef LTE_UECAP5_MBMS_VERSION
    VOS_UINT32 bitSysFrm                :10;                                    /*֡��*/
    VOS_UINT32 bitRecv2                 :6;                                     /*�����ֶ�*/
    VOS_UINT32 bitSubFrm                :4;                                     /*��֡��*/
    VOS_UINT32 bitRecv3                 :4;                                     /*�����ֶ�*/
    VOS_UINT32 bitRntiType              :8;                                     /*RNTI Type*/
#else
    VOS_UINT32 bitSysFrm                :10;                                    /*֡��*/
    VOS_UINT32 bitPmchIndex             :6;                                     /*ֻ��MBMSʹ�ø��ֶΣ���ָPMCH�ŵ�����������ҵ�񶼲�ʹ��*/
    VOS_UINT32 bitSubFrm                :4;                                     /*��֡��*/
    VOS_UINT32 bitRntiType              :4;                                     /*RNTI Type*/
    VOS_UINT32 bitAreaId                :8;                                     /*����ID*/
#endif
}LMAC_LPHY_DATA_IND_HEAD_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DATA_IND_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : �������ݽ��յ����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_DATA_IND_HEAD_STRU        stMacPhyIndHead;

    VOS_UINT8                           aucData[4];                             /*�����������ݿ�ʵ������*/
} LMAC_LPHY_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_BCCH_DATA_IND_HEAD_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ���й㲥���ݽ��յ����ݽṹͷ
*****************************************************************************/
typedef LMAC_LPHY_DATA_IND_HEAD_STRU LMAC_LPHY_BCCH_DATA_IND_HEAD_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_BCCH_DATA_IND_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ���й㲥���ݽ��յ����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_BCCH_DATA_IND_HEAD_STRU   stMacphyBcchIndHead;

    VOS_UINT8                           aucData[4];                             /*�������й㲥����ʵ������*/
} LMAC_LPHY_BCCH_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PCH_DATA_IND_HEAD_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ����Ѱ�����ݽ��յ����ݽṹͷ
*****************************************************************************/
typedef LMAC_LPHY_DATA_IND_HEAD_STRU LMAC_LPHY_PCH_DATA_IND_HEAD_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PCH_DATA_IND_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ����Ѱ�����ݽ��յ����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_PCH_DATA_IND_HEAD_STRU    stMacPhyPchIndHead;

    VOS_UINT8                           aucData[4];                             /*��������Ѱ����Ϣ����ʵ������*/
} LMAC_LPHY_PCH_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_MCH_DATA_IND_HEAD_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ����MBMS���ݽ��յ����ݽṹͷ
*****************************************************************************/
typedef LMAC_LPHY_DATA_IND_HEAD_STRU LMAC_LPHY_MCH_DATA_IND_HEAD_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_MCH_DATA_IND_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ����MBMS���ݽ��յ����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MCH_DATA_IND_HEAD_STRU    stMacPhyMchIndHead;

    VOS_UINT8                           aucData[4];                             /*��������Ѱ����Ϣ����ʵ������*/
} LMAC_LPHY_MCH_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PMCH_MTCH_STOP_INFO
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ����PMCHֹͣ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPmchIndex;                            /*MBMS��Ӧֹͣ��MBMS�����PMCH����*/
    VOS_UINT8                           aucRev[3];
    VOS_UINT32                          ulPmchStopSubFrameNum;                  /*MBMS��Ӧֹͣ��MBMS�����PMCH�ļ���*/
}LMAC_LPHY_PMCH_MTCH_STOP_INFO;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_MTCH_STOP_REQ_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : MAC֪ͨPHYֹͣPMCH����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucAreaId;                               /*MBMS��Ӧֹͣ����ID*/
    VOS_UINT8                           aucRev[1];
    LMAC_LPHY_PMCH_MTCH_STOP_INFO       stPmchStop;
} LMAC_LPHY_MTCH_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_UL_GRANT_INFO_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ������Ȩ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNewDataInd;                           /*������Ȩ������ָʾ��0:�ش�,1:������*/
    VOS_UINT8                           ucSchedulMode;                          /*������Ȩ��Ӧ����ģʽ��0:��̬����,1:�뾲̬����*/
    VOS_UINT8                           ucGapInd;                               /*�ñ�־ֻ�ڰ뾲̬��Ȩ��������Ч��0��Gap��Ч��1��Gap��Ч��Gapָʾ��Ӧ�������ݷ���ʱ��*/
    VOS_UINT8                           aucRev1[1];

    VOS_UINT32                          ulTBSize;                               /*������Ȩ��Ӧ��TB��С����λ:bit*/
}LMAC_LPHY_UL_GRANT_INFO_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_HARQ_INFO_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ����HARQ������Ϣ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHarqFeedInd;                          /*����HARQ������Ϣ��0:NACK 1:ACK*/
    VOS_UINT8                           aucRev[3];
}LMAC_LPHY_HARQ_INFO_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_UL_GRANT_HARQ_INFO_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ������Ȩ������HARQ������Ϣ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTxSFN;                                /*������Ȩ��HARQ��NACK������Ӧ���������ݷ��͵�֡��*/
    VOS_UINT16                          usTxSubFrameNum;                        /*������Ȩ��HARQ��NACK������Ӧ���������ݷ��͵���֡��*/

    VOS_UINT8                           ucHarqId;                               /*������Ȩ��HARQ��NACK������Ӧ���������ݷ��͵Ľ��̺�*/
    VOS_UINT8                           ucUlGrantInd;                           /*������Ȩ�Ƿ���Чָʾ,0:��ЧPHICH�ϱ���Ч;1:��ʾ��Ч*/
    VOS_UINT16                          usRnti;                                 /*RNTIָʾ�������ж���ʱRNTI��RNTI����Ҫ����Msg3��������*/

    LMAC_LPHY_UL_GRANT_INFO_STRU          stUlGrantInfo;                          /*������Ȩ��Ϣ*/

    LMAC_LPHY_HARQ_INFO_STRU              stHarqInfo;                             /*����HARQ������Ϣ*/
}LMAC_LPHY_UL_GRANT_HARQ_INFO_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_UL_GRANT_HARQ_IND_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ������Ȩ������HARQ������Ϣ�����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usRcvSFN;                               /*������Ȩ��HARQ�������յ�֡��*/
    VOS_UINT16                          usRcvSubFrameNum;                       /*������Ȩ��HARQ�������յ���֡��*/

    VOS_UINT8                           ucULGrantNum;                           /*������Ȩ��HARQ��������Ŀ*/
    VOS_UINT8                           aucRev[1];
    VOS_UINT8                           aucRev2[2];

    LMAC_LPHY_UL_GRANT_HARQ_INFO_STRU     astUlGrantHarqInfo[2];                  /*������Ȩ��HARQ������Ϣ*/
} LMAC_LPHY_UL_GRANT_HARQ_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_SR_DATA_REQ_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ����������Ϣ�����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_SR_DATA_REQ_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_SR_DATA_CNF_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ����������Ϣ��ȷ�����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucResult;                               /*0:�ɹ���1��ȡ����2��ʧ��(Ԥ������ʱ����)*/
    VOS_UINT8                           ucSubFrame;                             /*SR���ͳɹ����ڵ�֡��*/
    VOS_UINT16                          usFrame;                                /*SR���ͳɹ����ڵ���֡��*/
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_SR_DATA_CNF_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_TA_REQ_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : TAֵ������Ϣ��������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT16                          usTa;                                   /*���յ�eNB�·���TAֵ*/

    VOS_UINT16                          usTaRevSFN;                             /*���յ�eNB�·���TAֵ��֡��*/
    VOS_UINT16                          usTaRcvSubFN;                           /*���յ�eNB�·���TAֵ����֡��*/
} LMAC_LPHY_TA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_TA_CNF_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : TAֵ������Ϣ�����ȷ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_TA_CNF_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_CRNTI_CONFIG_REQ_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : C-RNTIֵ������Ϣ��������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT16                          usCrnti;                                /*���յ�eNB�·���Crntiֵ*/

} LMAC_LPHY_CRNTI_CONFIG_REQ_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_CRNTI_CONFIG_CNF_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : C-RNTIֵ������Ϣ�����ȷ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                               /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                 /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_CRNTI_CONFIG_CNF_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_CONNECTED_DRX_REQ_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ����̬�µ�DRX����Ԫ���յ�ָʾ��PHY�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                               /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                 /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_CONNECTED_DRX_REQ_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_CONNECTED_DRX_CNF_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ����̬�µ�DRX����Ԫ���յ�ָʾ��PHY��ȷ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_CONNECTED_DRX_CNF_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PDCCH_ORDER_IND_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : PDCCH ORDER�����ķǾ��������������Preamble��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT8                           ucDediPreambleID;                       /*ר��Preamble ID*/
    VOS_UINT8                           ucPrachMaskIndex;                       /*PRACH MASK Index*/
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_PDCCH_ORDER_IND_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PDCCH_ORDER_SUCC_IND_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : PDCCH ORDER�����ľ�������������ĳɹ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

} LMAC_LPHY_PDCCH_ORDER_SUCC_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_RAR_TIMEOUT_IND_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : PHY����RAR��ʱ�䴰��ʱ֪ͨMAC����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

} LMAC_LPHY_RAR_TIMEOUT_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_SPS_RELEASE_REQ_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨPHY���а뾲̬����������Ȩ��Դ�ͷŵ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_SPS_RELEASE_REQ_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_SPS_RELEASE_CNF_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨPHY���а뾲̬����������Ȩ��Դ�ͷŵ�ȷ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_SPS_RELEASE_CNF_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_RA_ACK_REQ_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : �������MAC����Ԫ�����ȷ����µ�ACK/NACK��Ϣ���ݽṹ
             MACд��ACK/NACK��Ϣ������Ϊ��Ч��DSP��ȡ������,��ԭ�����ߵ�������
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucValidFlag;                            /* 0:ACK/NACK��Ϣ��Ч;1:ACK/NACK��Ϣ��Ч��*/
    VOS_UINT8                           ucAckNack;                              /* 0:��ʾNACK��Ϣ,1:��ʾACK��Ϣ*/
} LMAC_LPHY_RA_ACK_REQ_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PBCH_IND_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : �������ݽ��յ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usSFN;                                  /*��������MIB���ݿ��֡��*/
    VOS_UINT16                          usSubFrameNum;                          /*��������MIB���ݿ����֡��*/

    VOS_UINT16                          usAntennaPortsCount;                    /*����������߶˿���*/
    VOS_UINT8                           aucRev[2];

    VOS_UINT32                          ulTBSize;                               /*��������MIB���ݿ��TB��С����λ:bit*/

    VOS_UINT8                           aucData[4];                             /*��������MIB���ݿ�ʵ������*/
} LMAC_LPHY_PBCH_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_TA_TIMER_REQ_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : TA Timer�Ƿ�����֪ͨPHY����Ӧ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT16                          usTaTimerRunInd;                        /*0����ʱ�����У�1����������*/
} LMAC_LPHY_TA_TIMER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_TA_TIMER_CNF_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : TA Timer�Ƿ�����֪ͨPHY����Ӧ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_TA_TIMER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PL_IND_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : PLֵ�ϱ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPlValue;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_PL_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PHR_IND_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : PHRֵ�ϱ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_INT8                            cPhValue;
    VOS_UINT8                           aucRev[3];
} LMAC_LPHY_PHR_IND_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_FORCE_ACTIVE_REQ_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : MAC������̬DRX�ڼ�ǿ�Ƽ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDrxForceActive;
} LMAC_LPHY_FORCE_ACTIVE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_HO_CQI_SRS_ACTIVE_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : MAC���л�������֪ͨPHY����CQI/SRS��Ч�������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHoCqiSrsActive;
} LMAC_LPHY_HO_CQI_SRS_ACTIVE_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : PHY�ͷ����а뾲̬��Ȩָʾ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/

} LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_CAP_CONFIG_REQ_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : MAC����DSP��ͣGAP
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulGapStartFlag;                          /*1:Gap start;  0:Gap stop*/
} LMAC_LPHY_CAP_CONFIG_REQ_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_MSG3_HARQ_IND_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : Msg3�ش���ӦHARQ������Ϣ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTxSfn;                                /*Msg3�ش���Ӧ���͵�֡��*/
    VOS_UINT8                           ucTxSbfn;                               /*Msg3�ش���Ӧ���͵���֡��*/
    VOS_UINT8                           ucRev;
} LMAC_LPHY_MSG3_HARQ_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DL_TB_BUFF_STRU
 Э�����  :
 ASN.1���� :
 �ṹ˵��  : �������ݽ��յĻ���ṹ
*****************************************************************************/
typedef  struct
{
    VOS_UINT32      ulTotalNum;                                                 /*ARM�ṩ��DSP��TB�������������Χ[0,4]ARMд��DSP��*/
    VOS_UINT32      aulTbAddr[4];                                               /*TB�黺���׵�ַ���飬ÿһTB�黺��Ϊ16Kbyte���ݶ���                                                                                �����ڴ�飻�����ַ���׸�����Ԫ������������д��
                                                                                ���ܿ���С��4������ȫ0���룻ȫ0��ʾ�õ�ַ��Ч��ARMд��DSP��*/
    VOS_UINT32      ulUsedNum;                                                  /*DSPһ�������ϱ���TB����Ŀ����Χ[0,4]DSPд��ARM��*/
}LMAC_LPHY_DL_TB_BUFF_STRU;

typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgID;                                /*_H2ASN_MsgChoice_Export LMAC_LPHY_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LMAC_LPHY_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LMAC_LPHY_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    LMAC_LPHY_MSG_DATA                    stMsgData;
}MacPhyInterface_MSG;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
/*��������*/
#define LMAC_LPHY_SYSFRM_ADDR              (LPHY_LMAC_FRAME_ADDR)               /*MACֱ�Ӵ�BBP�Ĵ�����ȡϵͳ֡��*/
#define LMAC_LPHY_SUBFRM_ADDR              (LPHY_LMAC_SUB_FRAME_ADDR)           /*MACֱ�Ӵ�BBP�Ĵ�����ȡϵͳ��֡��*/
#define LMAC_LPHY_TIMER_LOCK_ADDR          (LPHY_LMAC_TIMER_LOCK_ADDR)          /*MACֱ�Ӵ�BBP�Ĵ�����ȡϵͳ֡�ź���֡��ʱ��Ҫ���������*/

/*��������*/
#define DEDI_MAILBOX_FLAG                (0x4)                                  /*ר������Ķ�д��־ռ4���ֽ�*/
#define DEDI_MAILBOX_UL_START_ADDR       (LPHY_MAILBOX_LMAC_UP_BASE_ADDR)       /*ר���������PHY�ϱ���MAC����Ϣ���׵�ַ*/
#define DEDI_MAILBOX_DL_START_ADDR       (LPHY_MAILBOX_LMAC_DOWN_BASE_ADDR)     /*ר���������MAC�·���PHY����Ϣ���׵�ַ*/
#else
extern VOS_UINT8        g_aucDediUlMailBox[512];
extern VOS_UINT8        g_aucDediDlMailBox[256];
extern VOS_UINT32       g_usSysFram;
extern VOS_UINT32       g_ucSubFram;
extern VOS_UINT32       g_ulFramLock;

#define LMAC_LPHY_SYSFRM_ADDR              (&g_usSysFram)                           /*MACֱ�Ӵ�BBP�Ĵ�����ȡϵͳ֡��*/
#define LMAC_LPHY_SUBFRM_ADDR              (&g_ucSubFram)                           /*MACֱ�Ӵ�BBP�Ĵ�����ȡϵͳ��֡��*/
#define LMAC_LPHY_TIMER_LOCK_ADDR          (&g_ulFramLock)          /*MACֱ�Ӵ�BBP�Ĵ�����ȡϵͳ֡�ź���֡��ʱ��Ҫ���������*/

#define DEDI_MAILBOX_FLAG                (0x4)                                  /*ר������Ķ�д��־ռ4���ֽ�*/
#define DEDI_MAILBOX_UL_START_ADDR       g_aucDediUlMailBox                     /*ר���������PHY�ϱ���MAC����Ϣ���׵�ַ*/
#define DEDI_MAILBOX_DL_START_ADDR       g_aucDediDlMailBox                           /*ר���������MAC�·���PHY����Ϣ���׵�ַ*/
#endif


/*****************************************************************************
 ר���������PHY �ϱ���MAC�ĸ�����Ϣ��ַ���ܴ�СԤ��Ϊ512Byte
 ˵��:Ϊ��ʹ�÷��㣬�Լ��������ܣ�һЩFLAG_ADDR��ʱ������ʹ��
        ֱ�Ӷ���ص�ַ��ȡ��ɣ������ر�˵����FLAG ADDRĬ����ʹ�õġ�
*****************************************************************************/
#define DEDI_UL_GRANT_HARQ_FLAG_ADDR     (DEDI_MAILBOX_UL_START_ADDR)
#define DEDI_UL_GRANT_HARQ_ADDR          (DEDI_UL_GRANT_HARQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_PDCCH_ORDER_IND_FLAG_ADDR   (DEDI_UL_GRANT_HARQ_ADDR + sizeof(LMAC_LPHY_UL_GRANT_HARQ_IND_STRU))
#define DEDI_PDCCH_ORDER_IND_ADDR        (DEDI_PDCCH_ORDER_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_PDCCH_ORDER_SUCC_FLAG_ADDR  (DEDI_PDCCH_ORDER_IND_ADDR + sizeof(LMAC_LPHY_PDCCH_ORDER_IND_STRU))
#define DEDI_PDCCH_ORDER_SUCC_ADDR       (DEDI_PDCCH_ORDER_SUCC_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_RAR_TIMEOUT_IND_FLAG_ADDR   (DEDI_PDCCH_ORDER_SUCC_ADDR + sizeof(LMAC_LPHY_PDCCH_ORDER_SUCC_IND_STRU))
#define DEDI_RAR_TIMEOUT_IND_ADDR        (DEDI_RAR_TIMEOUT_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_ACCESS_CNF_FLAG_ADDR        (DEDI_RAR_TIMEOUT_IND_ADDR + sizeof(LMAC_LPHY_RAR_TIMEOUT_IND_STRU))
#define DEDI_ACCESS_CNF_ADDR             (DEDI_ACCESS_CNF_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_SR_DATA_CNF_FLAG_ADDR       (DEDI_ACCESS_CNF_ADDR + sizeof(LMAC_LPHY_ACCESS_CNF_STRU))
#define DEDI_SR_DATA_CNF_ADDR            (DEDI_SR_DATA_CNF_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DEDI_PHR_IND_FLAG_ADDR��־��ʱ��ʹ�ã�PSֱ�Ӷ�ȡDEDI_PHR_IND_ADDR��Ϣʹ��*/
#define DEDI_PHR_IND_FLAG_ADDR           (DEDI_SR_DATA_CNF_ADDR + sizeof(LMAC_LPHY_SR_DATA_CNF_STRU))
#define DEDI_PHR_IND_ADDR                (DEDI_PHR_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DEDI_PL_IND_FLAG_ADDR��־��ʱ��ʹ�ã�PSֱ�Ӷ�ȡDEDI_PL_IND_ADDR��Ϣʹ��*/
#define DEDI_PL_IND_FLAG_ADDR            (DEDI_PHR_IND_ADDR + sizeof(LMAC_LPHY_PHR_IND_STRU))
#define DEDI_PL_IND_ADDR                 (DEDI_PL_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*PDCCH�ͷ����а뾲̬��Ȩ��ָʾ*/
#define DEDI_PDCCH_RELEASE_ULSPS_IND_FLAG_ADDR  (DEDI_PL_IND_ADDR + sizeof(LMAC_LPHY_PL_IND_STRU))
#define DEDI_PDCCH_RELEASE_ULSPS_IND_ADDR       (DEDI_PDCCH_RELEASE_ULSPS_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*Msg3 �ش���ӦHARQ����֡�ź���֡��*/
#define DEDI_MSG3_HARQ_IND_FLAG_ADDR  (DEDI_PDCCH_RELEASE_ULSPS_IND_ADDR + sizeof(LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND_STRU))
#define DEDI_MSG3_HARQ_IND_ADDR       (DEDI_MSG3_HARQ_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*RAR CONFIG CNF*/
#define DEDI_RAR_CONFIG_CNF_FLAG_ADDR    (DEDI_MSG3_HARQ_IND_ADDR + sizeof(LMAC_LPHY_MSG3_HARQ_IND_STRU))
#define DEDI_RAR_CONFIG_CNF_ADDR         (DEDI_RAR_CONFIG_CNF_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DSP��鵽MAC PDU Valid��־Ϊ��Ч,�Ѹñ�־��Ϊ1��MAC�������*/
#define DEDI_MAC_PDU_INVALID_FLAG        (DEDI_RAR_CONFIG_CNF_ADDR+sizeof(LMAC_LPHY_RAR_CONFIG_CNF_STRU))


/*****************************************************************************
 ר���������MAC�·���PHY�ĸ�����Ϣ��ַ�ܴ�СԤ��Ϊ256Byte
 ˵��:Ϊ��ʹ�÷��㣬�Լ��������ܣ�һЩFLAG_ADDR��ʱ������ʹ��
        ֱ�Ӷ���ص�ַ��ȡ��ɣ������ر�˵����FLAG ADDRĬ����ʹ�õġ�
*****************************************************************************/
/*DEDI_DL_TB_BUFF_FLAG_ADDR��־��ʱ��ʹ�ã�DSPֱ�Ӷ�ȡDEDI_DL_TB_BUFF_ADDR��Ϣʹ��*/
#define DEDI_DL_TB_BUFF_FLAG_ADDR        (DEDI_MAILBOX_DL_START_ADDR)
#define DEDI_DL_TB_BUFF_ADDR             (DEDI_DL_TB_BUFF_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_ACCESS_REQ_FLAG_ADDR        (DEDI_DL_TB_BUFF_ADDR + sizeof(LMAC_LPHY_DL_TB_BUFF_STRU))
#define DEDI_ACCESS_REQ_ADDR             (DEDI_ACCESS_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_SR_DATA_REQ_FLAG_ADDR       (DEDI_ACCESS_REQ_ADDR + sizeof(LMAC_LPHY_ACCESS_REQ_STRU))
#define DEDI_SR_DATA_REQ_ADDR            (DEDI_SR_DATA_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_RA_ACK_REQ_FLAG_ADDR        (DEDI_SR_DATA_REQ_ADDR + sizeof(LMAC_LPHY_SR_DATA_REQ_STRU))
#define DEDI_RA_ACK_REQ_ADDR             (DEDI_RA_ACK_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DEDI_FORCE_ACTIVE_REQ_FLAG_ADDR��־��ʱ��ʹ�ã�DSPֱ�Ӷ�ȡDEDI_FORCE_ACTIVE_REQ_ADDR��Ϣʹ��*/
#define DEDI_FORCE_ACTIVE_REQ_FLAG_ADDR  (DEDI_RA_ACK_REQ_ADDR + sizeof(LMAC_LPHY_RA_ACK_REQ_STRU))
#define DEDI_FORCE_ACTIVE_REQ_ADDR       (DEDI_FORCE_ACTIVE_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DEDI_HO_CQI_SRS_ACTIVE_FLAG_ADDR��־��ʱ��ʹ�ã�DSPֱ�Ӷ�ȡDEDI_HO_CQI_SRS_ACTIVE_ADDR��Ϣʹ��*/
#define DEDI_HO_CQI_SRS_ACTIVE_FLAG_ADDR (DEDI_FORCE_ACTIVE_REQ_ADDR + sizeof(LMAC_LPHY_FORCE_ACTIVE_REQ_STRU))
#define DEDI_HO_CQI_SRS_ACTIVE_ADDR      (DEDI_HO_CQI_SRS_ACTIVE_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*RAR CONFIG REQ*/
#define DEDI_RAR_CONFIG_REQ_FLAG_ADDR    (DEDI_HO_CQI_SRS_ACTIVE_ADDR + sizeof(LMAC_LPHY_HO_CQI_SRS_ACTIVE_STRU))
#define DEDI_RAR_CONFIG_REQ_ADDR         (DEDI_RAR_CONFIG_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)


/* L2�л��棬DSP���ܽ���˯�ߣ�����Ӱ������ʱ�ӣ�MAC�����ú����*/
#define DEDI_MAC_PHY_ONLY_RF_SLEEP_FLAG   (DEDI_RAR_CONFIG_REQ_ADDR+sizeof(LMAC_LPHY_RAR_CONFIG_REQ_STRU))

#define DEDI_GAP_CONFIG_REQ_FLAG_ADDR     (DEDI_MAC_PHY_ONLY_RF_SLEEP_FLAG + sizeof(VOS_UINT32))
#define DEDI_GAP_CONFIG_REQ_ADDR          (DEDI_GAP_CONFIG_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)
/*****************************************************************************
  10 ��������
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of LMacPhyInterface.h */