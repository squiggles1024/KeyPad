#ifndef ILI9341_HARDWARE_H_
#define ILI9341_HARDWARE_H_
#include <stdint.h>

typedef enum{
	ILI9341_Ok,
	ILI9341_Err
}ILI9341_Status_t;

typedef enum{
    ILI9341_Delay150,
	ILI9341_Delay1000
}ILI9341_Cmd_t;

typedef struct{
    void(*init)(void);
    void(*deinit)(void);
    ILI9341_Status_t (*write)(uint8_t, uint8_t*, uint32_t);
    ILI9341_Status_t (*read)(uint8_t, uint8_t*, uint32_t);
    uint8_t (*ioctl)(ILI9341_Cmd_t);
}ILI9341_IO_Drv_t;

extern ILI9341_IO_Drv_t ILI931_IO;


#endif