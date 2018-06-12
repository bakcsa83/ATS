/*
 * ats_structures.h
 *
 *  Created on: 12 Jun 2018
 *      Author: bakcsa
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
	const	ats_task_priority		priority;
			uint16_t				rank;
}ats_task;

#endif /* ATS_STRUCTURES_H_ */
