#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
	int data;
	struct NODE *next;
}NODE;

void getNode(NODE **list) {
	*list = (NODE *)malloc(sizeof(NODE));
}

void addNode(NODE *H, int n) {
	NODE *tmp = NULL;
	getNode(&tmp);
	tmp->data = n;
	tmp->next = H->next;
	H->next = tmp;
}

void printNode(NODE *H) {
	H = H->next;
	while (H->next != NULL) {
		printf("%d ", H->data);
		H = H->next;
	}
	printf("\n");
}

void sort(NODE *H) {
	NODE *a = NULL, *b = NULL;
	int tmp;
	a = H->next;
	while (a->next != NULL) {
		b = a->next;
		while (b->next != NULL) {
			if (a->data > b->data) {
				tmp = a->data;
				a->data = b->data;
				b->data = tmp;
			}
			b = b->next;
		}
		a = a->next;
	}
}
void main() {
	char a[100], n[6], c[6];
	int cnt = 0;
	NODE *H = NULL, *T = NULL, *tmp = NULL;
	getNode(&H);
	getNode(&T);
	H->next = T;
	T->next = NULL;
	tmp = H;
	while (1) {
		scanf("%s", a);
		getchar();
		if (strcmp(a, "add") == 0) {
			scanf("%s", n);
			getchar();
			cnt = 0;
			for (int i = 0; i < strlen(n); i++) {
				if ('0' <= n[i] && n[i] <= '9') {
					c[cnt] = n[i];
					cnt++;
				}
			}
			c[cnt] = '\0';
			addNode(tmp, atoi(c));
			tmp = tmp->next;
			
		}
		if (strcmp(a, "prt") == 0) {
			printNode(H);
		}
		if (strcmp(a, "sort") == 0) {
			sort(H);
			printNode(H);
		}
	}
}