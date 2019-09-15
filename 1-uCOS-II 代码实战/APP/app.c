#include "includes.h"

	
OS_STK task_led2_stk[TASK_A_STK_SIZE];		  //定义栈
OS_STK task_led3_stk[TASK_B_STK_SIZE];
OS_STK task_C_stk[STK_SIZE];
OS_STK task_status_stk[Status_STK_SIZE];
OS_EVENT *Semp;		//启动信号量

OS_EVENT *S;		//共享资源信号量
char *s;					//共享资源

void Task_Start(void *p_arg)
{
		INT8U count = 0;				//计数器
		INT8U err;
		Semp = OSSemCreate(0);	//获取信号量
		S = OSSemCreate(1);
	
  (void)p_arg;                							// 'p_arg' 并没有用到，防止编译器提示警告
	OSTaskCreate(Task_A,(void *)0, &task_led2_stk[TASK_A_STK_SIZE-1], TASK_A_PRIO);//创建任务2
	//printf("\r\nA start !\r\n");

	OSTaskCreate(Task_B,(void *)0, &task_led3_stk[TASK_B_STK_SIZE-1], TASK_B_PRIO);	//创建任务3
	//printf("B start !\r\n");
	
	OSTaskCreate(Task_C,(void *)0, &task_C_stk[STK_SIZE-1], TASK_C_PRIO);//创建任务3
	//printf("status start !\r\n");
	
	OSTaskCreate(status,(void *)0, &task_status_stk[Status_STK_SIZE-1], TASK_status_PRIO);//创建任务3
	//printf("status start !\r\n");

    while (1)
    {
				OSSemPend(S,0,&err);//获取共享资源
				sprintf(s,"Task_Start:\r\n%d, main\r\n",count);
				printf(s);
				OSSemPost(S);
			
			  count++;
			  
			  if(count==50){
					
					OSSemPost(Semp);	//启动任务C
					printf("Task_Start:启动任务C\r\n");
				}
				
				if(count==500){
					
					//关闭任务C，使得Semp信号量不可访问
					printf("Task_Start:关闭任务C\r\n");
				}
				
        OSTimeDlyHMSM(0, 0,0,100);
    }
}


//任务A   A 可以 挂起和杀死 B
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

//任务B
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

//任务C   在主任务中，设置启动时间
void Task_C(void *p_arg){
	INT8U err;
	
	OSSemPend(Semp,0,&err);//来自主任务的启动指令
		OSSemPend(S,0,&err);//获取共享资源
		sprintf(s, "C: start\r\n");
		printf(s);
		OSSemPost(S);
	OSSemPost(Semp);
	
}

void status(void *p_arg){
	OS_TCB *B = OSTCBPrioTbl[TASK_B_PRIO];
	OS_TCB *A = OSTCBPrioTbl[TASK_A_PRIO];
	
	while (1)
	{

		printf("status:OS_time=%d", OSTime);
		printf("status:B: %d-%d-%d\r\n",B->OSTCBStat,\
		B->OSTCBPrio,B->OSTCBDelReq);	//显示任务B的基本状态
		printf("status:A: %d-%d-%d\r\n",A->OSTCBStat,\
		A->OSTCBPrio,A->OSTCBDelReq);	//显示任务B的基本状态
			
		 OSTimeDlyHMSM(0, 0,0,100);
	}
}
