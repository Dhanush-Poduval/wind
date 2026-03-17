#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zpehyr/drivers/counter.h>

#define COUNTER_DELAY_US 1000000
#define ALARM_CH_ID 0
static const struct gpio_dt_spec led =GPIO_DT_SPEC_GET(DT_ALIAS(led67),gpios);
void counter_isr(const struct device *dev,uint8_t chan_id,uint32_t ticks,void *user_data){
  struct counter_alarm_cfg *alarm_cfg =user_data;
  alarm_cfg->ticks=counter_us_to_ticks(dev,COUNTER_DELAY_US);
  counter_set_channel_alarm(dev,ALARM_CH_ID,alarm_cfg);
}
