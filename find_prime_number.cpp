#include <iostream>
#include <string>



#include <vector>
#include <chrono>

using namespace std;

/*
소수 찾기
문제 설명
한자리 숫자가 적힌 종이 조각이 흩어져있습니다. 흩어진 종이 조각을 붙여 소수를 몇 개 만들 수 있는지 알아내려 합니다.

각 종이 조각에 적힌 숫자가 적힌 문자열 numbers가 주어졌을 때, 종이 조각으로 만들 수 있는 소수가 몇 개인지 return 하도록 solution 함수를 완성해주세요.

제한사항
numbers는 길이 1 이상 7 이하인 문자열입니다.
numbers는 0~9까지 숫자만으로 이루어져 있습니다.
"013"은 0, 1, 3 숫자가 적힌 종이 조각이 흩어져있다는 의미입니다.
입출력 예
numbers	return
"17"	3
"011"	2
입출력 예 설명
예제 #1
[1, 7]으로는 소수 [7, 17, 71]를 만들 수 있습니다.

예제 #2
[0, 1, 1]으로는 소수 [11, 101]를 만들 수 있습니다.

11과 011은 같은 숫자로 취급합니다.
출처
*/
#include <stdlib.h>
#include <unordered_set>
#include <unordered_map>
int primeNumberCount = 0;
unordered_set<int> checkedValue;
unordered_map<int, bool> primeNumberLookupTable;
bool primeNumberLookUpTableInitialized = false;

bool isPrimeNumber(int val)
{
    const auto &findIt = primeNumberLookupTable.find(val);
    if (findIt != primeNumberLookupTable.end())
    {
        return findIt->second;
    }

    if (val == 0)
    {
        primeNumberLookupTable[val] = false;
        return false;
    }
    else if (val == 1)
    {
        primeNumberLookupTable[val] = false;
        return false;
    }
    else
    {
        bool retVal = true;

        for (int i = 2; i < val; ++i)
        {
            if (val % i == 0)
            {
                retVal = false;
                break;
            }
        }

        if (retVal == true)
        {
            primeNumberLookupTable[val] = true;
            for (int i = val*2; i < 10000000; i += val)
            {
                primeNumberLookupTable[i] = false;
            }
        }
        else
        {
            primeNumberLookupTable[val] = false;
        }
        return retVal;
    }
}

void checkString(string &s)
{
    int integerVal = strtol(s.c_str(), nullptr, 10);
    if (checkedValue.find(integerVal) == checkedValue.end())
    {
        if (isPrimeNumber(integerVal) == true)
        {            
            primeNumberCount++;
        }

        checkedValue.insert(integerVal);
    }
}

void fullSearch(string choosen, string choose)
{
    if (choose.length() == 0)
    {
        return;
    }

    for (size_t i = 0; i < choose.size(); ++i)
    {
        string newStr = choosen + choose[i];
        string newChoose = choose.substr(0, i) + choose.substr(i + 1, choose.size() - (i + 1));
        checkString(newStr);
        fullSearch(newStr, newChoose);
    }
}

int solution(string numbers)
{    
    unordered_set<int> emptySet;
    swap(checkedValue, emptySet);
    primeNumberCount = 0;

    fullSearch("", numbers);

    return primeNumberCount;
}

// nP1
// nP2
// nP3
//...nPn 까 N!/N!

// nPr = n!/r!
// nCr = n-1Cr + n-1Cr-1 = nPr/r!
int main(void)
{

    vector<string> testCases{
        "17",
        "011",
    };

    for (auto &testCase : testCases)
    {
        const auto startTime = chrono::system_clock::now().time_since_epoch();
        const int result = solution(testCase);
        const auto endTime = chrono::system_clock::now().time_since_epoch();
        auto timeDiff = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << "time : " << timeDiff.count() << "ms, "
             << "testCase : " << testCase << ", answer : " << result << endl;
    }
    return 0;
}
