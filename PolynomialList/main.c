#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct ListNode {
	int coef;
	int expon;
	struct ListNode* link;
}ListNode;

typedef struct ListType {
	int size;
	ListNode* head;
	ListNode* tail;
}ListType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	return;
}

ListType* creat() {
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

void insert_last(ListType* plist, int coef, int expon) {
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL) error("Memory ");
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;
	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++;
}

void poly_add(ListType* plist1, ListType* plist2, ListType* plist3) {
	ListNode* a = plist1->head;
	ListNode* b = plist2->head;
	int sum;

	while (a != NULL && b != NULL) {
		if (a->expon == b->expon) {
			sum = a->coef + b->coef;
			if (sum != 0)insert_last(plist3, sum, a->expon);
			a = a->link; b = b->link;
		}
		else if (a->expon > b->expon) {
			insert_last(plist3, a->coef, a->expon);
			a = a->link;
		}
		else {
			insert_last(plist3, b->coef, b->expon);
			b = b->link;
		}
	}
	for (; a != NULL; a = a->link)
		insert_last(plist3, a->coef, a->expon);
	for (; b != NULL; b = b->link)
		insert_last(plist3, b->coef, b->expon);
}

void poly_print(ListType* plist)
{
	ListNode* p = plist->head;
	printf("polynomial = ");
	while (p) {
		if (p->link) {
			printf("%dx%d + ", p->coef, p->expon);
		}
		else {
			printf("%dx%d", p->coef, p->expon);
		}
		p = p->link;
	}
	printf("\n");
}


void poly_input(ListType* plist, char poly[]) {
	int coef = 0, expon = 0;
	int sign = 1;
	int i = 0;

	while (poly[i] != '\0') {
		if (poly[i] == '-' || poly[i] == '+') {
			sign = (poly[i] == '-') ? -1 : 1;
			i++;
		}
		coef = 0;
		expon = 0;

		while (isdigit((unsigned char)poly[i])) {
			coef = coef * 10 + (poly[i] - '0');
			i++;
		}
		coef *= sign;

		if (poly[i] == 'x') {
			i++;
			while (isdigit((unsigned char)poly[i])) {
				expon = expon * 10 + (poly[i] - '0');
				i++;
			}
		}
		insert_last(plist, coef, expon);
	}
}

int main() {
	ListType* list1, * list2, * list3;
	char poly1[MAX_SIZE], poly2[MAX_SIZE];

	list1 = creat();
	list2 = creat();
	list3 = creat();

	printf("Enter the first polynomial: ");
	scanf_s("%s", poly1, MAX_SIZE);
	poly_input(list1, poly1);

	printf("Enter the second polynomial: ");
	scanf_s("%s", poly2, MAX_SIZE);
	poly_input(list2, poly2);

	poly_add(list1, list2, list3);
	poly_print(list3);

	free(list1);
	free(list2);
	free(list3);

	return 0;
}