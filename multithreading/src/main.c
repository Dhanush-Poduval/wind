#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#define BLINK_STACK_SIZE 256
K_THREAD_STACK_DEFINE(blink_stack,BLINK_STACK_SIZE);
static struct k_thread blink_thread;
static const uint32_t led_time=500;
static const uint32_t  sleep_time=800;
static const struct gpio_dt_spec led=GPIO_DT_SPEC_GET(DT_ALIAS(my_led),gpios);
void blink_thread_start(void *arg1,void *arg2,void *arg3){
  int ret ;
  int state=0;
  while(1){
    state=!state;
    ret=gpio_pin_set_dt(&led,state);
    k_msleep(led_time);

  }
};

int main(){
  int ret;
  k_tid_t blink_tid;
  ret=gpio_pin_configure_dt(&led,GPIO_OUTPUT_ACTIVE);
  blink_tid=k_thread_create(&blink_thread,blink_stack,K_THREAD_STACK_SIZEOF(blink_stack),blink_thread_start,NULL,NULL,NULL,7,0,K_NO_WAIT);
  while(1){
    printk("Hello \n");
    k_msleep(sleep_time);
  }
};
