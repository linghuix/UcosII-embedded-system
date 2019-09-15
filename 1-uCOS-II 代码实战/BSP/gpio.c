/**
  ******************************************************************************
  * @file    delay.c
  * @author  Linghui Xu
  * @version V1.0
  * @date    2019.4.27
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  * @attention
  * 1. 本程序主要存放引脚的配置，针对GPIO以及其他复用功能TIME，ADC，USART，CAN...
  * 2. “事件控制”，“重映射”，“调试IO配置”，“外部中断”，时需要开启AFIO
  *
  ******************************************************************************
  */
#include "gpio.h"

void GPIO_Config(void){

    GPIO_InitTypeDef GPIO_InitStructure;


/** @addtogroup GPIOA 配置
  * @{
  */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);                //添加PA口时钟线

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  



    /*********串口GPIO端口配置***********/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                           /* 配置串口1 （USART1 Tx (PA.09)）*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                          /* 配置串口1 USART1 Rx (PA.10)*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*********串口GPIO端口配置END*********/


}

