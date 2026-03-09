#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>



#define sleep_time_ms=1000;

static const struct gpio_dt_spec led=GPIO_DT_SPEC_GET(DT_ALIAS(yellow_led),gpios);


int main() {
  int ret ;
  int status;
  status=1;
  ret=gpio_pin_dt_configure(&led,GPIO_OUTPUT_ACTIVE);
  gpio_pin_set_dt(&led,1);
  if(ret<0){
    printk("Device led not configured proeprly");
  }
  while(1){
    if(status==1){
      status=0;
    }else if(status==0){
      status=1;
    }
    printk("Status of the led : %d\n",status);
    gpio_pin_set_dt(&led,status);
    k_msleep(sleep_time_ms);
  
  }



}
