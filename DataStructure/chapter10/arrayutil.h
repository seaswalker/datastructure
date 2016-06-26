//数组常用函数
#include <stdio.h>

/**
 * [求数组的长度]
 * @param  array [数组]
 * @return       [返回数组的长度]
 */
int getLength(int array[]) {
	if(array == NULL) {
		return 0;
	}
	int counter = 0;
	for(counter;array[counter] != '\0';counter ++);
	return counter;
}

/**
 * [printArray 打印数组元素]
 * @param array [数组]
 */
void printArray(int array[]) {
	if(array == NULL) {
		return;
	}
	int length = getLength(array);
	for(int i = 0;i < length;i ++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

/**
 * [swap 交换数组两个元素]
 * @param array [数组]
 * @param posA  [第一个位置]
 * @param posB  [第二个位置]
 */
void swap(int array[], int posA, int posB) {
	if(array == NULL || posA == posB) {
		return;
	}
	int temp = array[posB];
	array[posB] = array[posA];
	array[posA] = temp;
}