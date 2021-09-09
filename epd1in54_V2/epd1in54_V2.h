#ifndef epd1in54_V2_H
#define epd1in54_V2_H

#include "epdif.h"

// Display resolution
#define EPD_WIDTH       200
#define EPD_HEIGHT      200

class Epd : EpdIf
{
public:
	unsigned long width;
	unsigned long height;

	Epd();
	~Epd();
	// int  Init(void);
	int LDirInit(void);
	int HDirInit(void);
	void SendCommand(unsigned char command);
	void SendData(unsigned char data);
	void WaitUntilIdle(void);
	void Reset(void);
	void Clear(void);
	void Display(const unsigned char* frame_buffer);
	void DisplayPartBaseImage(const unsigned char* frame_buffer);
	void DisplayPartBaseWhiteImage(void);
	void DisplayPart(const unsigned char* frame_buffer);
	void SetFrameMemory(
	        const unsigned char* image_buffer,
	        int x,
	        int y,
	        int image_width,
	        int image_height
	);
	void SetFrameMemoryPartial(
	        const unsigned char* image_buffer,
	        int x,
	        int y,
	        int image_width,
	        int image_height
	);
	void DisplayFrame(void);
	void DisplayPartFrame(void);

	void Sleep(void);
private:
	unsigned int reset_pin;
	unsigned int dc_pin;
	unsigned int cs_pin;
	unsigned int busy_pin;
	const struct device *dev;

	void Lut(unsigned char* lut);
	void SetLut(unsigned char* lut);
	void SetMemoryArea(int x_start, int y_start, int x_end, int y_end);
	void SetMemoryPointer(int x, int y);
};

#endif /* EPD1IN54B_H */

/* END OF FILE */
