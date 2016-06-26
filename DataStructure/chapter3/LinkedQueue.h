//链队列
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

#define OK 1

#define FALSE 0

#define TRUE 1

//定义基本数据类型
typedef int Element;

//定义链队列的节点
typedef struct {
	Element data;
	struct Node *next;
} Node;

//定义链队列
typedef struct {
	//指向头结点和尾节点
	Node *head;
	Node *rear;
} LinkedQueue;