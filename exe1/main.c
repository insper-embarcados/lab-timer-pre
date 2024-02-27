#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int LED_PIN_R = 4;

volatile int flag_f_r = 0;
volatile int g_timer_0 = 0;

void btn_callback(uint gpio, uint32_t events) {
    if (events == 0x4) { // fall edge
        flag_f_r = 1;
    } else if (events == 0x8) { // rise edge
    }
}

bool timer_0_callback(repeating_timer_t *rt) {
    g_timer_0 = 1;
    return true; // keep repeating
}

int main() {
    stdio_init_all();
    gpio_init(LED_PIN_R);
    gpio_set_dir(LED_PIN_R, GPIO_OUT);

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

    gpio_set_irq_enabled_with_callback(BTN_PIN_R,
                                       GPIO_IRQ_EDGE_FALL,
                                       true,
                                       &btn_callback);

    repeating_timer_t timer_0;
    int timer_enable = 0;
    int led_status = 0;
    while (true) {

        if (flag_f_r) {
            flag_f_r = 0;
            timer_enable = !timer_enable;

            if (timer_enable) {
                if (!add_repeating_timer_ms(500,
                                            timer_0_callback,
                                            NULL,
                                            &timer_0)) {
                }
            } else {
                cancel_repeating_timer(&timer_0);
                sleep_ms(10);
                g_timer_0 = 0;
                gpio_put(LED_PIN_R, 0);
            }
        }

        if (g_timer_0) {
            led_status = !led_status;
            gpio_put(LED_PIN_R, led_status);
            g_timer_0 = 0;
        }
    }
}
