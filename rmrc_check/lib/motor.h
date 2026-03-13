#ifndef MOTOR_H
#include <zephyr/kernel.h>
#include <zephyr/driver/gpio.h>
#define MOTOR_H
struct stepper_motor {
  uint16_t address;
  const struct gpio_dt_spec direction;
  const struct gpio_dt_spec motion;
  
};

void stepp_motion_movement(const struct stepper_motor *motor , int motion);
  
#endif // !DEBUG
