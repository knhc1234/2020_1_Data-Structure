#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct anod* TreePointer;
typedef struct anod {		// �� ����� ����
	int sno;				// �й�
	char name[50];			// �̸�
	TreePointer leftChild, rightChild;	// ����� �ڽĿ� ���� ������
} Ty_Node;

TreePointer In(TreePointer nod, char getname[50], int getsno, int *level, int *errorcount);		// ���ο� ��带 �ְ� �������� �� �� ����� ������ ���(Ia���� �Է� ���н� ������ ��� ���� ���⵵ ��) 
TreePointer Ia(TreePointer nod);	// sdata.txt ������ ��� ���� �����ϸ� �̹� �����ϹǷ� ���� ���е� ���ڵ��� ���� ���
void Sp(TreePointer nod);			// ��� BST ���� ��� ���ڵ带 �̸� ������ ��� (inorder traversal �̿�)
TreePointer De(TreePointer nod, char getname[50], int *record);	// ������ ����� �̸��� �Է¹޾� �̸� ���� ��带 �����ϸ� ���� �۾� �߿� �ٸ� ���� �̵��� �Ͼ ���ڵ��� �л��� �̸��� ���
TreePointer Da(TreePointer nod);	// sdata.txt ȭ���� ��� ����� �����ϴ� �۾��� �����ϸ� ���� �۾����� �߻��� ������ �� �̵�Ƚ���� ���
void Se(TreePointer nod, char getname[50], int* level);	// �̸��� �Է� �޾� �̸� ���� ��带 ã�Ƽ� �й� �� �̸�, �� ����� ������ ���
void Ht(TreePointer nod);			// ��ü ����Ž��Ʈ���� ���̸� ���Ͽ� ���(���̸� ���ϴ� �� FindHeight�� �̿�)
void FindHeight(TreePointer nod, int* level, int* height);	// ���� Ž�� Ʈ���� ���̸� ���ϴ� �Լ�
void Le(TreePointer nod);			// �� BST �� ��� �� �ڽ��� 1 ���� ����� ��, 0 ���� ����� ���� �˾Ƴ��� ���(����� ���� ����ϴ� �� Lecount�� �̿�)
void Lecount(TreePointer nod, int* lecount, int* onechildcount);	// BST�� ��忡�� �ڽ��� 1 ���� ����� ���� 0���� ����� ���� ����
void Ch(TreePointer nod, char getname[50]);	// �̸��� �Է� �޾Ƽ� �̸� ���� ����� immediate successor ã�Ƽ� �� ������ ���(������ ���ٰ� �����)
void Ex(int* endcount);				// while���� �������� ���α׷��� �����ϰ� ����� �Լ�

int main(void) {

	int endcount = 1;		// ex�� �Է��� ��� endcount�� 0�� �Ǿ� while���� �Բ� ���α׷��� �����
	TreePointer nod = NULL;
	nod = Ia(nod);			// ������ �����͸� �о� ��� ���� ��忡 ����
	system("cls");
	while (endcount) {		// endcount�� 0�� �� ��(ex �Է�)���� �ݺ�
		char name1[50] = { 0 };	// �Է� ���� �̸�	(�� while�� ���� �ʱ�ȭ)
		int sno1 = 0;			// �Է� ���� �й�	(�� while�� ���� �ʱ�ȭ)
		int level = 0;			// �ش� ����� ����(level)	(�� while�� ���� �ʱ�ȭ)
		int errorcount = 0;		// Ia���� �̹� �����Ͽ� ���� ���е� ���ڵ��� ��	
		char fullcommand[100] = { 0 };	// �Է� ���� ����� 1���� ����	(�� while�� ���� �ʱ�ȭ)
		char order[100] = { 0 };			// �Է� ���� ����� �۾� ��ɾ�(in, ia, sp, de, da, se, ht, le, ch, ex) ����	(�� while�� ���� �ʱ�ȭ)
		char string_sno[100] = { 0 };	// �Է� ���� �л��̸��� ���ڿ� ���·� ����	(�� while�� ���� �ʱ�ȭ)
		int i = 0;	
		int j = 0;
		int record = 0;		// da���� �̿�Ǵ� ������ �� �̵�Ƚ��	

		printf("������ �۾��� (in, ia, sp, de, da, se, ht, le, ch, ex) ? ");
		gets(fullcommand);	// ������ �۾��� �Է¹���
		while (fullcommand[i] != ' '&& fullcommand[i] != '\0') {	// ���� Ȥ�� \nŰ�� �ԷµǱ� �������� ��� �ܾ order�� ����(ù��° ��ɾ�� ������ �۾��� �з��ϱ� ����)
			order[i] = fullcommand[i];
			i++;
		}

		if (strcmp(order, "in") == 0) {	// order�� ����� ù��° ��ɾ in�� ���
			int checkerror = 0;	// �߸��� �Է��� �� ��츦 Ȯ���ϱ� ���� �뵵 ex) in �̸� ����
			i++;				// ����� ���� ��ĭ �������� �̵�
			while ((fullcommand[i] != ' ')&&(fullcommand[i]!='\0')) {	// ���Ⱑ �ԷµǱ� �������� ��� �ܾ string_sno�� ����(���� �߸��� �Է��� ��쿡 ����(in �� �Է��� ���))
				string_sno[j] = fullcommand[i];
				i++;
				j++;
			}
			sno1 = atoi(string_sno);		// string_sno�� ���ڿ��� ������ִ� ������ sno1(�Է� ���� �й�)�� int������ �ٲپ� ����

			if (sno1 == 0|| fullcommand[i]=='\0') {	// �Է��� �߸��Ǿ��ٸ� (in�� �Է��� ��� �Ǵ� in ���� �̸��� ������ ���� ���� ���)	
				system("cls");	
				printf("�߸��� �Է��Դϴ�.\n");	
				checkerror++;	// ������ �����Ƿ� ���� ������� ������ �ȵǵ��� ��ġ��
			}
			
			if (checkerror == 0) {	// �Է¿� ���ݱ��� ������ ���� ���
				i++;	// ����� ���� ��ĭ �������� �̵�
				j = 0;	// 0���� �ʱ�ȭ(���� �����)
				while (fullcommand[i] != '\0') {	// \n�� �Էµ� ������(null�� ������ ������)�� ��� �ܾ name1(�Է� ���� �̸�)�� ����
					name1[j] = fullcommand[i];
					i++;
					j++;
				}

				if (checkerror == 0) {	// ��� �Է��� ����� ����� ���
					system("cls");	
					nod = In(nod, name1, sno1, &level, &errorcount);	// �Է� ���� �̸��� �л� ������ ���� ��带 ���� �ְ� �������� �� �� ����� ������ �����( �̸� �ߺ��� �Ұ���)
				}
			}
		}
		else if (strcmp(order, "ia") == 0) {	// order�� ����� ù��° ��ɾ ia�� ���
			system("cls");
			nod = Ia(nod);	// sdata.txt ������ ��� ���� �����ϸ� �̹� �����ϹǷ� ���� ���е� ���ڵ��� ���� �����
		}
		else if (strcmp(order, "sp") == 0) {	// order�� ����� ù��° ��ɾ sp�� ���
			system("cls");	
			printf("ȭ���� ������ ������ �����ϴ�:\n");
			Sp(nod);		// ��� BST ���� ��� ���ڵ带 �̸� ������ �����
		}
		else if (strcmp(order, "de") == 0) {	// order�� ����� ù��° ��ɾ de�� ���
			int checkerror = 0;	// �߸��� �Է��� �� ��츦 Ȯ���ϱ� ���� �뵵 ex) de�� �Է�
			if (fullcommand[i] == '\0') {	// ��ɾ�� de�� �Է��� ��� �߸��� �Է�
				printf("�߸��� �Է��Դϴ�.\n");
				checkerror++;	// checkerror�� 1 ����
			}
			if (checkerror == 0) {	// ������ �߻����� ���� ���
				i++;	// ����� ���� ��ĭ �������� �̵�
				while (fullcommand[i] != '\0') {	// \n�� �Էµ� ������(null�� ������ ������)�� ��� �ܾ name1(�Է� ���� �̸�)�� ���� 
					name1[j] = fullcommand[i];
					i++;
					j++;
				}
				system("cls");
				nod = De(nod, name1, &record);	// �Է� ���� �̸��� ���� ��带 �����ϸ� ���� �۾� �߿� �ٸ� ���� �̵��� �Ͼ ���ڵ��� �л��� �̸��� ���
			}
		}
		else if (strcmp(order, "da") == 0) {	// order�� ����� ù��° ��ɾ da�� ���
			system("cls");		
			nod = Da(nod);	// sdata.txt ȭ���� ��� ����� �����ϴ� �۾��� �����ϸ� ���� �۾����� �߻��� ������ �� �̵�Ƚ���� ���
		}
		else if (strcmp(order, "se") == 0) {	// order�� ����� ù��° ��ɾ se�� ���
			int checkerror = 0;	// �߸��� �Է��� �� ��츦 Ȯ���ϱ� ���� �뵵 ex) se�� �Է�
			if (fullcommand[i] == '\0') {	// ��ɾ�� se�� �Է��� ��� �߸��� �Է�
				printf("�߸��� �Է��Դϴ�.\n");
				checkerror++;	// checkerror�� 1 ����
			}
			if (checkerror == 0) {	// ������ �߻����� ���� ���
				i++;	// ����� ���� ��ĭ �������� �̵�
				while (fullcommand[i] != '\0') {	// \n�� �Էµ� ������(null�� ������ ������)�� ��� �ܾ name1(�Է� ���� �̸�)�� ���� 
					name1[j] = fullcommand[i];
					i++;
					j++;
				}
				system("cls");
				Se(nod, name1, &level);	// �Է� ���� �̸��� ���� ��带 ã�Ƽ� �й� �� �̸�, �� ����� ������ ���
			}
		}
		else if (strcmp(order, "ht") == 0) {	// order�� ����� ù��° ��ɾ ht�� ���
			system("cls");
			Ht(nod);	// ��ü ����Ž��Ʈ���� ���̸� ���Ͽ� ���
		}	
		else if (strcmp(order, "le") == 0) {	// order�� ����� ù��° ��ɾ le�� ���
			system("cls");
			Le(nod);	// �� BST �� ��� �� �ڽ��� 1 ���� ����� ��, 0 ���� ����� ���� �˾Ƴ��� ���
		}
		else if (strcmp(order, "ch") == 0) {	// order�� ����� ù��° ��ɾ ch�� ���
			int checkerror = 0;	// �߸��� �Է��� �� ��츦 Ȯ���ϱ� ���� �뵵 ex) ch�� �Է�
			if (fullcommand[i] == '\0') {	// ��ɾ�� ch�� �Է��� ��� �߸��� �Է�
				printf("�߸��� �Է��Դϴ�.\n");
				checkerror++;	// checkerror�� 1 ����
			}
			if (checkerror == 0) {	// ������ �߻����� ���� ���
				i++;	// ����� ���� ��ĭ �������� �̵�
				while (fullcommand[i] != '\0') {	// \n�� �Էµ� ������(null�� ������ ������)�� ��� �ܾ name1(�Է� ���� �̸�)�� ���� 
					name1[j] = fullcommand[i];
					i++;
					j++;
				}
				system("cls");
				Ch(nod, name1);	// �Է� ���� �̸��� ���� ����� immediate successor ã�Ƽ� �� ������ ���(������ ���ٰ� �����)
			}
		}
		else if (strcmp(order, "ex") == 0) {	// order�� ����� ù��° ��ɾ ex�� ���
			system("cls");
			Ex(&endcount);	// ���α׷��� ������
		}
		else {	// �Է��� �߸� �޾��� ���
			printf("�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���.\n");
		}
	}
	return 0;
}

TreePointer In(TreePointer nod, char getname[50], int getsno, int *level, int *errorcount) {	// ���ο� ��带 �ְ� �������� �� �� ����� ������ ���(Ia���� �Է� ���н� ������ ��� ���� ���⵵ ��) 
	if (nod == NULL) {	// ��忡 �� ����� ���(������ ù��° ����̰ų� ��� �̵��Ͽ� �Է� ���� ������ ����� ��尡 �� �ڸ��� ã��)
		nod = (TreePointer)malloc(sizeof(Ty_Node));	// �����Ҵ� �� ��忡 �Է� ���� �̸�(getname)�� �Է� ���� �й�(getsno)�� ����, leftChild rightChild�� null�� ����� �������� �� �� ����� ���� ���
		strcpy(nod->name, getname);	
		nod->sno = getsno;
		nod->leftChild = NULL;
		nod->rightChild = NULL;
		printf("�Է� ����!	%d %s level %d\n", nod->sno, nod->name, *level);
	}
	else {	// ��尡 �� ��尡 �ƴ� ��� 
		if (strcmp(nod->name, getname) == 1) {	// ����� �̸��� �Է¹��� �̸����� �ļ������(�Է� ���� value�� ����� value���� ���� ���)
			*level = *level + 1;	// ����� ������ 1 �ø���
			nod->leftChild = In(nod->leftChild, getname, getsno, level, errorcount);	// leftChild�� �̵�(����ؼ� ����)
		}
		else if (strcmp(nod->name, getname) == -1) {	// ����� �̸��� �Է¹��� �̸����� �ռ������(�Է� ���� value�� ����� value���� ū ���)
			*level = *level + 1;	// ����� ������ 1 �ø���
			nod->rightChild = In(nod->rightChild, getname, getsno, level, errorcount);	// rightChild�� �̵��Ͽ� ã�ƺ�(����ؼ� ����)
		}
		else {	// ����� �̸��� �Է� ���� �̸��� ���� ��� �̹� �����ϴ� ����� ��� 
			printf("�̹� �����ϴ� ����Դϴ�.\n");	
			*errorcount = *errorcount + 1;	// Ia���� �̹� �����Ͽ� ���Կ� �����ϴ°� �� �� �̿� ��
		}
	}
	return nod;	// ���� ���� �����Ͽ� ���������� ���� ������ ��带 ������ ��ü��带 �����ϰ� ��
}

TreePointer Ia(TreePointer nod) {	// sdata.txt ������ ��� ���� �����ϸ� �̹� �����ϹǷ� ���� ���е� ���ڵ��� ���� ���
	char name1[50];	// ���Ͽ��� ���� �̸� ����
	int sno1;		// ���Ͽ��� ���� �й�����
	int res;		// ������ �����͸� ����� �о� ������ Ȯ���ϱ� ���� ����
	int level;		// �ش� ����� ����(level)
	int errorcount = 0;	// ������ �о ���� �� �� �̹� ��忡 �����Ͽ� ���� ���е� ���ڵ��� ��

	FILE* fp = fopen("sdata.txt", "r");	// sdata.txt������ ����
	while (1) {
		level = 0;	// �� while�� ���� level�� 0���� �ʱ�ȭ(0���� �ʱ�ȭ�Ͽ� �ٽ� ����)
		res = fscanf(fp, "%d %s", &sno1, name1);	// ���Ͽ��� �й��� �̸��� �о� sno1�� name1�� ���� ����
		if (res < 2) {	// ������ ������ �� �޾Ƶ����� ���߰ų� ������ ������ ������ ��� Ȥ�� �� �̻� ���� ������ ���� ��� while���� ��������
			break;
		}

		nod = In(nod, name1, sno1, &level, &errorcount);	// ���Ͽ��� ���� �������� ���� ��带 ������(���� ��忡 ���Ͽ� �ִ� ��尡 �̹� �����Ͽ� ���Կ� ������ ��� errorcount�� 1 ������)
	}
	printf("�̹� �����Ͽ� ���� ������ ����� ��: %d\n", errorcount);	// �̹� �����Ͽ� ���� ������ ����� ���� ���
	fclose(fp);	// sdata.txt������ ����
	return nod;	// ��ü ��带 ������
}

void Sp(TreePointer nod) {	// �̿� Ž�� Ʈ���̹Ƿ� leftChild�� �̸� ������ ���� ������ �״����� �θ��� �׸��� ���� �ڿ� ���� ���� rightChild�̹Ƿ� �� ������� ������ ����Ѵ�.
	if (nod != NULL) {
		Sp(nod->leftChild);		// ���� ��� Ž��
		printf("%s, %d\n", nod->name, nod->sno);	// �ڽ��� ��� ���� ���
		Sp(nod->rightChild);	// ������ ��� Ž��
	}
} 

TreePointer De(TreePointer nod, char getname[50], int *record) {	// ������ ����� �̸��� �Է¹޾� �̸� ���� ��带 �����ϸ� ���� �۾� �߿� �ٸ� ���� �̵��� �Ͼ ���ڵ��� �л��� �̸��� ���
	TreePointer parent, successor;	// �θ� ���(immediate successor�� �θ� ����)�� immediate successor����� ������ ���� ������ ����
	if (nod == NULL) {	// �Է� ���� �̸��� ���� ��尡 ���� ��� 
		printf("��尡 �������� �ʽ��ϴ�.\n");
		return NULL;
	}
	if (strcmp(nod->name, getname) == 1) {	// ����� �̸��� �Է¹��� �̸����� �ļ������(�Է� ���� value�� ����� value���� ���� ���)
		nod->leftChild = De(nod->leftChild, getname, record);	// leftChild�� �̵�(��峢�� ����ؼ� ����)
	}
	else if (strcmp(nod->name, getname) == -1) {	// ����� �̸��� �Է¹��� �̸����� �ռ������(�Է� ���� value�� ����� value���� ū ���)
		nod->rightChild = De(nod->rightChild, getname, record);	// leftChild�� �̵�(��峢�� ����ؼ� ����)
	}
	else {	// ����� �̸��� �Է� ���� �̸��� ���� ���
		if (nod->leftChild != NULL) {	// �ڽ� ��尡 �� �� �ְų� ���� �ڽ� ��常 �ִ� ���
			successor = nod->leftChild;	// ���� ����� leftChild���� �ѹ� �̵��Ͽ� immediate successor��忡 ���� ����(immediate successor�� ���ϱ� ����)
			parent = nod;	// �θ� ��忡 ���� ����� ������ ����
			while (successor->rightChild != NULL) {	// nod�� leftChild�� ��� �� ���� ū ��� �� rightChild�� ��� �̵��Ͽ� ���� �ִ� ��尡 immediate successor��
				parent = successor;	// �θ� ��忡 immediate successor ����� ���� ����
				successor = successor->rightChild;	// immediate successor�� ã������ ��� rightChild�� �̵�
			}
			strcpy(nod->name, successor->name);	// immediate successor�� ã�� ��� immediate successor�� ������ ��带 ��ü�ؾ� �ϹǷ� ������ ����� ������ immediate successor�� ������ ������
			nod->sno = successor->sno;
			*record = *record + 1;	// ���� �� �߻��ϴ� ����� �̵� Ƚ���� 1�� �߰���(Da���� �� �̵�Ƚ���� ���ϱ� ���� ����)
			printf("���������� �����Ǿ����ϴ�. %s�� ��ġ������ �Ͼ.\n", successor->name);	// ��ġ ���� �޼����� ���
			nod->leftChild = De(nod->leftChild, successor->name, record);	// immediate successor�� ��ġ�� �ٲ� ���̹Ƿ� ���� ���� �ٲ� ���̹Ƿ� �����ִ� immediate successor�� �ش��ϴ� ��带 �����ϱ� ���� leftChild�� �̵�(immediate successor�� �̵��� ���� �Ǵٸ� ����� �̵��� �� ������ ���Ե�)
		}
		else if (nod->leftChild == NULL && nod->rightChild != NULL) {	// ���� �ڽ� ��尡 ���� ������ �ڽ� ��常 �ִ� ���
			successor = nod->rightChild;	// ���� ����� rightChild���� �ѹ� �̵��Ͽ� immediate successor��忡 ���� ����(immediate successor�� ���ϱ� ����)
			parent = nod;	// �θ� ��忡 ���� ����� ������ ����		
			while (successor->leftChild != NULL) {	// nod�� rightChild�� ��� �� ���� ���� ��� �� leftChild�� ��� �̵��Ͽ� ���� �ִ� ��尡 immediate successor��
				parent = successor;	// �θ� ��忡 immediate successor ����� ���� ����
				successor = successor->leftChild;	// immediate successor�� ã������ ��� rightChild�� �̵�
			}
			strcpy(nod->name, successor->name);	// immediate successor�� ã�� ��� immediate successor�� ������ ��带 ��ü�ؾ� �ϹǷ� ������ ����� ������ immediate successor�� ������ ������
			nod->sno = successor->sno;
			*record = *record + 1;	// ���� �� �߻��ϴ� ����� �̵� Ƚ���� 1�� �߰���(Da���� �� �̵�Ƚ���� ���ϱ� ���� ����)
			printf("���������� �����Ǿ����ϴ�. %s�� ��ġ������ �Ͼ.\n", successor->name);	// ��ġ ���� �޼����� ���
			nod->rightChild = De(nod->rightChild, successor->name, record);	// immediate successor�� ��ġ�� �ٲ� ���̹Ƿ� ���� ���� �ٲ� ���̹Ƿ� �����ִ� immediate successor�� �ش��ϴ� ��带 �����ϱ� ���� rightChild�� �̵�(immediate successor�� �̵��� ���� �Ǵٸ� ����� �̵��� �� ������ ���Ե�)
		}
		else {	// ���� �ڽ� ��尡 ���ٸ�
			printf("���������� �����Ǿ����ϴ�.\n");
			nod = NULL;	// �ش� ��带 null�� ����� 
			free(nod);	// �ش� ����� �޸𸮸� ������
		}
	}
	return nod;	// ��带 ������(�������� ��ü ��带 ����)
}

TreePointer Da(TreePointer nod) {	// sdata.txt ȭ���� ��� ����� �����ϴ� �۾��� �����ϸ� ���� �۾����� �߻��� ������ �� �̵�Ƚ���� ���
	char name1[50];	// ���Ͽ��� ���� �̸� ����
	int sno1;		// ���Ͽ��� ���� �й�����
	int res;		// ������ �����͸� ����� �о� ������ Ȯ���ϱ� ���� ����
	int level;		// �ش� ����� ����(level)
	int record = 0;	// ���� �۾����� �߻��� ������ �� �̵�Ƚ��
	FILE* fp = fopen("sdata.txt", "r");	// sdata.txt������ ����
	while (1) {
		level = 0;	// �� while�� ���� level�� 0���� �ʱ�ȭ(0���� �ʱ�ȭ�Ͽ� �ٽ� ����)
		res = fscanf(fp, "%d %s", &sno1, name1);	// ���Ͽ��� �й��� �̸��� �о� sno1�� name1�� ���� ����
		if (res < 2) {	// ������ ������ �� �޾Ƶ����� ���߰ų� ������ ������ ������ ��� Ȥ�� �� �̻� ���� ������ ���� ��� while���� ��������
			break;
		}
		nod = De(nod, name1, &record);	// ���Ͽ��� ���� ������ ���� ��带 ������
	}
	printf("���� �������� ��ġ�� �̵��� �Ͼ Ƚ��: %d\n", record);	// ���� �������� ��ġ�� �̵��� �Ͼ �� Ƚ���� ���
	return nod;	// ��ü ��带 ����
}

void Se(TreePointer nod, char getname[50], int* level) {	// �̸��� �Է� �޾� �̸� ���� ��带 ã�Ƽ� �й� �� �̸�, �� ����� ������ ���
	int checkpoint = 0;	// ã�� ��尡 ���� ��츦 Ȯ���ϱ� ���� ����
	while (nod) {	// �ش� ��带 ã�ų� ��尡 null�� �� ������ ����ؼ� Ȯ�� 
		if (strcmp(getname, nod->name) == 0) {	// ã�� ����� ��� �ش� ����� ������ ����ϰ� while���� ��������
			printf("�̸�:%s, �й�: %d, ������ġ = %d\n", nod->name, nod->sno, *level);	
			checkpoint++;	// ��带 ã���� ��� checkpoint�� 1�� �Ǿ� Ȯ�� ����
			break;
		}
		else if (strcmp(getname, nod->name) == 1) {	// ã�� ��尡 �ش� ��庸�� ū ���(�̸� ������ ���� ���) rightChild�� �̵��Ͽ� Ž��
			*level = *level + 1;	// ����� ������ 1 �ø���
			nod = nod->rightChild;	// rightChild�� �̵��Ͽ� Ž��
		}
		else {	// ã�� ��尡 �ش� ��庸�� ���� ���(�̸� ������ ���� ���) 
			*level = *level + 1;	// ����� ������ 1 �ø���
			nod = nod->leftChild;	// leftChild�� �̵��Ͽ� Ž��
		}
	}
	if (checkpoint == 0) {	// ã�� ��尡 ��� ������ �� ���( + ���ʿ� ��尡 ���� ���)
		printf("�ش� ���� �������� �ʽ��ϴ�.\n");
	}
}

void Ht(TreePointer nod) {	// ��ü ����Ž��Ʈ���� ���̸� ���Ͽ� ���(���̸� ���ϴ� �� FindHeight�� �̿�)
	int level = -1;	// ����� ������ -1�� ���� (����(height)�� ����� �� ������ 1 ���� ��Ű�� ����ϱ� ����)
	int height = 0;	// ��ü ����Ž��Ʈ���� ����
	FindHeight(nod, &level, &height);	// ��ü ����Ž��Ʈ���� ���̸� ����
	printf("height = %d\n", height);	// ��ü ����Ž��Ʈ���� ���̸� ���
}

void FindHeight(TreePointer nod, int* level, int* height) {	// ���� Ž�� Ʈ���� ���̸� ���ϴ� �Լ�
	*level = *level + 1;	// ������ 1 ������Ŵ(���� Ž���� ������)
	if (nod != NULL) {		// nod�� null�� �ƴ϶��
		if (nod->rightChild == NULL && nod->leftChild == NULL) {	// �ڽ� ��尡 ���ٸ�
			if (*level > * height) {	// ���� ����� ������ ���ݱ��� �� ���� ū ���̺��� ũ�ٸ�
				*height = *level;		// ���� ����� ������ ����Ž��Ʈ���� ���̰� ��(�ᱹ ���� ū level�� ���Ͽ� ���� ����Ž��Ʈ���� ���̸� ���ϰ� ��)
			}
		}
		FindHeight(nod->leftChild, level, height);	// ���� ��� ���� Ž��
		FindHeight(nod->rightChild, level, height);	// ������ ��� ���� Ž��
	}
	*level = *level - 1;	// ��� Ž���� ������ �θ� ���� ���ư��� ��� ������ 1 ���ҽ�Ŵ
}

void Le(TreePointer nod) {	// �� BST �� ��� �� �ڽ��� 1 ���� ����� ��, 0 ���� ����� ���� �˾Ƴ��� ���(����� ���� ����ϴ� �� Lecount�� �̿�)
	int lecount = 0;	// �ڽ��� 0���� ����� ��
	int onechildcount = 0;	// �ڽ��� 1���� ����� ��
	Lecount(nod, &lecount, &onechildcount);	// �ڽ��� 0���� ����� ���� �ڽ��� 1���� ����� ���� �����
	printf("number of leaf nodes = %d\n", lecount);	// �ڽ��� 0���� ����� �� ���
	printf("�ڽ� ����� ���� 1���� ����� �� = %d\n", onechildcount);	// �ڽ��� 1���� ����� �� ���
}

void Lecount(TreePointer nod, int *lecount, int *onechildcount) {	// BST�� ��忡�� �ڽ��� 1 ���� ����� ���� 0���� ����� ���� ����
	if (nod != NULL) {	// ��尡 null�� �ƴ϶��
		if (nod->leftChild == NULL && nod->rightChild == NULL) {	// ����� �ڽ��� ���� ���
			*lecount = *lecount + 1;	// �ڽ��� 0���� ����� ���� 1 ����
		}
		if ((nod->leftChild != NULL && nod->rightChild == NULL) || (nod->leftChild == NULL && nod->rightChild != NULL)) {	// ����� �ڽ��� 1���� ���
			*onechildcount = *onechildcount + 1;	// �ڽ��� 1���� ����� ���� 1 ����
		}
		Lecount(nod->leftChild, lecount, onechildcount);	// ���� ��带 Ž��
		Lecount(nod->rightChild, lecount, onechildcount);	// ������ ��带 Ž��
	}
}

void Ch(TreePointer nod, char getname[50]) {	// �̸��� �Է� �޾Ƽ� �̸� ���� ����� immediate successor ã�Ƽ� �� ������ ���(������ ���ٰ� �����)
	TreePointer successor;	// immediate successor�� ������ ���� ���
	if (nod == NULL) {	// ��ü ��尡 null�̶�� ��尡 �������� �ʴ´ٰ� ���
		printf("��尡 �������� �ʽ��ϴ�.\n");
	}
	if (strcmp(nod->name, getname) == 1) {	// ����� �̸��� �Է¹��� �̸����� �ļ������(�Է� ���� value�� ����� value���� ���� ���)
		Ch(nod->leftChild, getname);	// leftChild�� �̵��Ͽ� Ž��
	}
	else if (strcmp(nod->name, getname) == -1) {	// ����� �̸��� �Է¹��� �̸����� �ռ������(�Է� ���� value�� ����� value���� ū ���)
		Ch(nod->rightChild, getname);	// rightChild�� �̵��Ͽ� Ž��
	}
	else {	// �Է¹��� �̸��� ���� ��带 ã�� ���
		if (nod->leftChild != NULL) {	// �ڽ� ��尡 �� �� �ְų� ���� �ڽ� ��常 �ִ� ���
			successor = nod->leftChild;	// ���� ����� leftChild���� �ѹ� �̵��Ͽ� immediate successor��忡 ���� ����(immediate successor�� ���ϱ� ����)
			while (successor->rightChild != NULL) {	// nod�� leftChild�� ��� �� ���� ū ��� �� rightChild�� ��� �̵��Ͽ� ���� �ִ� ��尡 immediate successor�� 
				successor = successor->rightChild;	// rightChild�� ��� �̵�
			}
			printf("Immediate successor�� ���� - �̸�:%s, �й�: %d\n", successor->name,successor->sno);	// immediate successor�� ã�����Ƿ� �ش� ������ ���
		}
		else if (nod->leftChild == NULL && nod->rightChild != NULL) {	// ���� �ڽ� ��尡 ���� ������ �ڽ� ��常 �ִ� ���
			successor = nod->rightChild;	// ���� ����� rightChild���� �ѹ� �̵��Ͽ� immediate successor��忡 ���� ����(immediate successor�� ���ϱ� ����)
			while (successor->leftChild != NULL) {	// nod�� rightChild�� ��� �� ���� ���� ��� �� leftChild�� ��� �̵��Ͽ� ���� �ִ� ��尡 immediate successor�� 
				successor = successor->leftChild;	// leftChild�� ��� �̵�
			}
			printf("Immediate successor�� ���� - �̸�:%s, �й�: %d\n", successor->name, successor->sno);	// immediate successor�� ã�����Ƿ� �ش� ������ ���
		}
		else {	// ���� �ڽ� ��尡 ���ٸ� Immediate successor�� ������ �� ����
			printf("Immediate successor�� �������� �ʽ��ϴ�.\n");
		}
	}
}

void Ex(int* endcount) {	// while���� �������� ���α׷��� �����ϰ� ����� �Լ�
	*endcount = 0;	// endcount�� 0���� ����� main�� while���� ���������� ����
	printf("���α׷��� �����մϴ�!");	// ���α׷��� �����Ѵٴ� �޼��� ���
}