#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>


static const int32_t sleep_time_ms=1000;

#define MY_ADC_CH DT_ALIAS(my_adc_channel)
static const struct device *adc=DEVICE_DT_GET(DT_ALIAS(my_adc));
static const struct adc_channel_cfg adc_ch=ADC_CHANNEL_CFG_DT(MY_ADC_CH);

int main(){
  int ret;
  uint16_t buf;
  uint16_t raw_val;
  int16_t  vref_mv;
  vref_mv=DT_PROP(MY_ADC_CH,zephyr_vref_mv);
  struct adc_sequence seq={
   .channels=BIT(adc_ch.channel_id),
   .buffer=&buf,
   .buffer_size=sizeof(buf),
   .resolution=DT_PROP(MY_ADC_CH,zephyr_resolution),
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
