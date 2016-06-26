//选择排序
#include "arrayutil.h"

/**
 * [simpleChooseSort 简单选择排序，时间复杂度O(n2)]
 * @param array [数组]
 */
static void simpleChooseSort(int array[]) {
	if(array == NULL) {
		return;
	}
	int length = getLength(array);
	//最小元素的下标
	int min = 0;
	for(int i = 0;i < length - 1;i ++) {
		//从i到length - 1选取最小的元素
		min = i;
		for(int j = i + 1;j < length;j ++) {
			if(array[j] < array[min]) {
				min = j;
			}
		}
		//交换i和最小值
		swap(array, i, min);
	}
}

int main(void) {
	int array[] = {10, 4, 20, 30, 15, 1, 9, 100, 7};
	simpleChooseSort(array);
	printf("The simpleChooseSort is done, the result is as follow:\n");
	printArray(array);
	return 0;
}