#ifndef LED_H
#define LED_H

#include "stm32f10x.h"

void LED_Init(void);
#define LED_ON    GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define LED_OFF   GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#endif
