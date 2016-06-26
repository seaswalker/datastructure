#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//记录的最大数量设为50
#define NOTESMAXSIZE 50

/**
 * 一条记录
 */
typedef struct {
	//学生id
	int id;
	char *name;
	//房号
	int roomNo;
} Note;

char dataPath[] = "D:\\C\\C-free\\projects\\Design\\data.txt";
//记录数量
int notesCount = 0;
//原始顺序记录数组
Note *originNotes[NOTESMAXSIZE];
//按id升序排列的数组
Note *idOrderNotes[NOTESMAXSIZE];
//按学生姓名排序的数组
Note *nameOrderNotes[NOTESMAXSIZE];
//房间号升序数组
Note *roomNoOrderNotes[NOTESMAXSIZE];

/**
 * [removeCR 如果所给的字符串以回车结尾，那么去掉]
 * @param str [需要处理的字符串]
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
 * [split 把所给的字符串按照空格分割为3部分]
 * @param p 3维指针数组 第一个元素为id， 第二个为姓名，第三个为宿舍号
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
 * [createNote 根据所给参数建立结构体]
 * @param  id     [学生id]
 * @param  name    [学生姓名]
 * @param  roomNo [宿舍号]
 * @return        [记录指针]
 */
static Note* createNote(int id, char *name, int roomNo) {
	Note *note = (Note*) malloc(sizeof(Note));
	note->id = id;
	note->name = name;
	note->roomNo = roomNo;
	return note;
}

/**
 * [str2Note 把一条记录转化为Note结构体]
 * 文件中记录的格式为1 skywalker 336(学号 姓名 宿舍号)
 * @param str [description]
 * @return 返回记录指针
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
 * [_initNotes 建立三个排序数组]
 * 冒泡排序
 * @param destArray 需要操作的目标数组
 * @param compare 用于排序的比较函数
 */
static void _initNotes(Note *destArray[], int (*compare)()) {
	//最小元素的下标
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
 * [compareInt 比较两个记录的id的大小]
 * @return   [如果noteA->id < noteB->id, 返回负数]
 */
static int compareId(Note *noteA, Note *noteB) {
	return noteA->id - noteB->id;
}

/**
 * [initIdOrderNotes 初始化按id排序的数组]
 */
static void initIdOrderNotes() {
	_initNotes(idOrderNotes, compareId);
}

/**
 * [compareRoomNo 比较两个记录的宿舍号的大小]
 * @return       [如果noteA比noteB小，返回负值]
 */
static int compareRoomNo(Note *noteA, Note *noteB) {
	return noteA->roomNo - noteB->roomNo;
}

/**
 * [initRoomNoNotes 初始化按宿舍号排序的数组]
 */
static void initRoomOrderNoNotes() {
	_initNotes(roomNoOrderNotes, compareRoomNo);
}

/**
 * [compareName 字典顺序比较姓名]
 */
static int compareName(Note *noteA, Note *noteB) {
	return strcmp(noteA->name, noteB->name);
}

/**
 * [initNameOrderNotes 初始化按姓名排序数组]
 */
static void initNameOrderNotes() {
	_initNotes(nameOrderNotes, compareName);
}

/**
 * [printNoteArray 打印记录数组]
 */
static void printNoteArray(Note *array[]) {
	if(array != NULL) {
		Note *note;
		for(int i = 0;i < notesCount;i ++) {
			note = array[i];
			printf("ID:%d 姓名:%s 宿舍号:%d\n", note->id, note->name, note->roomNo);
		}
	}
}

/**
 * [loadData 从本地文件加载记录]
 */
static void loadData() {
	printf("正在读取记录, 请稍候...\n");
	FILE *file;
	file = fopen(dataPath, "r");
	if(file == NULL) {
		printf("文件打开失败\n");
	}else {
		char line[1024];
		Note *note;
		while(!feof(file)) {
			fgets(line, 1024, file);
			removeCR(line);
			//建立原始记录数组
			note = str2Note(line);
			if(note != NULL) {
				originNotes[notesCount ++] = note;
			}
		}
		fclose(file);
		initIdOrderNotes();
		initRoomOrderNoNotes();
		initNameOrderNotes();
		printf("数据加载完成\n");
	}
}

/**
 * [binarySearch 二分查找函数]
 * @param array被查找的数组
 * @param compare 比较函数
 * @param begin 开始的位置
 * @param end 结束的位置
 * @param searched 被搜索的记录, 此参数的目的是方便直接使用compareXXX函数
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
 * [searchById 按学号查询]
 */
static void searchById() {
	int id = 0;
	printf("请输入您要查询的学号:\n");
	scanf("%d", &id);
	Note *searched = createNote(id, NULL, 0);
	Note *result = binarySearch(idOrderNotes, compareId, 0, notesCount - 1, searched);
	if(result == NULL) {
		printf("没有此记录!\n");
	}else {
		printf("已找到一条记录:\n");
		printf("学号:%d, 姓名:%s, 宿舍:%d\n", result->id, result->name, result->roomNo);
	}
}

/**
 * [searchByRoomNo 按宿舍号搜索]
 */
static void searchByRoomNo() {
	int roomNo = 0;
	printf("请输入您要查询的宿舍号:\n");
	scanf("%d", &roomNo);
	Note *searched = createNote(0, NULL, roomNo);
	Note *result = binarySearch(roomNoOrderNotes, compareRoomNo, 0, notesCount - 1, searched);
	if(result == NULL) {
		printf("没有此记录!\n");
	}else {
		printf("已找到一条记录:\n");
		printf("学号:%d, 姓名:%s, 宿舍:%d\n", result->id, result->name, result->roomNo);
	}
}

/**
 * [searchByName 根据姓名搜索]
 */
static void searchByName() {
	char name[30];
	printf("请输入您要查询的姓名:\n");
	scanf("%s", name);
	Note *searched = createNote(0, name, 0);
	Note *result = binarySearch(nameOrderNotes, compareName, 0, notesCount - 1, searched);
	if(result == NULL) {
		printf("没有此记录!\n");
	}else {
		printf("已找到一条记录:\n");
		printf("学号:%d, 姓名:%s, 宿舍:%d\n", result->id, result->name, result->roomNo);
	}
}

/**
 * [display 显示交互界面]
 */
static void display() {
	int operationCode = 0;
	while(1) {
		printf("--------------------------------请选择查询方式:---------------------\n");
		printf("-------------1.按姓名查询  2.按学号查询  3.按房号查询  0.退出-------\n");
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
