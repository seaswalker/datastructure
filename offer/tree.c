//�ؽ�������
#include <stdio.h>

//����������ڵ�
typedef struct {
	int value;
	//������
	struct BinaryTreeNode *left;
	//������
	struct BinaryTreeNode *right;
}BinaryTreeNode;

//����һ���µĶ������ڵ�
static BinaryTreeNode* createNode() {
	BinaryTreeNode *node = (BinaryTreeNode*) malloc(sizeof(BinaryTreeNode));
	node->value = 0;
	node->left = NULL; 
	node->right = NULL;
	return node;
}

/**
 *�ݹ鹹�������
 * startPreOrder: ��������Ŀ�ʼָ��
 * endPreOrder: �����������Ľ���ָ��
 * startInOrder: �����������Ŀ�ʼָ��
 * endInOrder: �����������Ľ���ָ��
*/ 
static BinaryTreeNode* construct(int *startPreOrder, int *endPreOrder, int *startInOrder, int *endInOrder) {
	//���ڵ��ֵ

	int rootValue = *startPreOrder;
	//�������ڵ�
	BinaryTreeNode *root = createNode();
	root->value = rootValue;
	//����������ӽڵ�
	if(startPreOrder == endPreOrder) {
		return root;
	}
	//�����������ҵ�root��ֵ
	int *rootInOrder = startInOrder;
	while(rootInOrder <= endInOrder && *rootInOrder != rootValue) {
		rootInOrder ++;
	}
	//�������Ľڵ���Ŀ
	int leftLength = rootInOrder - startInOrder;
	//��һ�ι�����̵��������н���λ��
	int *leftEndPreOrder = startPreOrder + leftLength;
	if(leftLength > 0) {
		//����������
		root->left = construct(startPreOrder + 1, leftEndPreOrder, startInOrder, rootInOrder - 1);
	}
	//��������������ڵ�
	if(leftLength < endPreOrder - startPreOrder) {
		root->right = construct(leftEndPreOrder + 1, endPreOrder, rootInOrder + 1, endInOrder);
	}
	return root;
}

//�������������
static void preOrderVisit(BinaryTreeNode *tree) {
	if(tree != NULL) {
		printf("%d ", tree->value);
		//����������
		preOrderVisit(tree->left);
		//������
		preOrderVisit(tree->right);
	}
}

int main(void) {
	//������������
	int preOrder[] = {1, 2, 4, 7, 3, 5, 6, 8};
	//����������
	int inOrder[] = {4, 7 ,2 ,1, 5, 3 ,8, 6};
	BinaryTreeNode* tree = construct(preOrder, preOrder + 7, inOrder, inOrder + 7);
	printf("������ɣ�����������:\n");
	preOrderVisit(tree);
	return 0;
}



