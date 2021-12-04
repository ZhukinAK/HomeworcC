#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>
#include <typeinfo>
using namespace std;

double take_x(string str) {
	int probel = str.find(" ");
	double x = stod(str.substr(0, probel));
	return x;
}

double take_y(string str) {
	int probel = str.find(" ");
	double y = stod(str.substr(probel + 1, str.length()));
	return y;
}

int which_sector(double x,vector<double> X) {
	int sector=0;
	if (x < X.front()) {
		sector = 0;
	}
	 else{
		for (int i = 0; i < X.size(); ++i) {
			if (x >= X[i]) sector = i+1;
		}
	}
	return sector;
}

void phys1(vector<double> X, vector<double> H, double t, double dt, double& y, double& x, double& vy, double& vx, double sector) {
	double g = 9.81;
	double y1;
	
	vy = vy - g * dt;
	x = x + vx * dt;
	y1 = y;
	y = y + vy * dt - g * dt * dt / 2;
	if (sector < X.size()) {
		if (x >= X[sector] && y1 <= H[sector]) {
			vx = -vx;
			x = X[sector] - 0.0000000001;
		}
	/*	cout << "R" << x << "   " << y << "  " << sector << endl;*/
	}
}

void phys2(vector<double> X, vector<double> H, double t, double dt, double& y, double& x, double& vy, double& vx, double sector) {
	double g = 9.81;
	double y1;

	vy = vy - g * dt;
	x = x + vx * dt;
	y1 = y;
	y = y + vy * dt - g * dt * dt / 2;
	if (sector >0) {
		if (x <= X[sector - 1] && y1 <= H[sector - 1]) { 
			vx = -vx;
			x = X[sector - 1] + 0.00000000001;
		}
	/*cout << "L" << x << "   " << y << "  " << sector << endl;*/
	}
}


int main(int argc, char** argv)
{
      if(argc < 2 || argc > 2){
        cout << "аргументов нет или их больше чем мы ожидаем"<< endl;
    }
    ifstream i_file;
    i_file.open(argv[1]);
      
	int a = 0;
	//параметры точки
	double y;
	double x;
	double vx;
	double vy;
	//сектор нахождения
	int sector;
	//параметры столбов
	vector<double> X;
	vector<double> H;
	//время
	double t = 0;
	double dt = 0.001;
	string str;
	//считывание файла
	while (getline(i_file, str))
	{
		if (a == 0)
		{
			y = stod(str);
			a = 1;
		}
		else if (a==1)
		{
			vx = take_x(str);
			vy = take_y(str);
		}
		else
		{
			X.push_back(take_x(str));
			H.push_back(take_y(str));
		}
	}   
	while (y)
	{
		which_sector(x,X);
		if (vx >= 0) phys1(X,H,t,dt,y,x,vy,vx,sector);
		if (vx < 0) phys2(X, H, t, dt, y, x, vy, vx, sector);
	}
	which_sector(x, X);
	cout << sector;
	return 0;
}
