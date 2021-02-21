# SPDX-License-Identifier: LGPLv3

cmake_minimum_required(VERSION 3.13.1)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(lambdachip-zephyr)

zephyr_compile_definitions(LAMBDACHIP_DEBUG)
zephyr_compile_definitions(LAMBDACHIP_ZEPHYR, CONFIG_DEPRECATED_ZEPHYR_INT_TYPES)
zephyr_library_compile_options(-Wall -Wno-unused -Wextra
  -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -Wno-pointer-arith
  -fdiagnostics-color=always -Wno-strict-aliasing -Wno-discarded-qualifiers)

zephyr_include_directories(app PRIVATE ${ZEPHYR_BASE}/include)
zephyr_include_directories(${APPLICATION_SOURCE_DIR}/lambdachip/inc)

FILE(GLOB app_sources src/*.c lambdachip/*.c)
# FILE(GLOB app_sources src/main.c lambdachip/*.c)
target_sources(app PRIVATE ${app_sources})
