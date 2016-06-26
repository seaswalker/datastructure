/*
	广义表头文件
*/
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

#define OK 1

#define FALSE 0

#define TRUE 1

/*
	广义表类型
	原子节点为0
	子表 --1
*/
typedef enum {
	ATOM, LIST
} EleTag;

/*
	原子类型数据为int
*/
typedef int AtomType;

/*
	定义广义表类型
*/
typedef struct GLNode {
	EleTag tag;
	union
	{
		AtomType atom;
		struct {
			struct GLNode * hp, *tp;
		}ptr;
	};
}GLNode;