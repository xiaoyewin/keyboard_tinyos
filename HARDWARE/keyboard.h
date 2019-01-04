#ifndef __KEYBOARD_H
#define __KEYBOARD_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 


#define KEY_F1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//读取按键F1   PB1
#define KEY_F2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键F2   PC5
#define KEY_F3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//读取按键F3     PA7
#define KEY_F4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//读取按键F4   PA5
#define KEY_F5  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//读取按键F5      PB0
#define KEY_F6  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)//读取按键F6    PC4

#define KEY_PLUS  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//读取按键+    PA6
#define KEY_MINUS  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)//读取按键-   PC8
#define KEY_CONFIRM  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//读取按键确认   PA4
#define KEY_EXIT  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//读取按键退出    PA8
#define KEY_UP  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)//读取按键上     PC7
#define KEY_DOWN  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//读取按键下  PC9
#define KEY_CONVERT  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//读取按键键转换  PB12
#define KEY_AB  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//读取按键AB     PB13
#define KEY_REPLAY  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//读取按键回放  PB15
#define KEY_DAC GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)//读取按键DAC   PC6
#define KEY_FLAG GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//读取按键flag  PB14


#define TESTPIN PAout(1)	// PA1


void keyboard_init(void);//初始化

		 				    
#endif
