#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NODE {
	int data;
	struct NODE *left;
	struct NODE *right;
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

void preorder(NODE *p) {
	if (p == NULL) return;
	else {
		printf("%d ", p->data);
		preorder(p->left);
		preorder(p->right);
	}
}

void inorder(NODE *p) {
	if (p == NULL) return;
	else {
		inorder(p->left);
		printf("%d ", p->data);
		inorder(p->right);
	}
}

void postorder(NODE *p) {
	if (p == NULL) return;
	else {
		postorder(p->left);
		postorder(p->right);
		printf("%d ", p->data);
	}
}

void Edge(NODE *p, NODE *l, NODE *r, int d) {
	p->data = d;
	p->left = l;
	p->right = r;
}

void id(NODE *p, int d, NODE **idnode) {
	if (p == NULL) return;
	if (p->data == d) {
		(*idnode) = p;
		return;
	}
	else {
		id(p->left, d, idnode);
		id(p->right, d, idnode);
	}
}

void addNode(NODE *p, int a, int b, int c) {
	NODE *l = NULL, *r = NULL;
	if (b != 0) {
		getNode(&l);
		Edge(l, NULL, NULL, b);
	}
	if (c != 0) {
		getNode(&r);
		Edge(r, NULL, NULL, c);
	}
	Edge(p, l, r, a);
}

void rootNode(NODE **r) {
	NODE *tmp = NULL;
	getNode(&tmp);
	tmp->left = NULL;
	tmp->right = NULL;
	(*r) = tmp;
}

void enqueue(TREE **p, TREE **q, NODE *n) {
	TREE *tmp = NULL;
	getTree(&tmp);
	tmp->n = n;
	tmp->next = NULL;
	if ((*q) == NULL) (*p) = tmp;
	else (*q)->next = tmp;
	(*q) = tmp;
}

void dequeue(TREE **p, TREE **q, NODE **n) {
	TREE *tmp = NULL;
	tmp = (*p);
	(*n) = tmp->n ;
	(*p) = (*p)->next;
	if ((*p) == NULL) (*q) = NULL;
	free(tmp);
}

void levelorder(NODE *root) {
	TREE *p = NULL, *q = NULL;
	NODE *tmp = NULL;
	enqueue(&p, &q, root);
	while (p != NULL) {
		dequeue(&p, &q, &tmp);
		printf("%d ", tmp->data);
		if(tmp->left != NULL) enqueue(&p, &q, tmp->left);
		if (tmp->right != NULL) enqueue(&p, &q, tmp->right);
	}
}

void main() {
	int a, b, c;
	char t[100];
	NODE *root = NULL, *idnode = NULL;
	while (1) {
		scanf("%d", &a); 
		if (a == -1) break;
		scanf("%d %d", &b, &c); 
		if (root == NULL) {
			rootNode(&root);
			addNode(root, a, b, c);
		}
		else {
			id(root, a, &idnode);
			addNode(idnode, a, b, c);
		}
	}
	while (1) {
		scanf("%s", t); getchar();
		if (strcmp(t, "preorder") == 0) 
			preorder(root);
		else if (strcmp(t, "inorder") == 0) 
			inorder(root);
		else if (strcmp(t, "postorder") == 0) 
			postorder(root);
		else if (strcmp(t, "levelorder") == 0)
			levelorder(root);
		printf("\n");
	}
}