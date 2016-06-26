/*
	顺序结构字符串
*/

#include "String.h"
#include <time.h>

/*
	获取一个字符串
*/
static SString * getSString() {
	SString *str = (SString *)malloc(sizeof(SString) * MAXSIZE);
	printf("请输入字符串:\n");
	gets_s(str, MAXSIZE);
	return str;
}

/*
	拷贝字符串
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
	判断字符串是否为空
	为空返回TRUE，否则FALSE
*/
static int isEmpty(SString *str) {
	return str == NULL || str[0] == '\0';
}

/*
	打印字符串
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
	按字母顺序比较两个字符串
	第一个大返回整数，相等返回0
	*/
static int compare(SString *strA, SString *strB) {
	if (strA == NULL || strB == NULL) {
		printf("字符串不能为空!\n");
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
	求字符串的长度
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
	清空字符串
	*/
static int clear(SString *str) {
	if (str != NULL) {
		str[0] = '\0';
	}
	return OK;
}

/*
	字符串拼接
	两个拼接后放到第一个参数
	*/
static int concat(SString *target, SString *strA, SString *strB) {
	//略去判空处理
	int index = 0;
	char c;
	while ((c = *strA++) != '\0') {
		target[index++] = c;
	}
	while ((c = *strB++) != '\0') {
		target[index++] = c;
	}
	//末尾加上结束字符
	target[index] = '\0';
	return OK;
}

/*
	字符串截取
	pos --起始位置(从0开始)
	length --从起始位置开始截取的长度
	关系如下：[pos, pos + length)
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
kmp算法，获取next数组
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
			//继续向前寻找
			k = next[k];
		}
	}
	return next;
}

/*
	查找字串的位置
	source查找的字符串
	target字串
	pos --开始查找的位置(0开始计)
	*/
static int indexOf(SString *source, SString *target, int pos) {
	if (source == NULL || target == NULL) {
		return -1;
	}

	int sIndex = pos;
	int tIndex = 0;
	int ls = length(source);
	int lt = length(target);
	//为了避免求长度而导致增加时间复杂度，source串迭代到结束
	//for (sIndex; source[sIndex] != '\0'; sIndex++) {
	//	//逐个比较字串字符
	//	while (source[sIndex] != '\0' && target[tIndex] != '\0' && source[sIndex] == target[tIndex]) {
	//		sIndex++;
	//		tIndex++;
	//	}
	//	if (target[tIndex] == '\0') {
	//		//找到
	//		return sIndex - tIndex;
	//	}
	//	if (source[sIndex] == '\0') {
	//		查找结束
	//		return -1;
	//	}
	//	//继续查找
	//	sIndex -= tIndex;
	//	tIndex = 0;
	//}
	//return -1;

	//标准写法
	/*while (sIndex < ls && tIndex < lt) {
		if (source[sIndex] == target[tIndex]) {
			sIndex++;
			tIndex++;
		}
		//匹配失败，指针回溯
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

	//kmp算法实现
	//next数组
	int *next = getNext(target);
	while (sIndex < ls && tIndex < lt) {
		//tIndex == -1 表示模式串的第一个字符和主串不匹配，主串指针后移，模式串指针归0
		if (tIndex == -1 || source[sIndex] == target[tIndex]) {
			sIndex++;
			tIndex++;
		}
		else {
			tIndex = next[tIndex];
		}
	}
	//匹配成功
	if (tIndex >= lt) {
		return sIndex - lt;
	}
	return -1;
}

/*
	字符串替换
	source --被替换的字符串
	replaced --被替换的串
	replacement --用此字符串替换
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
		//如果被替换的串长度大于替换的，从pos + lrd的字符全部前移dis
		if (lrd > lrt) {
			//前移的距离
			int dis = lrd - lrt;
			for (int i = (pos + lrd); i <= ls; i++) {
				source[i - dis] = source[i];
			}
		}
		else {
			//被替换的长度小于等于替换的
			//从pos + lrd开始后移lrt - lrd个
			int dis = lrt - lrd;
			for (int i = ls; i >= pos + lrd; i--) {
				source[i + dis] = source[i];
			}
		}
		//替换
		for (int i = 0; replacement[i] != '\0'; i++) {
			source[pos + i] = replacement[i];
		}
		//寻找下一个
		ls += (lrt - lrd);
		pos = indexOf(source, replaced, 0);
	}
	return OK;
}

/*
	在source串的第pos个之前插入
	target，
	pos从1开始计
*/
static int insert(SString *source, SString *target, int pos) {
	if (source == NULL || target == NULL) {
		return ERROR;
	}
	//两个串的长度
	int ls = length(source);
	int lt = length(target);
	//挪出空位
	for (int i = ls; i >= pos - 1; i--) {
		source[i + lt] = source[i];
	}
	//插入
	for (int i = 1; i <= lt; i++) {
		source[pos + lt - 1 - i] = target[lt - i];
	}
	return OK;
}

/*
	销毁字符串
*/
static int destory(SString *str) {
	if (str != NULL) {
		free(str);
	}
}

/*
	删除特定的字符
	pos --开始的位置(从1开始)
	len --删除的长度
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

	//测试复制
	/*SString *copied = NULL;
	copySString(copied, str);
	printf("字符串拷贝完毕，字符串如下:\n");
	printString(str);*/

	/*if (isEmpty(str)) {
		printf("空");
	}*/

	//测试compare函数
	/*SString *strB = getSString();
	printf("%d", compare(strA, strB));*/

	//测试求长度
	//printf("%d\n", length(strA));

	//测试concat
	/*SString *strB = getSString();
	SString *target = getSString();
	concat(target, strA, strB);
	printf("字符串拼接完成:\n");
	printString(target);*/

	//测试截取字符串
	/*SString *target = (SString *)malloc(sizeof(SString) * MAXSIZE);
	substring(target, strA, 2, 20);
	printf("截取完成:\n");
	printString(target);*/

	//测试查找
	SString *target = getSString();
	printf("%d", indexOf(strA, target, 0));

	//测试替换
	/*SString *replaced = getSString();
	SString *replacement = getSString();
	replaceAll(strA, replaced, replacement);
	printf("替换完成:\n");
	printString(strA);*/

	//测试插入
	/*SString *inserted = getSString();
	insert(strA, inserted, 7);
	printf("插入完成:\n");
	printString(strA);*/

	//测试删除
	/*deleteCharAt(strA, 2, 3);
	printf("删除完成:\n");
	printString(strA);*/


	getchar();
	return 0;
}
