#include "Skip_List.h"
#include <iostream>
using namespace std;


int main() {
	setlocale(2, "rus");
	
	int level = 3;
	cout << "Введите количество уровней списка с пропусками" << endl;
	cin >> level;
	SkipList l(level);

	size_t item;
	cout << "Введите новые элементы" << endl;
	cin >> item;
	while (item) {
		l.insert(item);
		cin >> item;
	}
	l.print_list();
}
