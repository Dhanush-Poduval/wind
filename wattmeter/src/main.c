#include <stdio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include "watt.h"
static const struct device *watt_meter0=DEVICE_DT_GET(DT_ALIAS(wattmeter));
struct sensor_value current,voltage,power;
const int multimeter_value=1000;
const int ina219_reading =1000;
int main(){
  int wattmeter_ret;
  wattmeter_ret=sensor_sample_fetch(watt_meter0);
  if(wattmeter_ret<0){
    printk("Not able to configure the wttmeter\n");
  }
  //uint16_t cal=0;
  //cal=callibration(multimeter_value,ina219_reading);
  //ina219_write_reg(watt_meter0,cal);
  while(1){
    wattmeter_ret=sensor_channel_get(watt_meter0,SENSOR_CHAN_POWER,&power);
    wattmeter_ret=sensor_channel_get(watt_meter0,SENSOR_CHAN_VOLTAGE,&voltage);
    wattmeter_ret=sensor_channel_get(watt_meter0,SENSOR_CHAN_CURRENT,&current);
    printk("Value of power : %d.%d\n",power.val1,power.val2/1000);
    printk("Value of current : %d.%d\n",current.val1,current.val2/1000);
    printk("Value of voltage : %d.%d\n",voltage.val1,voltage.val2/1000);

  }
}
