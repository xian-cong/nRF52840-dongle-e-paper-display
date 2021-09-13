cmake_minimum_required(VERSION 3.13.1)

# set(BOARD nrf52840dongle_nrf52840)

find_package(Zephyr HINTS $ENV{ZEPHYR_BASE})
project(epd1in54_V2)

target_sources(app PRIVATE main.cpp)
target_sources(app PRIVATE epd1in54_V2.cpp)
target_sources(app PRIVATE epd1in54_V2.h)
target_sources(app PRIVATE epdif.cpp)
target_sources(app PRIVATE epdif.h)
target_sources(app PRIVATE epdpaint.cpp)
target_sources(app PRIVATE epdpaint.h)
target_sources(app PRIVATE font8.c)
target_sources(app PRIVATE font12.c)
target_sources(app PRIVATE font20.c)
target_sources(app PRIVATE font24.c)
target_sources(app PRIVATE fonts.h)
# target_sources(app PRIVATE imagedata.cpp)
# target_sources(app PRIVATE imagedata.h)

target_include_directories(app PRIVATE ./)