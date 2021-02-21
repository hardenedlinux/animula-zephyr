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
#define BUF_SIZE    512

#if defined BOARD_LAMBDACHIP_ALONZO
#  define LEF_LOADER load_lef_from_tf
GLOBAL_DEF (const struct device *, dev_led0) = device_get_binding (LED0);
GLOBAL_DEF (const struct device *, dev_led1) = device_get_binding (LED1);
GLOBAL_DEF (const struct device *, dev_led2) = device_get_binding (LED2);
GLOBAL_DEF (const struct device *, dev_led3) = device_get_binding (LED3);

static void init_alonzo (void)
{
  int ret = 0;
  /* Set LED pin as output */
  ret
    = gpio_pin_configure (dev_led0, LED0_PIN, GPIO_OUTPUT_ACTIVE | LED0_FLAGS);
  if (ret < 0)
    {
      return;
    }
  ret
    = gpio_pin_configure (dev_led1, LED1_PIN, GPIO_OUTPUT_ACTIVE | LED1_FLAGS);
  if (ret < 0)
    {
      return;
    }
  ret
    = gpio_pin_configure (dev_led2, LED2_PIN, GPIO_OUTPUT_ACTIVE | LED2_FLAGS);
  if (ret < 0)
    {
      return;
    }
  ret
    = gpio_pin_configure (dev_led3, LED3_PIN, GPIO_OUTPUT_ACTIVE | LED3_FLAGS);
  if (ret < 0)
    {
      return;
    }

  gpio_pin_set (dev_led0, LED0_PIN, 1);
  gpio_pin_set (dev_led1, LED1_PIN, 1);
  gpio_pin_set (dev_led2, LED2_PIN, 1);
  gpio_pin_set (dev_led3, LED3_PIN, 1);
}
#endif

static lef_t load_lef_from_tf (void)
{
  lef_t lef = NULL;
  u8_t buf[BUF_SIZE] = {0};

  if (0 != mount_disk ())
    {
      printk ("Alonzo: TF card mount error!\n");
      return NULL;
    }

  lef = load_lef_from_file (DEFAULT_LEF);

  return lef;
}

void main (void)
{
  // set BLE module to transparent send mode
  printk ("\r\nAT+AUTO+++=Y\r\n");

  /* TODO:
   * 1. Add a REPL shell (include an interpreter)
   * 2. Load file from storage
   * 3. Add a special naming convention, if VM detect them then autorun
   * 4. Add online DEBUG
   */
  printk ("Platform: zephyr on %s\n", CONFIG_BOARD);

#if defined BOARD_LAMBDACHIP_ALONZO
  init_alonzo ();
  lambdachip_start (load_lef_from_file);
#else
  printk ("FATAL: LambdaChip was incorrectly configured, please check your "
          "config!\n");
  panic ("PANIC!");
#endif
}
