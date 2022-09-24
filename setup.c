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

#include "cipher.h"
#include "update.h"


void Setup(uint8_t *state, uint8_t *key, uint8_t *iv)
{
	unsigned char init_poly[4] = {1, 0, 0, 0};
    unsigned char temp5[sboxCnt_dizy80];
    unsigned char bin[120];
    lfsr_4(RC, init_poly);
    int l;
    int i;
    for (l = 0; l < 2; l++) {
        for (i = 0; i < ROUNDS; i++) {
            from8to5bits_120(temp5, state, 1);
            if (l == 0) {
                if (i == 0) {
                    key_add_2bit(key, temp5, 2);
                }
            }
            if (l == 1) {
                if (i == 0) {
                    IV_add_2bit(iv, temp5, 4);
                }
            }
            const_add_dizy80(RC[i], temp5);
            sBox(temp5, sboxCnt_dizy80);
            from5toBin_120(bin, temp5);
            perm120(bin);
            fromBinto8_120(state, bin, 1);
            from8to5bits_120(temp5, state, 1);
            shifting_dizy80(temp5);
            from5toBin_120(bin, temp5);
            fromBinto8_120(state, bin, 1);
        }
	}
}
