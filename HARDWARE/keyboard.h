#ifndef __KEYBOARD_H
#define __KEYBOARD_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 


#define KEY_F1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//��ȡ����F1   PB1
#define KEY_F2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//��ȡ����F2   PC5
#define KEY_F3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//��ȡ����F3     PA7
#define KEY_F4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//��ȡ����F4   PA5
#define KEY_F5  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//��ȡ����F5      PB0
#define KEY_F6  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)//��ȡ����F6    PC4

#define KEY_PLUS  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//��ȡ����+    PA6
#define KEY_MINUS  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)//��ȡ����-   PC8
#define KEY_CONFIRM  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//��ȡ����ȷ��   PA4
#define KEY_EXIT  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//��ȡ�����˳�    PA8
#define KEY_UP  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)//��ȡ������     PC7
#define KEY_DOWN  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//��ȡ������  PC9
#define KEY_CONVERT  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//��ȡ������ת��  PB12
#define KEY_AB  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//��ȡ����AB     PB13
#define KEY_REPLAY  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//��ȡ�����ط�  PB15
#define KEY_DAC GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)//��ȡ����DAC   PC6
#define KEY_FLAG GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//��ȡ����flag  PB14


#define TESTPIN PAout(1)	// PA1


void keyboard_init(void);//��ʼ��

		 				    
#endif
