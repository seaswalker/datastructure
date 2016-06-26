#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//����ṹ��
typedef struct DuLNode {
    int data;
    struct DuLNode *pre;
    struct DuLNode *next;
} DuLNode;

//��¼�������ֵľ���ֵ�Ĵ�С��ϵ��1��ʾ��һ������
int bigger = 1;
//��¼�������ĳ���(��������)
int resultLength = 0;

//���ݸ�����data����һ���ڵ�
static DuLNode* createNode(int data) {
    DuLNode *node = (DuLNode*) malloc(sizeof(DuLNode));
    node->data = data;
    node->pre = NULL;
    node->next = NULL;
    return node;
}

//����������ת��Ϊ����ڵ�
//1,0000,3456,4322
static DuLNode* number2Node(char *number) {
    if(number != NULL) {
        //����ͷ��㣬ͷ���ʹ��1��-1��ʾ���ֵ�����
        DuLNode *head = createNode(1);
        DuLNode *node;
        DuLNode *cur = head;
        //��������ʼλ��
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

//��ӡ����������
static void printList(DuLNode *list) {
    if(list != NULL) {
        DuLNode *node = list->next;
        if(list->data < 0) {
            printf("-");
        }
        //������ŵĸ����Լ�λ��
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
 * [insertBefore �ڽ�������е������һ���ڵ�]
 * @param data [�ڵ��ֵ]
 * @param ptrR [��������ָ��]
 */
static DuLNode* insertBefore(int data, DuLNode *ptrR) {
    DuLNode *node = createNode(data);
    ptrR->pre = node;
    node->next = ptrR;
    return node;
}

/**
 * [_arithmetic �������������]
 * @param first ��һ������
 * @param second �ڶ�������
 * @param operation ��ȡһ�Խڵ�������
 * @return ����������
 */
static DuLNode* arithmetic(DuLNode *first, DuLNode *second, int (*operation)()) {
    DuLNode *resultList = createNode(1);
    DuLNode *ptrR = resultList;
    DuLNode *node;
    DuLNode *ptrF = first->pre;
    DuLNode *ptrS = second->pre;
    //��λ
    int add = 0;
    while(ptrF != first && ptrS != second) {
        ptrR = operation(ptrF, ptrS, ptrR, &add);       
        ptrF = ptrF->pre;
        ptrS = ptrS->pre;
        resultLength ++;
    }
    //����ʣ��ڵ�
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
 * [plusOperation �ӷ�����]
 * @param  ptrF ptrS [��������ĵ�ǰָ��]
 * @param ptrR �������λ��ָ��
 * @param  add  [��λ��ָ��]
 * @return      [����]
 */
static DuLNode* plusOperation(DuLNode *ptrF, DuLNode *ptrS, DuLNode *ptrR, int *add) {
    int fData = ptrF == NULL ? 0 : ptrF->data;
    int sData = ptrS == NULL ? 0 : ptrS->data;
    int result = fData + sData + *add;
    *add = result > 9 ? result / 10 : 0;
    return insertBefore(result % 10, ptrR);
}

/**
 * [subOperation ��������]
 */
static int subOperation(DuLNode *ptrF, DuLNode *ptrS, DuLNode *ptrR, int *add) {
    //������
    int minuend = 0;
    //����
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
 * [removeZero ȥ����ͷ���㣬���ڼ�������]
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

//ִ�мӷ�����
static void plus(DuLNode *first, DuLNode *second) {
    if(first == NULL || second == NULL) {
        return;
    }
    //����������
    DuLNode *resultList;
    //�����������ͬ��
    if(first->data * second->data > 0) {
        resultList = arithmetic(first, second, plusOperation);
        resultList->data = first->data > 0 ? 1 : -1;
    }else if(first->data < 0) {
        //��һ�������Ǹ�
        resultList = arithmetic(first, second, subOperation);
        resultList->data = bigger == 1 ? -1 : 1;
        removeZero(resultList);
    }else {
        //�ڶ��������Ǹ���
        resultList = arithmetic(first, second, subOperation);
        resultList->data = bigger == 1 ? 1 : -1;
        removeZero(resultList);
    }
    printf("������Ϊ:\n");
    printList(resultList);
}

/**
 * [setBigger ��¼�ĸ�������]
 */
static void setBigger(char *first, char *second, int firstLength, int secondLength) {
    if(firstLength != secondLength) {
        bigger = (secondLength > firstLength) ? 2 : 1;
    }else {
        bigger = strcmp(first, second) < 0 ? 2 : 1;
    }
}

/**
 * [getNumberLength ��ȡһ���ַ����в��������ŵĸ���]
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
 * [check ����û��������ʽ�Ƿ�Ϸ�]
 * @param  first        [��һ����]
 * @param  second       [�ڶ�����]
 * @param  firstLength  [����Ϸ���˳�����first���ĳ���]
 * @param  secondLength [second�ĳ���]
 * @return              [����Ϸ�������1������0]
 */
static int check(char *first, char *second, int *firstLength, int *secondLength) {
    int lengthF = strlen(first);
    int startF = 0;
    int endF = lengthF;
    if(first[0] == '-') {
        lengthF --;
        startF = 1;
    }
    //first�Ķ�������
    int commaNumF = ceil(getNumberLength(first) / 4.0) - 1;
    //����λ������
    int commaFIndexes[commaNumF];
    //��λ��ǰ
    for(int i = 0;i < commaNumF;i ++) {
        commaFIndexes[i] = endF - 1 - (4 + 5 * (commaNumF - i - 1));
    }
    int index = 0;
    //У��first
    for(int i = startF;i < endF;i ++) {
        //�����λ��Ӧ���Ƕ���
        if(commaNumF > 0 && i == commaFIndexes[index]) {
            if(first[i] != ',') {
                return 0;
            }
            index ++;
        }else {
            //������0-9������
            if(first[i] < '0' || first[i] > '9') {
                return 0;
            }
        }
    }
    //firstУ��ͨ��
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
    //У��second
    index = 0;
    for(int i = startS;i < endS;i ++) {
        //�����λ��Ӧ���Ƕ���
        if(commaNumS > 0 && i == commaSIndexes[index]) {
            if(second[i] != ',') {
                return 0;
            }
            index ++;
        }else {
            //������0-9������
            if(second[i] < '0' || second[i] > '9') {
                return 0;
            }
        }
    }
    *secondLength = lengthS;
    return 1;
}

//��ʾ�������
static void display() {
    char first[100];
    char second[100];
    while(1) {
        printf("----------------------------���ⳤ�����ӷ�����:--------------------\n");
        printf("-----------------------------����0�˳�ϵͳ:-----------------------\n");
        printf("�������һ�����ⳤ����,ÿ��λ��,�ָ�:\n");
        scanf("%s", first);
        if(strcmp(first, "0") == 0) {
            break;
        }
        printf("������ڶ������ⳤ����,ÿ��λ��,�ָ�:\n");
        scanf("%s", second);
        int firstLength = 0;
        int secondLength = 0;
        if(check(first, second, &firstLength, &secondLength) == 0) {
            printf("������ĸ�ʽ��������������!\n");
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
