/*
다리를 지나는 트럭
문제 설명
트럭 여러 대가 강을 가로지르는 일차선 다리를 정해진 순으로 건너려 합니다. 모든 트럭이 다리를 건너려면 최소 몇 초가 걸리는지 알아내야 합니다. 다리에는 트럭이 최대 bridge_length대 올라갈 수 있으며, 다리는 weight 이하까지의 무게를 견딜 수 있습니다. 단, 다리에 완전히 오르지 않은 트럭의 무게는 무시합니다.

예를 들어, 트럭 2대가 올라갈 수 있고 무게를 10kg까지 견디는 다리가 있습니다. 무게가 [7, 4, 5, 6]kg인 트럭이 순서대로 최단 시간 안에 다리를 건너려면 다음과 같이 건너야 합니다.

경과 시간	다리를 지난 트럭	다리를 건너는 트럭	대기 트럭
0	[]	[]	[7,4,5,6]
1~2	[]	[7]	[4,5,6]
3	[7]	[4]	[5,6]
4	[7]	[4,5]	[6]
5	[7,4]	[5]	[6]
6~7	[7,4,5]	[6]	[]
8	[7,4,5,6]	[]	[]
따라서, 모든 트럭이 다리를 지나려면 최소 8초가 걸립니다.

solution 함수의 매개변수로 다리에 올라갈 수 있는 트럭 수 bridge_length, 다리가 견딜 수 있는 무게 weight, 트럭 별 무게 truck_weights가 주어집니다. 이때 모든 트럭이 다리를 건너려면 최소 몇 초가 걸리는지 return 하도록 solution 함수를 완성하세요.

제한 조건
bridge_length는 1 이상 10,000 이하입니다.
weight는 1 이상 10,000 이하입니다.
truck_weights의 길이는 1 이상 10,000 이하입니다.
모든 트럭의 무게는 1 이상 weight 이하입니다.
입출력 예
bridge_length	weight	truck_weights	return
2	10	[7,4,5,6]	8
100	100	[10]	101
100	100	[10,10,10,10,10,10,10,10,10,10]	110
출처
※ 공지 - 2020년 4월 06일 테스트케이스가 추가되었습니다
*/

#include <string>
#include <vector>
#include <queue>
using namespace std;

class Bridge
{
private:
    struct TruckWithTimestamp
    {
        int truckWeight;
        int bridgeTime;
        
        TruckWithTimestamp(int tw, int bt)
        {
            truckWeight = tw;
            bridgeTime = bt;
        }
    };

private:
    const int bridge_length;
    const int bridge_weight;
    int bridgeTime;
    int bridgeCurrentWeight;
    queue<TruckWithTimestamp> trucksOnTheBridge;

public:
    Bridge(const int bl, const int bw) : bridge_length(bl), bridge_weight(bw)
    {
        bridgeTime = 0;
        bridgeCurrentWeight = 0;
    }

    void timePass()
    {
        bridgeTime++;

        if (trucksOnTheBridge.empty())
        {
            return;
        }

        auto &frontTruckInfo = trucksOnTheBridge.front();
        int frontTruckPassedTime = bridgeTime - frontTruckInfo.bridgeTime;
        if (frontTruckPassedTime >= bridge_length)
        {
            bridgeCurrentWeight -= frontTruckInfo.truckWeight;
            trucksOnTheBridge.pop();
        }
    }
    
    bool addTruck(int truck_weight)
    {
        //Check the weight
        if(bridgeCurrentWeight + truck_weight > bridge_weight)
        {
            return false;
        }

        //Check the maximum possible load truck on the bridge
        if(trucksOnTheBridge.size() + 1 > bridge_length)
        {
            return false;
        }

        trucksOnTheBridge.push(TruckWithTimestamp(truck_weight,bridgeTime));
        bridgeCurrentWeight += truck_weight;

        return true;
    }

    bool isBridgeEmtpy()
    {
        return trucksOnTheBridge.empty();
    }

    int getTime()
    {
        return bridgeTime;
    }
};
int solution(int bridge_length, int weight, vector<int> truck_weights)
{
    Bridge bridge(bridge_length,weight);
    size_t totalTruck = truck_weights.size();
    
    for(auto& truckWeight : truck_weights)
    {
        while(1)
        {
            if(bridge.addTruck(truckWeight))
            {
                bridge.timePass();
                break;
            }
            else
            {
                bridge.timePass();
            }
        }
    }

    while(!bridge.isBridgeEmtpy())
    {
        bridge.timePass();
    }

    return bridge.getTime() + 1;
}

struct TEST_CASE
{
    int bridge_length;
    int weight;
    vector<int> truck_wieghts;
    int answer;
};

#include <iostream>
int main(int argc, char **argv)
{
    TEST_CASE t1 = {
        .bridge_length = 2,
        .weight = 10,
        .truck_wieghts = {7, 4, 5, 6},
        .answer = 8,
    };

    TEST_CASE t2 = {
        .bridge_length = 100,
        .weight = 100,
        .truck_wieghts = {10},
        .answer = 101,
    };

    TEST_CASE t3 = {
        .bridge_length = 100,
        .weight = 100,
        .truck_wieghts = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
        .answer = 110,
    };

    cout << "t1 : answer(" << t1.answer << "), solution(" << solution(t1.bridge_length, t1.weight, t1.truck_wieghts) << ")" << endl;
    cout << "t2 : answer(" << t2.answer << "), solution(" << solution(t2.bridge_length, t2.weight, t2.truck_wieghts) << ")" << endl;
    cout << "t3 : answer(" << t3.answer << "), solution(" << solution(t3.bridge_length, t3.weight, t3.truck_wieghts) << ")" << endl;

    return 0;
}