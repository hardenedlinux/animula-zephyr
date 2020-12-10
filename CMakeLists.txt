# SPDX-License-Identifier: LGPLv3

cmake_minimum_required(VERSION 3.13.1)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(lambdachip)

add_definitions(-DLAMBDACHIP_ZEPHYR -DLAMBDACHIP_DEBUG)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -Wall -Wno-pointer-arith")
include_directories(lambdachip/inc)
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
