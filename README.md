# nrf52840-dongle-e-paper-display
Using **nrf52840 dongle** with **zephyr rtos** to display stuff on waveshare **epaper display** through SPI  

Zephyr build:  
```
cd zephyrproject/zephyr
west build -p -b nrf52840dongle_nrf52840 samples/subsys/display/lvgl -- -DSHIELD=waveshare_epaper_gdeh0154a07
```
