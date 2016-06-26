#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//定义结构体
typedef struct DuLNode {
    int data;
    struct DuLNode *pre;
    struct DuLNode *next;
} DuLNode;

//记录两个数字的绝对值的大小关系，1表示第一个更大
int bigger = 1;
//记录运算结果的长度(不含负号)
int resultLength = 0;

//根据给定的data创建一个节点
static DuLNode* createNode(int data) {
    DuLNode *node = (DuLNode*) malloc(sizeof(DuLNode));
    node->data = data;
    node->pre = NULL;
    node->next = NULL;
    return node;
}

//把两个数字转化为链表节点
//1,0000,3456,4322
static DuLNode* number2Node(char *number) {
    if(number != NULL) {
        //创建头结点，头结点使用1或-1表示数字的正负
        DuLNode *head = createNode(1);
        DuLNode *node;
        DuLNode *cur = head;
        //遍历的起始位置
        int start = 0;
        if(number[0] == '-') {
            start = 1;
            head->data = -1;
        }
        char c;
        for(int i = start;(c = number[i]) != '\0';i ++) {
            if(c != ',') {
                node = createNode(c - '0');
                cur->next = node;
                node->pre = cur;
                cur = node;
            }
        }
        cur->next = head;
        head->pre = cur;
        return head;
    }
    return NULL;
}

//打印出整个链表
static void printList(DuLNode *list) {
    if(list != NULL) {
        DuLNode *node = list->next;
        if(list->data < 0) {
            printf("-");
        }
        //结果逗号的个数以及位置
        int resultCommaNum = ceil(resultLength / 4.0) - 1;
        resultLength += resultCommaNum;
        int resultCommas[resultCommaNum];
        for(int i = 0;i < resultCommaNum;i ++) {
            resultCommas[i] = resultLength - 1 - (4 + 5 * (resultCommaNum - i - 1));
        }
        int index = 0;
        int i = 0;
        while(node != list) {
            if(resultCommaNum > 0 && i == resultCommas[index]) {
                printf(",");
                printf("%d", node->data);
                index ++;
                i ++;
            }else {
                printf("%d", node->data);
            }
            node = node->next;
            i ++;
        }
        printf("\n");
    }
}

/**
 * [insertBefore 在结果链表中倒序插入一个节点]
 * @param data [节点的值]
 * @param ptrR [结果链表的指针]
 */
static DuLNode* insertBefore(int data, DuLNode *ptrR) {
    DuLNode *node = createNode(data);
    ptrR->pre = node;
    node->next = ptrR;
    return node;
}

/**
 * [_arithmetic 真正的运算过程]
 * @param first 第一操作数
 * @param second 第二操作数
 * @param operation 获取一对节点运算结果
 * @return 运算结果链表
 */
static DuLNode* arithmetic(DuLNode *first, DuLNode *second, int (*operation)()) {
    DuLNode *resultList = createNode(1);
    DuLNode *ptrR = resultList;
    DuLNode *node;
    DuLNode *ptrF = first->pre;
    DuLNode *ptrS = second->pre;
    //进位
    int add = 0;
    while(ptrF != first && ptrS != second) {
        ptrR = operation(ptrF, ptrS, ptrR, &add);       
        ptrF = ptrF->pre;
        ptrS = ptrS->pre;
        resultLength ++;
    }
    //处理剩余节点
    while(ptrF != first) {
        ptrR = operation(ptrF, NULL, ptrR, &add);
        ptrF = ptrF->pre;
        resultLength ++;
    }
    while(ptrS != second) {
        ptrR = operation(NULL, ptrS, ptrR, &add);
        ptrS = ptrS->pre;
        resultLength ++;
    }
    if(add != 0) {
        ptrR = insertBefore((add + 10) % 10, ptrR);
        resultLength ++;
    }
    resultList->next = ptrR;
    ptrR->pre = resultList;
}

/**
 * [plusOperation 加法运算]
 * @param  ptrF ptrS [两个链表的当前指针]
 * @param ptrR 结果链表位置指针
 * @param  add  [进位的指针]
 * @return      [返回]
 */
static DuLNode* plusOperation(DuLNode *ptrF, DuLNode *ptrS, DuLNode *ptrR, int *add) {
    int fData = ptrF == NULL ? 0 : ptrF->data;
    int sData = ptrS == NULL ? 0 : ptrS->data;
    int result = fData + sData + *add;
    *add = result > 9 ? result / 10 : 0;
    return insertBefore(result % 10, ptrR);
}

/**
 * [subOperation 减法运算]
 */
static int subOperation(DuLNode *ptrF, DuLNode *ptrS, DuLNode *ptrR, int *add) {
    //被减数
    int minuend = 0;
    //减数
    int subtrahend = 0;
    if(bigger == 1) {
        minuend = ptrF == NULL ? 0 : ptrF->data;
        subtrahend = ptrS == NULL ? 0 : ptrS->data;
    }else {
        subtrahend = ptrF == NULL ? 0 : ptrF->data;
        minuend = ptrS == NULL ? 0 : ptrS->data;
    }
    minuend += *add;
    int result = 0;
    if(minuend < subtrahend) {
        result = 10 - subtrahend + minuend;
        *add = -1;
    }else {
        result = minuend - subtrahend;
        *add = 0;
    }
    return insertBefore(result, ptrR);
}

/**
 * [removeZero 去掉开头的零，用于减法运算]
 */
static void removeZero(DuLNode *list) {
    if(list != NULL) {
        DuLNode *node = list->next;
        DuLNode *temp;
        while(node->data == 0 && node != list->pre) {
            temp = node;
            node = node->next;
            free(temp);
            resultLength --;
        }
        list->next = node;
        node->pre = list;
    }
}

//执行加法操作
static void plus(DuLNode *first, DuLNode *second) {
    if(first == NULL || second == NULL) {
        return;
    }
    //计算结果链表
    DuLNode *resultList;
    //如果两个数字同号
    if(first->data * second->data > 0) {
        resultList = arithmetic(first, second, plusOperation);
        resultList->data = first->data > 0 ? 1 : -1;
    }else if(first->data < 0) {
        //第一个链表是负
        resultList = arithmetic(first, second, subOperation);
        resultList->data = bigger == 1 ? -1 : 1;
        removeZero(resultList);
    }else {
        //第二个链表是负数
        resultList = arithmetic(first, second, subOperation);
        resultList->data = bigger == 1 ? 1 : -1;
        removeZero(resultList);
    }
    printf("运算结果为:\n");
    printList(resultList);
}

/**
 * [setBigger 记录哪个数更大]
 */
static void setBigger(char *first, char *second, int firstLength, int secondLength) {
    if(firstLength != secondLength) {
        bigger = (secondLength > firstLength) ? 2 : 1;
    }else {
        bigger = strcmp(first, second) < 0 ? 2 : 1;
    }
}

/**
 * [getNumberLength 获取一个字符串中不包括逗号的个数]
 */
static int getNumberLength(char *str) {
    int count = 0;
    while(*str != '\0') {
        str ++;
        if(*str != ',') {
            count ++;
        }
    }
    return count;
}

/**
 * [check 检查用户的输入格式是否合法]
 * @param  first        [第一个串]
 * @param  second       [第二个串]
 * @param  firstLength  [如果合法，顺便求出first串的长度]
 * @param  secondLength [second的长度]
 * @return              [如果合法，返回1，否则0]
 */
static int check(char *first, char *second, int *firstLength, int *secondLength) {
    int lengthF = strlen(first);
    int startF = 0;
    int endF = lengthF;
    if(first[0] == '-') {
        lengthF --;
        startF = 1;
    }
    //first的逗号数量
    int commaNumF = ceil(getNumberLength(first) / 4.0) - 1;
    //逗号位置索引
    int commaFIndexes[commaNumF];
    //高位在前
    for(int i = 0;i < commaNumF;i ++) {
        commaFIndexes[i] = endF - 1 - (4 + 5 * (commaNumF - i - 1));
    }
    int index = 0;
    //校验first
    for(int i = startF;i < endF;i ++) {
        //如果此位置应该是逗号
        if(commaNumF > 0 && i == commaFIndexes[index]) {
            if(first[i] != ',') {
                return 0;
            }
            index ++;
        }else {
            //必须是0-9的数字
            if(first[i] < '0' || first[i] > '9') {
                return 0;
            }
        }
    }
    //first校验通过
    *firstLength = lengthF;
    int lengthS = strlen(second);
    int startS = 0;
    int endS = lengthS;
    if(second[0] == '-') {
        lengthS --;
        startS = 1;
    }
    int commaNumS = ceil(getNumberLength(second) / 4.0) - 1;
    int commaSIndexes[commaNumS];
    for(int i = 0;i < commaNumS;i ++) {
        commaSIndexes[i] = endS - 1 - (4 + 5 * (commaNumS - i - 1));
    }
    //校验second
    index = 0;
    for(int i = startS;i < endS;i ++) {
        //如果此位置应该是逗号
        if(commaNumS > 0 && i == commaSIndexes[index]) {
            if(second[i] != ',') {
                return 0;
            }
            index ++;
        }else {
            //必须是0-9的数字
            if(second[i] < '0' || second[i] > '9') {
                return 0;
            }
        }
    }
    *secondLength = lengthS;
    return 1;
}

//显示程序界面
static void display() {
    char first[100];
    char second[100];
    while(1) {
        printf("----------------------------任意长整数加法运算:--------------------\n");
        printf("-----------------------------输入0退出系统:-----------------------\n");
        printf("请输入第一个任意长整数,每四位以,分隔:\n");
        scanf("%s", first);
        if(strcmp(first, "0") == 0) {
            break;
        }
        printf("请输入第二个任意长整数,每四位以,分隔:\n");
        scanf("%s", second);
        int firstLength = 0;
        int secondLength = 0;
        if(check(first, second, &firstLength, &secondLength) == 0) {
            printf("您输入的格式有误，请重新输入!\n");
            continue;
        }
        resultLength = 0;
        setBigger(first, second, firstLength, secondLength);
        DuLNode *firstList = number2Node(first);
        DuLNode *secondList = number2Node(second);
        plus(firstList, secondList);
    }
}

/*
int main(void) {
    display();
    return 0;
}*/
