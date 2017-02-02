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

void mergeX(struct points *input, int left_idx, int med_idx, int right_idx)
{
        int ele_num_l = med_idx - left_idx + 1;
        int ele_num_r = right_idx - med_idx;
        int temp_l[ele_num_l];
        int temp_r[ele_num_r];

        for(int i = 0; i < ele_num_l; i++)
        {
                temp_l[i] = input[left_idx + i].x;
        }

        for(int j = 0; j < ele_num_r; j++)
        {
                temp_r[j] = input[med_idx+ 1 + j].x;
        }
        int i = 0;
        int j = 0;
        int k = left_idx;
        while(i < ele_num_l && j < ele_num_r)
        {
                if(temp_l[i] <= temp_r[j])
                {
                        input[k].x = temp_l[i];
                        i++;
                }
                else
                {
                        input[k].x = temp_r[j];
                        j++;
                }
                k++;
        }
        while(i < ele_num_l)
        {
                input[k].x = temp_l[i];
                i++;
                k++;
        }
        while(j < ele_num_r)
        {
                input[k].x = temp_r[j];
		j++;
                k++;
        }
}

void mergeY(struct points *input, int left_idx, int med_idx, int right_idx)
{
        int ele_num_l = med_idx - left_idx + 1;
        int ele_num_r = right_idx - med_idx;
        int temp_l[ele_num_l];
        int temp_r[ele_num_r];

        for(int i = 0; i < ele_num_l; i++)
        {
                temp_l[i] = input[left_idx + i].y;
        }

        for(int j = 0; j < ele_num_r; j++)
        {
                temp_r[j] = input[med_idx+ 1 + j].y;
        }
        int i = 0;
        int j = 0;
        int k = left_idx;
	while(i < ele_num_l && j < ele_num_r)
        {
                if(temp_l[i] <= temp_r[j])
                {
                        input[k].y = temp_l[i];
                        i++;
                }
                else
                {
                        input[k].y = temp_r[j];
                        j++;
                }
                k++;
        }
        while(i < ele_num_l)
        {
                input[k].y = temp_l[i];
                i++;
                k++;
        }
        while(j < ele_num_r)
        {
                input[k].y = temp_r[j];
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
		mergeSortY(mid,0,n);
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
	mergeSortX(input,0,lineCount);
	string min = closestPair(input,lineCount);


	return 0;
}

