/*  Copyright (C) 2020-2021
 *        "Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>
 *  LambdaChip is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.

 *  LambdaChip is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.

 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#include "lambdachip.h"
#include "vos.h"
#include <sys/printk.h>
#include <zephyr.h>

GLOBAL_DEF (bool, vm_verbose) = true;
GLOBAL_DEF (bool, vm_execute) = false;

/* TODO:
 * Configure these size when building
 */
GLOBAL_DEF (size_t, VM_CODESEG_SIZE) = 8192;
GLOBAL_DEF (size_t, VM_DATASEG_SIZE) = 0;
GLOBAL_DEF (size_t, VM_STKSEG_SIZE) = 1024;

#define DEFAULT_LEF "/SD:/program.lef"

#define LEF_LOADER load_lef_from_tf
GLOBAL_DEF (struct device *, dev_led0) = NULL;
GLOBAL_DEF (struct device *, dev_led1) = NULL;
GLOBAL_DEF (struct device *, dev_led2) = NULL;
GLOBAL_DEF (struct device *, dev_led3) = NULL;

GLOBAL_DEF (super_device, super_dev_led0) = {0};
GLOBAL_DEF (super_device, super_dev_led1) = {0};
GLOBAL_DEF (super_device, super_dev_led2) = {0};
GLOBAL_DEF (super_device, super_dev_led3) = {0};

#if defined CONFIG_BOARD_LAMBDACHIP_ALONZO
static void init_alonzo (void)
{
  GLOBAL_SET (dev_led0, device_get_binding (LED0));
  GLOBAL_SET (dev_led1, device_get_binding (LED1));
  GLOBAL_SET (dev_led2, device_get_binding (LED2));
  GLOBAL_SET (dev_led3, device_get_binding (LED3));

  (GLOBAL_REF (super_dev_led0)).dev = GLOBAL_REF (dev_led0);
  (GLOBAL_REF (super_dev_led0)).gpio_pin = LED0_PIN;
  (GLOBAL_REF (super_dev_led1)).dev = GLOBAL_REF (dev_led1);
  (GLOBAL_REF (super_dev_led1)).gpio_pin = LED1_PIN;
  (GLOBAL_REF (super_dev_led2)).dev = GLOBAL_REF (dev_led2);
  (GLOBAL_REF (super_dev_led2)).gpio_pin = LED2_PIN;
  (GLOBAL_REF (super_dev_led3)).dev = GLOBAL_REF (dev_led3);
  (GLOBAL_REF (super_dev_led3)).gpio_pin = LED3_PIN;

  /* Set LED pin as output */
  assert (gpio_pin_configure (GLOBAL_REF (dev_led0), LED0_PIN,
                              GPIO_OUTPUT_ACTIVE | LED0_FLAGS)
          >= 0);
  assert (gpio_pin_configure (GLOBAL_REF (dev_led1), LED1_PIN,
                              GPIO_OUTPUT_ACTIVE | LED1_FLAGS)
          >= 0);
  assert (gpio_pin_configure (GLOBAL_REF (dev_led2), LED2_PIN,
                              GPIO_OUTPUT_ACTIVE | LED2_FLAGS)
          >= 0);
  assert (gpio_pin_configure (GLOBAL_REF (dev_led3), LED3_PIN,
                              GPIO_OUTPUT_ACTIVE | LED3_FLAGS)
          >= 0);

  gpio_pin_set (GLOBAL_REF (dev_led0), LED0_PIN, 0);
  gpio_pin_set (GLOBAL_REF (dev_led1), LED1_PIN, 0);
  gpio_pin_set (GLOBAL_REF (dev_led2), LED2_PIN, 0);
  gpio_pin_set (GLOBAL_REF (dev_led3), LED3_PIN, 0);
}
#endif

static lef_t load_lef_from_tf (const char *filename)
{
  lef_t lef = NULL;

  if (0 != mount_disk ())
    {
      printk ("Alonzo: TF card mount error!\n");
      return NULL;
    }

  lef = load_lef_from_file (filename);

  return lef;
}

void main (void)
{
  /* TODO:
   * 1. Add a REPL shell (include an interpreter)
   * 2. Load file from storage
   * 3. Add a special naming convention, if VM detect them then autorun
   * 4. Add online DEBUG
   */
  printk ("Platform: zephyr on %s\n", CONFIG_BOARD);

#if defined CONFIG_BOARD_LAMBDACHIP_ALONZO
  init_alonzo ();
  struct LEF_Loader loader
    = {.filename = DEFAULT_LEF, .loader = load_lef_from_tf};
  lambdachip_start (&loader);
#else
  //#  error "what?!"
  printk ("FATAL: LambdaChip was incorrectly configured, please check your "
          "config!\n");
  panic ("PANIC!");
#endif
}
