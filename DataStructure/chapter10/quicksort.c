//快速排序
#include "bubblesort.c"

/**
 * [getPivotkey 获得枢轴，直接以第一个元素，作为枢轴]
 * @param  array [数组]
 * @param  low   [数组下界]
 * @param  high  [数组上届]
 * @return       [枢轴]
 */
static int getPivotkey(int array[], int low, int high) {
	if(array == NULL || low >= high) {
		return -1;
	}
	return array[low];
}

/**
 * [getMiddle 取三个数的中位数]
 * @param  numberA numberB numberC  [三个数字]
 */
static int getMiddle(int numberA, int numberB, int numberC) {
	int array[] = {numberA, numberB, numberC};
	//利用冒泡排序对这三个数字进行排序
	buuleSortImprove(array);
	return array[1];
}

/**
 * [getPivotkeyImprove 改进版获取枢轴，取array[low]、array[high]、array[(low + high) / 2]的中值作为枢轴]
 * 可以解决数组在有序或者基本有序时退化为冒泡排序的弊端
 * @param  array [数组]
 * @param  low   [下界]
 * @param  high  [上届]
 * @return       [中值]
 */
static int getPivotkeyImprove(int array[], int low, int high) {
	if(array == NULL || low >= high) {
		return -1;
	}
	return getMiddle(array[low], array[high], array[(low + high) / 2]);
}

/**
 * [divideArray 按照快排算法把给定的数组部分以枢轴为边界划分为两部分]
 * @param array [数组]
 * @param low   [下边界]
 * @param high  [上边界]
 * @return 返回新的枢轴位置
 */
static int divideArray(int array[], int low, int high) {
	if(array == NULL || low >= high) {
		return 0;
	}
	//交替从高位、低位搜索、交换，这里是算法的精华部分
	//int privotKey = getPivotkey(array, low, high);
	int privotKey = getPivotkeyImprove(array, low, high);
	while(low < high) {
		while(low < high && array[high] >= privotKey) {
			high --;
		}
		swap(array, low, high);
		while(low < high && array[low] <= privotKey) {
			low ++;
		}
		swap(array, low, high);
	}
	return low;
}

/**
 * [quickSort 快速排序算法]
 * @param array [数组]
 * @param low   [下边界]
 * @param high  [上边界]
 */
static void quickSort(int array[], int low, int high) {
	//递归调用临界条件
	if(array == NULL || low >= high) {
		return;
	}
	int privotKeyPos = divideArray(array, low, high);
	quickSort(array, low, privotKeyPos - 1);
	quickSort(array, privotKeyPos + 1, high);
}

int main(void) {
	int array[] = {10, 4, 20, 30, 15, 1, 9, 100, 7};
	quickSort(array, 0, getLength(array) - 1);
	printf("The quickSort is done, the result is as follow:\n");
	printArray(array);
	return 0;
}
