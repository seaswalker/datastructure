//��̬����
#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"

//������󳤶�
#define SIZE 100

//���徲̬����
typedef struct {
	ElemType data;
	//��ʾ��һ��Ԫ�ص�����
	int cur;
}StaticLinkedList;

//����һ���������� �㷨2.14
StaticLinkedList* initStaticLinkedList() {
	StaticLinkedList *list = (StaticLinkedList *)malloc(SIZE * sizeof(StaticLinkedList));
	for (int i = 0; i < SIZE - 1; i++) {
		list[i].cur = (i + 1);
	}
	list[SIZE - 1].cur = NULL;
	return list;
}

//�㷨2.15 ����ؼ� ������һ����������
int mallocSLL(StaticLinkedList *list) {
	int positon = list[0].cur;
	//�ռ����þ�
	if (positon == NULL) {
		return ERROR;
	}
	list[0].cur = list[positon].cur;
	return positon;
}

//����һ���ڵ� �㷨2.16 positionΪ���յ��±�
void freeSLL(StaticLinkedList *list, int  position) {
	list[position].cur = list[0].cur;
	list[0].cur = position;
}

/*
	�㷨2.13 
	��ȡԪ�ص�λ��
*/
int getLocation(StaticLinkedList *list, int head, ElemType ele) {
	if (list == NULL) {
		return ERROR;
	}
	int position = head;
	while (position != NULL) {
		if (list[position].data == ele) {
			return position;
		}
		position = list[position].cur;
	}
	return ERROR;
}

//��ӡ
void printfSLL(StaticLinkedList *list, int head) {
	int position = head;
	while (position != NULL) {
		printf("%d ", list[position].data);
		position = list[position].cur;
	}
	printf("\n");
}

/*
	�㷨2.17 ������A��B�Ĳ���
	space �Ǳ��ÿؼ�����
*/
void joinSSL() {
	StaticLinkedList *space = initStaticLinkedList();
	//��ʾ��������ͷָ��(�±�)
	int head = 0;
	printf("����������AԪ�صĸ�����\n");
	int lengthA = 0;
	scanf_s("%d", &lengthA);
	if (lengthA < 1) return;

	//����A��Ԫ�أ�ֱ�Ӵ�������
	int position = 0;
	//��һ��Ԫ�ص��±�
	int pre = 0;
	for (int i = 1; i <= lengthA; i++) {
		printf("�������%d��Ԫ��:\n", i);
		position = mallocSLL(space);
		scanf_s("%d", &space[position].data);
		space[position].cur = NULL;
		if (i == 1) {
			head = position;
			pre = head;
		}
		else {
			space[pre].cur = position;
			pre = position;
		}
	}

	int lengthB = 0;
	printf("����������BԪ�ظ���:\n");
	scanf_s("%d", &lengthB);
	int temp = 0;
	int location = 0;
	for (int i = 1; i <= lengthB; i++) {
		printf("�������%d��Ԫ��:\n", i);
		scanf_s("%d", &temp);
		location = getLocation(space, head, temp);
		//�����Ԫ���Ѿ�����
		if (location != ERROR) {
			continue;
		}
		position = mallocSLL(space);
		space[position].data = temp;
		space[position].cur = NULL;
		space[pre].cur = position;
		pre = position;
	}

	printf("�ϲ���ɣ�������£�\n");
	printfSLL(space, head);
}

void testStaticLinkedList(void) {
	joinSSL();
	getchar();
	getchar();
}
