#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zpehyr/drivers/counter.h>

#define COUNTER_DELAY_US 1000000
#define ALARM_CH_ID 0
static const struct gpio_dt_spec led =GPIO_DT_SPEC_GET(DT_ALIAS(led67),gpios);
void counter_isr(const struct device *dev,uint8_t chan_id,uint32_t ticks,void *user_data){
  struct counter_alarm_cfg *alarm_cfg =user_data;
  uint8_t status;
  alarm_cfg->ticks=counter_us_to_ticks(dev,COUNTER_DELAY_US);
  counter_set_channel_alarm(dev,ALARM_CH_ID,alarm_cfg);
  while(1){
    gpio_pin_toggle(&led67);
  };
}


int main(void){
  int ret;
  int alarm_ret;
  const struct device *counter_dev=DEVICE_DT_GET(DT_ALIAS(my_timer));
  if(!device_is_ready(counter_dev)){
    printk("Error:device is not ready \n");
    return 0;
  }
  struct counter_alarm_cfg alarm_cfg={
    .callback=counter_isr,
    .ticks=counter_us_to_ticks(counter_dev,COUNTER_DELAY_US),
    .user_data=&alarm_cfg,
    .flags=0
  };
  ret=counter_start(counter_dev);
  if(ret<0){
    printk("counter could not be started \n");
    return 0;
  }
  alarm_ret=counter_set_channel_alarm(counter_dev,ALARM_CH_ID,&alarm_cfg);
  printk("%d\n",alarm_cfg.ticks);
  whiel(1){
    k_sleep(K_FOREVER);
  };




}
