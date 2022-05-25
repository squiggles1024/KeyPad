#include <ILI9341.h>
#include <ILI9341_Hardware.h>

#define CAST_AND_DEREFERENCE_32bitPtr(x) *((const uint32_t*)(&x))

typedef struct{
    uint8_t S_MSB;
    uint8_t S_LSB;
    uint8_t E_MSB;
    uint8_t E_LSB;
}ILI9341_DrawBounds_t;

typedef enum{
    DimensionsInvalid = 0,
    DimensionsValid = 1,
}ImageDimensionValidity_t;

static void ILI9341_SetCoordinates(ILI9341_Handle_t *Dev, ILI9341_Coordinate_t StartCorner, ILI9341_Coordinate_t EndCorner);
static ImageDimensionValidity_t ValidateCoordinates(ILI9341_Handle_t *Dev, ILI9341_Coordinate_t StartCorner, ILI9341_Coordinate_t EndCorner);

/******************************************************************
 *@brief: Initializes the LCD Hardware and prepares it to receive image data
 * See https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf for details regarding commands and data
 * Credit to ST Micro ILI9341.c Driver for initilization sequence
 ******************************************************************/

void ILI9341_Init(ILI9341_Init_Struct_t Settings, ILI9341_Handle_t *Dev, ILI9341_IO_Drv_t IO_Driver){
	Dev->Orientation = Settings.Orientation;
	Dev->ScreenHeight = Settings.ScreenHeight;
	Dev->ScreenWidth = Settings.ScreenWidth;
	Dev->Cursor.X = 0;
	Dev->Cursor.Y = 0;
	Dev->IO_Drv = IO_Driver;

	Dev->IO_Drv.init();
	uint8_t buffer[20];


	Dev->IO_Drv.write(ILI9341_SWRESET, buffer, 0);
	Dev->IO_Drv.ioctl(ILI9341_Delay1000);
    

	//Power Control A - Page 195
    buffer[0] = 0x39;
    buffer[1] = 0x2C;
    buffer[2] = 0x00;
    buffer[3] = 0x34;
    buffer[4] = 0x02;
	Dev->IO_Drv.write(ILI9341_PWRCONTROLA, buffer, 5);


	//Power Control B - Page 196
    buffer[0] = 0x00;
    buffer[1] = 0xC1;
    buffer[2] = 0x30;
    Dev->IO_Drv.write(ILI9341_PWRCONTROLB, buffer, 3);

    //Driver Timing Control A - Page 197
    buffer[0] = 0x85;
    buffer[1] = 0x00;
    buffer[2] = 0x78;
    Dev->IO_Drv.write(ILI9341_TIMINGCONTROLA, buffer, 3);

    //Driver Timing Control B - Page 199
    buffer[0] = 0x00;
    buffer[1] = 0x00;
    Dev->IO_Drv.write(ILI9341_TIMINGCONTROLB, buffer, 2);

    //Power on Sequence Control - Page 200
    buffer[0] = 0x64;
    buffer[1] = 0x03;
    buffer[2] = 0x12;
    buffer[3] = 0x81;
    Dev->IO_Drv.write(ILI9341_Pwr_on_sequence_control, buffer, 4);

    //Pump Ratio Control - Page 202
    buffer[0] = 0x20;
    Dev->IO_Drv.write(ILI9341_Pump_ratio_control, buffer, 1);

    //Power Control 1 - Page 178
    buffer[0] = 0x10;
    Dev->IO_Drv.write(ILI9341_PWCTRL_1, buffer, 1);

    //Power Control 2 - Page 179
    buffer[0] = 0x10;
    Dev->IO_Drv.write(ILI9341_PWCTRL_2, buffer, 1);

    //VCOM Control 1 - Page 180
    buffer[0] = 0x45;
    buffer[1] = 0x15;
    Dev->IO_Drv.write(ILI9341_VMCTRL1, buffer, 2);

    //VCOM Control 2 - Page 182
    buffer[0] = 0x90;
    Dev->IO_Drv.write(ILI9341_VMCTRL2, buffer, 1);

    //Memory Access Control - Page 127
    buffer[0] = 0x30;
    Dev->IO_Drv.write(ILI9341_MADCTL, buffer, 1);

    //Pixel Format Set - Page 134
    buffer[0] = 0x66;
    Dev->IO_Drv.write(ILI9341_PIXSET, buffer, 1);

    //Frame Rate Control (In Normal Mode/Full Colors) - Page 155
    buffer[0] = 0x00;
    buffer[1] = 0x18;
    Dev->IO_Drv.write(ILI9341_FRMCTR1, buffer, 2);

    // Display Function Control - Page 164
    buffer[0] = 0x08;
    buffer[1] = 0x82;
    buffer[2] = 0x27;
    Dev->IO_Drv.write(ILI9341_DISCTRL, buffer, 3);

    //Enable 3G - Page 201
    buffer[0] = 0x00;
    Dev->IO_Drv.write(ILI9341_Enable_3G, buffer, 1);

    //Gamma Set - Page 107
    buffer[0] = 0x01;
    Dev->IO_Drv.write(ILI9341_GAMSET, buffer, 1);

    //Positive Gamma Correction - Page 188
    buffer[0] = 0x0F;
    buffer[1] = 0x29;
    buffer[2] = 0x24;
    buffer[3] = 0x0C;
    buffer[4] = 0x0E;
    buffer[5] = 0x09;
    buffer[6] = 0x4E;
    buffer[7] = 0x78;
    buffer[8] = 0x3C;
    buffer[9] = 0x09;
    buffer[10] = 0x13;
    buffer[11] = 0x05;
    buffer[12] = 0x17;
    buffer[13] = 0x11;
    buffer[14] = 0x00;
    Dev->IO_Drv.write(ILI9341_PGAMCTRL, buffer, 15);

    //Negative Gamma Correction - Page 189
    buffer[0] = 0x00;
    buffer[1] = 0x16;
    buffer[2] = 0x1B;
    buffer[3] = 0x04;
    buffer[4] = 0x11;
    buffer[5] = 0x07;
    buffer[6] = 0x31;
    buffer[7] = 0x33;
    buffer[8] = 0x42;
    buffer[9] = 0x05;
    buffer[10] = 0x0C;
    buffer[11] = 0x0A;
    buffer[12] = 0x28;
    buffer[13] = 0x2F;
    buffer[14] = 0x0F;
    Dev->IO_Drv.write(ILI9341_NGAMCTRL, buffer, 15);

    //Sleep Out - Page 101
    Dev->IO_Drv.write(ILI9341_SLPOUT, buffer, 0);
    Dev->IO_Drv.ioctl(ILI9341_Delay150);


    //Display ON - Page 109
    Dev->IO_Drv.write(ILI9341_DISPON, buffer, 0);

    Dev->IO_Drv.write(ILI9341_MADCTL, &Settings.Orientation,1);
}

void ILI9341_DeInit(ILI9341_Handle_t *Dev){
	uint8_t dummy;
	Dev->IO_Drv.write(ILI9341_SWRESET, &dummy,0);
	Dev->IO_Drv.deinit();
}

void ILI9341_Reset(ILI9341_Handle_t *Dev){
	uint8_t dummy;
	Dev->IO_Drv.write(ILI9341_SWRESET, &dummy,0);
}

/************************************************
* Fix Later: Change screen height/width based upon orientation
************************************************/
static void ILI9341_SetScreenOrientation(ILI9341_Handle_t *Dev, ILI9341_ScreenOrientation_t Orientation){
	Dev->IO_Drv.write(ILI9341_MADCTL, &Orientation,1);
    switch(Orientation){
        case Normal:
        	Dev->ScreenHeight = 320;
        	Dev->ScreenWidth = 240;
            break;
        case YMirror:
        	Dev->ScreenHeight = 240;
        	Dev->ScreenWidth = 320;
            break;
        case XMirror:
        	Dev->ScreenHeight = 320;
        	Dev->ScreenWidth = 240;
            break;
        case XYMirror:
        	Dev->ScreenHeight = 240;
        	Dev->ScreenWidth = 320;
            break;
        case XYExchange:
        	Dev->ScreenHeight = 320;
        	Dev->ScreenWidth = 240;
            break;
        case XYExchangeYMirror:
        	Dev->ScreenHeight = 240;
        	Dev->ScreenWidth = 320;
            break;
        case XYExchangeXMirror:
        	Dev->ScreenHeight = 320;
        	Dev->ScreenWidth = 240;
            break;
        case XYExchangeXYMirror:
        	Dev->ScreenHeight = 240;
        	Dev->ScreenWidth = 320;
            break;
        default:
        	Dev->ScreenHeight = 240;
        	Dev->ScreenWidth = 320;
            break;
    }
}

void ILI9341_DrawPixel(ILI9341_Handle_t *Dev, ILI9341_Color_t Color, ILI9341_Coordinate_t Position){
    ILI9341_SetCoordinates(Dev,Position,Position);
    Dev->IO_Drv.write(ILI9341_RAMWR,(uint8_t*)&Color,3);
}

void ILI9341_FillSceen(ILI9341_Handle_t *Dev, ILI9341_Color_t Color){
    ILI9341_Coordinate_t CoordinateStart = {.X = 0, .Y = 0};
    ILI9341_Coordinate_t CoordinateEnd = {.X = Dev->ScreenWidth-1, .Y = Dev->ScreenHeight-1};
    ILI9341_SetCoordinates(Dev, CoordinateStart, CoordinateEnd);
    Dev->IO_Drv.write(ILI9341_RAMWR,(uint8_t*)&Color, 0);
    Dev->IO_Drv.write(ILI9341_NOCOMMAND, (uint8_t*)&Color, TOTAL_SCREEN_BYTES);
}

void ILI9341_DrawRectangle(ILI9341_Handle_t *Dev, uint16_t width, uint16_t height, ILI9341_Coordinate_t Middle, ILI9341_Color_t Color){

    ILI9341_Coordinate_t CoordinateStart = {.X = Middle.X - width/2, .Y = Middle.Y - height/2};
    ILI9341_Coordinate_t CoordinateEnd = {.X = Middle.X + width/2, .Y = Middle.Y + height/2};

    if(ValidateCoordinates(Dev, CoordinateStart,CoordinateEnd) == DimensionsInvalid){
        return;
    }

    if(CoordinateStart.X < 0){
        CoordinateStart.X = 0; //One pixel off screen
    }

    if(CoordinateStart.Y < 0){
        CoordinateStart.Y = 0;
    }


    if(CoordinateEnd.X > Dev->ScreenWidth - 1){
        CoordinateEnd.X = Dev->ScreenWidth - 1; //One pixel off screen
    }

    if(CoordinateStart.Y > Dev->ScreenHeight - 1){
        CoordinateStart.Y = Dev->ScreenHeight - 1;
    }

    ILI9341_SetCoordinates(Dev, CoordinateStart, CoordinateEnd);
    uint32_t TotalBytes = width*height*3;
    Dev->IO_Drv.write(ILI9341_RAMWR,(uint8_t*)&Color,0);
    Dev->IO_Drv.write(ILI9341_NOCOMMAND, (uint8_t*)&Color, TotalBytes);
}

static void ILI9341_SetCoordinates(ILI9341_Handle_t *Dev, ILI9341_Coordinate_t StartCorner, ILI9341_Coordinate_t EndCorner){
    ILI9341_DrawBounds_t Coordinate = {.S_MSB = StartCorner.X >> 8, .S_LSB = StartCorner.X, .E_MSB = EndCorner.X >> 8, .E_LSB = EndCorner.X};
    Dev->IO_Drv.write(ILI9341_CASET,(uint8_t*)&Coordinate,4);
    Coordinate.S_MSB = StartCorner.Y >> 8;
    Coordinate.S_LSB = StartCorner.Y;
    Coordinate.E_MSB = EndCorner.Y >> 8;
    Coordinate.E_LSB = EndCorner.Y;
    Dev->IO_Drv.write(ILI9341_PASET,(uint8_t*)&Coordinate,4);
}

static ImageDimensionValidity_t ValidateCoordinates(ILI9341_Handle_t *Dev, ILI9341_Coordinate_t StartCorner, ILI9341_Coordinate_t EndCorner){
    //Entire Image off screen
    if(EndCorner.X < 0 || EndCorner.Y < 0){
        return DimensionsInvalid;
    }

    //Entire Image off screen
    if(StartCorner.X >= Dev->ScreenWidth || StartCorner.Y >= Dev->ScreenHeight){
        return DimensionsInvalid;
    }

    //Start corner exceeds end corner
    if(StartCorner.X > EndCorner.X || StartCorner.Y > EndCorner.Y){
        return DimensionsInvalid;
    }
    return DimensionsValid;
}

void ILI9341_DisplayImage(ILI9341_Handle_t *Dev, ILI9341_Image_t Image){
    ILI9341_Coordinate_t CoordinateStart = {.X = Dev->Cursor.X, .Y = Dev->Cursor.Y};
    ILI9341_Coordinate_t CoordinateEnd = {.X = CoordinateStart.X + Image.Width - 1, .Y = CoordinateStart.Y + Image.Height - 1};
    ILI9341_SetCoordinates(Dev,CoordinateStart,CoordinateEnd);
    uint8_t dummy;
    //Dev->IO_Drv.write(ILI9341_RAMWR,(uint8_t*)&dummy,0);
    Dev->IO_Drv.write(ILI9341_RAMWR, Image.ImageData, Image.ImageLength);
}



void ILI9341_ImageOpen(const uint8_t *BitmapFile, ILI9341_Image_t *Image){
  Image->ImageLength = CAST_AND_DEREFERENCE_32bitPtr(BitmapFile[0x02]);
  Image->Width = CAST_AND_DEREFERENCE_32bitPtr(BitmapFile[0x12]);
  Image->Height = CAST_AND_DEREFERENCE_32bitPtr(BitmapFile[0x16]);
  Image->ImageData = (&BitmapFile[0x36]);
}

void ILI9341_DrawLine(ILI9341_Handle_t *Dev, ILI9341_Color_t Color, ILI9341_Coordinate_t Start, ILI9341_Coordinate_t End){
    ILI9341_Coordinate_t Iter = {Start.X, Start.Y};
    do{
    ILI9341_DrawPixel(Dev, Color, Iter);
    Iter.X++;
    Iter.Y = Start.Y + (End.Y - Start.Y)*Iter.X / (End.X - Start.X);
    }while(Iter.X <= End.X);
}

void ILI9341_DrawVLine(ILI9341_Handle_t *Dev, ILI9341_Color_t Color, int16_t StartX, int16_t EndY){
    ILI9341_Coordinate_t Iter = {StartX, 0};
    do{
    ILI9341_DrawPixel(Dev, Color, Iter);
    Iter.Y++;
    }while(Iter.Y <= EndY);
}

#define PixelNumberToHeightPosition(x) ((x) / font.Width)
#define PixelNumberToWidthPosition(x)  ((x) % font.Width)

/*
void ILI9341_PrintText(uint8_t *text, sFONT font, ILI9341_Color_t Color){
    uint32_t BytesToParse = (font.Height / 8) * font.Height;
    uint8_t Bitmap = 0x00;
    uint8_t Character = *text;

    ILI9341_Coordinate_t Cursor_Offset;
    ILI9341_Color_t BlackColor = {0,0,0};

    while(Character != '\0'){
        Cursor_Offset.X = Cursor.X;
        Cursor_Offset.Y = Cursor.Y;

                                       //Char * FontByteSlope           + Offset
        for(uint32_t HeightIter = 0; HeightIter < font.Height; HeightIter++){
  
            for(uint32_t WidthIter = 0; WidthIter < font.Width; WidthIter++){
                Bitmap = font.table[(Character - 32) * BytesToParse + ((HeightIter*((font.Width / 8) + 1))) + WidthIter / 8];

                if(((Bitmap >> ((7 - WidthIter) % 8)) & 0x01) == 0x01){
                    ILI9341_DrawPixel(Color,Cursor_Offset);
                } else {
                    ILI9341_DrawPixel(BlackColor,Cursor_Offset);
                }
                Cursor_Offset.X++;
                if( (Cursor_Offset.X - Cursor.X) >= font.Width){
                    Cursor_Offset.X = Cursor.X;
                    Cursor_Offset.Y++;
            }

            }
            //Update cursor

        }

    Cursor.X = Cursor.X + font.Width;
    if(Cursor.X >= SCREEN_WIDTH){
        Cursor.X = 0;
        Cursor.Y = Cursor.Y + font.Height;
    }
    text++;
    Character = *text;
    }
}
*/
