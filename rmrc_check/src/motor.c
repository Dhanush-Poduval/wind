#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "motor.h"
const uint8_t sleep_time=100;

int step_motion(const struct stepper_motor *motor , int dir , int pos){
  if(dir==1){
    printk("Clockwise motion");
    gpio_pin_set_dt(&(motor->direction),1);
    pos+=1;
  }else if(dir==0){
    printk("Anticlockwise motion");
    gpio_pin_set_dt(&(motor->direction),0);
    pos-=1;
  }else {
    return pos;
  }
  gpio_pin_set_dt(&(motor->step),1);
  k_usleep(10);
  gpio_pin_set_dt(&(motor->step),0);
  k_usleep(10);
  /*
  int pulses=pos%4;
  if(pulses==0){
    gpio_pin_set_dt(&(motor->step),0);
  }else if(pulses==1){
    gpio_pin_set_dt(&(motor->step),1);
  }else if(pulses==2){
    gpio_pin_set_dt(&(motor->step),1);
  }else if(pulses==3){
    gpio_pin_set_dt(&(motor->step),0);
  }
  */
  return pos;


}
