/*
 * log_pages_cfg.c
 *
 * for pages log cfg api define
 *
 * Copyright (C) 2022 Huawei Technologies Co., Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */
#include "log_cfg_api.h"

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/delay.h>
#include <linux/stat.h>
#include <linux/slab.h>

#include <securec.h>
#include "tc_ns_log.h"
#include "tlogger.h"
#include "los_adapt.h"

void unregister_log_exception(void)
{
}
int register_log_exception(void)
{
	return 0;
}

struct pages_module_result {
	uint64_t log_addr;
	uint32_t log_len;
};

struct pages_module_result g_mem_info = {0};

#define SZ_1K (0x00000400)

#ifdef CONFIG_512K_LOG_PAGES_MEM
#define PAGES_LOG_MEM_LEN   (512 * SZ_1K) /* mem size: 512 k */
#else
#define PAGES_LOG_MEM_LEN   (256 * SZ_1K) /* mem size: 256 k */
#endif

static int tee_pages_register_core(void)
{
	g_mem_info.log_addr = (uintptr_t)__get_free_pages(
		GFP_KERNEL | __GFP_ZERO, PAGES_LOG_MEM_LEN);
	if (IS_ERR_OR_NULL((void *)(uintptr_t)g_mem_info.log_addr)) {
		tloge("get log mem error\n");
		return -1;
	}

	g_mem_info.log_len = PAGES_LOG_MEM_LEN;
	return 0;
}

/* Register log memory */
int register_log_mem(uint64_t *addr, uint32_t *len)
{
	int ret;
	uint64_t mem_addr;
	uint32_t mem_len;

	if (!addr || !len) {
		tloge("check addr or len is failed\n");
		return -1;
	}

	ret = tee_pages_register_core();
	if (ret)
		return ret;

	mem_addr = virt_to_phys((void *)(uintptr_t)g_mem_info.log_addr);
	mem_len = g_mem_info.log_len;

	ret = register_mem_to_teeos(mem_addr, mem_len, true);
	if (ret)
		return ret;

	*addr = g_mem_info.log_addr;
	*len = g_mem_info.log_len;
	return ret;
}

void report_log_system_error(void)
{
}

void report_log_system_panic(void)
{
/* default support trigger ap reset */
#ifndef NOT_TRIGGER_AP_RESET
	panic("TEEOS panic\n");
#endif
}

void ta_crash_report_log(void)
{
}

int *map_log_mem(uint64_t mem_addr, uint32_t mem_len)
{
	(void)mem_len;
	return (int *)(uintptr_t)mem_addr;
}

void unmap_log_mem(int *log_buffer)
{
	free_pages((void *)(unsigned long)(uintptr_t)log_buffer,
		get_order(PAGES_LOG_MEM_LEN));
}

#define ROOT_UID				0

#ifdef LAST_TEE_MSG_ROOT_GID
#define FILE_CHOWN_GID			0
#else
/* system gid for last_teemsg file sys chown */
#define FILE_CHOWN_GID			1000
#endif

void get_log_chown(uid_t *user, gid_t *group)
{
	if (!user || !group) {
		tloge("user or group buffer is null\n");
		return;
	}

	*user = ROOT_UID;
	*group = FILE_CHOWN_GID;
}
