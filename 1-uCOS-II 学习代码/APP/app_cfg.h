#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__


/*******************设置任务优先级*******************/
#define STARTUP_TASK_PRIO       4	   
#define	TASK_A_PRIO							5
#define	TASK_status_PRIO				6 
#define	TASK_B_PRIO							7 
#define	TASK_C_PRIO							8 


/************设置栈大小（单位为 OS_STK ）************/
#define STARTUP_TASK_STK_SIZE   80   
#define	TASK_A_STK_SIZE		80
#define	TASK_B_STK_SIZE		80
#define	Status_STK_SIZE		80
#define	STK_SIZE					80
#endif

