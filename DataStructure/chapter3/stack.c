/*
	ջ���Լ���ʼ����
	pop��push����
*/
#include "Stack.h"

//��ʼ��һ���յ�ջ
Stack *createStack() {
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	//ջ��ָ��ָ���·��������
	stack->bottom = (Elemtype *)malloc(INITSIZE * sizeof(Elemtype));
	stack->stacksize = INITSIZE;
	stack->top = stack->bottom;
	return stack;
}

/*
	��ջ
	ɾ��ջ��Ԫ��
*/
Elemtype pop(Stack *stack) {
	if (stack == NULL || stack->bottom == stack->top) {
		return ERROR;
	}
	return *(--stack->top);
}

/*
	��ջ
	��ɾ��ջ��Ԫ��
*/
Elemtype poll(Stack *stack) {
	if (stack == NULL || stack->bottom == stack->top) {
		return ERROR;
	}
	Elemtype *addr = stack->top - 1;
	return *addr;
}

/*
	ѹջ
*/
int push(Stack *stack, Elemtype e) {
	if (stack == NULL) {
		return ERROR;
	}
	//�ж��Ƿ��Ѿ��ﵽ����
	if (stack->top - stack->bottom >= stack->stacksize) {
		//���·����ڴ�
		stack->stacksize += INCRESIZE;
		realloc(stack, stack->stacksize * sizeof(Elemtype));
	}
	*(stack->top++) = e;
	return OK;
}

/*
	��ӡջ
*/
int printStack(Stack *stack) {
	if (stack == NULL) {
		return ERROR;
	}
	while (stack->top > stack->bottom) {
		printf("%d ", pop(stack));
	}
	printf("\n");
	return OK;
}

/*
	�õ�stack�ĳ���
*/
int stackLength(Stack *stack) {
	if (stack == NULL) {
		return ERROR;
	}
	return stack->top - stack->bottom;
}

/*
	���ջ
*/
void clearStack(Stack *stack) {
	if (stack != NULL) {
		stack->top = stack->bottom;
	}
}

/*
	��char�ĸ�ʽ��ӡstack
*/
int printfStackByChar(Stack *stack) {
	if (stack == NULL) {
		return ERROR;
	}
	while (stack->top > stack->bottom) {
		printf("%c ", pop(stack));
	}
	printf("\n");
	return OK;
}


//���Ժ�������Ҫʱ��Ϊmain
static int testStack(void) {
	Stack *stack = createStack();
	for (int i = 1; i <= 10; i++) {
		push(stack, i);
	}

	printf("ջ��Ԫ����%d\n", poll(stack));

	printStack(stack);

	getchar();
	return 0;
}