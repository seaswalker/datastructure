//重建二叉树
#include <stdio.h>

//定义二叉树节点
typedef struct {
	int value;
	//左子树
	struct BinaryTreeNode *left;
	//右子树
	struct BinaryTreeNode *right;
}BinaryTreeNode;

//建立一个新的二叉树节点
static BinaryTreeNode* createNode() {
	BinaryTreeNode *node = (BinaryTreeNode*) malloc(sizeof(BinaryTreeNode));
	node->value = 0;
	node->left = NULL; 
	node->right = NULL;
	return node;
}

/**
 *递归构造二叉树
 * startPreOrder: 先序遍历的开始指针
 * endPreOrder: 先序遍历结果的结束指针
 * startInOrder: 中序遍历结果的开始指针
 * endInOrder: 中序遍历结果的结束指针
*/ 
static BinaryTreeNode* construct(int *startPreOrder, int *endPreOrder, int *startInOrder, int *endInOrder) {
	//根节点的值

	int rootValue = *startPreOrder;
	//创建根节点
	BinaryTreeNode *root = createNode();
	root->value = rootValue;
	//如果不存在子节点
	if(startPreOrder == endPreOrder) {
		return root;
	}
	//在中序结果中找到root的值
	int *rootInOrder = startInOrder;
	while(rootInOrder <= endInOrder && *rootInOrder != rootValue) {
		rootInOrder ++;
	}
	//左子树的节点数目
	int leftLength = rootInOrder - startInOrder;
	//下一次构造过程的先序序列结束位置
	int *leftEndPreOrder = startPreOrder + leftLength;
	if(leftLength > 0) {
		//构造左子树
		root->left = construct(startPreOrder + 1, leftEndPreOrder, startInOrder, rootInOrder - 1);
	}
	//如果还有右子树节点
	if(leftLength < endPreOrder - startPreOrder) {
		root->right = construct(leftEndPreOrder + 1, endPreOrder, rootInOrder + 1, endInOrder);
	}
	return root;
}

//先序遍历二叉树
static void preOrderVisit(BinaryTreeNode *tree) {
	if(tree != NULL) {
		printf("%d ", tree->value);
		//遍历左子树
		preOrderVisit(tree->left);
		//右子树
		preOrderVisit(tree->right);
	}
}

int main(void) {
	//先序遍历结果：
	int preOrder[] = {1, 2, 4, 7, 3, 5, 6, 8};
	//中序遍历结果
	int inOrder[] = {4, 7 ,2 ,1, 5, 3 ,8, 6};
	BinaryTreeNode* tree = construct(preOrder, preOrder + 7, inOrder, inOrder + 7);
	printf("构造完成，先序遍历结果:\n");
	preOrderVisit(tree);
	return 0;
}



