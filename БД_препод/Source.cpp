#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#define FNAME_I "./bd15.dat"	//имя файла с исходной базой
#define FNAME_R "./bd25.dat"	//имя файла с результатами поиска
int proverka_file(const char*, const char*);	//проверка наличия файла
void dobavka(const char* fname);
void zag1();
void zag2();
void prosmotrbd1(const char* fname);
void prosmotrbd2(const char* fname);
void poiskcountry(const char* fname1, const char* fname2);
void sort_name(const char* fname);
void sort_voz_cena(const char* fname);
const char PR_R[] = "rb";	//признак открытия бинарного файла на чтение
const char PR_S[] = "r+b";	//признак открытия файла на чтение и запись
const char PR_W[] = "wb";	//признак открытия файла на запись
const char PR_A[] = "ab";	//признак открытия файла на добавление
typedef struct {
	char name[15];	//наименование тура
	char country[15];	//страна пребывания
	int cena;			//стоимость путевки (тыс. руб.)
	int time;			//продолжительность тура (дни)
	char trans[10];		//транспорт
}trip;


int main() {
	int var;
	char otv;
	char fname_i[40] = FNAME_I;
	char fname_r[40] = FNAME_R;
	setlocale(LC_ALL, "Russian");
	
	for (; ;) {
		printf("\n    Вид действия:\n");
		printf("  1 - создание базы данных\n");
		printf("  2 - добавление новых записей\n");
		printf("  3 - сортировка по наименованию тура\n");
		printf("  4 - сортировка туров по цене поездки\n");
		printf("  5 - поиск туров по названию страны пребывания\n");
		printf("  6 - просмотр базы данных\n");
		printf("  7 - просмотр базы данных поиска туров\n");
		printf("  8 - завершение задачи\n");
		printf("  Введите вид действия ->");
		scanf("%i", &var);
		switch (var) {
		default: break;
		case 1: 
			if (proverka_file(fname_i, PR_R)) {
				printf(" Файл базы данных турпоездок с именем ", fname_i);
				printf(" был создан раньше.\n");
				printf(" Создаём файл с новым именем? [Y/N] ");
				while ((otv = getchar()) == '\n');
				if (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н') {
					printf(" Задайте имя создаваемого файла: ");
					scanf("%s", fname_i);
				} else break;
			}

			if (!proverka_file(fname_i, PR_W)) {
				printf("\n Ошибка открытия файла для записи\n");
				break;
			}

			printf(" Создаем базу ", fname_i, '\n');
			getchar();
			dobavka(fname_i);
			printf("\n Создание файла закончено.\n");
			if (proverka_file(fname_i, PR_R)) {
				printf(" База данных готова к работе\n");
			}
			else {
				printf("\n база не создана\n");
			}

			break;
		case 2: 
			if (proverka_file(fname_i, PR_R)) {
				printf(" Файл базы данных турпоездок с именем ", fname_i);
				printf(" был создан раньше.\n");
				printf(" Будем добавлять новые записи в него? [Y/N] ");
				while ((otv = getchar()) == '\n');
				if (otv == 'N' || otv == 'n' || otv == 'Т' || otv == 'т') {
					printf(" Задайте имя файла другой базы: ");
					scanf("%s", fname_i);
					if (!proverka_file(fname_i, PR_R)) {
						printf(" Такая база данных не создавалась\n");
						break;
					}
				}
			}
			printf(" Добавляем записи в файл ", fname_i, '\n');
			dobavka(fname_i);
			printf("\n Изменение файла закончено.");
			break;
		case 3: 
			if (!proverka_file(fname_i, PR_S)) {
				printf("\n Ошибка открытия файла для чтения и записи\n");
				break;
			}
			sort_name(fname_i);
			printf("\n Сортировка по названию тура закончена.");
			break;
		case 4: 
			if (!proverka_file(fname_i, PR_S)) {
				printf("\n Ошибка открытия файла для чтения и записи\n");
				break;
			}
			sort_voz_cena(fname_i);
			printf("\n Сортировка по цене поездки закончена.");
			break;
		case 5: 
			if (!proverka_file(fname_i, PR_R)) {
				printf("\n Ошибка открытия файла для чтения\n");
				break;
			}
			if (!proverka_file(fname_r, PR_W)) {
				printf("\n Ошибка открытия файла для записи\n");
				break;
			}
			poiskcountry(fname_i, fname_r);
			printf("\n Поиск по названию страны пребывания закончен.");
			break;
		case 6: 
			if (!proverka_file(fname_i, PR_R)) {
				printf("\n Ошибка открытия файла для чтения\n");
				break;
			}
			prosmotrbd1(fname_i);
			break;
		case 7: 
			if (!proverka_file(fname_r, PR_R)) {
				printf("\n Ошибка открытия файла для чтения\n");
				break;
			}
			prosmotrbd2(fname_r);
			break;
		case 8: return 0;
		}
	}
}

//Добавление новых элементов в базу данных
void dobavka(const char* fname) {
	char otv;
	trip tur;
	FILE* baza;
	baza = fopen(fname, PR_A);
	rewind(baza);
	do {
		printf("\n Наименование тура? ");
		scanf("%s", &tur.name);

		printf(" Страна пребывания? ");
		scanf("%s", &tur.country);

		printf(" Стоимость путевки? (тыс. руб) ");
		scanf("%i", &tur.cena);

		printf(" Продолжительность? (дней) ");
		scanf("%i", &tur.time);

		printf(" Транспорт? ");
		scanf("%s", &tur.trans);

		fwrite(&tur, sizeof(tur), 1, baza);

		printf("\n Продолжать?[Y/N]");
		while ((otv = getchar()) == '\n');
	} while (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н');
	fclose(baza);
	return;
}

//Вывод заголовка при просмотре исходного файла
void zag1() {
	int i;

	printf("\n");
	for (i = 1; i <= 66; i++)
		printf("-");
	printf("\n");
	printf("|%15s|%15s|%10s|%10s|%10s|\n", "Наименование ", "Страна    ",
		"Стоимость", "Продолжит.", "Транспорт");
	for (i = 1; i <= 66; i++)
		printf("-");
	return;
}

//Вывод заголовка при просмотре файла поиска тура
void zag2() {
	int i;

	printf("\n");
	for (i = 1; i <= 66; i++)
		printf("-");
	printf("\n");
	printf("|%15s|%15s|%10s|%10s|%10s|\n", "Страна    ", "Наименование ",
		"Стоимость", "Продолжит.", "Транспорт");
	for (i = 1; i <= 66; i++)
		printf("-");
	return;
}

//Просмотр базы данных турпоездок
void prosmotrbd1(const char* fname) {
	int i;
	trip tur;
	FILE* baza;
	baza = fopen(fname, PR_R);
	printf("\n     База данных турпоездок");
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

//Просмотр базы данных поиска турпоездок по стране пребывания
void prosmotrbd2(const char* fname) {
	int i;
	trip tur;
	FILE* baza;
	baza = fopen(fname, PR_R);	//открываем файл на чтение
	printf("\n  База данных поиска турпоездок по стране пребывания");
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

//Поиск туров по названию страны пребывания
void poiskcountry(const char* fname1, const char* fname2) {
	char country[15];
	trip tur;
	FILE* in, * out;				//файл результатов поиска
	in = fopen(fname1, PR_R);		//открываем файл на чтение
	out = fopen(fname2, PR_W);		//открываем файл на запись
	printf("\n Название страны пребывания для поиска? ");
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

//Сортировка по наименованию турпоездки по алфавиту
void sort_name(const char* fname) {
	int i;
	int fl;
	trip ppp, tur;
	FILE* baza;
	baza = fopen(fname, PR_S);	//открываем файл на чтение и запись
	do {
		rewind(baza);
		fl = 0;
		for (i = 0; fread(&tur, sizeof(tur), 1, baza) > 0; i += sizeof(tur), fseek(baza, i, SEEK_SET)) {
			if (fread(&ppp, sizeof(tur), 1, baza) > 0) {
				if (strncmp(tur.name, ppp.name, 15) > 0) {
					fseek(baza, i, SEEK_SET);	//позиция i от НАЧАЛА файла
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

//Сортировка по убыванию стоимости путевки
void sort_voz_cena(const char* fname) {
	int i;
	int fl;
	trip ppp, tur;
	FILE* baza;
	baza = fopen(fname, PR_S);	//открываем файл на чтение и запись
	do {
		rewind(baza);
		fl = 0;
		for (i = 0; fread(&tur, sizeof(tur), 1, baza) > 0; i += sizeof(tur), fseek(baza, i, SEEK_SET)) {
			if (fread(&ppp, sizeof(tur), 1, baza) > 0) {
				if (tur.cena > ppp.cena) {
					fseek(baza, i, SEEK_SET);	//позиция i от НАЧАЛА файла
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

//проверка наличия физического файла
int proverka_file(const char* fname, const char* pr) {
	if (!(fopen(fname, pr)))		//файл не существует
		return(0);
	return(1);
}