/*
	�����ͷ�ļ�
*/
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

#define OK 1

#define FALSE 0

#define TRUE 1

/*
	���������
	ԭ�ӽڵ�Ϊ0
	�ӱ� --1
*/
typedef enum {
	ATOM, LIST
} EleTag;

/*
	ԭ����������Ϊint
*/
typedef int AtomType;

/*
	������������
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