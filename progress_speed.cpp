#include <string>
#include <vector>
#include <queue>

using namespace std;

/*
progresses	                speeds	                return
[93, 30, 55]	            [1, 30, 5]	            [2, 1]
[95, 90, 99, 99, 80, 99]	[1, 1, 1, 1, 1, 1]	    [1, 3, 2]
*/
vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    queue<int> q;    
    int curProgressIdx = 0, counter = 0, exceed100Count = 0;
    
    for(int& element : progresses)
        q.push(element);

    while(true){
A:            
        if(q.empty()){
            if(exceed100Count > 0)
                answer.push_back(exceed100Count);
            break;
        }
        int& frontElement = q.front();
        if(frontElement + speeds[curProgressIdx] * counter >= 100){
            ++exceed100Count;  
            ++curProgressIdx;          
            q.pop();
            goto A;
        }
        else{            
            if(exceed100Count > 0)
                answer.push_back(exceed100Count);
            
            exceed100Count = 0;
            counter++;
        }
    }
    return answer;
}

int main(void)
{
    vector<int> p{93,30,55};
    vector<int> s{1,30,5};
    solution(p,s);
    return 0;
}