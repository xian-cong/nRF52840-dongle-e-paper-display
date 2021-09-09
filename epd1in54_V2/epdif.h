#ifndef EPDIF_H
#define EPDIF_H

#include <zephyr.h>

#define RST_PIN         13
#define DC_PIN          15
#define CS_PIN          17
#define BUSY_PIN        20

class EpdIf {
private:
    const struct device *gpio0;
    const struct device *spi_display;
    struct spi_cs_control spi_cs;
	const struct spi_config spi_cfg;
public:
    EpdIf(void);
    ~EpdIf(void);

    static int  IfInit(void);
    static void DigitalWrite(const struct device *gpio0, int pin, int value); 
    static int  DigitalRead(const struct device *gpio0, int pin);
    static void DelayMs(unsigned int delaytime);
    static void SpiTransfer(unsigned char data);

};

#endif