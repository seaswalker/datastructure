//二叉排序树，使用的树和课本227页相比多了一个101节点
//2015年6月3日 17:07:20
#include <stdio.h>

#define ERROR -1

//使用二叉链表作为存储结构
typedef struct {
	int value;
	struct BSTTree* left;
	struct BSTTree* right;
} BSTTree;

//搜索结果，如果没有找到，cur和parent相同，都是最后一个节点
//发现一个问题，只有引用自己类型的时候需要加struct，否则不需要
typedef struct {
	//搜索结果，找到了为1，否则为0
	int resultCode;
	//结果所在的节点
	BSTTree* cur;
	//所在节点的父节点
	BSTTree* parent;
} SearchResult;

//函数声明
static int insert(BSTTree* tree, int value);

static BSTTree* createTreeNode() {
	BSTTree* node = (BSTTree*) malloc(sizeof(BSTTree));
	node->value = 0;
	node->left = NULL;
	node->right = NULL;
	return node;
}

static SearchResult* createSearchResult() {
	SearchResult* result = (SearchResult*) malloc(sizeof(SearchResult));
	result->resultCode = 0;
	result->cur = NULL;
	result->parent = NULL;
	return result;
}

//求出数组的长度
static int getLength(int array[]) {
	if(array == NULL) {
		return ERROR;
	}
	int length = 0;
	while(array[length] != '\0') {
		length ++;
	}
	return length;
} 

/* 
 添加孩子节点
 isLeft 1代表左子树
 parent 父节点 
 返回新的节点
*/
static BSTTree* appendChild(BSTTree* parent, int isLeft, int value) {
	BSTTree* node = createTreeNode();
	node->value = value;
	if(parent != NULL) {
		if(isLeft) {
			parent->left = node;
		}else {
			parent->right = node;
		}
	}
	return node;
}

//创建一棵二叉排序树
static BSTTree* createBSTTREE() {
	//使用insert方法生成排序二叉树(只需说明root元素，数组的第一个元素即为root元素)
	//一个很恶心的问题，就是数组最后加个\0
	int array[] = {45, 12, 53, 3, 37, 100, 101, 24, 61, 90, 78, '\0'};
	//根节点
	BSTTree* root = createTreeNode();
	root->value = 45;
	int length = getLength(array);
	for(int i = 1;i < length;i ++) {
		insert(root, array[i]);
	}
	return root;
}

//排序二叉树遍历 ==>> 先序
static void visit(BSTTree* tree) {
	if(tree != NULL) {
		printf("%d ", tree->value);
		visit(tree->left);
		visit(tree->right);
	}
}

//搜索
static void searchBST(BSTTree* tree, int value, SearchResult* result) {
	if(tree != NULL) {
		if(tree->value == value) {
			result->cur = tree;
			result->resultCode = 1;
		}else if(tree->value > value) {
			result->parent = tree;
			searchBST(tree->left, value, result);
		}else {
			result->parent = tree;
			searchBST(tree->right, value, result);
		}
	}
}

//向二叉树中插入，仅在原树中不存在此记录时执行插入
static int insert(BSTTree* tree, int value) {
	if(tree == NULL) {
		printf("The tree cant't NULL!");
		return ERROR;
	}
	SearchResult* result = createSearchResult();
	searchBST(tree, value, result);
	if(result->resultCode == 1) {
		return 0;
	}else {
		BSTTree* node = createTreeNode();
		node->value = value;
		if(result->parent->value > value) {
			//建立左子树
			result->parent->left = node;
		}else if(result->parent->value < value) {
			//建立右子树
			result->parent->right = node;
		} 
		return 1;
	}
}

//比较两个节点是否相等
static int _compare(BSTTree* nodeA, BSTTree* nodeB) {
	if(nodeA == NULL && nodeB == NULL) {
		return 1;
	}else if(nodeA == NULL || nodeB == NULL) {
		return 0;
	}else if(nodeA->value == nodeB->value){
		return 1;
	}else {
		return 0;
	}
}

//在树中删除节点，返回0，没有此节点，1删除成功
static int deleteNode(BSTTree* tree, int value) {
	if(tree == NULL) {
		printf("The tree cant't NULL!\n");
		return ERROR;
	}
	SearchResult* result = createSearchResult();
	searchBST(tree, value, result);
	if(result->resultCode == 0) {
		printf("There is no node found to be deleted\n");
		return 0;
	}
	//找到节点,并且是父节点的左子树
	BSTTree* temp = NULL;
	if(_compare(result->cur, result->parent->left)) {
		//左右子树都为空，只需要改变父节点
		if(result->cur->left == NULL && result->cur->right == NULL) {
			result->parent->left = NULL;
			free(result->cur);
		}else if(result->cur->left == NULL){
			temp = result->cur;
			result->parent->left = temp->right;
			free(temp);
		}else if(result->cur->right == NULL) {
			temp = result->cur;
			result->parent->left = temp->left;
			free(temp);
		}else {
			//左右子树都不为空，左子树直接变为父节点的左子树，右子树变为被删除节点的左子树的右子树尽头的右节点
			temp = result->cur->left;
			while(temp->right) {
				temp = temp->right;
			}
			temp->right = result->cur->right;
			temp = result->cur;
			result->parent->left = result->cur->left;
			free(temp);
		}
	}else {
		//是父节点的右子树
		//左右子树都为空，只需要改变父节点
		if(result->cur->left == NULL && result->cur->right == NULL) {
			result->parent->right = NULL;
			free(result->cur);
		}else if(result->cur->left == NULL){
			temp = result->cur;
			result->parent->right = temp->right;
			free(temp);
		}else if(result->cur->right == NULL) {
			temp = result->cur;
			result->parent->right = temp->left;
			free(temp);
		}else {
			//左右子树都不为空，右子树直接变为父节点的右子树，左子树变为被删除节点的右子树的左子树尽头的左节点，和上面的相反
			temp = result->cur->right;
			while(temp->left) {
				temp = temp->left;
			}
			temp->left = result->cur->left;
			temp = result->cur;
			result->parent->right = result->cur->right;
			free(temp);
		}
	}
	printf("delete success!\n");
	return 1;
}

int main(void) {
	BSTTree* tree = createBSTTREE();
	printf("The tree created as fllow:\n");
	visit(tree);
	printf("\n");
	
	//搜索
	/* printf("Please input the number that you want to find...:\n");
	int number = 0;
	scanf("%d", &number);
	SearchResult* result = createSearchResult();
	searchBST(tree, number, result);
	if(result->resultCode == 0) {
		printf("there is no result found");
	}else {
		printf("has found:%d", result->cur->value);
	} */
	
	//测试插入
	/* int result = insert(tree, 3);
	if(result) {
		printf("insert performed, and the new tree is :\n");
		visit(tree);
	}else {
		printf("the value which is found has already existed\n");
	} */
	
	//测试删除
	printf("Please input the number you want to delete:\n");
	int number = 0;
	scanf("%d", &number);
	deleteNode(tree, number);
	visit(tree);
	
	return 0;
}
