#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 15

void servo_set_angle(uint pin, float angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    uint slice_num = pwm_gpio_to_slice_num(pin);

    pwm_set_clkdiv(slice_num, 125.0f);   // 1 MHz
    pwm_set_wrap(slice_num, 20000);      // 20 ms

    // 1.5% to 12% duty cycle
    float duty = 0.015f + (angle / 180.0f) * (0.12f - 0.015f);

    uint16_t level = (uint16_t)(duty * 20000);

    pwm_set_gpio_level(pin, level);
}
int main() {
    stdio_init_all();

    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    pwm_set_enabled(slice_num, true);

    while (true) {
        for (float angle = 0; angle <= 180; angle += 1) {
            servo_set_angle(SERVO_PIN, angle);
            sleep_ms(20);
        }

        for (float angle = 180; angle >= 0; angle -= 1) {
            servo_set_angle(SERVO_PIN, angle);
            sleep_ms(20);
        }
    }
}