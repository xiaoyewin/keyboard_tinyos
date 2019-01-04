
//��ʼд����
//1,��дһ��LED�ĳ���
//2,���������ж��̵߳��л�
//3,дһ������������

//����ʱ�����ǲ���ϵͳ


#include "tinyOS.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "keyboard.h"
#include "timer.h"
#include "rtc.h"
#include "tsensor.h"
#include "adc.h"
#include "ds18b20.h"

unsigned char first_key_value=0;  //0����û�м�����
unsigned char second_key_value=0;  //0����û�м�����
unsigned char send_key_value=0;
unsigned char riqi_info[6];
char key_down_flag;		  //���±��
char key_up_flag;	       //�ɿ����
int key_count;//�����Ĵ�����
int  g_count;   //

u16 g_tem_value;

short g_temperature=0;  //pb9


//���ڲ�оƬ���²��е��������DS18B20оƬ

void send_string_uart1(char *s,int length)
{
	
	if(length<1)
	{
		return;
	}
	else{
		for(int i=0;i<length;i++)
		{
			 while(1)
			 {
				 if((USART1->SR&0x40)==0x40)   //�������
				 {
						USART1->DR =s[i]; 
					 break;
				 }

			 }	
				 
		}
	}


}
 int main(void)
 {		
		delay_init();	    	 //��ʱ������ʼ�� ��Ҫ��������systick ��Ƶ�ʣ���ʱ��Դ
	  keyboard_init();  	//��Ҫ����ģʽ���ٶ�
	  DS18B20_Init();
	 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2     Ƕ���жϿ�����  2λ��ռ���ȼ�  2λ�����ȼ�   
          
	 
	 
	 RecvStartFlag=0;
		g_count=0;
	 //�������ڿ�����Ϊ���ԵĹ���   ��������������Ե�
	 uart1_init(9600);	 //���ڳ�ʼ��Ϊ15200
	 
	//�����25ms��һ��,   ����һ����ʱ��
 // ��Ҫ���ǳ���
 //��ʱ��1s�����£��¶ȣ�GPS, AD��ѹֵ��������һ���ض��ĸ�ʽ�Ϳ�����
	 
	 	 //��ADʵ�����¶ȼ��   ��AD�ĵ�ѹ������
	 T_Adc_Init();	//��ʼ���¶ȵ�ģ��
	 Adc_Init();  //ADCģ��ĳ�ʼ��
	 //��ʱ�����     //��������Ϊ 20ms       50HZ    
	 TIM3_Int_Init(199,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms       7200   10K         �õ��Ƕ�ʱ��3     //���������Ķ�ʱ����ʱ��=pclk1/psc =36000/3600   //��λ��K   ��λ��0.1ms
	 //Ӧ�õ�����һ����ʱ��ʹ��λ������Ҫô�������

	 g_tem_value=0;
	 
	 //ʵ����RTCʱ��
	 
	 while(RTC_Init())		//RTC��ʼ��	��һ��Ҫ��ʼ���ɹ�
	 { 

			delay_ms(800);
	 }		 
	 
	 	//�������ȡ�¶�
	 while(DS18B20_Init())	//DS18B20��ʼ��  	
	{
 		delay_ms(200);
	}			
	 
	//	printf("\r\nRTC2\r\n");
	 int t,len,times;
	 
	
	 int i=0;
	 unsigned char temp_uchar;

	 	while(1)
	{
		
		if(USART_RX_STA&0x8000)   //  ��ʾ�нڵ��ż   ��ʾ���յ�������
		{	
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			USART_RX_STA=0;  
			if(len>=6)
			{
				 //��ʵ����г�ͻ�ģ�������������
				for(int i=0;i<6;i++)
				{
						riqi_info[i]=USART_RX_BUF[i];
				}
				if((riqi_info[5]>=0)&&(riqi_info[5]<100))
				{
						 if((riqi_info[4]>=0)&&(riqi_info[4]<=12))
						{
							if((riqi_info[3]>=0)&&(riqi_info[3]<=31))
							{
							   	if((riqi_info[2]>=0)&&(riqi_info[2]<=24))
									{
							       	if((riqi_info[1]>=0)&&(riqi_info[1]<=60))
											{
												if((riqi_info[0]>=0)&&(riqi_info[0]<=60))
												{
																		
													//Ȼ���������������;
													RTC_Set(riqi_info[5]+2000,riqi_info[4],riqi_info[3],riqi_info[2],riqi_info[1],riqi_info[0]);
												}
											}
									}
							}
						}
				}

				
			}	
		}
	
		delay_ms(100);
		g_temperature=DS18B20_Get_Temp();	
	  delay_ms(100);   
}
}
 
 
 
 
 void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 

		//�����ﴦ�����   //�͵�ƽ��ʾ����
			
			char key_value[2];
//			char key_value[2];
//			char key_value[2];
			char temp_key1=0x0;
//			temp_value1[0]=0x10;
//			 temp_value1[1]=0x12;
//			 printf("%s",temp_value1);

	
		//��Ҫ����P0����ͬʱ��ס2������
			
 

		 //��2������һ���ˣ��Ͳ�������    �Ȳ��ÿ��Ƕ������һ��
		 if(KEY_F1==0)
		 {
			 temp_key1=0x8; 
		 }
		 
		 if(KEY_F2==0)
		 {
			 temp_key1=0x7; 
		 }
		 
		 if(KEY_F3==0)
		 {
			 temp_key1=0x6; 
		 }
		 
		 if(KEY_F4==0)
		 {
			 temp_key1=0x5; 
		 }
		 
		 if(KEY_F5==0)
		 {
			 temp_key1=0x4; 
		 }
		 
		 if(KEY_F6==0)
		 {
			 temp_key1=0x3; 
		 }
		 
		 if(KEY_PLUS==0)
		 {
			 temp_key1=0x2; 
		 }
		 
		 if(KEY_MINUS==0)
		 {
			 temp_key1=0x16; 
		 }
		 
		 if(KEY_CONFIRM==0)
		 {
			 temp_key1=0x1; 
		 }
		 
		 if(KEY_EXIT==0)
		 {
			 temp_key1=0x15; 
		 }
		 
		 if(KEY_UP==0)
		 {
			 temp_key1=0x12; 
		 }
		 
		 if(KEY_DOWN==0)
		 {
			 temp_key1=0x11; 
		 }
		 
		 
		 if(KEY_AB==0)
		 {
			 temp_key1=0x14; 
		 }
		 if(KEY_REPLAY==0)
		 {
			 temp_key1=0x13; 
		 }
		 if(KEY_DAC==0)
		 {
			 temp_key1=0x17; 
		 }
		 
		 	if(KEY_FLAG==0)
		 {
			 temp_key1=0x18; 
		 }
		 

		 if(temp_key1>0)  //˵���м�������
		{
			if(KEY_CONVERT==0)
		  {
			  temp_key1|=0x20;
		  }
		}
		
		
				 	//��ʾ֮ǰ�а�������   //F1-F6����ÿһ�����һ��  ����B�����棬ÿһ�����10��
		if(key_down_flag==1)
		{
			if(temp_key1==first_key_value)   //���ֵ��������һ��ֵ
			{
					key_count++;    //�����ﻹҪ���ǳ���   ����ֻ��һ�Σ�������Щ��û�а�����Ϣ
					if(key_count>16)
					{
						if(key_count%8==0)
						{
							if((temp_key1>=3)&&(temp_key1<=8))	//ֻ��F1-F6�г���
							{	
								if(key_count==32)      //ֻ��F1-F6 �г���
								{
										key_value[0]=0xf1;
										key_value[1]=(temp_key1|0x40);
										send_string_uart1(key_value,2);

								}
							}
							else
							{	 
									  key_value[0]=0xf1;
										key_value[1]=temp_key1;
										send_string_uart1(key_value,2);
//								 �����������
							}
						}
				 }
			}
			else
			{
					if(temp_key1==0)   //��ʾ��Ч  //����������ʱû�õ�
					{
						if(key_count>=32)
						{
							key_down_flag=0;
							key_count=0;		
						}
						else
						{
							second_key_value=first_key_value;
							key_up_flag=1;   //��ʾ�����ɿ�����.
						}	
					}
					else    //���¿�ʼ
					{
						first_key_value=temp_key1;
						key_count=0;
					}
					key_count=0;
				}
		}
		else
		{
			if(temp_key1>0)
			{
				first_key_value=temp_key1;
				key_down_flag=1;
				key_count=0;
			}
		}
		 
	
		if(key_down_flag&key_up_flag)
		{
			if(second_key_value!=0)
			{  
					key_down_flag=0;
					key_up_flag=0;
				 key_value[0]=0xf1;
				 key_value[1]=second_key_value;
				 send_string_uart1(key_value,2);
			}
		}
		
		
		//g_tem_value=T_Get_Adc_Average(ADC_CH_TEMP,1); //�����AD ��ֵ
		
		g_tem_value=Get_Adc_Average(ADC_Channel_1,10);
		float temp1;
		short temp2;
		//	send_data_uart2(g_count);
	//F0 ��������Ϣ��FLAG,.���¶ȣ���ѹ//0:flag,1����ѹ��2,3: �¶�   4,5,GPS ,X   6,7  GPS  Y
	if(g_count==50)	   //1s
	{
		g_count=0;
//		send_data_uart2(0xF0);
//		send_data_uart2(g_adc_value);
//		send_data_uart2((g_temperature>>8)&0xff);
//		send_data_uart2(g_temperature&0xff);
//    	send_data_uart2(0);
//		send_data_uart2(0);
//	    send_data_uart2(0);
//		send_data_uart2(0);
		
	
	//	temp1=(float)g_tem_value*(3.3/4096);
 		//temp1=(1.43-temp1)/0.0043+25;		//�������ǰ�¶�ֵ	   //�����ʱ���ùܣ���������֤�� 

	//	g_tem_value=(short)temp1;
  //  һ����20k  һ�� 4.7      3* ��24.7/4.7��
		g_tem_value  =  (g_tem_value*157.66)/4095;     //���Ҫ������   
		char otherinfo_value[8];
		otherinfo_value[0]=0xF0;
		otherinfo_value[1]=0x12;
		otherinfo_value[2]=((g_temperature>>8)&0xff);
		otherinfo_value[3]=(g_temperature&0xff);
		otherinfo_value[4]=0x0;
		otherinfo_value[5]=0x0;
		otherinfo_value[6]=0x0;
		otherinfo_value[7]=0x0;

		send_string_uart1(otherinfo_value,8);
	   //14BYTE
		
		send_key_value=0;
	}
	else if(g_count==25)
	{
		g_count=26;
	char riqi_value[7];
	
	riqi_value[0]=0xF2;
	riqi_value[1]=calendar.sec;
	riqi_value[2]=calendar.min;
	riqi_value[3]=calendar.hour;
	riqi_value[4]=calendar.w_date;
	riqi_value[5]=calendar.w_month;
	riqi_value[6]=(calendar.w_year-2000);

	send_string_uart1(riqi_value,7);
	// printf("%s",riqi_value);     //printf() ���������ʱ��ʱ�����0XE0  ��֪����ʲô��˼
	}
	else
	{	
		g_count++;

	}
		
			
			
		
			
			//printf("\r\n�����͵�Ϊ=%d:\r\n",g_tem_value);
			
		}
}


//RTCʱ���ж�
//ÿ�봥��һ��  
//extern u16 tcnt; 
void RTC_IRQHandler(void)
{		 
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)//�����ж�
	{							
		RTC_Get();//����ʱ��   
 	}

	if(RTC_GetITStatus(RTC_IT_ALR)!= RESET)//�����ж�
	{
		RTC_ClearITPendingBit(RTC_IT_ALR);		//�������ж�	  	   
  	} 				  								 
	RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);		//�������ж�
	RTC_WaitForLastTask();	  	    						 	   	 
}
 




 
