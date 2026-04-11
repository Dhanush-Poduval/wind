#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include "dth11.h"

static const int sleep_time_ms =1000;

#define MY_ADC_CHANNEL_1 DT_ALIAS(bio_sensor4)
//#define ADC_CHANNEL_2 DT_ALIAS(sensors5)
static const struct adc_channel_cfg adc_channel_1=ADC_CHANNEL_CFG_DT(MY_ADC_CHANNEL_1);
//static const struct adc_channel_cfg adc_channel_2=ADC_CHANNEL_CFG_DT(ADC_CHANNEL_2);
static const struct device *bio_sen1=DEVICE_DT_GET(DT_ALIAS(sensors14_channel));
static const struct gpio_dt_spec dht_sensor=GPIO_DT_SPEC_GET(DT_ALIAS(dth11_sensor),gpios);
/*
static const struct device *bio_sen2=DEVICE_DT_GET(DT_ALIAS(bio_sensor2));
static const struct device *bio_sen3=DEVICE_DT_GET(DT_ALIAS(bio_sensor3));
static const struct device *bio_sen4=DEVICE_DT_GET(DT_ALIAS(bio_sensor4));
static const struct device *bio_sen5=DEVICE_DT_GET(DT_ALIAS(bio_sensor5));
*/  

int main(){
  int ret;
  int dht_res;
  uint16_t buf;
  int dth11_data[5];
  uint8_t status;
  uint16_t vref;
  uint8_t vref2;
  int32_t final_voltage;
  vref=DT_PROP(MY_ADC_CHANNEL_1,zephyr_vref_mv);
  //vref2=DT_PROP(ADC_CHANNEL_2,zephyr_vref_mv);
  struct adc_sequence seq={
    .channels=BIT(adc_channel_1.channel_id),
    .buffer=&buf,
    .buffer_size=sizeof(buf),
    .resolution=DT_PROP(MY_ADC_CHANNEL_1,zephyr_resolution),
  };
  /*
  struct adc_sequence seq2={
    .channels=BIT(adc_channel_2.channel_id),
    .buffer=&buf,
    .buffer_size=sizeof(buf),
    .resolution=DT_PROP(ADC_CHANNEL_2,zephyr_resolution),
  };
  */ 
  
  if(!device_is_ready(bio_sen1)){
    printk("Bio sensor 1 not configured properly \n");
  };
  ret=adc_channel_setup(bio_sen1,&adc_channel_1);
  while(1){
    ret=adc_read(bio_sen1,&seq);
    if(ret<0){
      printk("Error in reading value of sensor 1");
      return 0;
    }
    final_voltage=(buf*vref)/(1<<seq.resolution);
    dht_res=read_sensor_values(dht_sensor,dth11_data);
    printk("The value read by the Analog sensor is : %u\n",buf);
    printk("The resultant voltage : %u\n",final_voltage);
    printk("The value read by the dth sensor humidity is : %d.%d\n",dth11_data[0],dth11_data[1]);
    printk("The value read by the dht sensor temperature : %d.%d\n",dth11_data[2],dth11_data[3]);

    k_msleep(sleep_time_ms);
  }
  return 0;

}
