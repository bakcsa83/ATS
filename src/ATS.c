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
 * @file ATS.c
 * @author Zoltan Bakcsa (zoltan@bakcsa.hu)
 *
 * ATS main source file. It contains most of the implementation
 * @copyright https://www.gnu.org/licenses/gpl-3.0-standalone.html
 */

#include "ATS.h"
#define IN_USE	1
#define FREE	0
static ats_task tasks[MAX_TASKS];
static uint8_t task_slot_status[MAX_TASKS];	///1=Task slot is in use; 0=Task slot is free
static volatile uint8_t is_running;			/// 0 means ATS is not running. 1 means ATS is running

void (*report_error)(uint8_t error_code);
void (*report_task_invocation)(ats_task *task);
void (*sleep)();

/**
 * Initializes the framework
 *
 * \param report_error Function pointer.
 */
void ats_init(void (*report_error_)(uint8_t error_code), void (*report_task_invocation_)(ats_task *task), void (*sleep_)()) {
	report_error = report_error_;
	report_task_invocation = report_task_invocation_;
	sleep=sleep_;
	ats_reset();
}

/**
 * Internal function that calculates task ranks and returns
 * the task with the highest rank.
 */
static ats_task *calculate_rank();

/**
 * Resets all internal variables to 0, drops all tasks.
 */

void ats_reset() {
	memset(tasks, 0, sizeof(ats_task) * MAX_TASKS);
	is_running = 0;
}

ats_result ats_get_free_task_slot(ats_task **task) {
	for (uint8_t i = 0; i < MAX_TASKS; i++) {
		if (task_slot_status[i] == FREE) {
			task_slot_status[i] = IN_USE;
			*task = &tasks[i];
			return OK;
		}
	}

	*task = NULL;
	return ERROR;
}

void ats_release_task_slot(ats_task *task) {
	memset(task, 0, sizeof(ats_task));
	for (uint8_t i = 0; i < MAX_TASKS; i++) {
		if (&tasks[i] == task) {
			task_slot_status[i] = FREE;
			return;
		}
	}
}

void ats_systick() {
	for (uint8_t i = 0; i < MAX_TASKS; i++) {
		if (tasks[i].run == NULL)
			return;
		if (tasks[i].status > ATS_QUIET)
			tasks[i].age++;
	}
}

void ats_start() {
	is_running = 1;
	ats_task *task_to_run;
	while (is_running) {
		task_to_run = calculate_rank();
		if (task_to_run != NULL) {
			task_to_run->run(task_to_run->task_reference);
			if (report_task_invocation != NULL)
				report_task_invocation(task_to_run);
		}
		else{
			if(sleep!=NULL) sleep();
		}
	}
}

void ats_stop() {
	is_running = 0;
}

static ats_task *calculate_rank() {
	ats_task *task = NULL;
	for (uint8_t i = 0; i < MAX_TASKS; i++) {
		if (tasks[i].run == NULL)
			break;
		tasks[i].rank = tasks[i].status * tasks[i].status * tasks[i].priority + tasks[i].age;
	}

	for (uint8_t i = 0; i < MAX_TASKS; i++) {
		if (tasks[i].run == NULL)
			break;
		if (task == NULL || task->rank < tasks[i].rank) {
			task = &tasks[i];
		}
	}
	return task;
}
