#include <stdio.h>
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/device.h>
#include <zephyr/sys/byteorder.h>
#include "watt.h"
uint16_t cal_value=4096;
/*
int ina219_write_reg(const struct device *dev , uint16_t cal){
  const struct ina219_config *cfg =dev->config;
  uint8_t buf[3];
  buf[0]=0x05;
  sys_put_be16(cal,&buf[1]);
  return i2c_write_dt(&cfg->bus,buf,sizeof(buf));
};
*/ 
uint16_t calibration(int a , int b){
  float factor=a/b;
  cal_value= (uint16_t)(factor * cal_value) & 0xFFFE;
  return cal_value;
};
