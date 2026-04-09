#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

static const uint8_t sleep_time_ms =1000;

#define ADC_CHANNEL_1 DT_ALIAS(sensors14_channel);
#define ADC_CHANNEL_2 DT_ALIAS(sensors5_channel);
static const struct adc_channel_cfg adc_channel_1=ADC_CHANNEL_CFG_DT(ADC_CHANNEL_1);
static const struct adc_channel_cfg adc_channel_2=ADC_CHANNEL_CFG_DT(ADC_CHANNEL_2);
static const struct device *bio_sen1=DEVICE_DT_GET(DT_ALIAS(bio_sensor1));
static const struct device *bio_sen2=DEVICE_DT_GET(DT_ALIAS(bio_sensor2));
static const struct device *bio_sen3=DEVICE_DT_GET(DT_ALIAS(bio_sensor3));
static const struct device *bio_sen4=DEVICE_DT_GET(DT_ALIAS(bio_sensor4));
static const struct device *bio_sen5=DEVICE_DT_GET(DT_ALIAS(bio_sensor5));

int main(){
  int ret;
  uint8_t buf;
  uint8_t status;
  uint8_t vref;
  uint8_t vref2;
  vref=DT_PROP(ADC_CHANNEL_1,zephyr_vref_mv);
  vref2=DT_PROP(ADC_CHANNEL_2,zephyr_vref_mv);
  struct adc_sequence seq={
    .channels=BIT(adc_channel_1.channel_id),
    .buffer=&buf,
    .buffer_size=sizeof(buf),
    .resolution=DT_PROP(ADC_CHANNEL_1,zephyr_resolution),
  };
  

}
