#include "gpio_in.h"
 
// �������
void Human_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);	 	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 	//��ʼ������Ϊ����״̬ 
 GPIO_Init(GPIOB, &GPIO_InitStructure);				
	
 GPIO_ResetBits(GPIOB,GPIO_Pin_9);
}

// ��μ��
void Rain_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);	 	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 	//��ʼ������Ϊ����״̬ 
 GPIO_Init(GPIOB, &GPIO_InitStructure);				
	
 //GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}


// ������
void fire_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);	 	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 	//��ʼ������Ϊ����״̬ 
 GPIO_Init(GPIOB, &GPIO_InitStructure);				
	
 GPIO_ResetBits(GPIOB,GPIO_Pin_7);
}