#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>



#define sleep_time_ms 1000 

static const struct gpio_dt_spec led=GPIO_DT_SPEC_GET(DT_ALIAS(my_led),gpios);
static const struct gpio_dt_spec dir_motor=GPIO_DT_SPEC_GET(DT_ALIAS(my_stepper),direction_gpios);
static const struct gpio_st_spec step_motor=GPIO_DT_SPEC_GET(DT_ALIAS(my_stepper),step_gpios);

int main() {
  int ret ;
  int motor_dir;
  int motor_step;
  int status;
  uint8_t dir;
  uint8_t pos=0;
  status=1;
  ret=gpio_pin_configure_dt(&led,GPIO_OUTPUT_ACTIVE);
  motor_dir=gpio_pin_configure_dt(&dir_motor,GPIO_OUTPUT_ACTIVE);
  motor_step=gpio_dt_configure_dt(&step_motor,GPIO_OUTPUT_ACTIVE);
  gpio_pin_set_dt(&led,1);
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
    printk("Enter the direction to move \n");
    scanf("%u\n",input);
    if(input=='w'){
      dir=1;
    }else if(input =='a'){
      dir=0;
    }
    pulse=step_motion(step_motor,dir,pulse);
    if(pulse & 0x003 ==0){
      gpio_pin_set_dt(&led,1);
      printk("led is ON stepper moved one step");
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
    k_msleep(sleep_time_ms);
  
  }



}
