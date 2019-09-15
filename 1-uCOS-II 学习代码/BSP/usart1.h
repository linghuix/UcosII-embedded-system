#ifndef __USART1_H
#define	__USART1_H


#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include <stdio.h>



/*****************  function declaration 函数声明********************************************/

void USART1_Config(void);
void USART1_NVIC_Configuration(void);



/**
  * @attention
  *     使用如下函数，需要定义MICRO-LIB宏
  */
int fputc(int ch, FILE *f);
int fgetc(FILE *f);


#endif /* __USART1_H */
