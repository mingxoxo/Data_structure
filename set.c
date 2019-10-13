#include <stdio.h> //header없는 list , remove를 사용했기 때문에 한번 돌리면 원래 list에 아무것도 없음
#include <string.h>
#include <stdlib.h>

typedef struct NODE {
	int data;
	struct NODE *next;
}NODE;

void getNode( NODE **p) {
	(*p) = (NODE *)malloc(sizeof(NODE));
}

void addLast(NODE **list, int data) {
	NODE *tmp = NULL, *t = (*list);
	getNode(&tmp);
	tmp->data = data;
	tmp->next = NULL;
	if ((*list) == NULL) {
		(*list) = tmp;
		return;
	}
	while (t->next != NULL) t = t->next;
	t->next = tmp;
}

void removeFirst(NODE **list) {
	NODE *tmp = NULL;
	tmp = (*list);
	if (tmp == NULL) return;
	(*list) = (*list)->next;
	free(tmp);
}

int get(NODE *list) {
	return list->data;
}

NODE **unionSet(NODE **A, NODE **B) {
	NODE *C = NULL;
	int a = 0, b = 0;
	while ((*A) != NULL && (*B) != NULL) {
		a = get(*A);
		b = get(*B);
		if (a > b) {
			addLast(&C, b);
			removeFirst(B);
		}
		else if (a < b) {
			addLast(&C, a);
			removeFirst(A);
		}
		else if (a == b) {
			addLast(&C, a);
			removeFirst(A);
			removeFirst(B);
		}
	}
	while ((*A) != NULL) {
		addLast(&C, get(*A));
		removeFirst(A);
	}
	while ((*B) != NULL) {
		addLast(&C, get(*B));
		removeFirst(B);
	}
	return &C;
}

NODE **intersect(NODE **A, NODE **B) {
	NODE *C = NULL;
	int a = 0, b = 0;
	while ((*A) != NULL && (*B) != NULL) {
		a = get(*A);
		b = get(*B);
		printf("%d %d\n", a, b);
		if (a > b) {
			removeFirst(B);
		}
		else if (a < b) {
			removeFirst(A);
		}
		else if (a == b) {
			addLast(&C, a);
			removeFirst(A);
			removeFirst(B);
		}
	}
	while ((*A) != NULL) {
		removeFirst(A);
	}
	while ((*B) != NULL) {
		removeFirst(B);
	}
	return &C;
}

void printset(NODE *list) {
	while (list != NULL) {
		printf(" %d", list->data);
		list = list->next;
	}
	printf("\n");
}
void main() {
	NODE *A = NULL, *B = NULL, *U = NULL, *I = NULL;
	int n, i, data;
	scanf("%d", &n);
	if(n == 0) addLast(&A, 0);
	for (i = 0; i < n; i++) {
		scanf("%d", &data);
		addLast(&A, data);
	}
	scanf("%d", &n);
	if (n == 0) addLast(&B, 0);
	for (i = 0; i < n; i++) {
		scanf("%d", &data);
		addLast(&B, data);
	}
	U = *(unionSet(&A, &B));
	I = *(intersect(&A, &B));

	printset(U);
	printset(I);
}
