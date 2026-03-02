#include <zephyr/kernel.h>
#include <stdio.h>
#include "button.h"
#include <zephyr/drivers/gpio.h>
static const struct device *holy_btn=DEVICE_DT_GET(DT_ALIAS(my_button_1));
static const uint32_t time=1000;
static const struct gpio_dt_spec led=GPIO_DT_SPEC_GET(DT_ALIAS(my_led),gpios);
int main(){
  int res;
  if(!device_is_ready(holy_btn)){
     printk("Button has not been configures properly\n");
     return 0;
  }
  uint8_t led_status;
  uint8_t status;
  int ret;
  ret=gpio_pin_configure_dt(&led,GPIO_OUTPUT_ACTIVE);
  const struct button_api *btn_api=(const struct button_api*)holy_btn->api; 
  while(1){
    res=btn_api->get(holy_btn,&status);
    if(res<0){
      printk("THe button has not been configured properly\n");
      continue;
    }
    printk("%u\n",status);
    gpio_pin_set_dt(&led,status);
    printk("The green led is in state : %u\n",status);
    k_msleep(time);
    
  }

  return 0;
}
