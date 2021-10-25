#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void merge_sort(vector<int>& unsortedVector, int start_idx, int end_idx)
{
    if (end_idx == start_idx)
    {
        return;
    }

    int mid_idx = (start_idx + end_idx) / 2;

    int left_end_idx = mid_idx;
    int right_end_idx = end_idx;

    merge_sort(unsortedVector, start_idx, mid_idx);
    merge_sort(unsortedVector, mid_idx + 1, end_idx);

    int left_idx = start_idx;
    int right_idx = mid_idx + 1;

    vector<int> sorted;
    sorted.reserve(end_idx + start_idx + 1);

    while (true)
    {
        // 1. left_idx <= left_end_idx && right_idx <= right_end_idx
        if (left_idx <= left_end_idx && right_idx <= right_end_idx)
        {
            if (unsortedVector[left_idx] > unsortedVector[right_idx])
            {
                sorted.push_back(unsortedVector[right_idx]);
                ++right_idx;
                
            }
            else
            {
                sorted.push_back(unsortedVector[left_idx]);
                ++left_idx;
            }
        }
        // 2. left_idx <= left_end_idx && right_idx> right_end_idx
        else if (left_idx <= left_end_idx && right_idx > right_end_idx)
        {
            sorted.push_back(unsortedVector[left_idx]);
            ++left_idx;
        }
        // 3. left_idx > left_end_idx && right_idx <= right_end_idx
        else if (left_idx > left_end_idx && right_idx <= right_end_idx)
        {
            sorted.push_back(unsortedVector[right_idx]);
            ++right_idx;
        }
        // 4. left_idx > left_end_idx && right_idx > right_end_idx
        else
        {
            break;
        }
    }
    for(int i = start_idx,j = 0; i <= end_idx;++i,++j)
    {
        unsortedVector[i] = sorted[j];
    }    
}

bool isVectorSortedByAscendingOrder(vector<int>& v)
{
    int prevValue = 0;
    for(int i = 0 ; i < v.size();++i)
    {
        if(i == 0)
        {
            prevValue = v[i];
        }
        else
        {
            if(v[i] < prevValue)
            {
                return false;
            }
            prevValue = v[i];
        }
    }
    
    return true;
}

int main(void)
{
    srand((unsigned int)time(nullptr));
    for (int i = 0; i < 1000; ++i)
    {
        vector<int> testBuff;
        for (int j = 0; j < 1000; ++j)
        {
            testBuff.push_back(rand() % 101);
        }
        
        #if 0
        cout<<"test("<<setw(2)<<setfill('0')<<i<<")"<<endl;
        cout<<"before sort : ";
        for(int& v : testBuff)
        {
            cout<<v<<" ";
        }
        cout<<endl;
        #endif

        merge_sort(testBuff,0,testBuff.size()-1);
        #if 0
        cout<<"after sort : ";
        for(int& v : testBuff)
        {
            cout<<v<<" ";
        }
        cout<<endl;     
        #endif

        cout<<"Ascending order sorted ? "<< (isVectorSortedByAscendingOrder(testBuff) ? "true" : "false") <<endl;
    }

    return 0;
}