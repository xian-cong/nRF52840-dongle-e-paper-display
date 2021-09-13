#ifndef EPDIF_H
#define EPDIF_H

#include <zephyr.h>

#define RST_PIN         13
#define DC_PIN          15
#define CS_PIN          17
#define BUSY_PIN        20

class EpdIf {
private:
public:
    EpdIf(void);
    ~EpdIf(void);

    const struct device *gpio0;

    static int  IfInit(void);
    static void DigitalWrite(const struct device *gpio0, int pin, int value); 
    static int  DigitalRead(const struct device *gpio0, int pin);
    static void DelayMs(unsigned int delaytime);
    static void SpiTransfer(unsigned char data);

};

#endif