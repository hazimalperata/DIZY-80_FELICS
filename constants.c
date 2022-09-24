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


/*
 *
 * Cipher constants
 *
 */
/* Replace with the cipher constants definition */
/*SBOX_BYTE S0[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
SBOX_BYTE S1[16] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};*/
RAM_DATA_BYTE S[32] = {
        0x00, 0x04, 0x0e, 0x09, 0x0d, 0x0b, 0x1e, 0x1b, 0x1c, 0x14, 0x13, 0x18, 0x17, 0x1d, 0x05, 0x0c,
        0x0f, 0x11, 0x08, 0x15, 0x03, 0x1f, 0x19, 0x06, 0x10, 0x02, 0x16, 0x07, 0x1a, 0x0a, 0x01, 0x12
};
RAM_DATA_BYTE RC[15] = {0};
