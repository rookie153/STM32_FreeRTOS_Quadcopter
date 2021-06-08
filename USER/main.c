#include "FreeRTOS.h"
#include "task.h"
#include "stm32f10x.h"
#include "led.h"

static TaskHandle_t Start_Task_Handle=NULL;
static TaskHandle_t Led_Task_Handle=NULL;
static void LED_Task(void* parameter);

void delay()  //�����ʱ500ms��
{
	unsigned int a=12000;
	int b=500;
	for(;b>0;b--)for(a=12000;a>0;a--);
	

}

static void Start_Task(void* parameter)
{
	taskENTER_CRITICAL();
	xTaskCreate(  LED_Task,     //������ں���
	              "LED_Task",    //��������
	               100,          //����ջ��С
	              NULL,          //������ں�������
	              1,             //���ȼ�
	               &Led_Task_Handle //���   ������ƿ�ָ��
	             );
	vTaskDelete(Start_Task_Handle);
	taskEXIT_CRITICAL();
}
static void LED_Task(void* parameter)
{
	while(1)
	{
		LED_ON;
		vTaskDelay(500);
		LED_OFF;
		vTaskDelay(500);      
	}
}

void BSP_Iint(void)
{
    NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
    LED_Init();
	USART_Config();
}
int main(void)
{
    BSP_Iint();
	xTaskCreate(Start_Task,"Start_Task",100,NULL,2,&Start_Task_Handle);
	vTaskStartScheduler();
	while(1);
}
