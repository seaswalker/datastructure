/*
	链表存储结构二叉树
*/
#include "Tree.h"

//全局计数器
static int counter = 0;

/*
	创建一个二叉树节点
*/
static BiTNode *createBinaryTreeNode() {
	BiTNode *node =  (BiTNode *)malloc(sizeof(BiTNode));
	node->data = '/0';
	node->lchild = NULL;
	node->rchild = NULL;
	return node;
}

/*
	递归创建左子树
	node --当前index的父节点
	index -字符串需要处理的下标值
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
	printf("以先序输入节点的值(空格代表空树):\n");
	char str[100];
	gets_s(str, 100);
	//第一个字符是空串，空树
	if (str[0] == ' ') {
		return NULL;
	}
	BiTNode *tree = NULL;
	recursion(tree, str);
	return tree;
}

/*
	先序遍历二叉树
*/
static void preOrderIterator(BiTNode *tree) {
	if (tree == NULL) {
		return;
	}
	printf("%c", tree->data);
	//左子树
	preOrderIterator(tree->lchild);
	//右子树
	preOrderIterator(tree->rchild);
}

int main(void) {
	BiTNode *tree = createBinaryTree();
	printf("构造完成:\n");
	preOrderIterator(tree);

	getchar();
	return 0;
}