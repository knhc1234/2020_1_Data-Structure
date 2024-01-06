#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void Hanoi(int n, int source, int desti, int mid, int st[][100], int cnt[],FILE *FP);	// hanoi함수
void move_disk(int source, int desti, int st[][100], FILE *FP);							// pole에 있는 디스크를 움직이고 그 정보를 파일에 입력하는 함수
void show_pole(int st[][100], int cnt[], FILE *FP);										// pole에 있는 디스크의 현 상황을 파일에 입력하고 cnt에 변화된 정보를 저장하는 함수

int main(void) {
	int n;			// 원반의 갯수
	int source = 1;	// 첫번째 폴
	int mid = 2;	// 두번째 폴
	int desti = 3;	// 세번째 폴

	FILE* fp = fopen("hanoi_result.txt","w");	

	do {
		printf("원반의 총수를 입력하시오(0 < n <= 100): ");
		scanf("%d", &n);
	} while (n <= 0 && n > 100);

	int ST[3][100] = { 0 };	
	int CNT[3] = { n,0,0 };		// 현 상황 pole 1에 n개 , pole 2에 0개 pole 3에 0개

	for (int i = 0; i < n; i++) {
		if (n - i > 0)
			ST[0][i] = n - i;	// 작은 디스크가 제일 위로(배열에서 뒷순위로) 가도록 배치
	}

	Hanoi(n, source, desti, mid, ST, CNT, fp);	
	fclose(fp);

	return 0;
}

void Hanoi(int n, int source, int desti, int mid, int st[][100], int cnt[],FILE *FP) {
	if (n == 1) {
		move_disk(source, desti, st, FP);	// pole에 있는 디스크를 움직이고 그 정보를 FP에 저장
		show_pole(st, cnt, FP);				// pole에 있는 디스크의 현 상황을 FP에 저장하고 움직인 디스크에 따라 변하는 cnt정보 수정
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
		if (st[source - 1][i] != 0) {	// 가장 작은 디스크를 확인
			fprintf(FP, "Disk %d is moved from pole %d to pole %d.", st[source - 1][i], source, desti);	// 디스크의 이동경로를 파일에 입력
			for (j = 0; j < 100; j++) {
				if (st[desti - 1][j] == 0) {	// 옮긴 pole의 가장 위에 디스크를 배치
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
		fprintf(FP, "P%d=", j + 1);				// 파일에 각각의 Pole에 어떤 디스크들이 있는지 현 상황을 입력
		for (i = 99; i >= 0; i--) {
			if (st[j][i] != 0) {				// 해당 폴에 디스크가 하나라도 있다면
				fprintf(FP, "%d,", st[j][i]);	// 해당 디스크를 입력
				total++;
			}
		}

		if (total == 0) {						// 해당 폴에 디스크가 없다면 .출력
			fprintf(FP, ".");
		}
		cnt[j] = total;							// 이 과정에서 각 Pole에 몇개의 디스크가 있는지 cnt에 정보 저장
	}
	fprintf(FP, "\n");
}