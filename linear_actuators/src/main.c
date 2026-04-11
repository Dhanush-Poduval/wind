#include<stdio.h>
#include<zephyr/kernel.h>
#include<zehyr/drivers/pwm.h>
#include<zephyr/drivers/gpio.h>

const int sleep_time_ms=1000;

static const struct pwm_dt_spec *link1=PWM_DT_SPEC_GET(DT_ALIAS(link_1),pwms);
static const struct pwm_dt_spec *link2=PWM_DEVICE_DT_SPEC_GET(DT_ALIAS(link_2),pwms);
uint16_t maxpulse=PWM_DEVICE_DT_SPEC_GET(DT_ALIAS(link_2),max_pulse);
uint16_t minpulse=PWM_DEVICE_DT_SPEC_GET(DT_ALIAS(link_1),min_pulse);

#define STEP PWM_USEC(100)

enum direction {
  UP,
  DOWN,
};

int main(){
  uint16_t pulse_width=minpulse;
  enum direction dir=UP;
  int ret;
  if (!pwm_is_ready_dt(&link1) && !pwm_is_ready_dt(&link2)) {
		printk("Error: PWM device is not ready\n",);
		return 0;
	};
  while(1){
    ret=pwm_set_pulse_dt(&link1,pulse_width);
    if(dir==DOWN){
      if(pulse_width<minpulse){
        dir=UP;
        pulse_width=min_pulse;
      } else {
        pulse_widt-=STEP;
      };
    } else {
      pulse_width+=STEP;
      if(pulse_width>maxpulse){
        dir=DOWN;
        pulse_width=maxpulse;
      };
    };
    k_msleep(sleep_time_ms);
  };
  return 0;
}

