/*
 * power-manager
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/


/**
 * @file	pm_core.h
 * @author	Suchang Woo (suchang.woo@samsung.com)
 * @modified by Wonil Choi (wonil22.choi@samsung.com)
 * @version	0.2
 * @brief	 Power manager main loop header file
 */
#ifndef __POWER_MANAGER_H__
#define __POWER_MANAGER_H__

#include "util.h"
#include "pm_poll.h"
#include "pm_llinterface.h"
#include "pm_setting.h"
#include "pm_conf.h"

#define WITHOUT_STARTNOTI	0x1
#define MASK_BIT 0x7		/* 111 */
#define MASK_DIM 0x1		/* 001 */
#define MASK_OFF 0x2		/* 010 */
#define MASK_SLP 0x4		/* 100 */

#define VCALL_FLAG		0x00000001
#define LOWBT_FLAG		0x00000100
#define CHRGR_FLAG		0x00000200
#define PWRSV_FLAG		0x00000400
#define BRTCH_FLAG		0x00002000

#define TOLERANCE_SLOT		2

unsigned int status_flag;

/*
 * State enumeration
 */
enum state_t {
	S_START = 0,
	S_NORMAL,		/*< normal state */
	S_LCDDIM,		/*< LCD dimming */
	S_LCDOFF,		/*< LCD off */
	S_SLEEP,		/*< system suspend */
	S_END
};

/* 
 * Global variables
 *   cur_state   : current state
 *   states      : state definitions
 *   trans_table : state transition table
 */
int cur_state;
int old_state;

/*
 * @brief State structure
 */
struct state {
	enum state_t state;					/**< state number */
	int (*trans) (int evt);		/**< transition function pointer */
	int (*action) (int timeout);	/**< enter action */
	int (*check) (int next);	/**< transition check function */
	int timeout;
} states[S_END];

/* If the bit in a condition variable is set, 
 *  we cannot transit the state until clear this bit. */
int trans_condition;
pid_t idle_pid;
int (*pm_init_extention) (void *data);		/**< extention init function */
void (*pm_exit_extention) (void);		/**< extention exit function */
int check_processes(enum state_t prohibit_state);

/*
 * Power manager Main loop
 *
 * @internal
 * @param[in] flags If the first bit of this is set, start managing without Start notification.
 * 					If the second bit of ths is set, use unified device manager functions.
 */
void start_main(unsigned int flags);

/**
 * @}
 */

#endif
