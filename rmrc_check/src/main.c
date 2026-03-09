#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>



#define sleep_time_ms=1000;

static const struct gpio_dt_spec led=GPIO_DT_SPEC_GET(DT_ALIAS(yellow_led),gpios);


int main() {
  int ret ;
  int status;
  ret=gpio_pin_dt_configure(&led,GPIO_OUTPUT_ACTIVE);
  gpio_pin_set_dt(&led,1);
  if(ret<0){
    printk("Device led not configured proeprly");
  }



}
