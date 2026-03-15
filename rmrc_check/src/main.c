#include <stdio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/console/console.h>
#include "motor.h"
#define sleep_time_ms 3
#define CONTROL_STACK_SIZE 512
#define MOTOR_STACK_SIZE 512
K_THREAD_STACK_DEFINE(control_stack,CONTROL_STACK_SIZE);
K_THREAD_STACK_DEFINE(motor_stack,MOTOR_STACK_SIZE);
static struct  k_thread control_thread;
static struct k_thread motor_thred;
K_MUTEX_DEFINE(stepper_mutex);
uint8_t rotation;
static const struct gpio_dt_spec led=GPIO_DT_SPEC_GET(DT_ALIAS(my_led),gpios);
static const struct gpio_dt_spec dir_motor=GPIO_DT_SPEC_GET(DT_ALIAS(my_stepper),direction_gpios);
static const struct gpio_dt_spec step_motor=GPIO_DT_SPEC_GET(DT_ALIAS(my_stepper),step_gpios);
static const struct stepper_motor my_motor = {
  .direction=dir_motor,
  .step=step_motor
};
void control_thread_start(void *arg1,void *arg2 , void *arg3){
  uint8_t dir;
  while(1){
    char *line=console_getline();
    if(line[0]=='w'){
      dir=1;
    }else if(line[0]=='a'){
      dir=0;
    }else {
      continue;
    }
    k_mutex_lock(&stepper_mutex,K_FOREVER);
    rotation=(uint8_t)dir;
    k_mutex_unlock(&stepper_mutex);
    printk("Direction of rotation is : %d\n",rotation);

  }
}

void motor_thread_start(void *arg1 , void *arg2 , void *arg3){
  uint8_t pulse=0;
  uint8_t direction_rotation=0;
  while(1){
    k_mutex_lock(&stepper_mutex,K_FOREVER);
    direction_rotation=rotation;
    k_mutex_unlock(&stepper_mutex);
    pulse=step_motion(&my_motor,direction_rotation,pulse);
    if((pulse & 0x03)==0){
      gpio_pin_set_dt(&led,1);
    }else {
      gpio_pin_set_dt(&led,0);
    }
    printk("Rotating the stepper motor to one step \n");
  }
}
int main() {
  int motor_dir;
  int motor_step;
  uint8_t status=0;
  int ret;
  console_getline_init();
  status=1;
  ret=gpio_pin_configure_dt(&led,GPIO_OUTPUT_ACTIVE);
  motor_dir=gpio_pin_configure_dt(&dir_motor,GPIO_OUTPUT_ACTIVE);
  motor_step=gpio_pin_configure_dt(&step_motor,GPIO_OUTPUT_ACTIVE);
  k_tid_t motor;
  k_tid_t control;
  motor=k_thread_create(&motor_thred,motor_stack,K_THREAD_STACK_SIZEOF(motor_stack),motor_thread_start,NULL,NULL,NULL,7,0,K_NO_WAIT);
  control=k_thread_create(&control_thread,control_stack,K_THREAD_STACK_SIZEOF(control_stack),control_thread_start,NULL,NULL,NULL,8,0,K_NO_WAIT);
  gpio_pin_set_dt(&led,0);
  gpio_pin_set_dt(&dir_motor,0);
  gpio_pin_set_dt(&step_motor,0);
  if(motor_dir <0){
    printk("Device stepper nto configured properly");
  }
  if (motor_step <0){
    printk("Device stepper not configured properly the pulse channel");
  }
  if(ret<0){
    printk("Device led not configured proeprly");
  }
  char input;
  while(1){
    /*
    char *line=console_getline();
    /*
    printk("Enter the direction to move\n");
    scanf(" %c",&input);
    if(input=='w'){
      dir=1;
    }else if(input =='a'){
      dir=0;
    }else {
      printk("Invalid key presses \n");
      return 0;
    }
    */
    /*
    if(line[0]=='w'){
      dir=1;
    }else if(line[0]=='a'){
      dir=0;
    }else {
      printk("Invalid character \n");
      continue;
    }
    pos=step_motion(&my_motor,dir,pos);
    if((pos & 0x03) ==0){
      gpio_pin_set_dt(&led,1);
      printk("led is ON stepper moved one step forward or back");
    }else{
      gpio_pin_set_dt(&led,0);
      printk("led is OFF");
    }
    */
    /*
    if(status==1){
      status=0;
    }else if(status==0){
      status=1;
    }
    
    printk("Status of the led : %d\n",status);
    gpio_pin_set_dt(&led,status);
    */
    k_sleep(K_FOREVER);
  }



}
