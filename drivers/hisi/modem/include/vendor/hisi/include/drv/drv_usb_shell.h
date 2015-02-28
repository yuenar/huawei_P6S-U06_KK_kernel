/*******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 *******************************************************************************
  文 件 名   : usb_shell.h
  版 本 号   : 初稿
  作    者   : 张彪 kf67996
  生成日期   : 2012年9月13日
  最近修改   :
  功能描述   : USB ASHELL/CSHELL模块头文件信息
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月13日
    作    者   : 张彪 kf67996
    修改内容   : 创建文件

*******************************************************************************/

/*******************************************************************************
  1 其他头文件包含
*******************************************************************************/

#ifndef    _BSP_USB_SHELL_H_
#define    _BSP_USB_SHELL_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/**************************************************************************
  list 定义
**************************************************************************/

/**************************************************************************
  配置宏定义
**************************************************************************/

/**************************************************************************
  功能宏定义
**************************************************************************/


/**************************************************************************
  STRUCT定义
**************************************************************************/

/**************************************************************************
  函数声明
**************************************************************************/
int  usb_shell_init(void);
extern void BSP_USB_UdiDisableNotify (void);
extern void BSP_USB_UdiEnableNotify (void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* _BSP_USB_SHELL_H_ */


