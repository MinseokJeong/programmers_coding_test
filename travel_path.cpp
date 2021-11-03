/*
여행경로
문제 설명
주어진 항공권을 모두 이용하여 여행경로를 짜려고 합니다. 항상 "ICN" 공항에서 출발합니다.

항공권 정보가 담긴 2차원 배열 tickets가 매개변수로 주어질 때, 방문하는 공항 경로를 배열에 담아 return 하도록 solution 함수를 작성해주세요.

제한사항
모든 공항은 알파벳 대문자 3글자로 이루어집니다.
주어진 공항 수는 3개 이상 10,000개 이하입니다.
tickets의 각 행 [a, b]는 a 공항에서 b 공항으로 가는 항공권이 있다는 의미입니다.
주어진 항공권은 모두 사용해야 합니다.
만일 가능한 경로가 2개 이상일 경우 알파벳 순서가 앞서는 경로를 return 합니다.
모든 도시를 방문할 수 없는 경우는 주어지지 않습니다.
입출력 예
tickets	return
[["ICN", "JFK"], ["HND", "IAD"], ["JFK", "HND"]]	["ICN", "JFK", "HND", "IAD"]
[["ICN", "SFO"], ["ICN", "ATL"], ["SFO", "ATL"], ["ATL", "ICN"], ["ATL","SFO"]]	["ICN", "ATL", "ICN", "SFO", "ATL", "SFO"]
입출력 예 설명
예제 #1

["ICN", "JFK", "HND", "IAD"] 순으로 방문할 수 있습니다.

예제 #2

["ICN", "SFO", "ATL", "ICN", "ATL", "SFO"] 순으로 방문할 수도 있지만 ["ICN", "ATL", "ICN", "SFO", "ATL", "SFO"] 가 알파벳 순으로 앞섭니다.
*/

#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>

using namespace std;

class Ticket
{
public:
    string *origin_ariport;
    string *destination_airport;

    Ticket(string *org, string *dst)
    {
        origin_ariport = org;
        destination_airport = dst;
    }

    Ticket()
    {
        origin_ariport = nullptr;
        destination_airport = nullptr;
    }
};

bool isTicketPossibleOrder(Ticket &first, Ticket &second)
{
    if (first.destination_airport->compare(second.origin_ariport->c_str()) == 0)
    {
        return true;
    }
    return false;
}

void findPath(list<Ticket *> &selected, list<Ticket *> &selectionPool, vector<string> &path)
{
    size_t selectionPoolSize = selectionPool.size();

    if (selectionPoolSize == 0)
    {
        if (path.empty())
        {
            for (auto it = selected.begin(); it != selected.end(); ++it)
            {
                path.push_back(*((*it)->origin_ariport));
            }
            path.push_back(*(selected.back()->destination_airport));
        }
        else
        {
            size_t i = 0;
            bool changeThePathToNew = false;
            bool midBreakFlag = false;

            for (auto it = selected.begin(); it != selected.end() && !changeThePathToNew; ++it)
            {
                string &tempStr = (*((*it)->origin_ariport));

                for (int j = 0; j < 3; j++)
                {
                    if (path[i].at(j) > tempStr.at(j))
                    {
                        changeThePathToNew = true;
                        break;
                    }
                    else if (path[i].at(j) < tempStr.at(j))
                    {
                        midBreakFlag = true;
                        break;
                    }
                }

                if (midBreakFlag)
                {
                    break;
                }
                ++i;
            }
/*
            string &tempStr = (*(selected.back()->destination_airport));
            for (int j = 0; j < 3; j++)
            {
                if (path.back().at(j) > tempStr.at(j))
                {
                    changeThePathToNew = true;
                    break;
                }
                break;                
            }
*/
            if (changeThePathToNew)
            {
                path.clear();
                for (auto it = selected.begin(); it != selected.end(); ++it)
                {
                    path.push_back(*((*it)->origin_ariport));
                }
                path.push_back(*(selected.back()->destination_airport));
            }
        }
        return;
    }

    if (selected.size() == 0)
    {
        for (size_t i = 0; i < selectionPoolSize; ++i)
        {
            auto frontElement = selectionPool.front();
            selectionPool.pop_front();

            if (frontElement->origin_ariport->compare("ICN") == 0)
            {
                selected.push_back(frontElement);
                findPath(selected, selectionPool, path);
                selected.pop_back();
            }

            selectionPool.push_back(frontElement);
        }
    }
    else
    {
        for (size_t i = 0; i < selectionPoolSize; ++i)
        {
            auto &lastSelectedTicket = selected.back();
            auto selectionPoolFrontElement = selectionPool.front();
            selectionPool.pop_front();
            if (isTicketPossibleOrder(*lastSelectedTicket, *selectionPoolFrontElement))
            {
                selected.emplace_back(selectionPoolFrontElement);
                findPath(selected, selectionPool, path);
                selected.pop_back();
            }
            selectionPool.push_back(selectionPoolFrontElement);
        }
    }
}

vector<string> solution(vector<vector<string>> tickets)
{
    list<Ticket *> ticketsToList;
    list<Ticket *> selectedTicket;
    vector<string> answer;
    Ticket *pTickets = new Ticket[tickets.size()];
    size_t idx = 0;

    // First make the ticket
    for (auto &ticket : tickets)
    {
        // To reduce the contruct time
        pTickets[idx].origin_ariport = &ticket[0];
        pTickets[idx].destination_airport = &ticket[1];
        ticketsToList.push_back(&pTickets[idx]);
        idx++;
    }

    findPath(selectedTicket, ticketsToList, answer);

    delete[] pTickets;

    return answer;
}

#include <iostream>
struct TEST_CASE
{
    vector<vector<string>> tickets;
    vector<string> answer;
};

void printVector(vector<string> v)
{
    for (auto &i : v)
    {
        cout << i << " ";
    }
}

int main(int argc, char *argv[])
{
    TEST_CASE t1{
        .tickets = {{"ICN", "JFK"}, {"HND", "IAD"}, {"JFK", "HND"}},
        .answer = {"ICN", "JFK", "HND", "IAD"}};

    TEST_CASE t2{
        .tickets = {{"ICN", "SFO"}, {"ICN", "ATL"}, {"SFO", "ATL"}, {"ATL", "ICN"}, {"ATL", "SFO"}},
        .answer = {"ICN", "ATL", "ICN", "SFO", "ATL", "SFO"}};

    cout << "t1 : answer -> ";
    printVector(t1.answer);
    cout << ", solution -> ";
    printVector(solution(t1.tickets));
    cout << endl;

    cout << "t2 : answer -> ";
    printVector(t2.answer);
    cout << ", solution -> ";
    printVector(solution(t2.tickets));
    cout << endl;

    return 0;
}