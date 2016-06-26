/*
	ѭ������
*/
#include "CyclicQueue.h"

//�����������
#define MAXSIZE 30

/*
	��ʼ��һ��ѭ������
*/
CyclicQueue *createCyclicQueue() {
	CyclicQueue *queue = (CyclicQueue *)malloc(sizeof(CyclicQueue));
	//������
	ELement *data = (ELement *)malloc(MAXSIZE * sizeof(ELement));
	queue->base = data;
	queue->head = 0;
	queue->rear = 0;
	return queue;
}

/*
	���β����Ԫ��
*/
static int offer(CyclicQueue *queue, ELement ele) {
	//�ж�Ϊnull�����Ƿ��Ѿ�����
	if (queue == NULL || (queue->rear + 1) % MAXSIZE == queue->head) {
		return ERROR;
	}
	queue->base[queue->rear] = ele;
	queue->rear = (queue->rear + 1) % MAXSIZE;
	return OK;
}

/*
	ȡ�ö�ͷԪ��
*/
static ELement element(CyclicQueue *queue) {
	if (queue == NULL || queue->head == queue->rear) {
		return ERROR;
	}
	return queue->base[queue->head++];
}

/*
	��ö��еĳ���
*/
static int length(CyclicQueue *queue) {
	if (queue == NULL) {
		return ERROR;
	}
	return (queue->rear - queue->head + MAXSIZE) % MAXSIZE;
}

/*
	��������
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
	//����29��Ԫ�أ���Ϊ���ּ�������㷨���˷�һ���ռ�
	for (int i = 1; i <= 31; i++) {
		offer(queue, i);
	}

	printf("���г���Ϊ:%d\n", length(queue));

	printCyclicQueue(queue);
	destory(queue);

	getchar();
	return 0;
}
