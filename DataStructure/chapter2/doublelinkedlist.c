//˫������
#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"

//��ʼ��һ��˫������ͷ���
DuLNode *createDLN() {
	DuLNode *head = (DuLNode *)malloc(sizeof(DuLNode));
	head->data = 0;
	head->next = NULL;
	head->pre = NULL;
	return head;
}

/*
	�������
	�㷨 2.18
*/
int insertDLN(DuLNode *list, ElemType ele, int index) {
	if (list == NULL || index < 1) {
		return ERROR;
	}
	int counter = 1;
	DuLNode *node = list->next;
	DuLNode *previous = list;
	while (node != NULL && counter < index) {
		previous = node;
		node = node->next;
		counter++;
	}
	//���index > ���� + 1
	if (counter < index - 1) {
		return ERROR;
	}
	DuLNode *newNode = createDLN();
	newNode->data = ele;

	//����ָ��
	previous->next = newNode;
	newNode->pre = previous;
	if (node != NULL) {
		newNode->next = node;
		node->pre = newNode;
	}
	return OK;
}

/*
	�ڵ�ɾ��
	�㷨2.19
*/
int deleteDLN(DuLNode *list, int index) {
	if (list == NULL || index < 1) {
		return ERROR;
	}
	DuLNode *previous = list;
	DuLNode *node = list->next;
	int counter = 1;
	while (node != NULL && counter < index) {
		previous = node;
		node = node->next;
		counter++;
	}
	if (counter < index) {
		return ERROR;
	}
	previous->next = node->next;
	if (node->next != NULL) {
		node->next->pre = previous;
	}
	return OK;
}

//������ӡ˫������
void printDLN(DuLNode *list) {
	if (list == NULL) {
		printf("�����������Ϊ��\n");
		return;
	}
	DuLNode *node = list->next;
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");
}

int testDLN(void) {
	DuLNode *list = createDLN();
	for (int i = 1; i < 5; i++) {
		insertDLN(list, i, i);
	}

	//insertDLN(list, 10, 5);

	deleteDLN(list, 1);
	printDLN(list);
	getchar();
	return 0;
}