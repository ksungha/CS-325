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
/*	cout << "mergesortlist" << endl;
	for(int z=0; z<right_idx; z++){
		cout << input[z].x << " " << input[z].y << endl;
	}*/
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
		float d1 = sqrt(abs(pow(input[2].x-input[1].x,2)+pow(input[2].y-input[1].y,2))), d2 = sqrt(abs(pow(input[2].x-input[0].x,2)+pow(input[2].y-input[0].y,2))), d3 = sqrt(abs(pow(input[1].x-input[0].x,2)+pow(input[1].y-input[0].y,2)));
               	float temp2 = min(d1, d2);
                temp = min(temp2,d3); //min vs p1-p2
                return temp;
        }
        else
        {
                temp = sqrt(abs(pow(input[1].x-input[0].x,2)+pow(input[1].y-input[0].y,2)));
           	return temp;
        }	
}

float closestCrossPair(struct points* input, int minf, int size){
	float dmin = minf, d;
	for(int i=0; i<size-1; i++){
		int j = i+1;
		while(input[j].y-input[i].y <= minf && j<=size){
			d = sqrt(abs(pow(input[j].x-input[i].x,2)+pow(input[j].y-input[i].y,2)));
			dmin = min(d, dmin);
			j++;
		}
	}
	return dmin;
}

float closestPair(struct points *input,int n)
{
	int i;
	if(n <= 3)
	{
		return handleBasecase(input,n);
	}
	else
	{
		float L = input[n/2].x;
		struct points *left = (struct points *) calloc(L,sizeof(struct points));
		struct points *right = (struct points *) calloc(L,sizeof(struct points));
		int j = 0;
		int z = 0;
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
		}
		float min1 = closestPair(left,L);
		float min2 = closestPair(right,L);
		float minf = min(min1,min2);
		cout << "Current min: " << minf << endl;
		float lowerBound = L - minf;
		float upperBound = L - minf;
		for(i=0; i<n; i++)
		{
			if(input[i].x <=upperBound and input[i].x >= lowerBound)
				lPointCount++;
		}
		struct points *mid = (struct points *) calloc(lPointCount,sizeof(struct points));
		for(i = 0;i<n; i++)
		{
			if(input[i].x <= upperBound and input[i].x >= lowerBound)
			{
				mid[j].x = input[i].x;
				mid[j].y = input[i].y;
				j++;
			}
		}
		mergeSortY(mid,0,j-1);
		float finalMin = closestCrossPair(mid,minf,lPointCount);
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
	float a,b;
	int i = 0;
	while(file >> a >> b)
	{
		input[i].x = a;
		input[i].y = b;
		i++;
	}

	cout << "file contents:\n";
	for(i = 0; i < lineCount; i++)
	{
		cout << input[i].x << " " << input[i].y << "\n";
	}





	/* SORT HERE  */
	mergeSortX(input,0,lineCount-1);
	cout << "file contents:\n";
	for(i = 0; i < lineCount; i++)
	{
		cout << input[i].x << " " << input[i].y << "\n";
	}
	float minf = closestPair(input,lineCount);
	cout << minf << endl;

	return 0;
}

