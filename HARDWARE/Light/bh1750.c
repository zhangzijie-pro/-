#include "bh1750.h"

//iic�ӿڳ�ʼ��

/**
**  ����SDAΪ���
**/
void SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructer;
    GPIO_InitStructer.GPIO_Pin= BH1750_SDA_GPIO_PIN;
    GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructer.GPIO_Mode=GPIO_Mode_OUT;
		GPIO_InitStructer.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(BH1750_GPIO_PORT, &GPIO_InitStructer);
}


/**
**  ����SDAΪ����
**/
void SDA_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStructer;
    GPIO_InitStructer.GPIO_Pin= BH1750_SDA_GPIO_PIN;
    GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IN;
		GPIO_InitStructer.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(BH1750_GPIO_PORT, &GPIO_InitStructer);
}


void Single_Write_BH1750(uchar REG_Address)
{
   BH1750_IIC_Start();                  //��ʼ�ź�
   BH1750_IIC_Send_Byte(BHAddWrite);   //�����豸��ַ+д�ź�
   BH1750_IIC_Send_Byte(REG_Address);    //�ڲ��Ĵ�����ַ��
  //  BH1750_SendByte(REG_data); 	//�ڲ��Ĵ������ݣ�
   BH1750_IIC_Stop();                   //����ֹͣ�ź�
}

void BH1750_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(BH1750_GPIO_CLK, ENABLE);	 //ʹ��A�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = BH1750_SCL_GPIO_PIN|BH1750_SDA_GPIO_PIN;	 
 	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(BH1750_GPIO_PORT, &GPIO_InitStructure);
 	GPIO_SetBits(BH1750_GPIO_PORT,BH1750_SCL_GPIO_PIN|BH1750_SDA_GPIO_PIN);	

	//Single_Write_BH1750(0x01);
	bh_data_send(BHPowOn);  //BH1750�ϵ�
	bh_data_send(BHReset);	//BH1750��λ
	//bh_data_send(BHModeH2); //BH1750д�����ģʽ��ѡ����Ƿֱ�����4lx������ʱ����16ms��
}

//����IIC��ʼ�ź�
void BH1750_IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void BH1750_IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t BH1750_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			BH1750_IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void BH1750_IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//������ACKӦ��		    
void BH1750_IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void BH1750_IIC_Send_Byte(u8 txd)
{                        
	uint8_t t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t BH1750_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        BH1750_IIC_NAck();//����nACK
    else
        BH1750_IIC_Ack(); //����ACK   
    return receive;
}

/*************************************************************************************/
void bh_data_send(u8 command)
{
    do{
    BH1750_IIC_Start();                      //iic��ʼ�ź�
    BH1750_IIC_Send_Byte(BHAddWrite);       //����������ַ
    }while(BH1750_IIC_Wait_Ack());           //�ȴ��ӻ�Ӧ��
    BH1750_IIC_Send_Byte(command);          //����ָ��
    BH1750_IIC_Wait_Ack();                   //�ȴ��ӻ�Ӧ��
    BH1750_IIC_Stop();                       //iicֹͣ�ź�
}

uint16_t bh_data_read(void)
{
	uint16_t buf;
	BH1750_IIC_Start();                       //iic��ʼ�ź�
	BH1750_IIC_Send_Byte(BHAddRead);         //����������ַ+����־λ
	BH1750_IIC_Wait_Ack();                     //�ȴ��ӻ�Ӧ��
	buf=BH1750_IIC_Read_Byte(1);              //��ȡ����
	buf=buf<<8;                        //��ȡ������߰�λ����
	buf+=0x00ff&BH1750_IIC_Read_Byte(0);      //��ȡ������ڰ�λ����
	BH1750_IIC_Stop();                        //����ֹͣ�ź� 
	return buf; 
}


