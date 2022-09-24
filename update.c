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

void sBox(unsigned char *temp, int adet) {
    int k;
    for (k = 0; k < adet; k++) {
        temp[k] = S[temp[k]];
    }
}

void lfsr_4(unsigned char *lfsr_consts, unsigned char *initial_value) {

    int i;
    unsigned char fb;
    unsigned char rg[4];
    for (i = 0; i < 4; i++) {
        rg[i] = initial_value[i];
    }
    for (i = 0; i < 15; i++) {
        unsigned char output = (rg[0] << 3 | rg[1] << 2 | rg[2] << 1 | rg[3]);
        lfsr_consts[i] = output;

        fb = rg[0] ^ rg[3];
        rg[0] = rg[1];
        rg[1] = rg[2];
        rg[2] = rg[3];
        rg[3] = fb;
    }
}

void perm120(unsigned char *state) {
    int i;
    unsigned char temp[120] = {0};

    for (i = 0; i < 4; i++) {
        temp[i * 30] = state[(i * 30) + 6] ^ state[(i * 30) + 22];
        temp[(i * 30) + 1] = state[(i * 30) + 16] ^ state[(i * 30) + 18];
        temp[(i * 30) + 2] = state[i * 30] ^ state[(i * 30) + 18];
        temp[(i * 30) + 3] = state[(i * 30) + 15];
        temp[(i * 30) + 4] = state[(i * 30) + 1];

        temp[(i * 30) + 5] = state[(i * 30) + 7] ^ state[(i * 30) + 27];
        temp[(i * 30) + 6] = state[(i * 30) + 20] ^ state[(i * 30) + 13];
        temp[(i * 30) + 7] = state[(i * 30) + 2] ^ state[(i * 30) + 23];
        temp[(i * 30) + 8] = state[(i * 30) + 21];
        temp[(i * 30) + 9] = state[(i * 30) + 11];

        temp[(i * 30) + 10] = state[(i * 30) + 12] ^ state[(i * 30) + 17];
        temp[(i * 30) + 11] = state[(i * 30) + 26] ^ state[(i * 30) + 3];
        temp[(i * 30) + 12] = state[(i * 30) + 10] ^ state[(i * 30) + 28];
        temp[(i * 30) + 13] = state[(i * 30) + 25];
        temp[(i * 30) + 14] = state[(i * 30) + 5];

        temp[(i * 30) + 15] = state[(i * 30) + 2] ^ state[(i * 30) + 27];
        temp[(i * 30) + 16] = state[(i * 30) + 21] ^ state[(i * 30) + 9];
        temp[(i * 30) + 17] = state[(i * 30) + 11] ^ state[(i * 30) + 24];
        temp[(i * 30) + 18] = state[(i * 30) + 16];
        temp[(i * 30) + 19] = state[i * 30];

        temp[(i * 30) + 20] = state[(i * 30) + 7] ^ state[(i * 30) + 17];
        temp[(i * 30) + 21] = state[(i * 30) + 15] ^ state[(i * 30) + 14];
        temp[(i * 30) + 22] = state[(i * 30) + 1] ^ state[(i * 30) + 29];
        temp[(i * 30) + 23] = state[(i * 30) + 20];
        temp[(i * 30) + 24] = state[(i * 30) + 10];

        temp[(i * 30) + 25] = state[(i * 30) + 12] ^ state[(i * 30) + 25];
        temp[(i * 30) + 26] = state[(i * 30) + 22] ^ state[(i * 30) + 4];
        temp[(i * 30) + 27] = state[(i * 30) + 5] ^ state[(i * 30) + 19];
        temp[(i * 30) + 28] = state[(i * 30) + 26];
        temp[(i * 30) + 29] = state[(i * 30) + 6];
    }

    for (i = 0; i < 120; i++) {
        state[i] = temp[i];
    }
}

void IV_add_2bit(unsigned char *IV, unsigned char *temp5, int cnt) {
    unsigned char i;
    for (i = 0; i < cnt; i++) {
        temp5[i] ^= (IV[i] << 3);
    }
}

void key_add_2bit(unsigned char *key, unsigned char *temp5, int cnt) {
    unsigned char i;
    for (i = 0; i < cnt; i++) {
        temp5[i] ^= (key[i] << 3);
    }
}

void const_add_dizy80(unsigned char round_consts, unsigned char *temp5) {
    unsigned char sbox_cnt;
    for (sbox_cnt = 0; sbox_cnt < sboxCnt_dizy80; sbox_cnt++) {
        temp5[sbox_cnt] ^= (round_consts);
    }
}


void from8to5bits_120(unsigned char *temp5, unsigned char *state, int offSet) {
    int i = 0;
    for (i = 0; i < sboxCnt_dizy80; i += 8) {
        temp5[i] = (state[((5 * i) / 8) + 1 - offSet] >> 3) & 0x1f;
        temp5[i + 1] = (state[((5 * i) / 8) + 1 - offSet] & 0x7) << 2 | (state[((5 * i) / 8) + 2 - offSet] >> 6) & 0x3;
        temp5[i + 2] = (state[((5 * i) / 8) + 2 - offSet] >> 1) & 0x1f;
        temp5[i + 3] = (state[((5 * i) / 8) + 2 - offSet] & 0x1) << 4 | (state[((5 * i) / 8) + 3 - offSet] >> 4) & 0xf;
        temp5[i + 4] = (state[((5 * i) / 8) + 3 - offSet] & 0xf) << 1 | (state[((5 * i) / 8) + 4 - offSet] >> 7) & 0x1;
        temp5[i + 5] = (state[((5 * i) / 8) + 4 - offSet] >> 2) & 0x1f;
        temp5[i + 6] = (state[((5 * i) / 8) + 4 - offSet] & 0x3) << 3 | (state[((5 * i) / 8) + 5 - offSet] >> 5);
        temp5[i + 7] = state[((5 * i) / 8) + 5 - offSet] & 0x1f;
    }
}

void from5toBin_120(unsigned char *temp, unsigned char *temp5) {
    int i = 0;
    for (i = 0; i < 120; i += 5) {
        temp[i] = (temp5[i / 5] >> 4) & 1;
        temp[i + 1] = (temp5[i / 5] >> 3) & 1;
        temp[i + 2] = (temp5[i / 5] >> 2) & 1;
        temp[i + 3] = (temp5[i / 5] >> 1) & 1;
        temp[i + 4] = temp5[i / 5] & 1;
    }
}

void fromBinto8_120(unsigned char *state, unsigned char *bin, int offSet) {
    int i = 0;
    state[0] = 0;
    for (i = 0; i < ROUNDS; ++i) {
        state[i + 1 - offSet] =
                ((bin[8 * i] & 1) << 7) | ((bin[(8 * i) + 1] & 1) << 6) | ((bin[(8 * i) + 2] & 1) << 5) |
                ((bin[(8 * i) + 3] & 1) << 4) | ((bin[(8 * i) + 4] & 1) << 3) | ((bin[(8 * i) + 5] & 1) << 2) |
                ((bin[(8 * i) + 6] & 1) << 1) | bin[(8 * i) + 7] & 1;
    }
}

void shifting_dizy80(unsigned char *temp5) {
    unsigned char temp[18];
    int i;

    for (i = 0; i < 18; i++) {
        temp[i] = temp5[i + 3];
    }

    temp5[3] = temp[9];
    temp5[4] = temp[10];
    temp5[5] = temp[11];

    temp5[6] = temp[0];
    temp5[7] = temp[1];
    temp5[8] = temp[2];

    temp5[9] = temp[12];
    temp5[10] = temp[13];
    temp5[11] = temp[14];

    temp5[12] = temp[3];
    temp5[13] = temp[4];
    temp5[14] = temp[5];

    temp5[15] = temp[15];
    temp5[16] = temp[16];
    temp5[17] = temp[17];

    temp5[18] = temp[6];
    temp5[19] = temp[7];
    temp5[20] = temp[8];
}

