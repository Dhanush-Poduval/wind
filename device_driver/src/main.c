#include <zephyr/kernel.h>
#include <stdio.h>
#include "button.h"

static const struct device *holy_btn=DEVICE_DT_GET(DT_ALIAS(my_button_1));
static const uint32_t time=1000;

int main(){
  int res;
  if(!device_is_ready(holy_btn)){
     printk("Button has not been configures properly\n");
     return 0;
  }
  uint8_t status;
  const struct button_api *btn_api=(const struct button_api*)holy_btn->api;
  while(1){
    res=btn_api->get(holy_btn,&status);
    if(res<0){
      printk("THe button has not been configured properly\n");
      continue;
    }
    printk("%u\n",status);
    k_msleep(time);
    
  }

  return 0;
}
