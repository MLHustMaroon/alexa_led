#include "driver/gpio.h"

#include "mrubyc.h"

#include "models/led.h"
#include "loops/master.h"

#define MEMORY_SIZE (1024*40)

static uint8_t memory_pool[MEMORY_SIZE];

static void c_gpio_init_output(mrb_vm *vm, mrb_value *v, int argc) {
  int pin = GET_INT_ARG(1);
  console_printf("init pin %d\n", pin);
  gpio_set_direction(pin, GPIO_MODE_OUTPUT);
}

static void c_gpio_set_level(mrb_vm *vm, mrb_value *v, int argc){
  int pin = GET_INT_ARG(1);
  int level = GET_INT_ARG(2);
  gpio_set_level(pin, level);
}

void app_main(void) {
  mrbc_init(memory_pool, MEMORY_SIZE);

  mrbc_define_method(0, mrbc_class_object, "gpio_init_output", c_gpio_init_output);
  mrbc_define_method(0, mrbc_class_object, "gpio_set_level", c_gpio_set_level);

  mrbc_create_task( led, 0 );
  mrbc_create_task( master, 0 );
  mrbc_run();
}