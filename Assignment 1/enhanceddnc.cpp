#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

struct points {
	int x;
	int y;	
};

int main (int argc, const char * argv[])
{
	int lineCount = 0;
	ifstream myFile(argv[1]);
	string line;
	while(getline(myFile,line))
	{
		lineCount++;
	}
	ifstream file(argv[1]);
	struct points *input = (struct points *) calloc(lineCount,sizeof(struct points));
	int a,b;
	int i = 0;
	while(file >> a >> b)
	{
		input[i].x = a;
		input[i].y = b;
		i++;
	}
/*
	cout << "file contents:\n";
	for(i = 0; i < lineCount; i++)
	{
		cout << input[i].x << " " << input[i].y << "\n";
	}
*/




	/* SORT HERE  */




	return 0;
}
