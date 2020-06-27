#include "dmxled.h"
#include "ir_mode.h"
#include <stdlib.h>

uint16_t rand16seed = RAND16_SEED;

#ifdef __cplusplus
extern "C" {
#endif

#define FADE_SPEED (4)

uint8_t ir_fade_buf_from[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                               0, 0, 0, 0, 0};
uint8_t ir_fade_buf_to[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0};
#ifdef TARGET_STORM
uint8_t ir_raw[32] = { 255, 215, 180, 255, 215, 180, 255, 215, 180,
                                255, 215, 180, 255, 215, 180, 255, 215, 180,
                                255, 215, 180, 255, 215, 180, 255, 215, 180,
                                255, 215, 180, 0, 0 };
#endif
#if defined(TARGET_DESK) || defined(TARGET_UART_SIMPLE)

// RGB-Stripe Decke: 7 17 18

uint8_t ir_raw[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

#endif


uint8_t scene_bg[32] = {     255, 255, 0,    0, 0, 0,    0, 0, 0,    0, 0, 0,
                               0, 0, 0,    0, 0, 0,    0, 0, 0,    0, 0, 0,
                             0, 0, 0,    0, 0, 0,    0, 0 };

uint8_t scene_rainbow[32] = { 255, 0, 0,    200, 100, 0,    100, 200, 0,    0, 255, 0,
                              0, 200, 100,    0, 100, 200,    0, 0, 255,    50, 0, 230,
                              100, 0, 200,    255, 0, 150,    0, 0 };


static uint8_t          selected_device_id = 0;
static fade_function_t  fade_function;
static uint8_t          current_speed = 5;
static void             (*current_function)(uint8_t*);
static uint8_t          global_dim = 255;
#define DIM(value)      (scale8_video(value, global_dim))

void ir_mode(void) {
    IRMP_DATA p;
    if (irmp_get_data(&p)) {
#ifdef DEBUG
        printf("P: %2d;\t0x%x;\t0x%x;\t0x%x;\tRepeat: %d\n",
                p.protocol, p.address, p.command, p.flags,
                p.flags & IRMP_FLAG_REPETITION);
#endif

        if (p.address == IR_ADDRESS) {
#ifdef DEBUG
            blinkGreen();
#endif

            switch(p.command) {
                case BTN_POWER:  // Power
                    fade_to(fnc_solid_black, FADE_SPEED);
                    break;
                case BTN_MUTE:  // Mute
                    fade_to(fnc_solid_fullon, FADE_SPEED);
                    break;
                case BTN_1:  // 1
                    //selected_device_id = 1;
                    fade_to(fnc_solid_black, FADE_SPEED);
                    break;
                case BTN_2:  // 2
                    //selected_device_id = 2;
                    fade_to(fnc_solid_black, FADE_SPEED);
                    break;
                case BTN_3:  // 3
                    //selected_device_id = 3;
                    fade_to(fnc_solid_black, FADE_SPEED);
                    break;
                case BTN_4:  // 4
                    //selected_device_id = 4;
                    fade_to(fnc_solid_black, FADE_SPEED);
                    break;
                case BTN_5:  // 5
                    //selected_device_id = 5;
                    fade_to(fnc_green_blue_reverse, FADE_SPEED);
                    break;
                case BTN_6:  // 6
                    //selected_device_id = 6;
                    fade_to(fnc_red_blue_reverse, FADE_SPEED);
                    break;
                case BTN_7:  // 7
                    fade_to(fnc_red_blue, FADE_SPEED);
                    break;
                case BTN_8:  // 8
                    fade_to(fnc_rainbow2, FADE_SPEED);
                    break;
                case BTN_9:  // 9
                    fade_to(fnc_rainbow, FADE_SPEED);
                    break;
                case BTN_0:  // 0
                    fade_to(fnc_solid_black, FADE_SPEED);
                    selected_device_id = 0;
                    break;
                case BTN_PRUP:  // PR up
                    if (global_dim > 240) global_dim = 240;
                    global_dim += 15;
                    break;
                case BTN_PRDOWN:  // PR down
                    if (global_dim < 15) global_dim = 15;
                    global_dim -= 15;
                    break;
                case BTN_VOLUP:  // Volume up
                    current_speed++;
                    if (current_speed > 250) current_speed = 250;
                    break;
                case BTN_VOLDOWN:  // Volume down
                    current_speed--;
                    if (current_speed < 1) current_speed = 1;
                    break;
                case BTN_RED:  // red
                    if (selected_device_id != DEVICE_ID && selected_device_id != 0) break;
                    fade_to(fnc_solid_red, FADE_SPEED);
                    break;
                case BTN_GREEN:  // green
                    if (selected_device_id != DEVICE_ID && selected_device_id != 0) break;
                    fade_to(fnc_solid_green, FADE_SPEED);
                    break;
                case BTN_YELLOW:  // yellow
                    if (selected_device_id != DEVICE_ID && selected_device_id != 0) break;
                    fade_to(fnc_solid_yellow, FADE_SPEED);
                    break;
                case BTN_BLUE:  // blue
                    if (selected_device_id != DEVICE_ID && selected_device_id != 0) break;
                    fade_to(fnc_solid_blue, FADE_SPEED);
                    break;
                case BTN_PINK:  // pink
                    if (selected_device_id != DEVICE_ID && selected_device_id != 0) break;
                    fade_to(fnc_solid_pink, FADE_SPEED);
                    break;
                case BTN_MIX:  // mix
                    if (selected_device_id != DEVICE_ID && selected_device_id != 0) break;
                    fade_to(fnc_solid_rainbow, FADE_SPEED);
                    break;
                case BTN_P100:  // P100
                    if (selected_device_id != DEVICE_ID && selected_device_id != 0) break;
                    fade_to(fnc_solid_bg, FADE_SPEED);
                    break;
                case BTN_SOUND:  // Smart Controls: Sound
                    if (selected_device_id != DEVICE_ID && selected_device_id != 0) break;
                    fade_to(fnc_solid_natural, FADE_SPEED);
                    break;
            }
        }
    }
    if (current_function != NULL) current_function(ir_raw);
}


void fade_to(void (*f)(uint8_t*), uint8_t speed) {
    if (current_function == f || current_function == fnc_fading) return; // debug
    if (current_function != fnc_fading) fade_function.from = current_function;
    fade_function.to = f;
    fade_function.speed = speed;
    fade_function.step = 0;
    fade_function.active = 1;

    current_function = fnc_fading;
}

void fnc_fading(uint8_t* target) {

    if ((255 - fade_function.speed) <= fade_function.step) {
        // finished!
        fade_function.active = 0;
        current_function = fade_function.to;
    }
    else {
        // calculate intermediates
        if (fade_function.from != NULL) {
            fade_function.from(ir_fade_buf_from);
        }
        else {
            memset(ir_fade_buf_from, 0, IR_CHANNELS);
        }
        if (fade_function.to != NULL) {
            fade_function.to(ir_fade_buf_to);
        }
        else {
            memset(ir_fade_buf_to, 0, IR_CHANNELS);
        }

        for (int i = 0; i < 10; ++i) {
            target[3*i + 0] = lerp8by8(ir_fade_buf_from[3*i+0], ir_fade_buf_to[3*i+0], fade_function.step);
            target[3*i + 1] = lerp8by8(ir_fade_buf_from[3*i+1], ir_fade_buf_to[3*i+1], fade_function.step);
            target[3*i + 2] = lerp8by8(ir_fade_buf_from[3*i+2], ir_fade_buf_to[3*i+2], fade_function.step);
        }
        fade_function.step += fade_function.speed;
    }
}

uint8_t mod_func(uint8_t (*f)(uint8_t), uint8_t speed, uint8_t offset) {
    return f(offset + beat8(speed));
}

void fnc_red_blue(uint8_t* target) {
    for (int i = 0; i < 10; ++i) {
        target[3*i + 0] = DIM(mod_func(quadwave8, current_speed, -18*i));
        target[3*i + 1] = 0;
        target[3*i + 2] = DIM(mod_func(quadwave8, current_speed, 140 - 18*i));
    }
}

void fnc_rainbow2(uint8_t* target) {
    for (int i = 0; i < 10; ++i) {
        target[3*i + 0] = DIM(mod_func(quadwave8, 2*current_speed, 0   - 18*i));
        target[3*i + 1] = DIM(mod_func(quadwave8, current_speed, 200 + 18*i));
        target[3*i + 2] = DIM(mod_func(triwave8, current_speed, 100 - 18*i));
    }
}
void fnc_rainbow(uint8_t* target) {
    for (int i = 0; i < 10; ++i) {
        target[3*i + 0] = DIM(mod_func(quadwave8, current_speed, 0   - 18*i));
        target[3*i + 1] = DIM(mod_func(quadwave8, current_speed, 200 - 18*i));
        target[3*i + 2] = DIM(mod_func(quadwave8, current_speed, 100 - 18*i));
    }
}

void fnc_green_blue_reverse(uint8_t* target) {
    for (int i = 0; i < 10; ++i) {
        target[3*i + 0] = 0;
        target[3*i + 1] = DIM(mod_func(cubicwave8, current_speed, 0 - 18*i));
        target[3*i + 2] = DIM(mod_func(cubicwave8, current_speed, 30 + 18*i));
    }
}


void fnc_red_blue_reverse(uint8_t* target) {
    for (int i = 0; i < 10; ++i) {
        target[3*i + 0] = DIM(mod_func(cubicwave8, current_speed, 0 - 18*i));
        target[3*i + 1] = 0;
        target[3*i + 2] = DIM(mod_func(cubicwave8, current_speed, 30 + 18*i));
    }
}



void fnc_solid_red(uint8_t* target) {
    for (int i = 0; i < 10; ++i) {
        target[3*i + 0] = DIM(255);
        target[3*i + 1] = 0;
        target[3*i + 2] = 0;
    }
}

void fnc_solid_green(uint8_t* target) {
    for (int i = 0; i < 10; ++i) {
        target[3*i + 0] = 0;
        target[3*i + 1] = DIM(255);
        target[3*i + 2] = 0;
    }
}

void fnc_solid_blue(uint8_t* target) {
    for (int i = 0; i < 10; ++i) {
        target[3*i + 0] = 0;
        target[3*i + 1] = 0;
        target[3*i + 2] = DIM(255);
    }
}

void fnc_solid_pink(uint8_t* target) {
    for (int i = 0; i < 10; ++i) {
        target[3*i + 0] = DIM(255);
        target[3*i + 1] = 0;
        target[3*i + 2] = DIM(255);
    }
}

void fnc_solid_yellow(uint8_t* target) {
    for (int i = 0; i < 10; ++i) {
        target[3*i + 0] = DIM(255);
        target[3*i + 1] = DIM(250);
        target[3*i + 2] = 0;
    }
}

void fnc_solid_bg(uint8_t* target) {
    for (int i = 0; i < IR_CHANNELS; ++i) {
        target[i] = DIM(scene_bg[i]);
    }
}


void fnc_solid_rainbow(uint8_t* target) {
    for (int i = 0; i < IR_CHANNELS; ++i) {
        target[i] = DIM(scene_rainbow[i]);
    }
}

void fnc_solid_natural(uint8_t* target) {
    // TODO: durch memcpy ersetzen?
    for (int i = 0; i < 10; ++i) {
        target[3*i + 0] = DIM(255);
        target[3*i + 1] = DIM(215);
        target[3*i + 2] = DIM(180);
    }
}

void fnc_solid_fulloff(uint8_t* target) {
    memset((void*)target, 0, IR_CHANNELS);
}

void fnc_solid_fullon(uint8_t* target) {
    memset((void*)target, 255, IR_CHANNELS);
}


#ifdef __cplusplus
}
#endif
