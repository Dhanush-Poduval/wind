#include <stdio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/console/console.h>
#include "motor.h"
#define sleep_time_ms 3 
static const struct gpio_dt_spec led=GPIO_DT_SPEC_GET(DT_ALIAS(my_led),gpios);
static const struct gpio_dt_spec dir_motor=GPIO_DT_SPEC_GET(DT_ALIAS(my_stepper),direction_gpios);
static const struct gpio_dt_spec step_motor=GPIO_DT_SPEC_GET(DT_ALIAS(my_stepper),step_gpios);

int main() {
  int ret ;
  int motor_dir;
  int motor_step;
  int status;
  uint8_t dir;
  uint8_t pos=0;
  console_getline_init();
  static const struct stepper_motor my_motor = {
    .direction=dir_motor,
    .step=step_motor
  };
  status=1;
  ret=gpio_pin_configure_dt(&led,GPIO_OUTPUT_ACTIVE);
  motor_dir=gpio_pin_configure_dt(&dir_motor,GPIO_OUTPUT_ACTIVE);
  motor_step=gpio_pin_configure_dt(&step_motor,GPIO_OUTPUT_ACTIVE);
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
    
    /*
    if(status==1){
      status=0;
    }else if(status==0){
      status=1;
    }
    
    printk("Status of the led : %d\n",status);
    gpio_pin_set_dt(&led,status);
    */
     
  }



}
