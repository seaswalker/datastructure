/*
	����洢�ṹ������
*/
#include "Tree.h"

//ȫ�ּ�����
static int counter = 0;

/*
	����һ���������ڵ�
*/
static BiTNode *createBinaryTreeNode() {
	BiTNode *node =  (BiTNode *)malloc(sizeof(BiTNode));
	node->data = '/0';
	node->lchild = NULL;
	node->rchild = NULL;
	return node;
}

/*
	�ݹ鴴��������
	node --��ǰindex�ĸ��ڵ�
	index -�ַ�����Ҫ������±�ֵ
*/
static void recursion_left(BiTNode *node, char str[]) {
	char c = str[counter];
	if (c == ' ' || c == '\0') {
		node = NULL;
		return;
	}
	node = createBinaryTreeNode();
	node->data = str[counter];
	recursion(node->lchild, str, ++counter);
	recursion(node->rchild, str, ++counter);
}

static BiTNode *createBinaryTree() {
	printf("����������ڵ��ֵ(�ո�������):\n");
	char str[100];
	gets_s(str, 100);
	//��һ���ַ��ǿմ�������
	if (str[0] == ' ') {
		return NULL;
	}
	BiTNode *tree = NULL;
	recursion(tree, str);
	return tree;
}

/*
	�������������
*/
static void preOrderIterator(BiTNode *tree) {
	if (tree == NULL) {
		return;
	}
	printf("%c", tree->data);
	//������
	preOrderIterator(tree->lchild);
	//������
	preOrderIterator(tree->rchild);
}

int main(void) {
	BiTNode *tree = createBinaryTree();
	printf("�������:\n");
	preOrderIterator(tree);

	getchar();
	return 0;
}