#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>
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
	struct points *min = (struct points *) calloc(2*lineCount, sizeof(struct points));
	int numpoints = i, numties = 0;
	float minD = 1000, curD;
	for(i=0; i<numpoints; i++){
		for(int j=i+1; j<numpoints; j++){
			//cout << input[i].x << " " << input[i].y << " " << input[j].x << " " << input[j].y << "\n";
			curD = sqrt(abs(pow(input[j].x-input[i].x,2)+pow(input[j].y-input[i].y,2)));
			//cout << curD << " " << minD << "\n";
			if(curD < minD){
				minD = curD;
				numties = 0;
				min[0].x = input[i].x;
				min[0].y = input[i].y;
				min[1].x = input[j].x;
				min[1].y = input[j].y;
			}
			else if(curD == minD){
				numties +=1;
				min[2*numties].x = input[i].x;
				min[2*numties].y = input[i].y;
				min[2*numties+1].x = input[j].x;
				min[2*numties+1].y = input[j].y;
			}
		}
	}
	cout << minD << "\n";
	for(i=0; i<=numties; i++){
		cout << min[2*i].x << " " << min[2*i].y << " " << min[2*i+1].x << " " << min[2*i+1].y << "\n";
	}

	return 0;
}
