/*
	广义表
*/
#include "GeneralizedList.h"

/*
	初始化、创建广义表
	LIST类型，头指针以及为指针均为NULL
*/
GLNode *initGList() {
	GLNode *list = (GLNode *)malloc(sizeof(GLNode));
	list->tag = LIST;
	list->ptr.hp = NULL;
	list->ptr.tp = NULL;
	return list;
}

/*
	生成测试广义表
	结构如下：
		A
	   / \
	  B   C
	 /     \
	5       D
			 \
			  7
*/
static GLNode *generateGList() {
	//A节点
	GLNode *list = getNode(0, -1);
	//B节点
	GLNode *B = getNode(0, -1);
	list->ptr.hp = B;
	//B节点下的原子节点
	GLNode *bAtom = getNode(1, 5);
	B->ptr.hp = bAtom;

	GLNode *cBoat = getNode(0, -1);
	list->ptr.tp = cBoat;
	//C节点
	GLNode *C = getNode(0, -1);
	cBoat->ptr.hp = C;

	//D节点
	 

}

/*
	生成一个节点
	isAtom为1 --原子节点
*/
static GLNode *getNode(int isAtom, AtomType atom) {
	GLNode *node = (GLNode *)malloc(sizeof(GLNode));
	if (isAtom) {
		node->tag = ATOM;
		node->atom = atom;
	}
	else {
		node->tag = LIST;
		node->ptr.hp = NULL;
		node->ptr.tp = NULL;
	}
	return node;
}

/*
	判断是否为空
	空表就是类型为LIST，同时两个指针都为NULL
*/
static int isEmpty(GLNode *list) {
	return list == NULL || (list->tag == LIST && list->ptr.hp == NULL && list->ptr.tp == NULL);
}

int main(void) {
	GLNode *list = initGList();
	//printf("%d\n", list->tag);

	//测试判空
	//printf("%d\n", isEmpty(list));

	printf("%d", -2 >> 2);

	getchar();
	return 0;
}