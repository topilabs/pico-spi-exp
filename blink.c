#include <stdio.h>
#include "pico/stdlib.h"

const uint led_pin = 25;

repeating_timer_t timer;

typedef struct _status {
    uint led;
} _status;

_status status;

bool repeating_timer_callback(struct repeating_timer *t) {
    // Blink LED
    if (status.led == 0) 
    {
        gpio_put(led_pin, true);
        status.led = 1;
    } else if (status.led !=0)
    {
        gpio_put(led_pin, false);
        status.led = 0;
    }
}

int main() {

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    status.led = 0;

    // Initialize chosen serial port
    stdio_init_all();

    // Add repeating timer to an alarm pool
    add_repeating_timer_us(1000*100, repeating_timer_callback, &status, &timer);

    // Loop forever
    while (true) {
        // Notify user of activity
        printf("Blinking!\r\n");
        sleep_ms(500);
        timer.delay_us+=10000;
    }

}

