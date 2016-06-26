/*
	循环队列定义
*/
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

#define OK 1

#define FALSE 0

#define TRUE 1

//存放的基本类型
typedef int ELement;

//循环队列类型
typedef struct {
	ELement *base;
	int head;
	int rear;
} CyclicQueue;