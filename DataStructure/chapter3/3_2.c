/*
	第3.2节
	栈的应用
*/

#include "Stack.h"

/*
	算法3.1
	数制转换函数
	10进制向其它进制转换
	n--待转换的10进制数字
	scale--目标进制
*/
void conversion(int n, int scale) {
	Stack *stack = createStack();
	while (n > 0) {
		push(stack, n % scale);
		n = n / scale;
	}
	printf("%d的%d进制数为：\n", n, scale);
	printStack(stack);
}

/*
	括号匹配的检验
*/
int checkBrace() {
	char str[50];
	char c;
	//栈顶左括号
	char left;
	printf("请开始输入测试数据:\n");
	Stack *stack = createStack();
	gets_s(str, 50);
	for(int i = 0;(c = str[i]) != '\0';i ++) {
		if (c == '{' || c == '[' || c == '(') {
			push(stack, c);
		}
		else if (c == '}' || c == ']' || c == ')') {
			//如果没有左括号
			if (stackLength(stack) == 0) {
				printf("格式有误！\n");
				return ERROR;
			}
			left = (char) poll(stack);
			if (left == '{') {
				if (c == '}') {
					pop(stack);
					continue;
				}
				else {
					printf("格式有误！\n");
					return ERROR;
				}
			}
			else if (left == '[') {
				if (c == ']') {
					pop(stack);
					continue;
				}
				else {
					printf("格式有误！\n");
					return ERROR;
				}
			}
			else if (left == '(') {
				if (c == ')') {
					pop(stack);
					continue;
				}
				else {
					printf("格式有误！\n");
					return ERROR;
				}
			}
		}
	}
	//检查
	int braces = stackLength(stack);
	if (braces == 0) {
		printf("匹配成功");
	}
	else {
		printf("匹配失败");
	}
	return OK;
}

/*
	算法3.2
	行编辑程序
*/
int lineEdit() {
	printf("请输入数据:\n");
	char str[50];
	gets_s(str, 50);
	Stack *stack = createStack();
	char c;
	for (int i = 0; (c = str[i]) != '\0'; i++) {
		if (c == '#') {
			//退格
			pop(stack);
			continue;
		}
		else if (c == '@') {
			clearStack(stack);
			break;
		}
		else {
			push(stack, c);
		}
	}
	printf("结果为:\n");
	printfStackByChar(stack);
}

static int test3_2(void) {
	lineEdit();

	getchar();
	return 0;
}