cmake_minimum_required(VERSION 3.13)

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected; defaulting to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_C_STANDARD 11)

# Development project uses the RPi Pico.
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project).
include(pico_sdk_import.cmake)

# Always use the latest version of the Pico SDK.
if (PICO_SDK_VERSION_STRING VERSION_LESS "1.5.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.5.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(pico-tiny)
pico_sdk_init()
add_executable(pico-tiny src/pico-tiny.c)
target_include_directories(pico-tiny PRIVATE inc)

#pico_set_program_name(pico-tiny "pico-tiny")
#pico_set_program_version(pico-tiny "0.1")

set(CMAKE_C_FLAGS_DEBUG "-g3 -Og -Wall -Wextra")
set(CMAKE_C_FLAGS_MINSIZEREL "-g2 -Os -Wall -Wextra -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g2 -Os -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELWITHDEBINFO} -DNDEBUG")

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES})
else()
    target_compile_options(pico-tiny PRIVATE -fanalyzer)
endif()

target_compile_definitions(pico-tiny PRIVATE
    PARAM_ASSERTIONS_DISABLE_ALL=1

    ## Disable alarm pool if not in use.
    #PICO_TIME_DEFAULT_ALARM_POOL_DISABLED=1

    ## Disable support for older versions of the RP2040.
    #PICO_RP2040_B0_SUPPORTED=0
    #PICO_FLOAT_SUPPORT_ROM_V1=0
    #PICO_DOUBLE_SUPPORT_ROM_V1=0
    #PICO_RP2040_B1_SUPPORTED=0

    #PICO_RUNTIME_SKIP_INIT_BOOTROM_RESET=1
    #PICO_RUNTIME_SKIP_INIT_PER_CORE_BOOTROM_RESET=1
    #PICO_RUNTIME_SKIP_POST_CLOCK_RESETS=1
    #PICO_RUNTIME_SKIP_INIT_CLOCKS=1

    ## Following is relevant to printf support only.
    PICO_STDIO_ENABLE_CRLF_SUPPORT=0
    PICO_STDIO_DEFAULT_CRLF=0
    PICO_PRINTF_SUPPORT_FLOAT=0
    PICO_PRINTF_SUPPORT_EXPONENTIAL=0
    PICO_PRINTF_SUPPORT_LONG_LONG=0
    PICO_PRINTF_SUPPORT_PTRDIFF_T=0

    # tiny_panic resets to USB with an activity LED.
    PICO_STDIO_USB_RESET_BOOTSEL_ACTIVITY_LED=1
    PICO_PANIC_FUNCTION=tiny_panic)

#set(pico_set_double_implementation pico_double_none)

# no_flash means the target is to run from RAM
pico_set_binary_type(pico-tiny no_flash)
# pico_set_binary_type(pico-tiny copy_to_ram)

# Allow USB serial terminal
pico_enable_stdio_uart(pico-tiny 0)
pico_enable_stdio_usb(pico-tiny 0)

# Add the standard library to the build
target_link_libraries(pico-tiny pico_stdlib)

# Add the standard include files to the build
target_include_directories(pico-tiny PRIVATE inc)

# Add any user requested libraries
#target_link_libraries(pico-tiny hardware_spi hardware_dma)

pico_add_extra_outputs(pico-tiny)

