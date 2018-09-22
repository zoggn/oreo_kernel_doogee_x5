/* Copyright Statement:
* 
* This software/firmware and related documentation ("MediaTek Software") are
* protected under relevant copyright laws. The information contained herein
* is confidential and proprietary to MediaTek Inc. and/or its licensors.
* Without the prior written permission of MediaTek inc. and/or its licensors,
* any reproduction, modification, use or disclosure of MediaTek Software,
* and information contained herein, in whole or in part, shall be strictly prohibited.
*/
/* MediaTek Inc. (C) 2010. All rights reserved.
* 
* BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
* THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
* RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
* AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
* NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
* SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
* SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
* THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
* THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
* CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
* SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
* STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
* CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
* AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
* OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
* MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
* The following software/firmware and/or related documentation ("MediaTek Software")
* have been modified by MediaTek Inc. All revisions are subject to any receiver's
* applicable license agreements with MediaTek Inc.
*/

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifdef BUILD_LK
#include <platform/mt_gpio.h>
#include <platform/mt_pmic.h>
#else
#include <mt-plat/mt_gpio.h>
//#include <mt-plat/upmu_common.h>
#include <linux/string.h>
#include <linux/kernel.h>
#endif
#include "lcm_drv.h"

#if defined(BUILD_LK)
#define LCM_DEBUG  printf
#define LCM_FUNC_TRACE() printf("huyl [uboot] %s\n",__func__)
#else
#define LCM_DEBUG  printk
#define LCM_FUNC_TRACE() printk("huyl [kernel] %s\n",__func__)
#endif
// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (720)
#define FRAME_HEIGHT (1280)

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))

#define REGFLAG_DELAY             							0XFFE
#define REGFLAG_END_OF_TABLE      							0xFFF   // END OF REGISTERS MARKER

// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	        lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)											lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)


struct LCM_setting_table {
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[64];
};

static void lcm_init_power(void)
{
    
}

static void lcm_suspend_power(void)
{
    
}

static void lcm_resume_power(void)
{
    
}

static struct LCM_setting_table lcm_initialization_setting[] = {
    { 0xE0, 0x01, {0x00}},
    { 0xE1, 0x01, {0x93}},
    { 0xE2, 0x01, {0x65}},
    { 0xE3, 0x01, {0xF8}},
    { 0xE0, 0x01, {0x01}},
    { 0x01, 0x00, {0x00}},
    { 0x01, 0x01, {0xB6}},
    { 0x03, 0x01, {0x00}},
    { 0x04, 0x01, {0xC5}},
    { 0x17, 0x01, {0x00}},
    { 0x18, 0x01, {0xBF}},
    { 0x19, 0x01, {0x01}},
    { 0x1A, 0x01, {0x00}},
    { 0x1B, 0x01, {0xBF}},
    { 0x1C, 0x01, {0x01}},
    { 0x1F, 0x01, {0x7C}},
    { 0x20, 0x01, {0x26}},
    { 0x21, 0x01, {0x26}},
    { 0x22, 0x01, {0x4E}},
    { 0x37, 0x01, {0x09}},
    { 0x38, 0x01, {0x04}},
    { 0x39, 0x01, {0x08}},
    { 0x3A, 0x01, {0x1F}},
    { 0x3B, 0x01, {0x1F}},
    { 0x3C, 0x01, {0x78}},
    { 0x3D, 0x01, {0xFF}},
    { 0x3E, 0x01, {0xFF}},
    { 0x3F, 0x01, {0x00}},
    { 0x40, 0x01, {0x04}},
    { 0x41, 0x01, {0xA0}},
    { 0x43, 0x01, {0x0F}},
    { 0x44, 0x01, {0x0A}},
    { 0x45, 0x01, {0x24}},
    { 0x55, 0x01, {0x01}},
    { 0x56, 0x01, {0x01}},
    { 0x57, 0x01, {0xA5}},
    { 0x58, 0x01, {0x0A}},
    { 0x59, 0x01, {0x4A}},
    { 0x5A, 0x01, {0x38}},                                                                                                                                                                                                                                                     
    { 0x5B, 0x01, {0x10}},                                                                                                                                                                                                                                                     
    { 0x5C, 0x01, {0x19}},                                                                                                                                                                                                                                                     
    { 0x5D, 0x01, {0x7C}},                                                                                                                                                                                                                                                     
    { 0x5E, 0x01, {0x64}},                                                                                                                                                                                                                                                     
    { 0x5F, 0x01, {0x54}},                                                                                                                                                                                                                                                     
    { 0x60, 0x01, {0x48}},                                                                                                                                                                                                                                                     
    { 0x61, 0x01, {0x44}},                                                                                                                                                                                                                                                     
    { 0x62, 0x01, {0x35}},                                                                                                                                                                                                                                                     
    { 0x63, 0x01, {0x3A}},                                                                                                                                                                                                                                                     
    { 0x64, 0x01, {0x24}},                                                                                                                                                                                                                                                     
    { 0x65, 0x01, {0x3B}},                                                                                                                                                                                                                                                     
    { 0x66, 0x01, {0x39}},                                                                                                                                                                                                                                                     
    { 0x67, 0x01, {0x37}},                                                                                                                                                                                                                                                     
    { 0x68, 0x01, {0x56}},                                                                                                                                                                                                                                                     
    { 0x69, 0x01, {0x41}},                                                                                                                                                                                                                                                     
    { 0x6A, 0x01, {0x47}},                                                                                                                                                                                                                                                     
    { 0x6B, 0x01, {0x2F}},                                                                                                                                                                                                                                                     
    { 0x6C, 0x01, {0x23}},                                                                                                                                                                                                                                                     
    { 0x6D, 0x01, {0x13}},                                                                                                                                                                                                                                                     
    { 0x6E, 0x01, {0x02}},                                                                                                                                                                                                                                                     
    { 0x6F, 0x01, {0x08}},                                                                                                                                                                                                                                                     
    { 0x70, 0x01, {0x7C}},                                                                                                                                                                                                                                                     
    { 0x71, 0x01, {0x64}},
    { 0x72, 0x01, {0x54}},
    { 0x73, 0x01, {0x48}},
    { 0x74, 0x01, {0x44}},
    { 0x75, 0x01, {0x35}},
    { 0x76, 0x01, {0x3A}},
    { 0x77, 0x01, {0x22}},
    { 0x78, 0x01, {0x3B}},
    { 0x79, 0x01, {0x39}},
    { 0x7A, 0x01, {0x38}},
    { 0x7B, 0x01, {0x52}},
    { 0x7C, 0x01, {0x41}},
    { 0x7D, 0x01, {0x47}},
    { 0x7E, 0x01, {0x2F}},
    { 0x7F, 0x01, {0x23}},
    { 0x80, 0x01, {0x13}},
    { 0x81, 0x01, {0x02}},
    { 0x82, 0x01, {0x08}},
    { 0xE0, 0x01, {0x02}},
    { 0x00, 0x01, {0x57}},
    { 0x01, 0x01, {0x77}},
    { 0x02, 0x01, {0x44}},
    { 0x03, 0x01, {0x46}},
    { 0x04, 0x01, {0x48}},
    { 0x05, 0x01, {0x4A}},
    { 0x06, 0x01, {0x4C}},
    { 0x07, 0x01, {0x4E}},
    { 0x08, 0x01, {0x50}},
    { 0x09, 0x01, {0x55}},
    { 0x0A, 0x01, {0x52}},
    { 0x0B, 0x01, {0x55}},
    { 0x0C, 0x01, {0x55}},
    { 0x0D, 0x01, {0x55}},
    { 0x0E, 0x01, {0x55}},
    { 0x0F, 0x01, {0x55}},
    { 0x10, 0x01, {0x55}},
    { 0x11, 0x01, {0x55}},
    { 0x12, 0x01, {0x55}},
    { 0x13, 0x01, {0x40}},
    { 0x14, 0x01, {0x55}},
    { 0x15, 0x01, {0x55}},
    { 0x16, 0x01, {0x57}},
    { 0x17, 0x01, {0x77}},
    { 0x18, 0x01, {0x45}},
    { 0x19, 0x01, {0x47}},
    { 0x1A, 0x01, {0x49}},
    { 0x1B, 0x01, {0x4B}},
    { 0x1C, 0x01, {0x4D}},
    { 0x1D, 0x01, {0x4F}},
    { 0x1E, 0x01, {0x51}},
    { 0x1F, 0x01, {0x55}},
    { 0x20, 0x01, {0x53}},
    { 0x21, 0x01, {0x55}},
    { 0x22, 0x01, {0x55}},
    { 0x23, 0x01, {0x55}},
    { 0x24, 0x01, {0x55}},
    { 0x25, 0x01, {0x55}},
    { 0x26, 0x01, {0x55}},
    { 0x27, 0x01, {0x55}},
    { 0x28, 0x01, {0x55}},
    { 0x29, 0x01, {0x41}},
    { 0x2A, 0x01, {0x55}},
    { 0x2B, 0x01, {0x55}},
    { 0x2C, 0x01, {0x57}},
    { 0x2D, 0x01, {0x77}},
    { 0x2E, 0x01, {0x4F}},
    { 0x2F, 0x01, {0x4D}},
    { 0x30, 0x01, {0x4B}},
    { 0x31, 0x01, {0x49}},
    { 0x32, 0x01, {0x47}},
    { 0x33, 0x01, {0x45}},
    { 0x34, 0x01, {0x41}},
    { 0x35, 0x01, {0x55}},
    { 0x36, 0x01, {0x53}},
    { 0x37, 0x01, {0x55}},
    { 0x38, 0x01, {0x55}},
    { 0x39, 0x01, {0x55}},
    { 0x3A, 0x01, {0x55}},
    { 0x3B, 0x01, {0x55}},
    { 0x3C, 0x01, {0x55}},
    { 0x3D, 0x01, {0x55}},
    { 0x3E, 0x01, {0x55}},
    { 0x3F, 0x01, {0x51}},
    { 0x40, 0x01, {0x55}},
    { 0x41, 0x01, {0x55}},
    { 0x42, 0x01, {0x57}},
    { 0x43, 0x01, {0x77}},
    { 0x44, 0x01, {0x4E}},
    { 0x45, 0x01, {0x4C}},
    { 0x46, 0x01, {0x4A}},
    { 0x47, 0x01, {0x48}},
    { 0x48, 0x01, {0x46}},
    { 0x49, 0x01, {0x44}},
    { 0x4A, 0x01, {0x40}},
    { 0x4B, 0x01, {0x55}},
    { 0x4C, 0x01, {0x52}},
    { 0x4D, 0x01, {0x55}},
    { 0x4E, 0x01, {0x55}},
    { 0x4F, 0x01, {0x55}},
    { 0x50, 0x01, {0x55}},
    { 0x51, 0x01, {0x55}},
    { 0x52, 0x01, {0x55}},
    { 0x53, 0x01, {0x55}},
    { 0x54, 0x01, {0x55}},
    { 0x55, 0x01, {0x50}},
    { 0x56, 0x01, {0x55}},
    { 0x57, 0x01, {0x55}},
    { 0x58, 0x01, {0x40}},
    { 0x59, 0x01, {0x00}},
    { 0x5A, 0x01, {0x00}},
    { 0x5B, 0x01, {0x10}},
    { 0x5C, 0x01, {0x09}},
    { 0x5D, 0x01, {0x30}},
    { 0x5E, 0x01, {0x01}},
    { 0x5F, 0x01, {0x02}},
    { 0x60, 0x01, {0x30}},
    { 0x61, 0x01, {0x03}},
    { 0x62, 0x01, {0x04}},
    { 0x63, 0x01, {0x06}},
    { 0x64, 0x01, {0x6A}},
    { 0x65, 0x01, {0x75}},
    { 0x66, 0x01, {0x0F}},
    { 0x67, 0x01, {0xB3}},
    { 0x68, 0x01, {0x0B}},
    { 0x69, 0x01, {0x06}},
    { 0x6A, 0x01, {0x6A}},
    { 0x6B, 0x01, {0x10}},
    { 0x6C, 0x01, {0x00}},
    { 0x6D, 0x01, {0x04}},
    { 0x6E, 0x01, {0x04}},
    { 0x6F, 0x01, {0x88}},
    { 0x70, 0x01, {0x00}},
    { 0x71, 0x01, {0x00}},
    { 0x72, 0x01, {0x06}},
    { 0x73, 0x01, {0x7B}},
    { 0x74, 0x01, {0x00}},
    { 0x75, 0x01, {0xBC}},
    { 0x76, 0x01, {0x00}},
    { 0x77, 0x01, {0x05}},
    { 0x78, 0x01, {0x2E}},
    { 0x79, 0x01, {0x00}},
    { 0x7A, 0x01, {0x00}},
    { 0x7B, 0x01, {0x00}},
    { 0x7C, 0x01, {0x00}},
    { 0x7D, 0x01, {0x03}},
    { 0x7E, 0x01, {0x7B}},
    { 0xE0, 0x01, {0x04}},
    { 0x09, 0x01, {0x10}},
    { 0x2B, 0x01, {0x2B}},
    { 0x2E, 0x01, {0x44}},
    { 0xE0, 0x01, {0x00}},
    { 0xE6, 0x01, {0x02}},
    { 0xE7, 0x01, {0x02}},
    { 0x35, 0x01, {0x00}},
    { 0x11, 0x01, {0x00}},
    { REGFLAG_DELAY, 120, {0x00}},
    { 0x29, 0x01, {0x00}},
    { REGFLAG_DELAY, 0x20, {0x00}},
    { REGFLAG_END_OF_TABLE, 0x00, {0x00}}
    
};

static struct LCM_setting_table lcm_sleep_mode_in_setting[] = {
    // Display off sequence
    {0x28, 0, {0x00}},
    {REGFLAG_DELAY, 20, {}},
    
    // Sleep Mode On
    {0x10, 0, {0x00}},
    {REGFLAG_DELAY, 120, {}},
    {REGFLAG_END_OF_TABLE, 0x00, {}}
};


static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
    unsigned int i;
    
    for(i = 0; i < count; i++) {
        
        unsigned cmd;
        cmd = table[i].cmd;
        
        switch (cmd) {
            
            case REGFLAG_DELAY :
                MDELAY(table[i].count);
                break;
                
            case REGFLAG_END_OF_TABLE :
                break;
                
            default:
                dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
                //MDELAY(2);
        }
    }
    
}

// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}

static void lcm_get_params(LCM_PARAMS *params)
{
    
    memset(params, 0, sizeof(LCM_PARAMS));	
    params->type   = LCM_TYPE_DSI;
    params->width  = FRAME_WIDTH;
    params->height = FRAME_HEIGHT;
    params->dsi.mode   = SYNC_PULSE_VDO_MODE;
    
    // DSI
    /* Command mode setting */
    params->dsi.word_count = 2160;
    params->dsi.vertical_sync_active = 4;
    params->dsi.vertical_backporch = 18;
    params->dsi.vertical_frontporch = 48;
    params->dsi.PLL_CLOCK = 416;
    params->dsi.lcm_esd_check_table[0].cmd = 10;
    params->dsi.lcm_esd_check_table[0].para_list[0] = -100;
    params->dsi.lcm_esd_check_table[1].cmd = 14;
    params->dsi.lcm_esd_check_table[1].para_list[0] = -128;
    params->dsi.LANE_NUM = 2;
    params->dsi.data_format.format = 2;
    params->dsi.PS = 2;
    params->dsi.horizontal_active_pixel = 720;
    params->dsi.vertical_active_line = 1280;
    params->dbi.te_mode = 0;
    params->dbi.te_edge_polarity = 0;
    params->dsi.data_format.color_order = 0;
    params->dsi.data_format.trans_seq = 0;
    params->dsi.data_format.padding = 0;
    params->dsi.intermediat_buffer_num = 0;
    params->dsi.cont_clock = 1;
    params->dsi.esd_check_enable = 1;
    params->dsi.customization_esd_check_enable = 1;
    params->dsi.lcm_esd_check_table[0].count = 1;
    params->dsi.lcm_esd_check_table[1].count = 1;
    params->dsi.horizontal_sync_active = 80;
    params->dsi.horizontal_backporch = 80;
    params->dsi.horizontal_frontporch = 80;
}

static void lcm_init(void)
{
    SET_RESET_PIN(1);
    MDELAY(1);
    SET_RESET_PIN(0);
    MDELAY(50);
    SET_RESET_PIN(1);
    MDELAY(120);
    push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_suspend(void)
{
    SET_RESET_PIN(1);
    MDELAY(10);
    SET_RESET_PIN(0);
    MDELAY(10);
    SET_RESET_PIN(1);
    MDELAY(150);
    push_table(lcm_sleep_mode_in_setting, sizeof(lcm_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_resume(void)
{
    lcm_init();
}

LCM_DRIVER jd9365_inx50_jmg_hd_lcm_drv =
{
    .name			= "jd9365_inx50_jmg_hd",
    .set_util_funcs = lcm_set_util_funcs,
    .get_params     = lcm_get_params,
    .init           = lcm_init,
    .suspend        = lcm_suspend,
    .resume         = lcm_resume,
    .init_power     = lcm_init_power,
    .resume_power   = lcm_resume_power,
    .suspend_power  = lcm_suspend_power,
};
