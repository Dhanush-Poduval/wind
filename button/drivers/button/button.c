#define DT_DRV_COMPAT custom_button
#include <errno.h>
#include <zephyr/logging/log.h>
#include "button.h"

LOG_MODULE_REGISTER(button);

static int button_init(const struct device *dev);
static int button_state_get(const struct device *dev , uint8_t *state);

//private function
static int button_init(const struct device *dev){
	const struct button_config *cfg=(const struct button_config*)dev->config;
	const struct gpio_dt_spec *btn=&cfg->btn;
	LOG_DBG("Initialized the button id : %d\n",cfg->id);
	if(!gpio_is_ready_dt(btn)){
		LOG_ERR("GPIO IS NOT READY");
		return -ENODEV;
	}
	int res;
	res=gpio_pin_configure_dt(btn,GPIO_INPUT);
	if(res<0){
	 LOG_ERR("COuld not configure the button");
	 return -ENODEV;
	}
	return 0;
}
//public function 

static int button_state_get(const struct device *dev,uint8_t *state){
	int res;
	const struct button_config *cfg=(const struct button_config*)dev->config;
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

//marcos

static const struct button_api button_api_funcs={
	.get=button_state_get,

};

#define BUTTON_DEFINE(inst)   \
			      \
	static const struct button_config button_config_##inst={  \
		.btn=GPIO_DT_SPEC_GET(DT_PHANDLE(DT_INST(inst,custom_button),pin),gpios),  \
		.id=inst,      \
	};		      \
	DEVICE_DT_INST_DEFINE(inst , button_init,NULL , NULL , &button_config_##inst,POST_KERNEL,CONFIG_GPIO_INIT_PRIORITY,&button_api_funcs);

DT_INST_FOREACH_STATUS_OKAY(BUTTON_DEFINE);
