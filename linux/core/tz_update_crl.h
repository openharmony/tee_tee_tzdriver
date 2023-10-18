/*
 * tz_update_crl.h
 *
 * function for update crl
 *
 * Copyright (c) 2012-2022 Huawei Technologies Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef TZ_UPDATE_CRL_H
#define TZ_UPDATE_CRL_H
#include "teek_ns_client.h"

#define DEVICE_CRL_MAX 0x4000 /* 16KB */
int send_crl_to_tee(const char *crl_buffer, uint32_t crl_len, const struct tc_ns_dev_file *dev_file);
int tc_ns_update_ta_crl(const struct tc_ns_dev_file *dev_file, void __user *argp);
int tz_update_crl(const char *file_path, const struct tc_ns_dev_file *dev_file);

#endif