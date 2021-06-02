#pragma once
#include "list.h"
#include <fstream>
#include <float.h>
#include <string>
using namespace std;
class FWGraph {

public:
	double** adjMatrix;
	double** fwMatrix;
	list<string> cities;
	int** minWay;

	FWGraph() {
		fstream in("F:\\Универ\\Прога 4 сем\\AlgAndDataStruct_4Sem_3\\FloydWarshall\\in.txt");
		in >> noskipws;
		inputCities(in);
		in.close();
		in.open("F:\\Универ\\Прога 4 сем\\AlgAndDataStruct_4Sem_3\\FloydWarshall\\in.txt");
		inpAdjMatrix(in);
		outAdjMatrix();
		createFWMatrix();
		in.close();
	}
	void inputCities(fstream& in) {
		string temp = "";
		char c = ' ';
		while (true) {
			c = ' ';
			if (in.eof()) break;
			temp = inputCity(in);
			if (!cities.contain(temp)) cities.push_back(temp);
			temp = inputCity(in);
			if (!cities.contain(temp)) cities.push_back(temp);
			while (c != '\n' && !in.eof()) in >> c;
		}
	}

	string inputCity(fstream& in) {
		string temp;
		char c = ' ';
		while (true) {
			in >> c;
			if (c == ';') {
				return temp;
			}
			if (c == '\n' || in.eof()) {
				break;
				//throw "Ошибка во входных данных";
			}
			temp += c;
		}
	}

	void inpAdjMatrix(fstream& in) {
		adjMatrix = new double* [cities.getSize()];
		for (int i = 0; i < cities.getSize(); i++) {
			adjMatrix[i] = new double[cities.getSize()];
			for (int j = 0; j < cities.getSize(); j++) 
				if (i == j) adjMatrix[i][j] = 0;
				else adjMatrix[i][j] = DBL_MAX;
		}
		int i = 0;
		char c = ' ';
		string from = "", to = "";
		string temp = "";
		while (!in.eof()) {
			temp = "";
			from = inputCity(in);
			to = inputCity(in);
			in >> c;
			while (c != ';') {
				temp += c;
				in >> c;
			}
			int fromindex = cities.indexOf(from);
			int toindex = cities.indexOf(to);
			if (temp != "N/A")
				if (toindex != fromindex && stod(temp) > 0) adjMatrix[fromindex][toindex] = stod(temp);
				else throw "Ошибка во входных данных";
			temp = "";
			in >> c;
			while (c != '\n' && !in.eof()) {
				temp += c;
				in >> c;
			}
			if (temp != "N/A")
				if (toindex != fromindex && stod(temp) > 0) adjMatrix[toindex][fromindex] = stod(temp);
				else throw "Ошибка во входных данных";
			i++;
		}
	}

	void outAdjMatrix() {
		fstream out("out.txt", ios::out);
		for (int i = 0; i < cities.getSize(); i++) {
			out << cities.at(i) << " ";
			for (int j = 0; j < cities.getSize(); j++) 
				if(adjMatrix[i][j] != DBL_MAX) out << adjMatrix[i][j] << " ";
				else out << "N/A ";
			out << endl;
		}
	}

	void createFWMatrix() {
		fwMatrix = new double* [cities.getSize()];
		minWay = new int* [cities.getSize()];
		for (int i = 0; i < cities.getSize(); i++) {
			minWay[i] = new int[cities.getSize()]{0};
			fwMatrix[i] = new double[cities.getSize()];
			for (int j = 0; j < cities.getSize(); j++)
				fwMatrix[i][j] = adjMatrix[i][j];
		}
		for (int i = 0; i < cities.getSize(); i++) 
			for(int j = 0; j < cities.getSize(); j++)
				for(int k = 0; k < cities.getSize(); k++)
					if (fwMatrix[j][i] + fwMatrix[i][k] < fwMatrix[j][k]) {
						fwMatrix[j][k] = fwMatrix[j][i] + fwMatrix[i][k];
						minWay[j][k] = i + 1;
					}
	}

	double findMinWay() {
		string from = "", to = "";
		cout << "Откуда: ";
		cin >> from;
		cout << "Куда: ";
		cin >> to;
		return findMinWay(from, to);
	}

	double findMinWay(string from, string to) {
		int fromindex = cities.indexOf(from);
		int toindex = cities.indexOf(to);
		if (fromindex == -1 || toindex == -1 || fwMatrix[fromindex][toindex] == DBL_MAX) cout << "Из " << from << " в " << to << " нет пути";
		else {
			string trajectory = "";
			cout << cities.at(fromindex);
			createTrajectory(trajectory, fromindex, toindex);
			cout << " -> " << trajectory << cities.at(toindex);
			cout << "\nМинимальная цена пути из " << from << " в " << to << " стоит " << fwMatrix[fromindex][toindex];
			return fwMatrix[fromindex][toindex];
		}
		return -1;
	}

	void createTrajectory(string& way, int fromindex, int toindex) {
		int gap = minWay[fromindex][toindex] - 1;
		if (gap != -1) {
			createTrajectory(way, fromindex, gap);
			way += cities.at(gap) + " -> ";
			createTrajectory(way, gap, toindex);
		}
	}
};