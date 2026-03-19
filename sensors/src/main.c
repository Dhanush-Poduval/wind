#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#define sleep_time_ms 1000

static const struct gpio_dt_spec led =GPIO_DT_SPEC_GET(DT_ALIAS(my_led),gpios);
static const struct device *mpu_sensor =DEVICE_DT_GET(DT_ALIAS(turntable_imu));
struct sensor_value accel[3] , gyro[3];
int main(){
  int ret;
  int sensor_ret;
  if(!device_is_ready(mpu_sensor)){
    printk("MPu sensor is not ready and configured properly \n");
    return 0;
  }
  ret=gpio_pin_configure_dt(&led,GPIO_OUTPUT_ACTIVE);
  if(ret<0){
    printk("Not able to congiure the led pins \n");
  }
  while(1){
    sensor_ret=sensor_sample_fetch(mpu_sensor);
    if(sensor_ret<0){
      printk("Error reading values from the sensor not configured properly \n");
      return 0;
    }
    sensor_ret=sensor_channel_get(mpu_sensor,SENSOR_CHAN_ACCEL_XYZ,accel);
    sensor_ret=sensor_channel_get(mpu_sensor,SENSOR_CHAN_GYRO_XYZ,gyro);
    //can add for temperature also
    printk("Accel : %f , %f , %f , Gyro : %f , %f , %f \n",sensor_value_to_double(&accel[0]),sensor_value_to_double(&accel[1]),sensor_value_to_double(&accel[2]),sensor_value_to_double(&gyro[0]),sensor_value_to_double(&gyro[1]),sensor_value_to_double(&gyro[2]));
    gpio_pin_toggle_dt(&led);
    k_msleep(sleep_time_ms);

  };
  

}
