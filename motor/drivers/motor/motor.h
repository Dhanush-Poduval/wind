#ifndef MOTOR_H
#define MOTOR_H
#include <zephyr/drivers/gpio.h>

struct motor_api{
  int(*get)(const struct device *dev, uint8_t *status);
};


struct motor {
  struct gpio_button_spec motor;
  uint32_t motor_state;

};


