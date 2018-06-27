/*
Copyright 2018 Zoltan Bakcsa (zoltan@bakcsa.hu)

 This file is part of ATS (ARM Task Scheduler).

ATS (ARM Task Scheduler) is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as published by
the Free Software Foundation.

ATS (ARM Task Scheduler) is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/gpl-3.0-standalone.html>.
*/

/**
 * @file ATS.h
 * @author Zoltan Bakcsa (zoltan@bakcsa.hu)
 * @date 12 Jun 2018
 * ATS main source file. It contains most of the implementation
 * @copyright https://www.gnu.org/licenses/gpl-3.0-standalone.html
 */

#ifndef ATS_H_
#define ATS_H_

#include <stdint.h>
#include <string.h>
#include "ats_config.h"
#include "ats_structures.h"

#define ats_result		uint8_t
#define	OK				0
#define	ERROR			1

void			ats_init(void (*report_task_invocation_)(ats_task *task),void (*sleep_)(void));
void			ats_reset();
ats_result		ats_get_free_task_slot(ats_task **task);
void			ats_release_task_slot(ats_task *task);
void			ats_systick();
void			ats_start();
void			ats_stop();


#endif /* ATS_H_ */
