#ifndef WATT_H
#define WATT_H
#include <zephyr/kernel.h>
#include <zephyr/device.h>
uint16_t callibration(int multimeter_reading_ma , int ina219_reading_ma);
//int ina219_write_reg(const struct device *dev , uint16_t status);

#endif
