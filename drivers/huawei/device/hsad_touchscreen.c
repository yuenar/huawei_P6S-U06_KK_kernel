/*
 *
 * Copyright (C) 2013 HUAWEI Device Corp,Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/kernel.h>
#include <hsad/config_mgr.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#define HSAD_DEV_NAME_LEN 64

int hsad_tp_get_gpio(char *name)
{
	int gpio = 0;

	if (get_hw_config_int(name, &gpio, NULL ) == false) {
		pr_err("%s: fail.\n", __func__);
		return -1;
	}

	return gpio;
}

int hsad_tp_get_type(void)
{
	bool ret;
	int value = 0;

	ret = get_hw_config_int("touchscreen/type", &value, NULL);
	if (ret == true) {
		return value;
	}

	return value;
}
int hsad_tp_get_fw_type(void)
{
	bool ret;
	int value = 0;

	ret = get_hw_config_int("touchscreen/fw_type", &value, NULL);
	if (ret == true) {
		return value;
	}

	return value;
}

int hsad_get_cyttsp4_enable(void)
{
	bool ret;
	int value = 0;

	ret = get_hw_config_int("touchscreen/cyttsp4_enable", &value, NULL);
	if (ret == true) {
		return value;
	}

	return value;
}

int hsad_get_rmi_enable(void)
{
	bool ret;
	int value = 0;

	ret = get_hw_config_int("touchscreen/rmi_enable", &value, NULL);
	if (ret == true) {
		return value;
	}

	return value;
}

