//�㷨2����1�����������Ա�Ĳ���
#include <stdio.h>
#include "datastructure.h"


//Ϊ�������Ա�ֵ
void assginment(List *list) {
	printf("���������Ա�Ԫ�ظ���:\n");
	int num = 0;
	scanf_s("%d", &num);
	printf("���������Ա��Ԫ�أ��Կո�ֿ�:\n");
	for (int i = 0; i < num; i++) {
		scanf_s("%d", &list->ele[i]);
		list->length++;
	}
}

//�ϲ��������Ա�
void join(List *A, List *B) {
	ElemType ele;
	for (int i = 0; i < B->length; i++) {
		ele = B->ele[i];
		if (locate(A, ele, compare) == ERROR) {
			//����
			insert(A, ele, A->length + 1);
		}
	}
}

void test2_1() {
	List *A = initList();
	List *B = initList();

	assginment(A);
	assginment(B);

	//�ϲ�
	join(A, B);
	printf("�������Ա�ϲ���ɣ�������£�\n");
	printfList(A);

	getchar();
	getchar();
}