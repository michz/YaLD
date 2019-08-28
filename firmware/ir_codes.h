/**
 * @file
 * @author  Michael Zapf
 */

#ifndef __IR_CODES_H
#define __IR_CODES_H

#ifdef TARGET_STORM

#define BTN_POWER       0x20
#define BTN_MUTE        0x2b
#define BTN_1           0x11
#define BTN_2           0x12
#define BTN_3           0x13
#define BTN_4           0x14
#define BTN_5           0x15
#define BTN_6           0x16
#define BTN_7           0x17
#define BTN_8           0x18
#define BTN_9           0x19
#define BTN_0           0x10
#define BTN_PRUP        0x1c
#define BTN_PRDOWN      0x1b
#define BTN_VOLUP       0x24
#define BTN_VOLDOWN     0x25
#define BTN_RED         0x26
#define BTN_GREEN       0x2c
#define BTN_YELLOW      0x2e
#define BTN_BLUE        0x33
#define BTN_PINK        0x2f
#define BTN_MIX         0x4
#define BTN_P100        0x6
#define BTN_SOUND       0xb

#endif
#ifdef TARGET_DESK

// RGB-Stripe Decke: 7 17 18

#define BTN_POWER       0x1f
#define BTN_MUTE        0x1b
#define BTN_1           0x1
#define BTN_2           0x2
#define BTN_3           0x3
#define BTN_4           0x4
#define BTN_5           0x5
#define BTN_6           0x6
#define BTN_7           0x7
#define BTN_8           0x8
#define BTN_9           0x9
#define BTN_0           0x0
#define BTN_PRUP        0x30
#define BTN_PRDOWN      0x34
#define BTN_VOLUP       0x18
#define BTN_VOLDOWN     0x1c
#define BTN_RED         0xA
#define BTN_GREEN       0x29
#define BTN_YELLOW      0xB
#define BTN_BLUE        0x28
#define BTN_PINK        0x14
#define BTN_MIX         0x17
#define BTN_P100        0x16
#define BTN_SOUND       0xFF

#endif


#endif // __IR_CODES_H
