#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

static const int32_t sleep_time_ms=1000;
static const struct gpio_dt_spec btn=GPIO_DT_SPEC_GET(DT_ALIAS(my_button),gpios);
static const struct gpio_dt_spec led=GPIO_DT_SPEC_GET(DT_ALIAS(my_led),gpios);

int main(){
	int res;
	int state;
	if(!gpio_is_ready_dt(&btn)){
		printk("Error in loading the pin : ");
		return 0;
	}
	res=gpio_pin_configure_dt(&btn,GPIO_INPUT);
	if(res<0){
		return 0;	
	}
	res=gpio_pin_configure_dt(&led,GPIO_OUTPUT_ACTIVE);
	printk("Button spec flags : 0x%x",btn.dt_flags);
	while(1){
		state=gpio_pin_get_dt(&btn);

		gpio_pin_set_dt(&led,state);
		if(state<0){
		  printk("Error %d : failed to read the button pin ",state);

		}else{
		  printk("Button state : %d\n",state);
		}

		k_msleep(sleep_time_ms);
	  
	}
	return 0;
  

}

