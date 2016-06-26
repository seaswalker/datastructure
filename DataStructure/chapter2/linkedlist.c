//链表
#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"

//辅助函数，打印链表
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

//创建一个链表(仅包含头节点)
LNode* createLNode() {
	LNode *head = (LNode *)malloc(sizeof(LNode));
	head->next = NULL;
}

//插入一个节点，位置从1开始,29页算法2.9
int insertLinkedList(LNode * list, ElemType eleType, int index) {
	if (index < 1) return ERROR;
	//标志量记录是否找到
	int isFound = FALSE;
	//不要从头指针开始
	LNode *p = list->next;
	//如果仅有一个头结点
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

//获取特定位置的元素(从1开始) 算法2.8
ElemType getItemFromLinkedList(LNode *list, int index) {
	LNode *p = list->next;
	//只有头结点
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

//算法2.10 删除特定位置的节点，被删除的元素放到ele中
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

//合并两个已经从小到大排号许的链表 算法2.12
//结果放入listC
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
	//链接剩余的
	c->next = pA ? pA : pB;
	free(listA);
	free(listB);
	return OK;
}

/*
	链表的逆置
	用了半个小时
*/
int reverseLinkedList(LNode *list) {
	if (list == NULL) {
		return ERROR;
	}
	//头结点后的第一个节点
	LNode *p = list->next;
	if (p == NULL) {
		return OK;
	}
	//记录位置
	LNode *position = p->next;
	LNode *node = NULL; 
	//头结点后的第一个节点变尾节点
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

	//插入数据
	//for (int num = 1; num <= 10; num++) {
	//	if (num % 2 != 0) {
	//		insertLinkedList(listA, num, i++);
	//	}
	//	else {
	//		insertLinkedList(listB, num, j++);
	//	}
	//}

	//printf("链表A:\n");
	//printfLNode(listA);
	//printf("链表B:\n");
	//printfLNode(listB);

	////合并
	//joinLinkedList(listA, listB, listC);
	//printf("合并完成：\n");
	//printfLNode(listC);



	//insertLinkedList(list, 10, 11);

	/*printfLNode(list);
	printf("第3个：%d\n", getItemFromLinkedList(list, 3));

	ElemType deleted = 0;
	deleteFromLinkedList(list, 5, &deleted);
	printf("第5个被删除，是%d\n", deleted);
	printfLNode(list);*/

	for (int i = 1; i < 10; i++) {
		insertLinkedList(listA, i, i);
	}
	printf("原链表为:\n");
	printfLNode(listA);
	reverseLinkedList(listA);
	printf("逆序完成:\n");
	printfLNode(listA);

	getchar();
	return 0;
}