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

listPointer search_insert_position(listPointer hd, char nm[]) {		// 이름순으로 배열
	listPointer pv = NULL;
	int cmp;
	while (1) {
		if (!hd) {	// hd가 NULL일 경우 pv(NULL)을 리턴
			return pv;
		}
		else {
			cmp = strcmp(nm, hd->name);	// nm과 hd->name을 비교
			if (cmp <= 0)				// nm과 hd->name이 같거나 nm이 hd->name보다 앞이라면 pv 리턴
				return pv;
			else {						// nm이 hd->name보다 뒤라면 pv를 hd로 만들고 hd는 링크에 연결된 hd->link로 만듦 (이 함수가 끝나고 nm이 들어갈 자리의 앞노드가 pv로 리턴되도록 만듦)
				pv = hd;
				hd = hd->link;
			}
		}
	}
}

void IS(listPointer hd, listPointer np) {	// 새 학생의 데이터 삽입
	listPointer prev;
	prev = search_insert_position(hd, np->name);
	if (!prev) {		// prev가 NULL이라면 
		np->link = hd;	// np의 link가 hd를 가리키고 np가 hd(링크드 리스트의 맨 앞 head)가 됨
		hd = np;
	}
	else {				// prev가 존재한다면 
		np->link = prev->link;	// np의 link는 prev의 링크를 가리키고 prev의 link는 np가 됨 ( prev와 prev가 가리키는 링크사이에 np가 들어옴(prev - np - prev가 링크로 가리키던 것))
		prev->link = np;
	}
}

void SE(listPointer hd, char nm[]) {	// 한 학생 검색
	int cmp;
	while (hd) {
		cmp = strcmp(nm, hd->name);		
		if (cmp == 0) {	// nm과 hd->name이 같다면 해당 학생의 정보 출력
			printf("%s %d %f %s %s\n", hd->name, hd->sno, hd->gpa, hd->phone, hd->province);	
			break;
		}
		else {
			hd = hd->link;
		}
	}
}

void RG(listPointer hd, char nm1[], char nm2[]) {	// 일부의 출력( 두 이름 사이에 있는 모든 학생 출력)
	listPointer prev;
	prev = hd;	// hd에 존재하지 않는 이름의 학생이 nm1일 경우 맨 앞의 학생부터 nm2와 같은 이름의 학생 전(혹은 이름순서상 앞에있는) 까지 출력하기 위한 용도로 사용
	int cmp;
	int checkcount = 1;	// nm1과 같은 이름이 있다면 0이 되고 0에서 nm2와 같은 이름이 있다면 반복문에서 탈출 한다. 만약 1인 상태로 반복문을 빠져나왔다면 맨 앞의 학생부터 nm2와 같은 이름이 나오는 학생 전(혹은 이름순서상 앞에있는 학생)까지 출력한다.
	while (hd) {
		if (checkcount == 1) {
			cmp = strcmp(nm1, hd->name);
			if (cmp == 0) {		// 이름이 nm1과 같다면 checkcount가 0이됨
				checkcount--;
			}
			hd = hd->link;
		}
		else if (checkcount == 0) {	
			cmp = strcmp(nm2, hd->name);
			if (cmp == 0) {		// 이름이 같다면 반복문에서 탈출 아니라면 같은 이름 혹은 이름 순서상 뒤의 학생이 나올 때 까지 사이에 있는 학생 정보 출력 
				break;
			}
			printf("%s %d %f %s %s\n", hd->name, hd->sno, hd->gpa, hd->phone, hd->province);
			hd = hd->link;
		}
	}
	if (checkcount == 1) {		// nm1과 같은 이름의 학생이 없을 경우
		while (prev) {
			cmp = strcmp(nm2, prev->name);
			if (cmp <= 0) {		// nm2와 같거나 이름 순서상 뒤에 있는 학생이 나오기 전까지 그 사이에 있는 모든 학생 정보 출력
				break;
			}
			printf("%s %d %f %s %s\n", prev->name, prev->sno, prev->gpa, prev->phone, prev->province);
			prev = prev->link;
		}
	}
	
}

void DL(listPointer hd) {	// 연결리스트의 맨 끝에 달린 학생의 정보를 출력하고 나서 이 학생을 삭제
	listPointer pv;
	pv = NULL;

	while (hd->link != NULL) {
		pv = hd;
		hd = hd->link;
	}
	printf("%s %d %f %s %s\n", hd->name, hd->sno, hd->gpa, hd->phone, hd->province);
	pv->link = NULL;
}

void SP(listPointer hd, char phone[]) {	// 전화번호 맨 뒤 4 자리를 입력받아 이러한 전화번호를 가진 학생을 출력
	while (hd) {
		if (strcmp(phone, hd->phone + 9) == 0) {
			printf("%s %d %f %s %s\n", hd->name, hd->sno, hd->gpa, hd->phone, hd->province);
			break;
		}
		hd = hd->link;
	}
}

void LO(listPointer hd, char province[]) {	// 지역명을 입력받아서 이 지역 출신의 모든 학생들을 출력
	while (hd) {
		if (strcmp(province, hd->province) == 0) {
			printf("%s %d %f %s %s\n", hd->name, hd->sno, hd->gpa, hd->phone, hd->province);
		}
		hd = hd->link;
	}
}

void printList(listPointer first) {	// 어떤 학생들이 있는지 mydata.txt에 적혀있는 정보들을 링크드리스트에 정렬한 상태로 데이터 출력
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
	char command[3];	// 각종 명령 수행 루프 확인용
	char name1[50];		// 파일에서 이름 정보 입력용, 명령 수행 루프에서 사용
	char name2[50];		// 명령 수행 루프(RG)에서 사용
	int sno1, res;		// 파일에서 학생 번호 입력용, 명령 수행 루프에서 사용
	float gpa1;			// 파일에서 학생 성적 입력용, 명령 수행 루프에서 사용
	char phone1[20];	// 파일에서 학생 핸드폰 번호 입력용, 명령 수행 루프에서 사용
	char province1[20];	// 파일에서 학생 출신 입력용, 명령 수행 루프에서 사용

	head = NULL;
	np   = NULL;
	prev = NULL;

	FILE* fp;
	fp = fopen("mydata.txt", "r");

	while (1) {
		res = fscanf(fp, "%s %d %f %s %s", name1, &sno1, &gpa1, phone1, province1);

		if (res < 5) {	// 파일의 정보를 잘 받아들이지 못했거나 파일의 정보가 부족한 경우
			break;
		}
		
		np = (listPointer)malloc(sizeof(struct listNode));
		strcpy(np->name, name1);	// 파일에서 받아들인 내용들을 np에 저장
		np->sno = sno1;
		np->gpa = gpa1;
		strcpy(np->phone, phone1);
		strcpy(np->province, province1);
		
		
		prev = search_insert_position(head,name1);	
		if (!prev) {			// prev가 NULL이라면 nd가 링크드리스트에서 제일 앞 노드 즉 head가 됨
			np->link = head;
			head = np;
		}
		else {					// prev가 NULL이 아니라면 리턴받은 prev(pv)의 뒤에 np가 존재하게 됨(기존: prev -> prev의 링크가 가리키는 것, 변경: prev -> nd -> prev의 링크가 가리키던 것) 
			np->link = prev->link;
			prev->link = np;
		}
		
	}
	fclose(fp);

	printList(head);	// 정렬된 링크드리스트 정보를 출력

	while (1) {
		
		printf("Type command> ");
		scanf("%s", command);
		if (strcmp(command, "IS") == 0) {	// type command가 IS인 경우 이름, 학생번호, 성적, 전화번호, 출신지를 입력받고 이름의 순서를 통해 노드에 배치함 
			scanf("%s %d %f %s %s", name1, &sno1, &gpa1, phone1, province1);
			np = (listPointer)malloc(sizeof(struct listNode));
			strcpy(np->name, name1);
			np->sno = sno1;
			np->gpa = gpa1;
			strcpy(np->phone, phone1);
			strcpy(np->province, province1);
			IS(head, np);
		}
		else if (strcmp(command, "SE") == 0) {	// type command가 SE인 경우 확인하려는 학생의 이름을 입력받고 정보를 출력
			scanf("%s", name1);
			SE(head, name1);
		}
		else if (strcmp(command, "RG") == 0) {	// type command가 RG인 경우 두 학생의 이름(똑같지 않다면 순서상) 사이에 있는 모든 사람들의 정보를 출력함
			scanf("%s %s", name1, name2);
			RG(head, name1, name2);
		}
		else if (strcmp(command, "DL") == 0) {	// type command가 DL인 경우 링크드리스트의 맨 끝에 달리 학생의 정보를 출력하고 이 학생을 삭제
			DL(head);
		}
		else if (strcmp(command, "SP") == 0) {	// type command가 SP인 경우 전화번호 맨 뒤 4자리를 입력받아 이와 같은 전화번호를 가진 학생을 출력함
			scanf("%s", phone1);
			SP(head, phone1);
		}
		else if (strcmp(command, "LO") == 0) {	// type command가 LO인 경우 지역명을 입력받아서 이 지역 출신의 모든 학생들을 출력함
			scanf("%s", province1);
			LO(head, province1);
		}
		else if (strcmp(command, "EX") == 0) {	// type command가 EX인 경우 명령 수행 루프에서 나옴
			break;
		}
	}

	return 0;
}