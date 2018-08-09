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

#ifndef ATS_CONFIG_H_
#define ATS_CONFIG_H_

/**
 * Defines the maximum of manageable tasks.
 * This value must not be greater than 255 (max value of uint8_t)
 */
#define	MAX_TASKS		20

#endif /* ATS_CONFIG_H_ */
