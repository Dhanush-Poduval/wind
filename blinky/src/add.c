#include<zephyr/kernel.h>
#include<zephyr/sys/printk.h>
#include "add.h"

void add(){
  int result =5+3;
  printk("%d",result);
}
