/*
	�����
*/
#include "GeneralizedList.h"

/*
	��ʼ�������������
	LIST���ͣ�ͷָ���Լ�Ϊָ���ΪNULL
*/
GLNode *initGList() {
	GLNode *list = (GLNode *)malloc(sizeof(GLNode));
	list->tag = LIST;
	list->ptr.hp = NULL;
	list->ptr.tp = NULL;
	return list;
}

/*
	���ɲ��Թ����
	�ṹ���£�
		A
	   / \
	  B   C
	 /     \
	5       D
			 \
			  7
*/
static GLNode *generateGList() {
	//A�ڵ�
	GLNode *list = getNode(0, -1);
	//B�ڵ�
	GLNode *B = getNode(0, -1);
	list->ptr.hp = B;
	//B�ڵ��µ�ԭ�ӽڵ�
	GLNode *bAtom = getNode(1, 5);
	B->ptr.hp = bAtom;

	GLNode *cBoat = getNode(0, -1);
	list->ptr.tp = cBoat;
	//C�ڵ�
	GLNode *C = getNode(0, -1);
	cBoat->ptr.hp = C;

	//D�ڵ�
	 

}

/*
	����һ���ڵ�
	isAtomΪ1 --ԭ�ӽڵ�
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
	�ж��Ƿ�Ϊ��
	�ձ��������ΪLIST��ͬʱ����ָ�붼ΪNULL
*/
static int isEmpty(GLNode *list) {
	return list == NULL || (list->tag == LIST && list->ptr.hp == NULL && list->ptr.tp == NULL);
}

int main(void) {
	GLNode *list = initGList();
	//printf("%d\n", list->tag);

	//�����п�
	//printf("%d\n", isEmpty(list));

	printf("%d", -2 >> 2);

	getchar();
	return 0;
}