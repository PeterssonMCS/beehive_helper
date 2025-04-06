# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Atividade_Final C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Atividade_Final 
                Atividade_Final.c
                pOS.c
                hal/hardware/gpio/gpio.c 
                hal/hardware/timer/timer.c 
                hal/hardware/i2c/i2c.c 
                hal/hardware/spi/spi.c 
                hal/hardware/adc/adc.c 
                hal/hardware/pwm/pwm.c
                hal_def.c 
                hal/led/led.c
                hal/buzzer/buzzer.c
                hal/joystick/joystick.c
                hal/display/driver1306.c
                hal/display/font.c
                hal/microphone/microphone.c
                ihm/ihm.c
                hal/aht10/aht10.c
                ihm/bee.c
                hal/button/button.c)

pico_set_program_name(Atividade_Final "Atividade_Final")
pico_set_program_version(Atividade_Final "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Atividade_Final 0)
pico_enable_stdio_usb(Atividade_Final 1)

# Add the standard library to the build
target_link_libraries(Atividade_Final
        pico_stdlib 
        hardware_i2c 
        hardware_spi 
        hardware_adc
        hardware_pwm
        hardware_dma)

# Add the standard include files to the build
target_include_directories(Atividade_Final PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(Atividade_Final 
        
        )

pico_add_extra_outputs(Atividade_Final)

