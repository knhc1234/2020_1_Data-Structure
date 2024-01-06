#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

typedef struct ano* nodeptr;
typedef struct ano {
	char name[30];	// 이름
	float gpa;		// 학점
	char place[100];	// 주소
	nodeptr links[MAX];	// 자식들
} nodetype;

nodeptr ROOT = NULL;	
nodeptr stack[100];
int top = -1;

nodeptr search_node(nodeptr cur, char sname[]) {	// sname과 같은 name을 가지고 있는 노드를 찾아 리턴
	int i;
	nodeptr rptr;
	if (!cur)		// 노드가 null이라면
		return NULL;	// null을 return
	
	if (strcmp(cur->name, sname) == 0)	// sname과 같은 name을 가지고 있는 노드를 찾은 경우
		return cur;		// 그 노드를 return
	else {	// sname과 name이 다른 경우
		for (i = 0; cur->links[i] != NULL; i++) {		// 현재 노드가 가지고 있는 자식들이 sname과 같은 지 확인
			rptr = search_node(cur->links[i], sname);	
			if (rptr)	// rptr이 NULL이 아닌 경우
				return rptr; // rptr을 리턴
		}
		return NULL;	// 자식들에게서 sname과 같은 name을 가지고 있는 노드를 찾지 못한 경우 NULL을 리턴
	}
}

int read_upper(FILE* fp, char buf[20][50]) {	// txt파일의 상단부를 읽는 함수
	int i, j, k;
	char line[400]; 
	char* cp;
	cp = fgets(line, 400, fp);	// cp에 파일을 읽고 정보 저장
	if (!cp) {	// cp가 NULL인 경우 정보를 못 읽었거나 txt파일이 비어있는 경우
		printf("Impossible for the control to reach here.\n");
		return 0;
	}
	else {	// cp가 NULL이 아닌 경우
		if (line[0] == '-')	// -가 나올 때 까지 읽어들임(상단부만 읽음)
			return 0;

		i = 0;
		j = 0;
		k = 0;
		while (1) {
			while (line[j] != ' ' && line[j] != '\n') {		// 읽은 부분이 공백 또는 \n일 때 까지 반복
				if (line[j] == '\t') {	// 읽은 부분이 \t인 경우
					buf[i][k] = '\0';	// 해당 부분은 \0으로 변경하고 
					i++;				// i와 j를 1증가, k=0으로 초기화 함
					j++;
					k = 0;
				}
				else {					// 읽은 부분이 \t가 아닌 경우
					buf[i][k] = line[j];	// 해당 부분의 정보를 buf에 저장
					j++;					// j와 k 1씩 증가
					k++;
				}
			}
			buf[i][k] = '\0';		// 읽은 부분이 공백 또는 \n이면 해당 부분을 \0으로 변경
			i++;					// i를 1 증가
			if (line[j] == '\n')	// 읽은 부분이 \n이였었다면 while문을 빠져나감
				break;
			else
				do j++; while (line[j] == ' ');	// 공백이였을 경우 읽은 부분이 공백인 경우 다음 부분을 읽음
		}
		return i;	// 현재까지 읽은 단어의 개수 (ex) 부모 자식1 자식2 자식3 인 경우 4개)를 리턴
	}
}

void read_store_lower_data(FILE* fp) {	// 파일의 하단부를 읽고 해당 데이터를 저장하는 함수
	char rname[30], address[100];	
	float rgpa;
	nodeptr np;
	int read_num;
	do {
		read_num = fscanf(fp, "%s %f %s", rname, &rgpa, address);	// 파일을 읽고 이름, 학점, 주소정보를 얻음
		if (read_num != 3)	// 더 이상 읽을게 없는 경우
			break;	// while문 탈출
		else {
			np = search_node(ROOT, rname);	// 파일에서 읽은 rname을 name으로 가지는 노드를 찾음
			if (!np)	// 그런 노드가 없는 경우 없다고 화면에 출력
				printf("이런 이름을 가진 노드가 없습니다.\n");
			else {		// 있는 경우
				strcpy(np->name, rname);	// 해당 노드의 name에 rname을 저장
				np->gpa = rgpa;				// 해당 노드의 gpa에 rgpa를 저장
				strcpy(np->place, address);	// 해당 노드의 plac에 address를 저장
			}
		}
	} while (1);	// 파일의 정보를 모두 읽을 때 까지 반복
}

void add_data(nodeptr curr, char* sname, char* sname2, float gpa, char* address) {	// ad 부모이름 자식이름 학점 주소를 입력한 경우 부모이름을 가진 노드를 부모노드로 삼고 자식이름(sname2), 학점(gpa), 주소 정보(address)를 가지는 새로운 노드를 자식노드로 가짐
	nodeptr np;
	nodeptr rnp;
	int i;

	if (sname == NULL || sname2 == NULL || address == NULL)		// 부모이름이 없거나 자식이름이 없거나 주소가 없는 경우(입력을 잘못한 경우) 종료
		return;
	else {
		np = search_node(curr, sname);	// curr과 그 자손들중 sname과 같은 이름을 가진 노드를 찾음
		if (!np)	// 그런 노드가 없는 경우 없다고 출력
			printf("이런 이름을 가진 노드가 없습니다.\n");
		else {		// 있는 경우
			for (i = 0; np->links[i]; i++) {	// np->links[i]가 NULL이 될 때 까지 i를 ++함
			}
			if (strcmp(np->name, sname) == 0) {	// 현재 노드가 sname과 같은 이름을 가진 경우(부모노드)
				rnp = (nodeptr)malloc(sizeof(nodetype));	// 새로운 노드를 만들어 해당 노드의 이름에 sname2, 학점에 gpa, 주소에 address를 저장
				strcpy(rnp->name, sname2);
				rnp->gpa = gpa;
				strcpy(rnp->place, address);
				printf("이름:%s  학점:%5.2f  주소:%s \n", rnp->name, rnp->gpa, rnp->place); // 아닌 경우 현재 노드에 저장된 정보를 출력
				rnp->links[0] = NULL;		// 생성된 노드의 자식노드를 NULL로 만들고
				np->links[i] = rnp;			// 현재 노드의 자식노드에 생성한 노드를 추가
				np->links[i + 1] = NULL;	// 해당 links의 다음 links를 NULL로 만듦
			}
		}
	}

}

void print_general_tree(nodeptr curr) {	// 일반트리의 모든 노드를 출력
	int i;
	if (!curr)	// curr이 NULL인 경우 읽을 정보가 없음
		return;
	printf("이름:%s  학점:%5.2f  주소:%s \n", curr->name, curr->gpa, curr->place); // 아닌 경우 현재 노드에 저장된 정보를 출력
	for (i = 0; curr->links[i]; i++)	// 현재 노드의 자식노드가 존재하는 경우
		print_general_tree(curr->links[i]);	// 그 자식노드의 정보를 읽고 출력함
}

void print_descendant(nodeptr curr, char* sname) {	// 모든 자손들을 1줄에 1명씩 출력
	int i;
	if (!curr)	// 현재 노드가 NULL이라면 return함
		return;
	if (strcmp(sname, curr->name) != 0)	// 현재 노드의 이름과 sname이 같지 않은 경우
		printf("%s \n", curr->name);	// 이름을 출력 (대상인 sname은 출력하지 않고 그 자손들만을 출력함)
	for (i = 0; curr->links[i]; i++)	// 자식 노드가 존재한다면 해당 자식들의 이름을 출력
		print_descendant(curr->links[i], sname);
}

nodeptr search_parent_node(nodeptr cur, char sname[]) {	// 부모노드를 찾아서 리턴함
	int i;
	nodeptr rptr;
	if (!cur)	// 현재 노드가 NULL이라면 NULL을 리턴
		return NULL;
	if (strcmp(cur->name, sname) == 0) {	// 만약 현재 노드의 이름과 sname이 같은 경우(sname의 대상이 첫번째 노드인 경우) 
		printf("형제자매가 존재하지 않습니다. \n");		// 첫번째 노드의 형제자매는 존재하지 않는다고 출력
		return NULL;	// NULL을 리턴
	}
	
	for (i = 0; cur->links[i] != NULL; i++) {	// 자식노드가  NULL이 아닌 경우
		if (strcmp(cur->links[i]->name, sname) == 0) {	// 자식 노드의 이름이 sname과 같은 경우
			return cur;		// 현재 노드(sname을 이름으로 갖는 노드의 부모노드)를 리턴
		}
		else {	// 아닌 경우
			rptr = search_parent_node(cur->links[i], sname);	// sname을 이름으로 갖는 노드의 부모노드를 계속 찾음
			if (rptr)
				return rptr;
		}
	}
	return NULL;	// sname을 이름으로 갖는 노드가 없는 경우 NULL을 리턴
}

void print_brother(nodeptr curr, char* sname) {		// 형제 자매의 이름을 출력 (curr에 부모노드의 정보를 가지고 있음)
	int i;
	if (!curr)	
		return;
	
	for (i = 0; curr->links[i]; i++) {	// 부모노드의 자식 노드들 중
		if (strcmp(sname, curr->links[i]->name) != 0)	// 해당 대상(sname을 이름으로 갖는 노드)을 제외한 모든 형제 자매들의 이름을 출력함
			printf("%s \n", curr->links[i]->name);
	}
	if (i == 1) {	// 만약 부모노드의 자식이 대상밖에 없다면 형제자매가 없다고 출력함
		printf("형제자매가 존재하지 않습니다.\n");
	}
}

void print_nodecount(nodeptr curr, int* count) {	// 트리 내의 모든 노드의 수를 세 count에 정보를 저장(갱신)함
	int i;
	*count = *count + 1;	
	if (!curr) {	// curr이 NULL인 경우 종료
		return;
	}
	for (i = 0; curr->links[i]; i++) {	// NULL이 아니라면 자식노드가 있는 경우
		print_nodecount(curr->links[i],count);	// 해당 자식 노드로 이동하여 노드의 개수를 세어 count에 정보를 저장(갱신)함
	}
}

void print_levelnode(nodeptr curr, int* level,int* lvcount) {	// 입력한 level과 같은 level에 있는 노드들을 출력
	int i;
	if (!curr)	// curr이 NULL인 경우 종료
		return;

	*lvcount = *lvcount + 1;	// 매 이동마다 level이 증가함
	if (*lvcount == *level)		// 현재 노드의 level이 입력한 level과 같은 경우 현재 노드의 이름 출력
		printf("%s ", curr->name);

	for (i = 0; curr->links[i]; i++) {	// 자식 노드가 있는 경우
		print_levelnode(curr->links[i], level, lvcount);	// 해당 자식 노드로 이동하여 입력한 level과 같은 level인 경우 이름 출력
	}
	*lvcount = *lvcount - 1;	// 현재 함수의 일을 끝내고 부모노드로 이동하는 경우 level이 감소
}

void make_node_and_attach_to_parent(nodeptr parent, char* tname, int loc) {		// 새 노드를 만들어 부모에 연결함
	nodeptr np1;
	np1 = (nodeptr)malloc(sizeof(nodetype));	// 새 노드를 생성(동적 할당)
	strcpy(np1->name, tname);	// 새 노드의 이름으로 tname을 가짐
	np1->links[0] = NULL;		// 새 노드의 자식노드를 NULL로 만듦
	parent->links[loc] = np1;	// 부모노드의 links(자식노드)로 생성한 노드를 연결
}

void dfs_height(nodeptr cur, int par_height, int* tree_height) {	// 전체 트리의 높이를 tree_height에 저장(갱신)함
	int my_height = par_height + 1;		// 현재의 높이는 부모의 높이 + 1 
	int i;
	if (*tree_height < my_height)	// 가장 높았던 트리의 높이(tree_height)보다 현재의 높이가 더 큰 경우
		* tree_height = my_height;	// 가장 높은 트리의 높이(tree_height)에 현재의 높이를 저장(결국 tree_height에 전체 트리의 높이(가장 높았던 높이)가 저장됨)
	for (i = 0; cur->links[i]; i++) {	// 자식 노드가 있는 경우
		dfs_height(cur->links[i], my_height, tree_height);	// 해당 자식의 높이와 현재의 tree_height을 비교
	}
	return;	
}

int dfs_depth(nodeptr cur, int par_height, char* sname) {	// sname을 이름으로 갖는 노드의 깊이를 구함
	int my_height = par_height + 1;	// 현재의 높이는 부모의 높이 + 1
	int i;
	int res;
	if (strcmp(cur->name, sname) == 0) {	// 현재 노드의 이름이 sname과 같은 경우
		printf("Height of the node of %s : %d\n", sname, my_height);	// 현재 노드의 높이(깊이)를 출력
		return 1;
	}
	for (i = 0; cur->links[i]; i++) {	// 현재 노드의 이름이 sname과 다르고 자식노드가 있을 경우
		res = dfs_depth(cur->links[i], my_height, sname);	// 자식 노드들의 이름중 sname을 이름으로 갖는 노드가 있는지 찾고 존재한다면 해당 노드의 깊이를 출력함
		if (res)
			return 1;
	}
	return 0;	// 실패한 경우 0을 리턴함
}

void push_stack(nodeptr nptr) {	
	top++;	// top을 1만큼 증가
	stack[top] = nptr;	// top에 nptr의 정보 저장
}

void pop_stack() {	// top을 1만큼 감소
	top--;
}

int dfs_ancestors(nodeptr cur, char* sname) {	// sname을 이름으로 갖는 노드의 조상들을 출력
	int i, res;
	if (strcmp(cur->name, sname) == 0) {	// 현재 노드의 이름이 sname과 같은 경우
		printf("This person's ancestors: ");	// 이 사람의 조상을 출력
		for (i = 0; i <= top; i++)	// top이 i보다 크거나 같은 경우
			printf("%s ", stack[i]->name);	// 해당 스택의 이름을 출력(조상의 이름 출력)
		printf("\n");
		return 1;
	}
	// 현재 노드의 이름이 sname과 다른 경우
	push_stack(cur);	// top을 1만큼 증가시키고 cur의 정보를 저장 함
	for (i = 0; cur->links[i]; i++) {	// cur의 자식들의 이름중 sname을 이름으로 갖는 노드가 있는지 확인하고 그 때까지 stack에 저장된 조상들의 이름을 출력함
		res = dfs_ancestors(cur->links[i], sname);
		if (res)
			return 1;
	}

	pop_stack();	// 현재 함수가 끝난다면 pop으로 stack의 정보에서 빠짐(데이터가 없어지는건 아니지만 나중에 새로운 데이터로 채워지기 때문에 일종의 삭제라고 보면 됨)
	return 0;		// sname을 이름으로 갖는 노드가 없다면 0을 리턴
}

int main(void) {
	char buf[20][50];
	int num_persons, k;
	nodeptr np;

	FILE* fp;
	fp = fopen("tree_data.txt", "r");	// tree_data.txt파일을 읽음
	if (!fp) {	// 파일이 NULL이라면 에러표시
		printf("file open error.\n");
		return;
	}

	do {
		num_persons = read_upper(fp, buf);	// 파일의 상단부를 한 줄씩 읽고 그 안에 저장된 사람의 수를 num_persons에 저장
		if (num_persons == 0)	// 사람이 없다면 이 while문을 빠져나감
			break;
		if (!ROOT) {	// ROOT가 NULL이라면 첫 노드를 생성(맨 처음 읽은 사람의 data가 부모노드가 되고 나머지가 자식노드가 됨)
			np = (nodeptr)malloc(sizeof(nodetype));	
			strcpy(np->name, buf[0]);
			ROOT = np;
			np->links[0] = NULL;
			for (k = 1; k < num_persons; k++) {	// 해당 buf[k]에 저장된 단어를 이름으로 가지는
				make_node_and_attach_to_parent(np, buf[k], k - 1);	// 자식노드를 생성하고 연결함
			}
			np->links[k - 1] = NULL;	// 자식노드가 생성되지 않은 링크는 NULL로 만듦(ex)자식이 3명인 경우 np->links는 links[0],[1],[2]까지 생성되며 그 바로 다음인 [3]을 NULL로 만듦
		}
		else {	// ROOT가 NULL이 아니라면 두번째 줄 이하를 읽는 것이므로
			np = search_node(ROOT, buf[0]);	// 두 번째 줄 이하의 첫번째 단어를 이름으로 가지는 노드를 찾아(부모노드가 됨)
			if (!np) {	// 이전에 생성된 노드에 위에서 읽은 첫번째 단어(buf[0])에 입력된 이름을 가지는 노드가 없는 경우(부모노드로 삼을 노드가 없는 경우) 에러
				printf("Error: 2째 줄 이하의 첫 이름의 노드가 없음.\n");
				getchar();
			}
			for (k = 1; k < num_persons; k++) {	// 그 뒤에 입력된 단어를 이름으로 가지는
				make_node_and_attach_to_parent(np, buf[k], k - 1);	// 자식노드를 생성하고 연결함
			}
			np->links[k - 1] = NULL;	// 자식노드가 생성되지 않은 링크는 NULL로 만듦
		}
	} while (1);
	read_store_lower_data(fp);	// 위에서 생성된 트리의 각 노드에 이름, 학점, 주소의 정보를 파일의 하단부를 읽어 얻어옴
	print_general_tree(ROOT);	// 현재까지 만들어진 트리의 모든 노드의 정보들을 출력

	do {
		char command[400];
		char line[400];
		char name[400];
		char name2[400];
		float gpa2;
		char gpa[400];
		char address[400];

		printf("Type a command> ");
		gets(line);		// line을 입력 받음

		int i = 0;
		while (line[i] == ' ' || line[i] == '\t') i++;	// line에서 공백 또는 \t인 경우 이 뒤의 내용을 읽음
		int k = 0;
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line이 공백, \t, \0이 아닐 때까지
			command[k] = line[i];	// 읽은 정보(line)의 명령어 부분을 command에 저장
			i++;
			k++;
		}
		command[k] = '\0';	// line에서 공백, \t, \0을 만난 경우 command로 입력한 정보가 끝이므로 command의 맨 뒤에 \0을 저장

		if (strcmp(command, "ex") == 0) {	// command가 ex 일 경우	while문을 빠져나감(루프를 종료함)
			break;
		}
		else if (strcmp(command, "ht") == 0) {	// command가 ht인 경우
			int tree_height = 0;
			dfs_height(ROOT, 0, &tree_height);	// 트리의 높이정보(tree_height)를 얻음 (가장 큰 level = tree_height)
			printf("Height of the tree : %d \n", tree_height);	// 전체 트리의 높이(height)를 출력
			continue;	// 다음 while문으로 넘어감(continue를 안하면 제일 밑의 while문의 else에 걸려 맞게 입력했지만 wrong command가 출력됨)
		}
		else if (strcmp(command, "nm") == 0) {	// command가 nm인 경우
			int count = 0;
			print_nodecount(ROOT, &count);	// 모든 노드의 수를 세고 그 정보를 count에 저장
			printf("Number of nodes : %d \n", count);	// 모든 노드의 갯수를 출력
			continue;	// 다음 while문으로 넘어감(continue를 안하면 제일 밑의 while문의 else에 걸려 맞게 입력했지만 wrong command가 출력됨)
		}
		else;	// 이 외의 경우 (command 이름 또는 command 이름 이름 학점 주소 또는 잘못 입력한 경우) 계속 진행

		k = 0;	// k를 0으로 초기화
		while (line[i] == ' ' || line[i] == '\t') i++;	// line이 공백 또는 \t일경우 그 다음을 읽음
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line이 공백 또는 \t, \0이 아닐 때까지
			name[k] = line[i];	// 읽은 정보(line)의 이름 부분을 name에 저장
			i++;
			k++;
		}
		name[k] = '\0';	// line에서 공백, \t, \0을 만난 경우 name에 입력한 정보가 끝이므로 name의 맨 뒤에 \0을 저장

		if (strcmp(command, "se") == 0) {	// command가 se인 경우
			np = search_node(ROOT, name);	// 입력한 이름(name)을 가진 노드를 찾음
			if (np)	// 찾은 경우 해당 노드의 정보 출력
				printf("Search success:	%s %5.2f %s\n", np->name, np->gpa, np->place);
			else printf("Such a person does not exist.\n");	// 입력한 이름을 가진 노드가 없는 경우 해당 노드는 존재하지 않는다고 출력
			continue;	// 다음 while문으로 넘어감(continue를 안하면 제일 밑의 while문의 else에 걸려 맞게 입력했지만 wrong command가 출력됨)
		}
		else if (strcmp(command, "dp") == 0) {	// command가 dp인 경우
			int res = dfs_depth(ROOT, 0, name);	// 입력한 이름(name)을 가진 노드의 깊이를 찾고 출력함
			if (!res)	// 찾지 못한 경우(return 0인 경우)
				printf("Such a name does not exist in the tree.\n");	// 입력한 이름(name)을 가진 노드가 없다고 출력
			continue;	// 다음 while문으로 넘어감(continue를 안하면 제일 밑의 while문의 else에 걸려 맞게 입력했지만 wrong command가 출력됨)
		}
		else if (strcmp(command, "ac") == 0) {	// command가 ac인 경우
			top = -1;	// top을 -1로 만듦
			int res = dfs_ancestors(ROOT, name);	// stack을 이용하여 입력한 이름(name)을 가진 노드의 조상들을 출력함
			if (!res)	// 실패한 경우(입력한 이름을 가진 노드가 없는 경우)
				printf("Such a name does not exist in the tree.\n");	// 입력한 이름(name)을 가진 노드가 없다고 출력
			continue;	// 다음 while문으로 넘어감(continue를 안하면 제일 밑의 while문의 else에 걸려 맞게 입력했지만 wrong command가 출력됨)
		}
		else if (strcmp(command, "na") == 0) {	// command가 na인 경우
			np = search_node(ROOT, name);	// 입력한 이름(name)의 노드를 찾음
			if (np)	// 노드를 찾은 경우
				print_descendant(np, name);	// 해당 노드의 자식들을 모두 출력함
			else printf("Such a person does not exist.\n");	// 노드를 찾지 못한 경우(입력한 이름(name)의 노드가 없는 경우) 입력한 이름(name)을 가진 노드가 없다고 출력
			continue;	// 다음 while문으로 넘어감(continue를 안하면 제일 밑의 while문의 else에 걸려 맞게 입력했지만 wrong command가 출력됨)
		}
		else if (strcmp(command, "br") == 0) {	// command가 br인 경우
			np = search_parent_node(ROOT, name);	// 입력한 이름(name)의 부모노드를 찾음
			if (np)	// 부모노드를 찾은 경우
				print_brother(np, name);	// 입력한 이름(name)을 가진 노드의 형제 자매들을 출력함
			else printf("Such a person does not exist.(Or that person's node is first node)\n");	// 부모노드를 찾지 못한 경우 입력한 이름(name)을 가진 노드가 없거나 첫번째 노드라 부모노드가 없는 경우 둘 중 하나라고 출력
			continue;	// 다음 while문으로 넘어감(continue를 안하면 제일 밑의 while문의 else에 걸려 맞게 입력했지만 wrong command가 출력됨)
		}
		else if (strcmp(command, "LV") == 0) {	// command가 LV인 경운
			int level = atoi(name);		// 입력한 레벨(name)을 정수로 바꿔 level에 저장
			int lvcount = 0;	// 매 노드의 lv을 나타냄
			if (level > 0) {	// level이 0보다 큰 경우(제대로 된 입력인 경우)
				print_levelnode(ROOT, &level, &lvcount);	// 입력한 level과 같은 level의 노드들을 출력함
				printf("\n");
			}
			else printf("Wrong command.\n");	// level이 0보다 작은 경우 잘못된 입력임
			continue;	// 다음 while문으로 넘어감(continue를 안하면 제일 밑의 while문의 else에 걸려 맞게 입력했지만 wrong command가 출력됨)
		}
		else; // 이 외의 경우 (command 이름 이름 학점 주소 또는 잘못 입력한 경우) 계속 진행

		k = 0;	// k를 0으로 초기화
		while (line[i] == ' ' || line[i] == '\t') i++;	// line이 공백 또는 \t일경우 그 다음을 읽음
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line이 공백 또는 \t, \0이 아닐 때까지
			name2[k] = line[i];		// 읽은 정보(line)의 자식노드이름 부분을 name2에 저장
			i++;
			k++;
		}
		name2[k] = '\0';	// line에서 공백, \t, \0을 만난 경우 name2에 입력한 정보가 끝이므로 name2의 맨 뒤에 \0을 저장

		k = 0;	// k를 0으로 초기화
		while (line[i] == ' ' || line[i] == '\t') i++;	// line이 공백 또는 \t일경우 그 다음을 읽음
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line이 공백 또는 \t, \0이 아닐 때까지
			gpa[k] = line[i];	// 읽은 정보(line)의 학점 부분을 gpa에 저장
			i++;
			k++;
		}
		gpa[k] = '\0';		// line에서 공백, \t, \0을 만난 경우 gpa에 입력한 정보가 끝이므로 gpa의 맨 뒤에 \0을 저장
		gpa2 = (float)atof(gpa);	// 입력받은 gpa를 float형태로 변환

		k = 0;	// k를 0으로 초기화
		while (line[i] == ' ' || line[i] == '\t') i++;	// line이 공백 또는 \t일경우 그 다음을 읽음
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line이 공백 또는 \t, \0이 아닐 때까지
			address[k] = line[i];	// 읽은 정보(line)의 주소 부분을 address에 저장
			i++;
			k++;
		}
		address[k] = '\0';	// line에서 공백, \t, \0을 만난 경우 address에 입력한 정보가 끝이므로 address의 맨 뒤에 \0을 저장

		if (strcmp(command, "ad") == 0) {	// command가 ad인 경우
			add_data(ROOT, name, name2, gpa2, address);	// name을 부모노드로 하여 이름을 name2, 학점을 gpa2, 주소를 address로 갖는 새 노드를 자식노드로 연결함
		}
		else {	// 이 외의 경우 (잘못된 입력인 경우)
			printf("Wrong command.\n");	// 잘못된 입력이라고 출력
		}
	} while (1);
}