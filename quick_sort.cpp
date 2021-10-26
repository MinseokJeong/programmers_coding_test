
#include <vector>

using namespace std;

void quick_sort(vector<int> &unsorted_vector, int start_idx, int end_idx)
{
    if (end_idx <= start_idx)
        return;

    // choose pivot index
    int pivot_idx = (start_idx + end_idx) / 2;
    const int pivot_val = unsorted_vector[pivot_idx];

    swap(unsorted_vector[pivot_idx], unsorted_vector[end_idx]);

    int left_idx = start_idx;
    int right_idx = end_idx - 1;

    while (true)
    {
        if (left_idx > right_idx)
        {
            pivot_idx = left_idx;
            swap(unsorted_vector[pivot_idx], unsorted_vector[end_idx]);
            break;
        }

        if (unsorted_vector[left_idx] > pivot_val && unsorted_vector[right_idx] < pivot_val)
        {
            swap(unsorted_vector[left_idx], unsorted_vector[right_idx]);
            ++left_idx;
            --right_idx;
        }
        else if (unsorted_vector[left_idx] > pivot_val && unsorted_vector[right_idx] >= pivot_val)
        {
            --right_idx;
        }
        else if (unsorted_vector[left_idx] <= pivot_val && unsorted_vector[right_idx] < pivot_val)
        {
            ++left_idx;
        }
        else// if (unsorted_vector[left_idx] <= pivot_val && unsorted_vector[right_idx] >= pivot_val)
        {
            ++left_idx;            
        }
        
    }

    quick_sort(unsorted_vector, start_idx, pivot_idx - 1);
    quick_sort(unsorted_vector, pivot_idx + 1, end_idx);
}

#include <iostream>
#include "mj_timer.h"

void printVector(vector<int>& v)
{
    cout<<"Vector Element : ";
    for(auto& i : v)
    {
        cout<<i<<" ";
    }
    cout<<endl;
}

int main(void)
{
    srand((unsigned int)time(nullptr));

    int testCount = 0;
    while (testCount < 10)
    {
        vector<int> unsortedVector;
        for (int i = 0; i < 1000; ++i)
        {
            unsortedVector.push_back(rand()% 1001);
        }
        
        cout<<"-- Unsorted Vector --"<<endl;
        printVector(unsortedVector);
        startTimer();
        quick_sort(unsortedVector,0,unsortedVector.size()-1);
        endTimer();
        printTimeDiff();
        cout<<"-- Sorted Vector --"<<endl;
        printVector(unsortedVector);
        cout<<endl<<endl;
        ++testCount;
    }

    return 0;
}
