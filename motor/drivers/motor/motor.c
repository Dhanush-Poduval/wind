#define DT_DRV_COMPACT custom_motor
#include <errno.h>
#include <zephyr/logging/log.h>
#include "motor.h"

LOG_MODULE_REGISTER(motor);
static int motor_init(const struct device *dev);
static int motor_get(const struct device *dev , uint8_t *state);




