//算法2_2，按顺序合并线性表
#include <stdio.h>
#include "datastructure.h"

List* orderJoin(List *A, List *B) {
	//建立一个新链表
	List *C = initList();
	int counterA = 0;
	int counterB = 0;
	int counterC = 0;
	int lengthA = A->length;
	int lengthB = B->length;
	ElemType eleA, eleB;
	//不能使用\0判断int数组的结束。因为有默认值
	while (counterA < lengthA && counterB < lengthB) {
		eleA = A->ele[counterA];
		eleB = B->ele[counterB];
		if (compare(eleB, eleA) <= 0) {
			//插入B
			insert(C, eleB, ++counterC);
			counterB++;
		}
		else {
			insert(C, eleA, ++counterC);
			counterA++;
		}
	}
	//插入A或B中剩余的元素
	while (counterA < lengthA) {
		insert(C, A->ele[counterA++], ++counterC);
	}
	while (counterB < lengthB) {
		insert(C, B->ele[counterB++], ++counterC);
	}
	return C;
}

//测试数据 2 6 8 9 11 15 20
int test2_2(void) {
	List *A = initList();
	List *B = initList();

	//输入数据
	assginment(A);
	assginment(B);

	List *C = orderJoin(A, B);
	printf("合并完成:\n");
	printfList(C);

	getchar();
	getchar();

	return 0;
}