/*
 * list.c
 *
 *  Created on: 2015Äê10ÔÂ13ÈÕ
 *      Author: skywalker
 */

#include "stdio.h"
#include "malloc.h"

typedef struct node {
	int value;
	struct node *next;
} List;

List* createList() {
	List* head = (List*) malloc(sizeof(List));
	head->value = 0;
	head->next = NULL;
	return head;
}

void appendTail(List* list, int value) {
	if (list != NULL) {
		List* node = list;
		while (node->next != NULL) {
			node = node->next;
		}
		List* newNode = (List*) malloc(sizeof(List));
		newNode->value = value;
		newNode->next = NULL;
		node->next = newNode;
	}
}

int deleteTail(List* list, int value) {
	if (list != NULL) {
		List* node = list;
		List* pre = NULL;
		while (node != NULL && node->value != value) {
			pre = node;
			node = node->next;
		}
		if (node != NULL) {
			pre->next = node->next;
			free(node);
			return 1;
		}
	}
	return -1;
}

void printList(List* list) {
	if (list != NULL) {
		List* node = list->next;
		while (node != NULL) {
			printf("%d ", node->value);
		}
	}
}

//²âÊÔ
int main(void) {
	List* list = createList();
	appendTail(list, 1);
	appendTail(list, 2);
	appendTail(list, 3);
	appendTail(list, 4);
	appendTail(list, 5);
	appendTail(list, 6);
	printList(list);
	return 0;
}


