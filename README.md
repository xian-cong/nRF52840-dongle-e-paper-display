# nRF52840 Dongle E-paper Display
Using **nrf52840 dongle** with **zephyr rtos** to display stuff on [**waveshare epaper display**](https://www.waveshare.com/e-paper-shield.htm) through SPI  

Zephyr build:  
```
west build -p -b nrf52840dongle_nrf52840 samples/myprojects/epd1in54_V2
```
Zephyr documentation:
https://docs.zephyrproject.org/latest/boards/shields/waveshare_epaper/doc/index.html  
Waveshare e-paper module:
https://www.waveshare.com/wiki/1.54inch_e-Paper_Module  
