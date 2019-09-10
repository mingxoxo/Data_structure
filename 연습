#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE{
	struct NODE *prev;
	struct NODE *next;
	char data;
}NODE;

void getNode(NODE **p){
	(*p) = (NODE *)malloc(sizeof(NODE));
}

void push(NODE **p, char e){
	NODE *tmp = NULL;
	getNode(&tmp);
	tmp->data = e;
	tmp->next = (*p);
	tmp->prev = NULL;
	if((*p) != NULL){
		(*p)->prev = tmp;
	}
	(*p) = tmp;
}

void pop(NODE **p){
	NODE *tmp = NULL;
	tmp = (*p);
	(*p) = (*p)->next;
	(tmp->next)->prev = NULL;
	free(tmp);
}

void top(NODE *p){
	printf("%c\n", p->data);
}

void print(NODE *p){
	while(p!= NULL){
		printf("%c ", p->data);
		p = p->next;
	}
	printf("\n");
}
void main(){
	NODE *p = NULL;
	char str[100];
	char e;
	while(1){
		scanf("%s", str); getchar();
		if(strcmp(str, "push") == 0){
			scanf("%c", &e);getchar();
			push(&p, e);
		}
		else if(strcmp(str, "pop") == 0){
			pop(&p);
		}
		else if(strcmp(str, "top") == 0){
			top(p);
		}
		else if(strcmp(str, "print") == 0){
			print(p);
		}
	}
}
