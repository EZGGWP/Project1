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

	long maxlen = 40, curlen = 0;		// �����-�� �����
	const long dlen = 20;
	char* buf, c, ph = 0;			// buf - �����, c - ������

	buf = (char*)malloc(maxlen);

	while (1) {
		while (!feof(in) && isspace(c = fgetc(in))) {     //���� ��������� �� � ����� ����� ������ ��� ���������� - ������, ��
			fputc(c, out);								// ������� ������ � ���� ������ (������� ������, �� �����������)
		}

		if (feof(in)) {   // ���� �������� ���� ��������, �� 
			break;	//������ ����
		}

		while (1) {	//	���� ���������� �����

			if (c == '.' || feof(in)) {	//	����� ����� ��� ����� �����
				buf[curlen++] = c;	
				buf[curlen] = 0;
				break;	//	��������� ���� ���������� �����
			}

			if (curlen == maxlen) {			// ���� ����� �������� ���������
				maxlen += dlen;				// �� ���������� � ��������� 20
				buf = (char*)realloc(buf, maxlen);	// � ������������ ������
			}

			buf[curlen++] = c;
			//printf("%c", c);
			c = fgetc(in);
		}

		if (tolower(buf[0]) != tolower(buf[curlen - 1])) {		// ����������� ������ � ��������� �������
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