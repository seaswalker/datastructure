//算法2——1，求两个线性表的并集
#include <stdio.h>
#include "datastructure.h"


//为两个线性表赋值
void assginment(List *list) {
	printf("请输入线性表元素个数:\n");
	int num = 0;
	scanf_s("%d", &num);
	printf("请输入线性表的元素，以空格分开:\n");
	for (int i = 0; i < num; i++) {
		scanf_s("%d", &list->ele[i]);
		list->length++;
	}
}

//合并两个线性表
void join(List *A, List *B) {
	ElemType ele;
	for (int i = 0; i < B->length; i++) {
		ele = B->ele[i];
		if (locate(A, ele, compare) == ERROR) {
			//插入
			insert(A, ele, A->length + 1);
		}
	}
}

void test2_1() {
	List *A = initList();
	List *B = initList();

	assginment(A);
	assginment(B);

	//合并
	join(A, B);
	printf("两个线性表合并完成，结果如下：\n");
	printfList(A);

	getchar();
	getchar();
}