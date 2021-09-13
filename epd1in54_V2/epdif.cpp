#include "epdif.h"

#include <drivers/gpio.h>
#include <drivers/spi.h>
#include <zephyr.h>
#include <device.h>

EpdIf::EpdIf() {
};

EpdIf::~EpdIf() {
};

static const struct device *spi_display;
// static struct spi_cs_control cs_ctrl;
static const struct spi_config spi_cfg = {
	.frequency = 2000000U,
    .operation = SPI_TRANSFER_MSB | SPI_MODE_CPOL | SPI_MODE_CPHA,
    .slave = 0,
};

// static struct spi_buf tx;
// const static struct spi_buf_set tx_bufs = {
//     .buffers = &tx,
//     .count = 1,
// };
// uint8_t spi_data[] = {0};

void EpdIf::DigitalWrite(const struct device *gpio0, int pin, int value) {
    gpio_pin_set(gpio0, pin, value);
}

int EpdIf::DigitalRead(const struct device *gpio0, int pin) {
    return gpio_pin_get(gpio0, pin);
}

void EpdIf::DelayMs(unsigned int delaytime) {
    k_msleep(delaytime);
}

void EpdIf::SpiTransfer(unsigned char data) {
    gpio_pin_set(gpio0, CS_PIN, 0);
    // spi_data[0] = data;
    // tx.buf = spi_data;
    struct spi_buf tx_buf = {.buf = &data, .len = 1};
	struct spi_buf_set tx_bufs = {.buffers = &tx_buf, .count = 1};   
    spi_transceive (spi_display, &spi_cfg, &tx_bufs, NULL);
    gpio_pin_set(gpio0, CS_PIN, 1);
}

int EpdIf::IfInit(void) {
    gpio0 = device_get_binding("GPIO_0");

    gpio_pin_configure(gpio0, CS_PIN, GPIO_OUTPUT);
    gpio_pin_configure(gpio0, RST_PIN, GPIO_OUTPUT);
    gpio_pin_configure(gpio0, DC_PIN, GPIO_OUTPUT);
    gpio_pin_configure(gpio0, BUSY_PIN, GPIO_INPUT); 

    spi_display = device_get_binding("SPI_0");

    // SPI.begin();
    // SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    return 0;
}