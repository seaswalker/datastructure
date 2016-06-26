//静态链表
#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"

//数组最大长度
#define SIZE 100

//定义静态链表
typedef struct {
	ElemType data;
	//表示下一个元素的坐标
	int cur;
}StaticLinkedList;

//生成一个备用链表 算法2.14
StaticLinkedList* initStaticLinkedList() {
	StaticLinkedList *list = (StaticLinkedList *)malloc(SIZE * sizeof(StaticLinkedList));
	for (int i = 0; i < SIZE - 1; i++) {
		list[i].cur = (i + 1);
	}
	list[SIZE - 1].cur = NULL;
	return list;
}

//算法2.15 分配控件 参数是一个备用链表
int mallocSLL(StaticLinkedList *list) {
	int positon = list[0].cur;
	//空间已用尽
	if (positon == NULL) {
		return ERROR;
	}
	list[0].cur = list[positon].cur;
	return positon;
}

//回收一个节点 算法2.16 position为回收的下标
void freeSLL(StaticLinkedList *list, int  position) {
	list[position].cur = list[0].cur;
	list[0].cur = position;
}

/*
	算法2.13 
	获取元素的位置
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

//打印
void printfSLL(StaticLinkedList *list, int head) {
	int position = head;
	while (position != NULL) {
		printf("%d ", list[position].data);
		position = list[position].cur;
	}
	printf("\n");
}

/*
	算法2.17 求链表A和B的并集
	space 是备用控件链表
*/
void joinSSL() {
	StaticLinkedList *space = initStaticLinkedList();
	//表示结果链表的头指针(下标)
	int head = 0;
	printf("请输入链表A元素的个数：\n");
	int lengthA = 0;
	scanf_s("%d", &lengthA);
	if (lengthA < 1) return;

	//输入A的元素，直接存入链表
	int position = 0;
	//上一个元素的下标
	int pre = 0;
	for (int i = 1; i <= lengthA; i++) {
		printf("请输入第%d个元素:\n", i);
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
	printf("请输入链表B元素个数:\n");
	scanf_s("%d", &lengthB);
	int temp = 0;
	int location = 0;
	for (int i = 1; i <= lengthB; i++) {
		printf("请输入第%d个元素:\n", i);
		scanf_s("%d", &temp);
		location = getLocation(space, head, temp);
		//如果此元素已经存在
		if (location != ERROR) {
			continue;
		}
		position = mallocSLL(space);
		space[position].data = temp;
		space[position].cur = NULL;
		space[pre].cur = position;
		pre = position;
	}

	printf("合并完成，结果如下：\n");
	printfSLL(space, head);
}

void testStaticLinkedList(void) {
	joinSSL();
	getchar();
	getchar();
}
