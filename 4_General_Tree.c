#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

typedef struct ano* nodeptr;
typedef struct ano {
	char name[30];	// �̸�
	float gpa;		// ����
	char place[100];	// �ּ�
	nodeptr links[MAX];	// �ڽĵ�
} nodetype;

nodeptr ROOT = NULL;	
nodeptr stack[100];
int top = -1;

nodeptr search_node(nodeptr cur, char sname[]) {	// sname�� ���� name�� ������ �ִ� ��带 ã�� ����
	int i;
	nodeptr rptr;
	if (!cur)		// ��尡 null�̶��
		return NULL;	// null�� return
	
	if (strcmp(cur->name, sname) == 0)	// sname�� ���� name�� ������ �ִ� ��带 ã�� ���
		return cur;		// �� ��带 return
	else {	// sname�� name�� �ٸ� ���
		for (i = 0; cur->links[i] != NULL; i++) {		// ���� ��尡 ������ �ִ� �ڽĵ��� sname�� ���� �� Ȯ��
			rptr = search_node(cur->links[i], sname);	
			if (rptr)	// rptr�� NULL�� �ƴ� ���
				return rptr; // rptr�� ����
		}
		return NULL;	// �ڽĵ鿡�Լ� sname�� ���� name�� ������ �ִ� ��带 ã�� ���� ��� NULL�� ����
	}
}

int read_upper(FILE* fp, char buf[20][50]) {	// txt������ ��ܺθ� �д� �Լ�
	int i, j, k;
	char line[400]; 
	char* cp;
	cp = fgets(line, 400, fp);	// cp�� ������ �а� ���� ����
	if (!cp) {	// cp�� NULL�� ��� ������ �� �о��ų� txt������ ����ִ� ���
		printf("Impossible for the control to reach here.\n");
		return 0;
	}
	else {	// cp�� NULL�� �ƴ� ���
		if (line[0] == '-')	// -�� ���� �� ���� �о����(��ܺθ� ����)
			return 0;

		i = 0;
		j = 0;
		k = 0;
		while (1) {
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
			if (line[j] == '\n')	// ���� �κ��� \n�̿����ٸ� while���� ��������
				break;
			else
				do j++; while (line[j] == ' ');	// �����̿��� ��� ���� �κ��� ������ ��� ���� �κ��� ����
		}
		return i;	// ������� ���� �ܾ��� ���� (ex) �θ� �ڽ�1 �ڽ�2 �ڽ�3 �� ��� 4��)�� ����
	}
}

void read_store_lower_data(FILE* fp) {	// ������ �ϴܺθ� �а� �ش� �����͸� �����ϴ� �Լ�
	char rname[30], address[100];	
	float rgpa;
	nodeptr np;
	int read_num;
	do {
		read_num = fscanf(fp, "%s %f %s", rname, &rgpa, address);	// ������ �а� �̸�, ����, �ּ������� ����
		if (read_num != 3)	// �� �̻� ������ ���� ���
			break;	// while�� Ż��
		else {
			np = search_node(ROOT, rname);	// ���Ͽ��� ���� rname�� name���� ������ ��带 ã��
			if (!np)	// �׷� ��尡 ���� ��� ���ٰ� ȭ�鿡 ���
				printf("�̷� �̸��� ���� ��尡 �����ϴ�.\n");
			else {		// �ִ� ���
				strcpy(np->name, rname);	// �ش� ����� name�� rname�� ����
				np->gpa = rgpa;				// �ش� ����� gpa�� rgpa�� ����
				strcpy(np->place, address);	// �ش� ����� plac�� address�� ����
			}
		}
	} while (1);	// ������ ������ ��� ���� �� ���� �ݺ�
}

void add_data(nodeptr curr, char* sname, char* sname2, float gpa, char* address) {	// ad �θ��̸� �ڽ��̸� ���� �ּҸ� �Է��� ��� �θ��̸��� ���� ��带 �θ���� ��� �ڽ��̸�(sname2), ����(gpa), �ּ� ����(address)�� ������ ���ο� ��带 �ڽĳ��� ����
	nodeptr np;
	nodeptr rnp;
	int i;

	if (sname == NULL || sname2 == NULL || address == NULL)		// �θ��̸��� ���ų� �ڽ��̸��� ���ų� �ּҰ� ���� ���(�Է��� �߸��� ���) ����
		return;
	else {
		np = search_node(curr, sname);	// curr�� �� �ڼյ��� sname�� ���� �̸��� ���� ��带 ã��
		if (!np)	// �׷� ��尡 ���� ��� ���ٰ� ���
			printf("�̷� �̸��� ���� ��尡 �����ϴ�.\n");
		else {		// �ִ� ���
			for (i = 0; np->links[i]; i++) {	// np->links[i]�� NULL�� �� �� ���� i�� ++��
			}
			if (strcmp(np->name, sname) == 0) {	// ���� ��尡 sname�� ���� �̸��� ���� ���(�θ���)
				rnp = (nodeptr)malloc(sizeof(nodetype));	// ���ο� ��带 ����� �ش� ����� �̸��� sname2, ������ gpa, �ּҿ� address�� ����
				strcpy(rnp->name, sname2);
				rnp->gpa = gpa;
				strcpy(rnp->place, address);
				printf("�̸�:%s  ����:%5.2f  �ּ�:%s \n", rnp->name, rnp->gpa, rnp->place); // �ƴ� ��� ���� ��忡 ����� ������ ���
				rnp->links[0] = NULL;		// ������ ����� �ڽĳ�带 NULL�� �����
				np->links[i] = rnp;			// ���� ����� �ڽĳ�忡 ������ ��带 �߰�
				np->links[i + 1] = NULL;	// �ش� links�� ���� links�� NULL�� ����
			}
		}
	}

}

void print_general_tree(nodeptr curr) {	// �Ϲ�Ʈ���� ��� ��带 ���
	int i;
	if (!curr)	// curr�� NULL�� ��� ���� ������ ����
		return;
	printf("�̸�:%s  ����:%5.2f  �ּ�:%s \n", curr->name, curr->gpa, curr->place); // �ƴ� ��� ���� ��忡 ����� ������ ���
	for (i = 0; curr->links[i]; i++)	// ���� ����� �ڽĳ�尡 �����ϴ� ���
		print_general_tree(curr->links[i]);	// �� �ڽĳ���� ������ �а� �����
}

void print_descendant(nodeptr curr, char* sname) {	// ��� �ڼյ��� 1�ٿ� 1�� ���
	int i;
	if (!curr)	// ���� ��尡 NULL�̶�� return��
		return;
	if (strcmp(sname, curr->name) != 0)	// ���� ����� �̸��� sname�� ���� ���� ���
		printf("%s \n", curr->name);	// �̸��� ��� (����� sname�� ������� �ʰ� �� �ڼյ鸸�� �����)
	for (i = 0; curr->links[i]; i++)	// �ڽ� ��尡 �����Ѵٸ� �ش� �ڽĵ��� �̸��� ���
		print_descendant(curr->links[i], sname);
}

nodeptr search_parent_node(nodeptr cur, char sname[]) {	// �θ��带 ã�Ƽ� ������
	int i;
	nodeptr rptr;
	if (!cur)	// ���� ��尡 NULL�̶�� NULL�� ����
		return NULL;
	if (strcmp(cur->name, sname) == 0) {	// ���� ���� ����� �̸��� sname�� ���� ���(sname�� ����� ù��° ����� ���) 
		printf("�����ڸŰ� �������� �ʽ��ϴ�. \n");		// ù��° ����� �����ڸŴ� �������� �ʴ´ٰ� ���
		return NULL;	// NULL�� ����
	}
	
	for (i = 0; cur->links[i] != NULL; i++) {	// �ڽĳ�尡  NULL�� �ƴ� ���
		if (strcmp(cur->links[i]->name, sname) == 0) {	// �ڽ� ����� �̸��� sname�� ���� ���
			return cur;		// ���� ���(sname�� �̸����� ���� ����� �θ���)�� ����
		}
		else {	// �ƴ� ���
			rptr = search_parent_node(cur->links[i], sname);	// sname�� �̸����� ���� ����� �θ��带 ��� ã��
			if (rptr)
				return rptr;
		}
	}
	return NULL;	// sname�� �̸����� ���� ��尡 ���� ��� NULL�� ����
}

void print_brother(nodeptr curr, char* sname) {		// ���� �ڸ��� �̸��� ��� (curr�� �θ����� ������ ������ ����)
	int i;
	if (!curr)	
		return;
	
	for (i = 0; curr->links[i]; i++) {	// �θ����� �ڽ� ���� ��
		if (strcmp(sname, curr->links[i]->name) != 0)	// �ش� ���(sname�� �̸����� ���� ���)�� ������ ��� ���� �ڸŵ��� �̸��� �����
			printf("%s \n", curr->links[i]->name);
	}
	if (i == 1) {	// ���� �θ����� �ڽ��� ���ۿ� ���ٸ� �����ڸŰ� ���ٰ� �����
		printf("�����ڸŰ� �������� �ʽ��ϴ�.\n");
	}
}

void print_nodecount(nodeptr curr, int* count) {	// Ʈ�� ���� ��� ����� ���� �� count�� ������ ����(����)��
	int i;
	*count = *count + 1;	
	if (!curr) {	// curr�� NULL�� ��� ����
		return;
	}
	for (i = 0; curr->links[i]; i++) {	// NULL�� �ƴ϶�� �ڽĳ�尡 �ִ� ���
		print_nodecount(curr->links[i],count);	// �ش� �ڽ� ���� �̵��Ͽ� ����� ������ ���� count�� ������ ����(����)��
	}
}

void print_levelnode(nodeptr curr, int* level,int* lvcount) {	// �Է��� level�� ���� level�� �ִ� ������ ���
	int i;
	if (!curr)	// curr�� NULL�� ��� ����
		return;

	*lvcount = *lvcount + 1;	// �� �̵����� level�� ������
	if (*lvcount == *level)		// ���� ����� level�� �Է��� level�� ���� ��� ���� ����� �̸� ���
		printf("%s ", curr->name);

	for (i = 0; curr->links[i]; i++) {	// �ڽ� ��尡 �ִ� ���
		print_levelnode(curr->links[i], level, lvcount);	// �ش� �ڽ� ���� �̵��Ͽ� �Է��� level�� ���� level�� ��� �̸� ���
	}
	*lvcount = *lvcount - 1;	// ���� �Լ��� ���� ������ �θ���� �̵��ϴ� ��� level�� ����
}

void make_node_and_attach_to_parent(nodeptr parent, char* tname, int loc) {		// �� ��带 ����� �θ� ������
	nodeptr np1;
	np1 = (nodeptr)malloc(sizeof(nodetype));	// �� ��带 ����(���� �Ҵ�)
	strcpy(np1->name, tname);	// �� ����� �̸����� tname�� ����
	np1->links[0] = NULL;		// �� ����� �ڽĳ�带 NULL�� ����
	parent->links[loc] = np1;	// �θ����� links(�ڽĳ��)�� ������ ��带 ����
}

void dfs_height(nodeptr cur, int par_height, int* tree_height) {	// ��ü Ʈ���� ���̸� tree_height�� ����(����)��
	int my_height = par_height + 1;		// ������ ���̴� �θ��� ���� + 1 
	int i;
	if (*tree_height < my_height)	// ���� ���Ҵ� Ʈ���� ����(tree_height)���� ������ ���̰� �� ū ���
		* tree_height = my_height;	// ���� ���� Ʈ���� ����(tree_height)�� ������ ���̸� ����(�ᱹ tree_height�� ��ü Ʈ���� ����(���� ���Ҵ� ����)�� �����)
	for (i = 0; cur->links[i]; i++) {	// �ڽ� ��尡 �ִ� ���
		dfs_height(cur->links[i], my_height, tree_height);	// �ش� �ڽ��� ���̿� ������ tree_height�� ��
	}
	return;	
}

int dfs_depth(nodeptr cur, int par_height, char* sname) {	// sname�� �̸����� ���� ����� ���̸� ����
	int my_height = par_height + 1;	// ������ ���̴� �θ��� ���� + 1
	int i;
	int res;
	if (strcmp(cur->name, sname) == 0) {	// ���� ����� �̸��� sname�� ���� ���
		printf("Height of the node of %s : %d\n", sname, my_height);	// ���� ����� ����(����)�� ���
		return 1;
	}
	for (i = 0; cur->links[i]; i++) {	// ���� ����� �̸��� sname�� �ٸ��� �ڽĳ�尡 ���� ���
		res = dfs_depth(cur->links[i], my_height, sname);	// �ڽ� ������ �̸��� sname�� �̸����� ���� ��尡 �ִ��� ã�� �����Ѵٸ� �ش� ����� ���̸� �����
		if (res)
			return 1;
	}
	return 0;	// ������ ��� 0�� ������
}

void push_stack(nodeptr nptr) {	
	top++;	// top�� 1��ŭ ����
	stack[top] = nptr;	// top�� nptr�� ���� ����
}

void pop_stack() {	// top�� 1��ŭ ����
	top--;
}

int dfs_ancestors(nodeptr cur, char* sname) {	// sname�� �̸����� ���� ����� ������� ���
	int i, res;
	if (strcmp(cur->name, sname) == 0) {	// ���� ����� �̸��� sname�� ���� ���
		printf("This person's ancestors: ");	// �� ����� ������ ���
		for (i = 0; i <= top; i++)	// top�� i���� ũ�ų� ���� ���
			printf("%s ", stack[i]->name);	// �ش� ������ �̸��� ���(������ �̸� ���)
		printf("\n");
		return 1;
	}
	// ���� ����� �̸��� sname�� �ٸ� ���
	push_stack(cur);	// top�� 1��ŭ ������Ű�� cur�� ������ ���� ��
	for (i = 0; cur->links[i]; i++) {	// cur�� �ڽĵ��� �̸��� sname�� �̸����� ���� ��尡 �ִ��� Ȯ���ϰ� �� ������ stack�� ����� ������� �̸��� �����
		res = dfs_ancestors(cur->links[i], sname);
		if (res)
			return 1;
	}

	pop_stack();	// ���� �Լ��� �����ٸ� pop���� stack�� �������� ����(�����Ͱ� �������°� �ƴ����� ���߿� ���ο� �����ͷ� ä������ ������ ������ ������� ���� ��)
	return 0;		// sname�� �̸����� ���� ��尡 ���ٸ� 0�� ����
}

int main(void) {
	char buf[20][50];
	int num_persons, k;
	nodeptr np;

	FILE* fp;
	fp = fopen("tree_data.txt", "r");	// tree_data.txt������ ����
	if (!fp) {	// ������ NULL�̶�� ����ǥ��
		printf("file open error.\n");
		return;
	}

	do {
		num_persons = read_upper(fp, buf);	// ������ ��ܺθ� �� �پ� �а� �� �ȿ� ����� ����� ���� num_persons�� ����
		if (num_persons == 0)	// ����� ���ٸ� �� while���� ��������
			break;
		if (!ROOT) {	// ROOT�� NULL�̶�� ù ��带 ����(�� ó�� ���� ����� data�� �θ��尡 �ǰ� �������� �ڽĳ�尡 ��)
			np = (nodeptr)malloc(sizeof(nodetype));	
			strcpy(np->name, buf[0]);
			ROOT = np;
			np->links[0] = NULL;
			for (k = 1; k < num_persons; k++) {	// �ش� buf[k]�� ����� �ܾ �̸����� ������
				make_node_and_attach_to_parent(np, buf[k], k - 1);	// �ڽĳ�带 �����ϰ� ������
			}
			np->links[k - 1] = NULL;	// �ڽĳ�尡 �������� ���� ��ũ�� NULL�� ����(ex)�ڽ��� 3���� ��� np->links�� links[0],[1],[2]���� �����Ǹ� �� �ٷ� ������ [3]�� NULL�� ����
		}
		else {	// ROOT�� NULL�� �ƴ϶�� �ι�° �� ���ϸ� �д� ���̹Ƿ�
			np = search_node(ROOT, buf[0]);	// �� ��° �� ������ ù��° �ܾ �̸����� ������ ��带 ã��(�θ��尡 ��)
			if (!np) {	// ������ ������ ��忡 ������ ���� ù��° �ܾ�(buf[0])�� �Էµ� �̸��� ������ ��尡 ���� ���(�θ���� ���� ��尡 ���� ���) ����
				printf("Error: 2° �� ������ ù �̸��� ��尡 ����.\n");
				getchar();
			}
			for (k = 1; k < num_persons; k++) {	// �� �ڿ� �Էµ� �ܾ �̸����� ������
				make_node_and_attach_to_parent(np, buf[k], k - 1);	// �ڽĳ�带 �����ϰ� ������
			}
			np->links[k - 1] = NULL;	// �ڽĳ�尡 �������� ���� ��ũ�� NULL�� ����
		}
	} while (1);
	read_store_lower_data(fp);	// ������ ������ Ʈ���� �� ��忡 �̸�, ����, �ּ��� ������ ������ �ϴܺθ� �о� ����
	print_general_tree(ROOT);	// ������� ������� Ʈ���� ��� ����� �������� ���

	do {
		char command[400];
		char line[400];
		char name[400];
		char name2[400];
		float gpa2;
		char gpa[400];
		char address[400];

		printf("Type a command> ");
		gets(line);		// line�� �Է� ����

		int i = 0;
		while (line[i] == ' ' || line[i] == '\t') i++;	// line���� ���� �Ǵ� \t�� ��� �� ���� ������ ����
		int k = 0;
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line�� ����, \t, \0�� �ƴ� ������
			command[k] = line[i];	// ���� ����(line)�� ��ɾ� �κ��� command�� ����
			i++;
			k++;
		}
		command[k] = '\0';	// line���� ����, \t, \0�� ���� ��� command�� �Է��� ������ ���̹Ƿ� command�� �� �ڿ� \0�� ����

		if (strcmp(command, "ex") == 0) {	// command�� ex �� ���	while���� ��������(������ ������)
			break;
		}
		else if (strcmp(command, "ht") == 0) {	// command�� ht�� ���
			int tree_height = 0;
			dfs_height(ROOT, 0, &tree_height);	// Ʈ���� ��������(tree_height)�� ���� (���� ū level = tree_height)
			printf("Height of the tree : %d \n", tree_height);	// ��ü Ʈ���� ����(height)�� ���
			continue;	// ���� while������ �Ѿ(continue�� ���ϸ� ���� ���� while���� else�� �ɷ� �°� �Է������� wrong command�� ��µ�)
		}
		else if (strcmp(command, "nm") == 0) {	// command�� nm�� ���
			int count = 0;
			print_nodecount(ROOT, &count);	// ��� ����� ���� ���� �� ������ count�� ����
			printf("Number of nodes : %d \n", count);	// ��� ����� ������ ���
			continue;	// ���� while������ �Ѿ(continue�� ���ϸ� ���� ���� while���� else�� �ɷ� �°� �Է������� wrong command�� ��µ�)
		}
		else;	// �� ���� ��� (command �̸� �Ǵ� command �̸� �̸� ���� �ּ� �Ǵ� �߸� �Է��� ���) ��� ����

		k = 0;	// k�� 0���� �ʱ�ȭ
		while (line[i] == ' ' || line[i] == '\t') i++;	// line�� ���� �Ǵ� \t�ϰ�� �� ������ ����
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line�� ���� �Ǵ� \t, \0�� �ƴ� ������
			name[k] = line[i];	// ���� ����(line)�� �̸� �κ��� name�� ����
			i++;
			k++;
		}
		name[k] = '\0';	// line���� ����, \t, \0�� ���� ��� name�� �Է��� ������ ���̹Ƿ� name�� �� �ڿ� \0�� ����

		if (strcmp(command, "se") == 0) {	// command�� se�� ���
			np = search_node(ROOT, name);	// �Է��� �̸�(name)�� ���� ��带 ã��
			if (np)	// ã�� ��� �ش� ����� ���� ���
				printf("Search success:	%s %5.2f %s\n", np->name, np->gpa, np->place);
			else printf("Such a person does not exist.\n");	// �Է��� �̸��� ���� ��尡 ���� ��� �ش� ���� �������� �ʴ´ٰ� ���
			continue;	// ���� while������ �Ѿ(continue�� ���ϸ� ���� ���� while���� else�� �ɷ� �°� �Է������� wrong command�� ��µ�)
		}
		else if (strcmp(command, "dp") == 0) {	// command�� dp�� ���
			int res = dfs_depth(ROOT, 0, name);	// �Է��� �̸�(name)�� ���� ����� ���̸� ã�� �����
			if (!res)	// ã�� ���� ���(return 0�� ���)
				printf("Such a name does not exist in the tree.\n");	// �Է��� �̸�(name)�� ���� ��尡 ���ٰ� ���
			continue;	// ���� while������ �Ѿ(continue�� ���ϸ� ���� ���� while���� else�� �ɷ� �°� �Է������� wrong command�� ��µ�)
		}
		else if (strcmp(command, "ac") == 0) {	// command�� ac�� ���
			top = -1;	// top�� -1�� ����
			int res = dfs_ancestors(ROOT, name);	// stack�� �̿��Ͽ� �Է��� �̸�(name)�� ���� ����� ������� �����
			if (!res)	// ������ ���(�Է��� �̸��� ���� ��尡 ���� ���)
				printf("Such a name does not exist in the tree.\n");	// �Է��� �̸�(name)�� ���� ��尡 ���ٰ� ���
			continue;	// ���� while������ �Ѿ(continue�� ���ϸ� ���� ���� while���� else�� �ɷ� �°� �Է������� wrong command�� ��µ�)
		}
		else if (strcmp(command, "na") == 0) {	// command�� na�� ���
			np = search_node(ROOT, name);	// �Է��� �̸�(name)�� ��带 ã��
			if (np)	// ��带 ã�� ���
				print_descendant(np, name);	// �ش� ����� �ڽĵ��� ��� �����
			else printf("Such a person does not exist.\n");	// ��带 ã�� ���� ���(�Է��� �̸�(name)�� ��尡 ���� ���) �Է��� �̸�(name)�� ���� ��尡 ���ٰ� ���
			continue;	// ���� while������ �Ѿ(continue�� ���ϸ� ���� ���� while���� else�� �ɷ� �°� �Է������� wrong command�� ��µ�)
		}
		else if (strcmp(command, "br") == 0) {	// command�� br�� ���
			np = search_parent_node(ROOT, name);	// �Է��� �̸�(name)�� �θ��带 ã��
			if (np)	// �θ��带 ã�� ���
				print_brother(np, name);	// �Է��� �̸�(name)�� ���� ����� ���� �ڸŵ��� �����
			else printf("Such a person does not exist.(Or that person's node is first node)\n");	// �θ��带 ã�� ���� ��� �Է��� �̸�(name)�� ���� ��尡 ���ų� ù��° ���� �θ��尡 ���� ��� �� �� �ϳ���� ���
			continue;	// ���� while������ �Ѿ(continue�� ���ϸ� ���� ���� while���� else�� �ɷ� �°� �Է������� wrong command�� ��µ�)
		}
		else if (strcmp(command, "LV") == 0) {	// command�� LV�� ���
			int level = atoi(name);		// �Է��� ����(name)�� ������ �ٲ� level�� ����
			int lvcount = 0;	// �� ����� lv�� ��Ÿ��
			if (level > 0) {	// level�� 0���� ū ���(����� �� �Է��� ���)
				print_levelnode(ROOT, &level, &lvcount);	// �Է��� level�� ���� level�� ������ �����
				printf("\n");
			}
			else printf("Wrong command.\n");	// level�� 0���� ���� ��� �߸��� �Է���
			continue;	// ���� while������ �Ѿ(continue�� ���ϸ� ���� ���� while���� else�� �ɷ� �°� �Է������� wrong command�� ��µ�)
		}
		else; // �� ���� ��� (command �̸� �̸� ���� �ּ� �Ǵ� �߸� �Է��� ���) ��� ����

		k = 0;	// k�� 0���� �ʱ�ȭ
		while (line[i] == ' ' || line[i] == '\t') i++;	// line�� ���� �Ǵ� \t�ϰ�� �� ������ ����
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line�� ���� �Ǵ� \t, \0�� �ƴ� ������
			name2[k] = line[i];		// ���� ����(line)�� �ڽĳ���̸� �κ��� name2�� ����
			i++;
			k++;
		}
		name2[k] = '\0';	// line���� ����, \t, \0�� ���� ��� name2�� �Է��� ������ ���̹Ƿ� name2�� �� �ڿ� \0�� ����

		k = 0;	// k�� 0���� �ʱ�ȭ
		while (line[i] == ' ' || line[i] == '\t') i++;	// line�� ���� �Ǵ� \t�ϰ�� �� ������ ����
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line�� ���� �Ǵ� \t, \0�� �ƴ� ������
			gpa[k] = line[i];	// ���� ����(line)�� ���� �κ��� gpa�� ����
			i++;
			k++;
		}
		gpa[k] = '\0';		// line���� ����, \t, \0�� ���� ��� gpa�� �Է��� ������ ���̹Ƿ� gpa�� �� �ڿ� \0�� ����
		gpa2 = (float)atof(gpa);	// �Է¹��� gpa�� float���·� ��ȯ

		k = 0;	// k�� 0���� �ʱ�ȭ
		while (line[i] == ' ' || line[i] == '\t') i++;	// line�� ���� �Ǵ� \t�ϰ�� �� ������ ����
		while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')) {	// line�� ���� �Ǵ� \t, \0�� �ƴ� ������
			address[k] = line[i];	// ���� ����(line)�� �ּ� �κ��� address�� ����
			i++;
			k++;
		}
		address[k] = '\0';	// line���� ����, \t, \0�� ���� ��� address�� �Է��� ������ ���̹Ƿ� address�� �� �ڿ� \0�� ����

		if (strcmp(command, "ad") == 0) {	// command�� ad�� ���
			add_data(ROOT, name, name2, gpa2, address);	// name�� �θ���� �Ͽ� �̸��� name2, ������ gpa2, �ּҸ� address�� ���� �� ��带 �ڽĳ��� ������
		}
		else {	// �� ���� ��� (�߸��� �Է��� ���)
			printf("Wrong command.\n");	// �߸��� �Է��̶�� ���
		}
	} while (1);
}