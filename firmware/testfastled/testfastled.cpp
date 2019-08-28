#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

#include <curses.h>
#include <signal.h>
#include <unistd.h>

#define __INC_LED_SYSDEFS_H
#ifndef FASTLED_NAMESPACE_BEGIN
#define FASTLED_NAMESPACE_BEGIN
#define FASTLED_NAMESPACE_END
#define FASTLED_USING_NAMESPACE
#endif

#include "../FastLED/lib8tion.h"



using namespace std;
using namespace std::chrono;

typedef struct pixel {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
} pixel;


volatile pixel pixels[10];
volatile bool repeat = true;

void my_int_handler(int s){
    printf("Caught signal %d. Shutting down.\n", s);
    repeat = false;
}

uint32_t get_millisecond_timer(void) {
    return duration_cast< milliseconds >(
                steady_clock::now().time_since_epoch()
            ).count();
}

void paint(void) {
    erase(); // clear window

    int y = 0;
    mvaddstr(y, 0, "Testprogramm - zum Beenden STRG+C drücken.");
    y += 3;
    

    for (int i = 9; i >= 0; --i) {
        char bufr[255];
        char bufg[255];
        char bufb[255];
        sprintf(bufr, "    %d",    pixels[i].r);
        sprintf(bufg, " %d: %d", i, pixels[i].g);
        sprintf(bufb, "    %d",    pixels[i].b);

        mvaddstr(y,   0,   bufr);
        mvaddstr(y+1, 0, bufg);
        mvaddstr(y+2, 0, bufb);

        int x = 10;
        for (int j = 0; j < (pixels[i].r / 3); ++j) {
            attron(COLOR_PAIR(1));
            mvaddstr(y, x++, "#");
            attroff(COLOR_PAIR(1));
        }
        x = 10;
        for (int j = 0; j < (pixels[i].g / 3); ++j) {
            attron(COLOR_PAIR(2));
            mvaddstr(y+1, x++, "#");
            attroff(COLOR_PAIR(2));
        }
        x = 10;
        for (int j = 0; j < (pixels[i].b / 3); ++j) {
            attron(COLOR_PAIR(3));
            mvaddstr(y+2, x++, "#");
            attroff(COLOR_PAIR(3));
        }
        y += 4;
    }

    refresh();
}

uint8_t mod_func(uint8_t (*f)(uint8_t), uint8_t speed, uint8_t offset) {
    return f(offset + beat8(speed));
}

void fnc_sine_red_blue(void) {
    uint8_t speed = 5;      // in BPM
    for (int i = 0; i < 10; ++i) {
        pixels[i].r = mod_func(quadwave8, speed, -18*i);
        pixels[i].g = 0;
        pixels[i].b = mod_func(quadwave8, speed, 140 - 18*i);
    }
}

void fnc_rainbow2(void) {
    uint8_t speed = 5;      // in BPM
    for (int i = 0; i < 10; ++i) {
        pixels[i].r = mod_func(quadwave8, 2*speed, 0   - 18*i);
        pixels[i].g = mod_func(quadwave8, speed, 200 + 18*i);
        pixels[i].b = mod_func(triwave8, speed, 100 - 18*i);
    }
}

void fnc_rainbow_old(void) {
    uint8_t speed = 5;      // in BPM
    for (int i = 0; i < 10; ++i) {
        pixels[i].r = mod_func(quadwave8, speed, 0   - 18*i);
        pixels[i].g = mod_func(quadwave8, speed, 200 - 18*i);
        pixels[i].b = mod_func(quadwave8, speed, 100 - 18*i);
    }
}

void fnc_rainbow(void) {
    uint8_t speed = 5;      // in BPM
    for (int i = 0; i < 10; ++i) {
        pixels[i].r = (255-beat8(speed)) + 18*i;
        pixels[i].g = 0; //mod_func(cubicwave8, speed, 0   - 18*i);
        pixels[i].b = 0; //mod_func(cubicwave8, speed, 30 + 18*i);
    }
}

int main(int argc, char** argv) {
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_int_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    WINDOW * mainwin;

    if ( (mainwin = initscr()) == NULL ) {
        cerr << "Error initialising ncurses." << endl;
        exit(EXIT_FAILURE);
    }
    start_color();
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    init_pair(3, COLOR_BLUE, COLOR_BLUE);

    for (int i = 0; i < 10; ++i) {
        pixels[i].r = i;
        pixels[i].g = i;
        pixels[i].b = i;
    }

    while(repeat) {
        fnc_rainbow();
        paint();
        std::this_thread::sleep_for(std::chrono::milliseconds(35));
    }

    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}
