/*
*========================================================================================================
*
* File                : LCD_22.C
* Hardware Environment: STM32F446
* Build Environment   : Keil uVision 5
* Version             : 1.0
* By                  : Victor Nikitchuk & WaveShare Indian programmers
*
*	�������� �� ������� ��� Open16F877A. https://www.waveshare.com/wiki/File:Open16F877A-Demo.7z
*
*========================================================================================================
*/

#ifndef LCD_22_H
#define LCD_22_H

#include "main.h"
/* ������� �������������� � ������� �����/������ */
//������ ����������� ������ �� ���� ���������� �� ���������
#define PENIRQ						(HAL_GPIO_ReadPin(T_IRQ_GPIO_Port, T_IRQ_Pin) == GPIO_PIN_SET)
//���������/�������� ����������� ������ CS ���������
#define Touch_CS_Reset		HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_RESET)
#define Touch_CS_Set			HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_SET)
//���������/�������� ����������� ������ ����� ������ �������
#define TFT_RESET_Reset		HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_RESET)  
#define TFT_RESET_Set			HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_SET)
//���������/�������� ����������� ������ CS �������
#define TFT_CS_Reset			HAL_GPIO_WritePin(D_CS_GPIO_Port, D_CS_Pin, GPIO_PIN_RESET)
#define TFT_CS_Set				HAL_GPIO_WritePin(D_CS_GPIO_Port, D_CS_Pin, GPIO_PIN_SET)
//�������� ������/������� � �������
#define TFT_data					HAL_GPIO_WritePin(D_RS_GPIO_Port, D_RS_Pin, GPIO_PIN_SET)
#define TFT_index					HAL_GPIO_WritePin(D_RS_GPIO_Port, D_RS_Pin, GPIO_PIN_RESET)

//TODO: ����������� ��� �� �������
#define SAMP_COUNT				5
#define SAMP_THRESHOLD		5

#define TOUCH_CMD_X 		0xD0
#define TOUCH_CMD_Y 		0x90
/* ����� */
//TODO: ������ ������
#define COLOR_YELLOW 		0xFFE0
#define COLOR_BLACK 		0x0000
#define COLOR_WHITE 		0xFFFF
#define COLOR_INIT 			COLOR_YELLOW

#define DOT_WIDTH 4
//��������� ��� ��������� ������� �� �������� 
typedef struct xy {
	uint16_t x;
	uint16_t y;
} xy_t;

#define TOUCH_MAX_CACHE 8
/* ������� ������ � �������� */
//���������� ������������ �������
void TFT_reset(void);
//������������� �������
void TFT_init(SPI_HandleTypeDef *_displaySPI);
//������� ������� (������� �����)
void TFT_clear(void);
/* ������� ������ � ���������� */





//������ �����
void post_data(uint16_t data);
void post_cmd(uint16_t index, uint16_t cmd);
/**/
uint16_t get_touch_data(uint16_t cmd);
xy_t get_touch_xy(void);
uint8_t get_point_xy(void);
uint8_t draw_lcd(void);
void init_lcd(void);

void LCD_test(void);

#endif
