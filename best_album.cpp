/*
베스트앨범
문제 설명
스트리밍 사이트에서 장르 별로 가장 많이 재생된 노래를 두 개씩 모아 베스트 앨범을 출시하려 합니다. 노래는 고유 번호로 구분하며, 노래를 수록하는 기준은 다음과 같습니다.

속한 노래가 많이 재생된 장르를 먼저 수록합니다.
장르 내에서 많이 재생된 노래를 먼저 수록합니다.
장르 내에서 재생 횟수가 같은 노래 중에서는 고유 번호가 낮은 노래를 먼저 수록합니다.
노래의 장르를 나타내는 문자열 배열 genres와 노래별 재생 횟수를 나타내는 정수 배열 plays가 주어질 때, 베스트 앨범에 들어갈 노래의 고유 번호를 순서대로 return 하도록 solution 함수를 완성하세요.

제한사항
genres[i]는 고유번호가 i인 노래의 장르입니다.
plays[i]는 고유번호가 i인 노래가 재생된 횟수입니다.
genres와 plays의 길이는 같으며, 이는 1 이상 10,000 이하입니다.
장르 종류는 100개 미만입니다.
장르에 속한 곡이 하나라면, 하나의 곡만 선택합니다.
모든 장르는 재생된 횟수가 다릅니다.
입출력 예
genres	plays	return
["classic", "pop", "classic", "classic", "pop"]	[500, 600, 150, 800, 2500]	[4, 1, 3, 0]
입출력 예 설명
classic 장르는 1,450회 재생되었으며, classic 노래는 다음과 같습니다.

고유 번호 3: 800회 재생
고유 번호 0: 500회 재생
고유 번호 2: 150회 재생
pop 장르는 3,100회 재생되었으며, pop 노래는 다음과 같습니다.

고유 번호 4: 2,500회 재생
고유 번호 1: 600회 재생
따라서 pop 장르의 [4, 1]번 노래를 먼저, classic 장르의 [3, 0]번 노래를 그다음에 수록합니다.

※ 공지 - 2019년 2월 28일 테스트케이스가 추가되었습니다.

Start : 2021.11.01 23:03
End : 2021.11.01 23:38

*/



#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct GenrePlays
{
    int mostPlaysSongIndex;
    int mostPlaysSongCount;
    
    int secondPlaysSongIndex;
    int secondPlaysSongCount;

    int currentGenreTotalPlaysCount;

    bool hasTwoIdx;

    GenrePlays(int idx, int totalPlayCount)
    {
        mostPlaysSongIndex = idx;        
        mostPlaysSongCount = totalPlayCount;

        secondPlaysSongIndex = -1;        
        secondPlaysSongCount = 0;
     
        currentGenreTotalPlaysCount = totalPlayCount;

        hasTwoIdx = false;
    }

    void compare(int idx, int plays)
    {
        if(hasTwoIdx)
        {
            if(plays > mostPlaysSongCount)
            {
                secondPlaysSongIndex = mostPlaysSongIndex;
                secondPlaysSongCount = mostPlaysSongCount;

                mostPlaysSongIndex = idx;
                mostPlaysSongCount = plays;
            }
            else if(plays > secondPlaysSongCount)
            {
                secondPlaysSongIndex = idx;
                secondPlaysSongCount = plays;
            }
        }
        else
        {
            if(plays > mostPlaysSongCount)
            {
                secondPlaysSongIndex = mostPlaysSongIndex;
                secondPlaysSongCount = mostPlaysSongCount;

                mostPlaysSongIndex = idx;
                mostPlaysSongCount = plays;
            }
            else
            {
                secondPlaysSongIndex = idx;
                secondPlaysSongCount = plays;
            }

            hasTwoIdx = true;
        }

        currentGenreTotalPlaysCount += plays;

    }
};

vector<int> solution(vector<string> genres, vector<int> plays) 
{
    vector<int> answer;
    unordered_map<string,GenrePlays*> genreMap;
    vector<GenrePlays*> forOrderingTempVector;
    
    size_t genresSize = genres.size();
    
    for(size_t i = 0 ; i < genresSize; ++i)
    {
        
         if(genreMap.find(genres[i]) != genreMap.end())
        {
            genreMap[genres[i]]->compare(i,plays[i]);
        }
        else
        {
            GenrePlays* pGenrePlays = new GenrePlays(i,plays[i]);
            genreMap[genres[i]] = pGenrePlays;
            forOrderingTempVector.push_back(pGenrePlays);
        }
    }
    
    sort(forOrderingTempVector.begin(),forOrderingTempVector.end(),
    [](const GenrePlays* lhs,const GenrePlays* rhs)->bool
    {
        return lhs->currentGenreTotalPlaysCount > rhs->currentGenreTotalPlaysCount;        
    });
    
    for(auto& element : forOrderingTempVector)
    {
        if(element->hasTwoIdx)
        {
            answer.push_back(element->mostPlaysSongIndex);
            answer.push_back(element->secondPlaysSongIndex);
        }
        else
        {
            answer.push_back(element->mostPlaysSongIndex);
        }

        delete element;
    }

    //clear the memory
    

    return answer;
}

#include <iostream>
struct TEST_CASE{
    vector<string> genres;
    vector<int> plays;
    vector<int> answer;
};

void printVector(vector<int> v)
{
    for(auto& i : v)
    {
        cout<<i<<" ";
    }
}
int main(int argc, char *argv[])
{
    TEST_CASE t1{
        .genres = {"classic", "pop", "classic", "classic", "pop"},
        .plays = {500, 600, 150, 800, 2500},
        .answer = {4, 1, 3, 0},
    };
    cout<<"Answer : ";
    printVector(t1.answer);
    cout<<"Solution : ";
    printVector(solution(t1.genres,t1.plays));
    cout<<endl;
    return 0;
}