#include "bsp_iic.h"
static void i2c_Delay(void)
{
	uint8_t i;

	/*　
	 	下面的时间是通过逻辑分析仪测试得到的。
    工作条件：CPU主频72MHz ，MDK编译环境，1级优化
  
		循环次数为10时，SCL频率 = 205KHz 
		循环次数为7时，SCL频率 = 347KHz， SCL高电平时间1.5us，SCL低电平时间2.87us 
	 	循环次数为5时，SCL频率 = 421KHz， SCL高电平时间1.25us，SCL低电平时间2.375us 
	*/
	for (i = 0; i < 5; i++);
}

void i2c_Start()
{
	IIC_SDA_H;
	IIC_SCL_H;
	i2c_Delay();
	IIC_SDA_L;
	i2c_Delay();
	IIC_SCL_L;
	i2c_Delay();
}

void i2c_Stop()
{
	IIC_SCL_L;
	IIC_SDA_L;
	i2c_Delay();
	IIC_SCL_H;
	i2c_Delay();
	IIC_SDA_H;
	
}
void i2c_SendByte(uint8_t byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		if(byte&0x80) 
        {
		    IIC_SDA_H;
		}
		else 
        {
			IIC_SDA_L;
		}	
		i2c_Delay();
		
		IIC_SCL_H;
		i2c_Delay();
		IIC_SCL_L;
		
		byte<<=1;
		i2c_Delay();	
	}
	
}

uint8_t i2c_ReadByte()
{
	uint8_t i;
    uint8_t value=0;
	
	for(i=0;i<8;i++)
	{
		value <<=1;
		IIC_SCL_H;
		i2c_Delay();
		if(IIC_SDA_READ)
		{
			value |=0x01;
		}
		IIC_SCL_L;
		i2c_Delay();	
	}
	return value; 
	
}
uint8_t i2c_WaitAck() //主机产生时钟信号   等待应答  返回1为正确应答  否则器件无响应
{
	uint8_t t;
	IIC_SDA_H;
	i2c_Delay();
	IIC_SCL_H;
	i2c_Delay();
	if(IIC_SDA_READ)
	{
		t=1;
	}
	else
    {
		t=0;
	}
	IIC_SCL_L;
	i2c_Delay();
	return t;	
}
void i2c_Ack()   //主机产生应答
{
	IIC_SDA_L;
	i2c_Delay();
	IIC_SCL_H;
	i2c_Delay();
	IIC_SCL_L;
	i2c_Delay();
	IIC_SDA_H;    //释放总线
	
}
void i2c_NAck() //主机不产生应答
{
	IIC_SDA_H;
	i2c_Delay();
	IIC_SCL_H;
	i2c_Delay();
	IIC_SCL_L;
	i2c_Delay();
	
}
void i2c_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(IIC_PORT,ENABLE);
	GPIO_InitStructure.GPIO_Pin = IIC_SDA|IIC_SCL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(IIC_GPIO_PORT,&GPIO_InitStructure);

}