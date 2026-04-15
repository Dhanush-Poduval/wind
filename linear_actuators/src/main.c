#include<stdio.h>
#include<zephyr/kernel.h>
#include<zephyr/drivers/pwm.h>
#include<zephyr/drivers/gpio.h>

const int sleep_time_ms=1000;

static const struct pwm_dt_spec link1=PWM_DT_SPEC_GET(DT_ALIAS(link_1));
//static const struct pwm_dt_spec link2=PWM_DT_SPEC_GET(DT_ALIAS(link_2));
uint32_t maxpulse=DT_PROP(DT_ALIAS(link_1),max_pulse);
uint32_t minpulse=DT_PROP(DT_ALIAS(link_1),min_pulse);

#define STEP PWM_USEC(100)

enum direction {
  UP,
  DOWN,
};

int main(){
  uint32_t pulse_width=maxpulse;
  enum direction dir=DOWN;
  int ret;
  if (!pwm_is_ready_dt(&link1)) {
		printk("Error: PWM device is not ready\n");
		return 0;
	};
  while(1){
    printk("min: %d , max:%d \n",minpulse,maxpulse);
    printk("pulse width %d",pulse_width);
    ret=pwm_set_pulse_dt(&link1,pulse_width);
    if(ret<0){
      printk("Error is configuration : %d\n",ret);
    };
    if(dir==DOWN){
      if(pulse_width<=minpulse){
        dir=UP;
        pulse_width=minpulse;
      } else {
        pulse_width-=STEP;
      };
    } else {
      pulse_width+=STEP;
      if(pulse_width>=maxpulse){
        dir=DOWN;
        pulse_width=maxpulse;
      };
    };
    k_msleep(200);
  };
  return 0;
}

