/* 二分查找 */
#include <stdio.h>

#define ERROR -1

//求出数组的长度
static int getLength(int array[]) {
	if(array == NULL) {
		return ERROR;
	}
	int length = 0;
	while(array[length] != '\0') {
		length ++;
	}
	return length;
}

/**
 * 二分查找函数
 * array被查找的数组
 * number 查找的数字
 * begin 开始的位置
 * end 结束的位置
*/
static int binarySearch(int array[], int number, int begin, int end) {
	int middle = (end - begin) / 2 + begin;
	if(array[middle] == number) {
		return middle;
	}else if(array[middle] > number) {
		binarySearch(array, number, begin, middle - 1);
	}else {
		binarySearch(array, number, middle + 1, end);
	}
}

int main(void) {
	//定义测试数组
	int array[] = {5, 13, 19, 21, 37, 56, 64, 75, 80, 88, 92};
	printf("请输入要查找的数字:\n");
	int number = 0;
	scanf("%d", &number);
	
	int length = getLength(array);
	int position = binarySearch(array, number, 0, length - 1);
	
	printf("第%d个数字\n", position + 1);
}
