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

int closestPair(struct points *input,int n)
{
	int i;
	if(n <= 3)
	{
		return handleBasecase(input,n);
	}
	else
	{
		int L = n/2;
		struct points *left = (struct points *) calloc(L,sizeof(struct points));
		struct points *right = (struct points *) calloc(L,sizeof(struct points));
		int j,z = 0;
		int lPointCount = 0;
		for(i = 0; i < n; i++)
		{
			if(input[i].x < L)
			{
				left[j].x = input[n].x;
				left[j].y = input[n].y;
			}
			else if(input[i].x > L)
			{
				right[j].x = input[n].x;
                                right[j].y = input[n].y;
			}
			else
			{
				lPointCount++;
			}
		}
		int min1 = closestPair(left,L);
		int min2 = closestPair(right,L);
		int min = min(min1,min2);
		struct points *mid = (struct points *) calloc(lPointCount,sizeof(struct points));
		j=0;
		for(i = 0;i<n; i++)
		{
			if(input[i].x == L)
			{
				mid[j].x = input[i].x;
				mid[j].y = input[i].y;
				j++;
			}
		}
		mergeSortY(mid,n);
		int finalMin = closestCrossPair(mid,min);
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
	mergeSortX(input,lineCount);
	string min = closestPair(input,lineCount);


	return 0;
}

