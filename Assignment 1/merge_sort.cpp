#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void merge(int arr[], int left_idx, int med_idx, int right_idx)
{
	//getting the number of elements between each array
	int ele_num_l = med_idx - left_idx + 1;
	int ele_num_r = right_idx - med_idx;
	
	//creating the left and right arrays
	int temp_l[ele_num_l];
	int temp_r[ele_num_r];
	
	//placing the data into the temp arrays
	for(int i = 0; i < ele_num_l; i++)
	{
		temp_l[i] = arr[left_idx + i];
	}

	for(int j = 0; j < ele_num_r; j++)
	{
		temp_r[j] = arr[med_idx+ 1 + j];
	}
	//resetting variables to be the initial index of the first second and merged sub_arrays
	int i = 0;
	int j = 0;
	int k = left_idx;
	//comparison are made here to determine which array the elements go into
	while(i < ele_num_l && j < ele_num_r)
	{
		if(temp_l[i] <= temp_r[j])
		{
			arr[k] = temp_l[i];
			i++;
		}
		else
		{
			arr[k] = temp_r[j];
			j++;
		}
		k++;
	}
	//Here we're making sure that the remain elements are being put in the temp left array
	while(i < ele_num_l)
	{
		arr[k] = temp_l[i];
		i++;
		k++;
	}
	//Here we're making sure that the remain elements are being put in the temp right array
	while(j < ele_num_r)
	{
		arr[k] = temp_r[j];
		j++;
		k++;
	}
}
void merge_sort(int arr[],int left_idx, int right_idx)
{
	if(left_idx < right_idx)
	{
		int med_idx = (left_idx + right_idx)/2;
		
		merge_sort(arr, left_idx, med_idx);//for the first half of the array
		merge_sort(arr,med_idx + 1, right_idx);//for the second
		
		merge(arr, left_idx, med_idx, right_idx);//merge them together
	}
}
void print_array(int arr[], int arr_size)
{
	for(int i = 0; i < arr_size;i++)
	{
		cout << arr[i] << " ";
	}
	cout << "\n";
}
int main()
{
	int count = 0;
	int test_arr[] = {12,11,13,5,6,7};
	int arr_size = sizeof(test_arr)/4; //need to divide by 4 to get number of elements
	cout << "Array size: " << arr_size << "\n";	
	print_array(test_arr, arr_size);
	
	merge_sort(test_arr,0, arr_size - 1);
	
	cout << "Sorted array: " << "\n";
	print_array(test_arr, arr_size);
	
	return 0;
}
