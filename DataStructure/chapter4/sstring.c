/*
	˳��ṹ�ַ���
*/

#include "String.h"
#include <time.h>

/*
	��ȡһ���ַ���
*/
static SString * getSString() {
	SString *str = (SString *)malloc(sizeof(SString) * MAXSIZE);
	printf("�������ַ���:\n");
	gets_s(str, MAXSIZE);
	return str;
}

/*
	�����ַ���
*/
int copySString(SString *target, SString *source) {
	if (source == NULL) {
		return ERROR;
	}
	if (target == NULL) {
		target = (SString *)malloc(sizeof(SString) * MAXSIZE);
	}
	char c;
	for (int i = 0; (c = source[i]) != '\0'; i++) {
		target[i] = c;
	}
	return OK;
}

/*
	�ж��ַ����Ƿ�Ϊ��
	Ϊ�շ���TRUE������FALSE
*/
static int isEmpty(SString *str) {
	return str == NULL || str[0] == '\0';
}

/*
	��ӡ�ַ���
*/
static int printString(SString *str) {
	if (str == NULL) {
		return ERROR;
	}
	for (int i = 0; str[i] != '\0'; i++) {
		printf("%c", str[i]);
	}
	printf("\n");
}

/*
	����ĸ˳��Ƚ������ַ���
	��һ���󷵻���������ȷ���0
	*/
static int compare(SString *strA, SString *strB) {
	if (strA == NULL || strB == NULL) {
		printf("�ַ�������Ϊ��!\n");
		return;
	}
	char a, b;
	while ((a = *strA) == (b = *strB) && a != '\0' && b != '\0') {
		strA++;
		strB++;
	}
	return a - b;
}

/*
	���ַ����ĳ���
	*/
static int length(SString *str) {
	if (str == NULL) {
		return 0;
	}
	int counter = 0;
	while (*str++ != '\0') {
		counter++;
	}
	return counter;
}

/*
	����ַ���
	*/
static int clear(SString *str) {
	if (str != NULL) {
		str[0] = '\0';
	}
	return OK;
}

/*
	�ַ���ƴ��
	����ƴ�Ӻ�ŵ���һ������
	*/
static int concat(SString *target, SString *strA, SString *strB) {
	//��ȥ�пմ���
	int index = 0;
	char c;
	while ((c = *strA++) != '\0') {
		target[index++] = c;
	}
	while ((c = *strB++) != '\0') {
		target[index++] = c;
	}
	//ĩβ���Ͻ����ַ�
	target[index] = '\0';
	return OK;
}

/*
	�ַ�����ȡ
	pos --��ʼλ��(��0��ʼ)
	length --����ʼλ�ÿ�ʼ��ȡ�ĳ���
	��ϵ���£�[pos, pos + length)
	*/
static int substring(SString *sub, SString *source, int pos, int length) {
	if (sub == NULL || source == NULL) {
		return ERROR;
	}
	int index = 0;
	int end = pos + length;
	char c;
	while ((c = source[pos]) != '\0' && pos++ < end) {
		sub[index++] = c;
	}
	sub[index] = '\0';
	return OK;
}

/*
kmp�㷨����ȡnext����
*/
static int *getNext(SString *str) {
	if (str == NULL) {
		return NULL;
	}
	int ls = length(str);
	int *next = (int *)malloc(sizeof(int) * ls);
	int k = -1;
	int j = 0;
	next[0] = -1;
	while (j < ls - 1) {
		if (k == -1 || str[k] == str[j]) {
			k++;
			j++;
			next[j] = k;
		}
		else {
			//������ǰѰ��
			k = next[k];
		}
	}
	return next;
}

/*
	�����ִ���λ��
	source���ҵ��ַ���
	target�ִ�
	pos --��ʼ���ҵ�λ��(0��ʼ��)
	*/
static int indexOf(SString *source, SString *target, int pos) {
	if (source == NULL || target == NULL) {
		return -1;
	}

	int sIndex = pos;
	int tIndex = 0;
	int ls = length(source);
	int lt = length(target);
	//Ϊ�˱����󳤶ȶ���������ʱ�临�Ӷȣ�source������������
	//for (sIndex; source[sIndex] != '\0'; sIndex++) {
	//	//����Ƚ��ִ��ַ�
	//	while (source[sIndex] != '\0' && target[tIndex] != '\0' && source[sIndex] == target[tIndex]) {
	//		sIndex++;
	//		tIndex++;
	//	}
	//	if (target[tIndex] == '\0') {
	//		//�ҵ�
	//		return sIndex - tIndex;
	//	}
	//	if (source[sIndex] == '\0') {
	//		���ҽ���
	//		return -1;
	//	}
	//	//��������
	//	sIndex -= tIndex;
	//	tIndex = 0;
	//}
	//return -1;

	//��׼д��
	/*while (sIndex < ls && tIndex < lt) {
		if (source[sIndex] == target[tIndex]) {
			sIndex++;
			tIndex++;
		}
		//ƥ��ʧ�ܣ�ָ�����
		else {
			sIndex = sIndex - tIndex + 1;
			tIndex = 0;
		}
	}

	if (tIndex == lt) {
		return sIndex - tIndex;
	}
	else {
		return -1;
	}*/

	//kmp�㷨ʵ��
	//next����
	int *next = getNext(target);
	while (sIndex < ls && tIndex < lt) {
		//tIndex == -1 ��ʾģʽ���ĵ�һ���ַ���������ƥ�䣬����ָ����ƣ�ģʽ��ָ���0
		if (tIndex == -1 || source[sIndex] == target[tIndex]) {
			sIndex++;
			tIndex++;
		}
		else {
			tIndex = next[tIndex];
		}
	}
	//ƥ��ɹ�
	if (tIndex >= lt) {
		return sIndex - lt;
	}
	return -1;
}

/*
	�ַ����滻
	source --���滻���ַ���
	replaced --���滻�Ĵ�
	replacement --�ô��ַ����滻
*/
static int replaceAll(SString *source, SString *replaced, SString *replacement) {
	if (source == NULL || replacement == NULL) {
		return ERROR;
	}
	int ls = length(source);
	int pos = indexOf(source, replaced, 0);
	int lrd = length(replaced);
	int lrt = length(replacement);
	while (pos >= 0) {
		//������滻�Ĵ����ȴ����滻�ģ���pos + lrd���ַ�ȫ��ǰ��dis
		if (lrd > lrt) {
			//ǰ�Ƶľ���
			int dis = lrd - lrt;
			for (int i = (pos + lrd); i <= ls; i++) {
				source[i - dis] = source[i];
			}
		}
		else {
			//���滻�ĳ���С�ڵ����滻��
			//��pos + lrd��ʼ����lrt - lrd��
			int dis = lrt - lrd;
			for (int i = ls; i >= pos + lrd; i--) {
				source[i + dis] = source[i];
			}
		}
		//�滻
		for (int i = 0; replacement[i] != '\0'; i++) {
			source[pos + i] = replacement[i];
		}
		//Ѱ����һ��
		ls += (lrt - lrd);
		pos = indexOf(source, replaced, 0);
	}
	return OK;
}

/*
	��source���ĵ�pos��֮ǰ����
	target��
	pos��1��ʼ��
*/
static int insert(SString *source, SString *target, int pos) {
	if (source == NULL || target == NULL) {
		return ERROR;
	}
	//�������ĳ���
	int ls = length(source);
	int lt = length(target);
	//Ų����λ
	for (int i = ls; i >= pos - 1; i--) {
		source[i + lt] = source[i];
	}
	//����
	for (int i = 1; i <= lt; i++) {
		source[pos + lt - 1 - i] = target[lt - i];
	}
	return OK;
}

/*
	�����ַ���
*/
static int destory(SString *str) {
	if (str != NULL) {
		free(str);
	}
}

/*
	ɾ���ض����ַ�
	pos --��ʼ��λ��(��1��ʼ)
	len --ɾ���ĳ���
*/
static int deleteCharAt(SString *str, int pos, int len) {
	if (str == NULL) {
		return ERROR;
	}
	int end = pos + len;
	int ls = length(str);
	if (end > ls) {
		end = ls + 1;
		len = ls - pos + 1;
	}
	for (int i = end - 1; i <= ls; i++) {
		str[i - len] = str[i];
	}
	return OK;
}

int testSString(void) {
	SString *strA = getSString();

	//���Ը���
	/*SString *copied = NULL;
	copySString(copied, str);
	printf("�ַ���������ϣ��ַ�������:\n");
	printString(str);*/

	/*if (isEmpty(str)) {
		printf("��");
	}*/

	//����compare����
	/*SString *strB = getSString();
	printf("%d", compare(strA, strB));*/

	//�����󳤶�
	//printf("%d\n", length(strA));

	//����concat
	/*SString *strB = getSString();
	SString *target = getSString();
	concat(target, strA, strB);
	printf("�ַ���ƴ�����:\n");
	printString(target);*/

	//���Խ�ȡ�ַ���
	/*SString *target = (SString *)malloc(sizeof(SString) * MAXSIZE);
	substring(target, strA, 2, 20);
	printf("��ȡ���:\n");
	printString(target);*/

	//���Բ���
	SString *target = getSString();
	printf("%d", indexOf(strA, target, 0));

	//�����滻
	/*SString *replaced = getSString();
	SString *replacement = getSString();
	replaceAll(strA, replaced, replacement);
	printf("�滻���:\n");
	printString(strA);*/

	//���Բ���
	/*SString *inserted = getSString();
	insert(strA, inserted, 7);
	printf("�������:\n");
	printString(strA);*/

	//����ɾ��
	/*deleteCharAt(strA, 2, 3);
	printf("ɾ�����:\n");
	printString(strA);*/


	getchar();
	return 0;
}
