#include <stdio.h>
#include <string.h>
#include <string.h>

typedef struct NODE {
	char num[100];
	struct NODE *r;
	struct NODE *l;
}NODE;

typedef struct TREE {
	NODE *n;
	struct TREE *next;
}TREE;

void getNode(NODE **p) {
	(*p) = (NODE *)malloc(sizeof(NODE));
}

void getTree(TREE **p) {
	(*p) = (TREE *)malloc(sizeof(TREE));
}

void inject(TREE **p, TREE **q, NODE *n) {
	TREE *tmp = NULL;
	getTree(&tmp);
	tmp->n = n;
	tmp->next = NULL;
	if (*q == NULL) *p = tmp;
	else (*q)->next = tmp;
	*q = tmp;
}

void pop(TREE **p, TREE **q, NODE **n) {
	TREE *tmp = NULL;
	tmp = *p;
	*n = tmp->n;
	(*p) = (*p)->next;
	if (*p == NULL) *q = NULL;
	free(tmp);
}

void levelorder(NODE *root) {
	TREE *p = NULL, *q = NULL;
	NODE *n = NULL;
	inject(&p, &q, root);
	while (p != NULL) {
		pop(&p, &q, &n);
		if (strcmp(n->num, "0") != 0) {
			printf(" %s", n->num);
		}
		if(n->l != NULL)inject(&p, &q, n->l);
		if(n->r != NULL)inject(&p, &q, n->r);
	}
}
void Edge(NODE *p, NODE *r, NODE *l, char *n) {
	p->l = l;
	p->r = r;
	strcpy(p->num, n);
}

void preorder(NODE *p) {
	if (p == NULL) return;
	else {
		if (strcmp(p->num, "0")!= 0) {
			printf(" %s", p->num);
		}
		preorder(p->l);
		preorder(p->r);
	}
}

void inorder(NODE *p) {
	if (p == NULL) return;
	else {
		inorder(p->l);
		if (strcmp(p->num, "0") != 0) {
			printf(" %s", p->num);
		}
		inorder(p->r);
	}
}

void postorder(NODE *p) {
	if (p == NULL) return;
	else {
		postorder(p->l);
		postorder(p->r);
		if (strcmp(p->num, "0") != 0) {
			printf(" %s", p->num);
		}
	}
}

void id(NODE *p, char *num, NODE **idnode) {
	if (p == NULL) return;
	if (strcmp(p->num, num) == 0) {
		(*idnode) = p;
		return;
	}
	else {
		id(p->l, num, idnode);
		id(p->r, num, idnode);
	}
}

void addNode(NODE *root, char *a, char *b, char *c) {
	NODE *r = NULL, *l = NULL;
	getNode(&r); getNode(&l);
	Edge(root, r, l, a);
	Edge(l, NULL, NULL, b);
	Edge(r, NULL, NULL, c);
}

void rootNode(NODE **root) {
	NODE *tmp = NULL;
	getNode(&tmp);
	tmp->l = NULL;
	tmp->r = NULL;
	(*root) = tmp;
}

void mm(char a[3][100], char *t) {
	int n;
	n = strlen(t);
	int l = 0;
	for (int j = 0; j <= n; j++) {
		if (t[j] == ' ') {
			t[j] = '\0';
			strcpy(a[l], t);
			strcpy(t, t + j + 1);
			n = strlen(t);
			l++;
			j = -1;
		}
		else if (t[j] == '\0') {
			strcpy(a[l], t);
		}
	}
}
void main() {
	NODE *root = NULL, *idnode = NULL;
	int N, n, l = 0;
	char t[100], a[3][100];
	scanf("%d", &N); getchar();
	for (int i = 0; i < N; i++) {
		gets(t);
		mm(a, t);
		if (root == NULL) {
			rootNode(&root);
			addNode(root, a[0], a[1], a[2]);
		}
		else {
			id(root, a[0], &idnode);
			addNode(idnode, a[0], a[1], a[2]);
		}
	}
	while (1) {
		scanf("%s", t); getchar();
		if (strcmp(t, "pre") == 0) preorder(root); 
		else if (strcmp(t, "in") == 0) inorder(root);
		else if (strcmp(t, "post") == 0) postorder(root);
		else if (strcmp(t, "level") == 0) levelorder(root);
		printf("\n");
	}
}
