/*
* LinearList.c
* �������������Ա�
*  Created on: 2015��3��19��
*      Author: skywalker
*/

#include <stdio.h>
#include <stdlib.h>
#include  "datastructure.h"

//���������ʼ����
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

//��ʼ�������������ش����Ա��ָ��
List* initList() {
	List *list = (List*)malloc(sizeof(List));
	list->ele = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	list->length = 0;
	list->listsize = LIST_INIT_SIZE;
	return list;
}

//������������
int destory(List *list) {
	if (list == NULL) {
		return ERROR;
	}
	free(list);
	return OK;
}

//������Ա�
int clearList(List *list) {
	if (list == NULL) {
		return ERROR;
	}
	list->ele = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	list->length = 0;
	list->listsize = LIST_INIT_SIZE;
	return OK;
}

//�жϸ������±��Ƿ�Խ��
int isOutofBound(List *list, int index) {
	if (list != NULL) {
		return (index < 1 || index > list->length);
	}
	return ERROR;
}

//�ж����Ա��Ƿ�Ϊ��
int isEmpty(List *list) {
	return list == NULL || list->length == 0;
}

//�������Ա�ĳ���
int length(List *list) {
	if (list == NULL) {
		return 0;
	}
	return list->length;
}

//���ص�i��Ԫ��
ElemType getItem(List *list, int i) {
	//�ж��Ƿ�Խ�磬�ڼ�����Ӧ�±� i - 1
	if (list == NULL || isOutofBound(list, i)) {
		return ERROR;
	}
	return list->ele[i - 1];
}

//�Ƚ�����ElemTypeԪ�صĴ�С
int compare(ElemType e1, ElemType e2) {
	return e1 - e2;
}

//�ҵ�����Ԫ�ص��±�ֵ
int locate(List *list, ElemType e, int(*compare)()) {
	if (list == NULL) {
		return ERROR;
	}
	for (int i = 0; i < list->length; i++) {
		if ((*compare) (list->ele[i], e) == 0) {
			return (i + 1);
		}
	}
	//û���ҵ�
	return ERROR;
}

//���ظ���Ԫ�ص���һ��Ԫ��
ElemType priorEle(List *list, ElemType e, int(*compare)()) {
	if (list == NULL) {
		return ERROR;
	}
	for (int i = 0; i < list->length; i++) {
		if ((*compare) (list->ele[i], e) == 0) {
			if (i == 0) {
				return ERROR;
			}
			return list->ele[i - 1];
		}
	}
	return ERROR;
}

//���ظ���Ԫ�ص���һ��Ԫ��
ElemType nextEle(List *list, ElemType e, int(*compare)()) {
	if (list == NULL) {
		return ERROR;
	}
	for (int i = 0; i < list->length; i++) {
		if ((*compare) (list->ele[i], e) == 0) {
			if (i == list->length - 1) {
				return ERROR;
			}
			return list->ele[i + 1];
		}
	}
	return ERROR;
}

//�ڸ�����λ�ò���һ���µ�Ԫ�أ�������1��ʼ
int insert(List *list, ElemType e, int index) {
	if (list == NULL || index < 1 || index > list->length + 1) {
		return ERROR;
	}
	//����û���þ�
	if (list->length < list->listsize) {
		list->length++;
		//�����Ԫ��ȫ������һ����λ
		for (int i = list->length; i >= index - 1; i--) {
			list->ele[i + 1] = list->ele[i];
		}
		list->ele[index - 1] = e;
	}
	else {
		index--;
		//��������þ�������
		list->listsize += LISTINCREMENT;
		ElemType *newEle = (ElemType*)malloc(list->listsize * sizeof(ElemType));
		for (int i = 0; i < index; i++) {
			newEle[i] = list->ele[i];
		}
		newEle[index] = e;
		for (int i = index; i < list->length; i++) {
			newEle[index + 1] = list->ele[i];
		}
		free(list->ele);
		list->ele = newEle;
		list->length++;
	}
	return OK;
}

//ɾ������λ�õ�Ԫ�أ����ر�ɾ����Ԫ��
ElemType deleteItem(List *list, int index) {
	if (isEmpty(list) || isOutofBound(list, index)) {
		return ERROR;
	}
	ElemType old = list->ele[index - 1];
	//ɾ�������һ��Ԫ�ز���Ҫ���⴦����Ϊ������ͨ��length������
	for (int i = index; i < list->length; i++) {
		list->ele[i - 1] = list->ele[i];
	}
	list->length--;
	return old;
}

//����
void traverse(List *list) {
	if (isEmpty(list)) {
		return;
	}
	for (int i = 0; i < list->length; i++) {
		printf("��%d��Ԫ��  ", i + 1);
	}
}

//���Ը������������list
void fill(List *list, int limit) {
	for (int i = 1; i <= limit; i++) {
		list->ele[i - 1] = rand() % 100;
	}
	list->length = limit;
}

//����������Ա�
void printfList(List *list) {
	for (int i = 0; i < list->length; i++) {
		printf("%d ", list->ele[i]);
	}
	printf("\n");
}

void testLinearList() {
	ElemType result = 0;
	char *resultStr;
	ElemType element = 0;

	List *list = initList();
	int count = 0;
	printf("��������Ҫ���Ԫ�صĸ���:\n");
	scanf_s("%d", &count);
	fill(list, count);
	printf("���Ա�������:\n");
	printfList(list);

	//�����жϳ��纯��
	int position = 0;
	while (TRUE) {
		printf("�������ж�Խ���λ��(��1��ʼ������-1����):\n");
		scanf_s("%d", &position);
		if (position == -1) {
			break;
		}
		result = isOutofBound(list, position);
		resultStr = result == ERROR ? "����" : (result ? "Խ��" : "��Խ��");
		printf("%s\n", resultStr);
	}

	//����length����
	int length = list->length;
	printf("list�ĳ�����%d\n", length);

	//����getItem()����
	while (TRUE) {
		printf("����getItem�������������ȡԪ�ص��±�(����-1����):\n");
		scanf_s("%d", &position);
		if (position == -1) {
			break;
		}
		result = getItem(list, position);
		if (result == ERROR) {
			printf("��������±�Խ�磬����������");
			continue;
		}
		printf("��%d��Ԫ����%d\n", position, result);
	}

	//���Զ�λ����
	while (TRUE) {
		printf("��������Ҫ��λ��Ԫ��(-1����):\n");
		scanf_s("%d", &element);
		if (element == -1) {
			break;
		}
		result = locate(list, element, compare);
		if (result == ERROR) {
			printf("û�д�Ԫ��\n");
			continue;
		}
		printf("��Ҫ�ҵ�Ԫ���ǵ�%d��Ԫ��\n", result);
	}

	//������һ������
	while (TRUE) {
		printf("������һ��Ԫ��(-1����):\n");
		scanf_s("%d", &element);
		if (element == -1) {
			break;
		}
		element = priorEle(list, element, compare);
		if (element == ERROR) {
			printf("û�д�Ԫ��\n");
			continue;
		}
		printf("��һ��Ԫ����%d\n", element);
	}

	//������һ������
	while (TRUE) {
		printf("������һ��Ԫ��(-1����):\n");
		scanf_s("%d", &element);
		if (element == -1) {
			break;
		}
		element = nextEle(list, element, compare);
		if (element == ERROR) {
			printf("û�д�Ԫ��\n");
			continue;
		}
		printf("��һ��Ԫ����%d\n", element);
	}

	//����insert����
	while (TRUE) {
		printf("���Բ����Ԫ��(-1����):\n");
		scanf_s("%d", &element);
		if (element == -1) {
			break;
		}
		printf("�����λ��:\n");
		scanf_s("%d", &position);
		result = insert(list, element, position);
		if (result == ERROR) {
			printf("λ�÷Ƿ�\n");
			continue;
		}
		printf("����ɹ��������Ա�Ϊ\n");
		printfList(list);
	}

	//����ɾ������
	while (TRUE) {
		printf("ɾ����λ��(��1��ʼ-1����):\n");
		scanf_s("%d", &position);
		if (position == -1) {
			break;
		}
		result = deleteItem(list, position);
		if (result == ERROR) {
			printf("û�д�Ԫ��\n");
			continue;
		}
		printf("ɾ���ɹ��������Ա�Ϊ\n");
		printfList(list);
	}

	getchar();
	getchar();
}
