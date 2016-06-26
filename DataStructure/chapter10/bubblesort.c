//冒泡排序
#include <stdio.h>
#include "arrayutil.h"

/**
 * [冒泡排序， 从小到大排序]
 * 固定执行N-1趟排序
 * @param array [int型数组]
 */
static void bubbleSort(int array[]) {
	if(array == NULL) {
		return;
	}
	int length = getLength(array);
	int temp = 0;
	for(int i = 0;i < length - 1;i ++) {
		for(int j = 0;j < length - 1;j ++) {
			if(array[j + 1] < array[j]) {
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
 			}
		}
	}
}

/**
 * [buuleSortImprove 冒泡排序的改进]
 * 上面的算法一律都是N-1趟排序，其实不一定，可能存在不用N-1趟就排序完成，后面的是不必要的
 * 方法就是设置一个变量，监视上一趟排序有没有交换，如果没有，不必进行剩余的排序
 * @param array [数组]
 */
void buuleSortImprove(int array[]) {
	if(array == NULL) {
		return;
	}
	//监视变量
	int hasChanged = 1;
	int length = getLength(array);
	int temp = 0;
	for(int i = 0;i < length - 1;i ++) {
		if(hasChanged) {
			hasChanged = 0;
			for(int j = 0;j < length - 1;j ++) {
				if(array[j + 1] < array[j]) {
					temp = array[j];
					array[j] = array[j + 1];
					array[j + 1] = temp;
					hasChanged = 1;
	 			}
			}
		}
	}
}

/*int main(void) {
	int array[] = {10, 4, 20, 30, 15, 1, 9, 100, 7};
	//bubbleSort(array);
	buuleSortImprove(array);
	printf("The sort is done, the result as follow::\n");
	printArray(array);
	return 0;
}*/
