#include "pwmout.h"
#include "pca9685.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Translation from 8bit to 12bit (kind of logarithmic scale) */
const static int eight_to_twelve_bit_table[] = {
    0,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,
    7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,11,11,12,12,12,13,13,14,14,
    15,15,15,16,17,17,18,18,19,19,20,21,21,22,23,24,24,25,26,27,
    28,29,30,31,32,33,34,35,36,37,39,40,41,43,44,45,47,48,50,52,
    53,55,57,59,61,63,65,67,69,72,74,77,79,82,84,87,90,93,96,99,
    103,106,110,113,117,121,125,129,133,138,142,147,152,157,162,
    168,173,179,185,191,197,204,210,217,225,232,240,248,256,264,
    273,282,292,301,311,322,332,343,355,366,379,391,404,417,431,
    446,460,476,491,508,525,542,560,579,598,618,638,659,681,704,
    727,751,776,802,828,856,884,913,944,975,1007,1041,1075,1111,
    1148,1186,1225,1266,1308,1351,1396,1442,1490,1539,1590,1643,
    1697,1754,1812,1872,1934,1998,2064,2133,2203,2277,2352,2430,
    2511,2594,2680,2769,2860,2955,3053,3154,3259,3367,3479,3594,
    3713,3836,3964,4095};


/** PWM data variables, 16bit vide, 12bit used */
/*volatile*/
long PWMData[32] = {
    0x0,    // Channel 0
    0x0,    // Channel 1
    0x0,    // Channel 2
    0x0,    // Channel 3
    0x0,    // Channel 4
    0x0,    // Channel 5
    0x0,    // Channel 6
    0x0,    // Channel 7
    0x0,    // Channel 8
    0x0,    // Channel 9
    0x0,    // Channel 10
    0x0,    // Channel 11
    0x0,    // Channel 12
    0x0,    // Channel 13
    0x0,    // Channel 14
    0x0,    // Channel 15
    0x0,    // Channel 16
    0x0,    // Channel 17
    0x0,    // Channel 18
    0x0,    // Channel 19
    0x0,    // Channel 20
    0x0,    // Channel 21
    0x0,    // Channel 22
    0x0,    // Channel 23
    0x0,    // Channel 24
    0x0,    // Channel 25
    0x0,    // Channel 26
    0x0,    // Channel 27
    0x0,    // Channel 28
    0x0,    // Channel 29
    0x0,    // Channel 30
    0x0     // Channel 31
};

void pwmout_init_output() {
    pca9685_init(LEDDRV1);
    pca9685_init(LEDDRV2);
}

void pwmout_write_output(volatile uint8_t source[]) {
    for (int i = 0; i < 32; ++i) {
        PWMData[i] = eight_to_twelve_bit_table[source[i]];
    }

    pca9685_send_all(LEDDRV1, PWMData);
    pca9685_send_all(LEDDRV2, PWMData+16);
}

#ifdef __cplusplus
}
#endif
