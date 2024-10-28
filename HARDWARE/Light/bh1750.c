#include "BH1750.h"
#include "iic.h"

void Single_Write_BH1750(char REG_Address)
{
   IIC_Start();                  //��ʼ�ź�
   IIC_Send_Byte(BHAddWrite);   //�����豸��ַ+д�ź�
   IIC_Send_Byte(REG_Address);    //�ڲ��Ĵ�����ַ
   IIC_Stop();                   //����ֹͣ�ź�
}

void BH1750_Init(void)
{
	IIC_Init();

	//Single_Write_BH1750(0x01);
	//bh_data_send(BHPowOn);  //BH1750�ϵ�
	//bh_data_send(BHReset);	//BH1750��λ
	//bh_data_send(BHModeH2); //BH1750д�����ģʽ��ѡ����Ƿֱ�����4lx������ʱ����16ms��
}

/*************************************************************************************/
void bh_data_send(u8 command)
{
    IIC_Start();                      //iic��ʼ�ź�
    IIC_Send_Byte(BHAddWrite);       //����������ַ
		IIC_Wait_Ack();
    IIC_Send_Byte(command);          //����ָ��
    IIC_Wait_Ack();                   //�ȴ��ӻ�Ӧ��
    IIC_Stop();                       //iicֹͣ�ź�
}

u16 bh_data_read(void)
{
	u16 buf;
	IIC_Start();                       //iic��ʼ�ź�
	IIC_Send_Byte(BHAddRead);         //����������ַ+����־λ
	IIC_Wait_Ack();                     //�ȴ��ӻ�Ӧ��
	buf=IIC_Read_Byte(1);              //��ȡ����
	buf=buf<<8;                        //��ȡ������߰�λ����
	buf+=0x00ff&IIC_Read_Byte(0);      //��ȡ������ڰ�λ����
	IIC_Stop();                        //����ֹͣ�ź� 
	return buf; 
}