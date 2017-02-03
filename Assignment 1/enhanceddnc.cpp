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
	float x;
	float y;	
};

float closestCrossPair(struct points* input, int minInput, int size){
	float temp = minInput; 
	float d;
	for(int i=0; i<size-1; i++){
		int j = i+1;
		while(input[j].y-input[i].y <= minInput && j<=size){
			d = sqrt(abs(pow(input[j].x-input[i].x,2)+pow(input[j].y-input[i].y,2)));
			temp = min(d, temp);
			j++;
		}
	}
	return temp;
}


void mergeX(struct points *input, int left_idx, int med_idx, int right_idx)
{
        int ele_num_l = med_idx - left_idx + 1;
        int ele_num_r = right_idx - med_idx;
	struct points *temp_l = (struct points *) calloc(ele_num_l,sizeof(struct points));
        struct points *temp_r = (struct points *) calloc(ele_num_r,sizeof(struct points));
        for(int i = 0; i < ele_num_l; i++)
        {
                temp_l[i].x = input[left_idx + i].x;
		temp_l[i].y = input[left_idx + i].y;
        }

        for(int j = 0; j < ele_num_r; j++)
        {
                temp_r[j].x = input[med_idx+ 1 + j].x;
		temp_r[j].y = input[med_idx+ 1 + j].y;
        }
        int i = 0;
        int j = 0;
        int k = left_idx;
        while(i < ele_num_l && j < ele_num_r)
        {
                if(temp_l[i].x <= temp_r[j].x)
                {
                        input[k].x = temp_l[i].x;
			input[k].y = temp_l[i].y;
                        i++;
                }
                else
                {
                        input[k].x = temp_r[j].x;
                        input[k].y = temp_r[j].y;
                        j++;
                }
                k++;
        }
        while(i < ele_num_l)
        {
                input[k].x = temp_l[i].x;
		input[k].y = temp_l[i].y;
                i++;
                k++;
        }
        while(j < ele_num_r)
        {
                input[k].x = temp_r[j].x;
		input[k].y = temp_r[j].y;
		j++;
                k++;
        }
}

void mergeY(struct points *input, int left_idx, int med_idx, int right_idx)
{
        int ele_num_l = med_idx - left_idx + 1;
        int ele_num_r = right_idx - med_idx;
	struct points *temp_l = (struct points *) calloc(ele_num_l,sizeof(struct points));
        struct points *temp_r = (struct points *) calloc(ele_num_r,sizeof(struct points));
        for(int i = 0; i < ele_num_l; i++)
        {
                temp_l[i].y = input[left_idx + i].y;
		temp_l[i].x = input[left_idx + i].x;
        }

        for(int j = 0; j < ele_num_r; j++)
        {
                temp_r[j].y = input[med_idx+ 1 + j].y;
		temp_r[j].x = input[med_idx+ 1 + j].x;
        }
        int i = 0;
        int j = 0;
        int k = left_idx;
	while(i < ele_num_l && j < ele_num_r)
        {
                if(temp_l[i].y <= temp_r[j].y)
                {
                        input[k].y = temp_l[i].y;
			input[k].x = temp_l[i].x;
                        i++;
                }
                else
                {
                        input[k].y = temp_r[j].y;
			input[k].x = temp_r[j].x;
                        j++;
                }
                k++;
        }
        while(i < ele_num_l)
        {
                input[k].y = temp_l[i].y;
		input[k].x = temp_l[i].x;
                i++;
                k++;
        }
        while(j < ele_num_r)
        {
                input[k].y = temp_r[j].y;
		input[k].x = temp_r[j].x;
                j++;
                k++;
        }
}


void mergeSortX(struct points *input,int left_idx, int right_idx)
{
	int i;
        if(left_idx < right_idx)
        {
                int med_idx = (left_idx + right_idx)/2;
                mergeSortX(input, left_idx, med_idx);//for the first half of the inputay
                mergeSortX(input,med_idx + 1, right_idx);//for the second
                mergeX(input, left_idx, med_idx, right_idx);//merge them together
        }
}

void mergeSortY(struct points *input,int left_idx, int right_idx)
{
        if(left_idx < right_idx)
        {
                int med_idx = (left_idx + right_idx)/2;

                mergeSortY(input, left_idx, med_idx);//for the first half of the inputay
                mergeSortY(input,med_idx + 1, right_idx);//for the second
                mergeY(input, left_idx, med_idx, right_idx);//merge them together
        }
}

float handleBasecase(struct points *input,int n)
{
	float temp;
        if(n == 3)
        {
		float d2 = sqrt(abs(pow(input[2].x-input[1].x,2)+pow(input[2].y-input[1].y,2)));
		float d3 = sqrt(abs(pow(input[2].x-input[0].x,2)+pow(input[2].y-input[0].y,2)));
               	float temp2 = min(d2, d3);
		float d1 = sqrt(abs(pow(input[1].x-input[0].x,2)+pow(input[1].y-input[0].y,2)));
                temp = min(temp2,d1); //min vs p1-p2
                return temp;
        }
        else
        {
                temp = sqrt(abs(pow(input[1].x-input[0].x,2)+pow(input[1].y-input[0].y,2)));
           	return temp;
        }	
}

float closestPair(struct points *X_x,struct points *X_y,int n)
{
	int i;
	if(n <= 3)
	{
		return handleBasecase(X_x,n);
	}
	else
	{
		float L = n/2;
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
		float min1 = closestPair(Q_x,Q_y,L);
		float min2 = closestPair(R_x,R_y,L);
		float minTotal = min(min1,min2);
		j=0;
		float lowerBound = L - minTotal;
		float upperBound = L + minTotal;
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
				M[j].x = X_y[i].x;
				M[j].y = X_y[i].y;
				j++;
			}
		}
		float finalMin = closestCrossPair(M,minTotal,lPointCount);
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
	struct points *X_x = (struct points *) calloc(lineCount,sizeof(struct points));
        struct points *X_y = (struct points *) calloc(lineCount,sizeof(struct points));
	float a,b;
	int i = 0;
	while(file >> a >> b)
	{
		X_y[i].x = a;
		X_y[i].y = b;
		X_x[i].x = a;
                X_x[i].y = b;
		i++;
	}

	cout << "file contents:\n";
	for(i = 0; i < lineCount; i++)
	{
		cout << X_x[i].x << " " << X_x[i].y << "\n";
	}


	//lineCount--;


	/* SORT HERE  */
	mergeSortX(X_x, 0 ,lineCount-1);
	mergeSortY(X_y, 0 ,lineCount-1);
	cout << "file contents:\n";
        for(i = 0; i < lineCount; i++)
        {
                cout << X_x[i].x << " " << X_x[i].y << "\n";
        }

	float min = closestPair(X_x,X_y,lineCount);
	cout << "minimum distance found: " << min << "\n";
	return 0;
}
