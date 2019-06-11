#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NODE {
	char data;
	int num;
	struct NODE *next;
}NODE;


void getNode(NODE **p) {
	(*p) = (NODE *)malloc(sizeof(NODE));
}

void push(NODE **p, char data, int num) {
	NODE *tmp = NULL;
	getNode(&tmp);
	tmp->num = num;
	tmp->data = data;
	tmp->next = (*p);
	(*p) = tmp;
}

char pop(NODE **p) {
	char e;
	NODE *tmp = NULL;
	tmp = (*p);
	e = tmp->data;
	(*p) = (*p)->next;
	free(tmp);
	return e;
}

int top(NODE *p) {
	return p->num;
}

int number(char e) {
	if (e == '*') return 2;
	else if (e == '+' || e == '-') return 1;
	else return -1;
}

int re(char *a) {
	NODE *p = NULL;
	int num = 0, j = 0, n1 = 0, n2 = 0;
	char e[100];
	for (int i = 0; i < strlen(a); i++) {
		j = 0;
		if ('0' <= a[i] && a[i] <= '9') {
			while (a[i] != ' ') {
				e[j] = a[i]; i++; j++;
			}
			e[j] = '\0';
			push(&p, NULL, atoi(e));
		}
		else if (a[i] == '*') {
			n2 = top(p); pop(&p);
			n1 = top(p); pop(&p);
			push(&p, NULL, n1*n2);
		}
		else if (a[i] == '+') {
			n2 = top(p); pop(&p);
			n1 = top(p); pop(&p);
			push(&p, NULL, n1+n2);
		}
		else if (a[i] == '-') {
			n2 = top(p); pop(&p);
			n1 = top(p); pop(&p);
			push(&p, NULL, n1-n2);
		}
	}
	num = top(p); pop(&p);
	return num;
}

void main() {
	NODE *p = NULL;
	int c = 0, topn, num;
	int result = 0;
	char t[101], a[101];
	while (1) {
		scanf("%s", t);
		c = 0;
		for (int i = 0; i < strlen(t); i++) {
			if ('0' <= t[i] && t[i] <= '9') {
				a[c] = t[i]; c++;
				if ('0' > t[i + 1] && t[i + 1] < '9') {
					a[c] = ' '; c++;
				}
			}
			else if (t[i] == '(') {
				push(&p, '(', 0);
			}
			else if (t[i] == ')') {
				topn = top(p);
				while (topn != 0) {
					a[c] = pop(&p); c++;
					topn = top(p);
				}
				pop(&p);
			}
			else {
				num = number(t[i]);
				if (p == NULL) {
					push(&p, t[i], num);
				}
				else {
					topn = top(p);
					while (topn >= num) {
						a[c] = pop(&p); c++;
						if (p == NULL) break;
						topn = top(p);
						if (topn == 0) break;
					}
					push(&p, t[i], num);
				}
			}
		}
		while (p != NULL) {
			a[c] = pop(&p); c++;
		}
		a[c] = '\0';
		result = re(a);
		if(result < 0){
			printf("%06d\n", result);
		}
		else if (result > 0) {
			printf("+%05d\n", result);
		}
		else printf("%05d\n", result);
	}
}

/*input example
1+2+3+4+5+6+7+8+9-9*2-8-9-7-6-5-6-7-8-9-0
(1+3)*(1+5)+6-7*(1-9-5-7)+5*5-9*9-(1+1*3-5)+1
11*2+2*2-13*2+4*2-5*2+16*2-7*2+8*2-9*12+9*2+2*16
11*2+(2*2-13*2)+4*2-5*2+16*2-7*2+8*2-9*(12+9*2+2*16)
11111+112*3-(5-10*10)+1+4-3333+(8*8-25)*27 */
