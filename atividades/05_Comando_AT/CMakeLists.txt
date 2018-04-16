set(ENV{ZEPHYR_BASE} /Users/cristopher/zephyr)
set(ENV{ZEPHYR_TOOLCHAIN_VARIANT} gccarmemb)
set(ENV{GCCARMEMB_TOOLCHAIN_PATH} /Users/cristopher/gcc-arm-none-eabi-7-2017-q4-major)

set(BOARD "bbc_microbit")

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(05_Comando_AT)

message(WARNING "Main file: ${PROJECT_SOURCE_DIR}/src/main.c")

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    )

list(APPEND SOURCES
    "${PROJECT_SOURCE_DIR}/src/uart_driver.c"
    "${PROJECT_SOURCE_DIR}/src/at.c"
    "${PROJECT_SOURCE_DIR}/src/main.c"
    )

target_sources(app PRIVATE ${SOURCES})
