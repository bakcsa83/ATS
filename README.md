# ATS - ARM Task Scheduler

ATS is a simple task manager framework for microcontrollers. It meant to schedule multiple, **interrupt triggered** tasks
on a way that always the most critical one gets executed.

## How does it work?
ATS uses the `ats_task` type for task management. `ats_task` has different properties and a function pointer:  

```C
typedef struct ats_task{
	void						(*handler)(void *task_reference);
	void						*task_reference;
	ats_task_status			status;
	uint8_t					age;
	ats_task_priority		priority;
}ats_task;
```
### Priority
The priority describes how time critical is the task in general.

```C
typedef enum ats_task_priority{
	ATS_LOW=1,
	ATS_NORMAL=2,
	ATS_HIGH=3
}ats_task_priority;
```
Most of the tasks should be defined as `ATS_NORMAL`.
`ATS_LOW` could be used for tasks which are not time sensitive at all. (e.g. temperature measurement)
`ATS_HIGH` could be used for time critical tasks like a sender or receiver function of timeslot based protocol.

Priority does not change at runtime. 

### Status 
The status meant to represent the level of an internal buffer, remaining time before timeout or other status of the task. 
The purpose of this property is to let the framework know how urgent would be to run the task. This property represents 
the current status which can change any time.

```C
typedef enum ats_task_status{
	ATS_QUIET=0,
	ATS_ATTENTION_NEEDED=1,
	ATS_URGENT_ACTION_REQUIRED=2,
	ATS_IMMEDIATE_ACTION_REQUIRED=3
}ats_task_status;
```
### Age
ATS periodically checks all tasks and increments their `Age` if the status is higher than `Quiet`. The age property ensures that low priority
tasks won't be delayed to much even if there are high priority tasks waiting.

### Task reference 
`task_reference` is a technical helper property.

### Run function
The `void (*run)(void *task_reference)` function pointer points to the function which implements the task.
