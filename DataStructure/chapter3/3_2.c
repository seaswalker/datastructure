/*
	��3.2��
	ջ��Ӧ��
*/

#include "Stack.h"

/*
	�㷨3.1
	����ת������
	10��������������ת��
	n--��ת����10��������
	scale--Ŀ�����
*/
void conversion(int n, int scale) {
	Stack *stack = createStack();
	while (n > 0) {
		push(stack, n % scale);
		n = n / scale;
	}
	printf("%d��%d������Ϊ��\n", n, scale);
	printStack(stack);
}

/*
	����ƥ��ļ���
*/
int checkBrace() {
	char str[50];
	char c;
	//ջ��������
	char left;
	printf("�뿪ʼ�����������:\n");
	Stack *stack = createStack();
	gets_s(str, 50);
	for(int i = 0;(c = str[i]) != '\0';i ++) {
		if (c == '{' || c == '[' || c == '(') {
			push(stack, c);
		}
		else if (c == '}' || c == ']' || c == ')') {
			//���û��������
			if (stackLength(stack) == 0) {
				printf("��ʽ����\n");
				return ERROR;
			}
			left = (char) poll(stack);
			if (left == '{') {
				if (c == '}') {
					pop(stack);
					continue;
				}
				else {
					printf("��ʽ����\n");
					return ERROR;
				}
			}
			else if (left == '[') {
				if (c == ']') {
					pop(stack);
					continue;
				}
				else {
					printf("��ʽ����\n");
					return ERROR;
				}
			}
			else if (left == '(') {
				if (c == ')') {
					pop(stack);
					continue;
				}
				else {
					printf("��ʽ����\n");
					return ERROR;
				}
			}
		}
	}
	//���
	int braces = stackLength(stack);
	if (braces == 0) {
		printf("ƥ��ɹ�");
	}
	else {
		printf("ƥ��ʧ��");
	}
	return OK;
}

/*
	�㷨3.2
	�б༭����
*/
int lineEdit() {
	printf("����������:\n");
	char str[50];
	gets_s(str, 50);
	Stack *stack = createStack();
	char c;
	for (int i = 0; (c = str[i]) != '\0'; i++) {
		if (c == '#') {
			//�˸�
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
	printf("���Ϊ:\n");
	printfStackByChar(stack);
}

static int test3_2(void) {
	lineEdit();

	getchar();
	return 0;
}