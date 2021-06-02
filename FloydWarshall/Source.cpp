#include <iostream>
#include <fstream>
#include "FloydWarshall.h"
#include "windows.h"

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FWGraph temp;
	temp.findMinWay();
	return 0;
}