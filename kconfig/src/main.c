#include<zephyr/kernel.h>
#include<zephyr/sys/printk.h>
#include<zephyr/random/random.h>
#ifdef CONFIG_SAY_HELLO
#include "hello.h"
#endif
static const int32_t sleep_time_ms=1000;

int main(){
  uint32_t rnd;
  while(1){
  #ifdef CONFIG_TEST_RANDOM_GENERATOR 
    rnd=sys_rand32_get();
    printk("Random number : %u\n",rnd);
 #endif
#ifdef CONFIG_SAY_HELLO
    say_hello();
#endif
    k_msleep(sleep_time_ms);
  }

  return 0;

}
