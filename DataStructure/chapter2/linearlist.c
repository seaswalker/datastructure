/*
* LinearList.c
* 建立基本的线性表
*  Created on: 2015年3月19日
*      Author: skywalker
*/

#include <stdio.h>
#include <stdlib.h>
#include  "datastructure.h"

//定义链表初始长度
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

//初始化线性链表，返回此线性表的指针
List* initList() {
	List *list = (List*)malloc(sizeof(List));
	list->ele = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	list->length = 0;
	list->listsize = LIST_INIT_SIZE;
	return list;
}

//销毁线性链表
int destory(List *list) {
	if (list == NULL) {
		return ERROR;
	}
	free(list);
	return OK;
}

//清空线性表
int clearList(List *list) {
	if (list == NULL) {
		return ERROR;
	}
	list->ele = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	list->length = 0;
	list->listsize = LIST_INIT_SIZE;
	return OK;
}

//判断给定的下标是否越界
int isOutofBound(List *list, int index) {
	if (list != NULL) {
		return (index < 1 || index > list->length);
	}
	return ERROR;
}

//判断线性表是否为空
int isEmpty(List *list) {
	return list == NULL || list->length == 0;
}

//返回线性表的长度
int length(List *list) {
	if (list == NULL) {
		return 0;
	}
	return list->length;
}

//返回第i的元素
ElemType getItem(List *list, int i) {
	//判断是否越界，第几个对应下标 i - 1
	if (list == NULL || isOutofBound(list, i)) {
		return ERROR;
	}
	return list->ele[i - 1];
}

//比较两个ElemType元素的大小
int compare(ElemType e1, ElemType e2) {
	return e1 - e2;
}

//找到所给元素的下标值
int locate(List *list, ElemType e, int(*compare)()) {
	if (list == NULL) {
		return ERROR;
	}
	for (int i = 0; i < list->length; i++) {
		if ((*compare) (list->ele[i], e) == 0) {
			return (i + 1);
		}
	}
	//没有找到
	return ERROR;
}

//返回给定元素的上一个元素
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

//返回给定元素的下一个元素
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

//在给定的位置插入一个新的元素，索引从1开始
int insert(List *list, ElemType e, int index) {
	if (list == NULL || index < 1 || index > list->length + 1) {
		return ERROR;
	}
	//容量没有用尽
	if (list->length < list->listsize) {
		list->length++;
		//后面的元素全部后移一个单位
		for (int i = list->length; i >= index - 1; i--) {
			list->ele[i + 1] = list->ele[i];
		}
		list->ele[index - 1] = e;
	}
	else {
		index--;
		//如果用量用尽，扩容
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

//删除给定位置的元素，返回被删除的元素
ElemType deleteItem(List *list, int index) {
	if (isEmpty(list) || isOutofBound(list, index)) {
		return ERROR;
	}
	ElemType old = list->ele[index - 1];
	//删除，最后一个元素不需要特殊处理，因为遍历是通过length决定的
	for (int i = index; i < list->length; i++) {
		list->ele[i - 1] = list->ele[i];
	}
	list->length--;
	return old;
}

//遍历
void traverse(List *list) {
	if (isEmpty(list)) {
		return;
	}
	for (int i = 0; i < list->length; i++) {
		printf("第%d个元素  ", i + 1);
	}
}

//测试辅助函数，填充list
void fill(List *list, int limit) {
	for (int i = 1; i <= limit; i++) {
		list->ele[i - 1] = rand() % 100;
	}
	list->length = limit;
}

//遍历输出线性表
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
	printf("请输入需要填充元素的个数:\n");
	scanf_s("%d", &count);
	fill(list, count);
	printf("线性表填充完毕:\n");
	printfList(list);

	//测试判断出界函数
	int position = 0;
	while (TRUE) {
		printf("请输入判断越界的位置(从1开始，输入-1结束):\n");
		scanf_s("%d", &position);
		if (position == -1) {
			break;
		}
		result = isOutofBound(list, position);
		resultStr = result == ERROR ? "出错" : (result ? "越界" : "不越界");
		printf("%s\n", resultStr);
	}

	//测试length函数
	int length = list->length;
	printf("list的长度是%d\n", length);

	//测试getItem()函数
	while (TRUE) {
		printf("测试getItem函数，请输入获取元素的下标(输入-1返回):\n");
		scanf_s("%d", &position);
		if (position == -1) {
			break;
		}
		result = getItem(list, position);
		if (result == ERROR) {
			printf("您输入的下标越界，请重新输入");
			continue;
		}
		printf("第%d个元素是%d\n", position, result);
	}

	//测试定位函数
	while (TRUE) {
		printf("请输入需要定位的元素(-1返回):\n");
		scanf_s("%d", &element);
		if (element == -1) {
			break;
		}
		result = locate(list, element, compare);
		if (result == ERROR) {
			printf("没有此元素\n");
			continue;
		}
		printf("您要找的元素是第%d个元素\n", result);
	}

	//测试上一个函数
	while (TRUE) {
		printf("测试上一个元素(-1返回):\n");
		scanf_s("%d", &element);
		if (element == -1) {
			break;
		}
		element = priorEle(list, element, compare);
		if (element == ERROR) {
			printf("没有此元素\n");
			continue;
		}
		printf("上一个元素是%d\n", element);
	}

	//测试下一个函数
	while (TRUE) {
		printf("测试下一个元素(-1返回):\n");
		scanf_s("%d", &element);
		if (element == -1) {
			break;
		}
		element = nextEle(list, element, compare);
		if (element == ERROR) {
			printf("没有此元素\n");
			continue;
		}
		printf("下一个元素是%d\n", element);
	}

	//测试insert函数
	while (TRUE) {
		printf("测试插入的元素(-1返回):\n");
		scanf_s("%d", &element);
		if (element == -1) {
			break;
		}
		printf("插入的位置:\n");
		scanf_s("%d", &position);
		result = insert(list, element, position);
		if (result == ERROR) {
			printf("位置非法\n");
			continue;
		}
		printf("插入成功，新线性表为\n");
		printfList(list);
	}

	//测试删除函数
	while (TRUE) {
		printf("删除的位置(从1开始-1返回):\n");
		scanf_s("%d", &position);
		if (position == -1) {
			break;
		}
		result = deleteItem(list, position);
		if (result == ERROR) {
			printf("没有此元素\n");
			continue;
		}
		printf("删除成功，新线性表为\n");
		printfList(list);
	}

	getchar();
	getchar();
}
