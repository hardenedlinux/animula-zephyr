# SPDX-License-Identifier: LGPLv3

cmake_minimum_required(VERSION 3.13.1)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(lambdachip-zephyr)

zephyr_compile_definitions(LAMBDACHIP_DEBUG)
zephyr_compile_definitions(LAMBDACHIP_ZEPHYR, CONFIG_DEPRECATED_ZEPHYR_INT_TYPES)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -Wall -Wno-pointer-arith -Wno-strict-aliasing -Wno-bool-compare -fdiagnostics-color=always")

zephyr_include_directories(app PRIVATE ${ZEPHYR_BASE}/include)
zephyr_include_directories(${APPLICATION_SOURCE_DIR}/lambdachip/inc)

FILE(GLOB app_sources src/*.c lambdachip/*.c)
# FILE(GLOB app_sources src/main.c lambdachip/*.c)
target_sources(app PRIVATE ${app_sources})

