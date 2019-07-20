#include "includes.h"

OS_STK task_led2_stk[TASK_A_STK_SIZE];		  //定义栈
OS_STK task_led3_stk[TASK_B_STK_SIZE];		  //定义栈

void Task_Start(void *p_arg)
{
    (void)p_arg;                							// 'p_arg' 并没有用到，防止编译器提示警告

	OSTaskCreate(Task_A,(void *)0,		  			//创建任务2
	   &task_led2_stk[TASK_A_STK_SIZE-1], TASK_A_PRIO);

	OSTaskCreate(Task_B,(void *)0,		   			//创建任务3
	   &task_led3_stk[TASK_B_STK_SIZE-1], TASK_B_PRIO);

    while (1)
    {
				printf("C");
        OSTimeDlyHMSM(0, 0,0,100);;
   
    }
}


//任务2
void Task_A(void *p_arg)
{
    (void)p_arg;                	
	
    while (1)
    {
     printf("A");
			
     OSTimeDlyHMSM(0, 0,0,2);
    }
}

//任务3
void Task_B(void *p_arg)
{
    (void)p_arg;      
	
    while (1)
    {
     printf("B");
			
     OSTimeDlyHMSM(0, 0,0,2);
    }
}
