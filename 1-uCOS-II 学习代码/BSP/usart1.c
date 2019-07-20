/**
  ******************************************************************************
  * @file    delay.c
  * @author  Linghui Xu
  * @version V1.0
  * @date    2019.4.27
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
	

#include "usart1.h"
#include <stdarg.h>

/**
  * @brief  串口1的中断配置
  * @param  None
  * @retval None
  */
void USART1_NVIC_Configuration(void){

    NVIC_InitTypeDef NVIC_InitStructure;

    /*设置NVIC中断分组2:2位抢占优先级，2位响应优先级*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	

    /*TIM3中断*/
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 

    /*先占优先级0级*/	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 

    /*从优先级3级*/	
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 

    /*IRQ通道被使能*/	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 

    /*根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器*/
    NVIC_Init(&NVIC_InitStructure);  
}


/**
  * @brief  USART1 GPIO 配置,工作模式配置。115200 8-N-1
  * @param  None
  * @retval None
  */
void USART1_Config(void){
    
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* 串口1工作模式（USART1 mode）配置 */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure); 

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                  //开启接收中断

    USART_Cmd(USART1, ENABLE);                                      //使能串口

    //USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);                  //USART1向DMA发出Tx请求，此时CPU是空闲的,,在主程序中配置
}


/**
  * @brief  重定向c库函数printf到USART1,由printf调用
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f){
    
    USART_SendData(USART1, (unsigned char) ch);                     /* 将Printf内容发往串口 */
    while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
    return (ch);
}


/**
  * @brief  ：重定向c库函数scanf到USART1, 由scanf调用
  * @param  None
  * @retval None
  */
int fgetc(FILE *f){

    while( USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);     //等待串口输入数据
    return (int) USART_ReceiveData(USART1);
}
