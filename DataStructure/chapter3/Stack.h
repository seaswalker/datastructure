/*
	ջͷ�ļ�����
*/
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

#define OK 1

#define FALSE 0

#define TRUE 1

//��ʼ�����Լ�ÿ�����ӵ�����
#define INITSIZE 25
#define INCRESIZE 10

//ջ��Ԫ������
typedef int Elemtype;

//����ջ��������
typedef struct {
	//ջ��ָ��
	Elemtype *top;
	Elemtype *bottom;
	//��ʼ������
	int stacksize;
} Stack;

//���ú���
Stack *createStack();
Elemtype pop(Stack *stack);
Elemtype poll(Stack *stack);
int push(Stack *stack, Elemtype e);
int printStack(Stack *stack);
int stackLength(Stack *stack);
void clearStack(Stack *stack);
int printfStackByChar(Stack *stack);