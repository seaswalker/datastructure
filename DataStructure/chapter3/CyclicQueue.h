/*
	ѭ�����ж���
*/
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

#define OK 1

#define FALSE 0

#define TRUE 1

//��ŵĻ�������
typedef int ELement;

//ѭ����������
typedef struct {
	ELement *base;
	int head;
	int rear;
} CyclicQueue;