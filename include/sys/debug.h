/*
 * Copyright (c) 2011-2012 LeafGrass <leafgrass.g@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 */

/*
 * @file    include/sys/debug.h
 * @brief   debuging services
 * @log     2011.8 initial revision
 */

#ifndef __SYS_DEBUG_H__
#define __SYS_DEBUG_H__

#define LOG_ALL		0
#define LOG_DEBUG	1
#define LOG_INFO	2
#define LOG_WARN	3
#define LOG_ERROR	4
#define LOG_CRITICAL	5
#define LOG_LEVEL	LOG_INFO

#define __dec		(os_systime_get()/1000)
#define __frac		(os_systime_get()%1000)
#define _OS_PRINTF(level, msg, args...) \
	do { \
		if (level >= LOG_LEVEL) { \
			os_printf(msg, ##args); \
		} \
	} while (0)
#define _OS_PRINTK(level, msg, args...) \
	do { \
		if (level >= LOG_LEVEL) { \
			os_printf("[%6u.%03u] " msg, __dec, __frac, ##args); \
		} \
	} while (0)

#define ASSERT_NONE	0
#define ASSERT_ALL	1
#define ASSERT_LEVEL	ASSERT_ALL

inline void _os_assert_fail(const char *p_file, int line, const char *p_exp);

#if defined(OUSIA_DEBUG_ASSERT) && (ASSERT_LEVEL >= ASSERT_ALL)
#define _OS_ASSERT(exp) \
	do { \
		if (exp) { \
		} else { \
			_os_assert_fail(__FILE__, __LINE__, #exp); \
		} \
	} while (0)
#else
#define _OS_ASSERT(exp) (void)((0))
#endif

#define os_assert(exp)			_OS_ASSERT(exp)
#define os_log(level, msg, args...)	_OS_PRINTF(level, msg, ##args)
#define os_printk(level, msg, args...)	_OS_PRINTK(level, msg, ##args)
#ifdef OUSIA_DEBUG_LOW_LEVEL
#define lldbg(msg, args...)		os_lldbg(msg, ##args)
#else
#define lldbg(msg, args...)
#endif

#endif /* __SYS_DEBUG_H__ */
