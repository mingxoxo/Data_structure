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

void push(NODE **p, char e, int n) {
	NODE *tmp = NULL;
	getNode(&tmp);
	tmp->next = (*p);
	tmp->data = e;
	tmp->num = n;
	(*p) = tmp;
}

char pop(NODE **p) {
	NODE *tmp = NULL;
	char e;
	getNode(&tmp);
	tmp = (*p);
	e = tmp->data;
	(*p) = (*p)->next;
	free(tmp);
	return e;
}

int top(NODE *p) {
	return p->num;
}

int number(char e, char i, int j) {
	if ((e == '!' || e == '+' || e == '-') && j == 0) return 6;
	else if ((e == '!' || e == '+' || e == '-') && !('A' <= i && i <= 'Z') && (i != '(' && i != ')')) return 6;
	else if (e == '*' || e == '/') return 5;
	else if (e == '+' || e == '-') return 4;
	else if (e == '>' || e == '<') return 3;
	else if (e == '&' && i == '&') return 2;
	else if (e == '|' && i == '|') return 1;
	else return -1;
}

void main() {
	int N, cnt = 0, tmp, num;
	char t[101], re[101] = { 0 };
	NODE *p = NULL;
	scanf("%d", &N); getchar();
	for (int j = 0; j < N; j++) {
		cnt = 0;
		scanf("%s", t); getchar();
		for (int i = 0; i < strlen(t); i++) {
			if ('A' <= t[i] && t[i] <= 'Z') {
				re[cnt] = t[i]; cnt++;
			}
			else if (t[i] == '(') push(&p, '(', 0);
			//괄호일때 ( 를 스택에 넣기
			else if (t[i] == ')') {
				while (top(p) != 0) {
					tmp = top(p);
					re[cnt] = pop(&p); cnt++;
					if (tmp == 2 || tmp == 1) {//&&이나 ||
						re[cnt] = re[cnt - 1]; cnt++;
					}
				}
				pop(&p); // '(' 삭제
			}
			else {
				num = number(t[i], t[i - 1], i); //t[i]의 순위
				if (num == -1) continue;
				else if (p == NULL) push(&p, t[i], num); //비교대상없음
				else {
					tmp = top(p);
					while (tmp >= num) { //우선순위 높으면 꺼내기
						if (tmp == 0) {//괄호 만나면 멈추기
							break;
						}
						re[cnt] = pop(&p); cnt++;
						if (tmp == 2 || tmp == 1) {//&&이나 ||
							re[cnt] = re[cnt - 1]; cnt++;
						}
						if (p == NULL) break;
						tmp = top(p);
					}
					push(&p, t[i], num);
				}
			}
		}
		while (p != NULL) {
			tmp = top(p);
			re[cnt] = pop(&p); cnt++;
			if (tmp == 2 || tmp == 1) {//&&이나 ||
				re[cnt] = re[cnt - 1]; cnt++;
			}
		}
		re[cnt] = '\0';
		printf("%s\n", re);
	}
}