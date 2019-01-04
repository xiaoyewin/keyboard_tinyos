
//开始写程序
//1,先写一个LED的程序
//2,接下来进行多线程的切换
//3,写一个按键检测程序

//先暂时不考虑操作系统


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

unsigned char first_key_value=0;  //0就是没有键按下
unsigned char second_key_value=0;  //0就是没有键按下
unsigned char send_key_value=0;
unsigned char riqi_info[6];
char key_down_flag;		  //按下标记
char key_up_flag;	       //松开标记
int key_count;//按键的次数，
int  g_count;   //

u16 g_tem_value;

short g_temperature=0;  //pb9


//你内部芯片的温差有点大，所以用DS18B20芯片

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
				 if((USART1->SR&0x40)==0x40)   //发送完成
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
		delay_init();	    	 //延时函数初始化 主要用来设置systick 的频率，等时钟源
	  keyboard_init();  	//主要设置模式和速度
	  DS18B20_Init();
	 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2     嵌套中断控制器  2位抢占优先级  2位子优先级   
          
	 
	 
	 RecvStartFlag=0;
		g_count=0;
	 //串口现在可以作为调试的工具   这个串口用作调试的
	 uart1_init(9600);	 //串口初始化为15200
	 
	//这个用25ms做一次,   设置一个定时器
 // 还要考虑长按
 //定时器1s传递下，温度，GPS, AD电压值，倒是以一个特定的格式就可以了
	 
	 	 //用AD实验下温度检测   和AD的电压的输入
	 T_Adc_Init();	//初始化温度的模块
	 Adc_Init();  //ADC模块的初始化
	 //定时器这块     //触发周期为 20ms       50HZ    
	 TIM3_Int_Init(199,7199);//10Khz的计数频率，计数到5000为500ms       7200   10K         用的是定时器3     //换算下来的定时器的时钟=pclk1/psc =36000/3600   //单位是K   单位是0.1ms
	 //应该单独加一个定时器使能位，才行要么放在最后

	 g_tem_value=0;
	 
	 //实验下RTC时钟
	 
	 while(RTC_Init())		//RTC初始化	，一定要初始化成功
	 { 

			delay_ms(800);
	 }		 
	 
	 	//在这里获取温度
	 while(DS18B20_Init())	//DS18B20初始化  	
	{
 		delay_ms(200);
	}			
	 
	//	printf("\r\nRTC2\r\n");
	 int t,len,times;
	 
	
	 int i=0;
	 unsigned char temp_uchar;

	 	while(1)
	{
		
		if(USART_RX_STA&0x8000)   //  表示有节点哈偶   表示接收到了数据
		{	
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			USART_RX_STA=0;  
			if(len>=6)
			{
				 //其实这个有冲突的，会设置有问题
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
																		
													//然后在这里进行设置;
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
 
 
 
 
 void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 

		//在这里处理键盘   //低电平表示按下
			
			char key_value[2];
//			char key_value[2];
//			char key_value[2];
			char temp_key1=0x0;
//			temp_value1[0]=0x10;
//			 temp_value1[1]=0x12;
//			 printf("%s",temp_value1);

	
		//还要考虑P0还会同时按住2个按键
			
 

		 //有2个按键一起按了，就不起作用    先不用考虑多个按键一起按
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
		 

		 if(temp_key1>0)  //说明有键按下了
		{
			if(KEY_CONVERT==0)
		  {
			  temp_key1|=0x20;
		  }
		}
		
		
				 	//表示之前有按键按下   //F1-F6长按每一秒进行一次  ，在B超界面，每一秒进行10次
		if(key_down_flag==1)
		{
			if(temp_key1==first_key_value)   //这个值还等于上一个值
			{
					key_count++;    //在这里还要考虑长按   长按只有一次，超过这些就没有按键信息
					if(key_count>16)
					{
						if(key_count%8==0)
						{
							if((temp_key1>=3)&&(temp_key1<=8))	//只有F1-F6有长按
							{	
								if(key_count==32)      //只有F1-F6 有长按
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
//								 这个是连续按
							}
						}
				 }
			}
			else
			{
					if(temp_key1==0)   //表示有效  //长按的落下时没用的
					{
						if(key_count>=32)
						{
							key_down_flag=0;
							key_count=0;		
						}
						else
						{
							second_key_value=first_key_value;
							key_up_flag=1;   //表示按键松开来了.
						}	
					}
					else    //从新开始
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
		
		
		//g_tem_value=T_Get_Adc_Average(ADC_CH_TEMP,1); //这个是AD 的值
		
		g_tem_value=Get_Adc_Average(ADC_Channel_1,10);
		float temp1;
		short temp2;
		//	send_data_uart2(g_count);
	//F0 是其他信息的FLAG,.有温度，电压//0:flag,1；电压，2,3: 温度   4,5,GPS ,X   6,7  GPS  Y
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
 		//temp1=(1.43-temp1)/0.0043+25;		//计算出当前温度值	   //这个暂时不用管，等明天验证下 

	//	g_tem_value=(short)temp1;
  //  一个是20k  一个 4.7      3* （24.7/4.7）
		g_tem_value  =  (g_tem_value*157.66)/4095;     //这个要测试下   
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
	// printf("%s",riqi_value);     //printf() 这个函数会时不时的输出0XE0  不知道是什么意思
	}
	else
	{	
		g_count++;

	}
		
			
			
		
			
			//printf("\r\n您发送的为=%d:\r\n",g_tem_value);
			
		}
}


//RTC时钟中断
//每秒触发一次  
//extern u16 tcnt; 
void RTC_IRQHandler(void)
{		 
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)//秒钟中断
	{							
		RTC_Get();//更新时间   
 	}

	if(RTC_GetITStatus(RTC_IT_ALR)!= RESET)//闹钟中断
	{
		RTC_ClearITPendingBit(RTC_IT_ALR);		//清闹钟中断	  	   
  	} 				  								 
	RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);		//清闹钟中断
	RTC_WaitForLastTask();	  	    						 	   	 
}
 




 
