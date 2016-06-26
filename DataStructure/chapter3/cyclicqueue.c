/*
	循环队列
*/
#include "CyclicQueue.h"

//定义最大容量
#define MAXSIZE 30

/*
	初始化一个循环队列
*/
CyclicQueue *createCyclicQueue() {
	CyclicQueue *queue = (CyclicQueue *)malloc(sizeof(CyclicQueue));
	//数据区
	ELement *data = (ELement *)malloc(MAXSIZE * sizeof(ELement));
	queue->base = data;
	queue->head = 0;
	queue->rear = 0;
	return queue;
}

/*
	向队尾插入元素
*/
static int offer(CyclicQueue *queue, ELement ele) {
	//判断为null或者是否已经满了
	if (queue == NULL || (queue->rear + 1) % MAXSIZE == queue->head) {
		return ERROR;
	}
	queue->base[queue->rear] = ele;
	queue->rear = (queue->rear + 1) % MAXSIZE;
	return OK;
}

/*
	取得队头元素
*/
static ELement element(CyclicQueue *queue) {
	if (queue == NULL || queue->head == queue->rear) {
		return ERROR;
	}
	return queue->base[queue->head++];
}

/*
	获得队列的长度
*/
static int length(CyclicQueue *queue) {
	if (queue == NULL) {
		return ERROR;
	}
	return (queue->rear - queue->head + MAXSIZE) % MAXSIZE;
}

/*
	垃圾回收
*/
static void destory(CyclicQueue *queue) {
	if (queue != NULL) {
		free(queue->base);
		free(queue);
	}
}

int printCyclicQueue(CyclicQueue *queue) {
	if (queue == NULL) {
		return ERROR;
	}
	int rear = queue->rear;
	for (int i = queue->head; i < rear; i++) {
		printf("%d ", element(queue));
	} 
	printf("\n");
}

static int testCyclicQueue(void) {
	CyclicQueue *queue = createCyclicQueue();
	//会有29个元素，因为此种检查满的算法会浪费一个空间
	for (int i = 1; i <= 31; i++) {
		offer(queue, i);
	}

	printf("队列长度为:%d\n", length(queue));

	printCyclicQueue(queue);
	destory(queue);

	getchar();
	return 0;
}
