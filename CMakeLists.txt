# SPDX-License-Identifier: LGPLv3

cmake_minimum_required(VERSION 3.13.1)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(lambdachip)

add_definitions(-DLAMBDACHIP_ZEPHYR -DLAMBDACHIP_DEBUG)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -Wall -Wno-pointer-arith")
include_directories(lambdachip/inc)
target_sources(app PRIVATE
  lambdachip/closure.c
  lambdachip/lef.c
  lambdachip/memory.c
  lambdachip/print.c
  lambdachip/storage.c
  lambdachip/gc.c
  lambdachip/lib.c
  lambdachip/object.c
  lambdachip/shell.c
  lambdachip/vector.c
  lambdachip/lambdachip.c
  lambdachip/list.c
  lambdachip/primitives.c
  lambdachip/stdio.c
  lambdachip/vm.c
  src/main.c)
