# SPDX-License-Identifier: LGPLv3

cmake_minimum_required(VERSION 3.13.1)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(lambdachip)

add_definitions(-DLAMBDACHIP_ZEPHYR -DLAMBDACHIP_DEBUG)
include_directories(lambdachip/inc)
target_sources(app PRIVATE
  lambdachip/lambdachip.c
  lambdachip/object.c
  lambdachip/values.c
  lambdachip/memory.c
  lambdachip/primitives.c
  lambdachip/shell.c
  lambdachip/lib.c
  lambdachip/lef.c
  lambdachip/stdio.c
  lambdachip/storage.c
  lambdachip/gc.c
  lambdachip/vm.c
  src/main.c)
