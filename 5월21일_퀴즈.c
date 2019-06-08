#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NODE {
	char e[2];
	struct NODE *next;
}NODE;

typedef struct NODE2 {
	char e[2];
	struct NODE2 *left;
	struct NODE2 *right;
}NODE2;

void getNode(NODE **p) {
	(*p) = (NODE *)malloc(sizeof(NODE));
}

void getNode2(NODE **p) {
	(*p) = (NODE2 *)malloc(sizeof(NODE2));
}

void add(NODE *p, int r, char e[]) {
	NODE *tmp = NULL;
	getNode(&tmp);
	for (int i = 1; i < r; i++) {
		p = p->next;
	}
	strcpy(tmp->e ,e);
	tmp->next = p->next;
	p->next = tmp;
}

void del(NODE *p, int r) {
	NODE *tmp = NULL;
	for (int i = 1; i < r; i++) {
		p = p->next;
	}
	tmp = p->next;
	p->next = tmp->next;
	free(tmp);
}

void set(NODE *p, int r, char e[]) {

	for (int i = 0; i < r; i++) {
		p = p->next;
	}
	strcpy(p->e, e);
}

void prt(NODE *p) {
	p = p->next;
	while (p->next != NULL) {
		printf("%s ", p->e);
		p = p->next;
	}
	printf("\n");
}

char *maxN(NODE *p) {
	if ((p->next)->next == NULL) {
		return p->e;
	}
	else {
		if (strlen(maxN(p->next)) > strlen(p->e)) return maxN(p->next);
		else if (strlen(maxN(p->next)) < strlen(p->e)) return p->e;
		else if ((strcmp(maxN(p->next), p->e) > 0 )) return maxN(p->next);
		else return p->e;
	}
}

void preorder(NODE2 *a) {
	if (a != NULL) {
		printf("%s ", a->e);
		preorder(a->left);
		preorder(a->right);
	}
}
void postorder(NODE2 *a) {
	if (a != NULL) {
		postorder(a->left);
		postorder(a->right);
		printf("%s ", a->e);
	}
}

void levelorder(NODE2 *a, NODE2 *b, NODE *t, int *r) {
	if (a != NULL) {
		if (a == b) {
			printf("%s ", a->e);
			add(t, *r, a->e);
			(*r)++;
		}
		if (a->left != NULL) {
			printf("%s ", (a->left)->e);
			add(t, *r, (a->left)->e);
			(*r)++;
		}
		if (a->right != NULL) {
			printf("%s ", (a->right)->e);
			add(t, *r, (a->right)->e);
			(*r)++;
		}
		levelorder(a->left, b, t, r);
		levelorder(a->right, b, t, r);
	}
	return r;
}

void edge(NODE2 *node, NODE2 *left, NODE2 *right, char e[]) {
	strcpy(node->e, e);
	node->left = left;
	node->right = right;
}

void tree(NODE *p, NODE *h) {
	NODE2 *a, *b, *c, *d, *e, *f;
	int r = 1;
	getNode2(&a);
	getNode2(&b);
	getNode2(&c);
	getNode2(&d);
	getNode2(&e);
	getNode2(&f);
	p = p->next;
	edge(a, b, c, p->e);
	p = p->next;
	edge(b, d, e, p->e);
	p = p->next;
	edge(c, f, NULL, p->e);
	p = p->next;
	edge(d, NULL, NULL, p->e);
	p = p->next;
	edge(e, NULL, NULL, p->e);
	p = p->next;
	edge(f, NULL, NULL, p->e);
	preorder(a); printf("\n");
	postorder(a); printf("\n");
	levelorder(a, a, h, &r); printf("\n");
}


void main() {
	NODE *H = NULL, *T = NULL;
	getNode(&H);
	getNode(&T);
	H->next = T;
	T->next = NULL;
	NODE *h = NULL, *t = NULL;
	getNode(&h);
	getNode(&t);
	h->next = t;
	t->next = NULL;
	char a[5], e[2];
	int r;
	while (1) {
		scanf("%s", a); getchar();
		if (strcmp(a, "add") == 0) {
			scanf("%d %s", &r, &e); getchar();
			add(H, r, e);
		}
		else if (strcmp(a, "del") == 0) {
			scanf("%d", &r);
			del(H, r);
		}
		else if (strcmp(a, "set") == 0) {
			scanf("%d %s", &r, &e); getchar();
			set(H, r, e);
		}
		else if (strcmp(a, "prt") == 0) {
			prt(H);
		}
		else if (strcmp(a, "maxN") == 0) {
			printf("%s\n", maxN(H->next));
		}
		else if (strcmp(a, "tree") == 0) {
			tree(H, h);
			H = h;
		}
	}
}
/*
add 1 z
add 1 h
add 1 g
add 1 f
add 1 e
add 1 d
add 1 c
add 1 b
add 1 a
prt
*/