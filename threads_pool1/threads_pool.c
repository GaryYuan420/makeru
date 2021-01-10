#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef void (* WorkFunc_PF)(long , void *);

typedef struct WorkInfo
{
	WorkFunc_PF pfWork;//挂接的执行函数
	void *arg;//执行函数
	struct WorkInfo *next;
}WorkInfo_s;

typedef struct tagThreadPool
{
	int uiThreadNumber; //线程数目
	pthread_t *pstThreadID; //线程ID数组
	WorkInfo_s *pstWorkQueueHead; //工作任务链表
	pthread_mutex_t stQueueLock;
	pthread_cond_t stQueueReady;
}ThreadPool_S;

int IdleThread = 0;

ThreadPool_S *g_ThreadPool;

void *ThreadRoutine(void* arg)
{
	long uiThreadCount = (long)arg;
	long uiThreadId = pthread_self();
	WorkInfo_s *WorkInfo;
	pthread_detach(uiThreadId);
	for(;;)
	{
		IdleThread++;
		pthread_mutex_lock(&g_ThreadPool->stQueueLock);
		while(g_ThreadPool->pstWorkQueueHead == NULL)
			(void)pthread_cond_wait(&g_ThreadPool->stQueueReady, &g_ThreadPool->stQueueLock);
		WorkInfo = g_ThreadPool->pstWorkQueueHead;
		g_ThreadPool->pstWorkQueueHead =  g_ThreadPool->pstWorkQueueHead->next;
		pthread_mutex_unlock(&g_ThreadPool->stQueueLock);
		WorkInfo->pfWork(uiThreadId, WorkInfo->arg);
		IdleThread--;
		free(WorkInfo);
	}
	
	return;
}


int ThreadPool_Init(int uiThreadNum)
{
	long uiThreadCount;
	g_ThreadPool = calloc(1, sizeof(ThreadPool_S));
	g_ThreadPool->uiThreadNumber = uiThreadNum;
	g_ThreadPool->pstWorkQueueHead = NULL;
	pthread_mutex_init(&g_ThreadPool->stQueueLock, NULL);
	pthread_cond_init(&g_ThreadPool->stQueueReady, NULL);
	g_ThreadPool->pstThreadID = calloc(uiThreadNum, sizeof(pthread_t));
	for(uiThreadCount = 0; uiThreadCount < uiThreadNum; uiThreadCount++)
	{
		pthread_create(&g_ThreadPool->pstThreadID[uiThreadCount], NULL, ThreadRoutine, (void*)uiThreadCount);
	}
	return 0;
}


int ThreadPool_AddWork(WorkFunc_PF workfunc, void *arg)
{
	WorkInfo_s *work = NULL;
	WorkInfo_s *work_tmp = NULL;
	work = calloc(1, sizeof(WorkInfo_s));
	work->pfWork = workfunc;
	work->arg = arg;
	work->next = NULL;
	pthread_mutex_lock(&g_ThreadPool->stQueueLock);
	work_tmp = g_ThreadPool->pstWorkQueueHead;
	if(NULL != work_tmp)
	{
		while(work_tmp->next != NULL)
			work_tmp = work_tmp->next;
		work_tmp->next = work;
	}
	else
		g_ThreadPool->pstWorkQueueHead = work;
	while(IdleThread <= 0);
	pthread_mutex_unlock(&g_ThreadPool->stQueueLock);
	pthread_cond_signal(&g_ThreadPool->stQueueReady);
	
	return 0;
}

void ThreadPool_Exit(void)
{
	WorkInfo_s *work_tmp;
	printf("EXIT!\n");
	pthread_mutex_lock(&g_ThreadPool->stQueueLock);
	while(g_ThreadPool->pstWorkQueueHead != NULL)
	{
		work_tmp = g_ThreadPool->pstWorkQueueHead;
		g_ThreadPool->pstWorkQueueHead = g_ThreadPool->pstWorkQueueHead->next;
		free(work_tmp);
	}
	pthread_mutex_unlock(&g_ThreadPool->stQueueLock);
	free(g_ThreadPool->pstThreadID);
	pthread_cond_destroy(&g_ThreadPool->stQueueReady);
	pthread_mutex_destroy(&g_ThreadPool->stQueueLock);
	free(g_ThreadPool);
	g_ThreadPool = NULL;
	return;
}

void work_printf(long ThreadId, void *arg)
{
	printf("work_printf ThreadId is %ld, arg is %ld\n", ThreadId & 0xfffff, (long)arg);
	return;
}

int main()
{
	int CpuNum = 5;//sysconf(_SC_NPROCESSORS_CONF);
	ThreadPool_Init(CpuNum);
	sleep(1);
	long arg = 1;
	while(arg < 100)
	{	
		ThreadPool_AddWork(work_printf, (void *)arg);
		arg++;
	}
	sleep(2);
	sync();
	ThreadPool_Exit();
	return 0;
}