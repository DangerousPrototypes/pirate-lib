// global config file
#ifndef BP_CONFIG
#define BP_CONFIG

#include <stdlib.h>
#include <stdio.h>
// enable splash screen at startup, increases firmware size and load time
#define BP_SPLASH_ENABLED

#define BP_FIRMWARE_VERSION "main branch"

#ifndef BP_FIRMWARE_HASH // this variable is for the current commit GIT hash
#define BP_FIRMWARE_HASH "unknown"
#endif
#ifndef BP_FIRMWARE_TIMESTAMP // this variable is for the compile timestamp
#define BP_FIRMWARE_TIMESTAMP _TIMEZ_
#endif

#define BP_SPI_START_SPEED 1000 * 1000
#define BP_SPI_HIGH_SPEED 1000 * 1000 * 16
#define BP_SPI_SHIFT_SPEED 1000 * 1000 * 16
// #define XSTR(x) STR(x)
// #define STR(x) #x
// #pragma message "BP_FIRMWARE_HASH value:" XSTR(BP_FIRMWARE_HASH)
#define BP_FILENAME_MAX 13

// USB VID/PID
#define USB_VID 0x1209
#define USB_PID 0x7331
#define USB_VENDOR "BusPirate.com"
#define USB_PRODUCT "BusPirate5"

#define BIG_BUFFER_SIZE (128 * 1024)

// clang-format off
// include platform
#define BP_VER 5
#define BP_REV 10
#ifndef BP_REV
    #error "No /platform/ file included in pirate.h"
#else
    #if BP_VER == 5
        #if BP_REV == 8
            #include "platform/bpi-rev8.h"
        #elif BP_REV == 9
            #include "platform/bpi-rev9.h"
        #elif BP_REV == 10
            #include "platform/bpi-rev10.h"
        #else
            #error "Unknown platform version in pirate.h"
        #endif
    #elif BP_VER == XL5
        #include "platform/bpi-rev10.h"
    #elif BP_VER == 6
        #include "platform/bpi6-rev1.h"
    #else
        #error "Unknown platform version in pirate.h"
    #endif
#endif
// clang-format on

#include <stdint.h>
#include <stdbool.h>

void lcd_irq_enable(int16_t repeat_interval);
void lcd_irq_disable(void);
void spi_busy_wait(bool enable);

//#define BP_PIO_SHOW_ASSIGNMENT

#if BP_VER == 6
#define PIO_RGB_LED_PIO pio2
#define PIO_RGB_LED_SM 0
#else
#define PIO_RGB_LED_PIO pio0
#define PIO_RGB_LED_SM 1
#endif


#endif

void pirate_init(void) ;