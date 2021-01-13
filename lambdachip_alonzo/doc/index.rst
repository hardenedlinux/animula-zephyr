.. _LambdaChip_Alonzo_board:

LambdaChip Alonzo
#################

Overview
********

The LambdaChip Alonzo board features an ARM Cortex-M4 based STM32F411CE MCU
with a wide range of connectivity support and configurations. Here are
some highlights of the LambdaChip Alonzo board:

- STM32 microcontroller in UFQFN48 package
- It comes out with these resources:
  - 2.54 Header connecters
  - Bluetooth 4.0 BLE

- Four user LEDs: D2, D3, D4, D5
- 3 push-buttons: BOOT0, RST, USER BUTTON

.. image:: img/lambdachip_alonzo.png
   :width: 720px
   :align: center
   :height: 720px
   :alt: LambdaChip Alonzo F411CE

More information about the board can be found at the `lambdachip website/alonzo`_.

Hardware
********

LambdaChip Alonzo F411CE provides the following hardware components:

- STM32F411CET6 in UFQFN48 package
- ARM |reg| 32-bit Cortex |reg|-M4 CPU with FPU
- 100 MHz max CPU frequency
- VDD from 1.7 V to 3.6 V
- 512 KB Flash
- 128 KB SRAM
- GPIO with external interrupt capability
- 12-bit ADC with 16 channels, with FIFO and burst support
- 8 General purpose timers
- 2 watchdog timers (independent and window)
- SysTick timer
- USART/UART (3)
- I2C (3)
- SPI (5)
- SDIO
- USB 2.0 OTG FS
- DMA Controller
- CRC calculation unit

More information about STM32F411CE can be found here:

- `STM32F411CE on www.st.com`_
- `STM32F411 reference manual`_

Supported Features
==================

The Zephyr lambdachip_alonzo board configuration supports the following hardware features:

+-----------+------------+-------------------------------------+
| Interface | Controller | Driver/Component                    |
+===========+============+=====================================+
| NVIC      | on-chip    | nested vector interrupt controller  |
+-----------+------------+-------------------------------------+
| UART      | on-chip    | serial port                         |
+-----------+------------+-------------------------------------+
| GPIO      | on-chip    | gpio                                |
+-----------+------------+-------------------------------------+
| PWM       | on-chip    | pwm                                 |
+-----------+------------+-------------------------------------+
| I2C       | on-chip    | i2c                                 |
+-----------+------------+-------------------------------------+
| SPI       | on-chip    | spi                                 |
+-----------+------------+-------------------------------------+

Other hardware features are not yet supported on this Zephyr port.

The default configuration can be found in the defconfig file:
``boards/arm/lambdachip_alonzo/lambdachip_alonzo_defconfig``


Connections and IOs
===================

LambdaChip Alonzo F411CE Board has 8 GPIO controllers. These controllers are responsible for pin muxing,
input/output, pull-up, etc.


Default Zephyr Peripheral Mapping:
----------------------------------

- UART_1 TX/RX : PB9/PA10
- UART_2 TX/RX : PA2/PA3 (For BLE)
- I2C1 SCL/SDA : PB8/PB9 (Arduino I2C)
- I2C2 SCL/SDA : PB10/PB3
- I2C1 SCL/SDA : PA8/B4
- SPI1 CS/SCK/MISO/MOSI : PA4/PA5/PA6/PA7 (Arduino SPI)
- USER_PB   : PC13
- LD2       : PA5


System Clock
------------

LambdaChip Alonzo System Clock is driven by external oscillator,
as well as main PLL clock. By default System clock is driven by PLL clock at 96MHz,
driven by 24MHz high speed external clock.

Serial Port
-----------

LambdaChip Alonzo board has 3 UARTs. The Zephyr console output is assigned to UART1.
Default settings are 115200 8N1.


Programming and Debugging
*************************

Applications for the ``lambdachip_alonzo`` board configuration can be built and
flashed in the usual way (see :ref:`build_an_application` and
:ref:`application_run` for more details).

Debugging
=========

You can debug an application in the usual way.  Here is an example for the
:ref:`hello_world` application.

.. zephyr-app-commands::
   :zephyr-app: samples/hello_world
   :board: lambdachip_alonzo
   :maybe-skip-config:
   :goals: debug

.. _lambdachip website/alonzo:
   http://lambdachip.com/


