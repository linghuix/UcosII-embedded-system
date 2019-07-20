#include "includes.h"

OS_STK task_led2_stk[TASK_A_STK_SIZE];		  //定义栈
OS_STK task_led3_stk[TASK_B_STK_SIZE];
OS_STK task_status_stk[Status_STK_SIZE];

void Task_Start(void *p_arg)
{
		INT8U count = 0;
    (void)p_arg;                							// 'p_arg' 并没有用到，防止编译器提示警告

	OSTaskCreate(Task_A,(void *)0,		  			//创建任务2
	   &task_led2_stk[TASK_A_STK_SIZE-1], TASK_A_PRIO);
	//printf("\r\nA start !\r\n");

	OSTaskCreate(Task_B,(void *)0,		   			//创建任务3
	   &task_led3_stk[TASK_B_STK_SIZE-1], TASK_B_PRIO);
	//printf("B start !\r\n");
	
	OSTaskCreate(status,(void *)0,		   			//创建任务3
	   &task_status_stk[Status_STK_SIZE-1], 6);
	//printf("B start !\r\n");

    while (1)
    {
				printf("\r\n%d, main C\r\n",count);
        OSTimeDlyHMSM(0, 0,0,100);
			  count++;
   
    }
}


//任务2
void Task_A(void *p_arg)
{
		INT8U count = 0;
    (void)p_arg;  
	
    while (1)
    {
     printf("%d A\r\n",count);
			
			if(count==20) {
				OSTaskSuspend(TASK_B_PRIO);
				printf("Suspend B\r\n");
			}
			else if(count==40)
			{
				OSTaskResume(TASK_B_PRIO);
				printf("rescure B\r\n");
			}
			else if(count==100)
			{
				while(OSTaskDelReq(TASK_B_PRIO)==OS_ERR_TASK_NOT_EXIST||OSTaskDelReq(TASK_B_PRIO)==OS_ERR_TASK_DEL);
				printf("Kill B\r\n");
			}
			
			count++;
     OSTimeDlyHMSM(0, 0,0,100);
    }
}

//任务3
void Task_B(void *p_arg)
{
    (void)p_arg;      
	
    while (1)
    {
			if(OSTaskDelReq (OS_PRIO_SELF)==OS_ERR_TASK_DEL_REQ){
				printf("B: I have to kill myself");
				OSTaskDel(OS_PRIO_SELF);
				printf("I am dead");																			//此句无法输出，因为B已经死了
				
			}
			 printf("B\r\n");
				
			 OSTimeDlyHMSM(0, 0,0,100);
    }
}

void status(void *p_arg){
	OS_TCB *B = OSTCBPrioTbl[TASK_B_PRIO];
	OS_TCB *A = OSTCBPrioTbl[TASK_A_PRIO];
	
	while (1)
	{

		printf("status:B: %d-%d-%d\r\n",B->OSTCBStat,\
		B->OSTCBPrio,B->OSTCBDelReq);	//显示任务B的基本状态
		printf("status:A: %d-%d-%d\r\n",A->OSTCBStat,\
		A->OSTCBPrio,A->OSTCBDelReq);	//显示任务B的基本状态
			
		 OSTimeDlyHMSM(0, 0,0,100);
	}
	
}
