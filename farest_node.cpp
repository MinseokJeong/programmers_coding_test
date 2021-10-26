/*
가장 먼 노드
문제 설명
n개의 노드가 있는 그래프가 있습니다. 각 노드는 1부터 n까지 번호가 적혀있습니다.
1번 노드에서 가장 멀리 떨어진 노드의 갯수를 구하려고 합니다.
가장 멀리 떨어진 노드란 최단경로로 이동했을 때 간선의 개수가 가장 많은 노드들을 의미합니다.

노드의 개수 n, 간선에 대한 정보가 담긴 2차원 배열 vertex가 매개변수로 주어질 때,
1번 노드로부터 가장 멀리 떨어진 노드가 몇 개인지를 return 하도록 solution 함수를 작성해주세요.

제한사항
노드의 개수 n은 2 이상 20,000 이하입니다.
간선은 양방향이며 총 1개 이상 50,000개 이하의 간선이 있습니다.
vertex 배열 각 행 [a, b]는 a번 노드와 b번 노드 사이에 간선이 있다는 의미입니다.
입출력 예
n	vertex	return
6	[[3, 6], [4, 3], [3, 2], [1, 3], [1, 2], [2, 4], [5, 2]]	3
입출력 예 설명
예제의 그래프를 표현하면 아래 그림과 같고, 1번 노드에서 가장 멀리 떨어진 노드는 4,5,6번 노드입니다.

image.png
*/
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

class Node
{
public:
    int nodeNumber;
    set<Node *> linkedNodes;

    Node(int number) : nodeNumber(number){};

    void addNode(Node *pNode)
    {
        if (linkedNodes.find(pNode) == linkedNodes.end())
        {
            linkedNodes.insert(pNode);
        }
    }
};

vector<bool> visitedNodeNumberTable(200001);
vector<int> shortestLineCountFromStartNode(200001);
queue<Node *> nextNodeToVisit;
void findShortestPath(Node *startNode)
{
    fill_n(visitedNodeNumberTable.begin(), 20001, false);
    fill_n(shortestLineCountFromStartNode.begin(), 20001, INT32_MAX);
    queue<Node *> tempQ;
    swap(nextNodeToVisit, tempQ);

    Node *pCurNode = startNode;
    int curNodeNumber = pCurNode->nodeNumber;
    shortestLineCountFromStartNode[curNodeNumber] = 0;
    nextNodeToVisit.push(pCurNode);

    while (pCurNode != nullptr)
    {
        curNodeNumber = pCurNode->nodeNumber;
        if (visitedNodeNumberTable[curNodeNumber] == true)
        {
            if (nextNodeToVisit.empty())
            {
                pCurNode = nullptr;
                break;
            }
            else
            {
                pCurNode = nextNodeToVisit.front();
                nextNodeToVisit.pop();
                continue;
            }
        }

        visitedNodeNumberTable[curNodeNumber] = true;

        auto &linkedNodesOfCurrentNode = pCurNode->linkedNodes;

        for (auto &pNode : linkedNodesOfCurrentNode)
        {
            int nodeNumber = pNode->nodeNumber;
            int nodePathCost = shortestLineCountFromStartNode[curNodeNumber] + 1;
            if (nodePathCost < shortestLineCountFromStartNode[nodeNumber])
            {
                shortestLineCountFromStartNode[nodeNumber] = nodePathCost;
            }

            nextNodeToVisit.push(pNode);
        }
    }
}

vector<Node *> nodesVector(200001);
void makeNodes(vector<vector<int>> &nodeInfos)
{
    for (size_t i = 0; i < nodesVector.size(); ++i)
    {
        if (nodesVector[i] != nullptr)
        {
            nodesVector[i]->linkedNodes.clear();
        }
    }    

    for (auto &nodeInfo : nodeInfos)
    {
        if (nodesVector[nodeInfo[0]] == nullptr)
        {
            nodesVector[nodeInfo[0]] = new Node(nodeInfo[0]);
        }

        if (nodesVector[nodeInfo[1]] == nullptr)
        {
            nodesVector[nodeInfo[1]] = new Node(nodeInfo[1]);
        }

        nodesVector[nodeInfo[0]]->addNode(nodesVector[nodeInfo[1]]);
        nodesVector[nodeInfo[1]]->addNode(nodesVector[nodeInfo[0]]);
    }
}

int solution(int n, vector<vector<int>> edge)
{
    makeNodes(edge);
    findShortestPath(nodesVector[1]);

    vector<int> onlyExist;
    onlyExist.reserve(20000);
    for (size_t i = 1; i < shortestLineCountFromStartNode.size(); ++i)
    {
        if (shortestLineCountFromStartNode[i] != INT32_MAX)
        {
            onlyExist.push_back(shortestLineCountFromStartNode[i]);
        }
    }

    sort(onlyExist.begin(), onlyExist.end());

    int sameMaximumPathCostCount = 0;
    int maximumPathCost = onlyExist.back();
    for (auto reverse_it = onlyExist.rbegin(); reverse_it != onlyExist.rend(); ++reverse_it)
    {
        if (*reverse_it == maximumPathCost)
        {
            ++sameMaximumPathCostCount;
        }
        else
        {
            break;
        }
    }

    return sameMaximumPathCostCount;
}

#include <iostream>
int main(int arg, char **argv)
{
    vector<vector<int>> testCase{{3, 6}, {4, 3}, {3, 2}, {1, 3}, {1, 2}, {2, 4}, {5, 2}};

    int result = solution(6, testCase);
    cout << "Result : " << result << endl;
    return 0;
}