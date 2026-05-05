#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>

#define sleep_time_ms 1000

static const struct gpio_dt_spec trigger=GPIO_DT_SPEC_GET(DT_ALIAS(my_ultrasonic),trig_gpios);
static const struct gpio_dt_spec echo=GPIO_DT_SPEC_GET(DT_ALIAS(my_ultrasonic),echo_gpios);


int main(){
  printk("Start of the program \n");
  int ret ;
  int echo_ret;
  if(!gpio_is_ready_dt(&trigger) || !gpio_is_ready_dt(&echo)){
    printk("Ultrasonic sensor not configured properly \n");
    return -1;
  }
  ret=gpio_pin_configure_dt(&trigger,GPIO_OUTPUT_INACTIVE);
  if(ret<0){
    printk("Error in the trigger pin connection for the ultrasonic sensor \n");
    return -1;
  }
  echo_ret=gpio_pin_configure_dt(&echo,GPIO_INPUT);
  while (1) {
    gpio_pin_set_dt(&trigger, 0);
    k_busy_wait(2);

    gpio_pin_set_dt(&trigger, 1);
    k_busy_wait(10);
    gpio_pin_set_dt(&trigger, 0);

    printk("Trigger sent\n");

    int timeout = 1000000;

    printk("Waiting HIGH\n");
    while (gpio_pin_get_dt(&echo) == 0) {
        if (--timeout == 0) {
            printk("No echo HIGH\n");
            goto sleep;
        }
    }

    int64_t start = k_cycle_get_64();

    timeout = 1000000;
    printk("Waiting LOW\n");
    while (gpio_pin_get_dt(&echo) == 1) {
        if (--timeout == 0) {
            printk("No echo LOW\n");
            goto sleep;
        }
    }

    int64_t end = k_cycle_get_64();

    uint64_t time_us = k_cyc_to_us_floor64(end - start);
    float distance = (time_us * 0.0343) / 2;

    printk("Distance: %.2f cm\n", (double)distance);

  sleep:
      k_msleep(1000);
  }
}
