//������
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

#define OK 1

#define FALSE 0

#define TRUE 1

//���������������
typedef int Element;

//���������еĽڵ�
typedef struct {
	Element data;
	struct Node *next;
} Node;

//����������
typedef struct {
	//ָ��ͷ����β�ڵ�
	Node *head;
	Node *rear;
} LinkedQueue;