#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ofstream MyFile("./files/iteration.txt");
	int number = 1;
	MyFile <<number;
	MyFile.close();
}
