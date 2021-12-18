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

GLOBAL_DEF (size_t, VM_STKSEG_SIZE) = 1024;

#define DEFAULT_LEF "/SD:/program.lef"

#define LEF_LOADER load_lef_from_tf
GLOBAL_DEF (struct device *, dev_led0) = NULL;
GLOBAL_DEF (struct device *, dev_led1) = NULL;
GLOBAL_DEF (struct device *, dev_led2) = NULL;
GLOBAL_DEF (struct device *, dev_led3) = NULL;

GLOBAL_DEF (struct device *, dev_gpio_pa9) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pa10) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pb4) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pa8) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pb5) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pb6) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pb7) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pb8) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pb9) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pa2) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pa3) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pb3) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pb10) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pb15) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pb14) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pb13) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_pb12) = NULL;
GLOBAL_DEF (struct device *, dev_gpio_ble_disable) = NULL;

GLOBAL_DEF (struct device *, dev_i2c2) = NULL;
GLOBAL_DEF (struct device *, dev_i2c3) = NULL;

GLOBAL_DEF (super_device, super_dev_led0) = {0};
GLOBAL_DEF (super_device, super_dev_led1) = {0};
GLOBAL_DEF (super_device, super_dev_led2) = {0};
GLOBAL_DEF (super_device, super_dev_led3) = {0};

GLOBAL_DEF (super_device, super_dev_gpio_pa9) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pa10) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pb4) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pa8) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pb5) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pb6) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pb7) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pb8) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pb9) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pa2) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pa3) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pb3) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pb10) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pb15) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pb14) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pb13) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_pb12) = {0};
GLOBAL_DEF (super_device, super_dev_gpio_ble_disable) = {0};

GLOBAL_DEF (super_device, super_dev_i2c2) = {0};
GLOBAL_DEF (super_device, super_dev_i2c3) = {0};

#if defined CONFIG_BOARD_LAMBDACHIP_ALONZO
static void init_alonzo (void)
{
  GLOBAL_SET (dev_led0, device_get_binding (LED0));
  GLOBAL_SET (dev_led1, device_get_binding (LED1));
  GLOBAL_SET (dev_led2, device_get_binding (LED2));
  GLOBAL_SET (dev_led3, device_get_binding (LED3));

  GLOBAL_SET (dev_gpio_pa9, device_get_binding (GPIO_PA9));
  GLOBAL_SET (dev_gpio_pa10, device_get_binding (GPIO_PA10));
  GLOBAL_SET (dev_gpio_pb4, device_get_binding (GPIO_PB4));
  GLOBAL_SET (dev_gpio_pa8, device_get_binding (GPIO_PA8));
  GLOBAL_SET (dev_gpio_pb5, device_get_binding (GPIO_PB5));
  GLOBAL_SET (dev_gpio_pb6, device_get_binding (GPIO_PB6));
  GLOBAL_SET (dev_gpio_pb7, device_get_binding (GPIO_PB7));
  GLOBAL_SET (dev_gpio_pb8, device_get_binding (GPIO_PB8));
  GLOBAL_SET (dev_gpio_pb9, device_get_binding (GPIO_PB9));
  GLOBAL_SET (dev_gpio_pa2, device_get_binding (GPIO_PA2));
  GLOBAL_SET (dev_gpio_pa3, device_get_binding (GPIO_PA3));
  GLOBAL_SET (dev_gpio_pb3, device_get_binding (GPIO_PB3));
  GLOBAL_SET (dev_gpio_pb10, device_get_binding (GPIO_PB10));
  GLOBAL_SET (dev_gpio_pb15, device_get_binding (GPIO_PB15));
  GLOBAL_SET (dev_gpio_pb14, device_get_binding (GPIO_PB14));
  GLOBAL_SET (dev_gpio_pb13, device_get_binding (GPIO_PB13));
  GLOBAL_SET (dev_gpio_pb12, device_get_binding (GPIO_PB12));
  GLOBAL_SET (dev_gpio_ble_disable, device_get_binding (BLEDISABLE));

  GLOBAL_SET (dev_i2c2, device_get_binding (DT_LABEL (DT_NODELABEL (i2c2))));
  GLOBAL_SET (dev_i2c3, device_get_binding (DT_LABEL (DT_NODELABEL (i2c3))));

  super_device *dev = NULL;
  dev = &GLOBAL_REF (super_dev_led0);
  dev->dev = GLOBAL_REF (dev_led0);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = LED0_PIN;

  dev = &GLOBAL_REF (super_dev_led1);
  dev->dev = GLOBAL_REF (dev_led1);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = LED1_PIN;

  dev = &GLOBAL_REF (super_dev_led2);
  dev->dev = GLOBAL_REF (dev_led2);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = LED2_PIN;

  dev = &GLOBAL_REF (super_dev_led3);
  dev->dev = GLOBAL_REF (dev_led3);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = LED3_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pa9));
  dev->dev = GLOBAL_REF (dev_gpio_pa9);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PA9_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pa10));
  dev->dev = GLOBAL_REF (dev_gpio_pa10);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PA10_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pb4));
  dev->dev = GLOBAL_REF (dev_gpio_pb4);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PB4_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pa8));
  dev->dev = GLOBAL_REF (dev_gpio_pa8);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PA8_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pb5));
  dev->dev = GLOBAL_REF (dev_gpio_pb5);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PB5_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pb6));
  dev->dev = GLOBAL_REF (dev_gpio_pb6);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PB6_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pb7));
  dev->dev = GLOBAL_REF (dev_gpio_pb7);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PB7_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pb8));
  dev->dev = GLOBAL_REF (dev_gpio_pb8);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PB8_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pb9));
  dev->dev = GLOBAL_REF (dev_gpio_pb9);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PB9_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pa2));
  dev->dev = GLOBAL_REF (dev_gpio_pa2);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PA2_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pa3));
  dev->dev = GLOBAL_REF (dev_gpio_pa3);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PA3_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pb3));
  dev->dev = GLOBAL_REF (dev_gpio_pb3);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PB3_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pb10));
  dev->dev = GLOBAL_REF (dev_gpio_pb10);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PB10_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pb15));
  dev->dev = GLOBAL_REF (dev_gpio_pb15);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PB15_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pb14));
  dev->dev = GLOBAL_REF (dev_gpio_pb14);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PB14_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pb13));
  dev->dev = GLOBAL_REF (dev_gpio_pb13);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PB13_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_pb12));
  dev->dev = GLOBAL_REF (dev_gpio_pb12);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = GPIO_PB12_PIN;

  dev = &(GLOBAL_REF (super_dev_gpio_ble_disable));
  dev->dev = GLOBAL_REF (dev_gpio_ble_disable);
  dev->type = SUPERDEVICE_TYPE_GPIO_PIN;
  dev->gpio_pin = BLEDISABLE_PIN;

  dev = &(GLOBAL_REF (super_dev_i2c2));
  dev->dev = GLOBAL_REF (dev_i2c2);
  dev->type = SUPERDEVICE_TYPE_I2C;
  dev->gpio_pin = 0;

  dev = &(GLOBAL_REF (super_dev_i2c3));
  dev->dev = GLOBAL_REF (dev_i2c3);
  dev->type = SUPERDEVICE_TYPE_I2C;
  dev->gpio_pin = 0;

  /* only non default devices need to be configured */
  /* Do not configure multi function GPIO pins */
  /* Set LED pin as output */
  /* I2C and SPI are configured automatically when system boots */
  /* gpio_pin_set is not required, gpio pins are automatically */
  /* initialized during system start */

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

  assert (gpio_pin_configure (GLOBAL_REF (dev_gpio_pb5), GPIO_PB5_PIN,
                              GPIO_OUTPUT_ACTIVE | GPIO_PB5_FLAGS)
          >= 0);

  assert (gpio_pin_configure (GLOBAL_REF (dev_gpio_pb6), GPIO_PB6_PIN,
                              GPIO_OUTPUT_ACTIVE | GPIO_PB6_FLAGS)
          >= 0);

  assert (gpio_pin_configure (GLOBAL_REF (dev_gpio_pb7), GPIO_PB7_PIN,
                              GPIO_OUTPUT_ACTIVE | GPIO_PB7_FLAGS)
          >= 0);

  assert (gpio_pin_configure (GLOBAL_REF (dev_gpio_pb8), GPIO_PB8_PIN,
                              GPIO_OUTPUT_ACTIVE | GPIO_PB8_FLAGS)
          >= 0);

  assert (gpio_pin_configure (GLOBAL_REF (dev_gpio_pb9), GPIO_PB9_PIN,
                              GPIO_OUTPUT_ACTIVE | GPIO_PB9_FLAGS)
          >= 0);

  assert (gpio_pin_configure (GLOBAL_REF (dev_gpio_ble_disable), BLEDISABLE_PIN,
                              GPIO_OUTPUT_ACTIVE | BLEDISABLE_FLAGS)
          >= 0);

  // pins are enable automatically when configuring devices from device tree
  // need to reverse output values manually
  gpio_pin_set (GLOBAL_REF (dev_led0), LED0_PIN, 0); // set LED_0 off
  gpio_pin_set (GLOBAL_REF (dev_led1), LED1_PIN, 0); // set LED_1 off
  gpio_pin_set (GLOBAL_REF (dev_led2), LED2_PIN, 0); // set LED_2 off
  gpio_pin_set (GLOBAL_REF (dev_led3), LED3_PIN, 0); // set LED_3 off
  gpio_pin_set (GLOBAL_REF (dev_gpio_ble_disable), BLEDISABLE_PIN,
                0); // enable BLE
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
  os_printk ("Platform: zephyr on %s\n", CONFIG_BOARD);

#if defined CONFIG_BOARD_LAMBDACHIP_ALONZO
  init_alonzo ();
  struct LEF_Loader loader
    = {.filename = DEFAULT_LEF, .loader = load_lef_from_tf};
  lambdachip_start (&loader);
#else
  //#  error "what?!"
  os_printk ("FATAL: LambdaChip was incorrectly configured, please check your "
             "config!\n");
  panic ("PANIC!");
#endif
}
