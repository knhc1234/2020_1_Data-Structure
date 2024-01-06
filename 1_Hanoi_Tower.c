#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void Hanoi(int n, int source, int desti, int mid, int st[][100], int cnt[],FILE *FP);	// hanoi�Լ�
void move_disk(int source, int desti, int st[][100], FILE *FP);							// pole�� �ִ� ��ũ�� �����̰� �� ������ ���Ͽ� �Է��ϴ� �Լ�
void show_pole(int st[][100], int cnt[], FILE *FP);										// pole�� �ִ� ��ũ�� �� ��Ȳ�� ���Ͽ� �Է��ϰ� cnt�� ��ȭ�� ������ �����ϴ� �Լ�

int main(void) {
	int n;			// ������ ����
	int source = 1;	// ù��° ��
	int mid = 2;	// �ι�° ��
	int desti = 3;	// ����° ��

	FILE* fp = fopen("hanoi_result.txt","w");	

	do {
		printf("������ �Ѽ��� �Է��Ͻÿ�(0 < n <= 100): ");
		scanf("%d", &n);
	} while (n <= 0 && n > 100);

	int ST[3][100] = { 0 };	
	int CNT[3] = { n,0,0 };		// �� ��Ȳ pole 1�� n�� , pole 2�� 0�� pole 3�� 0��

	for (int i = 0; i < n; i++) {
		if (n - i > 0)
			ST[0][i] = n - i;	// ���� ��ũ�� ���� ����(�迭���� �޼�����) ������ ��ġ
	}

	Hanoi(n, source, desti, mid, ST, CNT, fp);	
	fclose(fp);

	return 0;
}

void Hanoi(int n, int source, int desti, int mid, int st[][100], int cnt[],FILE *FP) {
	if (n == 1) {
		move_disk(source, desti, st, FP);	// pole�� �ִ� ��ũ�� �����̰� �� ������ FP�� ����
		show_pole(st, cnt, FP);				// pole�� �ִ� ��ũ�� �� ��Ȳ�� FP�� �����ϰ� ������ ��ũ�� ���� ���ϴ� cnt���� ����
	}
	else {
		Hanoi(n - 1, source, mid, desti, st, cnt, FP);
		move_disk(source, desti, st, FP);
		show_pole(st, cnt, FP);
		Hanoi(n - 1, mid, desti, source, st, cnt, FP);
	}
}

void move_disk(int source, int desti, int st[][100], FILE *FP) {
	int i, j;
	for (i = 99; i >= 0; i--) {
		if (st[source - 1][i] != 0) {	// ���� ���� ��ũ�� Ȯ��
			fprintf(FP, "Disk %d is moved from pole %d to pole %d.", st[source - 1][i], source, desti);	// ��ũ�� �̵���θ� ���Ͽ� �Է�
			for (j = 0; j < 100; j++) {
				if (st[desti - 1][j] == 0) {	// �ű� pole�� ���� ���� ��ũ�� ��ġ
					st[desti - 1][j] = st[source - 1][i];	
					break;
				}
			}
			st[source - 1][i] = 0;				
			break;
		}
	}
}

void show_pole(int st[][100], int cnt[], FILE *FP) {
	int i, j;
	for (j = 0; j < 3; j++) {
		int total = 0;
		fprintf(FP, "P%d=", j + 1);				// ���Ͽ� ������ Pole�� � ��ũ���� �ִ��� �� ��Ȳ�� �Է�
		for (i = 99; i >= 0; i--) {
			if (st[j][i] != 0) {				// �ش� ���� ��ũ�� �ϳ��� �ִٸ�
				fprintf(FP, "%d,", st[j][i]);	// �ش� ��ũ�� �Է�
				total++;
			}
		}

		if (total == 0) {						// �ش� ���� ��ũ�� ���ٸ� .���
			fprintf(FP, ".");
		}
		cnt[j] = total;							// �� �������� �� Pole�� ��� ��ũ�� �ִ��� cnt�� ���� ����
	}
	fprintf(FP, "\n");
}