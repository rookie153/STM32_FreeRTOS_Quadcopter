#include "led.h"
void LED_Init(void)	
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	AFIO->MAPR = 0X02000000; //ʹ��4����д �ͷ�ĳЩ����д��ص�����
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  , ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;		     //LED12
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}
