/**
 * @file
 * @author  Michael Zapf
 */

#ifndef __IR_MODE_H
#define __IR_MODE_H

#include <avr/io.h>
#include <util/delay.h>
#include "ir_codes.h"
#include "led.h"
#include "irmp/irmp.h"

#define RAND16_SEED  1337
#include "FastLED/led_sysdefs.h"
#include "FastLED/lib8tion.h"

#ifdef TARGET_STORM
#define IR_ADDRESS      (0x0)
#endif                                                                          
#ifdef TARGET_DESK
#define IR_ADDRESS      (0x14)
#endif 

#define IR_CHANNELS     (32)


#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t ir_raw[IR_CHANNELS];

void ir_mode(void);

typedef struct channel_function {
    uint8_t     channel;
    uint8_t     start;
    uint8_t     step;
    uint8_t     speed;
    uint8_t     target;
    uint8_t     parameters[4];
    uint8_t     id;
    void        (*f)(struct channel_function*);
} channel_function;

typedef struct fade_function_t {
    uint8_t     active;
    void        (*from)(uint8_t*);
    void        (*to)(uint8_t*);
    uint8_t     step;
    uint8_t     speed;
} fade_function_t;


void fade_to(void (*f)(uint8_t*), uint8_t speed);


uint8_t mod_func(uint8_t (*f)(uint8_t), uint8_t speed, uint8_t offset);

void fnc_fading(uint8_t*);
void fnc_rainbow(uint8_t*);
void fnc_rainbow2(uint8_t*);
void fnc_red_blue(uint8_t*);
void fnc_red_blue_reverse(uint8_t*);
void fnc_green_blue_reverse(uint8_t*);

void fnc_solid_red(uint8_t*);
void fnc_solid_green(uint8_t*);
void fnc_solid_blue(uint8_t*);
void fnc_solid_pink(uint8_t*);
void fnc_solid_yellow(uint8_t*);
void fnc_solid_natural(uint8_t*);
void fnc_solid_bg(uint8_t*);
void fnc_solid_rainbow(uint8_t*);
void fnc_solid_fulloff(uint8_t*);
void fnc_solid_fullon(uint8_t*);

#define fnc_solid_black (fnc_solid_fulloff)      // just for convenience
#define fnc_solid_white (fnc_solid_fullon)      // just for convenience



#ifdef __cplusplus
}
#endif

#endif // __IR_MODE_H
