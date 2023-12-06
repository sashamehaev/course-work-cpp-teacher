#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#define FNAME_I "./bd15.dat"	//��� ����� � �������� �����
#define FNAME_R "./bd25.dat"	//��� ����� � ������������ ������
int proverka_file(const char*, const char*);	//�������� ������� �����
void dobavka(const char* fname);
void zag1();
void zag2();
void prosmotrbd1(const char* fname);
void prosmotrbd2(const char* fname);
void poiskcountry(const char* fname1, const char* fname2);
void sort_name(const char* fname);
void sort_voz_cena(const char* fname);
const char PR_R[] = "rb";	//������� �������� ��������� ����� �� ������
const char PR_S[] = "r+b";	//������� �������� ����� �� ������ � ������
const char PR_W[] = "wb";	//������� �������� ����� �� ������
const char PR_A[] = "ab";	//������� �������� ����� �� ����������
typedef struct {
	char name[15];	//������������ ����
	char country[15];	//������ ����������
	int cena;			//��������� ������� (���. ���.)
	int time;			//����������������� ���� (���)
	char trans[10];		//���������
}trip;


int main() {
	int var;
	char otv;
	char fname_i[40] = FNAME_I;
	char fname_r[40] = FNAME_R;
	setlocale(LC_ALL, "Russian");
	
	for (; ;) {
		printf("\n    ��� ��������:\n");
		printf("  1 - �������� ���� ������\n");
		printf("  2 - ���������� ����� �������\n");
		printf("  3 - ���������� �� ������������ ����\n");
		printf("  4 - ���������� ����� �� ���� �������\n");
		printf("  5 - ����� ����� �� �������� ������ ����������\n");
		printf("  6 - �������� ���� ������\n");
		printf("  7 - �������� ���� ������ ������ �����\n");
		printf("  8 - ���������� ������\n");
		printf("  ������� ��� �������� ->");
		scanf("%i", &var);
		switch (var) {
		default: break;
		case 1: 
			if (proverka_file(fname_i, PR_R)) {
				printf(" ���� ���� ������ ���������� � ������ ", fname_i);
				printf(" ��� ������ ������.\n");
				printf(" ������ ���� � ����� ������? [Y/N] ");
				while ((otv = getchar()) == '\n');
				if (otv == 'Y' || otv == 'y' || otv == '�' || otv == '�') {
					printf(" ������� ��� ������������ �����: ");
					scanf("%s", fname_i);
				} else break;
			}

			if (!proverka_file(fname_i, PR_W)) {
				printf("\n ������ �������� ����� ��� ������\n");
				break;
			}

			printf(" ������� ���� ", fname_i, '\n');
			getchar();
			dobavka(fname_i);
			printf("\n �������� ����� ���������.\n");
			if (proverka_file(fname_i, PR_R)) {
				printf(" ���� ������ ������ � ������\n");
			}
			else {
				printf("\n ���� �� �������\n");
			}

			break;
		case 2: 
			if (proverka_file(fname_i, PR_R)) {
				printf(" ���� ���� ������ ���������� � ������ ", fname_i);
				printf(" ��� ������ ������.\n");
				printf(" ����� ��������� ����� ������ � ����? [Y/N] ");
				while ((otv = getchar()) == '\n');
				if (otv == 'N' || otv == 'n' || otv == '�' || otv == '�') {
					printf(" ������� ��� ����� ������ ����: ");
					scanf("%s", fname_i);
					if (!proverka_file(fname_i, PR_R)) {
						printf(" ����� ���� ������ �� �����������\n");
						break;
					}
				}
			}
			printf(" ��������� ������ � ���� ", fname_i, '\n');
			dobavka(fname_i);
			printf("\n ��������� ����� ���������.");
			break;
		case 3: 
			if (!proverka_file(fname_i, PR_S)) {
				printf("\n ������ �������� ����� ��� ������ � ������\n");
				break;
			}
			sort_name(fname_i);
			printf("\n ���������� �� �������� ���� ���������.");
			break;
		case 4: 
			if (!proverka_file(fname_i, PR_S)) {
				printf("\n ������ �������� ����� ��� ������ � ������\n");
				break;
			}
			sort_voz_cena(fname_i);
			printf("\n ���������� �� ���� ������� ���������.");
			break;
		case 5: 
			if (!proverka_file(fname_i, PR_R)) {
				printf("\n ������ �������� ����� ��� ������\n");
				break;
			}
			if (!proverka_file(fname_r, PR_W)) {
				printf("\n ������ �������� ����� ��� ������\n");
				break;
			}
			poiskcountry(fname_i, fname_r);
			printf("\n ����� �� �������� ������ ���������� ��������.");
			break;
		case 6: 
			if (!proverka_file(fname_i, PR_R)) {
				printf("\n ������ �������� ����� ��� ������\n");
				break;
			}
			prosmotrbd1(fname_i);
			break;
		case 7: 
			if (!proverka_file(fname_r, PR_R)) {
				printf("\n ������ �������� ����� ��� ������\n");
				break;
			}
			prosmotrbd2(fname_r);
			break;
		case 8: return 0;
		}
	}
}

//���������� ����� ��������� � ���� ������
void dobavka(const char* fname) {
	char otv;
	trip tur;
	FILE* baza;
	baza = fopen(fname, PR_A);
	rewind(baza);
	do {
		printf("\n ������������ ����? ");
		scanf("%s", &tur.name);

		printf(" ������ ����������? ");
		scanf("%s", &tur.country);

		printf(" ��������� �������? (���. ���) ");
		scanf("%i", &tur.cena);

		printf(" �����������������? (����) ");
		scanf("%i", &tur.time);

		printf(" ���������? ");
		scanf("%s", &tur.trans);

		fwrite(&tur, sizeof(tur), 1, baza);

		printf("\n ����������?[Y/N]");
		while ((otv = getchar()) == '\n');
	} while (otv == 'Y' || otv == 'y' || otv == '�' || otv == '�');
	fclose(baza);
	return;
}

//����� ��������� ��� ��������� ��������� �����
void zag1() {
	int i;

	printf("\n");
	for (i = 1; i <= 66; i++)
		printf("-");
	printf("\n");
	printf("|%15s|%15s|%10s|%10s|%10s|\n", "������������ ", "������    ",
		"���������", "���������.", "���������");
	for (i = 1; i <= 66; i++)
		printf("-");
	return;
}

//����� ��������� ��� ��������� ����� ������ ����
void zag2() {
	int i;

	printf("\n");
	for (i = 1; i <= 66; i++)
		printf("-");
	printf("\n");
	printf("|%15s|%15s|%10s|%10s|%10s|\n", "������    ", "������������ ",
		"���������", "���������.", "���������");
	for (i = 1; i <= 66; i++)
		printf("-");
	return;
}

//�������� ���� ������ ����������
void prosmotrbd1(const char* fname) {
	int i;
	trip tur;
	FILE* baza;
	baza = fopen(fname, PR_R);
	printf("\n     ���� ������ ����������");
	zag1();
	while (fread(&tur, sizeof(tur), 1, baza) > 0) {
		printf("\n|%15s|%15s|%10i|%10i|%10s|", tur.name, tur.country,
			tur.cena, tur.time, tur.trans);
	}
	printf("\n");
	for (i = 1; i <= 66; i++)
		printf("-");
	fclose(baza);
	return;
}

//�������� ���� ������ ������ ���������� �� ������ ����������
void prosmotrbd2(const char* fname) {
	int i;
	trip tur;
	FILE* baza;
	baza = fopen(fname, PR_R);	//��������� ���� �� ������
	printf("\n  ���� ������ ������ ���������� �� ������ ����������");
	zag2();
	while (fread(&tur, sizeof(tur), 1, baza) > 0) {
		printf("\n|%15s|%15s|%10i|%10i|%10s|", tur.country, tur.name,
			tur.cena, tur.time, tur.trans);
	}
	printf("\n");
	for (i = 1; i <= 66; i++)
		printf("-");
	fclose(baza);
	return;
}

//����� ����� �� �������� ������ ����������
void poiskcountry(const char* fname1, const char* fname2) {
	char country[15];
	trip tur;
	FILE* in, * out;				//���� ����������� ������
	in = fopen(fname1, PR_R);		//��������� ���� �� ������
	out = fopen(fname2, PR_W);		//��������� ���� �� ������
	printf("\n �������� ������ ���������� ��� ������? ");
	scanf("%s", &country);
	while (fread(&tur, sizeof(tur), 1, in) > 0) {
		if (strncmp(tur.country, country, 15) == 0) {
			fwrite(&tur, sizeof(tur), 1, out);
		}
	}
	fclose(out);
	fclose(in);
	return;
}

//���������� �� ������������ ���������� �� ��������
void sort_name(const char* fname) {
	int i;
	int fl;
	trip ppp, tur;
	FILE* baza;
	baza = fopen(fname, PR_S);	//��������� ���� �� ������ � ������
	do {
		rewind(baza);
		fl = 0;
		for (i = 0; fread(&tur, sizeof(tur), 1, baza) > 0; i += sizeof(tur), fseek(baza, i, SEEK_SET)) {
			if (fread(&ppp, sizeof(tur), 1, baza) > 0) {
				if (strncmp(tur.name, ppp.name, 15) > 0) {
					fseek(baza, i, SEEK_SET);	//������� i �� ������ �����
					fwrite(&ppp, sizeof(tur), 1, baza);
					fwrite(&tur, sizeof(tur), 1, baza);
					fl = 1;
				}
			}
		}
	} while (fl);
	fclose(baza);
	return;
}

//���������� �� �������� ��������� �������
void sort_voz_cena(const char* fname) {
	int i;
	int fl;
	trip ppp, tur;
	FILE* baza;
	baza = fopen(fname, PR_S);	//��������� ���� �� ������ � ������
	do {
		rewind(baza);
		fl = 0;
		for (i = 0; fread(&tur, sizeof(tur), 1, baza) > 0; i += sizeof(tur), fseek(baza, i, SEEK_SET)) {
			if (fread(&ppp, sizeof(tur), 1, baza) > 0) {
				if (tur.cena > ppp.cena) {
					fseek(baza, i, SEEK_SET);	//������� i �� ������ �����
					fwrite(&ppp, sizeof(tur), 1, baza);
					fwrite(&tur, sizeof(tur), 1, baza);
					fl = 1;
				}
			}
		}
	} while (fl);
	fclose(baza);
	return;
}

//�������� ������� ����������� �����
int proverka_file(const char* fname, const char* pr) {
	if (!(fopen(fname, pr)))		//���� �� ����������
		return(0);
	return(1);
}