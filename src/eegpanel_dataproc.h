/*
	Copyright (C) 2008-2009 Nicolas Bourdaud <nicolas.bourdaud@epfl.ch>

    This file is part of the eegpanel library

    The eegpan library is free software: you can redistribute it and/or
    modify it under the terms of the version 3 of the GNU General Public
    License as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef EEGPANEL_DATAPROC_H
#define EEGPANEL_DATAPROC_H

#include <filter.h>
#include "eegpanel.h"

typedef enum {
	EEG_LOWPASS_FILTER = EEG_LOWPASS_FLT,
	EEG_HIGHPASS_FILTER = EEG_HIGHPASS_FLT,
	EXG_LOWPASS_FILTER = SENSOR_LOWPASS_FLT,
	EXG_HIGHPASS_FILTER = SENSOR_HIGHPASS_FLT,
	EEG_DECIMATION_FILTER,
	EXG_DECIMATION_FILTER,
	EEG_OFFSET_FILTER,
	EXG_OFFSET_FILTER,
	NUM_FILTERS
} EnumFilter;


typedef struct _Indicators {
	unsigned int cms_in_range	: 1;
	unsigned int low_battery	: 1;
} Indicators;

struct InternalFilterState {
	hfilter filt;
	float fc;
	unsigned int numch;
	int reinit;
};
struct PanelDataProc {
	struct InternalFilterState filstate[NUM_FILTERS];
};

void add_samples(EEGPanel* pan, const float* eeg, const float* exg, const uint32_t* triggers, unsigned int num_samples);
int set_data_input(EEGPanel* pan, int num_samples);
void update_filter(EEGPanel* pan, EnumFilter type);
void destroy_dataproc(EEGPanel* pan);

#endif /* EEGPANEL_DATAPROC_H */
