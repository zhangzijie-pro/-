#include "pwm.h"

void PWM_init_servo(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);                       //����TIM3��ʱ����ʱ��
	
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);                     //PC6����ΪTIM3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);   
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	
	// 84MHz /8400/200 = 50Hz = 20ms
	TIM_TimBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimBaseStruct.TIM_Period = 200-1;		// ARR
	TIM_TimBaseStruct.TIM_Prescaler = 8400 - 1;		// PSC
	TIM_TimBaseStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimBaseStruct);
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_Pulse = 0;  // ��ʼ����
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	
	TIM_OC2Init(TIM3, &TIM_OCInitStruct);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_OC3Init(TIM3, &TIM_OCInitStruct);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	//TIM_ARRPreloadConfig(TIM3,ENABLE);                                        //ʹ��TIM4��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM3, ENABLE);                                                    //TIM4ʹ��
	
	TIM_CtrlPWMOutputs(TIM3, ENABLE);                                         //ʹ�������
}


void PWM_set_up(int value)
{
	TIM_SetCompare1(TIM3,value);
}

void PWM_set_down(int value)
{
	TIM_SetCompare2(TIM3,value);
}

void PWM_set_door(int value)
{
	TIM_SetCompare3(TIM3,value);
}

// Ƶ�� = CLK/ (PSC+1)/(ARR+1)
// ռ�ձ�=CCR/(ARR+1)
// �ֱ���=1/(ARR+1)

