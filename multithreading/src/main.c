#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/console/console.h>
#define BLINK_STACK_SIZE 256
#define INPUT_STACK_SIZE 526
#define blink_ms_max 2000
#define blink_ms_min 0
K_THREAD_STACK_DEFINE(blink_stack,BLINK_STACK_SIZE);
K_THREAD_STACK_DEFINE(input_stack , INPUT_STACK_SIZE);
static struct k_thread blink_thread;
static struct k_thread input_thread;
K_MUTEX_DEFINE(my_mutex);
static int32_t blink_sleep_ms=500;
static const struct gpio_dt_spec led=GPIO_DT_SPEC_GET(DT_ALIAS(my_led),gpios);
void input_thread_start(void *arg1,void *arg2,void *arg3){
  int32_t inc=0;
  while(1){
    const char* line=console_getline();
    if(line[0]=='+'){
      inc=1;
    }else if(line[0]=='-'){
      inc=-1;
    }else {
      continue;
    }
    k_mutex_lock(&my_mutex,K_FOREVER);
    blink_sleep_ms+=inc*100;
    if(blink_sleep_ms>blink_ms_max){
      blink_sleep_ms=blink_ms_max;
    }else if(blink_sleep_ms <blink_ms_min){
      blink_sleep_ms=blink_ms_min;
    }
    k_mutex_unlock(&my_mutex);
    printk("Sleep time : %u\n",blink_sleep_ms);
  }
};
void blink_thread_start(void *arg1,void *arg2,void *arg3){
  int ret ;
  int state=0;
  int32_t sleep_ms;
  while(1){

    k_mutex_lock(&my_mutex,K_FOREVER);
    sleep_ms=blink_sleep_ms;
    k_mutex_unlock(&my_mutex);
    state=!state;
    ret=gpio_pin_set_dt(&led,state);
    k_msleep(sleep_ms);

  }
};

int main(){
  printk("Hello from zephyr right here \n ");
  int ret;
  k_tid_t blink_tid;
  k_tid_t input_tid;
  ret=gpio_pin_configure_dt(&led,GPIO_OUTPUT_ACTIVE);
  console_getline_init();
  input_tid=k_thread_create(&input_thread,input_stack,K_THREAD_STACK_SIZEOF(input_stack),input_thread_start,NULL,NULL,NULL,8,0,K_NO_WAIT);
  blink_tid=k_thread_create(&blink_thread,blink_stack,K_THREAD_STACK_SIZEOF(blink_stack),blink_thread_start,NULL,NULL,NULL,7,0,K_NO_WAIT);
  while(1){
    k_msleep(1000);
  }
};
