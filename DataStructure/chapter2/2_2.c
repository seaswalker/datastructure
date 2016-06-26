//�㷨2_2����˳��ϲ����Ա�
#include <stdio.h>
#include "datastructure.h"

List* orderJoin(List *A, List *B) {
	//����һ��������
	List *C = initList();
	int counterA = 0;
	int counterB = 0;
	int counterC = 0;
	int lengthA = A->length;
	int lengthB = B->length;
	ElemType eleA, eleB;
	//����ʹ��\0�ж�int����Ľ�������Ϊ��Ĭ��ֵ
	while (counterA < lengthA && counterB < lengthB) {
		eleA = A->ele[counterA];
		eleB = B->ele[counterB];
		if (compare(eleB, eleA) <= 0) {
			//����B
			insert(C, eleB, ++counterC);
			counterB++;
		}
		else {
			insert(C, eleA, ++counterC);
			counterA++;
		}
	}
	//����A��B��ʣ���Ԫ��
	while (counterA < lengthA) {
		insert(C, A->ele[counterA++], ++counterC);
	}
	while (counterB < lengthB) {
		insert(C, B->ele[counterB++], ++counterC);
	}
	return C;
}

//�������� 2 6 8 9 11 15 20
int test2_2(void) {
	List *A = initList();
	List *B = initList();

	//��������
	assginment(A);
	assginment(B);

	List *C = orderJoin(A, B);
	printf("�ϲ����:\n");
	printfList(C);

	getchar();
	getchar();

	return 0;
}