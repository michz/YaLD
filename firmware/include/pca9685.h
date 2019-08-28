// source: http://www.ccsinfo.com/forum/viewtopic.php?t=47908 

/*
 * File:   pca9685_reg.h
 * Author: DevXP
 *
 * GNU GENERAL PUBLIC LICENSE
 * Created on April 2, 2012, 8:28 AM
 */

#ifndef pca9685_H
#define pca9685_H
/* General registers */
#define PCA9685 0x80                    // I2C address for PCA9865 with all inputs at zero
#define   Reset   0x01         // Reset the device
#define MODE1   0x00          // 0x00 location for Mode1 register address
#define MODE2   0x01          // 0x01 location for Mode2 reigster address
#define LED0    0x06          // location for start of LED0 registers
#define LEDCOUNT 15          // number of LEDS to light 15 max
/* Devices */                /* address pins:  A5    A0 */
#define LEDDRV1    0xA0    // 1st PCA9685      000000
#define LEDDRV2    0xB0    // 2nd PCA9685      000001
//#define LEDDRV1    0xb80    // 1st PCA9685      000000
//#define LEDDRV2    0xb82    // 2nd PCA9685      000001
#define LEDDRV3    0xd84    // 3rd PCA9685      000010
#define LEDDRV4    0xd86    // 4th PCA9685      000011
#define LEDDRV5    0xc88    // 5th PCA9685      000100
#define LEDDRV6    0xc8a    // 6th PCA9685      000101
#define LEDDRV7    0xc8c    // 7th PCA9685      000110
#define LEDDRV8    0xc8e    // 8th PCA9685      000111
#define LEDDRV9    0xc90    // 9th PCA9685      001000
/* MODE1 bits */
#define PCA9685_RESTART 0x80
#define PCA9685_EXTCLK  0x40
#define PCA9685_AI      0x20
#define PCA9685_SLEEP   0x10
#define PCA9685_SUB1    0x08
#define PCA9685_SUB2    0x04
#define PCA9685_SUB3    0x02
#define PCA9685_ALLCALL 0x01

/* MODE2 bits */
#define PCA9685_INVRT   0x10
#define PCA9685_OCH     0x08
#define PCA9685_OUTDRV  0x04
#define PCA9685_OUTNE1  0x02
#define PCA9685_OUTNE0  0x01

/* LEDX_ON_H bits */
#define PCA9685_LED_ON 0x10

/* LEDX_OFF_H bits */
#define PCA9685_LED_OFF 0x10


void pca9685_init(int address);

void pca9685_send_all(int address, long* PWMData);

void pca9685_send(int address, long value, int led);

void pca9685_brightness(int address, int percent, int led, long* PWMData);

void PCA9685AllLedOff(int address);

#endif 
