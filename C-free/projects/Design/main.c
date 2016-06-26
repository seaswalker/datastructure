#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//��¼�����������Ϊ50
#define NOTESMAXSIZE 50

/**
 * һ����¼
 */
typedef struct {
	//ѧ��id
	int id;
	char *name;
	//����
	int roomNo;
} Note;

char dataPath[] = "D:\\C\\C-free\\projects\\Design\\data.txt";
//��¼����
int notesCount = 0;
//ԭʼ˳���¼����
Note *originNotes[NOTESMAXSIZE];
//��id�������е�����
Note *idOrderNotes[NOTESMAXSIZE];
//��ѧ���������������
Note *nameOrderNotes[NOTESMAXSIZE];
//�������������
Note *roomNoOrderNotes[NOTESMAXSIZE];

/**
 * [removeCR ����������ַ����Իس���β����ôȥ��]
 * @param str [��Ҫ������ַ���]
 */
static void removeCR(char *str) {
	if(str != NULL) {
		int length = strlen(str);
		if(str[length - 1] == '\n' || str[length - 1] == '\r\n') {
			str[length - 1] = '\0';
		}
	}
}

/**
 * [split ���������ַ������տո�ָ�Ϊ3����]
 * @param p 3άָ������ ��һ��Ԫ��Ϊid�� �ڶ���Ϊ������������Ϊ�����
 */
static void split(char *str, char *p[3]) {
	if(str != NULL) {
		char *buf;
		int index = 0;
		for(int i = 0;i < 3;i ++) {
			buf = (char *) malloc(sizeof(char) * 20);
			int j = 0;
			char c;
			c = (i == 0 ? str[index] : str[++ index]);
			while(c != ' ' && c != '\0') {
				buf[j ++] = c;
				c = str[++ index];
			}
			buf[j] = '\0';
			p[i] = buf;
		}
	}
}

/**
 * [createNote �����������������ṹ��]
 * @param  id     [ѧ��id]
 * @param  name    [ѧ������]
 * @param  roomNo [�����]
 * @return        [��¼ָ��]
 */
static Note* createNote(int id, char *name, int roomNo) {
	Note *note = (Note*) malloc(sizeof(Note));
	note->id = id;
	note->name = name;
	note->roomNo = roomNo;
	return note;
}

/**
 * [str2Note ��һ����¼ת��ΪNote�ṹ��]
 * �ļ��м�¼�ĸ�ʽΪ1 skywalker 336(ѧ�� ���� �����)
 * @param str [description]
 * @return ���ؼ�¼ָ��
 */
static Note* str2Note(char *str) {
	if(str != NULL) {
		char *eles[3];
		split(str, eles);
		return createNote(atoi(eles[0]), eles[1], atoi(eles[2]));
	}
	return NULL;
}

/**
 * [_initNotes ����������������]
 * ð������
 * @param destArray ��Ҫ������Ŀ������
 * @param compare ��������ıȽϺ���
 */
static void _initNotes(Note *destArray[], int (*compare)()) {
	//��СԪ�ص��±�
	int min = 0;
	int index = 0;
	Note *temp;
	for(int i = 0;i < notesCount;i ++) {
		min = i;
		for(int j = i + 1;j < notesCount;j ++) {
			if(compare(originNotes[j], originNotes[min]) < 0) {
				min = j;
			}
		}
		destArray[index ++] = originNotes[min];
		temp = originNotes[min];
		originNotes[min] = originNotes[i];
		originNotes[i] = temp;
	}
}

/**
 * [compareInt �Ƚ�������¼��id�Ĵ�С]
 * @return   [���noteA->id < noteB->id, ���ظ���]
 */
static int compareId(Note *noteA, Note *noteB) {
	return noteA->id - noteB->id;
}

/**
 * [initIdOrderNotes ��ʼ����id���������]
 */
static void initIdOrderNotes() {
	_initNotes(idOrderNotes, compareId);
}

/**
 * [compareRoomNo �Ƚ�������¼������ŵĴ�С]
 * @return       [���noteA��noteBС�����ظ�ֵ]
 */
static int compareRoomNo(Note *noteA, Note *noteB) {
	return noteA->roomNo - noteB->roomNo;
}

/**
 * [initRoomNoNotes ��ʼ������������������]
 */
static void initRoomOrderNoNotes() {
	_initNotes(roomNoOrderNotes, compareRoomNo);
}

/**
 * [compareName �ֵ�˳��Ƚ�����]
 */
static int compareName(Note *noteA, Note *noteB) {
	return strcmp(noteA->name, noteB->name);
}

/**
 * [initNameOrderNotes ��ʼ����������������]
 */
static void initNameOrderNotes() {
	_initNotes(nameOrderNotes, compareName);
}

/**
 * [printNoteArray ��ӡ��¼����]
 */
static void printNoteArray(Note *array[]) {
	if(array != NULL) {
		Note *note;
		for(int i = 0;i < notesCount;i ++) {
			note = array[i];
			printf("ID:%d ����:%s �����:%d\n", note->id, note->name, note->roomNo);
		}
	}
}

/**
 * [loadData �ӱ����ļ����ؼ�¼]
 */
static void loadData() {
	printf("���ڶ�ȡ��¼, ���Ժ�...\n");
	FILE *file;
	file = fopen(dataPath, "r");
	if(file == NULL) {
		printf("�ļ���ʧ��\n");
	}else {
		char line[1024];
		Note *note;
		while(!feof(file)) {
			fgets(line, 1024, file);
			removeCR(line);
			//����ԭʼ��¼����
			note = str2Note(line);
			if(note != NULL) {
				originNotes[notesCount ++] = note;
			}
		}
		fclose(file);
		initIdOrderNotes();
		initRoomOrderNoNotes();
		initNameOrderNotes();
		printf("���ݼ������\n");
	}
}

/**
 * [binarySearch ���ֲ��Һ���]
 * @param array�����ҵ�����
 * @param compare �ȽϺ���
 * @param begin ��ʼ��λ��
 * @param end ������λ��
 * @param searched �������ļ�¼, �˲�����Ŀ���Ƿ���ֱ��ʹ��compareXXX����
*/
static Note *binarySearch(Note *destArray[], int (*compare)(), int begin, int end, Note* searched) {
	if(end < begin) {
		return NULL;
	}
	int middle = (end - begin) / 2 + begin;
	int compareResult = compare(destArray[middle], searched);
	if(compareResult == 0) {
		return destArray[middle];
	}else if(compareResult > 0) {
		return binarySearch(destArray, compare, begin, middle - 1, searched);
	}else {
		return binarySearch(destArray, compare, middle + 1, end, searched);
	}
}

/**
 * [searchById ��ѧ�Ų�ѯ]
 */
static void searchById() {
	int id = 0;
	printf("��������Ҫ��ѯ��ѧ��:\n");
	scanf("%d", &id);
	Note *searched = createNote(id, NULL, 0);
	Note *result = binarySearch(idOrderNotes, compareId, 0, notesCount - 1, searched);
	if(result == NULL) {
		printf("û�д˼�¼!\n");
	}else {
		printf("���ҵ�һ����¼:\n");
		printf("ѧ��:%d, ����:%s, ����:%d\n", result->id, result->name, result->roomNo);
	}
}

/**
 * [searchByRoomNo �����������]
 */
static void searchByRoomNo() {
	int roomNo = 0;
	printf("��������Ҫ��ѯ�������:\n");
	scanf("%d", &roomNo);
	Note *searched = createNote(0, NULL, roomNo);
	Note *result = binarySearch(roomNoOrderNotes, compareRoomNo, 0, notesCount - 1, searched);
	if(result == NULL) {
		printf("û�д˼�¼!\n");
	}else {
		printf("���ҵ�һ����¼:\n");
		printf("ѧ��:%d, ����:%s, ����:%d\n", result->id, result->name, result->roomNo);
	}
}

/**
 * [searchByName ������������]
 */
static void searchByName() {
	char name[30];
	printf("��������Ҫ��ѯ������:\n");
	scanf("%s", name);
	Note *searched = createNote(0, name, 0);
	Note *result = binarySearch(nameOrderNotes, compareName, 0, notesCount - 1, searched);
	if(result == NULL) {
		printf("û�д˼�¼!\n");
	}else {
		printf("���ҵ�һ����¼:\n");
		printf("ѧ��:%d, ����:%s, ����:%d\n", result->id, result->name, result->roomNo);
	}
}

/**
 * [display ��ʾ��������]
 */
static void display() {
	int operationCode = 0;
	while(1) {
		printf("--------------------------------��ѡ���ѯ��ʽ:---------------------\n");
		printf("-------------1.��������ѯ  2.��ѧ�Ų�ѯ  3.�����Ų�ѯ  0.�˳�-------\n");
		scanf("%d", &operationCode);
		switch(operationCode) {
			case 0:
				printf("Exiting...\n");
				exit(0);
				break;
			case 1:
				searchByName();
				break;
			case 2:
				searchById();
				break;
			case 3:
				searchByRoomNo();
				break;
		}
	}
}

int main(void) {
	loadData();
	display();

	getchar();
	return 0;
}
