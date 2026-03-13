#ifndef MOTOR_H
#define MOTOR_H
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
struct stepper_motor {
  uint16_t address;
  const struct gpio_dt_spec direction;
  const struct gpio_dt_spec step;
  
};
int step_motion(const struct stepper_motor *motor , int dir , int pos );
  
#endif // !DEBUG
