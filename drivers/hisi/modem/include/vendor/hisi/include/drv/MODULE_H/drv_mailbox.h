/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : drv_mailbox.h
  �� �� ��   : ����
  ��    ��   : Ī�� 00176101
  ��������   : 2012��9��20��
  ����޸�   :
  ��������   : �������ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��20��
    ��    ��   : ��ׯ�� 59026
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __DRV_MAILBOX_H__
#define __DRV_MAILBOX_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "drv_ipcm.h"
#include "drv_mailbox_ifc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* ����ԴCPU �� Ŀ��CPU������ͨ��, ÿͨ����Ӧ���������仺�� */

/* ����������ö����ĺ궨�� */
#define MAILBOX_CHANNEL_BEGIN(src, dst) \
    enum MAILBOX_CHANNEL_##src##2##dst##_ENUM \
    { \
        MAILBOX_CHANNEL_##src##2##dst##_RSERVED = -1,

#define MAILBOX_CHANNEL_ITEM(src, dst, channel)  \
    MAILBOX_CHANNEL_##src##2##dst##_##channel

#define MAILBOX_CHANNEL_END(src, dst) \
        MAILBOX_CHANNEL_##src##2##dst##_BUTT \
    };

/* CCPU -> HIFI */
MAILBOX_CHANNEL_BEGIN(CCPU, HIFI)
    /* ���¸�ö�����������, ����: MAILBOX_CHANNEL_CCPU2HIFI_DEFAULT */
    MAILBOX_CHANNEL_ITEM(CCPU, HIFI, MSG),
MAILBOX_CHANNEL_END(CCPU, HIFI)

/* CCPU -> MCU */
MAILBOX_CHANNEL_BEGIN(CCPU, MCU)
    MAILBOX_CHANNEL_ITEM(CCPU, MCU, MSG),
    MAILBOX_CHANNEL_ITEM(CCPU, MCU, IFC),
MAILBOX_CHANNEL_END(CCPU, MCU)

/* CCPU -> ACPU */
MAILBOX_CHANNEL_BEGIN(CCPU, ACPU)
    MAILBOX_CHANNEL_ITEM(CCPU, ACPU, MSG),
    MAILBOX_CHANNEL_ITEM(CCPU, ACPU, IFC),
MAILBOX_CHANNEL_END(CCPU, ACPU)

/* ACPU -> CCPU */
MAILBOX_CHANNEL_BEGIN(ACPU, CCPU)
    MAILBOX_CHANNEL_ITEM(ACPU, CCPU, MSG),
    MAILBOX_CHANNEL_ITEM(ACPU, CCPU, IFC),
MAILBOX_CHANNEL_END(ACPU, CCPU)

/* ACPU -> MCU */
MAILBOX_CHANNEL_BEGIN(ACPU, MCU)
    MAILBOX_CHANNEL_ITEM(ACPU, MCU, MSG),
    MAILBOX_CHANNEL_ITEM(ACPU, MCU, IFC),
MAILBOX_CHANNEL_END(ACPU, MCU)

/* ACPU -> HIFI */
MAILBOX_CHANNEL_BEGIN(ACPU, HIFI)
    MAILBOX_CHANNEL_ITEM(ACPU, HIFI, MSG),
MAILBOX_CHANNEL_END(ACPU, HIFI)

/* HIFI -> ACPU */
MAILBOX_CHANNEL_BEGIN(HIFI, ACPU)
    MAILBOX_CHANNEL_ITEM(HIFI, ACPU, MSG),
MAILBOX_CHANNEL_END(HIFI, ACPU)

/* HIFI -> CCPU */
MAILBOX_CHANNEL_BEGIN(HIFI, CCPU)
    MAILBOX_CHANNEL_ITEM(HIFI, CCPU, MSG),
MAILBOX_CHANNEL_END(HIFI, CCPU)

/* HIFI -> BBE16 */
MAILBOX_CHANNEL_BEGIN(HIFI, BBE16)
    MAILBOX_CHANNEL_ITEM(HIFI, BBE16, MSG),
MAILBOX_CHANNEL_END(HIFI, BBE16)

/* MCU -> ACPU */
MAILBOX_CHANNEL_BEGIN(MCU, ACPU)
    MAILBOX_CHANNEL_ITEM(MCU, ACPU, MSG),
    MAILBOX_CHANNEL_ITEM(MCU, ACPU, IFC),
MAILBOX_CHANNEL_END(MCU, ACPU)

/* MCU -> CCPU */
MAILBOX_CHANNEL_BEGIN(MCU, CCPU)
    MAILBOX_CHANNEL_ITEM(MCU, CCPU, MSG),
    MAILBOX_CHANNEL_ITEM(MCU, CCPU, IFC),
MAILBOX_CHANNEL_END(MCU, CCPU)

/* BBE16 -> HIFI */
MAILBOX_CHANNEL_BEGIN(BBE16, HIFI)
    MAILBOX_CHANNEL_ITEM(BBE16, HIFI, MSG),
MAILBOX_CHANNEL_END(BBE16, HIFI)

/* ����SI����, �����Ķ����� */
enum MAILBOX_GAP_FOR_SI_PARSE {MAILBOX_GAP_FOR_SI_BUTT};

#define MAILBOX_ID_SRC_CPU_OFFSET       (24)        /*�ʼ�ID�е�ԴCPU ID bitλƫ�Ƶ�ַ*/
#define MAILBOX_ID_DST_CPU_OFFSET       (16)        /*�ʼ�ID�е�ԴCPU ID bitλƫ�Ƶ�ַ*/
#define MAILBOX_ID_CHANNEL_OFFSET       (8)         /*�ʼ�ID�������ڴ�ͨ�� ID bitλƫ�Ƶ�ַ*/

/* �ʱ���ʼ��ź궨�� */
#define MAILBOX_MAILCODE_CHANNEL(src, dst, channel) \
    ( ((unsigned long)(src) << MAILBOX_ID_SRC_CPU_OFFSET) \
    | ((unsigned long)(dst) << MAILBOX_ID_DST_CPU_OFFSET) \
    | ((unsigned long)(channel) << MAILBOX_ID_CHANNEL_OFFSET) )

#define MAILBOX_CPUID(cpu)   MAILBOX_CPUID_##cpu

#define MAILBOX_MAILCODE_RESERVED(src, dst, channel) \
    MAILBOX_MAILCODE_CHANNEL(MAILBOX_CPUID(src), \
                             MAILBOX_CPUID(dst), \
                            MAILBOX_CHANNEL_ITEM(src, dst, channel))

#define MAILBOX_MAILCODE_ITEM_RESERVED(src, dst, channel) \
    MAILBOX_MAILCODE_##src##2##dst##_##channel##_RESERVED

#define MAILBOX_MAILCODE_ITEM_END(src, dst, channel)    \
    MAILBOX_MAILCODE_##src##2##dst##_##channel##_BUTT

#define MAILBOX_MAILCODE_ITEM_BEGIN(src, dst, channel)  \
    MAILBOX_MAILCODE_ITEM_RESERVED(src, dst, channel) = MAILBOX_MAILCODE_RESERVED(src, dst, channel)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ʵ �� ��  : MAILBOX_CPUID_E
 ��������  : ���������漰CPU���
*****************************************************************************/
enum MAILBOX_CPUID_ENUM
{
    MAILBOX_CPUID_RESERVED  =   -1,
    MAILBOX_CPUID_ACPU      =   IPC_CORE_ACPU,
    MAILBOX_CPUID_CCPU      =   IPC_CORE_CCPU,
    MAILBOX_CPUID_MCU       =   IPC_CORE_MCU,
    MAILBOX_CPUID_HIFI      =   IPC_CORE_HIFI,
    MAILBOX_CPUID_BBE16     =   IPC_CORE_BBE16,
    MAILBOX_CPUID_BUTT
};

/*****************************************************************************
 ʵ������  : MAILBOX_MAILCODE_ENUM
 ��������  : �ʱ�ö�ٶ���, �ʱ�Ψһ��ʶ�ʼ�����Ŀ��, Ҳ���ʼ����ݽ��մ�����
*****************************************************************************/
enum MAILBOX_MAILCODE_ENUM
{
    /* CCPU->MCU �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, MCU, MSG),
    MAILBOX_MAILCODE_CCPU_TO_MCU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_CCPU_TO_MCU_VOS_MSG_URGENT,
    BSP_MAILBOX_CHANNEL_CCPU_TO_MCU_MCA_CH,

    MAILBOX_MAILCODE_ITEM_END(CCPU, MCU, MSG),

    /* CCPU->MCU IFC���úŶ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, MCU, IFC),
    MAILBOX_IFC_CCPU_TO_MCU_TEST_CMP, //s00227525
    MAILBOX_IFC_CCPU_TO_MCU_TEST,
    MAILBOX_IFC_CCPU_TO_MCU_MCA,
    MAILBOX_MAILCODE_ITEM_END(CCPU, MCU, IFC),

    /* CCPU->HIFI �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, HIFI, MSG),
    MAILBOX_MAILCODE_CCPU_TO_HIFI_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_CCPU_TO_HIFI_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ITEM_END(CCPU, HIFI, MSG),

    /* CCPU->ACPU �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, ACPU, MSG),
    MAILBOX_MAILCODE_ITEM_END(CCPU, ACPU, MSG),

    /* CCPU->ACPU IFC��Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, ACPU, IFC),
    MAILBOX_IFC_CCPU_TO_ACPU_TEST_CMP, //s00227525
    MAILBOX_IFC_CCPU_TO_ACPU_TEST,
    MAILBOX_IFC_CCPU_TO_ACPU_PRINT,
    MAILBOX_IFC_CCPU_TO_ACPU_FOPEN,
    MAILBOX_IFC_CCPU_TO_ACPU_FCLOSE,
    MAILBOX_IFC_CCPU_TO_ACPU_FREAD,
    MAILBOX_IFC_CCPU_TO_ACPU_FWRITE,
    MAILBOX_IFC_CCPU_TO_ACPU_FSEEK,
    MAILBOX_IFC_CCPU_TO_ACPU_REMOVE,
    MAILBOX_IFC_CCPU_TO_ACPU_FTELL,
    MAILBOX_IFC_CCPU_TO_ACPU_RENAME,
    MAILBOX_IFC_CCPU_TO_ACPU_ACCESS,
    MAILBOX_IFC_CCPU_TO_ACPU_MKDIR,
    MAILBOX_IFC_CCPU_TO_ACPU_RMDIR,
    MAILBOX_IFC_ACPU_TO_CCPU_PMIC_IRQEVENT_REPO,
    MAILBOX_MAILCODE_ITEM_END(CCPU, ACPU, IFC),

    /* ACPU->MCU �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, MCU, MSG),
    MAILBOX_MAILCODE_ACPU_TO_MCU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_ACPU_TO_MCU_VOS_MSG_URGENT,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_IFC_CH,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_IFC_RESPONSE_CH,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_SENSOR_CH,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_TP_CH,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_MCA_CH,
    /*Modify_for_c_reset, l00212112,20130511, starts*/
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_RST_CH,
    /*Modify_for_c_reset, l00212112,20130511, ends*/
    MAILBOX_MAILCODE_ITEM_END(ACPU, MCU, MSG),

    /* ACPU->MCU IFCԶ�̺��������ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, MCU, IFC),
    MAILBOX_IFC_ACPU_TO_MCU_TEST_CMP, //s00227525
    MAILBOX_IFC_ACPU_TO_MCU_TEST,
    MAILBOX_IFC_ACPU_TO_MCU_HUTAF_HLT,
	MAILBOX_IFC_ACPU_TO_MCU_MCA,
    MAILBOX_IFC_ACPU_TO_MCU_MNTN,
    MAILBOX_IFC_ACPU_TO_MCU_RUN_CMD,
    MAILBOX_MAILCODE_ITEM_END(ACPU, MCU, IFC),


    /* ACPU->HIFI �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, HIFI, MSG),
    MAILBOX_MAILCODE_ACPU_TO_HIFI_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_ACPU_TO_HIFI_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ACPU_TO_HIFI_AUDIO,
    MAILBOX_MAILCODE_ACPU_TO_HIFI_MISC,
    /*Modify_for_c_reset, l00212112,20130511, starts*/
    MAILBOX_MAILCODE_ACPU_TO_HIFI_CCORE_RESET_ID,
    /*Modify_for_c_reset, l00212112,20130511, ends*/
    MAILBOX_MAILCODE_ITEM_END(ACPU, HIFI, MSG),

    /* ACPU->CCPU MSG�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, CCPU, MSG),
    MAILBOX_IFC_ACPU_TO_CCPU_CSHELL_START,
    MAILBOX_MAILCODE_ITEM_END(ACPU, CCPU, MSG),

    /* ACPU->CCPU IFC�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, CCPU, IFC),
    MAILBOX_IFC_ACPU_TO_CCPU_TEST_CMP, //s00227525
    MAILBOX_IFC_ACPU_TO_CCPU_TEST,
    MAILBOX_IFC_ACPU_TO_CCPU_PRINT,
    MAILBOX_IFC_ACPU_TO_CCPU_FOPEN,
    MAILBOX_IFC_ACPU_TO_CCPU_FCLOSE,
    MAILBOX_IFC_ACPU_TO_CCPU_FREAD,
    MAILBOX_IFC_ACPU_TO_CCPU_FWRITE,
    MAILBOX_IFC_ACPU_TO_CCPU_FSEEK,
    MAILBOX_IFC_ACPU_TO_CCPU_REMOVE,
    MAILBOX_IFC_ACPU_TO_CCPU_FTELL,
    MAILBOX_IFC_ACPU_TO_CCPU_RENAME,
    MAILBOX_IFC_ACPU_TO_CCPU_ACCESS,
    MAILBOX_IFC_ACPU_TO_CCPU_MKDIR,
    MAILBOX_IFC_ACPU_TO_CCPU_RMDIR,
    MAILBOX_IFC_ACPU_TO_CCPU_BASE_TEST2, //s00227525
    MAILBOX_IFC_ACPU_TO_CCPU_BASE_TEST1,  //s00227525
	MAILBOX_IFC_ACPU_TO_CCPU_PMIC_IRQEVENT,
    MAILBOX_IFC_ACPU_TO_CCPU_GET_EFUSE_TEMP_ADJUST,
    MAILBOX_IFC_ACPU_TO_CCPU_SYSTEMERROR,
    MAILBOX_IFC_ACPU_TO_CCPU_RST_MODEM,
    MAILBOX_IFC_ACPU_TO_CCPU_GET_EFUSE_DIEID,
    MAILBOX_IFC_ACPU_TO_CCPU_SET_EFUSE_CHIPID,
    MAILBOX_IFC_ACPU_TO_CCPU_GET_EFUSE_CHIPID,
    MAILBOX_IFC_ACPU_TO_CCPU_SET_EFUSE_AUTHKEY,
    MAILBOX_IFC_ACPU_TO_CCPU_GET_EFUSE_AUTHKEY,
    MAILBOX_IFC_ACPU_TO_CCPU_SET_EFUSE_DEBUGMODE,
    MAILBOX_IFC_ACPU_TO_CCPU_GET_EFUSE_DEBUGMODE,
    MAILBOX_MAILCODE_ITEM_END(ACPU, CCPU, IFC),

    /* HIFI->CCPU �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(HIFI, CCPU, MSG),
    MAILBOX_MAILCODE_HIFI_TO_CCPU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_HIFI_TO_CCPU_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ITEM_END(HIFI, CCPU, MSG),

    /* HIFI->ACPU �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(HIFI, ACPU, MSG),
    MAILBOX_MAILCODE_HIFI_TO_ACPU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_HIFI_TO_ACPU_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_HIFI_TO_ACPU_AUDIO,
    MAILBOX_MAILCODE_HIFI_TO_ACPU_MISC,
    /*Modify_for_c_reset, l00212112,20130511, starts*/
    MAILBOX_MAILCODE_HIFI_TO_ACPU_CCORE_RESET_ID,
    /*Modify_for_c_reset, l00212112,20130511, ends*/
    MAILBOX_MAILCODE_ITEM_END(HIFI, ACPU, MSG),

    /* HIFI->BBE16 �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(HIFI, BBE16, MSG),
    MAILBOX_MAILCODE_HIFI_TO_BBE16_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_HIFI_TO_BBE16_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ITEM_END(HIFI, BBE16, MSG),

    /* MCU->CCPU �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(MCU, CCPU, MSG),
    MAILBOX_MAILCODE_MCU_TO_CCPU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_MCU_TO_CCPU_VOS_MSG_URGENT,
    BSP_MAILBOX_CHANNEL_MCU_TO_CCPU_MCA_CH,
    MAILBOX_MAILCODE_ITEM_END(MCU, CCPU, MSG),

    /* MCU->CCPU ifc�ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(MCU, CCPU, IFC),
    MAILBOX_IFC_MCU_TO_CCPU_TEST_CMP, //s00227525
    MAILBOX_IFC_MCU_TO_CCPU_BASE_TEST2, //s00227525
    MAILBOX_IFC_MCU_TO_CCPU_BASE_TEST1, //s00227525
    MAILBOX_IFC_MCU_TO_CCPU_TEST,
    MAILBOX_MAILCODE_ITEM_END(MCU, CCPU, IFC),

    /* MCU->ACPU �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(MCU, ACPU, MSG),
    MAILBOX_MAILCODE_MCU_TO_ACPU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_MCU_TO_ACPU_VOS_MSG_URGENT,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_IFC_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_IFC_RESPONSE_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_SENSOR_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_TP_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_MCA_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_MNTN_CH,
    MAILBOX_IFC_MCU_TO_ACPU_HUTAF_HLT,
    /*Modify_for_c_reset, l00212112,20130511, starts*/
    MAILBOX_MAILCODE_MCU_TO_ACPU_CCORE_RESET_ID,
    /*Modify_for_c_reset, l00212112,20130511, ends*/
    MAILBOX_MAILCODE_MCU_TO_ACPU_HIFI_RESET_ID,    /*Modify_for_hifi_reset, l00249396,2013-10-14*/
    MAILBOX_MAILCODE_ITEM_END(MCU, ACPU, MSG),

    /* MCU->ACPU Զ�̺��������ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(MCU, ACPU, IFC),
    MAILBOX_IFC_MCU_TO_ACPU_TEST_CMP, //s00227525
    MAILBOX_IFC_MCU_TO_ACPU_TEST,
    MAILBOX_IFC_MCU_TO_ACPU_PRINT,
    MAILBOX_MAILCODE_ITEM_END(MCU, ACPU, IFC),

    /* BBE16 -> HIFI �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(BBE16, HIFI, MSG),
    MAILBOX_MAILCODE_BBE16_TO_HIFI_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_BBE16_TO_HIFI_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ITEM_END(BBE16, HIFI, MSG),
};

/*****************************************************************************
 ʵ �� ��  : MAILBOX_RET_ENUM
 ��������  : ����ӿڷ���ֵ
*****************************************************************************/
#define    MAILBOX_OK                       0
#define    MAILBOX_ERRO                     0xF7654321
#define    MAILBOX_FULL                     0xF7654322
#define    MAILBOX_NOT_READY                0xF7654323   /*Ŀ��CPU����δ��ʼ��*/
#define    MAILBOX_TARGET_NOT_READY         MAILBOX_NOT_READY   /*Ŀ��CPU����δ��ʼ��*/
#define    MAILBOX_TIME_OUT                 0xF7654324     /*���͵ȴ����س�ʱ*/


/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/
/*Զ�̵��÷�����������*/
#define DRV_IFC_GEN_CALL0(id, name)       _IFC_GEN_CALLx(0, id, name)
#define DRV_IFC_GEN_CALL1(id, name, ...)  _IFC_GEN_CALLx(1, id, name, __VA_ARGS__)
#define DRV_IFC_GEN_CALL2(id, name, ...)  _IFC_GEN_CALLx(2, id, name, __VA_ARGS__)
#define DRV_IFC_GEN_CALL3(id, name, ...)  _IFC_GEN_CALLx(3, id, name, __VA_ARGS__)
#define DRV_IFC_GEN_CALL4(id, name, ...)  _IFC_GEN_CALLx(4, id, name, __VA_ARGS__)
#define DRV_IFC_GEN_CALL5(id, name, ...)  _IFC_GEN_CALLx(5, id, name, __VA_ARGS__)
#define DRV_IFC_GEN_CALL6(id, name, ...)  _IFC_GEN_CALLx(6, id, name, __VA_ARGS__)

/*���ɴ�����������Զ�̵���ִ�к���*/
#define DRV_IFC_GEN_EXEC0(name)      __IFC_GEN_EXECx(0, name)
#define DRV_IFC_GEN_EXEC1(name, ...) __IFC_GEN_EXECx(1, name, __VA_ARGS__)
#define DRV_IFC_GEN_EXEC2(name, ...) __IFC_GEN_EXECx(2, name, __VA_ARGS__)
#define DRV_IFC_GEN_EXEC3(name, ...) __IFC_GEN_EXECx(3, name, __VA_ARGS__)
#define DRV_IFC_GEN_EXEC4(name, ...) __IFC_GEN_EXECx(4, name, __VA_ARGS__)
#define DRV_IFC_GEN_EXEC5(name, ...) __IFC_GEN_EXECx(5, name, __VA_ARGS__)
#define DRV_IFC_GEN_EXEC6(name, ...) __IFC_GEN_EXECx(6, name, __VA_ARGS__)

/*ע��Զ�̵���ִ�к���*/
#define MAILBOX_IFC_REG(id, name) mailbox_ifc_register_exec(id ,IFC_GEN_EXEC_NAME(name));

/*****************************************************************************
 �� �� ��  : mb_msg_cb
 ��������  : �������ݽ��մ����ص�����, Ŀ���������ʼ����ݵ���ʱ������
             �����û�ʵ�ֲ�ͨ��MAILBOX_RegisterRecvFuncע��
 �������  : UserHandle -- �û����
             MailHandle -- ������
             MailLen    -- ���ε����ʼ����ݳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : Ī�� 00176101
    �޸�����   : �����ɺ���

*****************************************************************************/
typedef void (*mb_msg_cb)(
                void                   *user_handle,
                void                   *mail_handle,
                unsigned long           mail_len);

/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : DRV_MAILBOX_SENDMAIL
 ��������  : �����û������ʼ�����
 �������  : MailCode   -- �ʱ�, ָ���ʼ�����Ŀ��
             pData      -- ָ���ʼ����ݵ�ָ��
             Length     -- ���������ݳ���, ��λbyte
 �������  : ��
 �� �� ֵ  : ��ȷ:MAILBOX_OK / ����:MAILBOX_ERRO��������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��28��
    ��    ��   : Ī�� 00176101
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned long DRV_MAILBOX_SENDMAIL(
                unsigned long           MailCode,
                void                   *pData,
                unsigned long           Length);

/*****************************************************************************
 �� �� ��  : DRV_MAILBOX_REGISTERRECVFUNC
 ��������  : ע���ʼ����ݽ��պ���
 �������  : MailCode   -- ���ݽ��պ��������Ķ����ʱ�
             pFun       -- �ʼ����ݽ��մ�������ָ��
             UserHandle -- �û�������, ���ݽ��պ���������ʱ����Ϊ���, �������
 �������  : ��
 �� �� ֵ  : ��ȷ:MAILBOX_OK / ����:MAILBOX_ERRO��������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��29��
    ��    ��   : Ī�� 00176101
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned long DRV_MAILBOX_REGISTERRECVFUNC(
                unsigned long           MailCode,
                mb_msg_cb               pFun,
                void                   *UserHandle);

/*****************************************************************************
 �� �� ��  : DRV_MAILBOX_READMAILDATA
 ��������  : �����û������ݽ��ջص������е���, �������ж�ȡһ�����ȵ�����ʼ�
 �������  : MailHandle -- ������, ���ݽ��ջص��������
             pData      -- ������������ݵĻ����ַ
             *pSize     -- ���泤��, ��λbyte, ��Ҫ���ڴ���ȡ�ʼ�����
 �������  : *pSize     -- ʵ�ʶ�ȡ����, ��λbyte
 �� �� ֵ  : ��ȷ:MAILBOX_OK / ����:MAILBOX_ERRO��������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��26��
    ��    ��   : Ī�� 00176101
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned long DRV_MAILBOX_READMAILDATA(
                void                   *MailHandle,
                unsigned char          *pData,
                unsigned long          *pSize);



/* TDS&LTE mailbox driver begin */

typedef enum tagMAILBOX_SLEEP_PROC_E
{
    EN_MAILBOX_SLEEP_WAKEUP = 0,        /* ǿ�ƻ���DSP�������� */
    EN_MAILBOX_SLEEP_WAIT,              /* DSP�Զ����Ѻ������� */
    EN_MAILBOX_SLEEP_LOST,              /* DSP����˯��ģʽʱ���������� */
    EN_MAILBOX_SLEEP_BUTT
}MAILBOX_SLEEP_PROC_E;

typedef enum tagMAILBOX_SERVICE_TYPE_E
{
    EN_MAILBOX_SERVICE_LTE_PS = 0,      /* LTE PS���� */
    EN_MAILBOX_SERVICE_LTE_CT,          /* LTE CT���� */
    EN_MAILBOX_SERVICE_LTE_BT,          /* LTE BT���� */
    EN_MAILBOX_SERVICE_LTE_OM,          /* LTE OM�������� */
    EN_MAILBOX_SERVICE_AUTO_OM,         /* �Զ�������OM�������󣬴�����ʱд���䲻���ж� */
    EN_MAILBOX_SERVICE_LTE_COEX,        /* LTE WIFI coex */
    EN_MAILBOX_SERVICE_LTE_HS_DIAG,     /* LTE ��ά�ɲ�͹����������� */

    EN_MAILBOX_SERVICE_TDS_PS,          /* TDS PS���� */
    EN_MAILBOX_SERVICE_TDS_CT,          /* TDS CT���� */
    EN_MAILBOX_SERVICE_TDS_BT,          /* TDS BT���� */
    EN_MAILBOX_SERVICE_TDS_OM,          /* TDS OM�������� */
    EN_MAILBOX_SERVICE_TDS_HS_DIAG,     /* TDS ��ά�ɲ�͹����������� */

    EN_MAILBOX_SERVICE_BUTT
}MAILBOX_SERVICE_TYPE_E;


typedef enum tagMAILBOX_INT_TYPE_E
{
    EN_MAILBOX_INT_SUBFRAME = 0,        /* ��֡�ж� */
    EN_MAILBOX_INT_COM_IPC,             /* IPC�ж� */
    EN_MAILBOX_INT_SP_IPC,              /* ר������IPC�ж� */
    EN_MAILBOX_INT_BUTT
}MAILBOX_INT_TYPE_E;


typedef enum tagMAILBOX_ERRORCODE_E
{
    ERR_MAILBOX_NOT_INIT = 1,           /* δ��ʼ�� */
    ERR_MAILBOX_PARAM_INCORRECT,        /* �������� */
    ERR_MAILBOX_MEMORY_NOTENOUGH,       /* �ռ䲻�� */
    ERR_MAILBOX_TIMEOUT,                /* ��ʱ */
    ERR_MAILBOX_COVER,                  /* ר������д����ʱԭ��δ���ߣ�ִ�и��ǲ��� */
    ERR_MAILBOX_WRITE_FAILED,           /* ����дʧ�� */
    ERR_MAILBOX_READ_FAILED,            /* �����ʧ�� */
    ERR_MAILBOX_READ_NULL,              /* �����������Ϣ */
    ERR_MAILBOX_DSP_POWERDOWN,          /* DSP���ڵ͹���״̬ */
    ERR_MAILBOX_OTHER,                  /* �������� */
    ERR_MAILBOX_ERRORCODE_BUTT
}MAILBOX_ERRORCODE_E;


/*****************************************************************************
 Prototype      : BSP_MailBox_ComMsgInit
 Description    : ͨ������ĳ�ʼ��(�ṩ��Э��ջ���ã�
                  �ӿ��ڲ�ʵ����DSP������Ϣ�ĳ�ʼ��)
 Input          : None
 Return Value   : None
*****************************************************************************/
BSP_VOID BSP_MailBox_ComMsgInit(BSP_VOID);


/*****************************************************************************
 Prototype      : BSP_MailBox_IsDspOk
 Description    : ��DSP�����ֺ������ж�DSP�Ƿ��ʼ������
                  (�ṩ��Э��ջ���ã�������ֲ��ɹ���Э��ջ��Ҫѭ����ε���)
 Input          : None
 Return Value   : BSP_TRUE: DSP��ʼ�����������ֳɹ�
                  BSP_FALSE:DSPû�г�ʼ�����������ֲ��ɹ�
*****************************************************************************/
BSP_BOOL BSP_MailBox_IsDspOk(BSP_VOID);

/*****************************************************************************
 Prototype       : BSP_MailBox_ComMsgWrite
 Description     : ����д�ӿ�(ÿ��ֻ֧��дһ��ԭ��)
 Input           : enMbxType    �����ҵ������
                   pData        ����ָ��
                   ulLen        ���ݳ���(���ֽ�Ϊ��λ)
                   enProcType   DSP˯��ʱ�Ĵ�������
 Output          : None.
 Return Value    : BSP_OK: �ɹ�
                   ����: ʧ��
*****************************************************************************/
BSP_U32 BSP_MailBox_ComMsgWrite(MAILBOX_SERVICE_TYPE_E enMbxType,
                               BSP_VOID* pData,
                               BSP_U32 ulLen,
                               MAILBOX_SLEEP_PROC_E enProcType);

typedef BSP_VOID (*BSP_MBX_NOTIFY_FUNC)(MAILBOX_INT_TYPE_E enIntType);

/*****************************************************************************
 Prototype       : BSP_MailBox_ComNotifyReg
 Description     : �������ݵ���֪ͨע��ӿڣ���֡�жϼ�ʹû����ҲҪ�ص���
 param           : enMbxType        �����ҵ������
                   pFun             �������ݵ��ﴦ������
 Return Value    : BSP_OK: �ɹ�
                   ERR_MAILBOX_NOT_INIT
                   ERR_MAILBOX_PARAM_INCORRECT
*****************************************************************************/
BSP_U32 BSP_MailBox_ComNotifyReg(MAILBOX_SERVICE_TYPE_E enMbxType,
                                BSP_MBX_NOTIFY_FUNC pFun);

/*****************************************************************************
 Prototype       : BSP_MailBox_IntTypeSet
 Description     : ����PS�����ж�Դ�ӿ�(Ĭ��IPC�жϷ�ʽ)
                   ֻ����PS���䣬OM�������ж��ϱ�
 param           : None
 Return Value    : 0: �ɹ�; ����: ���õ�type�Ƿ�
*****************************************************************************/
BSP_U32 BSP_MailBox_IntTypeSet(MAILBOX_INT_TYPE_E enIntType);

/*****************************************************************************
 Prototype       : BSP_MailBox_ComMsgSize
 Description     : ��ȡͨ�������е�һ��ԭ��ĳ���
                   (�ṩ���ϲ���ã��������ṩ������ԭ�������ӿڣ���Ҫ�ϲ�ѭ��
                   �����Ա����ϲ�©���ж�֪ͨʱ���������ԭ�ﻺ��)
 param           : enMbxType        �����ҵ������
 Return Value    : 0:  û�л�ȡԭ�����Ϊ�գ������������͵�ԭ��δ���ߣ�
                   ����ֵ: �����һ��ԭ��ĳ���
*****************************************************************************/
BSP_U32 BSP_MailBox_ComMsgSize(MAILBOX_SERVICE_TYPE_E enMbxType);

/*****************************************************************************
 Prototype       : BSP_MailBox_ComMsgRead
 Description     : ������ӿ�
                   (�˽ӿڻỽ��DSP����ҪBSP_MailBox_ComMsgSize���طǿ�ʱ����)
 param           : enMbxType    �����ҵ������
                   pData        ���յ����ݻ�����ָ��(�洢ԭ����Ϣ��������ԭ�ﳤ��)
                   ulLen        pData��������size(���ֽ�Ϊ��λ)
                   enProcType   DSP˯��ʱ�Ĵ�������
 Return Value    : 0 : �ɹ�
                   ���� : ʧ��
*****************************************************************************/
BSP_U32 BSP_MailBox_ComMsgRead(MAILBOX_SERVICE_TYPE_E enMbxType,
                              BSP_VOID* pData,
                              BSP_U32 ulLen,
                               MAILBOX_SLEEP_PROC_E enProcType);


/*****************************************************************************
 Prototype      : BSP_MailBox_SpULMsgHeadInit
 Description    : ר�У�Special Mailbox�������������Ϣͷ��ʼ���ӿ�
                  (��ʼ����������ÿ��ԭ�����Ϣͷ���ṩ��Э��ջ����Ҫ���ö��
                  �ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
 Input          :
                ulAddr : ר������ĵ�ַ
                ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
                ucData : ��ʼֵ
 Return Value   None
*****************************************************************************/
BSP_VOID BSP_MailBox_SpULMsgHeadInit(BSP_U32 ulAddr,
                                 BSP_U32 ulSize,
                                 BSP_U8 ucData);

/*****************************************************************************
 Prototype      : BSP_MailBox_SpDLMsgHeadInit
 Description    : ר�У�Special Mailbox�������������Ϣͷ��ʼ���ӿ�
                  (��ʼ����������ÿ��ԭ�����Ϣͷ���ṩ��Э��ջ����Ҫ���ö��
                  �ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
 Input          :
                ulAddr : ר������ĵ�ַ
                ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
                ucData : ��ʼֵ
 Return Value   None
*****************************************************************************/
BSP_VOID BSP_MailBox_SpDLMsgHeadInit(BSP_U32 ulAddr,
                                 BSP_U32 ulSize,
                                 BSP_U8 ucData);

/*****************************************************************************
 Prototype      : BSP_MailBox_SpMsgWrite
 Description    : ר�����䣨Special Mailbox����д�ӿ�
                  (�ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
 Input          :
                ulAddr : ר�������ƫ�Ƶ�ַ������Ϣͷ��ʼ�ĵ�ַ��
                ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
                pData  : ������Ϣ(��������Ϣͷ��Ϣ)
 Return Value   :
                BSP_OK: ��ʾ�����ɹ�
                ERR_MAILBOX_COVER: ��ʾǰһ��ԭ��δ�����ߣ�����
                ERR_MAILBOX_WRITE_FAILED: дʧ��
                ERR_MAILBOX_NOT_INIT: ����δ��ʼ��
                ERR_MAILBOX_PARAM_INCORRECT: ��������
*****************************************************************************/
BSP_U32 BSP_MailBox_SpMsgWrite(BSP_U32 ulAddr,
                               BSP_U32 ulSize,
                               BSP_VOID* pData);

/*****************************************************************************
 Prototype      : BSP_MailBox_SpMsgRead
 Description    : ר�����䣨Special Mailbox���Ķ��ӿ�
                  (�ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
 Input          :
                ulAddr : ר�������ƫ�Ƶ�ַ������Ϣͷ��ʼ�ĵ�ַ��
                ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
                pData  : ������Ϣ(��������Ϣͷ��Ϣ)
 Return Value   :
                BSP_OK: ��ȡ�ɹ�
                ERR_MAILBOX_READ_NULL: ������
                ERR_MAILBOX_NOT_INIT: ����δ��ʼ��
                ERR_MAILBOX_PARAM_INCORRECT: ��������
*****************************************************************************/
BSP_U32 BSP_MailBox_SpMsgRead(BSP_U32 ulAddr,
                              BSP_U32 ulSize,
                              BSP_VOID* pData);

/*****************************************************************************
 Prototype       : BSP_MailBox_SpNotifyReg
 Description     : ר���������ݵ���֪ͨע��ӿ�
 param           : pFun             �������ݵ��ﴦ������
 Return Value    : BSP_OK: �ɹ�
                   ����: ʧ��
*****************************************************************************/
BSP_U32 BSP_MailBox_SpNotifyReg(BSP_MBX_NOTIFY_FUNC pFun);

/*****************************************************************************
 Prototype       : BSP_MailBox_SpNotifyEnable
 Description     : ר���������ݵ���֪ͨ�ж�ʹ�ܽӿ�
 param           : None
 Return Value    : void
*****************************************************************************/
BSP_VOID BSP_MailBox_SpNotifyEnable(BSP_VOID);

/*****************************************************************************
 Prototype       : BSP_MailBox_SpNotifyDisable
 Description     : ר���������ݵ���֪ͨ�ж�ȥʹ�ܽӿ�
 param           : None
 Return Value    : void
*****************************************************************************/
BSP_VOID BSP_MailBox_SpNotifyDisable(BSP_VOID);


/*****************************************************************************
 Prototype       : BSP_Mailbox_ForbidDspSleep
 Description     : ��ֹDSP˯�߽ӿ�
 Input           : enProcType     DSP˯��ʱ�Ĵ�������
                    EN_MAILBOX_SLEEP_WAKEUP : ǿ�ƻ���ʱ���еȴ�������
                                              �������жϻص�������˲���
                                              ֻ��������������˲���
                    EN_MAILBOX_SLEEP_LOST   : �жϻص��������ж�������˲���

 Return Value    : BSP_OK: �ɹ�,DSP��ǰû˯�ߣ��������ý�ֹDSP����˯��
                   ERR_MAILBOX_DSP_POWERDOWN : ������ΪEN_MAILBOX_SLEEP_LOST,
                                               DSP��ǰ���ڵ͹���״̬,����ʧ��
                   ERR_MAILBOX_TIMEOUT       : ������ΪEN_MAILBOX_SLEEP_WAKEUP,
                                               ����DSP��ʱ(10s)
*****************************************************************************/
BSP_U32 BSP_Mailbox_ForbidDspSleep(MAILBOX_SLEEP_PROC_E enProcType);


/*****************************************************************************
 Prototype       : BSP_Mailbox_AllowDspSleep
 Description     : ����DSP˯�߽ӿ�
 Input           : None
 Return Value    : None
*****************************************************************************/
BSP_VOID BSP_Mailbox_AllowDspSleep(BSP_VOID);



typedef BSP_BOOL (*BSP_MBX_GET_STATUS_FUNC)(void);

/*****************************************************************************
 Prototype       : BSP_MailBox_GetDspStatusReg
 Description     : ��ȡDSP˯��״̬�ص�����ע��ӿڣ��͹���ģ�����
 param           : pFun             ��ȡDSP˯��״̬��������
 Return Value    : BSP_VOID
*****************************************************************************/
BSP_VOID BSP_MailBox_GetDspStatusReg(BSP_MBX_GET_STATUS_FUNC pFun);


typedef BSP_VOID (*BSP_MBX_DSP_AWAKE_FUNC)(void);

/*****************************************************************************
 Prototype       : BSP_MailBox_DspForceAwakeReg
 Description     : DSPǿ�ƻ��ѻص�����ע��ӿڣ��͹���ģ�����
 param           : pFun             DSPǿ�ƻ��Ѵ�������
 Return Value    : BSP_VOID
*****************************************************************************/
BSP_VOID BSP_MailBox_DspForceAwakeReg(BSP_MBX_DSP_AWAKE_FUNC pFun);


/*****************************************************************************
 Prototype       : BSP_MailBox_GetSpMsgStatusReg
 Description     : ��ȡר����������DSP˯��״̬�ص�����ע��ӿڣ�PS����
 param           : pFun             ��ȡDSP˯��״̬��������
 Return Value    : BSP_VOID
*****************************************************************************/
BSP_VOID BSP_MailBox_GetSpMsgStatusReg(BSP_MBX_GET_STATUS_FUNC pFun);


/*****************************************************************************
 Prototype       : BSP_MailBox_DspAwakeProc
 Description     : DSP���Ѻ�����䴦���ӿڣ��͹���ģ�����
 param           : BSP_VOID
 Return Value    : BSP_VOID
*****************************************************************************/
BSP_VOID BSP_MailBox_DspAwakeProc(BSP_VOID);

/*****************************************************************************
 Prototype       : BSP_MailBox_IsAllowDspSleep
 Description     : ��ѯ�Ƿ�����DSP˯�ߵĴ����ӿڣ��͹���ģ�����
                    ���ô˽ӿ�ʱ�͹���ģ�鱣֤DSPδ˯��
                    �˽ӿ�ֻ���PS�����ר�����䣬�����OM����(OMԭ����ʱ��Ҫ��)
 param           : BSP_VOID
 Return Value    : BSP_BOOL: TRUE-allow;FALSE-forbid
*****************************************************************************/
BSP_BOOL BSP_MailBox_IsAllowDspSleep(BSP_VOID);

/*****************************************************************************
 Prototype       : BSP_UniMailboxWrite
 Description     : �����ͨ��д�ӿ�(�ɵ����߱�֤����ĵ�ַ�ĺϷ���)
                   ���ӿ�ʵ������memcpy����������
                   �ӿ��ڲ���֤DSP�Ļ��Ѳ������������ʧ�ܣ�����ERR_MAILBOX_TIMEOUT
 Return Value    : 
                   BSP_OK
                   ERR_MAILBOX_PARAM_INCORRECT
                   ERR_MAILBOX_TIMEOUT
*****************************************************************************/
BSP_U32 BSP_UniMailboxWrite(BSP_VOID *pDst, BSP_VOID *pSrc, BSP_U32 ulLen);

/* TDS&LTE mailbox driver end */



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of drv_mailbox.h */

