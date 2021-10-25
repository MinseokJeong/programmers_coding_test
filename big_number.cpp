#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

/*
가장 큰 수
문제 설명
0 또는 양의 정수가 주어졌을 때, 정수를 이어 붙여 만들 수 있는 가장 큰 수를 알아내 주세요.

예를 들어, 주어진 정수가 [6, 10, 2]라면 [6102, 6210, 1062, 1026, 2610, 2106]를 만들 수 있고, 이중 가장 큰 수는 6210입니다.

0 또는 양의 정수가 담긴 배열 numbers가 매개변수로 주어질 때, 순서를 재배치하여 만들 수 있는 가장 큰 수를 문자열로 바꾸어 return 하도록 solution 함수를 작성해주세요.

제한 사항
numbers의 길이는 1 이상 100,000 이하입니다.
numbers의 원소는 0 이상 1,000 이하입니다.
정답이 너무 클 수 있으니 문자열로 바꾸어 return 합니다.
입출력 예
numbers	return
[6, 10, 2]	"6210"
[3, 30, 34, 5, 9]	"9534330"
*/
enum digit_e
{
    unit,
    ten,
    hundred,
    thousand
};

string solution(vector<int> numbers)
{
    vector<int> answerVector;
    vector<int> units;
    vector<int> tens;
    vector<int> hundreds;
    vector<int> thousands;

    digit_e curDigit = digit_e::unit;

    for (const auto &number : numbers)
    {
        double logVal = floor(log10(number));
        if (logVal < 1.0)
        {
            units.push_back(number);
        }
        else if (logVal < 2.0)
        {
            tens.push_back(number);
        }
        else if (logVal < 3.0)
        {
            hundreds.push_back(number);
        }
        else
        {
            thousands.push_back(number);
        }
    }

    sort(units.begin(), units.end());
    sort(tens.begin(), tens.end());
    sort(hundreds.begin(), hundreds.end());
    sort(thousands.begin(), thousands.end());

    while ((!units.empty() || !tens.empty() || !hundreds.empty() || !thousands.empty()))
    {
        int selectedNumber = -1;
        int itVal;

        auto unitIt = units.rbegin();
        auto tenIt = tens.rbegin();
        auto hundredIt = hundreds.rbegin();
        auto thousandIt = thousands.rbegin();

        if (unitIt != units.rend())
        {
            selectedNumber = *unitIt;
            curDigit = digit_e::unit;
        }

        if (tenIt != tens.rend())
        {
            if (selectedNumber == -1)
            {
                selectedNumber = *tenIt;
                curDigit = digit_e::ten;
            }
            else
            {
                itVal = *tenIt;
                if ((itVal * 10 + selectedNumber) > (selectedNumber * 100 + itVal))
                {
                    selectedNumber = itVal;
                    curDigit = digit_e::ten;
                }
            }
        }

        if (hundredIt != hundreds.rend())
        {
            if (selectedNumber == -1)
            {
                selectedNumber = *hundredIt;
                curDigit = digit_e::hundred;
            }
            else
            {
                itVal = *hundredIt;
                if (curDigit == digit_e::unit)
                {
                    if ((itVal * 10 + selectedNumber) > (selectedNumber * 1000 + itVal))
                    {
                        selectedNumber = itVal;
                        curDigit = digit_e::hundred;
                    }
                }
                else
                {
                    if ((itVal * 100 + selectedNumber) > (selectedNumber * 1000 + itVal))
                    {
                        selectedNumber = itVal;
                        curDigit = digit_e::hundred;
                    }
                }
            }
        }

        if (thousandIt != thousands.rend())
        {
            if (selectedNumber == -1)
            {
                selectedNumber = *thousandIt;
                curDigit = digit_e::thousand;
            }
            else
            {
                itVal = *thousandIt;

                if (curDigit == digit_e::unit)
                {
                    if ((itVal * 10 + selectedNumber) > (selectedNumber * 10000 + itVal))
                    {
                        selectedNumber = itVal;
                        curDigit = digit_e::thousand;
                    }
                }
                else if (curDigit == digit_e::ten)
                {
                    if ((itVal * 100 + selectedNumber) > (selectedNumber * 10000 + itVal))
                    {
                        selectedNumber = itVal;
                        curDigit = digit_e::thousand;
                    }
                }
                else
                {
                    if ((itVal * 1000 + selectedNumber) > (selectedNumber * 10000 + itVal))
                    {
                        selectedNumber = itVal;
                        curDigit = digit_e::thousand;
                    }
                }
            }
        }

        answerVector.push_back(selectedNumber);
        switch (curDigit)
        {
        case digit_e::unit:
            units.pop_back();
            break;
        case digit_e::ten:
            tens.pop_back();
            break;
        case digit_e::hundred:
            hundreds.pop_back();
            break;
        case digit_e::thousand:
            thousands.pop_back();
            break;
        default:
            break;
        }
    }
    stringstream answerStrStream;
    bool allValueZero = true;
    for (int &number : answerVector)
    {
        answerStrStream << number;
        if(allValueZero && (number > 0))
        {
            allValueZero = false;
        }        
    }

    if(allValueZero)
        return "0";

    string answer = answerStrStream.str();    
    return answerStrStream.str();
}

int main(void)
{
#if 0
    // 868,86,8
    // 86 868
    // 868 86
    // 1,10,100,1000
    // 8
    srand(time(NULL));
    vector<int> randValues;
    for (int i = 0; i < 5; i++)
    {
        randValues.push_back(rand() % 1001);
    }

    cout << "element : ";
    for (auto &element : randValues)
    {
        cout << element << " ";
    }
    cout << endl;

    cout << solution(randValues) << endl;
#endif

#if 1
    vector<vector<int>> testCases{
        {6, 10, 2, 0},
        {3, 30, 34, 5, 9},
        {979, 97, 978, 81, 818, 817},
        {67,676,677},
        {0,0,0,0},
    };
    
    for (auto &testCase : testCases)
    {
        cout << "element : ";
        for (auto &element : testCase)
        {
            cout << element << " ";
        }
        cout << endl;

        cout << solution(testCase) << endl;
    }
  
#endif
    return 0;
}
