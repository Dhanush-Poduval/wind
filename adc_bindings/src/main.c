#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/devicetree.h>
static const int32_t sleep_time_ms=1000;

#define MY_ADC_CH DT_ALIAS(my_adc_channel)
#define LIGHT_ADC_CH DT_ALIAS(light_control_channel)
//static const struct adc_dt_spec adc_light=ADC_DT_SPEC_GET(DT_ALIAS(light-control-channel));
//static const struct adc_dt_spec adc_main=ADC_DT_SPEC_GET(DT_ALIAS(my_adc_channel));
static const struct device *adc=DEVICE_DT_GET(DT_ALIAS(my_adc));
static const struct adc_channel_cfg adc_ch=ADC_CHANNEL_CFG_DT(MY_ADC_CH);
static const struct adc_channel_cfg light_adc=ADC_CHANNEL_CFG_DT(LIGHT_ADC_CH);
static const struct pwm_dt_spec led=PWM_DT_SPEC_GET(DT_ALIAS(my_led));

int mapping(int old , int old_min , int new_max , int new_min , int old_max){
   int new_value;
   new_value=(((old-old_min)*(new_max-new_min))/(old_max-old_min))+new_min;

};

int main(){
  int ret;
  uint16_t buf;
  uint16_t raw_val;
  int16_t  vref_mv;
  uint16_t status;
  int pulse;
  int o_max;
  int o_min=0;
  int n_max=255;
  int n_min=0;
  uint16_t curr;
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
  ret=adc_channel_setup(adc,&light_adc);
  while(1){
   //add random number generation for the code
   ret=adc_read(adc,&seq);
   if(ret<0){
     printk("Could not set up the adc");
     continue;
   }
   printk("Input channel of the potentiometer :%u\n ",light_adc.channel_id);
   o_max=(1<<seq.resolution)-1;  
   pulse=((uint64_t)buf * led.period )/4095;
   printk("Raw values : %u\n",buf);
   printk("Mapped values : %u\n",pulse);
   pwm_set_pulse_dt(&led,pulse);
   k_msleep(sleep_time_ms);
  };
  return 0;

}
