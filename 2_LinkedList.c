#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode* listPointer;

struct listNode {
	char name[50];	
	int sno;
	float gpa;
	char phone[20];
	char province[30];
	listPointer link;
};

listPointer search_insert_position(listPointer hd, char nm[]) {		// �̸������� �迭
	listPointer pv = NULL;
	int cmp;
	while (1) {
		if (!hd) {	// hd�� NULL�� ��� pv(NULL)�� ����
			return pv;
		}
		else {
			cmp = strcmp(nm, hd->name);	// nm�� hd->name�� ��
			if (cmp <= 0)				// nm�� hd->name�� ���ų� nm�� hd->name���� ���̶�� pv ����
				return pv;
			else {						// nm�� hd->name���� �ڶ�� pv�� hd�� ����� hd�� ��ũ�� ����� hd->link�� ���� (�� �Լ��� ������ nm�� �� �ڸ��� �ճ�尡 pv�� ���ϵǵ��� ����)
				pv = hd;
				hd = hd->link;
			}
		}
	}
}

void IS(listPointer hd, listPointer np) {	// �� �л��� ������ ����
	listPointer prev;
	prev = search_insert_position(hd, np->name);
	if (!prev) {		// prev�� NULL�̶�� 
		np->link = hd;	// np�� link�� hd�� ����Ű�� np�� hd(��ũ�� ����Ʈ�� �� �� head)�� ��
		hd = np;
	}
	else {				// prev�� �����Ѵٸ� 
		np->link = prev->link;	// np�� link�� prev�� ��ũ�� ����Ű�� prev�� link�� np�� �� ( prev�� prev�� ����Ű�� ��ũ���̿� np�� ����(prev - np - prev�� ��ũ�� ����Ű�� ��))
		prev->link = np;
	}
}

void SE(listPointer hd, char nm[]) {	// �� �л� �˻�
	int cmp;
	while (hd) {
		cmp = strcmp(nm, hd->name);		
		if (cmp == 0) {	// nm�� hd->name�� ���ٸ� �ش� �л��� ���� ���
			printf("%s %d %f %s %s\n", hd->name, hd->sno, hd->gpa, hd->phone, hd->province);	
			break;
		}
		else {
			hd = hd->link;
		}
	}
}

void RG(listPointer hd, char nm1[], char nm2[]) {	// �Ϻ��� ���( �� �̸� ���̿� �ִ� ��� �л� ���)
	listPointer prev;
	prev = hd;	// hd�� �������� �ʴ� �̸��� �л��� nm1�� ��� �� ���� �л����� nm2�� ���� �̸��� �л� ��(Ȥ�� �̸������� �տ��ִ�) ���� ����ϱ� ���� �뵵�� ���
	int cmp;
	int checkcount = 1;	// nm1�� ���� �̸��� �ִٸ� 0�� �ǰ� 0���� nm2�� ���� �̸��� �ִٸ� �ݺ������� Ż�� �Ѵ�. ���� 1�� ���·� �ݺ����� �������Դٸ� �� ���� �л����� nm2�� ���� �̸��� ������ �л� ��(Ȥ�� �̸������� �տ��ִ� �л�)���� ����Ѵ�.
	while (hd) {
		if (checkcount == 1) {
			cmp = strcmp(nm1, hd->name);
			if (cmp == 0) {		// �̸��� nm1�� ���ٸ� checkcount�� 0�̵�
				checkcount--;
			}
			hd = hd->link;
		}
		else if (checkcount == 0) {	
			cmp = strcmp(nm2, hd->name);
			if (cmp == 0) {		// �̸��� ���ٸ� �ݺ������� Ż�� �ƴ϶�� ���� �̸� Ȥ�� �̸� ������ ���� �л��� ���� �� ���� ���̿� �ִ� �л� ���� ��� 
				break;
			}
			printf("%s %d %f %s %s\n", hd->name, hd->sno, hd->gpa, hd->phone, hd->province);
			hd = hd->link;
		}
	}
	if (checkcount == 1) {		// nm1�� ���� �̸��� �л��� ���� ���
		while (prev) {
			cmp = strcmp(nm2, prev->name);
			if (cmp <= 0) {		// nm2�� ���ų� �̸� ������ �ڿ� �ִ� �л��� ������ ������ �� ���̿� �ִ� ��� �л� ���� ���
				break;
			}
			printf("%s %d %f %s %s\n", prev->name, prev->sno, prev->gpa, prev->phone, prev->province);
			prev = prev->link;
		}
	}
	
}

void DL(listPointer hd) {	// ���Ḯ��Ʈ�� �� ���� �޸� �л��� ������ ����ϰ� ���� �� �л��� ����
	listPointer pv;
	pv = NULL;

	while (hd->link != NULL) {
		pv = hd;
		hd = hd->link;
	}
	printf("%s %d %f %s %s\n", hd->name, hd->sno, hd->gpa, hd->phone, hd->province);
	pv->link = NULL;
}

void SP(listPointer hd, char phone[]) {	// ��ȭ��ȣ �� �� 4 �ڸ��� �Է¹޾� �̷��� ��ȭ��ȣ�� ���� �л��� ���
	while (hd) {
		if (strcmp(phone, hd->phone + 9) == 0) {
			printf("%s %d %f %s %s\n", hd->name, hd->sno, hd->gpa, hd->phone, hd->province);
			break;
		}
		hd = hd->link;
	}
}

void LO(listPointer hd, char province[]) {	// �������� �Է¹޾Ƽ� �� ���� ����� ��� �л����� ���
	while (hd) {
		if (strcmp(province, hd->province) == 0) {
			printf("%s %d %f %s %s\n", hd->name, hd->sno, hd->gpa, hd->phone, hd->province);
		}
		hd = hd->link;
	}
}

void printList(listPointer first) {	// � �л����� �ִ��� mydata.txt�� �����ִ� �������� ��ũ�帮��Ʈ�� ������ ���·� ������ ���
	printf("The list contains: ");
	for (; first; first = first->link) {
		printf("%s  ", first->name);
		printf("%d  ", first->sno);
		printf("%f  ", first->gpa);
		printf("%s  ", first->phone);
		printf("%s", first->province);
		printf("\n");
	}
}

int main(void) {
	listPointer head, np, prev;
	char command[3];	// ���� ��� ���� ���� Ȯ�ο�
	char name1[50];		// ���Ͽ��� �̸� ���� �Է¿�, ��� ���� �������� ���
	char name2[50];		// ��� ���� ����(RG)���� ���
	int sno1, res;		// ���Ͽ��� �л� ��ȣ �Է¿�, ��� ���� �������� ���
	float gpa1;			// ���Ͽ��� �л� ���� �Է¿�, ��� ���� �������� ���
	char phone1[20];	// ���Ͽ��� �л� �ڵ��� ��ȣ �Է¿�, ��� ���� �������� ���
	char province1[20];	// ���Ͽ��� �л� ��� �Է¿�, ��� ���� �������� ���

	head = NULL;
	np   = NULL;
	prev = NULL;

	FILE* fp;
	fp = fopen("mydata.txt", "r");

	while (1) {
		res = fscanf(fp, "%s %d %f %s %s", name1, &sno1, &gpa1, phone1, province1);

		if (res < 5) {	// ������ ������ �� �޾Ƶ����� ���߰ų� ������ ������ ������ ���
			break;
		}
		
		np = (listPointer)malloc(sizeof(struct listNode));
		strcpy(np->name, name1);	// ���Ͽ��� �޾Ƶ��� ������� np�� ����
		np->sno = sno1;
		np->gpa = gpa1;
		strcpy(np->phone, phone1);
		strcpy(np->province, province1);
		
		
		prev = search_insert_position(head,name1);	
		if (!prev) {			// prev�� NULL�̶�� nd�� ��ũ�帮��Ʈ���� ���� �� ��� �� head�� ��
			np->link = head;
			head = np;
		}
		else {					// prev�� NULL�� �ƴ϶�� ���Ϲ��� prev(pv)�� �ڿ� np�� �����ϰ� ��(����: prev -> prev�� ��ũ�� ����Ű�� ��, ����: prev -> nd -> prev�� ��ũ�� ����Ű�� ��) 
			np->link = prev->link;
			prev->link = np;
		}
		
	}
	fclose(fp);

	printList(head);	// ���ĵ� ��ũ�帮��Ʈ ������ ���

	while (1) {
		
		printf("Type command> ");
		scanf("%s", command);
		if (strcmp(command, "IS") == 0) {	// type command�� IS�� ��� �̸�, �л���ȣ, ����, ��ȭ��ȣ, ������� �Է¹ް� �̸��� ������ ���� ��忡 ��ġ�� 
			scanf("%s %d %f %s %s", name1, &sno1, &gpa1, phone1, province1);
			np = (listPointer)malloc(sizeof(struct listNode));
			strcpy(np->name, name1);
			np->sno = sno1;
			np->gpa = gpa1;
			strcpy(np->phone, phone1);
			strcpy(np->province, province1);
			IS(head, np);
		}
		else if (strcmp(command, "SE") == 0) {	// type command�� SE�� ��� Ȯ���Ϸ��� �л��� �̸��� �Է¹ް� ������ ���
			scanf("%s", name1);
			SE(head, name1);
		}
		else if (strcmp(command, "RG") == 0) {	// type command�� RG�� ��� �� �л��� �̸�(�Ȱ��� �ʴٸ� ������) ���̿� �ִ� ��� ������� ������ �����
			scanf("%s %s", name1, name2);
			RG(head, name1, name2);
		}
		else if (strcmp(command, "DL") == 0) {	// type command�� DL�� ��� ��ũ�帮��Ʈ�� �� ���� �޸� �л��� ������ ����ϰ� �� �л��� ����
			DL(head);
		}
		else if (strcmp(command, "SP") == 0) {	// type command�� SP�� ��� ��ȭ��ȣ �� �� 4�ڸ��� �Է¹޾� �̿� ���� ��ȭ��ȣ�� ���� �л��� �����
			scanf("%s", phone1);
			SP(head, phone1);
		}
		else if (strcmp(command, "LO") == 0) {	// type command�� LO�� ��� �������� �Է¹޾Ƽ� �� ���� ����� ��� �л����� �����
			scanf("%s", province1);
			LO(head, province1);
		}
		else if (strcmp(command, "EX") == 0) {	// type command�� EX�� ��� ��� ���� �������� ����
			break;
		}
	}

	return 0;
}