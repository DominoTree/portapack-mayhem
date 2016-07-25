/*
 * Copyright (C) 2015 Jared Boone, ShareBrained Technology, Inc.
 *
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __PORTAPACK_SHARED_MEMORY_H__
#define __PORTAPACK_SHARED_MEMORY_H__

#include <cstdint>
#include <cstddef>

#include "message_queue.hpp"

struct JammerRange {
	bool active;
	int64_t center;
	int64_t width;
	uint32_t duration;
};

/* NOTE: These structures must be located in the same location in both M4 and M0 binaries */
struct SharedMemory {
	static constexpr size_t application_queue_k = 11;
	static constexpr size_t app_local_queue_k = 11;

	uint8_t application_queue_data[1 << application_queue_k] { 0 };
	uint8_t app_local_queue_data[1 << app_local_queue_k] { 0 };
	const Message* volatile baseband_message { nullptr };
	MessageQueue application_queue { application_queue_data, application_queue_k };
	MessageQueue app_local_queue { app_local_queue_data, app_local_queue_k };

	char m4_panic_msg[32] { 0 };

	uint8_t radio_data[256];
	size_t bit_length;
	
	uint32_t afsk_samples_per_bit;
	uint32_t afsk_phase_inc_mark;
	uint32_t afsk_phase_inc_space;
	uint8_t afsk_repeat;
	uint32_t afsk_fmmod;
	bool afsk_transmit_done;
	bool afsk_alt_format;
	
	JammerRange jammer_ranges[16];
	
	char xylosdata[21];
	char epardata[13];
	int32_t excursion;
	
	bool transmit_done;
};

extern SharedMemory& shared_memory;

#endif/*__PORTAPACK_SHARED_MEMORY_H__*/
