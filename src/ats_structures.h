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

#ifndef ATS_STRUCTURES_H_
#define ATS_STRUCTURES_H_

#include <stdint.h>

/**
 * Member of the \link ats_task \endlink.
 * The status meant to represent the level of an internal buffer, remaining time before timeout or other status of the task.
 * The purpose of this property is to let the framework know how urgent would be to run the task. This property represents
 * the current status which can change any time.
 *
 */
typedef enum ats_task_status{
	ATS_QUIET=0,
	ATS_ATTENTION_NEEDED=1,
	ATS_URGENT_ACTION_REQUIRED=2,
	ATS_IMMEDIATE_ACTION_REQUIRED=3
}ats_task_status;

/**
 * Member of the \link ats_task \endlink.
 * Priority describes how time critical is the task in general.
 *
 */
typedef enum ats_task_priority{
	ATS_LOW=1,
	ATS_NORMAL=2,
	ATS_HIGH=3
}ats_task_priority;

typedef struct ats_task{
			uint8_t					task_number;
			void					(*run)(void *task_reference);
			void					*task_reference;
	volatile uint8_t				age;
			ats_task_status			status;
			ats_task_priority		priority;
			uint16_t				rank;
}ats_task;

#endif /* ATS_STRUCTURES_H_ */
