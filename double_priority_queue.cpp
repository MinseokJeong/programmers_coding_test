/*
이중우선순위큐
문제 설명
이중 우선순위 큐는 다음 연산을 할 수 있는 자료구조를 말합니다.

명령어	수신 탑(높이)
I 숫자	큐에 주어진 숫자를 삽입합니다.
D 1	큐에서 최댓값을 삭제합니다.
D -1	큐에서 최솟값을 삭제합니다.
이중 우선순위 큐가 할 연산 operations가 매개변수로 주어질 때, 모든 연산을 처리한 후 큐가 비어있으면 [0,0] 비어있지 않으면 [최댓값, 최솟값]을 return 하도록 solution 함수를 구현해주세요.

제한사항
operations는 길이가 1 이상 1,000,000 이하인 문자열 배열입니다.
operations의 원소는 큐가 수행할 연산을 나타냅니다.
원소는 “명령어 데이터” 형식으로 주어집니다.- 최댓값/최솟값을 삭제하는 연산에서 최댓값/최솟값이 둘 이상인 경우, 하나만 삭제합니다.
빈 큐에 데이터를 삭제하라는 연산이 주어질 경우, 해당 연산은 무시합니다.
입출력 예
operations	return
["I 16","D 1"]	[0,0]
["I 7","I 5","I -5","D -1"]	[7,5]
입출력 예 설명
16을 삽입 후 최댓값을 삭제합니다. 비어있으므로 [0,0]을 반환합니다.
7,5,-5를 삽입 후 최솟값을 삭제합니다. 최대값 7, 최소값 5를 반환합니다.

출처
*/

#include <string>
#include <vector>
#include <cstdio>

using namespace std;

enum COMMAND_ENUM
{
    cmd_insert,
    cmd_delete_max_value,
    cmd_delete_min_value,
};

struct COMMAND
{
    COMMAND_ENUM cmd;
    int data;

    COMMAND(COMMAND_ENUM e_cmd,int d)
    {
        cmd = e_cmd;
        data = d;
    }
};

vector<COMMAND> makeCommands(vector<string>& operations)
{
    char cmdChar;
    int value;
    COMMAND_ENUM commandEnum;    

    vector<COMMAND> commands;
    commands.reserve(operations.size());

    
    for(auto& operation : operations)
    {
        sscanf(operation.c_str(),"%c %d",&cmdChar,&value);
       
        if(cmdChar == 'I')
        {
            commandEnum = COMMAND_ENUM::cmd_insert;
        }
        else
        {
            if(value == 1)
            {
                commandEnum = COMMAND_ENUM::cmd_delete_max_value;
            }
            else
            {
                commandEnum = COMMAND_ENUM::cmd_delete_min_value;
            }
        }

        commands.emplace_back(commandEnum,value);
    }
    
    return commands;
}

class DoublePriorityQ
{
private:
    class InteagerDataNode
    {
    public:    
        int data;
        InteagerDataNode* pPrev;
        InteagerDataNode* pNext;

        InteagerDataNode(int d,InteagerDataNode* prev,InteagerDataNode* next)  
        {
            data = d;
            pPrev = prev;
            pNext = next;
        }

        InteagerDataNode(int d)  
        {
            data = d;
            pPrev = nullptr;
            pNext = nullptr;
        }

        InteagerDataNode()
        {
            data = 0;
            pPrev = nullptr;
            pNext = nullptr;
        }
    };

    InteagerDataNode* pHead;
    InteagerDataNode* pTail;
    int nodeCount;
public:
    DoublePriorityQ()
    {
        pHead = nullptr;
        pTail = nullptr;
        nodeCount = 0;
    }

    ~DoublePriorityQ()
    {
        InteagerDataNode* pIter = pHead;            
        InteagerDataNode* pTemp = nullptr;
            
        while(pIter != nullptr)
        {
            pTemp = pIter->pNext;
            delete pIter;
            pIter = pTemp;            
        }            
    }

    void add(int v)
    {
        InteagerDataNode* pNewNode = new InteagerDataNode(v);
        
        if(pHead == nullptr)
        {
            pHead = pNewNode;
            pTail = pNewNode;
        }
        else
        {            
            InteagerDataNode* pIter = pHead;            
            
            while(pIter != nullptr)
            {
                if(v > pIter->data)
                {
                    pNewNode->pPrev = pIter->pPrev;
                    pIter->pPrev = pNewNode;                    
                    pNewNode->pNext = pIter;

                    if(pIter == pHead)
                    {
                        pHead = pNewNode;
                    }
                    break;
                }
                
                pIter = pIter->pNext;
            }

            if(pIter == nullptr)
            {
                pTail->pNext = pNewNode;
                pNewNode->pPrev = pTail;
                
                pTail = pNewNode;
            }
        }

        ++nodeCount;
    }

    void deleteMax()
    {
        if(pHead == nullptr)
        {
            return;
        }

        if(pHead == pTail)
        {
            delete pHead;
            pHead = nullptr;
            pTail = nullptr;
        }
        else
        {
            InteagerDataNode* pTemp = pHead->pNext;
            delete pHead;
            pHead = pTemp;
        }

        --nodeCount;
    }

    void deleteMin()
    {
        if(pTail == nullptr)
        {
            return;
        }

        if(pTail == pHead)
        {
            delete pTail;
            pTail = nullptr;
            pHead = nullptr;
        }
        else
        {
            InteagerDataNode* pTemp = pTail->pPrev;
            delete pTail;
            pTail = pTemp;
            pTail->pNext = nullptr;
        }

        --nodeCount;
    }

    int getMax()
    {
        if(pHead != nullptr)
        {
            return pHead->data;
        }

        return 0;
    }

    int getMin()
    {
        if(pTail != nullptr)
        {
            return pTail->data;
        }

        return 0;
    }
    
};

vector<int> solution(vector<string> operations) 
{
    DoublePriorityQ dobulePrioirityQueue;

    auto commands = makeCommands(operations);
    
    for(auto& command : commands)
    {
        switch (command.cmd)
        {
        case COMMAND_ENUM::cmd_insert:
            dobulePrioirityQueue.add(command.data);
            break;
        case COMMAND_ENUM::cmd_delete_max_value:
            dobulePrioirityQueue.deleteMax();
            break;
        case COMMAND_ENUM::cmd_delete_min_value:
            dobulePrioirityQueue.deleteMin();
            break;
        default:
            break;
        }        
    }
    
    return {dobulePrioirityQueue.getMax(),dobulePrioirityQueue.getMin()};
}


struct TEST_CASE
{
    vector<string> operations;
    vector<int> answers;
};

#include <iostream>

int main(int argc, char** argv)
{
    TEST_CASE t1 = {
        .operations = {"I 16","D 1"},
        .answers = {0,0},
    };

    TEST_CASE t2 = {
        .operations = {"I 7","I 5","I -5","D -1"},
        .answers = {7,5},
    };

    TEST_CASE t3 = {
        .operations = {"I -45", "I 653", "D 1", "I -642", "I 45", "I 97", "D 1", "D -1", "I 333"},
        .answers = {333,-45},
    };

    auto solutionReturn = solution(t1.operations);
    cout<<"t1 : answer("<<t1.answers[0]<<","<<t1.answers[1]<<"), solution("<<solutionReturn[0]<<","<<solutionReturn[1]<<")"<<endl;
    
    solutionReturn = solution(t2.operations);
    cout<<"t2 : answer("<<t2.answers[0]<<","<<t2.answers[1]<<"), solution("<<solutionReturn[0]<<","<<solutionReturn[1]<<")"<<endl;

    solutionReturn = solution(t3.operations);
    cout<<"t3 : answer("<<t3.answers[0]<<","<<t3.answers[1]<<"), solution("<<solutionReturn[0]<<","<<solutionReturn[1]<<")"<<endl;
    
    return 0;
}

