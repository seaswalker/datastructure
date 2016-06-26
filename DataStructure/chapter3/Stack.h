/*
	栈头文件定义
*/
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

#define OK 1

#define FALSE 0

#define TRUE 1

//初始容量以及每次增加的容量
#define INITSIZE 25
#define INCRESIZE 10

//栈内元素类型
typedef int Elemtype;

//定义栈数据类型
typedef struct {
	//栈顶指针
	Elemtype *top;
	Elemtype *bottom;
	//初始的容量
	int stacksize;
} Stack;

//常用函数
Stack *createStack();
Elemtype pop(Stack *stack);
Elemtype poll(Stack *stack);
int push(Stack *stack, Elemtype e);
int printStack(Stack *stack);
int stackLength(Stack *stack);
void clearStack(Stack *stack);
int printfStackByChar(Stack *stack);