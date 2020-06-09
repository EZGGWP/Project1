#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "rus");
	FILE *in, *out;
	fopen_s(&in, "text.txt", "r");
	fopen_s(&out, "out.txt", "w");

	if (!in || !out) {
		printf("File not open\n");
		return 0;
	}

	long maxlen = 40, curlen = 0;		// какие-то длины
	const long dlen = 20;
	char* buf, c, ph = 0;			// buf - слово, c - символ

	buf = (char*)malloc(maxlen);

	while (1) {
		while (!feof(in) && isspace(c = fgetc(in))) {     //Если указатель не в конце файла символ под указателем - пробел, то
			fputc(c, out);								// Выводим символ в файл вывода (выводим побелы, не обрабатывая)
		}

		if (feof(in)) {   // Если исходный файл кончился, то 
			break;	//Ломаем цикл
		}

		while (1) {	//	цикл считывания фразы

			if (c == '.' || feof(in)) {	//	конец фразы или конец файла
				buf[curlen++] = c;	
				buf[curlen] = 0;
				break;	//	прерываем цикл считывания фразы
			}

			if (curlen == maxlen) {			// Если длина достигла максимума
				maxlen += dlen;				// То прибавляем к максимуму 20
				buf = (char*)realloc(buf, maxlen);	// И перевыделяем массив
			}

			buf[curlen++] = c;
			//printf("%c", c);
			c = fgetc(in);
		}

		if (tolower(buf[0]) != tolower(buf[curlen - 1])) {		// саравниваем первый и последний символы
			fprintf(out, "%s ", buf);
		}

		for (int i = 0; i < maxlen; i++) {
			if (buf[i] == 'a' || buf[i] == 'A') {
				for (int i = 0; i < maxlen; i++) {
					printf("%c", buf[i]);
				}
				printf("\n_______\n");
			}
		}

		curlen = 0;
	}

	free(buf);
	fclose(in);
	fclose(out);
	return 0;
}