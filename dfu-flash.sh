#!/bin/bash

sudo dfu-util -a 0 -s 0x08004000:leave -D  build/zephyr/zephyr.bin
