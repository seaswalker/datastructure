
#define ERROR -1

#define OK 1

#define FALSE 0

#define TRUE 1

//�������ݽṹ�õ�������
typedef int boolean;
//������ν��ElemType
typedef int ElemType;
//�������Ա���������
typedef struct {
	//��Ԫ��
	ElemType *ele;
	//����
	int length;
	//����
	int listsize;
}List;

//��������
typedef struct {
	//ʵ��ֵ
	ElemType data;
	struct LNode *next;
}LNode;

//����˫����������
typedef struct DuLNode {
	ElemType data;
	struct DuLNode *pre;
	struct DuLNode *next;
}DuLNode;

//������������
List* initList();
void printfList(List *list);
int compare(ElemType e1, ElemType e2);
int locate(List *list, ElemType e, int(*compare)());
int insert(List *list, ElemType e, int index);
void assginment(List *list);