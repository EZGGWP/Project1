#include "stdio.h"
#include <string>
#include <iostream>
#include <fstream>
#include <locale>
#include <list>

using namespace std;


void main() {
	setlocale(LC_ALL, "Russian");
	ifstream fileStream;
	fileStream.open("text.txt");
	string wholeText;
	if (fileStream.is_open()) {
		cout << "Файл открыт." << endl;
		while (!fileStream.eof()) {
			string line;
			getline(fileStream, line);
			line.append(" ");
			wholeText.append(line);
		};
		cout << wholeText << endl;
		list<size_t> positionsList;
		size_t position = NULL;
		if (wholeText.find(".") != string::npos) {
			position = wholeText.find(".");
			positionsList.push_back(position);
			cout << "First find is: " << position << endl;
		}
		while (position != string::npos) {
			position = wholeText.find(".", positionsList.back());
			cout << position << endl;
		};
		
		//wholeText.sub
	}
	else {
		cout << "Файл не открыт";
	}
};
