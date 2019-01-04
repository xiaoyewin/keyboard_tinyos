

#include "keyboard.h"



//键盘的初始化
void keyboard_init(void)
{
	
	//输入默认上拉输入
	
 GPIO_InitTypeDef  GPIO_InitStructure;   //这个是GPIO口的结构体
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA,PB,PC端口时钟   开启相应端口的时钟
	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 //KEY1   PA4
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉输入
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //KEY2   PA5
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //KEY3   PA6
  GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //KEY4   PA7
  GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	    		 //KEY5   PC4
  GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //KEY6   PC5
  GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //KEY7   PB0
  GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //KEY8   PB1
  GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	    		 //KEY9   PB12
  GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	    		 //KEY10   PB13
  GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	    		 //KEY11   PB14
  GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	    		 //KEY12   PB15
  GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //KEY13   PC6
  GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //KEY14   PC7
  GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //KEY15   PC8
  GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	    		 //KEY16   PC9
  GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //KEY16   PA8
  GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 // ，IO口速度为50MHz
	
	
	//这个是测试用的
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //KEY1   PA1
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //开漏输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
}

