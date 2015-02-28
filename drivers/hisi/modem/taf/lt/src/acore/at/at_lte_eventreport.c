/******************************************************************************
/*
/*                  ��Ȩ���� (C), 1998-2009, ��Ϊ�������޹�˾
/*
/******************************************************************************
/*  �� �� ��   : at_lte_eventreport.c
/*  �� �� ��   : V1.0
/*  ��    ��   : ������/00184452
/*  ��������   : 2011-10-22
/*  ��������   : LTE�����ϱ�����
/*
/*  �����б�   : TODO: ...
/*  �޸���ʷ   :
/*  1.��    �� : 2011-10-22
/*    ��    �� : ������/00184452
/*    �޸����� : �����ļ�
/*
/******************************************************************************

#include "osm.h"
#include "gen_msg.h"
#include "msp_at.h"
#include "at_lte_common.h"
#include "ATCmdProc.h"
//#include "AtNdisInterface.h"
//#include "AtDataProc.h"
//#include "AtDataProc.h"


#include "AtParse.h"/*Ϊ����MnClient.h
#include "gen_common.h"
#include "at_common.h"
#include "AtCtx.h"
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e767 ԭ��:Log��ӡ*/
/* ��������: atCsqInfoIndProc
/* ��������: ����CSQ�����ϱ���Ϣ
/*
/* ����˵��: pMsgBlock��MSP MSG��Ϣ�ṹ
/*
/* �� �� ֵ:
/*
/* ����Ҫ��: TODO: ...
/* ���þ���: TODO: ...
/* ��    ��: ������00184452 [2010-10-10]
/******************************************************************************
/*����V1�е�#define MSP_HAVE_AT_RSSI_REPORT�޸ĵ�
VOS_UINT32 atCsqInfoIndProc(VOS_VOID *pMsgBlock)
{
    L4A_CSQ_INFO_IND_STRU* pCsqInfo = NULL;
    VOS_UINT16 usLength = 0;
    VOS_INT16 ulRssi = 0;

    pCsqInfo = (L4A_CSQ_INFO_IND_STRU*)pMsgBlock;

    if(ERR_MSP_SUCCESS == pCsqInfo->ulErrorCode)
    {
        if(AT_RSSI_UNKNOWN == pCsqInfo->sRssi)
        {
            ulRssi = AT_RSSI_UNKNOWN;
        }
        else if(pCsqInfo->sRssi >= AT_RSSI_HIGH)
        {
            ulRssi = AT_CSQ_RSSI_HIGH;
        }
        else if(pCsqInfo->sRssi <= AT_RSSI_LOW)
        {
            ulRssi = AT_CSQ_RSSI_LOW;
        }
        else
        {
            ulRssi = (pCsqInfo->sRssi - AT_RSSI_LOW) / 2;
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,
                            (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,"%s%s%d%s",
                            gaucAtCrLf, "^RSSI:", ulRssi, gaucAtCrLf);
        At_SendResultData(AT_BROADCAST_CLIENT_INDEX_MODEM_0,pgucLAtSndCodeAddr,usLength);

    }

}

#define AT_ANTENNA_LEVEL_NUM        3
VOS_UINT8         g_ATAntennaLevel[AT_ANTENNA_LEVEL_NUM];
VOS_UINT8         g_ulAntennaLevel = 0;

VOS_UINT32       g_ATE5Order = 0;

VOS_UINT8 AT_CalculateLTEAntennaLevel(
    VOS_INT16                           usRsrp
)
{
	VOS_INT16 usLevel = 0;
       g_ATE5Order =4;
	/*���߸�ʽ��ʾ����
	if ( usRsrp <= g_stRsrpCfg.ssValue[3])
	{
		usLevel = AT_CMD_ANTENNA_LEVEL_4;
	}
	else if (( g_stRsrpCfg.ssValue[3] < usRsrp) && (usRsrp <= g_stRsrpCfg.ssValue[2]))
	{
		usLevel = AT_CMD_ANTENNA_LEVEL_3;
	}
	else if (( g_stRsrpCfg.ssValue[2] < usRsrp) && (usRsrp <= g_stRsrpCfg.ssValue[1]))
	{
		usLevel = AT_CMD_ANTENNA_LEVEL_2;
	}
	else
	{
		usLevel = AT_CMD_ANTENNA_LEVEL_1;
	}
	return (VOS_UINT8)usLevel;

}

VOS_UINT8 AT_GetSmoothLTEAntennaLevel(
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel
)
{
    VOS_UINT8                               i;
    g_ATE5Order =5;
    /* ����ʱ ��������  */
    if ( AT_CMD_ANTENNA_LEVEL_0 == enLevel )
    {
        g_ulAntennaLevel = enLevel;

        MSP_MEMSET( g_ATAntennaLevel, 0, sizeof(g_ATAntennaLevel) );
        return g_ulAntennaLevel;
    }

    /* �������з���״̬  ��������  */
    if ( AT_CMD_ANTENNA_LEVEL_0 == g_ulAntennaLevel )
    {
        g_ulAntennaLevel = enLevel;

        MSP_MEMSET( g_ATAntennaLevel, 0, sizeof(g_ATAntennaLevel) );
        g_ATAntennaLevel[AT_ANTENNA_LEVEL_NUM-1] = enLevel;
        return g_ulAntennaLevel;
    }

    /* ���ϴε��źŸ����Ƚ�, �仯�Ƚϴ�(����1��)���������� */
    if ( enLevel > (g_ulAntennaLevel + 1) )
    {
        g_ulAntennaLevel = enLevel;

        MSP_MEMSET( g_ATAntennaLevel, 0, sizeof(g_ATAntennaLevel) );
        g_ATAntennaLevel[AT_ANTENNA_LEVEL_NUM-1] = enLevel;
        return g_ulAntennaLevel;
    }
    else if (( enLevel + 1) < g_ulAntennaLevel )
    {
        g_ulAntennaLevel = enLevel;

        MSP_MEMSET( g_ATAntennaLevel, 0, sizeof(g_ATAntennaLevel) );
        g_ATAntennaLevel[AT_ANTENNA_LEVEL_NUM-1] = enLevel;
        return g_ulAntennaLevel;
    }
    else
    {
      /* Do nothing... */
    }

    /* �Ƚ��ȳ������3�εĲ�ѯ��� */
    for ( i=0; i<AT_ANTENNA_LEVEL_NUM-1; i++ )
    {
         g_ATAntennaLevel[i] = g_ATAntennaLevel[i+1];
    }
    g_ATAntennaLevel[i] = enLevel;


    /* ���������򲻸��£��Դﵽƽ����Ч�� */
    for ( i=0; i<AT_ANTENNA_LEVEL_NUM-1; i++ )
    {
        if (g_ATAntennaLevel[i]  != g_ATAntennaLevel[i+1] )
        {
            return g_ulAntennaLevel;
        }
    }

    /* �źŸ����ȶ��� AT_ANTENNA_LEVEL_MAX_NUM ��ʱ�������� */
    g_ulAntennaLevel = enLevel;
	return g_ulAntennaLevel;
}

VOS_UINT32 at_CsqInfoProc(VOS_VOID *pMsgBlock,AT_ANLEVEL_INFO_CNF_STRU* pAnlevelAnqueryInfo)
{
    VOS_UINT32 ulResult = ERR_MSP_SUCCESS;
    L4A_CSQ_INFO_IND_STRU* pCsqInfo = NULL;
    VOS_UINT16                          usRsrp;
    VOS_UINT8 							enCurAntennaLevel;
    g_ATE5Order =2;

    if((NULL == pMsgBlock)||(NULL == pAnlevelAnqueryInfo))
    {
        HAL_SDMLOG("pMsgBlock is NULL!\n");
        return AT_ERROR;
    }
    pCsqInfo = (L4A_CSQ_INFO_IND_STRU*)pMsgBlock;
    pAnlevelAnqueryInfo->usClientId= pCsqInfo->usClientId;
    pAnlevelAnqueryInfo->ulErrorCode = pCsqInfo->ulErrorCode;

    /*RSSI ��ʽ��ʾ����
    if(AT_RSSI_UNKNOWN == pCsqInfo->sRssi)
    {
        pAnlevelAnqueryInfo->sRssi = AT_RSSI_UNKNOWN;
    }
    else if(pCsqInfo->sRssi >= AT_RSSI_HIGH)
    {
        pAnlevelAnqueryInfo->sRssi = AT_CSQ_RSSI_HIGH;
    }
    else if(pCsqInfo->sRssi <= AT_RSSI_LOW)
    {
        pAnlevelAnqueryInfo->sRssi = AT_CSQ_RSSI_LOW;
    }
    else
    {
        pAnlevelAnqueryInfo->sRssi = ( VOS_UINT16)((pCsqInfo->sRssi - AT_RSSI_LOW) / 2);
    }

	/* �ϱ�����ת��:�� Rscp��Ecio��ʾΪ�Ǹ�ֵ����Rscp��EcioΪ-145��-32������rssiΪ99��
       ��ת��Ϊ0 */
    if ( (AT_RSSI_UNKNOWN  == pCsqInfo->sRsrp)|| (AT_RSSI_UNKNOWN == pCsqInfo->sRssi) )
    {
        /* ��������0, ��ӦӦ�õ�Ȧ�� */
        enCurAntennaLevel       = AT_CMD_ANTENNA_LEVEL_0;
    }
    else
    {
    	 /* ȡ����ֵ */
    	usRsrp                    = ( VOS_UINT16)(-(pCsqInfo->sRsrp));
	    /* ���ú���AT_CalculateAntennaLevel������D25�㷨������źŸ��� */
        enCurAntennaLevel = AT_CalculateLTEAntennaLevel((VOS_INT16)usRsrp);
    }

    /* �źŴ��ʹ��� */
    pAnlevelAnqueryInfo->sLevel = AT_GetSmoothLTEAntennaLevel( enCurAntennaLevel );

	pAnlevelAnqueryInfo->sRsrp = pCsqInfo->sRsrp;
	pAnlevelAnqueryInfo->sRsrq = pCsqInfo->sRsrq;

	return ulResult;
}

VOS_UINT32 atAnlevelInfoIndProc(VOS_VOID *pMsgBlock)
{
  VOS_UINT16 usLength = 0;
  VOS_UINT32 ulResult =0;
  VOS_UINT16 usRsrp=0;
  VOS_UINT16 usRsrq=0;
  AT_ANLEVEL_INFO_CNF_STRU stAnlevelAnqueryInfo = {0};
  g_ATE5Order =3;

  ulResult = at_CsqInfoProc(pMsgBlock,&stAnlevelAnqueryInfo);

  {
    usRsrp = (VOS_UINT16)((stAnlevelAnqueryInfo.sRsrp == 99)?99:(-(stAnlevelAnqueryInfo.sRsrp)));
    usRsrq = (VOS_UINT16)((stAnlevelAnqueryInfo.sRsrq == 99)?99:(-(stAnlevelAnqueryInfo.sRsrq)));

  	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,
						  (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,"%s%s0,99,%d,%d,%d,%d%s",
						  gaucAtCrLf, "^ANLEVEL:",
						  stAnlevelAnqueryInfo.sRssi,
						  stAnlevelAnqueryInfo.sLevel,
						  usRsrp,
						  usRsrq,gaucAtCrLf);
    At_SendResultData(AT_CLIENT_TAB_APP_INDEX,pgucLAtSndCodeAddr,usLength);
  }
  else
  {
    HAL_SDMLOG("ulResult = %d,\n",(VOS_INT)ulResult);
  }

  return AT_FW_CLIENT_STATUS_READY;
}

VOS_UINT32 atSetAnlevelCnfSameProc(VOS_VOID *pMsgBlock)
{
	VOS_UINT16 usLength = 0;
	VOS_UINT32 ulResult =0;
    VOS_UINT16 usRsrp=0;
    VOS_UINT16 usRsrq=0;

	AT_ANLEVEL_INFO_CNF_STRU stAnlevelAnqueryInfo = {0};
     g_ATE5Order =1;

    ulResult = at_CsqInfoProc(pMsgBlock,&stAnlevelAnqueryInfo);

	if(ERR_MSP_SUCCESS == ulResult)
  	{
        usRsrp = (VOS_UINT16)((stAnlevelAnqueryInfo.sRsrp == 99)?99:(-(stAnlevelAnqueryInfo.sRsrp)));
        usRsrq = (VOS_UINT16)((stAnlevelAnqueryInfo.sRsrq == 99)?99:(-(stAnlevelAnqueryInfo.sRsrq)));

  		usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,
						  (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,"%s%s0,99,%d,%d,%d,%d%s",
						  gaucAtCrLf, "^ANQUERY:",
						  stAnlevelAnqueryInfo.sRssi,
						  stAnlevelAnqueryInfo.sLevel,
						  usRsrp,
						  usRsrq,gaucAtCrLf);
  	}
  	else
  	{
  	      HAL_SDMLOG(" atSetAnlevelCnfSameProc ulResult = %d,\n",(VOS_INT)ulResult);
  	}

	CmdErrProc((VOS_UINT8)(stAnlevelAnqueryInfo.usClientId), stAnlevelAnqueryInfo.ulErrorCode,
						usLength, pgucLAtSndCodeAddr);

	return AT_FW_CLIENT_STATUS_READY;
}


/******************************************************************************
/* ��������: atSetCsqCnfProc
/* ��������: ����SET CSQ����ظ���Ϣ
/*
/* ����˵��: pMsgBlock��MSP MSG��Ϣ�ṹ
/*
/* �� �� ֵ:
/*
/* ����Ҫ��: TODO: ...
/* ���þ���: TODO: ...
/* ��    ��: ������00184452 [2010-10-10]
/******************************************************************************

/*���������AT������еĺ���������ͬ���ǲ���Ҫ���¸�����
VOS_UINT32 atSetCsqCnfSameProc(VOS_VOID *pMsgBlock)
{
    L4A_CSQ_INFO_CNF_STRU * pstSetCsqCnf = NULL;
    VOS_UINT8 ucRssiValue = 0;
    VOS_UINT8 ucChannalQual = 0;

    VOS_UINT16 usLength = 0;

    pstSetCsqCnf = (L4A_CSQ_INFO_CNF_STRU*)pMsgBlock;

    if(ERR_MSP_SUCCESS == pstSetCsqCnf->ulErrorCode)
    {
        if(AT_RSSI_UNKNOWN == pstSetCsqCnf->sRssi)
        {
            ucRssiValue = AT_RSSI_UNKNOWN;
        }
        else if(pstSetCsqCnf->sRssi >= AT_RSSI_HIGH)
        {
            ucRssiValue = AT_CSQ_RSSI_HIGH;
        }
        else if(pstSetCsqCnf->sRssi <= AT_RSSI_LOW)
        {
            ucRssiValue = AT_CSQ_RSSI_LOW;
        }
        else
        {
            ucRssiValue = (VOS_UINT8)((pstSetCsqCnf->sRssi - AT_RSSI_LOW) / 2);
        }

        ucChannalQual = AT_BER_UNKNOWN;
    }
    else
    {
        ucRssiValue   = AT_RSSI_UNKNOWN;
        ucChannalQual = AT_BER_UNKNOWN;
    }

    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucLAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
                                                    "%s: %d,%d%s",
                                                    "+CSQ",
                                                    ucRssiValue,
                                                    ucChannalQual,
                                                    gaucAtCrLf);

    CmdErrProc((VOS_UINT8)(pstSetCsqCnf->usClientId), ERR_MSP_SUCCESS, usLength, pgucLAtSndCodeAddr);

    return AT_FW_CLIENT_STATUS_READY;
}

VOS_UINT32 atCerssiInfoIndProc(VOS_VOID *pMsgBlock)
{
    L4A_CSQ_INFO_IND_STRU * pCerssi = NULL;
    VOS_UINT16 usLength = 0;

    pCerssi = (L4A_CSQ_INFO_IND_STRU*)pMsgBlock;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,
                            (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,"%s%s0,0,255,%d,%d,%d,%d,%d,%d%s",
                            gaucAtCrLf, "^CERSSI:",pCerssi->sRsrp,pCerssi->sRsrq,pCerssi->lSINR,
                            pCerssi->stCQI.usRI,pCerssi->stCQI.ausCQI[0],pCerssi->stCQI.ausCQI[1],gaucAtCrLf);

    At_SendResultData(AT_BROADCAST_CLIENT_INDEX_MODEM_0,pgucLAtSndCodeAddr,usLength);

    return AT_FW_CLIENT_STATUS_READY;
}

VOS_UINT32 atCerssiInfoCnfProc(VOS_VOID *pMsgBlock)
{
    L4A_CSQ_INFO_CNF_STRU * pCerssi = NULL;
    VOS_UINT16 usLength = 0;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;


    /* ͨ��clientid��ȡindex */

}

/* ��������: atSysModeIndProc
/* ��������: ����SYSMODE�����ϱ���Ϣ
/*
/* ����˵��: pMsgBlock��MSP MSG��Ϣ�ṹ
/*
/* �� �� ֵ:
/*
/* ����Ҫ��: TODO: ...
/* ���þ���: TODO: ...
/* ��    ��: ������00184452 [2010-10-10]
/******************************************************************************

VOS_UINT32 atSysModeIndProc(VOS_VOID *pMsgBlock)
{
#if 0
    L4A_MODE_IND_STRU * pMode = NULL;
    VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pMode = (L4A_MODE_IND_STRU*)pEvent->ulParam1;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,
                        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,"%s%s%d%s",
                        gaucAtCrLf, "^MODE:", pMode->ulMode, gaucAtCrLf);

    At_SendResultData(AT_BROADCAST_CLIENT_INDEX_MODEM_0,pgucLAtSndCodeAddr,usLength);
#endif
    return AT_FW_CLIENT_STATUS_READY;
}


/*****************************************************************************
 �� �� ��  : atLwclashCnfProc
 ��������  : ^LWCLASH����Ӧ����
 �������  : VOS_VOID *pMsgBlock
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��25��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 atLwclashCnfProc(VOS_VOID *pMsgBlock)
{
    L4A_READ_LWCLASH_CNF_STRU *pstLwclash = NULL;
    VOS_UINT16 usLength = 0;

    pstLwclash = (L4A_READ_LWCLASH_CNF_STRU *)pMsgBlock;

    usLength = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucLAtSndCodeAddr,
                (VOS_CHAR *)pgucLAtSndCodeAddr,
                "^LWCLASH: %d,%d,%d,%d,%d,%d",
                pstLwclash->stLwclashInfo.enState,
                pstLwclash->stLwclashInfo.usUlFreq, pstLwclash->stLwclashInfo.usUlBandwidth,
                pstLwclash->stLwclashInfo.usDlFreq, pstLwclash->stLwclashInfo.usDlBandwidth,
                pstLwclash->stLwclashInfo.usBand);

    CmdErrProc((VOS_UINT8)(pstLwclash->usClientId), pstLwclash->ulErrorCode, usLength, pgucLAtSndCodeAddr);

    return AT_FW_CLIENT_STATUS_READY;
}

VOS_UINT32 atQryCnmrCnfProc(VOS_VOID *pMsgBlock)
{
    L4A_READ_CNMR_CNF_STRU *pstCnf = NULL;
    VOS_UINT16 usLength = 0;
    VOS_UINT32 ulIndexTotal = 0;
    VOS_UINT32 ulIndexN = 0;
    VOS_UINT32 i=0;
    VOS_UCHAR * pChar = NULL;

    pstCnf = (L4A_READ_CNMR_CNF_STRU *)pMsgBlock;

    if(ERR_MSP_SUCCESS != pstCnf->ulErrorCode)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                    (VOS_CHAR *)pgucLAtSndCodeAddr,
                    (VOS_CHAR *)pgucLAtSndCodeAddr+ usLength,"%s^CNMR:%d,%d",
                    gaucAtCrLf,ulIndexTotal,ulIndexN);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                    (VOS_CHAR *)pgucLAtSndCodeAddr,
                    (VOS_CHAR *)pgucLAtSndCodeAddr+ usLength,"%s^CNMR:%d,%d",
                    gaucAtCrLf,ulIndexTotal+1,ulIndexN+1);
    }

    if(ERR_MSP_SUCCESS == pstCnf->ulErrorCode)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                        (VOS_CHAR *)pgucLAtSndCodeAddr,
                        (VOS_CHAR *)pgucLAtSndCodeAddr+ usLength,",");

        pChar = ((VOS_UCHAR*)&(pstCnf->stLteCelInfo));

        for(i =0;i<sizeof(L4A_READ_CNMR_CNF_STRU)-12-4;i++)
        {
            /*lint -e661*/
                        (VOS_CHAR *)pgucLAtSndCodeAddr,
                        (VOS_CHAR *)pgucLAtSndCodeAddr+ usLength,"%02x",
                        *(pChar+i));
			/*lint -e661*/
    }

    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucLAtSndCodeAddr,
                (VOS_CHAR *)pgucLAtSndCodeAddr+ usLength,"%s",
                 gaucAtCrLf);

    CmdErrProc((VOS_UINT8)(pstCnf->usClientId), ERR_MSP_SUCCESS, usLength, pgucLAtSndCodeAddr);

    return AT_FW_CLIENT_STATUS_READY;
}



VOS_UINT32 atQryCellIdCnfProc(VOS_VOID *pMsgBlock)
{
    L4A_READ_CELL_ID_CNF_STRU *pstCnf = NULL;
    VOS_UINT16 usLength = 0;

    pstCnf = (L4A_READ_CELL_ID_CNF_STRU *)pMsgBlock;

    usLength = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucLAtSndCodeAddr,
                (VOS_CHAR *)pgucLAtSndCodeAddr,
                ((2 == pstCnf->usMncNum)?"%s^CECELLID: %03x%02x,%d,%d,%d%s":"%s^CECELLID: %03x%03x,%d,%d,%d%s"),
                gaucAtCrLf,
                pstCnf->usMCC,
                (2 == pstCnf->usMncNum)?(pstCnf->usMNC&0xff):pstCnf->usMNC,
                pstCnf->ulCi,
                pstCnf->usPci,
                pstCnf->usTAC,
                gaucAtCrLf);

    CmdErrProc((VOS_UINT8)(pstCnf->usClientId), ERR_MSP_SUCCESS, usLength, pgucLAtSndCodeAddr);

    return AT_FW_CLIENT_STATUS_READY;
}

VOS_UINT32 g_ulCellNum =0;
VOS_UINT32 atQryCellInfoCnfProc(VOS_VOID *pMsgBlock)
{
    L4A_READ_CELL_INFO_CNF_STRU *pstcnf = NULL;
    VOS_UINT16 usLength = 0;
    VOS_UINT32 i =0;

    pstcnf = (L4A_READ_CELL_INFO_CNF_STRU *)pMsgBlock;

    if(0 != pstcnf->ulErrorCode)
    {
        CmdErrProc((VOS_UINT8)(pstcnf->usClientId), pstcnf->ulErrorCode, 0, NULL);

        return AT_FW_CLIENT_STATUS_READY;
    }

    if(0 == pstcnf->stNcellListInfo.enCellFlag)
    {
        usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucLAtSndCodeAddr,
                (VOS_CHAR *)pgucLAtSndCodeAddr+usLength,
                "%d:%d,%d,%d%s",
                1,
                EN_SERVICE_CELL_ID,
                pstcnf->stNcellListInfo.stSevCellInfo.stCellMeasInfo[0].stMeasRslt.usPhyCellId,
                pstcnf->stNcellListInfo.stSevCellInfo.stCellMeasInfo[0].stMeasRslt.sRssi,
                gaucAtCrLf);
    }
    else
    {
        /*ͬƵ*/
        for( i =0; i< pstcnf->stNcellListInfo.stIntraFreqNcellList.ulNCellNumber ;i++)
        {
            g_ulCellNum ++;
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucLAtSndCodeAddr,
                (VOS_CHAR *)pgucLAtSndCodeAddr+usLength,
                "%d:%d,%d,%d%s",
                g_ulCellNum,
                EN_SYN_FREQ_CELL_ID,
                pstcnf->stNcellListInfo.stIntraFreqNcellList.stCellMeasInfo[i].stMeasRslt.usPhyCellId,
                pstcnf->stNcellListInfo.stIntraFreqNcellList.stCellMeasInfo[i].stMeasRslt.sRssi,
                gaucAtCrLf);
        }
         /*��Ƶ*/
        for( i =0; i< pstcnf->stNcellListInfo.stInterFreqNcellList.ulNCellNumber ;i++)
        {
            g_ulCellNum ++;
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucLAtSndCodeAddr,
                (VOS_CHAR *)pgucLAtSndCodeAddr+usLength,
                "%d:%d,%d,%d%s",
                g_ulCellNum,
                EN_ASYN_FREQ_CELL_ID,
                pstcnf->stNcellListInfo.stInterFreqNcellList.stCellMeasInfo[i].stMeasRslt.usPhyCellId,
                pstcnf->stNcellListInfo.stInterFreqNcellList.stCellMeasInfo[i].stMeasRslt.sRssi,
                gaucAtCrLf);
        }
        /*W��Ƶ*/
        for( i =0; i< pstcnf->stNcellListInfo.stInterRATUMTSNcellList.ulNCellNumber ;i++)
        {
            g_ulCellNum ++;
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucLAtSndCodeAddr,
                (VOS_CHAR *)pgucLAtSndCodeAddr+usLength,
                "%d:%d,%d,%d%s",
                g_ulCellNum,
                EN_ASYN_UMTS_CELL_ID,
                pstcnf->stNcellListInfo.stInterRATUMTSNcellList.stUMTSNcellList[i].usPrimaryScramCode,
                pstcnf->stNcellListInfo.stInterRATUMTSNcellList.stUMTSNcellList[i].sCpichRscp,
                gaucAtCrLf);
        }
        /*G��Ƶ*/
        for( i =0; i< pstcnf->stNcellListInfo.stInterRATGeranNcellList.ulNCellNumber ;i++)
        {
            g_ulCellNum ++;
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucLAtSndCodeAddr,
                (VOS_CHAR *)pgucLAtSndCodeAddr+usLength,
                "%d:%d,%d,%d%s",
                g_ulCellNum,
                EN_ASYN_GSM_CELL_ID,
                (pstcnf->stNcellListInfo.stInterRATGeranNcellList.stGeranNcellList[i].stBSIC.usNcc) * 16 *16 +
                pstcnf->stNcellListInfo.stInterRATGeranNcellList.stGeranNcellList[i].stBSIC.usBcc,
                pstcnf->stNcellListInfo.stInterRATGeranNcellList.stGeranNcellList[i].sRSSI,
                gaucAtCrLf);
        }

        if(g_ulCellNum == 0)
        {
            usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucLAtSndCodeAddr,
                (VOS_CHAR *)pgucLAtSndCodeAddr+usLength,
                "%d%s",
                g_ulCellNum,
                gaucAtCrLf);
        }
    }

    g_ulCellNum = 0;
    CmdErrProc((VOS_UINT8)(pstcnf->usClientId), pstcnf->ulErrorCode, usLength, pgucLAtSndCodeAddr);

    return AT_FW_CLIENT_STATUS_READY;
}

/*****************************************************************************
 �� �� ��  : atLwclashInd
 ��������  : ^LWURC���������ϱ�����
 �������  : VOS_VOID *pMsgBlock
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��25��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID atLwclashInd(VOS_VOID *pMsgBlock)
{
    L4A_READ_LWCLASH_IND_STRU *pstLwclash = NULL;
    
    VOS_UINT16 usLength = 0;

    pstLwclash = (L4A_READ_LWCLASH_IND_STRU *)pMsgBlock;

                    (VOS_CHAR *)pgucLAtSndCodeAddr,
                    (VOS_CHAR *)pgucLAtSndCodeAddr,
                    "%s^LWURC: %d,%d,%d,%d,%d,%d%s",
                    gaucAtCrLf, pstLwclash->stLwclashInfo.enState,
                    pstLwclash->stLwclashInfo.usUlFreq, pstLwclash->stLwclashInfo.usUlBandwidth,
                    pstLwclash->stLwclashInfo.usDlFreq, pstLwclash->stLwclashInfo.usDlBandwidth,
                    pstLwclash->stLwclashInfo.usBand, gaucAtCrLf);

    At_SendResultData(AT_BROADCAST_CLIENT_INDEX_MODEM_0, pgucLAtSndCodeAddr, usLength);
}

typedef VOS_UINT32 (*AT_L4A_MSG_FUN)(VOS_VOID* pMsgBlock);

typedef struct
{
    VOS_UINT32 ulMsgId;
    AT_L4A_MSG_FUN atL4aMsgProc;
}AT_L4A_MSG_FUN_TABLE_STRU;

static const AT_L4A_MSG_FUN_TABLE_STRU g_astAtL4aCnfMsgFunTable[] = {

    {ID_MSG_L4A_CSQ_INFO_CNF        ,   atSetCsqCnfSameProc     },
	{ID_MSG_L4A_ANQUERY_INFO_CNF    , 	atSetAnlevelCnfSameProc },
    {ID_MSG_L4A_CNMR_CNF            , 	atQryCnmrCnfProc     	},
    {ID_MSG_L4A_CELL_ID_CNF         ,   atQryCellIdCnfProc      },
    {ID_MSG_L4A_LWCLASHQRY_CNF      ,   atLwclashCnfProc        },
    {ID_MSG_L4A_CELL_INFO_CNF       ,   atQryCellInfoCnfProc    },
    {ID_MSG_L4A_CERSSI_INQ_CNF      ,   atCerssiInfoCnfProc     },
};

static const AT_L4A_MSG_FUN_TABLE_STRU g_astAtL4aIndMsgFunTable[] = {
    {ID_MSG_L4A_RSSI_IND        	,   atCsqInfoIndProc        },
	{ID_MSG_L4A_ANLEVEL_IND			,	atAnlevelInfoIndProc	},
    {ID_MSG_L4A_CERSSI_IND	        ,	atCerssiInfoIndProc		},
    {ID_MSG_L4A_MODE_IND            ,   atSysModeIndProc        },
    {ID_MSG_L4A_LWCLASH_IND         ,   (AT_L4A_MSG_FUN)atLwclashInd},
};

/******************************************************************************
/* ��������: atL4aGetMsgFun
/* ��������: ��ȡ����L4A�ظ���Ϣ�ĺ���
/*
/* ����˵��: ulMsgId����ϢID
/*
/* �� �� ֵ:
/*
/* ����Ҫ��: TODO: ...
/* ���þ���: TODO: ...
/* ��    ��: ������00184452 [2010-10-10]
/******************************************************************************
AT_L4A_MSG_FUN_TABLE_STRU* atL4aGetCnfMsgFun(VOS_UINT32 ulMsgId)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 ulTableLen = 0;
    const AT_L4A_MSG_FUN_TABLE_STRU* pTable;

    pTable = g_astAtL4aCnfMsgFunTable;
    ulTableLen = sizeof(g_astAtL4aCnfMsgFunTable);

    for(i = 0; i < (ulTableLen/sizeof(AT_L4A_MSG_FUN_TABLE_STRU)); i++)
    {
        if(ulMsgId == (pTable + i)->ulMsgId)
        {
            return (AT_L4A_MSG_FUN_TABLE_STRU*)(pTable + i);
        }
    }

    /*����Ҳ���
    return NULL;
}

/******************************************************************************
/* ��������: atL4aGetIndMsgFun
/* ��������: ��ȡ����L4A�ظ���Ϣ�ĺ���
/*
/* ����˵��: ulMsgId����ϢID
/*
/* �� �� ֵ:
/*
/* ����Ҫ��: TODO: ...
/* ���þ���: TODO: ...
/* ��    ��: ������00184452 [2010-10-10]
/******************************************************************************
AT_L4A_MSG_FUN_TABLE_STRU* atL4aGetIndMsgFun(VOS_UINT32 ulMsgId)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 ulTableLen = 0;
    const AT_L4A_MSG_FUN_TABLE_STRU* pTable;

    pTable = g_astAtL4aIndMsgFunTable;
    ulTableLen = sizeof(g_astAtL4aIndMsgFunTable);

    for(i = 0; i < (ulTableLen/sizeof(AT_L4A_MSG_FUN_TABLE_STRU)); i++)
    {
        if(ulMsgId == (pTable + i)->ulMsgId)
        {
            return (AT_L4A_MSG_FUN_TABLE_STRU*)(pTable + i);
        }
    }

    /*����Ҳ���
    return NULL;
}

/*c00184452 end in 2011-10-04

/*c00184452 start in 2011-09-30
/******************************************************************************
/* ��������: at_L4aCnfProc
/* ��������: ����L4A��CNF��IND��Ϣ�������Ҷ�Ӧ�������д���
/*
/* ����˵��: pMsgBlockTmp��VOS��Ϣ
/*
/* �� �� ֵ:
/*
/* ����Ҫ��: TODO: ...
/* ���þ���: TODO: ...
/* ��    ��: ������00184452 [2010-10-10]
/******************************************************************************
VOS_UINT32 at_L4aCnfProc(MsgBlock* pMsgBlockTmp)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    VOS_UINT32 ulMsgId = 0;
    VOS_UINT16 usIndex = 0;
    AT_L4A_MSG_FUN_TABLE_STRU* pTable = NULL;
    AT_L4A_MSG_FUN pMsgProc = NULL;
    L4A_AT_CNF_HEADER_STRU    *pstMsgHeader;

    pstMsgHeader    = (L4A_AT_CNF_HEADER_STRU *)pMsgBlockTmp;
	ulMsgId = pstMsgHeader->enMsgId;

    At_ClientIdToUserId((VOS_UINT16)pstMsgHeader->usClientId, (TAF_UINT8 *)&usIndex);

    pstMsgHeader->usClientId = usIndex;
    {
        AT_STOP_TIMER_CMD_READY(usIndex);
        pMsgProc = pTable->atL4aMsgProc;
    }
    else if( (pTable = atL4aGetIndMsgFun(ulMsgId)) && (pTable->atL4aMsgProc))
    {
        pMsgProc = pTable->atL4aMsgProc;
    }
    else
    {
        ulRet = ERR_MSP_FAILURE;
    }

	if(pMsgProc)
    {
        ulRet = pMsgProc(pMsgBlockTmp);
    }

    return ulRet;
}
/*c00184452 end in 2011-09-30

AT_FTM_CNF_MSG_PROC_STRU g_astLteAtFtmCnfMsgTbl[] =
{
    { ID_MSG_SYM_SET_TMODE_CNF,         atSetTmodeParaCnfProc },
    { ID_MSG_FTM_SET_BANDSW_CNF,        atSetBandSWParaCnfProc },
    { ID_MSG_FTM_RD_BANDSW_CNF,         atQryBandSWParaCnfProc},
    { ID_MSG_FTM_F_SET_FCHANS_CNF,      atSetFFCHANSParaCnfProc },
    { ID_MSG_FTM_F_RD_FCHANS_CNF,       atQryFFCHANSParaCnfProc },
    { ID_MSG_FTM_F_SET_FSEGMENT_CNF,    atSetFFSEGMENTParaCnfProc },
    { ID_MSG_FTM_F_RD_FSEGMENT_CNF,     atQryFFSEGMENTParaCnfProc },
    { ID_MSG_FTM_F_SET_FPOWS_CNF,       atSetFFPOWSParaCnfProc },
    { ID_MSG_FTM_F_RD_FPOWS_CNF,        atQryFFPOWSParaCnfProc },
    { ID_MSG_FTM_F_SET_FPAS_CNF,        atSetFFPASParaCnfProc },
    { ID_MSG_FTM_F_RD_FPAS_CNF,         atQryFFPASParaCnfProc },
    { ID_MSG_FTM_F_SET_FLNAS_CNF,       atSetFFLNASParaCnfProc },
    { ID_MSG_FTM_F_RD_FLNAS_CNF,        atQryFFLNASParaCnfProc },
    { ID_MSG_FTM_F_SET_FTXWAVE_CNF,     atSetFFTXWAVEParaCnfProc },
    { ID_MSG_FTM_F_RD_FTXWAVE_CNF,      atQryFFTXWAVEParaCnfProc },
    { ID_MSG_FTM_F_SET_FSTART_CNF,      atSetFFSTARTParaCnfProc },
    { ID_MSG_FTM_F_RD_FSTART_CNF,       atQryFFSTARTParaCnfProc },
    { ID_MSG_FTM_F_SET_FRSSIS_CNF,      atSetFFRSSISParaCnfProc },
    { ID_MSG_FTM_F_RD_FCMTMS_CNF,       atSetFFCMTMSParaCnfProc },
    { ID_MSG_FTM_F_SET_FBLK_CNF,        atSetFBLKParaCnfProc },
    { ID_MSG_FTM_F_RD_FBLK_CNF,         atQryFBLKParaCnfProc },
    { ID_MSG_FTM_F_SET_FIPSTART_CNF,    atSetFIPSTARTParaCnfProc },
    { ID_MSG_FTM_F_SET_FMAXPOWER_CNF,   atSetFMAXPOWERParaCnfProc },
    { ID_MSG_FTM_F_RD_FMAXPOWER_CNF,    atQryFMAXPOWERParaCnfProc },
    { ID_MSG_FTM_F_SET_FPAPOWER_CNF,    atSetFPAPOWERParaCnfProc },
    { ID_MSG_FTM_F_RD_FPAPOWER_CNF,     atQryFPAPOWERParaCnfProc },
    { ID_MSG_FTM_SET_FVCTCXO_CNF,       atSetVCTCXOParaCnfProc },
    { ID_MSG_FTM_RD_FVCTCXO_CNF,        atQryVCTCXOParaCnfProc },
    { ID_MSG_FTM_SET_FCHAN_CNF,         atSetFCHANParaCnfProc },
    { ID_MSG_FTM_RD_FCHAN_CNF,          atQryFCHANParaCnfProc },
    { ID_MSG_FTM_SET_TXON_CNF,          atSetFTXONParaCnfProc },
    { ID_MSG_FTM_RD_TXON_CNF,           atQryFTXONParaCnfProc },
    { ID_MSG_FTM_SET_RXON_CNF,          atSetFRXONParaCnfProc },
    { ID_MSG_FTM_RD_RXON_CNF,           atQryFRXONParaCnfProc },
    { ID_MSG_FTM_SET_FWAVE_CNF,         atSetFWAVEParaCnfProc },
    { ID_MSG_FTM_RD_AAGC_CNF,           atQryFLNAParaCnfProc },
    { ID_MSG_FTM_FRSSI_CNF,             atQryFRSSIParaCnfProc },
    { ID_MSG_FTM_SET_FPDMS_CNF,         atSetFPDMSParaCnfProc},/*FPDMS ��ʵ��δ����*/
    { ID_MSG_FTM_SET_SSYNC_CNF,         atSetSSYNCParaCnfProc },
    { ID_MSG_FTM_RD_SSYNC_CNF,          atQrySSYNCParaCnfProc },
    { ID_MSG_FTM_SET_STXBW_CNF,         atSetSTXBWParaCnfProc },
    { ID_MSG_FTM_RD_STXBW_CNF,          atQrySTXBWParaCnfProc },
    { ID_MSG_FTM_SET_STXCHAN_CNF,       atSetSTXCHANParaCnfProc },
    { ID_MSG_FTM_RD_STXCHAN_CNF,        atQrySTXCHANParaCnfProc },
    { ID_MSG_FTM_SET_SSUBFRAME_CNF,     atSetSSUBFRAMEParaCnfProc },
    { ID_MSG_FTM_RD_SSUBFRAME_CNF,      atQrySSUBFRAMEParaCnfProc },
    { ID_MSG_FTM_SET_SPARA_CNF,         atSetSPARAParaCnfProc },
    { ID_MSG_FTM_RD_SPARA_CNF,          atQrySPARAParaCnfProc },
    { ID_MSG_FTM_SET_SSEGNUM_CNF,       atSetSSEGNUMParaCnfProc },
    { ID_MSG_FTM_RD_SSEGNUM_CNF,        atQrySSEGNUMParaCnfProc },
    { ID_MSG_FTM_SET_STXMODUS_CNF,      atSetSTXMODUSParaCnfProc },
    { ID_MSG_FTM_RD_STXMODUS_CNF,       atQrySTXMODUSParaCnfProc },
    { ID_MSG_FTM_SET_STXRBNUMS_CNF,     atSetSTXRBNUMSParaCnfProc },
    { ID_MSG_FTM_RD_STXRBNUMS_CNF,      atQrySTXRBNUMSParaCnfProc },
    { ID_MSG_FTM_SET_STXRBPOSS_CNF,     atSetSTXRBPOSSParaCnfProc },
    { ID_MSG_FTM_RD_STXRBPOSS_CNF,      atQrySTXRBPOSSParaCnfProc },
    { ID_MSG_FTM_SET_STXPOWS_CNF,       atSetSTXPOWSParaCnfProc },
    { ID_MSG_FTM_RD_STXPOWS_CNF,        atQrySTXPOWSParaCnfProc },
    { ID_MSG_FTM_SET_STXCHANTYPES_CNF,  atSetSTXCHANTYPESParaCnfProc },
    { ID_MSG_FTM_RD_STXCHANTYPES_CNF,   atQrySTXCHANTYPESParaCnfProc },
    { ID_MSG_FTM_SET_SSEGLEN_CNF,       atSetSSEGLENParaCnfProc },
    { ID_MSG_FTM_RD_SSEGLEN_CNF,        atQrySSEGLENParaCnfProc },
    { ID_MSG_FTM_SET_SRXSET_CNF,        atSetSRXSETParaCnfProc },
    { ID_MSG_FTM_RD_SRXSET_CNF,         atQrySRXSETParaCnfProc },
    { ID_MSG_FTM_SET_SRXSUBFRA_CNF,     atSetSRXSUBFRAParaCnfProc },
    { ID_MSG_FTM_RD_SRXSUBFRA_CNF,      atQrySRXSUBFRAParaCnfProc },
    { ID_MSG_FTM_RD_SRXBLER_CNF,        atQrySRXBLERParaCnfProc },
    { ID_MSG_FTM_SET_SSTART_CNF,        atSetSSTARTParaCnfProc },
    { ID_MSG_FTM_RD_SSTART_CNF,         atQrySSTARTParaCnfProc },
    { ID_MSG_FTM_SET_SSTOP_CNF,         atSetSSTOPParaCnfProc },
    /* */
    { ID_MSG_FTM_RD_DLOADINFO_CNF,      atQryDLoadInfoCnf },
    { ID_MSG_FTM_RD_AUTHORITYVER_CNF,   atQryAuthorityVerCnf },
    { ID_MSG_FTM_RD_AUTHORITYID_CNF,    atQryAuthorityIDCnf },
    { ID_MSG_FTM_SET_NVBACKUP_CNF,      atSetNVBackupCnf },
    { ID_MSG_FTM_SET_NVRESTORE_CNF,     atSetNVRestoreCnf },
    { ID_MSG_FTM_SET_NVRSTSTTS_CNF,     atSetNVRstSTTSCnf },
    {ID_MSG_FTM_SET_TBAT_CNF,           atSetTbatCnf},
    {ID_MSG_FTM_RD_TBAT_CNF,            atRdTbatCnf},
    {ID_MSG_FTM_SET_SDLOAD_CNF,     atSetSdloadCnf },
#if(FEATURE_ON == FEATURE_UE_MODE_TDS)
    { ID_MSG_FTM_RD_SCALIB_CNF,         atQrySCALIBParaCnfProc },
    { ID_MSG_FTM_SET_SCALIB_CNF,        atSetSCALIBParaCnfProc },
    { ID_MSG_FTM_RD_SCELLINFO_CNF,      atQryScellinfoParaCnfProc},

    { ID_MSG_FTM_RD_TEMPERATURE_CNF,    atQryCmtmCnfProc},
#endif
    { ID_MSG_FTM_SET_FCALIIP2S_CNF,     atSetFCALIIP2SParaCnfProc },
    { ID_MSG_FTM_RD_FCALIIP2S_CNF,      atQryFCALIIP2SParaCnfProc },
    { ID_MSG_FTM_SET_FCALIDCOCS_CNF,    atSetFCALIDCOCSParaCnfProc },
    { ID_MSG_FTM_RD_FCALIDCOCS_CNF,     atQryFCALIDCOCSParaCnfProc },
{ ID_MSG_FTM_SET_FGAINSTATES_CNF,   atSetFGAINSTATESParaCnfProc },
    { ID_MSG_FTM_RD_FGAINSTATES_CNF,    atQryFGAINSTATESParaCnfProc },
	{ ID_MSG_FTM_SET_FDBBATTS_CNF, 		atSetFDBBATTSParaCnfProc },
	{ ID_MSG_FTM_RD_FDBBATTS_CNF,       atQryFDBBATTSParaCnfProc },
	{ ID_MSG_FTM_SET_FBBATTS_CNF,		atSetFBBATTSParaCnfProc },
	{ ID_MSG_FTM_RD_FBBATTS_CNF,		atQryFBBATTSParaCnfProc },
    { ID_MSG_FTM_SET_FCALITXIQS_CNF,    atSetFCALITXIQSParaCnfProc },
	{ ID_MSG_FTM_RD_FCALITXIQS_CNF,		atQryFCALITXIQSParaCnfProc },
    { ID_MSG_FTM_SET_STCFGDPCH_CNF,       atSetSTCFGDPCHParaCnfProc },
    { ID_MSG_FTM_FPOW_CNF,              atSetFPOWParaCnfProc },
   { ID_MSG_FTM_RD_STRXBER_CNF,        atQrySTRXBERParaCnfProc },};
/******************************************************************************
/* ��������: atGetFtmCnfMsgProc
/* ��������: ���ݻظ�����Ϣ�ҵ�ƥ��Ĵ�������
/*
/* ����˵��:
/*   MsgId  [in] ��ϢID
/* �� �� ֵ:
/*    ��NULL g_astLteAtFtmCnfMsgTbl Ԫ�ص�ַ�������˴�������
/*    NULL ƥ��ʧ��
/* ��    ��: lwx26324 [20110927]
/******************************************************************************
AT_FTM_CNF_MSG_PROC_STRU* atGetFtmCnfMsgProc(VOS_UINT32 ulMsgId)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 ulTableLen = sizeof(g_astLteAtFtmCnfMsgTbl)/sizeof(g_astLteAtFtmCnfMsgTbl[0]);

    for (i=0; i<ulTableLen; i++)
    {
        if (g_astLteAtFtmCnfMsgTbl[i].ulMsgId == ulMsgId)
        {
            return &(g_astLteAtFtmCnfMsgTbl[i]);
        }
    }

    return NULL;
}

/******************************************************************************
/* ��������: atGetFtmCnfMsgProc
/* ��������: AT����LTEװ��FTM�ظ���Ϣ���
/*
/* ����˵��:
/*   pMsg  [in] �˼���Ϣ�ṹ
/* �� �� ֵ:
/*    ERR_MSP_SUCCESS �ɹ�
/*    ERR_MSP_FAILURE ʧ��
/* ��    ��: lwx26324 [20110927]
/******************************************************************************
VOS_UINT32 At_FtmEventMsgProc(VOS_VOID* pMsg)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    OS_MSG_STRU *pOsMsg = NULL;
    MsgBlock *pstMsgBlock = NULL;
    AT_FTM_CNF_MSG_PROC_STRU* pMsgProcItem = NULL;
    AT_FW_DATA_MSG_STRU *pDataMsg = (AT_FW_DATA_MSG_STRU*)pMsg;
    VOS_VOID * pTmp;


    if (NULL == pstMsgBlock)
    {
    	return ERR_MSP_FAILURE;
    }

    /*��Ϣ�ṹת��
    pOsMsg = (OS_MSG_STRU *)(pstMsgBlock->aucValue);
    pOsMsg->ulMsgId = pDataMsg->ulMsgId;
    pOsMsg->ulParam2 = pDataMsg->ulLen;

    pTmp = VOS_MemAlloc(WUEPS_PID_AT, (DYNAMIC_MEM_PT), pDataMsg->ulLen);
    if (NULL == pTmp)
    {
        VOS_MemFree(WUEPS_PID_AT, pstMsgBlock);
    	return ERR_MSP_FAILURE;
    }

    pOsMsg->ulParam1 = (VOS_UINT32)pTmp;

    /*��Ϣ����
    pMsgProcItem = atGetFtmCnfMsgProc(pDataMsg->ulMsgId);

    if(NULL == pMsgProcItem)
    {
        ulRet = ERR_MSP_FAILURE;
    }
    else
    {
        AT_STOP_TIMER_CMD_READY(pDataMsg->ulClientId);
        ulRet = pMsgProcItem->pfnCnfMsgProc((VOS_UINT8)(pDataMsg->ulClientId), (VOS_VOID *)pstMsgBlock);
    }

    VOS_MemFree(WUEPS_PID_AT, pTmp);
    VOS_MemFree(WUEPS_PID_AT, pstMsgBlock);
    return ulRet;
}
/*lkf58113 end in 2011-10-19

/*****************************************************************************
 �� �� ��  : AT_ProcTempprtEventInd
 ��������  : ������ϢID_TEMPPRT_AT_EVENT_IND
 �������  : pstMsg - ����SPY����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   :
   ��    ��   :
   �޸�����   :

*****************************************************************************/
VOS_UINT32    AT_ProcTempprtEventInd(
    TEMP_PROTECT_EVENT_AT_IND_STRU     *pstMsg
)
{
    VOS_UINT16                          usLength = 0;
    TEMP_PROTECT_EVENT_AT_IND_STRU     *pTempPrt = VOS_NULL;

    pTempPrt = (TEMP_PROTECT_EVENT_AT_IND_STRU*)pstMsg;

    HAL_SDMLOG("AT_ProcTempprtEventInd: Event %d Param %d\n", (VOS_INT)pTempPrt->ulTempProtectEvent, (VOS_INT)pTempPrt->ulTempProtectParam);

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,
                            (VOS_CHAR *)pgucLAtSndCodeAddr,"%s%s%d,%d%s",
                            gaucAtCrLf, "^TEMPPRT:", pTempPrt->ulTempProtectEvent,
                            pTempPrt->ulTempProtectParam, gaucAtCrLf);

    At_SendResultData(AT_CLIENT_TAB_APP_INDEX,pgucLAtSndCodeAddr,usLength);

    return VOS_OK;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


