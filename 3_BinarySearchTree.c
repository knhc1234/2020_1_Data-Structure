#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct anod* TreePointer;
typedef struct anod {		// 한 노드의 구조
	int sno;				// 학번
	char name[50];			// 이름
	TreePointer leftChild, rightChild;	// 노드의 자식에 대한 포인터
} Ty_Node;

TreePointer In(TreePointer nod, char getname[50], int getsno, int *level, int *errorcount);		// 새로운 노드를 넣고 성공여부 및 새 노드의 레벨을 출력(Ia에서 입력 실패시 실패한 노드 수를 세기도 함) 
TreePointer Ia(TreePointer nod);	// sdata.txt 파일의 모든 줄을 삽입하며 이미 존재하므로 삽입 실패된 레코드의 수를 출력
void Sp(TreePointer nod);			// 모든 BST 안의 모든 레코드를 이름 순으로 출력 (inorder traversal 이용)
TreePointer De(TreePointer nod, char getname[50], int *record);	// 삭제할 사람의 이름을 입력받아 이를 가진 노드를 삭제하며 삭제 작업 중에 다른 노드로 이동이 일어난 레코드의 학생의 이름도 출력
TreePointer Da(TreePointer nod);	// sdata.txt 화일의 모든 사람을 삭제하는 작업을 수행하며 삭제 작업에서 발생한 노드들의 총 이동횟수를 출력
void Se(TreePointer nod, char getname[50], int* level);	// 이름을 입력 받아 이를 가진 노드를 찾아서 학번 및 이름, 이 노드의 레벨을 출력
void Ht(TreePointer nod);			// 전체 이진탐색트리의 높이를 구하여 출력(높이를 구하는 건 FindHeight를 이용)
void FindHeight(TreePointer nod, int* level, int* height);	// 이진 탐색 트리의 높이를 구하는 함수
void Le(TreePointer nod);			// 이 BST 의 노드 중 자식이 1 개인 노드의 수, 0 개인 노드의 수를 알아내어 출력(노드의 수를 계산하는 건 Lecount를 이용)
void Lecount(TreePointer nod, int* lecount, int* onechildcount);	// BST의 노드에서 자식이 1 개인 노드의 수와 0개인 노드의 수를 구함
void Ch(TreePointer nod, char getname[50]);	// 이름을 입력 받아서 이를 가진 노드의 immediate successor 찾아서 그 내용을 출력(없으면 없다고 출력함)
void Ex(int* endcount);				// while문을 빠져나와 프로그램을 종료하게 만드는 함수

int main(void) {

	int endcount = 1;		// ex를 입력할 경우 endcount가 0이 되어 while문과 함께 프로그램이 종료됨
	TreePointer nod = NULL;
	nod = Ia(nod);			// 파일의 데이터를 읽어 모든 줄을 노드에 삽입
	system("cls");
	while (endcount) {		// endcount가 0이 될 때(ex 입력)까지 반복
		char name1[50] = { 0 };	// 입력 받은 이름	(매 while문 마다 초기화)
		int sno1 = 0;			// 입력 받은 학번	(매 while문 마다 초기화)
		int level = 0;			// 해당 노드의 높이(level)	(매 while문 마다 초기화)
		int errorcount = 0;		// Ia에서 이미 존재하여 삽입 실패된 레코드의 수	
		char fullcommand[100] = { 0 };	// 입력 받은 명령을 1차로 저장	(매 while문 마다 초기화)
		char order[100] = { 0 };			// 입력 받은 명령중 작업 명령어(in, ia, sp, de, da, se, ht, le, ch, ex) 저장	(매 while문 마다 초기화)
		char string_sno[100] = { 0 };	// 입력 받은 학생이름을 문자열 형태로 저장	(매 while문 마다 초기화)
		int i = 0;	
		int j = 0;
		int record = 0;		// da에서 이용되는 노드들의 총 이동횟수	

		printf("수행할 작업은 (in, ia, sp, de, da, se, ht, le, ch, ex) ? ");
		gets(fullcommand);	// 수행할 작업을 입력받음
		while (fullcommand[i] != ' '&& fullcommand[i] != '\0') {	// 띄어쓰기 혹은 \n키가 입력되기 전까지의 모든 단어를 order에 저장(첫번째 명령어는 수행할 작업을 분류하기 때문)
			order[i] = fullcommand[i];
			i++;
		}

		if (strcmp(order, "in") == 0) {	// order에 저장된 첫번째 명령어가 in인 경우
			int checkerror = 0;	// 잘못된 입력을 할 경우를 확인하기 위한 용도 ex) in 이름 숫자
			i++;				// 띄어쓰기로 부터 한칸 다음으로 이동
			while ((fullcommand[i] != ' ')&&(fullcommand[i]!='\0')) {	// 띄어쓰기가 입력되기 전까지의 모든 단어를 string_sno에 저장(만약 잘못된 입력인 경우에 중지(in 만 입력한 경우))
				string_sno[j] = fullcommand[i];
				i++;
				j++;
			}
			sno1 = atoi(string_sno);		// string_sno에 문자열로 저장되있던 정보를 sno1(입력 받은 학번)에 int형으로 바꾸어 저장

			if (sno1 == 0|| fullcommand[i]=='\0') {	// 입력이 잘못되었다면 (in만 입력한 경우 또는 in 숫자 이름의 순으로 쓰지 않은 경우)	
				system("cls");	
				printf("잘못된 입력입니다.\n");	
				checkerror++;	// 에러가 있으므로 뒤의 내용들이 실행이 안되도록 조치함
			}
			
			if (checkerror == 0) {	// 입력에 지금까지 문제가 없는 경우
				i++;	// 띄어쓰기로 부터 한칸 다음으로 이동
				j = 0;	// 0으로 초기화(정보 저장용)
				while (fullcommand[i] != '\0') {	// \n가 입력될 때까지(null이 나오기 전까지)의 모든 단어를 name1(입력 받은 이름)에 저장
					name1[j] = fullcommand[i];
					i++;
					j++;
				}

				if (checkerror == 0) {	// 모든 입력이 제대로 진행된 경우
					system("cls");	
					nod = In(nod, name1, sno1, &level, &errorcount);	// 입력 받은 이름과 학생 정보를 가진 노드를 새로 넣고 성공여부 및 새 노드의 레벨을 출력함( 이름 중복은 불가능)
				}
			}
		}
		else if (strcmp(order, "ia") == 0) {	// order에 저장된 첫번째 명령어가 ia인 경우
			system("cls");
			nod = Ia(nod);	// sdata.txt 파일의 모든 줄을 삽입하며 이미 존재하므로 삽입 실패된 레코드의 수를 출력함
		}
		else if (strcmp(order, "sp") == 0) {	// order에 저장된 첫번째 명령어가 sp인 경우
			system("cls");	
			printf("화일의 내용은 다음과 같습니다:\n");
			Sp(nod);		// 모든 BST 안의 모든 레코드를 이름 순으로 출력함
		}
		else if (strcmp(order, "de") == 0) {	// order에 저장된 첫번째 명령어가 de인 경우
			int checkerror = 0;	// 잘못된 입력을 할 경우를 확인하기 위한 용도 ex) de만 입력
			if (fullcommand[i] == '\0') {	// 명령어로 de만 입력한 경우 잘못된 입력
				printf("잘못된 입력입니다.\n");
				checkerror++;	// checkerror를 1 증가
			}
			if (checkerror == 0) {	// 에러가 발생하지 않은 경우
				i++;	// 띄어쓰기로 부터 한칸 다음으로 이동
				while (fullcommand[i] != '\0') {	// \n가 입력될 때까지(null이 나오기 전까지)의 모든 단어를 name1(입력 받은 이름)에 저장 
					name1[j] = fullcommand[i];
					i++;
					j++;
				}
				system("cls");
				nod = De(nod, name1, &record);	// 입력 받은 이름을 가진 노드를 삭제하며 삭제 작업 중에 다른 노드로 이동이 일어난 레코드의 학생의 이름도 출력
			}
		}
		else if (strcmp(order, "da") == 0) {	// order에 저장된 첫번째 명령어가 da인 경우
			system("cls");		
			nod = Da(nod);	// sdata.txt 화일의 모든 사람을 삭제하는 작업을 수행하며 삭제 작업에서 발생한 노드들의 총 이동횟수를 출력
		}
		else if (strcmp(order, "se") == 0) {	// order에 저장된 첫번째 명령어가 se인 경우
			int checkerror = 0;	// 잘못된 입력을 할 경우를 확인하기 위한 용도 ex) se만 입력
			if (fullcommand[i] == '\0') {	// 명령어로 se만 입력한 경우 잘못된 입력
				printf("잘못된 입력입니다.\n");
				checkerror++;	// checkerror를 1 증가
			}
			if (checkerror == 0) {	// 에러가 발생하지 않은 경우
				i++;	// 띄어쓰기로 부터 한칸 다음으로 이동
				while (fullcommand[i] != '\0') {	// \n가 입력될 때까지(null이 나오기 전까지)의 모든 단어를 name1(입력 받은 이름)에 저장 
					name1[j] = fullcommand[i];
					i++;
					j++;
				}
				system("cls");
				Se(nod, name1, &level);	// 입력 받은 이름을 가진 노드를 찾아서 학번 및 이름, 이 노드의 레벨을 출력
			}
		}
		else if (strcmp(order, "ht") == 0) {	// order에 저장된 첫번째 명령어가 ht인 경우
			system("cls");
			Ht(nod);	// 전체 이진탐색트리의 높이를 구하여 출력
		}	
		else if (strcmp(order, "le") == 0) {	// order에 저장된 첫번째 명령어가 le인 경우
			system("cls");
			Le(nod);	// 이 BST 의 노드 중 자식이 1 개인 노드의 수, 0 개인 노드의 수를 알아내어 출력
		}
		else if (strcmp(order, "ch") == 0) {	// order에 저장된 첫번째 명령어가 ch인 경우
			int checkerror = 0;	// 잘못된 입력을 할 경우를 확인하기 위한 용도 ex) ch만 입력
			if (fullcommand[i] == '\0') {	// 명령어로 ch만 입력한 경우 잘못된 입력
				printf("잘못된 입력입니다.\n");
				checkerror++;	// checkerror를 1 증가
			}
			if (checkerror == 0) {	// 에러가 발생하지 않은 경우
				i++;	// 띄어쓰기로 부터 한칸 다음으로 이동
				while (fullcommand[i] != '\0') {	// \n가 입력될 때까지(null이 나오기 전까지)의 모든 단어를 name1(입력 받은 이름)에 저장 
					name1[j] = fullcommand[i];
					i++;
					j++;
				}
				system("cls");
				Ch(nod, name1);	// 입력 받은 이름을 가진 노드의 immediate successor 찾아서 그 내용을 출력(없으면 없다고 출력함)
			}
		}
		else if (strcmp(order, "ex") == 0) {	// order에 저장된 첫번째 명령어가 ex인 경우
			system("cls");
			Ex(&endcount);	// 프로그램을 종료함
		}
		else {	// 입력을 잘못 받았을 경우
			printf("잘못된 입력입니다. 다시 입력해 주세요.\n");
		}
	}
	return 0;
}

TreePointer In(TreePointer nod, char getname[50], int getsno, int *level, int *errorcount) {	// 새로운 노드를 넣고 성공여부 및 새 노드의 레벨을 출력(Ia에서 입력 실패시 실패한 노드 수를 세기도 함) 
	if (nod == NULL) {	// 노드에 빈 노드인 경우(생성한 첫번째 노드이거나 계속 이동하여 입력 받은 정보가 저장될 노드가 들어갈 자리를 찾음)
		nod = (TreePointer)malloc(sizeof(Ty_Node));	// 동적할당 후 노드에 입력 받은 이름(getname)과 입력 받은 학번(getsno)을 저장, leftChild rightChild를 null로 만들고 성공여부 및 새 노드의 레벨 출력
		strcpy(nod->name, getname);	
		nod->sno = getsno;
		nod->leftChild = NULL;
		nod->rightChild = NULL;
		printf("입력 성공!	%d %s level %d\n", nod->sno, nod->name, *level);
	}
	else {	// 노드가 빈 노드가 아닌 경우 
		if (strcmp(nod->name, getname) == 1) {	// 노드의 이름이 입력받은 이름보다 후순위라면(입력 받은 value가 노드의 value보다 작은 경우)
			*level = *level + 1;	// 노드의 레벨을 1 올리고
			nod->leftChild = In(nod->leftChild, getname, getsno, level, errorcount);	// leftChild로 이동(계속해서 연결)
		}
		else if (strcmp(nod->name, getname) == -1) {	// 노드의 이름이 입력받은 이름보다 앞순위라면(입력 받은 value가 노드의 value보다 큰 경우)
			*level = *level + 1;	// 노드의 레벨을 1 올리고
			nod->rightChild = In(nod->rightChild, getname, getsno, level, errorcount);	// rightChild로 이동하여 찾아봄(계속해서 연결)
		}
		else {	// 노드의 이름과 입력 받은 이름이 같은 경우 이미 존재하는 노드라고 출력 
			printf("이미 존재하는 노드입니다.\n");	
			*errorcount = *errorcount + 1;	// Ia에서 이미 존재하여 삽입에 실패하는걸 셀 때 이용 됨
		}
	}
	return nod;	// 이전 노드와 연결하여 최종적으로 새로 생성된 노드를 포함한 전체노드를 리턴하게 함
}

TreePointer Ia(TreePointer nod) {	// sdata.txt 파일의 모든 줄을 삽입하며 이미 존재하므로 삽입 실패된 레코드의 수를 출력
	char name1[50];	// 파일에서 얻은 이름 정보
	int sno1;		// 파일에서 얻은 학번정보
	int res;		// 파일의 데이터를 제대로 읽어 오는지 확인하기 위한 변수
	int level;		// 해당 노드의 높이(level)
	int errorcount = 0;	// 파일을 읽어서 삽일 할 때 이미 노드에 존재하여 삽입 실패된 레코드의 수

	FILE* fp = fopen("sdata.txt", "r");	// sdata.txt파일을 열음
	while (1) {
		level = 0;	// 매 while문 마다 level을 0으로 초기화(0으로 초기화하여 다시 구함)
		res = fscanf(fp, "%d %s", &sno1, name1);	// 파일에서 학번과 이름을 읽어 sno1과 name1에 정보 저장
		if (res < 2) {	// 파일의 정보를 잘 받아들이지 못했거나 파일의 정보가 부족한 경우 혹은 더 이상 읽을 정보가 없는 경우 while문을 빠져나옴
			break;
		}

		nod = In(nod, name1, sno1, &level, &errorcount);	// 파일에서 읽은 정보들을 토대로 노드를 생성함(만약 노드에 파일에 있는 노드가 이미 존재하여 삽입에 실패한 경우 errorcount가 1 증가함)
	}
	printf("이미 존재하여 삽입 실패한 노드의 수: %d\n", errorcount);	// 이미 존재하여 삽입 실패한 노드의 수를 출력
	fclose(fp);	// sdata.txt파일을 닫음
	return nod;	// 전체 노드를 리턴함
}

void Sp(TreePointer nod) {	// 이원 탐색 트리이므로 leftChild의 이름 순서가 가장 빠르며 그다음이 부모노드 그리고 가장 뒤에 오는 것이 rightChild이므로 이 순서대로 정보를 출력한다.
	if (nod != NULL) {
		Sp(nod->leftChild);		// 왼쪽 노드 탐색
		printf("%s, %d\n", nod->name, nod->sno);	// 자신의 노드 정보 출력
		Sp(nod->rightChild);	// 오른쪽 노드 탐색
	}
} 

TreePointer De(TreePointer nod, char getname[50], int *record) {	// 삭제할 사람의 이름을 입력받아 이를 가진 노드를 삭제하며 삭제 작업 중에 다른 노드로 이동이 일어난 레코드의 학생의 이름도 출력
	TreePointer parent, successor;	// 부모 노드(immediate successor의 부모 역할)와 immediate successor노드의 정보를 담을 노드들을 생성
	if (nod == NULL) {	// 입력 받은 이름을 가진 노드가 없는 경우 
		printf("노드가 존재하지 않습니다.\n");
		return NULL;
	}
	if (strcmp(nod->name, getname) == 1) {	// 노드의 이름이 입력받은 이름보다 후순위라면(입력 받은 value가 노드의 value보다 작은 경우)
		nod->leftChild = De(nod->leftChild, getname, record);	// leftChild로 이동(노드끼리 계속해서 연결)
	}
	else if (strcmp(nod->name, getname) == -1) {	// 노드의 이름이 입력받은 이름보다 앞순위라면(입력 받은 value가 노드의 value보다 큰 경우)
		nod->rightChild = De(nod->rightChild, getname, record);	// leftChild로 이동(노드끼리 계속해서 연결)
	}
	else {	// 노드의 이름과 입력 받은 이름이 같은 경우
		if (nod->leftChild != NULL) {	// 자식 노드가 둘 다 있거나 왼쪽 자식 노드만 있는 경우
			successor = nod->leftChild;	// 현재 노드의 leftChild노드로 한번 이동하여 immediate successor노드에 정보 저장(immediate successor를 구하기 위함)
			parent = nod;	// 부모 노드에 현재 노드의 정보를 저장
			while (successor->rightChild != NULL) {	// nod의 leftChild의 노드 중 가장 큰 노드 즉 rightChild로 계속 이동하여 끝에 있는 노드가 immediate successor임
				parent = successor;	// 부모 노드에 immediate successor 노드의 정보 저장
				successor = successor->rightChild;	// immediate successor를 찾기위해 계속 rightChild로 이동
			}
			strcpy(nod->name, successor->name);	// immediate successor를 찾은 경우 immediate successor가 삭제할 노드를 대체해야 하므로 삭제할 노드의 정보에 immediate successor의 정보를 저장함
			nod->sno = successor->sno;
			*record = *record + 1;	// 삭제 시 발생하는 노드의 이동 횟수에 1을 추가함(Da에서 총 이동횟수를 구하기 위해 사용됨)
			printf("성공적으로 삭제되었습니다. %s의 위치변경이 일어남.\n", successor->name);	// 위치 변경 메세지를 출력
			nod->leftChild = De(nod->leftChild, successor->name, record);	// immediate successor의 위치가 바뀐 것이므로 현재 노드로 바뀐 것이므로 남아있는 immediate successor에 해당하는 노드를 삭제하기 위해 leftChild로 이동(immediate successor의 이동에 따른 또다른 노드의 이동도 이 과정에 포함됨)
		}
		else if (nod->leftChild == NULL && nod->rightChild != NULL) {	// 왼쪽 자식 노드가 없고 오른쪽 자식 노드만 있는 경우
			successor = nod->rightChild;	// 현재 노드의 rightChild노드로 한번 이동하여 immediate successor노드에 정보 저장(immediate successor를 구하기 위함)
			parent = nod;	// 부모 노드에 현재 노드의 정보를 저장		
			while (successor->leftChild != NULL) {	// nod의 rightChild의 노드 중 가장 작은 노드 즉 leftChild로 계속 이동하여 끝에 있는 노드가 immediate successor임
				parent = successor;	// 부모 노드에 immediate successor 노드의 정보 저장
				successor = successor->leftChild;	// immediate successor를 찾기위해 계속 rightChild로 이동
			}
			strcpy(nod->name, successor->name);	// immediate successor를 찾은 경우 immediate successor가 삭제할 노드를 대체해야 하므로 삭제할 노드의 정보에 immediate successor의 정보를 저장함
			nod->sno = successor->sno;
			*record = *record + 1;	// 삭제 시 발생하는 노드의 이동 횟수에 1을 추가함(Da에서 총 이동횟수를 구하기 위해 사용됨)
			printf("성공적으로 삭제되었습니다. %s의 위치변경이 일어남.\n", successor->name);	// 위치 변경 메세지를 출력
			nod->rightChild = De(nod->rightChild, successor->name, record);	// immediate successor의 위치가 바뀐 것이므로 현재 노드로 바뀐 것이므로 남아있는 immediate successor에 해당하는 노드를 삭제하기 위해 rightChild로 이동(immediate successor의 이동에 따른 또다른 노드의 이동도 이 과정에 포함됨)
		}
		else {	// 만약 자식 노드가 없다면
			printf("성공적으로 삭제되었습니다.\n");
			nod = NULL;	// 해당 노드를 null로 만들고 
			free(nod);	// 해당 노드의 메모리를 해제함
		}
	}
	return nod;	// 노드를 리턴함(마지막엔 전체 노드를 리턴)
}

TreePointer Da(TreePointer nod) {	// sdata.txt 화일의 모든 사람을 삭제하는 작업을 수행하며 삭제 작업에서 발생한 노드들의 총 이동횟수를 출력
	char name1[50];	// 파일에서 얻은 이름 정보
	int sno1;		// 파일에서 얻은 학번정보
	int res;		// 파일의 데이터를 제대로 읽어 오는지 확인하기 위한 변수
	int level;		// 해당 노드의 높이(level)
	int record = 0;	// 삭제 작업에서 발생한 노드들의 총 이동횟수
	FILE* fp = fopen("sdata.txt", "r");	// sdata.txt파일을 열음
	while (1) {
		level = 0;	// 매 while문 마다 level을 0으로 초기화(0으로 초기화하여 다시 구함)
		res = fscanf(fp, "%d %s", &sno1, name1);	// 파일에서 학번과 이름을 읽어 sno1과 name1에 정보 저장
		if (res < 2) {	// 파일의 정보를 잘 받아들이지 못했거나 파일의 정보가 부족한 경우 혹은 더 이상 읽을 정보가 없는 경우 while문을 빠져나옴
			break;
		}
		nod = De(nod, name1, &record);	// 파일에서 읽은 정보를 토대로 노드를 삭제함
	}
	printf("삭제 과정에서 위치의 이동이 일어난 횟수: %d\n", record);	// 삭제 과정에서 위치의 이동이 일어난 총 횟수를 출력
	return nod;	// 전체 노드를 리턴
}

void Se(TreePointer nod, char getname[50], int* level) {	// 이름을 입력 받아 이를 가진 노드를 찾아서 학번 및 이름, 이 노드의 레벨을 출력
	int checkpoint = 0;	// 찾는 노드가 없을 경우를 확인하기 위한 변수
	while (nod) {	// 해당 노드를 찾거나 노드가 null이 될 때까지 계속해서 확인 
		if (strcmp(getname, nod->name) == 0) {	// 찾는 노드인 경우 해당 노드의 정보를 출력하고 while문을 빠져나옴
			printf("이름:%s, 학번: %d, 레벨위치 = %d\n", nod->name, nod->sno, *level);	
			checkpoint++;	// 노드를 찾았을 경우 checkpoint가 1이 되어 확인 가능
			break;
		}
		else if (strcmp(getname, nod->name) == 1) {	// 찾는 노드가 해당 노드보다 큰 경우(이름 순서상 뒤인 경우) rightChild로 이동하여 탐색
			*level = *level + 1;	// 노드의 레벨을 1 올리고
			nod = nod->rightChild;	// rightChild로 이동하여 탐색
		}
		else {	// 찾는 노드가 해당 노드보다 작은 경우(이름 순서상 앞인 경우) 
			*level = *level + 1;	// 노드의 레벨을 1 올리고
			nod = nod->leftChild;	// leftChild로 이동하여 탐색
		}
	}
	if (checkpoint == 0) {	// 찾는 노드가 없어서 끝까지 돈 경우( + 애초에 노드가 없는 경우)
		printf("해당 노드는 존재하지 않습니다.\n");
	}
}

void Ht(TreePointer nod) {	// 전체 이진탐색트리의 높이를 구하여 출력(높이를 구하는 건 FindHeight를 이용)
	int level = -1;	// 노드의 레벨을 -1로 설정 (높이(height)를 계산할 때 레벨을 1 증가 시키고 계산하기 때문)
	int height = 0;	// 전체 이진탐색트리의 높이
	FindHeight(nod, &level, &height);	// 전체 이진탐색트리의 높이를 구함
	printf("height = %d\n", height);	// 전체 이진탐색트리의 높이를 출력
}

void FindHeight(TreePointer nod, int* level, int* height) {	// 이진 탐색 트리의 높이를 구하는 함수
	*level = *level + 1;	// 레벨을 1 증가시킴(깊이 탐색할 때마다)
	if (nod != NULL) {		// nod가 null이 아니라면
		if (nod->rightChild == NULL && nod->leftChild == NULL) {	// 자식 노드가 없다면
			if (*level > * height) {	// 현재 노드의 레벨이 지금까지 본 가장 큰 높이보다 크다면
				*height = *level;		// 현재 노드의 레벨이 이진탐색트리의 높이가 됨(결국 가장 큰 level을 구하여 현재 이진탐색트리의 높이를 구하게 됨)
			}
		}
		FindHeight(nod->leftChild, level, height);	// 왼쪽 노드 높이 탐색
		FindHeight(nod->rightChild, level, height);	// 오른쪽 노드 높이 탐색
	}
	*level = *level - 1;	// 노드 탐색을 끝내고 부모 노드로 돌아가는 경우 레벨을 1 감소시킴
}

void Le(TreePointer nod) {	// 이 BST 의 노드 중 자식이 1 개인 노드의 수, 0 개인 노드의 수를 알아내어 출력(노드의 수를 계산하는 건 Lecount를 이용)
	int lecount = 0;	// 자식이 0개인 노드의 수
	int onechildcount = 0;	// 자식이 1개인 노드의 수
	Lecount(nod, &lecount, &onechildcount);	// 자식이 0개인 노드의 수와 자식이 1개인 노드의 수를 계산함
	printf("number of leaf nodes = %d\n", lecount);	// 자식이 0개인 노드의 수 출력
	printf("자식 노드의 수가 1개인 노드의 수 = %d\n", onechildcount);	// 자식이 1개인 노드의 수 출력
}

void Lecount(TreePointer nod, int *lecount, int *onechildcount) {	// BST의 노드에서 자식이 1 개인 노드의 수와 0개인 노드의 수를 구함
	if (nod != NULL) {	// 노드가 null이 아니라면
		if (nod->leftChild == NULL && nod->rightChild == NULL) {	// 노드의 자식이 없는 경우
			*lecount = *lecount + 1;	// 자식이 0개인 노드의 수가 1 증가
		}
		if ((nod->leftChild != NULL && nod->rightChild == NULL) || (nod->leftChild == NULL && nod->rightChild != NULL)) {	// 노드의 자식이 1개인 경우
			*onechildcount = *onechildcount + 1;	// 자식이 1개인 노드의 수가 1 증가
		}
		Lecount(nod->leftChild, lecount, onechildcount);	// 왼쪽 노드를 탐색
		Lecount(nod->rightChild, lecount, onechildcount);	// 오른쪽 노드를 탐색
	}
}

void Ch(TreePointer nod, char getname[50]) {	// 이름을 입력 받아서 이를 가진 노드의 immediate successor 찾아서 그 내용을 출력(없으면 없다고 출력함)
	TreePointer successor;	// immediate successor의 정보를 위한 노드
	if (nod == NULL) {	// 전체 노드가 null이라면 노드가 존재하지 않는다고 출력
		printf("노드가 존재하지 않습니다.\n");
	}
	if (strcmp(nod->name, getname) == 1) {	// 노드의 이름이 입력받은 이름보다 후순위라면(입력 받은 value가 노드의 value보다 작은 경우)
		Ch(nod->leftChild, getname);	// leftChild로 이동하여 탐색
	}
	else if (strcmp(nod->name, getname) == -1) {	// 노드의 이름이 입력받은 이름보다 앞순위라면(입력 받은 value가 노드의 value보다 큰 경우)
		Ch(nod->rightChild, getname);	// rightChild로 이동하여 탐색
	}
	else {	// 입력받은 이름과 같은 노드를 찾은 경우
		if (nod->leftChild != NULL) {	// 자식 노드가 둘 다 있거나 왼쪽 자식 노드만 있는 경우
			successor = nod->leftChild;	// 현재 노드의 leftChild노드로 한번 이동하여 immediate successor노드에 정보 저장(immediate successor를 구하기 위함)
			while (successor->rightChild != NULL) {	// nod의 leftChild의 노드 중 가장 큰 노드 즉 rightChild로 계속 이동하여 끝에 있는 노드가 immediate successor임 
				successor = successor->rightChild;	// rightChild로 계속 이동
			}
			printf("Immediate successor의 정보 - 이름:%s, 학번: %d\n", successor->name,successor->sno);	// immediate successor를 찾았으므로 해당 정보를 출력
		}
		else if (nod->leftChild == NULL && nod->rightChild != NULL) {	// 왼쪽 자식 노드가 없고 오른쪽 자식 노드만 있는 경우
			successor = nod->rightChild;	// 현재 노드의 rightChild노드로 한번 이동하여 immediate successor노드에 정보 저장(immediate successor를 구하기 위함)
			while (successor->leftChild != NULL) {	// nod의 rightChild의 노드 중 가장 작은 노드 즉 leftChild로 계속 이동하여 끝에 있는 노드가 immediate successor임 
				successor = successor->leftChild;	// leftChild로 계속 이동
			}
			printf("Immediate successor의 정보 - 이름:%s, 학번: %d\n", successor->name, successor->sno);	// immediate successor를 찾았으므로 해당 정보를 출력
		}
		else {	// 만약 자식 노드가 없다면 Immediate successor는 존재할 수 없음
			printf("Immediate successor가 존재하지 않습니다.\n");
		}
	}
}

void Ex(int* endcount) {	// while문을 빠져나와 프로그램을 종료하게 만드는 함수
	*endcount = 0;	// endcount를 0으로 만들어 main의 while문을 빠져나가게 만듦
	printf("프로그램을 종료합니다!");	// 프로그램이 종료한다는 메세지 출력
}