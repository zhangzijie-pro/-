#ifndef __gpio_in_H
#define __gpio_in_H
#include "sys.h"

// �����Ӧ
#define HUMAN_EXIST GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)

void Human_Init(void);

// ��μ��  0����   1û��
#define RAIN_EXIST	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)
void Rain_Init(void);

// ������
#define FIRE_EXIST	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)
void fire_Init(void);

#endif
