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

int handleBasecase(struct point *input,int n)
{
	int temp;
        if(n == 3)
        {
               	int temp2 = min(sqrt(abs(pow(input[2].x-input[1].x,2)+pow(input[2].y-input[1].y,2))), sqrt(abs(pow(input[2].x-input[0].x,2)+pow(input[2].y-input[0].y,2))));
                temp = min(temp2,sqrt(abs(pow(input[1].x-input[0].x,2)+pow(input[1].y-input[0].y,2)))); //min vs p1-p2
                return temp;
        }
        else
        {
                temp = sqrt(abs(pow(input[1].x-input[0].x,2)+pow(input[1].y-input[0].y,2)));
           	return temp;
        }	
}

int closestPair(struct points *X_x,struct points *X_y,int n)
{
	int i;
	if(n <= 3)
	{
		return handleBasecase(X_x,n);
	}
	else
	{
		int L = n/2;
		struct points *Q_x = (struct points *) calloc(L,sizeof(struct points));
		struct points *R_x = (struct points *) calloc(L,sizeof(struct points));
		struct points *Q_y = (struct points *) calloc(L,sizeof(struct points));
                struct points *R_y = (struct points *) calloc(L,sizeof(struct points));
		int j = 0;
		int z = 0;
		int lPointCount = 0;
		for(i = 0; i < n; i++)
		{
			if(X_x[i].x < L)
			{
				Q_x[j].x = X_x[i].x;
				Q_x[j].y = X_x[i].y;
			}
			else if(X_x[i].x > L)
			{
				R_x[j].x = X_x[i].x;
                                R_x[j].y = X_x[i].y;
			}
		}
		for(i = 0; i < n; i++)
		{
			if(X_y[i].x < L)
			{
				Q_y[z].x = X_y[i].x;
				Q_y[z].y = X_y[i].y;
			}
			else if (X_y[i].x > L)
			{
				R_y[z].x = X_y[i].x;
                                R_y[z].y = X_y[i].y;
			}
		}
		int min1 = closestPair(Q_x,Q_y,L);
		int min2 = closestPair(R_x,R_y,L);
		int min = min(min1,min2);
		j=0;
		int lowerBound = L - min;
		int upperBound = L + min;
		for(i = 0; i < n; i++)
		{
			if(X_y[i].x <= upperBound and X_y[i].x >= lowerBound)
                        {
				lPointCount++;
			}
		}
		struct points *M = (struct points *) calloc(lPointCount,sizeof(struct points));
		for(i = 0;i<n; i++)
		{
			if(X_y[i].x <= upperBound and X_y[i].x >= lowerBound)
			{
				M[j].x = input[i].x;
				M[j].y = input[i].y;
				j++;
			}
		}
		int finalMin = closestCrossPair(M,min,lPointCount);
		return finalMin;
	}
}

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
//	struct points *input = (struct points *) calloc(lineCount,sizeof(struct points));
	struct points *X_x = (struct points *) calloc(lineCount,sizeof(struct points));
        struct points *X_y = (struct points *) calloc(lineCount,sizeof(struct points));
	int a,b;
	int i = 0;
	while(file >> a >> b)
	{
		X_y[i].x = a;
		X_y[i].y = b;
		X_x[i].x = a;
                X_x[i].y = b;
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
	mergeSortX(X_x,lineCount);
	mergeSortY(X_y,lineCount);
	string min = closestPair(X_x,X_y,lineCount);

	return 0;
}

