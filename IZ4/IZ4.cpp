//ЮФУ, ИКТИБ, МОП ЭВМ
//Программирование и основы теории алгоритмов
//Индивидуальное задание №4
//КТбо1-7 ПоповДС
//Вариант №13
//24.05.2023

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

//Структура для хранения системы подстановок НАМ
//string ishodnoe	    - часть строки, которую нужно заменить
//string podstanovka	- то, на что нужно заменить
struct podstanovki {
    string ishodnoe;
    string podstanovka;
};

//Функция инициализации системы подстановок
//Входные параметры:        struct podstanovki* ptr_podstanovki - указатель на структуру
//Выходные данные:          функция ничего не возвращает
int initsializatsia(struct podstanovki* ptr_podstanovki) {
    ifstream fin("INPUT.txt");
    int N;
    fin >> N;
    for (int i = 1; i <= N; i++) {
        fin >> ptr_podstanovki[i].ishodnoe >> ptr_podstanovki[i].podstanovka;
    }
    return N;
}


//Функция проверки коректности строки
//Входные параметры:    string STR - сама строка
//Выходные данные:      true, если строка корректна или false, если некорректна
bool proverka(string STR) {
	int chisla_1 = 0;
	bool zvezdochka = false;
	int chisla_2 = 0;
	for (int i = 0; i < STR.size(); i++) {
		if (STR[i] != '1' && STR[i] != '0' && STR[i] != '*') {
			return false;
			break;
		}
		if (zvezdochka == false && (STR[i] == '1' || STR[i] == '0')) {
			chisla_1++;
		}
		if (STR[i] == '*') {
			zvezdochka = true;
		}
		if (zvezdochka == true && (STR[i] == '1' || STR[i] == '0')) {
			chisla_2++;
		}
	}
	if (chisla_1 == 0 || chisla_2 == 0 || zvezdochka == false) {
		return false;
	}
	return true;
}

//функция выбора и реализации подстановки для текущего слова и вывода результата шага
//Входные параметры:	struct podstanovki* ptr_podstanovki - указатель на структуру системы подстановок НАМ
//						string STR - изменяемая строка
//						int N - количество подстановок НАМ
//                      bool &chek1 - маркер конца алгоритма
//Выходные данные:		Функция возвращает обработанную строку
string shag(struct podstanovki* ptr_podstanovki, string STR, int N, bool &chek1) {
    string str;
    str = STR;
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 1; i <= N; i++) {
        if (STR.find(ptr_podstanovki[i].ishodnoe) <= STR.size()) {
            STR.replace(STR.find(ptr_podstanovki[i].ishodnoe), ptr_podstanovki[i].ishodnoe.size(), ptr_podstanovki[i].podstanovka);
            cout << "(" << i << ") ";
            for (int j = 0; j < str.size(); j++) {
                if (j >= str.find(ptr_podstanovki[i].ishodnoe) && j < str.find(ptr_podstanovki[i].ishodnoe) + ptr_podstanovki[i].ishodnoe.size()) {
                    SetConsoleTextAttribute(hConsoleHandle, 4);
                    cout << str[j];
                }
                else {
                    cout << str[j];
                }
                SetConsoleTextAttribute(hConsoleHandle, 1);
            }
            cout << " -> ";
            for (int j = 0; j < STR.size(); j++) {
                if (j >= str.find(ptr_podstanovki[i].ishodnoe) && j < str.find(ptr_podstanovki[i].ishodnoe) + ptr_podstanovki[i].podstanovka.size()) {
                    cout << STR[j];
                }
                else {
                    cout << STR[j];
                }
            }
            cout << endl;
            return STR;
        }
    }
    chek1 = false;
    return STR;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	string STR;
	struct podstanovki* ptr_podstanovki;
	ptr_podstanovki = new struct podstanovki[32];
	bool chek;
    bool chek1;
    int N = initsializatsia(ptr_podstanovki);
	do {
		cout << "Введите входное слово: ";
		cin >> STR;
		chek = proverka(STR);
        if (chek == true) {
            chek1 = true;
            while (chek1) {
                STR = shag(ptr_podstanovki, STR, N, chek1);
            }
            cout << "Результат: " << STR << endl;
        }

		else {
			cout << "Ошибка! Введеная строка не соответствует условию" << endl;
		}
		STR.clear();
		cout << "Хотите продолжить работу?" << endl;
		cout << "1 - Да" << endl;
		cout<<"Любой другой символ - Нет" << endl;
		int x;
		cin >> x;
		if (x == 1) {
			chek = true;
		}
		else {
			chek = false;
		}
	} while (chek);
	cout << "Хорошего дня!";
}


