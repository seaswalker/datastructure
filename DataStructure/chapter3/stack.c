/*
	栈以以及初始化、
	pop、push函数
*/
#include "Stack.h"

//初始化一个空的栈
Stack *createStack() {
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	//栈底指针指向新分配的数组
	stack->bottom = (Elemtype *)malloc(INITSIZE * sizeof(Elemtype));
	stack->stacksize = INITSIZE;
	stack->top = stack->bottom;
	return stack;
}

/*
	出栈
	删除栈顶元素
*/
Elemtype pop(Stack *stack) {
	if (stack == NULL || stack->bottom == stack->top) {
		return ERROR;
	}
	return *(--stack->top);
}

/*
	出栈
	不删除栈顶元素
*/
Elemtype poll(Stack *stack) {
	if (stack == NULL || stack->bottom == stack->top) {
		return ERROR;
	}
	Elemtype *addr = stack->top - 1;
	return *addr;
}

/*
	压栈
*/
int push(Stack *stack, Elemtype e) {
	if (stack == NULL) {
		return ERROR;
	}
	//判断是否已经达到容量
	if (stack->top - stack->bottom >= stack->stacksize) {
		//重新分配内存
		stack->stacksize += INCRESIZE;
		realloc(stack, stack->stacksize * sizeof(Elemtype));
	}
	*(stack->top++) = e;
	return OK;
}

/*
	打印栈
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
	得到stack的长度
*/
int stackLength(Stack *stack) {
	if (stack == NULL) {
		return ERROR;
	}
	return stack->top - stack->bottom;
}

/*
	清空栈
*/
void clearStack(Stack *stack) {
	if (stack != NULL) {
		stack->top = stack->bottom;
	}
}

/*
	用char的格式打印stack
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


//测试函数，需要时改为main
static int testStack(void) {
	Stack *stack = createStack();
	for (int i = 1; i <= 10; i++) {
		push(stack, i);
	}

	printf("栈顶元素是%d\n", poll(stack));

	printStack(stack);

	getchar();
	return 0;
}