#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//union ÇÕÁýÇÕ

typedef struct NODE {
	int data;
	struct NODE *left;
	struct NODE *right;
}NODE;

void getNode(NODE **tmp) {
	*tmp = (NODE *)malloc(sizeof(NODE));
}

void push(NODE **front, NODE **rear) {
	NODE *tmp = NULL;
	int a;
	getNode(&tmp);
	scanf("%d", &a);
	tmp->data = a;
	tmp->left = NULL;
	if ((*rear) == NULL) {
		(*rear) = tmp;
	}
	tmp->right = (*front);
	(*front) = tmp;
}

void inject(NODE **front, NODE **rear, int a) {
	NODE *tmp = NULL;

	getNode(&tmp);

	tmp->data = a;
	tmp->right = NULL;
	if ((*front) == NULL) {
		(*front) = tmp;
	}
	else (*rear)->right = tmp;
	tmp->left = (*rear);
	(*rear) = tmp;
}

void pop(NODE **front, NODE **rear) {
	NODE *tmp = NULL;
	tmp = (*front);
	if ((*front) == (*rear)) {
		*rear = NULL;
		*front = NULL;
	}
	else {
		*front = (*front)->right;
		(*front)->left = NULL;
	}
	free(tmp);
}

void eject(NODE **front, NODE **rear) {
	NODE *tmp = NULL;
	tmp = (*rear);
	if (*front == *rear) {
		*rear = NULL;
		*front = NULL;
	}
	else {
		*rear = (*rear)->left;
		(*rear)->right = NULL;
	}
	free(tmp);
}

void prt(NODE *front) {
	NODE *tmp = NULL;
	tmp = front;
	while ((tmp->right) != NULL) {
		printf("%d ", tmp->data);
		tmp = tmp->right;
	}
	printf("%d\n", tmp->data);
}

int maxN(NODE *front) {
	if ((front->right) == NULL) {
		return front->data;
	}
	else {
		if (maxN(front->right) < front->data) {
			return  front->data;
		}
	}
}

void sort(NODE *front, NODE *rear) {
	NODE *i = NULL, *j = NULL;
	int tmp;
	i = front;
	while (i != rear) {
		j = i->right;
		while (j != NULL) {
			if (i->data > j->data) {
				tmp = i->data;
				i->data = j->data;
				j->data = tmp;
			}
			j = j->right;
		}
		i = i->right;
	}
}

void unionn(NODE *front) {
	NODE *fronta = NULL, *reara = NULL, *k = NULL;
	char c[1000], b[1000];
	int i = 0, cnt = 0, j = 0;
	gets(b);
	i = 0;
	while ('1' <= b[i] && b[i] <= '9') {
		j = 0;
		while ('1' <= b[i] && b[i] <= '9') {
			c[j] = b[i];
			j++;
			i++;
		}
		c[j] = '\0';
		k = front;
		cnt = 0;
		while (k != NULL) {
			if (atoi(c) == k->data) {
				cnt++;
				break;
			}
			k = k->right;
		}
		if (cnt == 0) {
			inject(&fronta, &reara, atoi(c));
		}
		//if ('1' <= b[i] && b[i] <= '9') break;
		i++;
	}
	k = front;
	while (k != NULL) {
		inject(&fronta, &reara, k->data);
		k = k->right;
	}
	sort(fronta, reara);
	prt(fronta);
}
void main() {
	NODE *front = NULL, *rear = NULL;
	int aa;
	char a[10];
	int d[100];
	int i = 0, j = 0, cnt = 0, l = 0;
	while (1) {
		scanf("%s", a); getchar();
		if (strcmp(a, "push") == 0) {
			push(&front, &rear);
		}
		else if (strcmp(a, "inject") == 0) {
			scanf("%d", &aa);
			inject(&front, &rear, aa);
		}
		else if (strcmp(a, "pop") == 0) {
			pop(&front, &rear);
		}
		else if (strcmp(a, "eject") == 0) {
			eject(&front, &rear);
		}
		else if (strcmp(a, "prt") == 0) {
			prt(front);
		}
		else if (strcmp(a, "maxN") == 0) {
			printf("%d\n", maxN(front));
		}
		else if (strcmp(a, "sort") == 0) {
			sort(front, rear);
			prt(front);
		}
		else if (strcmp(a, "union") == 0) {
			unionn(front);
		}
	}
}
/*inject 77
push 11
push 55
inject 33
inject 44
push 22
inject 66
prt*/