#include <stdio.h>

#define PC
#define sboxCnt_dizy80 24
#define ROUNDS 15


unsigned char S[32] = {
        0x00, 0x04, 0x0e, 0x09, 0x0d, 0x0b, 0x1e, 0x1b, 0x1c, 0x14, 0x13, 0x18, 0x17, 0x1d, 0x05, 0x0c,
        0x0f, 0x11, 0x08, 0x15, 0x03, 0x1f, 0x19, 0x06, 0x10, 0x02, 0x16, 0x07, 0x1a, 0x0a, 0x01, 0x12
};

void sBox(unsigned char *sboxes, int count) {
    int k;
    for (k = 0; k < count; k++) {
        sboxes[k] = S[sboxes[k]];
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

void matrice(unsigned char sboxes){

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

void key_add(unsigned char *key, unsigned char *sboxes, unsigned char loop_count,
             unsigned char key_offSet) { // TODO 6 VE 4 KERE DONECEK
    int i;
    for (i = 0; i < loop_count; ++i) {
        sboxes[i * 4] ^= (key[i + key_offSet] & 192) >> 3
        sboxes[i * 4 + 1] ^= (key[i + key_offSet] & 48) >> 1
        sboxes[i * 4 + 2] ^= (key[i + key_offSet] & 12) << 1
        sboxes[i * 4 + 3] ^= (key[i + key_offSet] & 3) << 3
    }
}

void iv_add(unsigned char *iv, unsigned char *sboxes, unsigned char loop_count,
            unsigned char iv_offSet) { // TODO 6 VE 4 KERE DONECEK
    int i;
    for (i = 0; i < loop_count; ++i) {
        sboxes[i * 4] ^= (iv[i + iv_offSet] & 192) >> 3
        sboxes[i * 4 + 1] ^= (iv[i + iv_offSet] & 48) >> 1
        sboxes[i * 4 + 2] ^= (iv[i + iv_offSet] & 12) << 1
        sboxes[i * 4 + 3] ^= (iv[i + iv_offSet] & 3) << 3
    }
}

void const_add_dizy80(unsigned char round_consts, unsigned char *sboxes) {
    unsigned char sbox_cnt;
    for (sbox_cnt = 0; sbox_cnt < sboxCnt_dizy80; sbox_cnt++) {
        sboxes[sbox_cnt] ^= (round_consts);
    }
}


void from8to5bits_120(unsigned char *temp5, unsigned char *state, int offSet) {
    int i;
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
    int i;
    for (i = 0; i < 120; i += 5) {
        temp[i] = (temp5[i / 5] >> 4) & 1;
        temp[i + 1] = (temp5[i / 5] >> 3) & 1;
        temp[i + 2] = (temp5[i / 5] >> 2) & 1;
        temp[i + 3] = (temp5[i / 5] >> 1) & 1;
        temp[i + 4] = temp5[i / 5] & 1;
    }
}

void fromBinto8_120(unsigned char *state, unsigned char *bin, int offSet) {
    int i;
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

void sboxes_to_state(unsigned char *sboxes, unsigned char *states) {
    int i;
    for (i = 0; i < 3; ++i) {
        states[i] = (sboxes[i] << 3) + (sboxes[i + 1] >> 2);
        states[i + 1] = ((sboxes[i + 1] & 3) << 6) + (sboxes[i + 2] << 1) + (sboxes[i + 3] >> 4);
        states[i + 2] = ((sboxes[i + 3] & 15) << 4) + (sboxes[i + 4] >> 1)
        states[i + 3] = ((sboxes[i + 4] & 1) << 7) + (sboxes[i + 5] << 2) + (sboxes[i + 6] >> 3)
        states[i + 4] = ((sboxes[i + 6] & 7) << 5) + sboxes[i + 7]
    }
}

void permute_classes(unsigned char *sboxes) {
    unsigned char temp[3];

    temp[0] = sboxes[6];
    temp[1] = sboxes[7];    //TODO YEDEGE 2 KOYDUM
    temp[2] = sboxes[8];

    sboxes[6] = sboxes[3];
    sboxes[7] = sboxes[4];  //TODO 1.CLASSI IKINCI YERE KOYDUM
    sboxes[8] = sboxes[5];

    sboxes[3] = sboxes[12];
    sboxes[4] = sboxes[13]; //TODO 4.CLASSI BIRINCI YERE KOYDUM
    sboxes[5] = sboxes[14];

    sboxes[12] = temp[0];
    sboxes[13] = temp[1];   //TODO YEDEGI YANI 2YI DORDUNCU YERE KOYDUM
    sboxes[14] = temp[2];

    temp[0] = sboxes[9];
    temp[1] = sboxes[10];    //TODO YEDEGE 3 KOYDUM
    temp[2] = sboxes[11];

    sboxes[9] = sboxes[15];
    sboxes[10] = sboxes[16];  //TODO 5.CLASSI UCUNCU YERE KOYDUM
    sboxes[11] = sboxes[17];

    sboxes[15] = sboxes[18];
    sboxes[16] = sboxes[19];  //TODO 6.CLASSI BESINCI YERE KOYDUM
    sboxes[17] = sboxes[20];

    sboxes[18] = temp[0];
    sboxes[19] = temp[1];     //TODO YEDEGI YANI 3U ALTINCI YERE KOYDUM
    sboxes[20] = temp[2];
}

void dizy80_ksg(unsigned char *key, unsigned char *round_consts, unsigned char *IV) {
    unsigned char state[15] = {0};
    unsigned char sboxes[sboxCnt_dizy80];
    unsigned char bin[120];
    int l;
    int i;
    for (l = 0; l < 3; l++) {
        for (i = 0; i < ROUNDS; i++) {
            if (l == 0) {
                if (i == 0) {
                    key_add_2bit(key, sboxes, 2);
                }
            }
            if (l == 1) {
                if (i == 0) {
                    IV_add_2bit(IV, sboxes, 4);
                }
            }
            const_add_dizy80(round_consts[i], sboxes);
            sBox(sboxes, sboxCnt_dizy80);
            from5toBin_120(bin, temp5);
            perm120(bin);
            fromBinto8_120(state, bin, 1);
            from8to5bits_120(temp5, state, 1);
            permute_classes(sboxes);
            sboxes_to_state(sboxes, state)
        }
#ifdef PC
        printf("\nstate %d: %02x%02x%02x%02x\n", l, state[0], state[1], state[2], state[3]); //32 bits keystream output
#else
        unsigned char output[32];
        sprintf(output,"\nstate %d: %02x%02x%02x%02x\n", l, state[0], state[1], state[2], state[3]); //32 bits keystream output
        send_USART_str(output);
#endif
    }
}

#ifdef PC

int main() {
    unsigned char round_consts[ROUNDS];
    unsigned char init_poly[4] = {1, 0, 0, 0};
    unsigned char key[2] = {1, 1};
    unsigned char IV[4] = {1, 1, 1, 1};
    lfsr_4(round_consts, init_poly);
    dizy80_ksg(key, round_consts, IV);

    return 0;
}

#else
#include "../stm32f4_wrapper.h"
int main(void)
{
unsigned char output[32];
    clock_setup();
    gpio_setup();
    usart_setup(115200);
    
    sprintf((char *)output, "done!");
        send_USART_str(output);

    signal_host();
    return 0;
}
#endif
