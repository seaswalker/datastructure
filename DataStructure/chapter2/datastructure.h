
#define ERROR -1

#define OK 1

#define FALSE 0

#define TRUE 1

//定义数据结构用到的类型
typedef int boolean;
//定义所谓的ElemType
typedef int ElemType;
//定义线性表数据类型
typedef struct {
	//首元素
	ElemType *ele;
	//长度
	int length;
	//容量
	int listsize;
}List;

//定义链表
typedef struct {
	//实际值
	ElemType data;
	struct LNode *next;
}LNode;

//定义双向链表类型
typedef struct DuLNode {
	ElemType data;
	struct DuLNode *pre;
	struct DuLNode *next;
}DuLNode;

//声明公共函数
List* initList();
void printfList(List *list);
int compare(ElemType e1, ElemType e2);
int locate(List *list, ElemType e, int(*compare)());
int insert(List *list, ElemType e, int index);
void assginment(List *list);