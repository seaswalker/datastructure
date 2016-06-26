//һԪ����ʽ
#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"

//���¶���Item��������
typedef struct {
	//ϵ��
	float coef;
	//ָ��
	int expn;
} Item;

typedef struct {
	Item *data;
	struct PolynNode *next;
} PolynNode;

PolynNode *createPolynNode() {
	PolynNode *node = (PolynNode *)malloc(sizeof(PolynNode));
	node->data = NULL;
	node->next = NULL;
	return node;
}

Item *createItem() {
	Item *ele = (Item *)malloc(sizeof(Item));
	ele->coef = 0.0;
	ele->expn = 0;
	return ele;
}

/*
	�����û����봴������ʽ����
	�㷨2.22
*/
PolynNode *createPolyn() {
	printf("���������ʽ������:\n");
	int n = 0;
	PolynNode *head = createPolynNode();
	//λ��ָ��
	PolynNode *cur = head;
	PolynNode *temp = NULL;
	Item *ele = NULL;
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		temp = createPolynNode();
		ele = createItem();
		printf("�������%d���ϵ��:\n", i + 1);
		scanf_s("%f", &ele->coef);
		printf("�������%d���ָ��:\n", i + 1);
		scanf_s("%d", &ele->expn);
		temp->data = ele;
		cur->next = temp;
		cur = temp;
	}
	return head;
}

void printPolyn(PolynNode *list) {
	PolynNode *node = list ? list->next : NULL;
	if (node == NULL) {
		printf("������Ķ���ʽΪ��\n");
		return;
	}
	//��ǵ�һ��
	int flag = TRUE;
	float coef = 0.0;
	while (node != NULL) {
		coef = node->data->coef;
		if (flag) {
			printf("%.2fx(^%d)", coef, node->data->expn);
			flag = FALSE;
		}
		else {
			printf(" + %.2fx(^%d)", coef, node->data->expn);
		}
		node = node->next;
	}
	printf("\n");
}

/*
	����ָ��
	�Ӷ���ʽ�в��ң��ҵ�������Ӧ�Ľڵ�
	û�ҵ�����NULL
*/
PolynNode *findPolyn(PolynNode *list, int expn) {
	PolynNode *node = list ? list->next : NULL;
	if (node == NULL) {
		return NULL;
	}
	while (node != NULL) {
		if (node->data->expn == expn) {
			return node;
		}
		node = node->next;
	}
	return NULL;
}

/*
	��ö���ʽ������
*/
int polynLength(PolynNode *list) {
	PolynNode *node = list ? list->next : NULL;
	if (node == NULL) {
		return 0;
	}
	int counter = 0;
	while (node != NULL) {
		counter++;
		node = node->next;
	}
	return counter;
}

//���뺯��
int insertPolyn(PolynNode *list, PolynNode *ele, int index) {
	if (list == NULL || index < 1) {
		return ERROR;
	}
	int counter = 1;
	PolynNode *node = list->next;
	PolynNode *previous = list;
	while (node != NULL && counter < index) {
		previous = node;
		node = node->next;
		counter++;
	}
	//���index > ���� + 1
	if (counter < index - 1) {
		return ERROR;
	}
	//����ָ��
	previous->next = ele;
	ele->next = NULL;
	return OK;
}


/*
	����ʽ��ӣ����������A
	�㷨2.23
*/
int addPolyn(PolynNode *A, PolynNode *B) {
	if (A == NULL || B == NULL) {
		return ERROR;
	}
	PolynNode *pB = B->next;
	PolynNode *result = NULL;
	PolynNode *position = NULL;
	int length = 0;
	while (pB != NULL) {
		result = findPolyn(A, pB->data->expn);
		position = pB->next;
		//A�к��д���
		if (result != NULL) {
			result->data->coef += pB->data->coef;
		}
		else {
			length = polynLength(A);
			//���뵽���һ��
			insertPolyn(A, pB, length + 1);
		}
		pB = position;
	}
	free(B);
	return OK;
}

int testPolyn(void) {
	PolynNode *A = createPolyn();
	printPolyn(A);

	PolynNode *B = createPolyn();
	printPolyn(B);

	addPolyn(A, B);
	printPolyn(A);

	getchar();
	getchar();
	return 0;
}