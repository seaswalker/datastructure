//一元多项式
#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"

//重新定义Item数据类型
typedef struct {
	//系数
	float coef;
	//指数
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
	根据用户输入创建多项式链表
	算法2.22
*/
PolynNode *createPolyn() {
	printf("请输入多项式的项数:\n");
	int n = 0;
	PolynNode *head = createPolynNode();
	//位置指针
	PolynNode *cur = head;
	PolynNode *temp = NULL;
	Item *ele = NULL;
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		temp = createPolynNode();
		ele = createItem();
		printf("请输入第%d项的系数:\n", i + 1);
		scanf_s("%f", &ele->coef);
		printf("请输入第%d项的指数:\n", i + 1);
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
		printf("您输入的多项式为空\n");
		return;
	}
	//标记第一个
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
	根据指数
	从多项式中查找，找到返回相应的节点
	没找到返回NULL
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
	获得多项式的项数
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

//插入函数
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
	//如果index > 长度 + 1
	if (counter < index - 1) {
		return ERROR;
	}
	//交换指针
	previous->next = ele;
	ele->next = NULL;
	return OK;
}


/*
	多项式相加，结果保存在A
	算法2.23
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
		//A中含有此项
		if (result != NULL) {
			result->data->coef += pB->data->coef;
		}
		else {
			length = polynLength(A);
			//插入到最后一项
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