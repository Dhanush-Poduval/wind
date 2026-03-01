#define DT_DRV_COMPAT custom_button
#include <errno.h>
#include <zephyr/logging/log.h>
#include "button.h"

LOG_MODULE_REGISTER(button);

static int button_init(const struct device *dev);
static int button_state_get(const struct device *dev , uint8_t *state);

//private function
static int button_init(const struct device *dev){
	const struct button_config *cfg=(const struct button_config)*dev->config;
	const struct gpio_dt_spec *btn=&cfg->btn;
	LOG_DBG("Initialized the button id : %y\n",cfg->id);
	if(!gpio_is_ready_dt(btn)){
		LOG_ERR("GPIO IS NOT READY");
		return -ENODEV;
	}
	int res;
	res=gpio_configure_dt(btn,GPIO_INPUT);
	if(res<0){
	 LOG_ERR("COuld not configure the button");
	 return -ENODEV;
	}
	return 0;
}
//public function 

static int button_state_get(const struct device *dev,uint8_t *state){
	int res;
	const struct button_config *cfg=(const struct button_config)*dev->config;
	const struct gpio_dt_spec *btn=&cfg->btn;
	res=gpio_pin_get_dt(btn);
	if(res<0){
	  LOG_ERR("Button could not be set up ");
	  return 0;
	}
	else {
	   *state=res;
	}
	return 0;

}


