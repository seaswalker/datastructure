/* ���ֲ��� */
#include <stdio.h>

#define ERROR -1

//�������ĳ���
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
 * ���ֲ��Һ���
 * array�����ҵ�����
 * number ���ҵ�����
 * begin ��ʼ��λ��
 * end ������λ��
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
	//�����������
	int array[] = {5, 13, 19, 21, 37, 56, 64, 75, 80, 88, 92};
	printf("������Ҫ���ҵ�����:\n");
	int number = 0;
	scanf("%d", &number);
	
	int length = getLength(array);
	int position = binarySearch(array, number, 0, length - 1);
	
	printf("��%d������\n", position + 1);
}
