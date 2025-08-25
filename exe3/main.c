#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;

const int LED_PIN_R = 4;

volatile int flag_f_f = 0;
volatile int flag_f_r = 0;

void btn_callback(uint gpio, uint32_t events) {
    if (events == 0x4) { // fall edge
        if (gpio == BTN_PIN_R)
            flag_f_f = 1;

    } else if (events == 0x8) { // rise edge
        if (gpio == BTN_PIN_R)
            flag_f_r = 1;
    }
}

int main() {
    stdio_init_all();

    gpio_init(LED_PIN_R);
    gpio_set_dir(LED_PIN_R, GPIO_OUT);

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

    gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true,
                                       &btn_callback);

    int t_r = 0;
    int r_trigged = 0;
    int led_status = 0;

    while (true) {

        if (flag_f_f && !r_trigged) {
            t_r = to_ms_since_boot(get_absolute_time());
            flag_f_f = 0;
            r_trigged = 1;
        }

        if (flag_f_r && r_trigged) {
            r_trigged = 0;
            flag_f_r = 0;
            if (to_ms_since_boot(get_absolute_time()) - t_r > 500) {
                led_status = !led_status;
            }
            gpio_put(LED_PIN_R, led_status);
        }
    }
}
