/*
*========================================================================================================
*
* File                : LCD_22.C
* Hardware Environment: STM32F446
* Build Environment   : Keil uVision 5
* Version             : 1.0
* By                  : Victor Nikitchuk & WaveShare Indian programmers
*
*	Основано на примере для Open16F877A. https://www.waveshare.com/wiki/File:Open16F877A-Demo.7z
*
*========================================================================================================
*/

#include "LCD_22.h"

//Шрифт
unsigned char ascii[]= {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//0
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x18,0x3C,0x7E,0x7E,0x7E,0x3C,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0xE7,0xC3,0x81,0x81,0x81,0xC3,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x1F,0x05,0x05,0x09,0x09,0x10,0x10,0x38,0x44,0x44,0x44,0x38,0x00,0x00,0x00,
0x00,0x1C,0x22,0x22,0x22,0x1C,0x08,0x08,0x7F,0x08,0x08,0x08,0x08,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x03,0x1D,0x11,0x13,0x1D,0x11,0x11,0x11,0x13,0x17,0x36,0x70,0x60,0x00,0x00,0x00,
0x08,0x08,0x5D,0x22,0x22,0x22,0x63,0x22,0x22,0x22,0x5D,0x08,0x08,0x00,0x00,0x00,	//0f
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xFF,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,
0x08,0x1C,0x2A,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x2A,0x1C,0x08,0x00,0x00,
0x00,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x00,0x00,0x24,0x24,0x00,0x00,
0x00,0x1F,0x25,0x45,0x45,0x45,0x25,0x1D,0x05,0x05,0x05,0x05,0x05,0x00,0x00,0x00,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x08,0x1C,0x2A,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0F,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x00,0x00,0x00,0x00,0x04,0x02,0x7F,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x10,0x20,0x7F,0x20,0x10,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	 //1F
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   
0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x18,0x18,0x00,0x00,0x00,
0x12,0x36,0x24,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x24,0x24,0x24,0xFE,0x48,0x48,0x48,0xFE,0x48,0x48,0x48,0x00,0x00,0x00,
0x00,0x10,0x38,0x54,0x54,0x50,0x30,0x18,0x14,0x14,0x54,0x54,0x38,0x10,0x10,0x00,
0x00,0x00,0x44,0xA4,0xA8,0xA8,0xA8,0x54,0x1A,0x2A,0x2A,0x2A,0x44,0x00,0x00,0x00,
0x00,0x00,0x30,0x48,0x48,0x48,0x50,0x6E,0xA4,0x94,0x88,0x89,0x76,0x00,0x00,0x00,
0x60,0x60,0x20,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x02,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x02,0x00,0x00,
0x40,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20,0x40,0x00,0x00,
0x00,0x00,0x00,0x10,0x10,0xD6,0x38,0x38,0xD6,0x10,0x10,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x10,0x10,0x10,0x10,0xFE,0x10,0x10,0x10,0x10,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x20,0xC0,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x00,0x00,
0x00,0x01,0x02,0x02,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x40,0x00,0x00,
0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,0x00,
0x00,0x00,0x10,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,0x00,
0x00,0x00,0x3C,0x42,0x42,0x42,0x04,0x04,0x08,0x10,0x20,0x42,0x7E,0x00,0x00,0x00,
0x00,0x00,0x3C,0x42,0x42,0x04,0x18,0x04,0x02,0x02,0x42,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0x04,0x0C,0x14,0x24,0x24,0x44,0x44,0x7E,0x04,0x04,0x1E,0x00,0x00,0x00,
0x00,0x00,0x7E,0x40,0x40,0x40,0x58,0x64,0x02,0x02,0x42,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0x1C,0x24,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x24,0x18,0x00,0x00,0x00,
0x00,0x00,0x7E,0x44,0x44,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00,
0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00,0x00,
0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x26,0x1A,0x02,0x02,0x24,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x20,0x00,
0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x40,0x00,0x00,0x00,
0x00,0x00,0x3C,0x42,0x42,0x62,0x02,0x04,0x08,0x08,0x00,0x18,0x18,0x00,0x00,0x00,
0x00,0x00,0x38,0x44,0x5A,0xAA,0xAA,0xAA,0xAA,0xB4,0x42,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0x10,0x10,0x18,0x28,0x28,0x24,0x3C,0x44,0x42,0x42,0xE7,0x00,0x00,0x00,
0x00,0x00,0xF8,0x44,0x44,0x44,0x78,0x44,0x42,0x42,0x42,0x44,0xF8,0x00,0x00,0x00,
0x00,0x00,0x3E,0x42,0x42,0x80,0x80,0x80,0x80,0x80,0x42,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0xF8,0x44,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0xF8,0x00,0x00,0x00,
0x00,0x00,0xFC,0x42,0x48,0x48,0x78,0x48,0x48,0x40,0x42,0x42,0xFC,0x00,0x00,0x00,
0x00,0x00,0xFC,0x42,0x48,0x48,0x78,0x48,0x48,0x40,0x40,0x40,0xE0,0x00,0x00,0x00,
0x00,0x00,0x3C,0x44,0x44,0x80,0x80,0x80,0x8E,0x84,0x44,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0xE7,0x00,0x00,0x00,
0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,0x00,
0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x88,0xF0,0x00,
0x00,0x00,0xEE,0x44,0x48,0x50,0x70,0x50,0x48,0x48,0x44,0x44,0xEE,0x00,0x00,0x00,
0x00,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x42,0xFE,0x00,0x00,0x00,
0x00,0x00,0xEE,0x6C,0x6C,0x6C,0x6C,0x54,0x54,0x54,0x54,0x54,0xD6,0x00,0x00,0x00,
0x00,0x00,0xC7,0x62,0x62,0x52,0x52,0x4A,0x4A,0x4A,0x46,0x46,0xE2,0x00,0x00,0x00,
0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0xFC,0x42,0x42,0x42,0x42,0x7C,0x40,0x40,0x40,0x40,0xE0,0x00,0x00,0x00,
0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0xB2,0xCA,0x4C,0x38,0x06,0x00,0x00,
0x00,0x00,0xFC,0x42,0x42,0x42,0x7C,0x48,0x48,0x44,0x44,0x42,0xE3,0x00,0x00,0x00,
0x00,0x00,0x3E,0x42,0x42,0x40,0x20,0x18,0x04,0x02,0x42,0x42,0x7C,0x00,0x00,0x00,
0x00,0x00,0xFE,0x92,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,0x00,
0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,0x00,
0x00,0x00,0xE7,0x42,0x42,0x44,0x24,0x24,0x28,0x28,0x18,0x10,0x10,0x00,0x00,0x00,
0x00,0x00,0xD6,0x92,0x92,0x92,0x92,0xAA,0xAA,0x6C,0x44,0x44,0x44,0x00,0x00,0x00,
0x00,0x00,0xE7,0x42,0x24,0x24,0x18,0x18,0x18,0x24,0x24,0x42,0xE7,0x00,0x00,0x00,
0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,0x00,
0x00,0x00,0x7E,0x84,0x04,0x08,0x08,0x10,0x20,0x20,0x42,0x42,0xFC,0x00,0x00,0x00,
0x1E,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1E,0x00,0x00,
0x00,0x40,0x40,0x20,0x20,0x10,0x10,0x10,0x08,0x08,0x04,0x04,0x04,0x02,0x02,0x00,
0x78,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x78,0x00,0x00,
0x1C,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,
0x60,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x1E,0x22,0x42,0x42,0x3F,0x00,0x00,0x00,
0x00,0x00,0xC0,0x40,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x64,0x58,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x40,0x40,0x40,0x22,0x1C,0x00,0x00,0x00,
0x00,0x00,0x06,0x02,0x02,0x02,0x1E,0x22,0x42,0x42,0x42,0x26,0x1B,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x7E,0x40,0x40,0x42,0x3C,0x00,0x00,0x00,
0x00,0x00,0x0F,0x11,0x10,0x10,0x7E,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x44,0x44,0x38,0x40,0x3C,0x42,0x42,0x3C,0x00,
0x00,0x00,0xC0,0x40,0x40,0x40,0x5C,0x62,0x42,0x42,0x42,0x42,0xE7,0x00,0x00,0x00,
0x00,0x00,0x30,0x30,0x00,0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,0x00,
0x00,0x00,0x0C,0x0C,0x00,0x00,0x1C,0x04,0x04,0x04,0x04,0x04,0x04,0x44,0x78,0x00,
0x00,0x00,0xC0,0x40,0x40,0x40,0x4E,0x48,0x50,0x68,0x48,0x44,0xEE,0x00,0x00,0x00,
0x00,0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x49,0x49,0x49,0x49,0x49,0xED,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xDC,0x62,0x42,0x42,0x42,0x42,0xE7,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xD8,0x64,0x42,0x42,0x42,0x44,0x78,0x40,0xE0,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x22,0x42,0x42,0x42,0x22,0x1E,0x02,0x07,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x32,0x20,0x20,0x20,0x20,0xF8,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x42,0x40,0x3C,0x02,0x42,0x7C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x10,0x10,0x7C,0x10,0x10,0x10,0x10,0x10,0x0C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xC6,0x42,0x42,0x42,0x42,0x46,0x3B,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x28,0x10,0x10,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xD7,0x92,0x92,0xAA,0xAA,0x44,0x44,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x6E,0x24,0x18,0x18,0x18,0x24,0x76,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x28,0x18,0x10,0x10,0xE0,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x44,0x08,0x10,0x10,0x22,0x7E,0x00,0x00,0x00, 
0x03,0x04,0x04,0x04,0x04,0x04,0x08,0x04,0x04,0x04,0x04,0x04,0x04,0x03,0x00,0x00,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x60,0x10,0x10,0x10,0x10,0x10,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x60,0x00,0x00,
0x4C,0x43,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*
0x00,0x00,0x1F,0x23,0x41,0x40,0xFE,0x40,0xFE,0x40,0x40,0x22,0x1C,0x00,0x00,0x00,	//128
0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x20,0x20,0x00,0x00,
0x00,0x07,0x04,0x04,0x08,0x0C,0x08,0x08,0x18,0x10,0x10,0x10,0x20,0x20,0xC0,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x6E,0x22,0x44,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x63,0x63,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x18,0x18,0x10,0x7E,0x10,0x18,0x18,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
0x00,0x18,0x18,0x76,0x7E,0x18,0x10,0x10,0x10,0x10,0x18,0x76,0x5A,0x18,0x18,0x00,
0x00,0x30,0x50,0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x30,0x48,0x48,0x48,0x49,0x32,0x04,0x08,0x11,0x22,0x42,0x82,0x02,0x01,0x00,0x00,
0x3C,0x00,0x3C,0x42,0x40,0x40,0x30,0x0C,0x06,0x02,0x02,0x42,0x7C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x10,0x20,0x60,0x60,0x20,0x10,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x3E,0x4A,0x48,0x48,0x4A,0x4E,0x48,0x48,0x48,0x49,0x3F,0x00,0x00,0x00,
0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,
0x14,0x08,0x00,0x7F,0x01,0x02,0x04,0x08,0x08,0x10,0x20,0x40,0x7F,0x00,0x00,0x00,
0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,
0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x60,0x60,0x20,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x01,0x01,0x00,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3C,0x3C,0x3C,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x60,0xB8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xE9,0x4B,0x4B,0x5D,0x55,0x5F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x88,0x70,0x20,0x30,0x48,0x40,0x60,0x38,0x0C,0x4C,0x78,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x40,0x20,0x30,0x10,0x20,0x20,0x40,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x02,0x7D,0x49,0x4F,0x48,0x48,0x4D,0x36,0x00,0x00,0x00,0x00,
0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0x28,0x10,0x00,0x7C,0x04,0x08,0x10,0x20,0x40,0x7C,0x00,0x00,0x00,
0x24,0x00,0x42,0x44,0x24,0x28,0x18,0x18,0x10,0x10,0x10,0x10,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x60,0x90,0x90,0x60,0x00,0x0E,0x11,0x20,0x20,0x20,0x20,0x20,0x11,0x0E,0x00,	//
0x00,0x60,0x90,0x90,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//
0x00,0x00,0x00,0x00,0x20,0x20,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,    //
0x00,0x04,0x04,0x04,0x18,0x2E,0x4E,0x50,0x50,0x50,0x22,0x3C,0x40,0x40,0x40,0x00,
0x00,0x00,0x1E,0x22,0x20,0x20,0x20,0x38,0x20,0x20,0x21,0xFA,0x4C,0x00,0x00,0x00, 
0x40,0x27,0x18,0x10,0x20,0x20,0x20,0x20,0x20,0x20,0x10,0x18,0x27,0x40,0x00,0x00,
0x00,0x00,0x62,0x24,0x24,0x14,0x18,0xFF,0x08,0xFF,0x08,0x08,0x3C,0x00,0x00,0x00,
0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x00,
0x08,0x08,0x04,0x02,0x03,0x04,0x08,0x08,0x05,0x02,0x01,0x04,0x08,0x08,0x07,0x00,
0x00,0x00,0x0C,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x7E,0xA6,0xC1,0xC1,0xC1,0xA6,0x5A,0x24,0x00,0x00,0x00,0x00,0x00,
0x00,0xE0,0x90,0xF0,0x90,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x11,0x22,0x24,0x44,0x4C,0x24,0x22,0x12,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xFF,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x7E,0xAA,0xA5,0xB9,0xA9,0xA6,0x42,0x3C,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x30,0x48,0x48,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x01,0x01,0x0F,0x01,0x01,0x01,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,
0x00,0x70,0x90,0x10,0x20,0x50,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x70,0x10,0x20,0x10,0x10,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x10,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x22,0x22,0x22,0x22,0x22,0x2F,0x50,0x40,0x40,0x00,0x00,0x00,
0x00,0x3E,0xF4,0xF4,0xF4,0xF4,0x74,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0x07,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x10,0x60,0x00,
0x00,0x20,0x20,0x20,0x20,0x20,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x70,0x98,0x88,0x50,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x88,0x48,0x24,0x22,0x32,0x24,0x44,0x88,0x00,0x00,0x00,0x00,
0x00,0x42,0x44,0x44,0x48,0x48,0x50,0x12,0x26,0x26,0x27,0x40,0x00,0x00,0x00,0x00,
0x00,0x44,0x44,0x44,0x48,0x48,0x50,0x17,0x21,0x22,0x44,0x47,0x00,0x00,0x00,0x00,
0x00,0x62,0x24,0x44,0x28,0x28,0x50,0x12,0x16,0x26,0x27,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x10,0x10,0x00,0x00,0x10,0x20,0x20,0x44,0x44,0x3C,0x00,0x00,0x00,
0x10,0x00,0x10,0x18,0x28,0x28,0x28,0x24,0x3C,0x44,0x44,0x42,0xC7,0x00,0x00,0x00,
0x10,0x20,0x10,0x18,0x28,0x28,0x28,0x24,0x3C,0x44,0x44,0x42,0xC7,0x00,0x00,0x00,
0x28,0x00,0x10,0x18,0x28,0x28,0x28,0x24,0x3C,0x44,0x44,0x42,0xC7,0x00,0x00,0x00,
0x0C,0x00,0x10,0x18,0x28,0x28,0x28,0x24,0x3C,0x44,0x44,0x42,0xC7,0x00,0x00,0x00,
0x3C,0x00,0x10,0x18,0x28,0x28,0x28,0x24,0x3C,0x44,0x44,0x42,0xC7,0x00,0x00,0x00,
0x28,0x18,0x10,0x18,0x28,0x28,0x28,0x24,0x3C,0x44,0x44,0x42,0xC7,0x00,0x00,0x00,
0x00,0x00,0x1E,0x18,0x28,0x28,0x2A,0x4E,0x78,0x48,0x48,0x89,0xDE,0x00,0x00,0x00,
0x00,0x00,0x1C,0x23,0x41,0x40,0x40,0x40,0x40,0x40,0x61,0x32,0x0C,0x08,0x08,0x00,
0x10,0x10,0x6E,0x42,0x40,0x44,0x44,0x7C,0x44,0x40,0x40,0x42,0xFE,0x00,0x00,0x00,
0x08,0x10,0x6E,0x42,0x40,0x44,0x44,0x7C,0x44,0x40,0x40,0x42,0xFE,0x00,0x00,0x00,
0x28,0x44,0x7E,0x42,0x40,0x44,0x44,0x7C,0x44,0x40,0x40,0x42,0xFE,0x00,0x00,0x00,
0x2C,0x00,0x7E,0x42,0x40,0x44,0x44,0x7C,0x44,0x40,0x40,0x42,0xFE,0x00,0x00,0x00,
0x10,0x10,0x38,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,0x00,
0x08,0x10,0x38,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,0x00,
0x28,0x00,0x38,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,0x00, 
0x2C,0x00,0x38,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,0x00,
0x00,0x00,0x3C,0x22,0x22,0x21,0x21,0x31,0x21,0x23,0x22,0x26,0x78,0x00,0x00,0x00,
0x0C,0x00,0x42,0x62,0x62,0x52,0x52,0x4A,0x4A,0x46,0x46,0x42,0xE2,0x00,0x00,0x00,
0x10,0x10,0x2C,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,0x00,
0x10,0x10,0x2C,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,0x00,
0x28,0x44,0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,0x00,
0x0C,0x00,0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,0x00,
0x24,0x00,0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,0x00,
0x00,0x00,0x10,0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x10,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x3C,0x42,0x46,0x4A,0x4A,0x53,0x52,0x62,0x62,0x44,0x38,0x00,0x00,0x00,
0x10,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0x38,0x00,0x00,0x00,
0x08,0x10,0x62,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0x38,0x00,0x00,0x00,
0x28,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0x38,0x00,0x00,0x00,
0x24,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0x38,0x00,0x00,0x00,
0x08,0x10,0x62,0x44,0x24,0x28,0x18,0x18,0x10,0x10,0x10,0x10,0x3C,0x00,0x00,0x00,
0x00,0x00,0x20,0x20,0x38,0x26,0x21,0x21,0x21,0x26,0x38,0x20,0x70,0x00,0x00,0x00,
0x00,0x00,0x1C,0x22,0x22,0x22,0x2C,0x22,0x22,0x22,0x22,0x3A,0x6C,0x00,0x00,0x00,
0x00,0x00,0x00,0x10,0x00,0x00,0x38,0x44,0x44,0x44,0x44,0x44,0x3A,0x00,0x00,0x00,
0x00,0x00,0x00,0x08,0x18,0x00,0x38,0x44,0x44,0x44,0x44,0x44,0x3A,0x00,0x00,0x00,
0x00,0x30,0x28,0x44,0x00,0x00,0x7C,0x44,0x1C,0x64,0x44,0x45,0x3A,0x00,0x00,0x00,
0x00,0x20,0x5C,0x00,0x00,0x00,0x7C,0x44,0x1C,0x64,0x44,0x45,0x3A,0x00,0x00,0x00,
0x00,0x28,0x6C,0x00,0x00,0x00,0x7C,0x44,0x1C,0x64,0x44,0x45,0x3A,0x00,0x00,0x00,
0x00,0x38,0x28,0x10,0x00,0x00,0x7C,0x44,0x1C,0x64,0x44,0x45,0x3A,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x66,0x99,0x91,0x3F,0x50,0x90,0x99,0x6E,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x18,0x64,0x44,0x40,0x40,0x44,0x44,0x38,0x20,0x10,0x60,0x00,
0x00,0x00,0x00,0x10,0x10,0x00,0x3C,0x42,0x42,0x7C,0x40,0x22,0x1C,0x00,0x00,0x00,
0x00,0x00,0x04,0x08,0x08,0x00,0x3C,0x42,0x42,0x7C,0x40,0x22,0x1C,0x00,0x00,0x00,
0x00,0x00,0x18,0x38,0x44,0x00,0x3C,0x42,0x42,0x7C,0x40,0x22,0x1C,0x00,0x00,0x00,
0x00,0x00,0x2C,0x24,0x00,0x00,0x3C,0x42,0x42,0x7C,0x40,0x22,0x1C,0x00,0x00,0x00,
0x00,0x00,0x20,0x20,0x10,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,0x00,
0x00,0x00,0x08,0x10,0x10,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,0x00,
0x00,0x10,0x28,0x48,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x3C,0x00,0x00,0x00,
0x00,0x28,0x6C,0x00,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x3C,0x00,0x00,0x00,
0x00,0x00,0x24,0x18,0x28,0x04,0x3E,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,0x00,
0x00,0x30,0x1C,0x00,0x00,0x00,0x7C,0x42,0x42,0x42,0x42,0x42,0xE6,0x00,0x00,0x00,
0x00,0x00,0x00,0x10,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x66,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x0C,0x08,0x00,0x3C,0x42,0x42,0x42,0x42,0x66,0x18,0x00,0x00,0x00,
0x00,0x18,0x28,0x04,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x44,0x38,0x00,0x00,0x00,
0x00,0x30,0x1C,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x44,0x38,0x00,0x00,0x00,
0x00,0x24,0x2C,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x44,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0x00,0x1F,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x46,0x4A,0x52,0x62,0x44,0xB8,0x00,0x00,0x00,
0x00,0x00,0x00,0x10,0x00,0xC4,0x44,0x44,0x44,0x44,0x44,0x26,0x3A,0x00,0x00,0x00,
0x00,0x00,0x04,0x08,0x18,0xC4,0x44,0x44,0x44,0x44,0x44,0x26,0x3A,0x00,0x00,0x00,
0x00,0x18,0x28,0x44,0x00,0x02,0x42,0x42,0x42,0x42,0x42,0x46,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x24,0x24,0xC4,0x44,0x44,0x44,0x44,0x44,0x26,0x3A,0x00,0x00,0x00,
0x00,0x0C,0x08,0x10,0x00,0x00,0x24,0x24,0x24,0x18,0x18,0x10,0x10,0x10,0x60,0x00,
0x00,0xC0,0x40,0x40,0x40,0x5E,0x22,0x42,0x42,0x22,0x22,0x54,0x48,0x40,0x60,0x00,*/
};

/* Глобальные переменные */
//Интерфейсы SPI для коммуникации с дисплеем и тачскрином
#ifndef TFT_SOFTSPI
SPI_HandleTypeDef *_displaySPI;
SPI_HandleTypeDef *_touchSPI;
#endif

//Размеры дисплея по горизонтали и вертикали (меняются при изменении ориентации экрана)
uint16_t TFT_MAX_X = 320;
uint16_t TFT_MAX_Y = 240;
//Массив с всеми основными цветами
const uint16_t colorfol[]={TFT_COLOR_Black,TFT_COLOR_Gray,TFT_COLOR_Silver,TFT_COLOR_White,TFT_COLOR_Fuchsia,TFT_COLOR_Purple,TFT_COLOR_Red,TFT_COLOR_Maroon,TFT_COLOR_Yellow,TFT_COLOR_Orange,TFT_COLOR_Lime,TFT_COLOR_Green,TFT_COLOR_Aqua,TFT_COLOR_Teal,TFT_COLOR_Blue,TFT_COLOR_Navy};
//TODO: Хрензнайт что это, разобраться
volatile xy_t touch_xy_buffer[TOUCH_MAX_CACHE];
volatile uint8_t touch_wr_index;
volatile uint8_t touch_rd_index;
volatile uint8_t touch_counter;

//Аппаратная перезагрузка дисплея
void TFT_reset(void) {
	TFT_RESET_Reset;
	HAL_Delay(1);
	TFT_RESET_Set;
	HAL_Delay(1);
}
//Инициализация дисплея
#ifndef TFT_SOFTSPI
void TFT_init(SPI_HandleTypeDef *displaySPI) {
	_displaySPI = displaySPI;
#endif
#ifdef TFT_SOFTSPI
void TFT_init(void) {
#endif
	//Общение на шине именно с дисплеем
	TFT_CS_Reset;
	//Аппаратная перезагрузка дисплея
	TFT_reset();
	
	TFT_sendCmd(0x000,0x0001); //Запуск осциллятора
	HAL_Delay(10);
	/* Настройки питания */  	
	TFT_sendCmd(0x100, 0x0000);		//Дисплей выключен
	TFT_sendCmd(0x101, 0x0000);		//Тактирование выключено 
	TFT_sendCmd(0x102, 0x3100); 	//Настройка частот преобразователей
	TFT_sendCmd(0x103, 0xe200); 	//Настройка напряжений
	TFT_sendCmd(0x110, 0x009d);		//Настройка апмлитуд переменного напряжения матрицы 
	TFT_sendCmd(0x111, 0x0022);		//Настройка тока 
	TFT_sendCmd(0x100, 0x0120);		//Включение операционных усилителей и запуск генератора градационного напряжения
	HAL_Delay(20);
	TFT_sendCmd(0x100, 0x3120);		//Включение питания матрицы и всего остального
	HAL_Delay(80);
	/* Управление дисплеем */   
	TFT_sendCmd(0x001, 0x0100); 	//Ориентация дисплея: 0x0100 - сверху вниз, 0x0000 - снизу вверх. Можно отзеркалить изображение 	
	TFT_sendCmd(0x002, 0x0000);		//Установка формы сигнала драйвера
	TFT_sendCmd(0x003, 0x1230);		//Режим ввода
	//TODO: Команду установки ориентации дисплея
	//0xXXX0 - ввод по короткой стороне (по ширине), 0xXXX8 - по длинной (по длине)
	//0xXXnX - инкремент/декремент по длине и ширине
	TFT_sendCmd(0x006, 0x0000);		//Контроль движения изображения
	TFT_sendCmd(0x007, 0x0101);		//Выключение дисплея как такогого
	TFT_sendCmd(0x008, 0x0808);		//Настройка рамок (?)
	TFT_sendCmd(0x009, 0x0000);		//Настройка сканирования (?)
	TFT_sendCmd(0x00b, 0x0000);		//Настройка количества цветов дисплея. Переключение между 8 цветами и 262k
	TFT_sendCmd(0x00c, 0x0000);		//Настройка интерфейса RGB 
	TFT_sendCmd(0x00d, 0x0017);		//Настройка частоты обновления кадров. 0xXX10 - максимальная, 0xXX1F - минимальная частота
	/* LTPS control settings */   
	TFT_sendCmd(0x012, 0x0000);
	TFT_sendCmd(0x013, 0x0000);	
	TFT_sendCmd(0x018, 0x0000);
	TFT_sendCmd(0x019, 0x0000);

	TFT_sendCmd(0x203, 0x0000);		//Маска записи в GRAM
	TFT_sendCmd(0x204, 0x0000);		//Маска записи в GRAM
	/* Выделение активной области дисплея, в которую будут отправляться данные */
	TFT_sendCmd(0x210, 0x0000);		//Начало по горизонтали
	TFT_sendCmd(0x211, 0x00ef);		//Конец по горизонтали
	TFT_sendCmd(0x212, 0x0000);		//Начало по вертикали
	TFT_sendCmd(0x213, 0x013f);		//Конец по вертикали
	/* Выделение активной области дисплея для движущегося изображения */
	TFT_sendCmd(0x214, 0x0000);		//Начало по горизонтали
	TFT_sendCmd(0x215, 0x0000);		//Конец по горизонтали
	TFT_sendCmd(0x216, 0x0000);		//Начало по вертикали
	TFT_sendCmd(0x217, 0x0000);		//Конец по вертикали
	/* Настройка градации серого */
	TFT_sendCmd(0x300, 0x5343);
	TFT_sendCmd(0x301, 0x1021);
	TFT_sendCmd(0x302, 0x0003);
	TFT_sendCmd(0x303, 0x0011);
	TFT_sendCmd(0x304, 0x050a);
	TFT_sendCmd(0x305, 0x4342);
	TFT_sendCmd(0x306, 0x1100);
	TFT_sendCmd(0x307, 0x0003);
	TFT_sendCmd(0x308, 0x1201);
	TFT_sendCmd(0x309, 0x050a);
	/* Настройка доступа к RAM */ 
	TFT_sendCmd(0x400, 0x4027);
	TFT_sendCmd(0x401, 0x0000);
	TFT_sendCmd(0x402, 0x0000);		/* First screen drive position (1) */   	
	TFT_sendCmd(0x403, 0x013f);		/* First screen drive position (2) */   	
	TFT_sendCmd(0x404, 0x0000);
	/* Установка текущего пикселя */
	TFT_sendCmd(0x200, 0x0000);		//По горизонтали
	TFT_sendCmd(0x201, 0x0000);		//По вертикали
	
	TFT_sendCmd(0x100, 0x7120);		//Включение питания дисплея
	TFT_sendCmd(0x007, 0x0103);		//Разрешение изображения
	HAL_Delay(10);
	TFT_sendCmd(0x007, 0x0113);		//Включение ключей

	TFT_CS_Set; //Поднятие CS, т.к. общение с дисплеем закончено
}
//Очистка дисплея (залитие белым)
void TFT_fill(uint16_t color) {
	TFT_CS_Reset;	//Общение на шине именно с дисплеем

	TFT_sendCmd(0x210,0x00);
	TFT_sendCmd(0x212,0x0000);
	TFT_sendCmd(0x211,0xEF);
	TFT_sendCmd(0x213,0x013F);
	
	TFT_sendCmd(0x200,0x0000);
	TFT_sendCmd(0x201,0x0000);

	TFT_index;
	TFT_sendData(0x202);
	TFT_data;
	
	for (uint32_t i = TFT_MAX_X*TFT_MAX_Y; i != 0; i--) {
		TFT_sendData(color);
	}
	TFT_CS_Set; //Поднятие CS, т.к. общение с дисплеем закончено
}

void LCD_test(void)
{
	uint16_t  temp,num;
	uint8_t n;//i;

	TFT_CS_Reset;	

	TFT_sendCmd(0x210,0x00);
	TFT_sendCmd(0x212,0x0000);
	TFT_sendCmd(0x211,0xEF);
	TFT_sendCmd(0x213,0x013F);
	
	TFT_sendCmd(0x200,0x0000);
	TFT_sendCmd(0x201,0x0000);

	TFT_index;
	TFT_sendData(0x202);
	TFT_data;
	for(n=0;n<16;n++)
	{
	    temp=colorfol[n];
		for(num=20*240;num>0;num--)
		{
			TFT_sendData(temp);
		}
	}
/*	for(n=0;n<1;n++)
	{
		TFT_sendCmd(0x210,0x00);
		TFT_sendCmd(0x212,0x0000);
		TFT_sendCmd(0x211,0xEF);
		TFT_sendCmd(0x213,0x013F);

		TFT_sendCmd(0x200,0x0000);
		TFT_sendCmd(0x201,0x0000);
		
		TFT_index();
		TFT_sendData(0x202);
		TFT_data();
	    temp=colorfol[n];
		for(i=0;i<240;i++)
		{
			for(num=0;num<320;num++)
			{
		  		TFT_sendData(temp);
			}
		}
	//	HAL_Delay(50);
	}*/
	TFT_CS_Set;
}
//Функция отправки 16 бит данных
void TFT_sendData(uint16_t data) {
	//Буффер данных для отправки
	//Отправка данных по SPI
	#ifndef TFT_SOFTSPI
	uint8_t buff[2] = {data>>8, (uint8_t)data};
	HAL_SPI_Transmit(_displaySPI, (uint8_t *)buff, 2, 0xFF);
	#endif
	#ifdef TFT_SOFTSPI
	uint16_t mask = 32768;
	for (uint8_t i = 0; i < 16; i++) {
		(data & (mask)) ? TFT_MOSI_Set : TFT_MOSI_Reset;
		TFT_SCK_Set;
		TFT_SCK_Reset;
		mask >>= 1;
	}
	#endif
	
}
//Функция отправки команды
void TFT_sendCmd(uint16_t cmd, uint16_t data) {
	//Установка RS в режим отправки команд
	TFT_index;
	//Отправка команды
	TFT_sendData(cmd);
	//Установка RS в режим отправки данных
	TFT_data;
	//Отправка данных
	TFT_sendData(data);
}

void DisplayChar(uint8_t casc,uint8_t postion_x,uint8_t postion_y)
{
	uint8_t i,j,b;
	uint8_t *p;
	
	TFT_CS_Reset;
	TFT_sendCmd(0x210,postion_x*8); 	//x start point
	TFT_sendCmd(0x212,postion_y*16); 	//y start point
	TFT_sendCmd(0x211,postion_x*8+7);	//x end point
	TFT_sendCmd(0x213,postion_y*16+15);	//y end point
	TFT_sendCmd(0x200,postion_x*8);	
	TFT_sendCmd(0x201,postion_y*16);
	
	TFT_index;
	TFT_sendData(0x202);
	TFT_data;
	p=ascii;
	p+=casc*16;
	for(j=0;j<16;j++)
	{
		b=*(p+j);
		for(i=0;i<8;i++)
		{
			if(b&0x80)
			{
				TFT_sendData(TFT_COLOR_Black);
			}
			else
			{
				TFT_sendData(TFT_COLOR_Yellow);
			}
			b=b<<1;
			
		}	
	}
	TFT_CS_Set;
}

void DisplayChar_Reverse(uint8_t casc,uint8_t postion_x,uint8_t postion_y)
{
	uint8_t i,j,b;
	uint8_t *p;
	
	TFT_CS_Reset;
	TFT_sendCmd(0x210,postion_x*8); 	//x start point
	TFT_sendCmd(0x212,postion_y*16); 	//y start point
	TFT_sendCmd(0x211,postion_x*8+7);	//x end point
	TFT_sendCmd(0x213,postion_y*16+15);	//y end point

	TFT_sendCmd(0x200,postion_x*8);	
	TFT_sendCmd(0x201,postion_y*16);
	
	TFT_index;
	TFT_sendData(0x202);
	TFT_data;
	p=ascii;
	p+=casc*16;
	for(j=16;j>0;j--)
	{
		b=*(p+j-1);
		for(i=0;i<8;i++)
		{
			if(b&0x01)
			{
				TFT_sendData(TFT_COLOR_Black);
			}
			else
			{
				TFT_sendData(TFT_COLOR_Yellow);
			}
			b=b>>1;
			
		}	
	}
	TFT_CS_Set;
}

uint8_t* swap(uint8_t *s,uint8_t sz)
{
    uint8_t i=0;
    static uint8_t b[10]={0};
    s+=sz-2;
    for(i=0;i<sz-1;i++)
    {
        b[i]=*s;
        s--;
    }
    s=b;
    return s;
}

void DisplayString(uint8_t *s,uint8_t x,uint8_t y,uint8_t Reverse)
{
	uint8_t a[10],i;
	if(Reverse)
	{
		i=0;
		while(*s){a[i]=*s;s++;i++;}
		s=swap(a,sizeof(a));
	}
	while (*s) 
	{ 
		if(Reverse)
			{DisplayChar_Reverse(*s,x,y);}
		else
			{DisplayChar(*s,x,y);}
		if(++x>=30)
		{
			x=0;
			if(++y>=20)
			{
			  y=0;
			}
		}
		s++;
    }
}

uint16_t get_touch_data(uint16_t cmd)
{
	uint8_t buff[2];
	/*uint8_t tmp;
	SSPBUF = cmd;
	while(!SSPIF);
	SSPIF=0;

	SSPBUF = 0;
	while(!SSPIF);
	SSPIF=0;

	tmp =SSPBUF;

	SSPBUF = 0;
	while(!SSPIF);
	SSPIF=0;*/
	//HAL_SPI_Receive(_touchSPI, (uint8_t *)buff, 2, 0xFF);

	return ( ((uint16_t)buff[0])<<5 | ((uint16_t)buff[1])>>3);
}

xy_t get_touch_xy(void)
{
	xy_t tmp_xy;
	if(!PENIRQ){
		tmp_xy.x = get_touch_data(TOUCH_CMD_X);
	    tmp_xy.y = get_touch_data(TOUCH_CMD_Y);
	} else{
		tmp_xy.x = 0xFFFF;
	    tmp_xy.y = 0xFFFF;
	}
	return tmp_xy;
}

uint8_t get_point_xy(void)
{
	uint8_t n,m,tmp;
	xy_t tmp_xy_buf[SAMP_COUNT], tmp_xy;
	uint32_t tmp_x = ((uint32_t)tmp_xy_buf[SAMP_COUNT/2].x + (uint32_t)tmp_xy_buf[SAMP_COUNT/2-1].x)/2;
	uint32_t tmp_y = ((uint32_t)tmp_xy_buf[SAMP_COUNT/2].y + (uint32_t)tmp_xy_buf[SAMP_COUNT/2-1].y)/2;
	
	if(touch_counter>=(TOUCH_MAX_CACHE-1)){
		return 0;
	}
	Touch_CS_Reset;
	//xy_t tmp_xy_buf[SAMP_COUNT], tmp_xy;
	for(n=0; n<SAMP_COUNT; n++){
		tmp_xy_buf[n] = get_touch_xy();
	}
	Touch_CS_Set;
	for(n=0; n<(SAMP_COUNT-1); n++){
		for(m=0; m<(SAMP_COUNT-n-1); m++){
			tmp = m+1;
			if((tmp_xy_buf[m].x + tmp_xy_buf[m].y) > (tmp_xy_buf[tmp].x + tmp_xy_buf[tmp].y)){
				tmp_xy = tmp_xy_buf[tmp];
				tmp_xy_buf[tmp] = tmp_xy_buf[m];
				tmp_xy_buf[m] = tmp_xy;
			}
		}
	}
	if((tmp_xy_buf[SAMP_COUNT/2].x - tmp_xy_buf[SAMP_COUNT/2-1].x > SAMP_THRESHOLD) 
		|| (tmp_xy_buf[SAMP_COUNT/2].y - tmp_xy_buf[SAMP_COUNT/2-1].y > SAMP_THRESHOLD)){
		return 0;
	}

	if(tmp_x >= 0xFFF || tmp_y >= 0xFFF){
		return 0;
	}
 	touch_xy_buffer[touch_wr_index].x = ((tmp_x * 240)>>12);
	touch_xy_buffer[touch_wr_index].y = ((tmp_y * 320)>>12);
	if(touch_wr_index < (TOUCH_MAX_CACHE-1)){
		touch_wr_index++;
	}else{
		touch_wr_index = 0;
	}
	touch_counter++;
	return 1;
}

uint8_t draw_lcd(void)
{
	uint8_t n;
	TFT_CS_Reset;
	if(touch_counter==0){
		return 0;
	}
	
	touch_counter--;

	TFT_sendCmd(0x210,touch_xy_buffer[touch_rd_index].x);
	TFT_sendCmd(0x212,touch_xy_buffer[touch_rd_index].y);
	TFT_sendCmd(0x211,touch_xy_buffer[touch_rd_index].x+(DOT_WIDTH-1));
	TFT_sendCmd(0x213,touch_xy_buffer[touch_rd_index].y+(DOT_WIDTH-1));
	if(touch_rd_index < (TOUCH_MAX_CACHE-1)){
		touch_rd_index++;
	}else{
		touch_rd_index = 0;
	}
	//TFT_sendCmd(0x0005,0x0010);

	TFT_index;
	TFT_sendData(0x202);
	TFT_data;
	for(n=0; n< (DOT_WIDTH*DOT_WIDTH); n++)
	{
		TFT_sendData(TFT_COLOR_Black);
	}
	TFT_CS_Set;
	return 1;
}
/**/
