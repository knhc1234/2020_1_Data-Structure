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

void set_graph() {	// Graph�� �� ���� no�� link �Ҵ�
	for (int i = 0; i < Max_vertex; i++) {
		Graph[i] = (nodeptr)malloc(sizeof(ty_node));
		Graph[i]->no = i;
		Graph[i]->link = NULL;
	}
}

void set_path() {	// path���� ��� INF�� ����
	for (int i = 0; i < Max_vertex; i++) {		
		for (int j = 0; j < Max_vertex; j++) {
			path[i][j] = INF;
		}
		set_S[i] = 0;
	}

}

void reset_visited() {	// �ѹ� ���� visted���� flag���� �ʱ�ȭ(depth_first)���� �̿�)
	for (int i = 0; i < Max_vertex; i++) {
		visited[i] = 0;
	}
	flag = 0;
}

void Read_and_make_graph() {	// txt������ �о� �׷����� �а� ����� �Լ�
	set_graph();	// �� �׷����� ���� �� �⺻ no, link �Ҵ�
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
		cp = fgets(line, 400, fp);	// �� ������ ����
		if (!cp) {	// �� �̻� ���� �� ������ while���� ��������
			break;
		}
		else {
			i = 0;
			j = 0;
			while (1) {
				k = 0;
				while (line[j] != ' ' && line[j] != '\n') {		// ���� �κ��� ���� �Ǵ� \n�� �� ���� �ݺ�
					if (line[j] == '\t') {	// ���� �κ��� \t�� ���
						buf[i][k] = '\0';	// �ش� �κ��� \0���� �����ϰ� 
						i++;				// i�� j�� 1����, k=0���� �ʱ�ȭ ��
						j++;
						k = 0;
					}
					else {					// ���� �κ��� \t�� �ƴ� ���
						buf[i][k] = line[j];	// �ش� �κ��� ������ buf�� ����
						j++;					// j�� k 1�� ����
						k++;
					}
				}
				buf[i][k] = '\0';		// ���� �κ��� ���� �Ǵ� \n�̸� �ش� �κ��� \0���� ����
				i++;					// i�� 1 ����
				if (line[j] == '\n') {	// ���� �κ��� \n�̿����ٸ� while���� ��������
					if (checkcount == 0) {			// checkcount�� 0(ù ���̶��) vertex�� ������ ����
						max_vertex = atoi(buf[0]);
						checkcount = 1;
						break;
					}
					else {	// ù��° ���� �ƴ϶��
						i_max = i - 1;	// i_max�� ����
						base_num = atoi(buf[0]);	// base_num�� ù��°�� �Է¹��� ����(�ٷ�� vertex)�� ����
						for (i = 1; i<i_max; i += 2) {	// �� for�� ���� COST���� �����ϰ� ���� ���Ḯ��Ʈ(Graph)�� ������
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
					do j++; while (line[j] == ' ');	// �����̿��� ��� ���� �κ��� ������ ��� ���� �κ��� ����
			}
		}
	}
	fclose(fp);	
	for (int i = 0; i < 12; i++) {		// COST ���� i�� j�� �ٸ��� ���� 0�̶�� ���� ���������ϴ� ����� ���� ���̹Ƿ� ���Ѵ�� ����
		for (int j = 0; j < 12; j++) {
			if (i != j) {
				if (COST[i][j] == 0)
					COST[i][j] = INF;
			}
		}
	}
	set_path();
}

int choose_shortest(int destination) {	// �̹� ������ ���� ���� ��(found�� FALSE) ���� �Ÿ��� ��ó�� ���� ã�Ƽ� ��ȯ
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

int shortest_path(int start, int destination) {	// dijkstra�� �̿��� �ּ� ��� ���ã�� 
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
						path[w][set_S[w]] = u;	// ���ŵ� ��� ����
						set_S[w]++;
					}
					else {
						for (int j = 0; j < (set_S[u] + 1); j++) {	// ���ŵ� ��� ����
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
	printf("dijkstra�� ã�� �ּҺ�� ���: ");
	for (int j = 0; j < Max_vertex; j++) {
		if (path[destination][j] != INF) {
			printf("%d, ", path[destination][j]);
		}
	}
	printf("%d\t", destination);
	printf("�Ѻ��: %f\n", distance[destination]);
	set_path();	
	return 0;
}

void depth_first(int start, int end) {		// dfs�� �̿��� ��� ã��
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
		printf("�ּҰ�θ� ã�� �� ������ �Է��Ͻÿ�> ");
		gets(line);
		i = 0;
		while (line[i] == ' ' || line[i] == '\t') i++;	// line���� ���� �Ǵ� \t�� ��� �� ���� ������ ����
		j = 0;
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line�� ����, \t, \0�� �ƴ� ������
			command[j] = line[i];	// ���� ����(line)�� ��ɾ� �κ��� command�� ����
			i++;
			j++;
		}
		command[j] = '\0';	// line���� ����, \t, \0�� ���� ��� command�� �Է��� ������ ���̹Ƿ� command�� �� �ڿ� \0�� ����

		if (strcmp(command, "e") == 0) {	// command�� e�� ��� ���α׷� ���� �ƴ� ��� �Ʒ��� ���
			printf("���α׷��� �����մϴ�.\n");
			break;
		}
		else;

		j = 0;
		while (line[i] == ' ' || line[i] == '\t') i++;	// line�� ���� �Ǵ� \t�ϰ�� �� ������ ����
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line�� ���� �Ǵ� \t, \0�� �ƴ� ������
			start1[j] = line[i];	// ���� ����(line)�� ���� ���� �κ��� start1�� ����
			i++;
			j++;
		}
		start1[j] = '\0';	// line���� ����, \t, \0�� ���� ��� start1�� �Է��� ������ ���̹Ƿ� start1�� �� �ڿ� \0�� ����
		start = atoi(start1);	// start1�� ������ ��ȯ�Ͽ� start�� ����

		j = 0;
		while (line[i] == ' ' || line[i] == '\t') i++;	// line�� ���� �Ǵ� \t�ϰ�� �� ������ ����
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line�� ���� �Ǵ� \t, \0�� �ƴ� ������
			destination1[j] = line[i];	// ���� ����(line)�� ���� ���� �κ��� destination1�� ����
			i++;
			j++;
		}
		destination1[j] = '\0';	// line���� ����, \t, \0�� ���� ��� destination1�� �Է��� ������ ���̹Ƿ� destination1�� �� �ڿ� \0�� ����
		destination = atoi(destination1);	// destination1�� ������ ��ȯ�Ͽ� destination�� ����

		if (start < 0 || start >= Max_vertex || destination < 0 || destination >= Max_vertex) {	// start�� destination�� 0���� �۰ų� �ִ� ���������� ũ�ų� ���� ��� �߸��� �Է�
			printf("�߸��� �Է��Դϴ�.\n");
		}
		else {	// start�� destination�� ����� �Էµ� ���
			if (strcmp(command, "j") == 0) {	// ��ɾ j�� ��� dijkstra�� �̿��Ͽ� �ּ� ��� ��ο� �� ��� ���
				shortest_path(start, destination);	
			}
			else if (strcmp(command, "f") == 0) {	// ��ɾ f�� ��� dfs�� �̿��Ͽ� ã�� ��θ� ���
				printf("depth-first ���: ");
				depth_first(start, destination);
				reset_visited();
				printf("\n");
			}
			else {	// ��ɾ �� ���� ��� (e�� �� ó���� �ٷ�) �߸��� �Է��� 
				printf("�߸��� �Է��Դϴ�.\n");
			}
		}
	}
	return 0;
}