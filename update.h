/*
 *
 * University of Luxembourg
 * Laboratory of Algorithmics, Cryptology and Security (LACS)
 *
 * FELICS - Fair Evaluation of Lightweight Cryptographic Systems
 *
 * Copyright (C) 2015 University of Luxembourg
 *
 * Written in 2015 by Daniel Dinu <dumitru-daniel.dinu@uni.lu>
 *
 * This file is part of FELICS.
 *
 * FELICS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * FELICS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdint.h>
#include "constants.h"

void sBox(unsigned char *temp, int adet);

void lfsr_4(unsigned char *lfsr_consts, unsigned char *initial_value) ;

void perm120(unsigned char *state);

void IV_add_2bit(unsigned char *IV, unsigned char *temp5, int cnt);

void key_add_2bit(unsigned char *key, unsigned char *temp5, int cnt) ;

void const_add_dizy80(unsigned char round_consts, unsigned char *temp5) ;


void from8to5bits_120(unsigned char *temp5, unsigned char *state, int offSet) ;

void from5toBin_120(unsigned char *temp, unsigned char *temp5);

void fromBinto8_120(unsigned char *state, unsigned char *bin, int offSet) ;

void shifting_dizy80(unsigned char *temp5) ;
