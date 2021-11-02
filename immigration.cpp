/*
입국심사
문제 설명
n명이 입국심사를 위해 줄을 서서 기다리고 있습니다. 각 입국심사대에 있는 심사관마다 심사하는데 걸리는 시간은 다릅니다.

처음에 모든 심사대는 비어있습니다. 한 심사대에서는 동시에 한 명만 심사를 할 수 있습니다. 가장 앞에 서 있는 사람은 비어 있는 심사대로 가서 심사를 받을 수 있습니다. 하지만 더 빨리 끝나는 심사대가 있으면 기다렸다가 그곳으로 가서 심사를 받을 수도 있습니다.

모든 사람이 심사를 받는데 걸리는 시간을 최소로 하고 싶습니다.

입국심사를 기다리는 사람 수 n, 각 심사관이 한 명을 심사하는데 걸리는 시간이 담긴 배열 times가 매개변수로 주어질 때, 모든 사람이 심사를 받는데 걸리는 시간의 최솟값을 return 하도록 solution 함수를 작성해주세요.

제한사항
입국심사를 기다리는 사람은 1명 이상 1,000,000,000명 이하입니다.
각 심사관이 한 명을 심사하는데 걸리는 시간은 1분 이상 1,000,000,000분 이하입니다.
심사관은 1명 이상 100,000명 이하입니다.
입출력 예
n	times	return
6	[7, 10]	28
입출력 예 설명
가장 첫 두 사람은 바로 심사를 받으러 갑니다.

7분이 되었을 때, 첫 번째 심사대가 비고 3번째 사람이 심사를 받습니다.

10분이 되었을 때, 두 번째 심사대가 비고 4번째 사람이 심사를 받습니다.

14분이 되었을 때, 첫 번째 심사대가 비고 5번째 사람이 심사를 받습니다.

20분이 되었을 때, 두 번째 심사대가 비지만 6번째 사람이 그곳에서 심사를 받지 않고 1분을 더 기다린 후에 첫 번째 심사대에서 심사를 받으면 28분에 모든 사람의 심사가 끝납니다.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct WAIT_LINE
{
public:    
    int timeValue;
    long long howMuchTimePersonWait;
    int waitingPersonCount;

    WAIT_LINE(int t)
    {
        timeValue = t;
        howMuchTimePersonWait = t;
        waitingPersonCount = 0;
    }
};

long long solution(int n, vector<int> times)
{
    auto compareWaitLine = [](const WAIT_LINE& lhs,const WAIT_LINE& rhs)->bool
    {        
        return !(lhs.howMuchTimePersonWait < rhs.howMuchTimePersonWait);        
    };

    priority_queue<WAIT_LINE,vector<WAIT_LINE>,decltype(compareWaitLine)> p_Q(compareWaitLine);            
    
    for(auto& t : times)
    {
        p_Q.push(WAIT_LINE(t));
    }

    long long answer = 0;
    while(n > 0 && !p_Q.empty())
    {
        WAIT_LINE wl = p_Q.top();
        p_Q.pop();
        ++wl.waitingPersonCount;
        --n;
        wl.howMuchTimePersonWait += wl.timeValue;
        answer = max(answer,(long long)(wl.timeValue * wl.waitingPersonCount));
        p_Q.push(wl);
    }
    
    return answer;
}

#include <iostream>
struct TEST_CASE
{
    int n;
    vector<int> times;
    int answer;
};
int main(int argc, char **argv)
{
    TEST_CASE t1{
        .n = 6,
        .times = {7, 10},
        .answer = 28};

    cout << "Test Case 1 : answer(" << t1.answer << "), solution(" << solution(t1.n, t1.times) << ")" << endl;
    return 0;
}