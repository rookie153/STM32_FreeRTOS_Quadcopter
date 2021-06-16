#include "bsp_iic.h"
static void i2c_Delay(void)
{
	uint8_t i;

	/*��
	 	�����ʱ����ͨ���߼������ǲ��Եõ��ġ�
    ����������CPU��Ƶ72MHz ��MDK���뻷����1���Ż�
  
		ѭ������Ϊ10ʱ��SCLƵ�� = 205KHz 
		ѭ������Ϊ7ʱ��SCLƵ�� = 347KHz�� SCL�ߵ�ƽʱ��1.5us��SCL�͵�ƽʱ��2.87us 
	 	ѭ������Ϊ5ʱ��SCLƵ�� = 421KHz�� SCL�ߵ�ƽʱ��1.25us��SCL�͵�ƽʱ��2.375us 
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
uint8_t i2c_WaitAck() //��������ʱ���ź�   �ȴ�Ӧ��  ����1Ϊ��ȷӦ��  ������������Ӧ
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
void i2c_Ack()   //��������Ӧ��
{
	IIC_SDA_L;
	i2c_Delay();
	IIC_SCL_H;
	i2c_Delay();
	IIC_SCL_L;
	i2c_Delay();
	IIC_SDA_H;    //�ͷ�����
	
}
void i2c_NAck() //����������Ӧ��
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