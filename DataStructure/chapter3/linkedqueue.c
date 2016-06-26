/*
	�����к���
*/
#include "LinkedQueue.h"

/*
	����������
*/
LinkedQueue *createLinkedQueue() {
	LinkedQueue *queue = (LinkedQueue *)malloc(sizeof(LinkedQueue));
	Node *node = (Node *)malloc(sizeof(Node));
	node->data = 0;
	node->next = NULL;
	queue->head = node;
	queue->rear = node;
	return queue;
}

/*
	���Ԫ�ص���β
*/
int offer(LinkedQueue *queue, Element ele) {
	if (queue == NULL) {
		return ERROR;
	}
	Node *node = (Node *)malloc(sizeof(Node));
	node->next = NULL;
	queue->rear->data = ele;
	queue->rear->next = node;
	queue->rear = node;
	return OK;
}

/*
	ȡ��ͷԪ��
*/
int element(LinkedQueue *queue) {
	if (queue == NULL || queue->head == queue->rear) {
		return ERROR;
	}
	Element result = queue->head->data;
	queue->head = queue->head->next;
	return result;
}

/*
	��ӡ������
*/
int printLinkedQueue(LinkedQueue *queue) {
	if (queue == NULL) {
		return ERROR;
	}
	while (queue->head != queue->rear) {
		printf("%d ", element(queue));
	}
	printf("\n");
	return OK;
}

/*
	���ٶ���
*/
int destoryQueue(LinkedQueue *queue) {
	if (queue != NULL) {
		Node *node = queue->head;
		Node *temp = NULL;
		while (node != NULL) {
			temp = node;
			node = node->next;
			free(temp);
		}
		free(queue);
	}
	return OK;
}

static int testLinkedQueue(void) {
	
	LinkedQueue *queue = createLinkedQueue();
	for (int i = 1; i <= 10; i++) {
		offer(queue, i);
	}

	printLinkedQueue(queue);
	destoryQueue(queue);

	getchar();
	return 0;
}