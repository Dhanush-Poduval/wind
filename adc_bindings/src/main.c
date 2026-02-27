#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>


static const int32_t sleep_time_ms=1000;

#define MY_ADC_CH DT_ALIAS(my_adc_channel)
#define LIGH_ADC_CH DT_ALIAS(ligh_control_channel)
//static const struct adc_dt_spec adc_light=ADC_DT_SPEC_GET(DT_ALIAS(light-control-channel));
//static const struct adc_dt_spec adc_main=ADC_DT_SPEC_GET(DT_ALIAS(my_adc_channel));
static const struct device *adc=DEVICE_DT_GET(DT_ALIAS(my_adc));
static const struct adc_channel_cfg adc_ch=ADC_CHANNEL_CFG_DT(MY_ADC_CH);
static const struct adc_channel_cfg light_adc=ADC_CHANNEL_CFG(LIGHT_ADC_CH);
static const struct gpio_dt_spec led=GPIO_DT_SPEC_GET(DT_ALIAS(my_led),gpios);
int main(){
  int ret;
  uint16_t buf;
  uint16_t raw_val;
  int16_t  vref_mv;
  uint16_t status;
  int res;
  if (res<0){
    return 0;
  }
  res=gpio_pin_configure_dt(&led,GPIO_OUTPUT_ACTIVE);
  vref_mv=DT_PROP(LIGHT_ADC_CH,zephyr_vref_mv);
  struct adc_sequence seq={
   .channels=BIT(light_adc.channel_id),
   .buffer=&buf,
   .buffer_size=sizeof(buf),
   .resolution=DT_PROP(LIGHT_ADC_CH,zephyr_resolution),
  };
  if(!device_is_ready(adc)){
    printk("ADC NOT SET /READY \n");
    return 0;
  }
  ret=adc_channel_setup(adc,&adc_ch);
  while(1){
   ret=adc_read(adc,&seq);
   if(ret<0){
     printk("Could not set up the adc");
     continue;
   }

   raw_val=buf*vref_mv/(1<<seq.resolution);
   printk("Raw values : %u",buf);
   k_msleep(sleep_time_ms);
  }


}
