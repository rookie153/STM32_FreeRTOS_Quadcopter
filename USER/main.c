#include<stm32f10x.h>
void delay()
{
	unsigned int a=12000;
	int b=500;
	for(;b>0;b--)for(a=12000;a>0;a--);
	

}

void LEDInit(void)	
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	AFIO->MAPR = 0X02000000; //使能4线烧写 释放某些与烧写相关的引脚
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  , ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;		     //LED12
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}
int  main()
{
	LEDInit();
	while(1)
	{		
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
		delay();
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		delay();
	};
	return 0;

}
