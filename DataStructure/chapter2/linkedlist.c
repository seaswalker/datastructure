//����
#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"

//������������ӡ����
void printfLNode(LNode *list) {
	LNode *node = list->next;
	if (node == NULL) {
		return;
	}
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");
}

//����һ������(������ͷ�ڵ�)
LNode* createLNode() {
	LNode *head = (LNode *)malloc(sizeof(LNode));
	head->next = NULL;
}

//����һ���ڵ㣬λ�ô�1��ʼ,29ҳ�㷨2.9
int insertLinkedList(LNode * list, ElemType eleType, int index) {
	if (index < 1) return ERROR;
	//��־����¼�Ƿ��ҵ�
	int isFound = FALSE;
	//��Ҫ��ͷָ�뿪ʼ
	LNode *p = list->next;
	//�������һ��ͷ���
	if (p == NULL) {
		if (index > 1) {
			return ERROR;
		}
		LNode *node = (LNode *)malloc(sizeof(LNode));
		node->data = eleType;
		node->next = NULL;
		list->next = node;
		return OK;
	}
	LNode *pre = list;
	int counter = 1;
	while (p != NULL) {
		if (counter == index) {
			isFound = TRUE;
			break;
		}
		counter++;
		pre = p;
		p = p->next;
	}
	if (!isFound && index > counter + 1) {
		return ERROR;
	}
	LNode *node = (LNode *)malloc(sizeof(LNode));
	node->data = eleType;
	pre->next = node;
	node->next = p;
	return OK;
}

//��ȡ�ض�λ�õ�Ԫ��(��1��ʼ) �㷨2.8
ElemType getItemFromLinkedList(LNode *list, int index) {
	LNode *p = list->next;
	//ֻ��ͷ���
	if (p == NULL) {
		return ERROR;
	}
	int counter = 1;
	while (p != NULL) {
		if (counter == index) {
			return p->data;
		}
		counter++;
		p = p->next;
	}
	return ERROR;
}

//�㷨2.10 ɾ���ض�λ�õĽڵ㣬��ɾ����Ԫ�طŵ�ele��
int deleteFromLinkedList(LNode *list, int index, ElemType *ele) {
	LNode *p = list->next;
	if (p == NULL || index < 1) {
		return ERROR;
	}
	LNode *pre = list;
	int counter = 1;
	int isFound = FALSE;
	while (p != NULL) {
		if (counter == index) {
			isFound = TRUE;
			break;
		}
		counter++;
		pre = p;
		p = p->next;
	}
	if (!isFound) {
		return ERROR;
	}
	*ele = p->data;
	pre->next = p->next;
	free(p);
	return OK;
}

//�ϲ������Ѿ���С�����ź�������� �㷨2.12
//�������listC
int joinLinkedList(LNode *listA, LNode *listB, LNode *listC) {
	if ((listA == NULL && listB == NULL) || listC == NULL) {
		return ERROR;
	}
	LNode *pA = listA->next;
	LNode *pB = listB->next;
	LNode *c = listC;
	while (pA != NULL && pB != NULL) {
		if (pA->data <= pB->data) {
			c->next = pA;
			c = pA;
			pA = pA->next;
		}
		else {
			c->next = pB;
			c = pB;
			pB = pB->next;
		}
	}
	//����ʣ���
	c->next = pA ? pA : pB;
	free(listA);
	free(listB);
	return OK;
}

/*
	���������
	���˰��Сʱ
*/
int reverseLinkedList(LNode *list) {
	if (list == NULL) {
		return ERROR;
	}
	//ͷ����ĵ�һ���ڵ�
	LNode *p = list->next;
	if (p == NULL) {
		return OK;
	}
	//��¼λ��
	LNode *position = p->next;
	LNode *node = NULL; 
	//ͷ����ĵ�һ���ڵ��β�ڵ�
	p->next = NULL;
	while (position != NULL) {
		node = position->next;
		position->next = list->next;
		list->next = position;
		position = node;
	}
	return OK;
}



int testLinkedList(void) {
	LNode *listA = createLNode();
	/*LNode *listB = createLNode();
	LNode *listC = createLNode();
	int i = 1, j = 1;*/

	//��������
	//for (int num = 1; num <= 10; num++) {
	//	if (num % 2 != 0) {
	//		insertLinkedList(listA, num, i++);
	//	}
	//	else {
	//		insertLinkedList(listB, num, j++);
	//	}
	//}

	//printf("����A:\n");
	//printfLNode(listA);
	//printf("����B:\n");
	//printfLNode(listB);

	////�ϲ�
	//joinLinkedList(listA, listB, listC);
	//printf("�ϲ���ɣ�\n");
	//printfLNode(listC);



	//insertLinkedList(list, 10, 11);

	/*printfLNode(list);
	printf("��3����%d\n", getItemFromLinkedList(list, 3));

	ElemType deleted = 0;
	deleteFromLinkedList(list, 5, &deleted);
	printf("��5����ɾ������%d\n", deleted);
	printfLNode(list);*/

	for (int i = 1; i < 10; i++) {
		insertLinkedList(listA, i, i);
	}
	printf("ԭ����Ϊ:\n");
	printfLNode(listA);
	reverseLinkedList(listA);
	printf("�������:\n");
	printfLNode(listA);

	getchar();
	return 0;
}