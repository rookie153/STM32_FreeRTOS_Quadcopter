#ifndef BSP_IIC_H
#define BSP_IIC_H

#include "stm32f10x.h"
#define IIC_PORT RCC_APB2Periph_GPIOB         //IIC  GPIOÊ±ÖÓÊ¹ÄÜ
#define IIC_GPIO_PORT GPIOB
#define IIC_SDA GPIO_Pin_7
#define IIC_SCL GPIO_Pin_6


#define IIC_SDA_H   IIC_GPIO_PORT->BSRR = IIC_SDA;
#define IIC_SDA_L   IIC_GPIO_PORT->BRR  = IIC_SDA;

#define IIC_SCL_H   IIC_GPIO_PORT->BSRR = IIC_SCL;
#define IIC_SCL_L   IIC_GPIO_PORT->BRR  = IIC_SCL;

#define IIC_SDA_READ (IIC_GPIO_PORT->IDR&IIC_SDA)
#define IIC_SCL_READ (IIC_GPIO_PORT->IDR&IIC_SCL)





#endif