#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define INF -1
#define INF2 1000
#define Max_vertex 12
typedef struct nodestr* nodeptr;
typedef struct nodestr {
	int no;
	nodeptr link;
} ty_node;
double COST[Max_vertex][Max_vertex];
nodeptr Graph[Max_vertex] = { NULL };
double distance[Max_vertex];
int pred[Max_vertex];
int set_S[Max_vertex];
int found[Max_vertex];
int path[Max_vertex][Max_vertex];
int visited[Max_vertex];
int flag = 0;

void set_graph() {	// Graph에 각 시작 no와 link 할당
	for (int i = 0; i < Max_vertex; i++) {
		Graph[i] = (nodeptr)malloc(sizeof(ty_node));
		Graph[i]->no = i;
		Graph[i]->link = NULL;
	}
}

void set_path() {	// path값을 모두 INF로 설정
	for (int i = 0; i < Max_vertex; i++) {		
		for (int j = 0; j < Max_vertex; j++) {
			path[i][j] = INF;
		}
		set_S[i] = 0;
	}

}

void reset_visited() {	// 한번 사용된 visted값과 flag값을 초기화(depth_first)에서 이용)
	for (int i = 0; i < Max_vertex; i++) {
		visited[i] = 0;
	}
	flag = 0;
}

void Read_and_make_graph() {	// txt파일을 읽어 그래프를 읽고 만드는 함수
	set_graph();	// 각 그래프에 공간 및 기본 no, link 할당
	int i, j, k;	
	int i_max = 0;
	int no1;		
	double no2;
	int checkcount = 0;
	int base_num;
	int max_vertex;
	char line[400];
	char* cp;
	char buf[25][50];
	FILE* fp = fopen("graphdata.txt", "r");
	while (1) {
		cp = fgets(line, 400, fp);	// 한 라인을 읽음
		if (!cp) {	// 더 이상 읽을 수 없으면 while문을 빠져나옴
			break;
		}
		else {
			i = 0;
			j = 0;
			while (1) {
				k = 0;
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
				if (line[j] == '\n') {	// 읽은 부분이 \n이였었다면 while문을 빠져나감
					if (checkcount == 0) {			// checkcount가 0(첫 줄이라면) vertex의 개수를 얻음
						max_vertex = atoi(buf[0]);
						checkcount = 1;
						break;
					}
					else {	// 첫번째 줄이 아니라면
						i_max = i - 1;	// i_max값 설정
						base_num = atoi(buf[0]);	// base_num을 첫번째로 입력받은 숫자(다루는 vertex)로 설정
						for (i = 1; i<i_max; i += 2) {	// 매 for문 마다 COST값을 지정하고 인접 연결리스트(Graph)를 생성함
							no1 = atoi(buf[i]);
							no2 = atof(buf[i + 1]);
							COST[base_num][no1] = no2;

							nodeptr node2;
							nodeptr node = (nodeptr)malloc(sizeof(ty_node));
							node->no = no1;
							node->link = NULL;
							for (node2 = Graph[base_num]; node2->link; node2 = node2->link) {
							}
							node2->link = node;
						}
						break;
					}
				}
				else
					do j++; while (line[j] == ' ');	// 공백이였을 경우 읽은 부분이 공백인 경우 다음 부분을 읽음
			}
		}
	}
	fclose(fp);	
	for (int i = 0; i < 12; i++) {		// COST 값을 i와 j가 다르고 값이 0이라면 둘을 직접연결하는 방법이 없는 것이므로 무한대로 설정
		for (int j = 0; j < 12; j++) {
			if (i != j) {
				if (COST[i][j] == 0)
					COST[i][j] = INF;
			}
		}
	}
	set_path();
}

int choose_shortest(int destination) {	// 이미 지나지 않은 점들 중(found가 FALSE) 가장 거리가 근처의 점을 찾아서 반환
	double min = 5000;
	int index = 0;
	for (int i = 0; i < Max_vertex; i++) {	
		if (distance[i] != INF && distance[i] < min && found[i] == FALSE) {
			min = distance[i];
			index = i;
		}
	}
	return index;
}

int shortest_path(int start, int destination) {	// dijkstra를 이용한 최소 비용 경로찾기 
	int i, u, w;
	for (i = 0; i < Max_vertex; i++) {
		found[i] = FALSE;
		if (COST[start][i] == INF)
			distance[i] = INF2;
		else
			distance[i] = COST[start][i];
		set_S[i] = 1;
		path[i][0] = start;
	}

	found[start] = TRUE;
	distance[start] = 0;

	for (i = 0; i < Max_vertex - 2; i++) {
		u = choose_shortest(destination);
		found[u] = TRUE;
		for (w = 0; w < Max_vertex; w++) {
			if (!found[w]) {
				if ((distance[u] + COST[u][w] < distance[w]) && distance[u] != INF2 && COST[u][w] != INF) {
					if (i == 0) {
						path[w][set_S[w]] = u;	// 갱신된 경로 저장
						set_S[w]++;
					}
					else {
						for (int j = 0; j < (set_S[u] + 1); j++) {	// 갱신된 경로 변경
							path[w][j] = path[u][j];
							path[w][j + 1] = u;
						}
						set_S[w]++;
					}
					distance[w] = distance[u] + COST[u][w];
				}
			}
		}
	}
	printf("dijkstra로 찾은 최소비용 경로: ");
	for (int j = 0; j < Max_vertex; j++) {
		if (path[destination][j] != INF) {
			printf("%d, ", path[destination][j]);
		}
	}
	printf("%d\t", destination);
	printf("총비용: %f\n", distance[destination]);
	set_path();	
	return 0;
}

void depth_first(int start, int end) {		// dfs를 이용한 경로 찾기
	nodeptr w;
	visited[start] = TRUE;
	printf("%d", start);
	if (start == end) {
		flag = 1;
		return;
	}
	printf(", ");
	for (w = Graph[start]; w; w = w->link) {
		if (flag == 1)
			break;
		if (!visited[w->no])
			depth_first(w->no, end);
	}
}

int main(void) {
	int start, destination;
	Read_and_make_graph();
	while (1) {
		char line[100];
		char command[100];
		char start1[100];
		char destination1[100];
		int i;
		int j;
		printf("최소경로를 찾을 두 정점을 입력하시오> ");
		gets(line);
		i = 0;
		while (line[i] == ' ' || line[i] == '\t') i++;	// line에서 공백 또는 \t인 경우 이 뒤의 내용을 읽음
		j = 0;
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line이 공백, \t, \0이 아닐 때까지
			command[j] = line[i];	// 읽은 정보(line)의 명령어 부분을 command에 저장
			i++;
			j++;
		}
		command[j] = '\0';	// line에서 공백, \t, \0을 만난 경우 command로 입력한 정보가 끝이므로 command의 맨 뒤에 \0을 저장

		if (strcmp(command, "e") == 0) {	// command가 e인 경우 프로그램 종료 아닌 경우 아래에 계속
			printf("프로그램을 종료합니다.\n");
			break;
		}
		else;

		j = 0;
		while (line[i] == ' ' || line[i] == '\t') i++;	// line이 공백 또는 \t일경우 그 다음을 읽음
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line이 공백 또는 \t, \0이 아닐 때까지
			start1[j] = line[i];	// 읽은 정보(line)의 시작 정점 부분을 start1에 저장
			i++;
			j++;
		}
		start1[j] = '\0';	// line에서 공백, \t, \0을 만난 경우 start1에 입력한 정보가 끝이므로 start1의 맨 뒤에 \0을 저장
		start = atoi(start1);	// start1을 정수로 반환하여 start에 저장

		j = 0;
		while (line[i] == ' ' || line[i] == '\t') i++;	// line이 공백 또는 \t일경우 그 다음을 읽음
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line이 공백 또는 \t, \0이 아닐 때까지
			destination1[j] = line[i];	// 읽은 정보(line)의 종료 정점 부분을 destination1에 저장
			i++;
			j++;
		}
		destination1[j] = '\0';	// line에서 공백, \t, \0을 만난 경우 destination1에 입력한 정보가 끝이므로 destination1의 맨 뒤에 \0을 저장
		destination = atoi(destination1);	// destination1을 정수로 반환하여 destination에 저장

		if (start < 0 || start >= Max_vertex || destination < 0 || destination >= Max_vertex) {	// start와 destination이 0보다 작거나 최대 정점수보다 크거나 같은 경우 잘못된 입력
			printf("잘못된 입력입니다.\n");
		}
		else {	// start와 destination이 제대로 입력된 경우
			if (strcmp(command, "j") == 0) {	// 명령어가 j인 경우 dijkstra를 이용하여 최소 비용 경로와 총 비용 출력
				shortest_path(start, destination);	
			}
			else if (strcmp(command, "f") == 0) {	// 명령어가 f인 경우 dfs를 이용하여 찾은 경로를 출력
				printf("depth-first 경로: ");
				depth_first(start, destination);
				reset_visited();
				printf("\n");
			}
			else {	// 명령어가 이 외인 경우 (e는 맨 처음에 다룸) 잘못된 입력임 
				printf("잘못된 입력입니다.\n");
			}
		}
	}
	return 0;
}