#include <stdlib.h>
#include "pirate-lib.h"
#include "pullup.h"
#include "shift.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "bio.h"
#include "lcd.h"
#include "amux.h"
#include "storage.h"
#include "spi_mutex.h"
#include "shift.h"

void pirate_init(void) {
    bio_init(); //initialize the buffered IO
    
    // setup SPI0 for on board peripherals
    uint baud = spi_init(BP_SPI_PORT, BP_SPI_HIGH_SPEED);
    gpio_set_function(BP_SPI_CDI, GPIO_FUNC_SPI);
    gpio_set_function(BP_SPI_CLK, GPIO_FUNC_SPI);
    gpio_set_function(BP_SPI_CDO, GPIO_FUNC_SPI);
    // init shift register pins
    #if (BP_VER == 5 || BP_VER == XL5)
        shift_init();
    #endif

    // SPI bus is used from here
    // setup the mutex for spi arbitration
    spi_mutex_init();

    // init psu pins
    //psucmd_init();

    // LCD pin init
    lcd_init();

    // ADC pin init
    amux_init();

    // TF flash card CS pin init
    //storage_init();
    // Output Pins
    gpio_set_function(FLASH_STORAGE_CS, GPIO_FUNC_SIO);
    gpio_put(FLASH_STORAGE_CS, 1);
    gpio_set_dir(FLASH_STORAGE_CS, GPIO_OUT);

    // initial pin states
    #if (BP_VER == 5 || BP_VER == XL5)
        // configure the defaults for shift register attached hardware
        shift_clear_set_wait(CURRENT_EN_OVERRIDE, (AMUX_S3 | AMUX_S1 | DISPLAY_RESET | CURRENT_EN));
    #endif

    pullup_init();

    lcd_backlight_enable(true);

}