#include <stdlib.h>
#include <stdio.h>
#include "pico/mutex.h"
static mutex_t spi_mutex;

void spi_mutex_init(void) {
    mutex_init(&spi_mutex);
}

// gives protected access to spi (core safe)
void spi_busy_wait(bool enable) {
    if (!enable) {
        // the check is to protect against the first csel_deselect call not matched by a csel_select
        if (lock_is_owner_id_valid(spi_mutex.owner)) {
            mutex_exit(&spi_mutex);
        }
    } else {
        mutex_enter_blocking(&spi_mutex);
    }
}