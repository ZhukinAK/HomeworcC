#include <iostream> 
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
double coordx(string str) {
	int determinator = str.find(" ");
	string X = str.substr(0, determinator);
	double x = stoi(X);
	return x;
}
double coordy(string str) {
	int determinator = str.find(" ");
	string Y = str.substr(determinator + 1, str.length());
	double y = stoi(Y);
	return y;
	return 0;
}
int main()
{
	ifstream i_file;
	i_file.open("in.txt");
	int a = 0;
	double x0;
	double y0;
	double x;
	double y;
	double mleftx;
	double mlefty;
	double mrightx;
	double mrighty;
	double dl = 0;
	double dr = 0;
	double dlina;
	string str;
	while (getline(i_file, str))
	{
		if (a == 0)
		{
			x0 = coordx(str);
			y0 = coordy(str);
			a = 1;
		}
		else
		{
			x = coordx(str);
			y = coordy(str);
			dlina = abs((x0 * y - y0 * x) / sqrt(y0 * y0 + x0 * x0));
			if (x0 * y - y0 * x > 0)
			{
				if (dl < dlina)
				{
					dl = dlina;
					mleftx = x;
					mlefty = y;
				}
			}
			else
			{
				if (dr < dlina)
				{
					dr = dlina;
					mrightx = x;
					mrighty = y;
				}
			}
		}
	}
	cout << "Leftmost: " << mleftx << " " << mlefty << endl;
	cout << "Rightmost: " << mrightx << " " << mrighty << endl;
	return 0;
}
