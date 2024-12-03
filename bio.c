#include <stdio.h>
#include "pico/stdlib.h"
#include "pirate.h"
#include "hardware/gpio.h"
#include "bio.h"



void bio_init(void) {
    // setup the buffer IO and DIRection pins
    for (uint8_t i = 0; i < 8; i++) {
        //pin direction
        //gpio_set_inover(bio2bufiopin[i], GPIO_OVERRIDE_NORMAL);
        //gpio_set_outover(bio2bufiopin[i], GPIO_OVERRIDE_NORMAL);
        gpio_set_drive_strength(i+8, GPIO_DRIVE_STRENGTH_2MA);
        gpio_set_dir(i+8, GPIO_IN);
        gpio_set_function(i+8, GPIO_FUNC_SIO);
        //buffer
        gpio_put(i, BUFDIR_INPUT);
        gpio_set_dir(i, GPIO_OUT);
        gpio_set_function(i, GPIO_FUNC_SIO);
    }
}
void bio_buf_pin_init(uint8_t bio) {
    gpio_put(bio2bufdirpin[bio], BUFDIR_INPUT);
    gpio_set_dir(bio2bufdirpin[bio], GPIO_OUT);
    gpio_set_function(bio2bufdirpin[bio], GPIO_FUNC_SIO);
}
// these are only for use with the BIO0...BIOn ordered pin format,
void bio_buf_output(uint8_t bio) {
    gpio_put(bio2bufdirpin[bio], BUFDIR_OUTPUT); // make the buffer an output
}
// these are only for use with the BIO0...BIOn ordered pin format,
void bio_buf_input(uint8_t bio) {
    gpio_put(bio2bufdirpin[bio], BUFDIR_INPUT); // make the buffer an input
}

// these are only for use with the BIO0...BIOn ordered pin format,
void bio_output(uint8_t bio) {
    // first set the buffer to output
    gpio_put(bio2bufdirpin[bio], BUFDIR_OUTPUT);
    // now set pin to output
    gpio_set_dir(bio2bufiopin[bio], GPIO_OUT);
}
// these are only for use with the BIO0...BIOn ordered pin format,
void bio_input(uint8_t bio) {
    // first set the pin to input
    gpio_set_dir(bio2bufiopin[bio], GPIO_IN);
    // now set buffer to input
    gpio_put(bio2bufdirpin[bio], BUFDIR_INPUT);
}
static inline void bio_put(uint8_t bio, bool value) {
    gpio_put(bio, value);
}
static inline bool bio_get(uint8_t bio) {
    return gpio_get(bio2bufiopin[bio]);
}
void bio_set_function(uint8_t bio, uint8_t function) {
    gpio_set_function(bio2bufiopin[bio], function);
}
void bio_buf_test(uint8_t bufio, uint8_t bufdir) {
    gpio_put(bufdir, BUFDIR_OUTPUT);
    gpio_set_dir(bufio, GPIO_OUT);
    gpio_put(bufio, 1);
    busy_wait_ms(2000);
    gpio_put(bufio, 0);
    gpio_set_dir(bufio, GPIO_IN);
    gpio_put(bufdir, BUFDIR_INPUT);
}