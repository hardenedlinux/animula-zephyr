# SPDX-License-Identifier: LGPLv3

cmake_minimum_required(VERSION 3.13.1)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(lambdachip)

zephyr_compile_definitions(LAMBDACHIP_ZEPHYR, LAMBDACHIP_DEBUG, CONFIG_DEPRECATED_ZEPHYR_INT_TYPES)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -Wall -Wno-pointer-arith")

zephyr_include_directories(app PRIVATE ${ZEPHYR_BASE}/includ)
zephyr_include_directories(${APPLICATION_SOURCE_DIR}/lambdachip/inc)

# zephyr_include_directories(${ZEPHYR_BASE}/boards/x86/up_squared)
target_sources(app PRIVATE
lambdachip/gc.c
lambdachip/lambdachip.c
lambdachip/lef.c
lambdachip/lib.c
lambdachip/list.c
lambdachip/memory.c
lambdachip/object.c
lambdachip/primitives.c
lambdachip/print.c
lambdachip/shell.c
lambdachip/stdio.c
lambdachip/storage.c
lambdachip/str.c
lambdachip/symbol.c
lambdachip/vector.c
lambdachip/vm.c
src/main.c)
