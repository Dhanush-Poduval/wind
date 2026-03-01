#ifndef ZEPHYR_BUTTON_H
#define ZEPHYR_BUTTON_H
#include <zephyr/drivers/gpio.h>

struct button_api{
	int (*get)(const struct device *dev,uint8_t *state);


};

struct button_config{
	struct gpio_dt_spec btn;
	uint32_t id;

};

#endif
