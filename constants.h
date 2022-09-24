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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "data_types.h"


/*
 *
 * Cipher characteristics:
 *  STATE_SIZE - the cipher state size in bytes
 *  KEY_SIZE - the cipher key size in bytes
 *  IV_SIZE - the cipher round keys size in bytes
 *  TEST_STREAM_SIZE - the cipher test stream size in bytes
 *
 */
#define STATE_SIZE 15 /* Replace with the cipher state size in bytes */

#define KEY_SIZE 10 /* Replace with the cipher key size in bytes */
#define IV_SIZE 10 /* Replace with the cipher IV size in bytes */

#define TEST_STREAM_SIZE 4 /* Replace with the test stream size in bytes */
#define ROUNDS 15
#define sboxCnt_dizy80 24

/*
 *
 * Cipher constants
 *
 */
/* Replace with the cipher constants declaration */
extern RAM_DATA_BYTE S[32];
extern RAM_DATA_BYTE RC[15];

#endif /* CONSTANTS_H */
